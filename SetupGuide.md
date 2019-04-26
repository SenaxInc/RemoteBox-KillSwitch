# Arduino

Upload code to arduinos

For the arduino monitoring the liquid level
https://create.arduino.cc/editor/dorkmo/c2d4928e-15f0-4c2c-a119-536aa2c805b0/preview
https://github.com/SenaxInc/RemoteBox-KillSwitch/blob/master/LoopTest-Level/LoopTest-Level.ino

https://create.arduino.cc/editor/dorkmo/c1a42b12-49da-4830-a664-cde163ad2a28/preview
https://github.com/SenaxInc/RemoteBox-KillSwitch/blob/master/LoopTest-Cutoff/LoopTest-Cutoff.ino


# XBee

Download XCTU
https://www.digi.com/resources/documentation/digidocs/90001458-13/default.htm#concept/c_downloading_installing_xctu.htm%3FTocPath%3DDownload%2520and%2520install%2520XCTU%7C_____0

Open XCTU

Plug in Xbee Explorer Dongle to computer - https://www.sparkfun.com/products/11697

Ctrl+Shft+D to search for radio

Change variables

NI - Set a discriptive name of location and cutoff or level 

SM - 1 pin sleep mode

ID - #### pick a network ID

Write down SH - Serial High and SL - Serial Low

Unplug 1st XBee and Install 2nd

Set the same parameters and enter the 1st's SH and SL into the DH - destination high and DL - destination low

Write down the SH and SL

Unplug 2nd xbee and plug in the 1st

Set the DH and DL as the SH and SL of the 2nd xbee


