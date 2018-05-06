//periodically checks for radio message. If recieve kill signal, flip relay module. Send Confirmation that relay has been engaged.

int p2 = 2; //define "read" Pin to confirm relay has been flipped

int r1 = 1; //define "write" pins to control Relay module

int s2 = digitalRead(2);  //to handle data of current State of the relay

int b2;  //to temporarily remember the last Broadcast data of the realy
