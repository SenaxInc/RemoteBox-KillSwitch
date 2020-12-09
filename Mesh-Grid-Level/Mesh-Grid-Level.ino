//used to monitor level height switch and send cut off signal to remote kill switch box. When recieve confirmation of cutoff, end sending message until level switch is reset.

///////////////////////

// We'll use SoftwareSerial to communicate with the XBee:
#include <SoftwareSerial.h>
// XBee's DOUT (TX) is connected to pin 2 (Arduino's Software RX)
// XBee's DIN (RX) is connected to pin 3 (Arduino's Software TX)
// SoftwareSerial XBee(2, 3); // RX, TX

////// VARIABLES //////

int lvlpin = 10; //liquid level switch set to Pin 10

int lvlstate = digitalRead(lvlpin);  //to handle data of current State of a switch

int bedtime = 0;

int tick8=0;

int sleeptick8s=75;   //how many sets of 8 seconds to wait before starting up again  225 

////// SETUP //////

void setup() {

pinMode(lvlpin,INPUT); //define liquid level pin mode
digitalWrite(lvlpin,HIGH);

pinMode(13, OUTPUT);  //LED
  
//pinMode(9, OUTPUT);  //XBee sleepmode pin. High=sleep. Low-awake.

Serial.begin(9600);      //START COMMUNICATING WITH XBEE  

//digitalWrite(9, LOW);                 //wake up XBee
delay(2000);                          //give it a few seconds to catch its breath
  
    Serial.print('A');  
    digitalWrite(13, LOW);
    delay(1000);

    digitalWrite(13, HIGH);
    delay(1000);

    digitalWrite(13, LOW);
    delay(1000);

    digitalWrite(13, HIGH);
    delay(1000);

    digitalWrite(13, LOW);
    delay(1000);  
  
    bedtime = 0;
  
  delay(5000);                              //wait 5 seconds    
  
}

//// LOOP ////

void loop() {
  
  
   // read the state of the switch into a local variable:
digitalWrite(lvlpin, HIGH);
delay(2000);
  lvlstate = digitalRead(lvlpin);
  delay(10);
  lvlstate = digitalRead(lvlpin);
delay(2000);
digitalWrite(lvlpin, LOW);

  if (lvlstate == HIGH) {       //And If the current state of the switch is "HIGH", AKA the N.C. switch is tripped...      
    Serial.print('K');   //Send the Kill Signal
    delay(5000);     
  } else {               //If the switch was not "HIGH"...
    Serial.print('A');   //Send Alive Signal
    delay(5000);     
  }
  
while (bedtime==0 && Serial.available()>0){             //if message available...
//could this if be written as a while(serial available && bedtime=0)

    
char RXbyte = char(Serial.read()); //read message...
  
if (RXbyte == 'k') { //if message is "k"...
    Serial.print('Z');                  //ready to sleep
}
if (RXbyte == 'a') { //if message is "a"...
    Serial.print('Z');                  //ready to sleep
}  
 
if (RXbyte == 'z') {
    Serial.print('z');                  //going to sleep
    delay(8000);
    bedtime=1;                           //initiate bedtime next loop
}

  
} //end Serial.available while

while (bedtime==1){
//    digitalWrite(9, HIGH);
 delay(8000);                             //wait 8 seconds
 tick8++;                                 //add 1 to "tick8"

//blink
    digitalWrite(13, HIGH);
    delay(500);
    digitalWrite(13, LOW);
//end blink
  
if (tick8>sleeptick8s){                          //after 30 minutes...
    tick8=0;
    bedtime=0;                           //end bedtime
      digitalWrite(9, LOW);
      
    digitalWrite(13, LOW);
    delay(1000);
    digitalWrite(13, HIGH);
    delay(1000);
    digitalWrite(13, LOW);
    delay(1000);
    digitalWrite(13, HIGH);
    delay(1000);
    digitalWrite(13, LOW);
    delay(1000);  
}                                        //end tick8 if  
  
} //end bedtime1 while

} //end main loop  
