//periodically checks for radio message. If recieve kill signal, flip relay module. Send Confirmation that relay has been engaged.

///////////////////////////

// We'll use SoftwareSerial to communicate with the XBee:
#include <SoftwareSerial.h>
// XBee's DOUT (TX) is connected to pin 2 (Arduino's Software RX)
// XBee's DIN (RX) is connected to pin 3 (Arduino's Software TX)
SoftwareSerial XBee(2, 3); // RX, TX

////// VARIABLES //////

int p11 = 11;                 //define "read" Pin to confirm relay has been flipped

int r10 = 10;                 //define "write" pins to control Relay module

int s11 = digitalRead(11);    //to handle data of current State of the relay

int b11;                      //to temporarily remember the last Broadcast data of the realy

int bedtime = 0;              //1= its time for bed. 0= its time to stay awake.

int st = 5;                   //minutes of radio inactivity before XBEE goes into sleep mode

int sp = 25;                  //minutes XBEE will sleep before waking the radio back up

int timeout = 0;

int tick8 = 0;

////// SETUP //////

void setup() {

pinMode(r10, OUTPUT); //SET PINS AS OUTPUT TO RELAY MODULE

digitalWrite(r10, LOW);  //ground ignition at startup for safety. verify connection before allowing engine to run.
  //if battery dies overnighht well will be down in the morning.

pinMode(p11,INPUT_PULLUP); //define liquid level pin mode
    
XBee.begin(9600);                       //START COMMUNICATING WITH XBEE

    XBee.print('A');  
    digitalWrite(r10, LOW);
    delay(1000);
    XBee.print('A');  
    digitalWrite(r10, HIGH);
    delay(1000);
    XBee.print('A');  
    digitalWrite(r10, LOW);
    delay(1000);
    XBee.print('A');  
    digitalWrite(r10, HIGH);
    delay(1000);
    XBee.print('A');  
    digitalWrite(r10, LOW);
    delay(1000);  
  
    bedtime = 0;
  
}

///// LOOP /////

void loop() {

while (bedtime=0){

                       //wait 5 seconds  
  
while (XBee.available()>0){             //if message available...
    
char RXbyte = char(XBee.read());        //read message...
  
  if (RXbyte == 'K') {                    //if message is "K"...
    digitalWrite(r10, LOW);               //close iginition circuit
    delay(5000);
    int s11 = digitalRead(p11);
    if (s11 == HIGH){
    XBee.print('k');                    //send "k" message to confirm relay has been flipped
    timeout=1;
    } else {
    XBee.print('E');  
    }
  }
if (RXbyte == 'A') {                      //if message is "A"...
    digitalWrite(r10, HIGH);               //open iginition circuit
    delay(5000);
    s11 = digitalRead(p11);
    if (s11 == LOW){
    XBee.print('a');                    //send "k" message to confirm relay has been flipped
    timeout=1;
    } else {
    XBee.print('E');  
    }
  }

if (RXbyte == 'Z') {                      //when level box recieves confirmation is sends "Z" 
    XBee.print('z');                    //send "z" to confirm
    timeout=1;
  }

if (RXbyte == 'z') {
                                         //end communication with xbee
   delay(300000);
    bedtime=1;                           //initiate bedtime next loop
    timeout=1;
  }

} //end serial available while

  delay(5000);
  timeout++;
  
  if (timeout>720000) {                   //if timout count is greater than 1 hour....
    digitalWrite(r10, LOW);               //close iginition circuit, kill engine
    XBee.print('k');                    //send "k" message to confirm relay has been flipped
  }  
  
} //end bedtime=0 while

while (bedtime=1){

 delay(8000);                             //wait 8 seconds
 tick8++;                                 //add 1 to "tick8"
  
if (tick8>225){                          //after 30 minutes...
    bedtime=0;                           //end bedtime
}                                        //end tick8 if  
  
} //end bedtime=1 while
  
} //end main loop
