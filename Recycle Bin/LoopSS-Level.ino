//used to monitor level height switch and send cut off signal to remote kill switch box. When recieve confirmation of cutoff, end sending message until level switch is reset.

///////////////////////

// We'll use SoftwareSerial to communicate with the XBee:
#include <SoftwareSerial.h>
// XBee's DOUT (TX) is connected to pin 2 (Arduino's Software RX)
// XBee's DIN (RX) is connected to pin 3 (Arduino's Software TX)
SoftwareSerial XBee(2, 3); // RX, TX

////// VARIABLES //////

int p10 = 10; //liquid level switch set to Pin 10

int b10;  //to temporarily remember the last Broadcast data for the switch

int s10 = digitalRead(p10);  //to handle data of current State of a switch

int bedtime = 0;

int tick8=0;

int sleeptick8s=225;   //how many sets of 8 seconds to wait before starting up again

////// SETUP //////

void setup() {

pinMode(p10,INPUT_PULLUP); //define liquid level pin mode

pinMode(13, OUTPUT);  //LED
  
pinMode(9, OUTPUT);  //XBee sleepmode pin. High=sleep. Low-awake.

XBee.begin(9600);      //START COMMUNICATING WITH XBEE  

digitalWrite(9, LOW);                 //wake up XBee
delay(2000);                          //give it a few seconds to catch its breath
  
    XBee.print('A');  
    digitalWrite(13, LOW);
    delay(1000);
    XBee.print('A');  
    digitalWrite(13, HIGH);
    delay(1000);
    XBee.print('A');  
    digitalWrite(13, LOW);
    delay(1000);
    XBee.print('A');  
    digitalWrite(13, HIGH);
    delay(1000);
    XBee.print('A');  
    digitalWrite(13, LOW);
    delay(1000);  
  
    bedtime = 0;
  
  delay(5000);                              //wait 5 seconds    
  
}

//// LOOP ////

void loop() {
  
while (bedtime==0){  
  
   // read the state of the switch into a local variable:
s10 = digitalRead(p10);
delay(10);
  s10 = digitalRead(p10);
delay(10);
  s10 = digitalRead(p10);
delay(10);
  s10 = digitalRead(p10);
  
  if (s10 == LOW) {       //And If the current state of the switch is "low", AKA the switch is tripped...      
    XBee.print('K');   //Send the Kill Signal
    delay(5000);     
  } else {               //If the switch was not "low"...
    XBee.print('A');   //Send Alive Signal
    delay(5000);     
  }
  
while (XBee.available()>0){             //if message available...
    
char RXbyte = char(XBee.read()); //read message...
  
if (RXbyte == 'k') { //if message is "k"...
    XBee.print('Z'); 
}
if (RXbyte == 'a') { //if message is "a"...
    XBee.print('Z'); 
}  
 
if (RXbyte == 'z') {
    bedtime=1;                           //initiate bedtime next loop
}

  
} //end XBee.available while

} //end bedtime=0

while (bedtime==1){
    digitalWrite(9, HIGH);
 delay(8000);                             //wait 8 seconds
 tick8++;                                 //add 1 to "tick8"
  
if (tick8>sleeptick8s){                          //after 30 minutes...
    bedtime=0;                           //end bedtime
      digitalWrite(9, LOW);
  delay(5000);
}                                        //end tick8 if  
  
} //end bedtime=1 while

} //end main loop  

