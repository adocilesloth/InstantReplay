/*******************************************
A Docile Sloth 2017 (adocilesloth@gmail.com)
*******************************************/
#include "InstantReplay.h"
#include "audio_io_state.h"
#include <thread>
#include <atomic>

//#include <fstream>

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
			psleep(wait);
			//Get Origin Scene
			obs_source_t* original_scene = obs_frontend_get_current_scene();
			if(original_scene == nullptr)
			{
				return;
			}
			const char *sceneUsedName = obs_source_get_name(original_scene);
			obs_source_release(original_scene);

			//Switch to Replay
			obs_source_t* replay_scene = obs_get_source_by_name(get_scene().c_str());
			obs_frontend_set_current_scene(replay_scene);
			obs_source_release(replay_scene);

			//wait for transition to end
			int pause = get_pause();
			psleep(pause);

			//mute mic and desktop
			bool chan1, chan2, chan3, chan4, chan5;
			get_desktop_mute(chan1, chan2);
			get_aux_mute(chan3, chan4, chan5);
			set_desktop_mute(true);
			set_aux_mute(true);

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
			set_desktop_mute(chan1, chan2);
			set_aux_mute(chan3, chan4, chan5);

			doReplay = false;
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
		id = obs_hotkey_register_frontend("Instat Replay", "Instant Replay", instant_replay_hotkey, NULL);

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
