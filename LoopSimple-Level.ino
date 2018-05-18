//used to monitor level height switch and send cut off signal to remote kill switch box. When recieve confirmation of cutoff, end sending message until level switch is reset.

///////////////////////

////// VARIABLES //////

int p10 = 10; //liquid level switch set to Pin 10

int b10;  //to temporarily remember the last Broadcast data for the switch

int s10 = digitalRead(p10);  //to handle data of current State of a switch

int bedtime = 0;

int st = 5; //minutes of radio inactivity before XBEE goes into sleep mode

int sp = 25; //minutes XBEE will sleep before waking the radio back up

int tick8=0;

int messageState = HIGH;         // the current state of the output pin
int lvlState;             // the current reading from the input pin
int lastlvlState = LOW;   // the previous reading from the input pin
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

////// SETUP //////

void setup() {

pinMode(p10,INPUT_PULLUP); //define liquid level pin mode
  
Serial.begin(9600);      //START COMMUNICATING WITH XBEE  
delay(5000);                              //wait 5 seconds    
  
}

//// LOOP ////

void loop() {
  
while (bedtime=0){  
  
    
////// DEBOUNCE

  // read the state of the switch into a local variable:
  int reading = digitalRead(p10);

  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH), and you've waited long enough
  // since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (reading != lastlvlState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != lvlState) {
      lvlState = reading;

      // only toggle the LED if the new button state is HIGH
      if (lvlState == HIGH) {
        messageState = !messageState;
      }
    }
  }

  // set the switch state:
  s10 = messageState;

  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastlvlState = reading;

////// END DEBOUNCE

delay(5000);           //wait 5 seconds
  
  if (s10 == LOW) {       //And If the current state of the switch is "low", AKA the switch is tripped...      
    Serial.print('K');   //Send the Kill Signal
    delay(5000);     
  } else {               //If the switch was not "low"...
    Serial.print('A');   //Send Alive Signal
    delay(5000);     
  }
  
while (Serial.available()>0){             //if message available...
    
char RXbyte = char(Serial.read()); //read message...
  
if (RXbyte == 'k') { //if message is "k"...
    Serial.print('Z'); 
}
if (RXbyte == 'a') { //if message is "a"...
    Serial.print('Z'); 
}  
 
if (RXbyte == 'z') {
                                         //end communication with xbee
    bedtime=1;                           //initiate bedtime next loop
}

delay(5000);
  
} //end serial available while

} //end bedtime=0

while (bedtime=1){

 delay(8000);                             //wait 8 seconds
 tick8++;                                 //add 1 to "tick8"
  
if (tick8>180){                          //after 24 minutes...
    bedtime=0;                           //end bedtime
}                                        //end tick8 if  
  
} //end bedtime=1 while

} //end main loop  

