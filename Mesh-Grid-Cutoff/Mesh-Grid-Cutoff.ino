//periodically checks for radio message. If recieve kill signal, flip relay module. Send Confirmation that relay has been engaged.

///////////////////////////

#include <SoftwareSerial.h>  // SoftwareSerial used to communicate with the XBee from Arduino
// XBee's DOUT (TX) is connected to pin 2 (Arduino's Software RX)
// XBee's DIN (RX) is connected to pin 3 (Arduino's Software TX)
// SoftwareSerial XBee(2, 3); // RX, TX

////// VARIABLES //////

int confirmpin = 11;                 //define "read" Pin to confirm relay has been flipped

int relaypin = 10;                 //define "write" pins to control Relay module

int confirmstate = digitalRead(confirmpin);    //to handle data of current State of the relay

int bedtime = 0;              //1= its time for bed. 0= its time to stay awake.

int timeout = 0;

int tick8 = 0;

int sleeptick8s=225;   //how many sets of 8 seconds to wait before starting up again  225 


////// SETUP //////

void setup() {

pinMode(relaypin, OUTPUT); //SET PINS AS OUTPUT TO RELAY MODULE

digitalWrite(relaypin, LOW);  //ground ignition at startup for safety. verify connection before allowing engine to run.
  //if battery dies overnighht well will be down in the morning.

pinMode(confirmpin,INPUT_PULLUP); //define liquid level pin mode

pinMode(13, OUTPUT);  //LED
  
pinMode(9, OUTPUT); //XBee sleepmode pin. High=sleep. Low=awake.  

digitalWrite(9, LOW);                 //wake up XBee
delay(2000);
  
Serial.begin(9600);                       //START COMMUNICATING WITH XBEE

    Serial.print('A');  
    digitalWrite(relaypin, LOW);
    delay(1000);

    digitalWrite(relaypin, HIGH);
    delay(1000);

    digitalWrite(relaypin, LOW);
    delay(1000);

    digitalWrite(relaypin, HIGH);
    delay(1000);

    digitalWrite(relaypin, LOW);
    delay(1000);  
  
    bedtime = 0;
  
}

///// LOOP /////

void loop() {

while (bedtime==0 && Serial.available()>0){               //if message available...
    
char RXbyte = char(Serial.read());        //read message...
  
  if (RXbyte == 'K') {                    //if message is "K"...
    digitalWrite(relaypin, LOW);               //close iginition circuit
    delay(10);
    confirmstate = digitalRead(confirmpin);
    if (confirmstate == HIGH){
    Serial.print('k');                    //send "k" message to confirm relay has been flipped
    timeout=1;
    } else {
    Serial.print('E');  
    }
  }
if (RXbyte == 'A') {                      //if message is "A"...
    digitalWrite(relaypin, HIGH);               //open iginition circuit
    delay(10);
    confirmstate = digitalRead(confirmpin);
    if (confirmstate == LOW){
    Serial.print('a');                    //send "k" message to confirm relay has been flipped
    timeout=1;
    } else {
    Serial.print('E');  
    }
  }

if (RXbyte == 'Z') {                      //when level box recieves confirmation is sends "Z" for "ready to sleep"
    Serial.print('z');                    //send "z" to confirm  "cut off ready to sleep"
    timeout=1;
  }

if (RXbyte == 'z') {
    delay(8000);
    bedtime=1;                           //initiate bedtime next loop
    timeout=1;
  }

} //end serial available while

  delay(5000);
  timeout++;
  
  if (timeout>720000) {                   //if timout count is greater than 1 hour....
    digitalWrite(relaypin, LOW);               //close iginition circuit, kill engine
    Serial.print('k');                    //send "k" message to confirm relay has been flipped
  }  
  

while (bedtime==1){
 digitalWrite(9, HIGH);                   //put XBee to sleep
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
   digitalWrite(9, LOW);                 //wake up XBee
   
    digitalWrite(13, LOW);
    delay(1000);
    digitalWrite(13, HIGH);
    delay(2000);
    digitalWrite(13, LOW);
    delay(1000);
    digitalWrite(13, HIGH);
    delay(4000);
    digitalWrite(13, LOW);
    delay(1000);  
}                                        //end tick8 if  
  
} //end bedtime=1 while
  
} //end main loop

