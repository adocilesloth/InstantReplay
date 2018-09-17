/*******************************************
A Docile Sloth 2017 (adocilesloth@gmail.com)
*******************************************/
#include "InstantReplay.h"

OBS_DECLARE_MODULE()
OBS_MODULE_USE_DEFAULT_LOCALE("InstantReplay", "en-US")

bool obs_module_load(void)
{
	obs_frontend_add_save_callback(instant_replay_save, nullptr);
	replayStartup();
	replay_callout_init();
	return true;
}

void obs_module_unload(void)
{
	return;
}

const char *obs_module_author(void)
{
	return "A Docile Sloth & spreadfire1";
}

const char *obs_module_name(void)
{
	return "Instant Replay XT";
}

const char *obs_module_description(void)
{
	return "Extended Edition. Scene switching support for instant replays";
}
