![Tutorial spreadfire1 instant replay hearthstone legend.gif](https://cdn.steemitimages.com/DQmVHKyRrQdP57sjTFsnX1q44oJ8JUuEvbBMXtik7nXYRDf/Tutorial%20spreadfire1%20instant%20replay%20hearthstone%20legend.gif)

### Repository
https://github.com/spreadfire/InstantReplayXT/tree/master/Tutorial

### What Will I Learn?
This tutorial is for live streamers looking to enhance their stream and viewer experience. By adding these little-known features, you can make your content stand out from the mass of streams.
- You will learn how to play an **Instant Replay** of a cool scene that happened during your live stream
- You will learn how to show the stream's **Highlights** (a compilation of all previously saved replays)

### Requirements
- [Open Broadcaster Software](https://obsproject.com/download) (OBS Studio).
- [Instant Replay XT](https://github.com/spreadfire/InstantReplayXT/raw/master/precompiled/InstantReplay.zip) - I created an Extended, easier to set up and use, version of the original [Instant Replay](https://obsproject.com/forum/resources/instant-replay.575/) plugin by William Pearson (https://github.com/adocilesloth).
- [VLC Player](https://www.vlc.de/) - for using a *VLC Video Source* in OBS to play all video files a specific folder contains.

### Difficulty
- Intermediate

I'm assuming you already know how to install OBS and VLC or have them installed.
The tutorial won't cover basics like how to use Windows applications or settings dialogs/controls.

---

### Tutorial Contents
#### Instant Replay
Does the following situation sound familiar and appealing to you?
1. **Insane monster pentakill action team fight**, **sick 360 noscope headshot** or something like that happens in your game.
2. After it happened you wish you could, at the press of a button, instantly save and show the replay of it.
3. You wish you could watch a replay of the event together with your stream viewers while commenting or doing whatever crazy stuff you feel like.

There's a lot of room for creativity with the feature.

##### Now here's how you set it up:
- **Download**
After downloading the [zip file](https://github.com/spreadfire/InstantReplayXT/raw/master/precompiled/InstantReplay.zip), extract it to your *OBS install path* (e.g. `C:\Program Files (x86)\obs-studio`). Keep the folder structure, as all files need to be extracted to their respective subdirectories.
- **Setup**
(I reuse parts of the original *Instant Replay* plugin documentation here)

---

###### 1. Start *OBS*

###### 2. Go to `File -> Settings -> Output`
In `Output Mode` "Simple", check `Enable Replay Buffer` and set the `Replay Buffer` `Maximum Replay Time (Seconds)`

![Tutorial OBS Settings Output Simple Replay Buffer.png](https://cdn.steemitimages.com/DQmfA6S5k57yfSi7XxWX63Z8vGz3iuMJxdLgwETqWKRAw1t/Tutorial%20OBS%20Settings%20Output%20Simple%20Replay%20Buffer.png)

**Examples of Replay Buffer Length**
This depends on your personal preference and what you want to do. Try different settings, tweak around and see what fits your game, play style and stream best.

To have some reference points, these are my personal suggestions:
a. Fast paced first-person-shooter **(FPS) 10 seconds**,
b. **MOBA** like *Heroes of the Storm* or *DotA* **30 seconds**,
c. Slow paced **card games** with long turns like *Hearthstone* or *Gwent* maybe even **60 seconds**.

###### 3. Open the Hotkeys under:  
`Settings -> Hotkeys`
Find the `Instant Replay` hotkey
Set it TO THE SAME KEY as you have `Save Replay` under `Replay Buffer` set to.

![Tutorial OBS Settings Hotkeys.png](https://cdn.steemitimages.com/DQmS3ZEsXxgK6xioFVQAeQS7ogeThVRkZXLkNPnfC7KNQjL/Tutorial%20OBS%20Settings%20Hotkeys.png)

It should be a key you can easily reach while streaming a game. So you can press it fast after a replay-worthy scene happens.
I use `F9` for example.

###### 4. Go to `Settings -> Advanced`

**Deprecated**:
> Setting up the replay source:
> Set your Recording to a constant name (so remove all the % stuff). Makes it
> easy to point your replay source to a file that will exist.
> Point your Media Source to what your replay will be saved as.

This is no longer necessary in *Instant Replay XT*. The plugin automatically sets the Instant Replay Media Source to the currently active replay file before switching to the replay scene.
You can set any `Recording` filename you like. To have a unique filename, you can use date and time wildcards for example:
`Filename Formatting` - `OBS %CCYY-%MM-%DD %hh-%mm-%ss`
`Replay Buffer Filename Prefix` - `Replay`

![Tutorial OBS Settings Advanced.png](https://cdn.steemitimages.com/DQmYxs7ivr7pZKG66PPf86sttGi1ugCstUVKajBFrkRSvzG/Tutorial%20OBS%20Settings%20Advanced.png)
The resulting file name in this example would be something like this: "C:\Users\Jeremias\Videos\Replay OBS 2018-09-14 18-42-57.flv"

Close the `Settings` dialog with `Ok`.

###### 5. Go to `Tools -> Instant Replay XT Settings`
![OBS plugin InstantReplayXT settings.png](https://cdn.steemitimages.com/DQmTarDosKGu6vjMyf4cSLMPEv9bVc79icZ19PaGvQtYkor/OBS%20plugin%20InstantReplayXT%20settings.png)

**Mandatory settings** for this tutorial:

`Enable` - Enables/disables the plugin

`Write Pause (s)` - Pause to allow OBS to write the replay file. 
OBS can't instantly write a file. ~10 seconds should be okay. 
Find something that works for you. 
(Functionality change in *Instant Replay XT*: Write Pause is the maximum amount of seconds you want to wait. If the replay file buffer was written before that, it switches to the Instant Replay scene immediately.)

`Transition Pause (ms)` - Length of the transition in milliseconds. 
If the stinger is at 30fps, multiply the number of frames by 33. 
If the stinger is at 60fps, multiply the number of frames by 16.

`Replay Length (s)` - Length of the replay in seconds.
OBS does not always write as much replay as you tell it to so this may need to be a second or two shorter than the buffer length (see *Replay Buffer Length* section in step 2 above for more details)

`Replay Scene` - Scene to switch to that has the replay source.

`Replay Source Name` - Name of the OBS Media Source you use to play the Instant Replay file. e.g. "Instant Replay Media Source".

**Optional settings**:
`Mute Desktop Audio` - Mute the Desktop Audio channels when replay is playing.
`Mute Mic/AUX` - Mute the Mic/Aux channels when replay is playing.
`Backup Replay File` - Enables/disables the backup feature.
`Backup File Path` - After the replay file buffer was written, copy it to this path.

`Close` the plugin settings dialog.

###### 6. `Add` a `Scene` to your scene collection
The *Instant Replay XT* plugin will switch to this scene after you press the hotkey.
**IMPORTANT:** The scene name has to match the exact name you set in `Tools -> Instant Replay XT Settings`, `Replay Scene`. In the sample screenshot, I use "Instant Replay Scene" for example.

![Tutorial OBS Add Instant Replay Scene.png](https://cdn.steemitimages.com/DQmZFF5Ngp6BdQjnbwM46FMazpDnLP4oLTJfHonQZigoyuK/Tutorial%20OBS%20Add%20Instant%20Replay%20Scene.png)

###### 7. `Add` a `Media source` to the scene
It will be used to play your *Instant Replay* file.

![Tutorial OBS Add Media Source.png](https://cdn.steemitimages.com/DQmYZmb9SKBKbY6CRdkkA2rDeeAq68zUjzVnJME7MAXyMG4/Tutorial%20OBS%20Add%20Media%20Source.png)

**IMPORTANT:** Make sure to use the same name for the `Media Source` as you set in `Tools -> Instant Replay XT Settings`, `Replay Source Name`. In the sample screenshot, I use "Instant Replay Media Source" for example.

![Tutorial OBS Properties Instant Replay Media Source.png](https://cdn.steemitimages.com/DQmcWpUiQjpDNPASP4E6EoKEv5buGbN1pGQJG3JJoTgUEds/Tutorial%20OBS%20Properties%20Instant%20Replay%20Media%20Source.png)

You can leave all `Properties` of the newly created `Media Source` at their default values. You don't have to set a file, you can leave it empty. *Instant Replay XT* will automatically set the Media Source `File Name` to the currently active replay file before switching to the replay scene.
Optionally, you can customize the rest of the media source's properties. I enable `Close file when inactive` for example.
Another interesting setting is the `Speed (percent)`. This allows you to play your *Instant Replays* in **slow motion**.

###### 8. Ready to go
Now that you have everything set up, give it a try.

![Tutorial OBS Start Streaming or Replay Buffer.png](https://cdn.steemitimages.com/DQmV6zFhLxHoTD4PU1wngtUbX9cpNSZVHuLfUjC5aPg2aMt/Tutorial%20OBS%20Start%20Streaming%20or%20Replay%20Buffer.png)
When you `Start Streaming` (a), the replay buffer is automatically started as well. If you don't want to go *live* and rather try it in an *offline* test environment, you can `Start Replay Buffer`(b) manually without having to `Start Streaming`.

**Here is what should happen:**
1. **Switch** to your default game **scene**
2. **Press** the **hotkey** button
3. *Instant Replay XT* switches to your *Instant Replay Scene* as soon as the replay buffer was written to the replay file
4. After the instant replay video finished playing, *Instant Replay XT* switches back to your default scene.

Here is an example of me using the feature to give you an idea of what it can look like when it's used in a productive environment:
https://d.tube/#!/v/spreadfire1/ajb6aewz

---

#### Stream Highlights
Based on the `Replay Buffer` OBS feature, you can use your previously saved replay files to show the stream's highlights.
This also works without having *Instant Replay XT* enabled. There are two ways to do that: Simply don't set a hotkey for *Instant Replay* playback (see step 3 of the previous section for details) or uncheck `Enable` in the plugin's settings (`Tools -> Instant Replay XT Settings`).

1. Set the `Recording Path`
OBS `Settings -> Output -> Recording Path`

2. Set up an OBS scene
This can be a new, dedicated scene or you can use an existing one. Whichever way you prefer to show your stream's highlights.
3. `Add` a `VLC Video Source`
![Tutorial OBS Add VLC Video Source.png](https://cdn.steemitimages.com/DQmZKRuMck7YqgyQGSdoaznfowNTPXgKzUTHKxCwkcBPDEH/Tutorial%20OBS%20Add%20VLC%20Video%20Source.png)
In `VLC Video Source -> Properties`, `Add directory`. This should be the path to the folder where your recordings/instant replays are saved (see step 1, `Recording Path`).
![Tutorial OBS VLC Video Source Properties.png](https://cdn.steemitimages.com/DQmRm679miskb1U5nHUaGdo1oP7V9Xp2gxWwWPSZeLbV4GE/Tutorial%20OBS%20VLC%20Video%20Source%20Properties.png)

4. Whenever you want to play the replay video files in that folder, switch to this scene (e.g. at the end of your stream).
If the playback doesn't start automatically, you might have to open `VLC Video Source -> Properties` and close the dialog again with `Ok`, to refresh.

Let me show you an example of how I use it / how it could look like:
![Tutorial Stream ending highlights scene.gif](https://cdn.steemitimages.com/DQmdL1s9mJrCynJPacz6wRDTfZpX1kErMX7MdiGegnFjwGE/Tutorial%20Stream%20ending%20highlights%20scene.gif)

---

Do you find this article helpful?
What would you use the Instant Replay feature for / are you already using it?

If you have ideas, feature requests, or you want to contribute yourself, let me know in the comments below or message me on https://twitter.com/spreadfire1.

Also be sure to check out my stream on [DLive.io/@spreadfire1](https://dlive.io/@spreadfire1).

---

### Curriculum
- [Instant Replay XT - Feature documentation 1st release](https://steemit.com/utopian-io/@spreadfire1/obs-plugin-for-live-streamers-instant-replay-xt-improved-and-extended-version)


### Proof of Work Done
https://github.com/spreadfire/InstantReplayXT/tree/master/Tutorial

