#include <avr/sleep.h>
#include <avr/power.h>
#include <avr/wdt.h>
#include <avr/interrupt.h>

//periodically checks for radio message. If recieve kill signal, flip relay module. Send Confirmation that relay has been engaged.

///////////////////////////

////// VARIABLES //////

int p2 = 2; //define "read" Pin to confirm relay has been flipped

int r1 = 1; //define "write" pins to control Relay module

int s2 = digitalRead(2);  //to handle data of current State of the relay

int b2;  //to temporarily remember the last Broadcast data of the realy

int bedtime = 0;

////// SETUP //////

void setup() {

wdt_disable(); //turn off timer to prevent errors on setup

pinMode(r1, OUTPUT); //SET PINS AS OUTPUT TO RELAY MODULE
  
  //SET AND START WATCHDOG TIMER
wdt_reset();   //reset watchdog
WDTCSR |= 0b00011000; 
WDTCSR = 0b00100001;
WDTCSR = WDTCSR | 0b01000000;  //put watchdog in interupt mode (interupt will happen every 8 seconds)
wdt_reset(); //reset watchdog - START COUNTING FROM ZERO
sei(); //enable interrupts
  
}

///// LOOP /////

void loop() {

//while (Serial.available()>0){
  while (bedtime=0){

char RXbyte = char(Serial.read());
  
  
  if (RXbyte == 'K') {
    digitalWrite(r1, HIGH);
    wdt_reset();
  }
if (RXbyte == 'A') {
    digitalWrite(r1, LOW);
    wdt_reset();
  }
  
  if (RXbyte == 'Z') {
    wdt_reset();
  }
if (RXbyte == 'z') {
    wdt_reset();
  }
  
  
} //end while
} //end main loop
