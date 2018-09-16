/*******************************************
A Docile Sloth 2017 (adocilesloth@gmail.com)

spreadfire1 2018 (https://twitter.com/@spreadfire1)
rewrote and reused parts of https://github.com/obsproject/obs-studio/blob/master/UI/frontend-plugins/frontend-tools/data/scripts/instant-replay.lua, credit to https://github.com/jp9000

*******************************************/
#include "InstantReplay.h"
#include "audio_io_state.h"
#include <thread>
#include <atomic>

//#include <iostream>
#include <filesystem>
#include <util/platform.h>

#define do_log(level, format, ...) \
	blog(level, "[InstantReplay] " format, ##__VA_ARGS__)

#define warn(format, ...)  do_log(LOG_WARNING, format, ##__VA_ARGS__)
#define info(format, ...)  do_log(LOG_INFO,    format, ##__VA_ARGS__)

using namespace std;

namespace fs = std::experimental::filesystem;

static void ensure_directory_exists(std::string &path)
{
	replace(path.begin(), path.end(), '\\', '/');
	size_t last = path.rfind('/');
	if (last == std::string::npos)
		return;
	std::string directory = path.substr(0, last);
	os_mkdirs(directory.c_str());
}

static void FindBestFilename(string &strPath, bool noSpace)
{
	int num = 2;

	if (!os_file_exists(strPath.c_str()))
		return;

	const char *ext = strrchr(strPath.c_str(), '.');
	if (!ext)
		return;

	int extStart = int(ext - strPath.c_str());
	for (;;) {
		string testPath = strPath;
		string numStr;

		numStr = noSpace ? "_" : " (";
		numStr += to_string(num++);
		if (!noSpace)
			numStr += ")";

		testPath.insert(extStart, numStr);

		if (!os_file_exists(testPath.c_str())) {
			strPath = testPath;
			break;
		}
	}
}

std::thread replay;
std::atomic<bool> doReplay(false);

obs_hotkey_id id;

//Sleep function
#ifdef _WIN32
#include <Windows.h>
void psleep(unsigned milliseconds)
{
	Sleep(milliseconds);
}
#else
#include <unistd.h>

void psleep(unsigned milliseconds)
{
	usleep(milliseconds * 1000); // takes microseconds
}
#endif

void replayThread()
{
	while(true)
	{
		while(!doReplay)
		{
			psleep(33);
		}

		if(get_enabled())
		{
			//Pause to allow file to write
			int wait = get_wait();
			//psleep(wait); //Instant Replay XT functionality change: use wait time as maximum wait time. Switch to replay scene as soon as the replay buffer was saved to file
			int attempts = 0;

			//Call the procedure of the replay buffer named "get_last_replay" to
			//get the last replay created by the replay buffer
			obs_output_t* replay_output = obs_frontend_get_replay_buffer_output();
			if (replay_output != NULL)
			{
				proc_handler_t* ph = obs_output_get_proc_handler(replay_output);				
				//if (ph!=NULL)
				//	proc_handler_call(ph, "save", NULL); //call not necessary, since the replay buffer is saved on the same hotkey button press that InstantReplay is called with

				//attempt playback every 1 second
				//until the replay is available (or until maximum wait time passed)
				if (obs_output_active(replay_output))
				{
					attempts = 0;
					while ((attempts <= wait) && doReplay)
					{
						psleep(1000);
						string replay_path="";
						const char * cRP=NULL;
						info("get_last_replay path attempt %d", attempts);
						
						calldata_t* cd = calldata_create();
						if (proc_handler_call(ph, "get_last_replay", cd) && cd != NULL)
						{
							try
							{
								calldata_get_string(cd, "path", &cRP);
								if (cRP)
									replay_path = cRP;
								//replay_path = calldata_string(cd, "path");
							}
							catch (...)
							{
								warn("exception on calldata_get_string");
							}

						}
						cRP=NULL;
						calldata_free(cd);
						if (replay_path.empty())
						{
							info("get_last_replay path was empty on attempt %d", attempts);

							attempts++;
							if (attempts > wait)
							{
								doReplay = false;
								info("stop retrying after maximum number of attempts reached: %d", attempts);
							}

						}
						else
						{
							if (get_backup_enabled())
							{
								//Backup replay file to specified path
								string backup_path = get_backup_path();
								string dest_file;

								try {
									ensure_directory_exists(backup_path);
									
									dest_file = replay_path;
									dest_file.replace(0,dest_file.rfind("/") + 1, backup_path); //replace folder, keep file name
										
									FindBestFilename(dest_file,true); //check if file exists and rename it
									info("backup replay file '%s' to '%s'. %s", replay_path.c_str(), backup_path.c_str(), dest_file.c_str());

									fs::copy_file(replay_path, dest_file);
								}
								catch (fs::filesystem_error& e) {
									warn("Could not copy file '%s' to '%s'. %s", replay_path.c_str(), dest_file.c_str(), e.what());
								}
								catch (...)
								{
									warn("exception on backup replay file '%s', backup path '%s', destination file '%s'", replay_path.c_str(), backup_path.c_str(),dest_file.c_str());
								}
							}

							//Get Origin Scene
							obs_source_t* original_scene = obs_frontend_get_current_scene();
							if (original_scene == nullptr)
							{
								return;
							}
							const char *sceneUsedName = obs_source_get_name(original_scene);
							obs_source_release(original_scene);

							//If the path is valid and the source exists, update it with the
							//replay file to play back the replay. Otherwise, stop attempting to
							//replay after max wait time
							obs_source_t* replaysource = obs_get_source_by_name(get_replay_source_name().c_str());
							if (replaysource != NULL)
							{								
								obs_data_t *settings = obs_data_create();
								obs_data_set_string(settings, "local_file", replay_path.c_str());
								obs_data_set_bool(settings, "is_local_file", true);
								obs_data_set_bool(settings, "close_when_inactive", true);
								obs_data_set_bool(settings, "restart_on_activate", true);

								//updating will automatically cause the source to
								//refresh if the source is currently active, otherwise
								//the source will play whenever its scene is activated
								obs_source_update(replaysource, settings);

								obs_data_release(settings);
								obs_source_release(replaysource);
							}


							//Switch to Replay
							obs_source_t* replay_scene = obs_get_source_by_name(get_scene().c_str());
							obs_frontend_set_current_scene(replay_scene);
							obs_source_release(replay_scene);

							//wait for transition to end
							int pause = get_pause();
							psleep(pause);

							//mute mic and desktop
							bool chan1, chan2, chan3, chan4, chan5;
							if (get_D_mute())
							{
								get_desktop_mute(chan1, chan2);
								set_desktop_mute(true);
							}
							if (get_A_mute())
							{
								get_aux_mute(chan3, chan4, chan5);
								set_aux_mute(true);
							}

							//Wait for replay to finish
							int replay_time = get_replay() - (2 * pause);
							psleep(replay_time);

							//Switch back to origional scene
							original_scene = obs_get_source_by_name(sceneUsedName);
							obs_frontend_set_current_scene(original_scene);
							obs_source_release(original_scene);

							//allow transition
							psleep(pause);

							//unmute mic and desktop
							if (get_D_mute())
							{
								set_desktop_mute(chan1, chan2);
							}
							if (get_A_mute())
							{
								set_aux_mute(chan3, chan4, chan5);
							}
							doReplay = false;
							info("Successfully finished");
						}
					}
				}
				else
				{
					warn("Tried to save an instant replay, but the replay buffer is not active!");
				}
			}
			else
			{
				warn("No active replay buffer output existing!");
			}
			obs_output_release(replay_output);
		}
	}
}

void replayStartup()
{
	replay = std::thread(replayThread);
	return;
}


void instant_replay_hotkey(void *data, obs_hotkey_id id, obs_hotkey_t *hotkey, bool pressed)
{
	UNUSED_PARAMETER(id);
	UNUSED_PARAMETER(hotkey);

	if(pressed && obs_frontend_replay_buffer_active())
	{
		info("instant_replay_hotkey pressed and obs_frontend_replay_buffer_active");
		doReplay = true;
	}
}

void instant_replay_save(obs_data_t *save_data, bool saving, void *)
{
	if(saving)
	{
		obs_data_t *obj = obs_data_create();
		obs_data_set_array(obj, "hotkey", obs_hotkey_save(id));
		obs_data_set_obj(save_data, "InstantReplay", obj);
		obs_data_release(obj);
	}
	else
	{
		id = obs_hotkey_register_frontend("Instant Replay", "Instant Replay", instant_replay_hotkey, NULL);

		obs_data_t *obj = obs_data_get_obj(save_data, "InstantReplay");
		if(!obj)
		{
			obj = obs_data_create();
		}
		obs_hotkey_load(id, obs_data_get_array(obj, "hotkey"));
		obs_data_release(obj);
	}
}

void instant_replay_callback(enum obs_frontend_event event, void *private_data)
{
	if(event == OBS_FRONTEND_EVENT_EXIT)
	{
		obs_frontend_save();
	}
}
