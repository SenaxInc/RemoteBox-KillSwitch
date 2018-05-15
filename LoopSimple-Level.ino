//used to monitor level height switch and send cut off signal to remote kill switch box. When recieve confirmation of cutoff, end sending message until level switch is reset.

///////////////////////

////// VARIABLES //////

int p10 = 10; //liquid level switch set to Pin 10

int b10;  //to temporarily remember the last Broadcast data for the switch

int s10 = digitalRead(p10);  //to handle data of current State of a switch

int ST = 5; //minutes of radio inactivity before XBEE goes into sleep mode

int SP = 25; //minutes XBEE will sleep before waking the radio back up

int messageState = HIGH;         // the current state of the output pin
int lvlState;             // the current reading from the input pin
int lastlvlState = LOW;   // the previous reading from the input pin
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

////// SETUP //////

void setup() {

pinMode(p10,INPUT_PULLUP); //define liquid level pin mode
  
}

//// LOOP ////

void loop() {
  
s10 = digitalRead(p10);
if (s1 != b1) {          //If the current state of the switch is not the same as the last broad cast...
Serial.begin(9600);      //START COMMUNICATING WITH XBEE
  delay(2000);           //wait 2 seconds
  if (s1 == LOW) {       //And If the current state of the switch is "low", AKA the switch is tripped...      
    Serial.print('K');   //Send the Kill Signal
    b1 = LOW;            //After broadcasting kill signal, define "the last broadcast" as "low"
  } else {               //If the switch was not "low"...
    Serial.print('A');   //Send Alive Signal
    b1 = HIGH;           //After broadcasting alive signal, define "the last broadcast" as "high"
  }
  freshb = true;         //After broadcasting a new message, change "fresh broadcast" state to true
}
  
}


//send message if nothing has been sent recently
///////need to convert this section to a sleep mode + sleep counter
if (freshb = false) {
  freshc ++; //add one to fresh count
  if(freshc >= fresho) {
    if (freshf = 1) {
      Serial.print('Z');
      freshf = 0;
    }
    else {
      Serial.print('z');
      freshf = 1;
    }
  }
}

} //end main loop  

void debounce() {
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
}
