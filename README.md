# Instant Replay XT

Plugin to allow Instant Replays  
It basically combines the "Automatic Scene Switching" and "Per Scene Volume"  
(from OBS Classic) plugins to allow instant replays in live streams.  


Instant Replay XT. Improved and extended version by [spreadfire1](https://steemit.com/@spreadfire1).
- Backup feature: Option to copy replay files to another folder.
- Replay Buffer Filename no longer has to be static. The plugin sets the Instant Replay Media Source to the current replay file before switching to the replay scene.
- No longer mandatory fixed pause waiting for the replay buffer file to write. Checking every second and switches as soon as the file is ready.

**===WINDOWS===**  
Windows is built and working for both 32bit and 64bit  

Drag and drop obs-studio folder into C:\Program Files  
(or wher ever you have obs-studio installed)  
Merge all files down and you should be good to go.  

**===LINUX===**  
Dependancies:  
OBS (duh)  
Qt5 dev  

Clone the git repo:  
	`git clone https://github.com/adocilesloth/InstantReplay.git`  
	
cd to where you downloaded the source  

Check the environment PATHS in Makefile  
	Make sure they match your OBS and Qt5 installations and fix if necessary.  
	(`OBS_API_INCLUDE` will not need updating as the files are in the git repo)  
  
Then run:  
```
make  
make install  
make clean (optional: if you want to remove the temporary .o and .so files)  
```

**===MAC===**  
Uh, sould work. Probably. Don't have a MAC to test with.  
So...  
You can try the LINUX instructions.  
Let me know if you get it to work!  

**===SETUP===**  
Open the settings popup under:  
`Tools -> Instant Replay Settings`  
	
Fill in the below settings:  
`Enable` - Enables/disables the plugin
`Write Pause (s)` - Pause to allow OBS to write the replay file. 
OBS can't instantly write a file. ~10 seconds should be okay. 
Find something that works for you  
(Functionality change in *Instant Replay XT*: Write Pause is the maximum amount of seconds you want to wait. If the replay file buffer was written before that, it switches to the Instant Replay scene immediately.)
`Transition Pause (ms)` - Length of the transition in milliseconds. 
If the stinger is at 30fps, multiply the number of 
frames by 33. 
If the stinger is at 60fps, multiply the number of 
frames by 16.  
`Replay Length (s)` - Length of the replay in seconds. 
OBS does not always write as much replay as you tell it 
to so this may need to be a second or two shorter than 
the buffer length  
`Replay Scene` - Scene to switch to that has the replay source. 
`Mute Desktop Audio` - Mute the Desktop Audio channels when replay is playing.
`Mute Mic/AUX` - Mute the Mic/Aux channels when replay is playing.

**XT settings**
`Backup Replay File` - Enables/disables the backup feature.
`Backup File Path` - After the replay file buffer was written, copy it to this path.
`Replay Source Name` - Name of the OBS Media Source you use to play the Instant Replay file. e.g. "Instant Replay Media Source".


Hit "OK"  

Open the Hotkeys under:  
`Settings -> Hotkeys`  
	
Find the `Instant Replay` hotkey  
Set it TO THE SAME KEY as you have `Save Replay` under `Replay Buffer` set to.  

**Deprecated**
This is no longer necessary in *Instant Replay XT*. The plugin sets the Instant Replay Media Source to the currently active replay file before switching to the replay scene.
> Setting up the replay source:  
>	Set your Recording to a constant name (so remove all the % stuff). Makes it  
>	easy to point your replay source to a file that will exist.  
>	Point your Media Source to what your replay will be saved as.  
