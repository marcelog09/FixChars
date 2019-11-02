## Install

Copy Compiled/fixchars.dll (if you are using Windows) or Compiled/fixchars.so (if you are using Linux) to your server plugins folder.

In your server.cfg file, in the plugins line, add fixchars.dll or fixchars.so. For example: 

plugins fixchars.dll

If you don't have plugins line / folder, you'll need to create it.

This plugin automatically redirects GameTextForAll, etc. functions when your scripts / gamemodes loaded. No further action is required (e.g. modify your scripts).

## Compile

See details in makefiles.