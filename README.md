/************************************  
A Docile Sloth adocilesloth@gmail.com  
************************************/  
Plugin to allow Instant Replays  
It basically combines the "Automatic Scene Switching" and "Per Scene Volume"  
(from OBS Classic) plugins to allow instant replays in live streams.  

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
`Enable` - Enables/disbale the plugins  
`Write Pause (s)` - Pause to allow OBS to write the replay file. 
OBS can't instantly write a file. ~10 seconds should be okay. 
Find something that works for you  
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

Hit "OK"  

Open the Hotkeys under:  
`Settings -> Hotkeys`  
	
Find the `Instant Replay` hotkey  
Set it TO THE SAME KEY as you have `Save Replay` under `Replay Buffer` set to.  

Setting up the replay source:  
	Set your Recording to a constant name (so remove all the % stuff). Makes it  
	easy to point your replay source to a file that will exist.  
	Point your Media Source to what your replay will be saved as.  
	
Notes:  
	When the Instant Replay is active, the Aux (microphones and the like) and  
	Desktop audio will be muted. They will then unmute when the scene switches  
	back.  