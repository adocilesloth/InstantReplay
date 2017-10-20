/*******************************************
A Docile Sloth 2017 (adocilesloth@gmail.com)
*******************************************/
#pragma once
#include <obs-module.h>
#include <obs-frontend-api.h>
#include <string>

void replayStartup();
void instant_replay_hotkey(void*, obs_hotkey_id, obs_hotkey_t*, bool);
void instant_replay_save(obs_data_t *save_data, bool saving, void *);

bool get_enabled();
int get_wait();
int get_pause();
int get_replay();
std::string get_scene();
void replay_callout_init();
