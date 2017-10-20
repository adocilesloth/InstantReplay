/*******************************************
A Docile Sloth 2017 (adocilesloth@gmail.com)
*******************************************/
#pragma once
//Desktop
bool get_desktop_mute();
void get_desktop_mute(bool &chan1, bool &chan2);
void toggle_desktop_mute();
void set_desktop_mute(bool chan0);
void set_desktop_mute(bool chan1, bool chan2);

//Auxillary / Mic;
bool get_aux_mute();
void get_aux_mute(bool &chan3, bool &chan4, bool &chan5);
void toggle_aux_mute();
void set_aux_mute(bool chan0);
void set_aux_mute(bool chan3, bool chan4, bool chan5);
