/*******************************************
A Docile Sloth 2017 (adocilesloth@gmail.com)
*******************************************/
#include <obs.h>

//Desktop
bool get_desktop_mute()
{
	obs_source_t* sceneUsed = obs_get_output_source(1);
	if(sceneUsed)
	{
		if(obs_source_muted(sceneUsed))
		{
			obs_source_release(sceneUsed);
			return true;
		}
		obs_source_release(sceneUsed);
	}
	sceneUsed = obs_get_output_source(2);
	if(sceneUsed)
	{
		if(obs_source_muted(sceneUsed))
		{
			obs_source_release(sceneUsed);
			return true;
		}
		obs_source_release(sceneUsed);
	}
	return false;
}

void get_desktop_mute(bool &chan1, bool &chan2)
{
	obs_source_t* sceneUsed = obs_get_output_source(1);
	if(sceneUsed)
	{
		chan1 = obs_source_muted(sceneUsed);
		obs_source_release(sceneUsed);
	}
	sceneUsed = obs_get_output_source(2);
	if(sceneUsed)
	{
		chan2 = obs_source_muted(sceneUsed);
		obs_source_release(sceneUsed);
	}
	return;
}

void toggle_desktop_mute()
{
	obs_source_t* sceneUsed = obs_get_output_source(1);
	if(sceneUsed)
	{
		if(obs_source_muted(sceneUsed))
		{
			obs_source_set_muted(sceneUsed, false);
		}
		else
		{
			obs_source_set_muted(sceneUsed, true);
		}
		obs_source_release(sceneUsed);
	}
	sceneUsed = obs_get_output_source(2);
	if(sceneUsed)
	{
		if(obs_source_muted(sceneUsed))
		{
			obs_source_set_muted(sceneUsed, false);
		}
		else
		{
			obs_source_set_muted(sceneUsed, true);
		}
		obs_source_release(sceneUsed);
	}
	return;
}

void set_desktop_mute(bool chan0)
{
	obs_source_t* sceneUsed = obs_get_output_source(1);
	if(sceneUsed)
	{
		obs_source_set_muted(sceneUsed, chan0);
		obs_source_release(sceneUsed);
	}
	sceneUsed = obs_get_output_source(2);
	if(sceneUsed)
	{
		obs_source_set_muted(sceneUsed, chan0);
		obs_source_release(sceneUsed);
	}
	return;
}

void set_desktop_mute(bool chan1, bool chan2)
{
	obs_source_t* sceneUsed = obs_get_output_source(1);
	if(sceneUsed)
	{
		obs_source_set_muted(sceneUsed, chan1);
		obs_source_release(sceneUsed);
	}
	sceneUsed = obs_get_output_source(2);
	if(sceneUsed)
	{
		obs_source_set_muted(sceneUsed, chan2);
		obs_source_release(sceneUsed);
	}
	return;
}

//Auxillary / Mic
bool get_aux_mute()
{
	obs_source_t* sceneUsed = obs_get_output_source(3);
	if(sceneUsed)
	{
		if(obs_source_muted(sceneUsed))
		{
			obs_source_release(sceneUsed);
			return true;
		}
		obs_source_release(sceneUsed);
	}
	sceneUsed = obs_get_output_source(4);
	if(sceneUsed)
	{
		if(obs_source_muted(sceneUsed))
		{
			obs_source_release(sceneUsed);
			return true;
		}
		obs_source_release(sceneUsed);
	}
	sceneUsed = obs_get_output_source(5);
	if(sceneUsed)
	{
		if(obs_source_muted(sceneUsed))
		{
			obs_source_release(sceneUsed);
			return true;
		}
		obs_source_release(sceneUsed);
	}
	return false;
}

void get_aux_mute(bool &chan3, bool &chan4, bool &chan5)
{
	obs_source_t* sceneUsed = obs_get_output_source(3);
	if(sceneUsed)
	{
		chan3 = obs_source_muted(sceneUsed);
		obs_source_release(sceneUsed);
	}
	sceneUsed = obs_get_output_source(4);
	if(sceneUsed)
	{
		chan4 = obs_source_muted(sceneUsed);
		obs_source_release(sceneUsed);
	}
	sceneUsed = obs_get_output_source(5);
	if(sceneUsed)
	{
		chan5 = obs_source_muted(sceneUsed);
		obs_source_release(sceneUsed);
	}
	return;
}

void toggle_aux_mute()
{
	obs_source_t* sceneUsed = obs_get_output_source(3);
	if(sceneUsed)
	{
		if(obs_source_muted(sceneUsed))
		{
			obs_source_set_muted(sceneUsed, false);
		}
		else
		{
			obs_source_set_muted(sceneUsed, true);
		}
		obs_source_release(sceneUsed);
	}
	sceneUsed = obs_get_output_source(4);
	if(sceneUsed)
	{
		if(obs_source_muted(sceneUsed))
		{
			obs_source_set_muted(sceneUsed, false);
		}
		else
		{
			obs_source_set_muted(sceneUsed, true);
		}
		obs_source_release(sceneUsed);
	}
	sceneUsed = obs_get_output_source(5);
	if(sceneUsed)
	{
		if(obs_source_muted(sceneUsed))
		{
			obs_source_set_muted(sceneUsed, false);
		}
		else
		{
			obs_source_set_muted(sceneUsed, true);
		}
		obs_source_release(sceneUsed);
	}
	return;
}

void set_aux_mute(bool chan0)
{
	obs_source_t* sceneUsed = obs_get_output_source(3);
	if(sceneUsed)
	{
		obs_source_set_muted(sceneUsed, chan0);
		obs_source_release(sceneUsed);
	}
	sceneUsed = obs_get_output_source(4);
	if(sceneUsed)
	{
		obs_source_set_muted(sceneUsed, chan0);
		obs_source_release(sceneUsed);
	}
	sceneUsed = obs_get_output_source(5);
	if(sceneUsed)
	{
		obs_source_set_muted(sceneUsed, chan0);
		obs_source_release(sceneUsed);
	}
	return;
}

void set_aux_mute(bool chan3, bool chan4, bool chan5)
{
	obs_source_t* sceneUsed = obs_get_output_source(3);
	if(sceneUsed)
	{
		obs_source_set_muted(sceneUsed, chan3);
		obs_source_release(sceneUsed);
	}
	sceneUsed = obs_get_output_source(4);
	if(sceneUsed)
	{
		obs_source_set_muted(sceneUsed, chan4);
		obs_source_release(sceneUsed);
	}
	sceneUsed = obs_get_output_source(5);
	if(sceneUsed)
	{
		obs_source_set_muted(sceneUsed, chan5);
		obs_source_release(sceneUsed);
	}
	return;
}