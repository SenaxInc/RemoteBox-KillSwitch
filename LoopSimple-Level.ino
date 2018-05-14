//used to monitor level height switch and send cut off signal to remote kill switch box. When recieve confirmation of cutoff, end sending message until level switch is reset.

///////////////////////

////// VARIABLES //////

int p10 = 10; //liquid level switch set to Pin 10

int b10;  //to temporarily remember the last Broadcast data for the switch

int s10 = digitalRead(10);  //to handle data of current State of a switch

boolean freshb = false; //keep track of weather a new broadcast has been send each loop
int freshc = 0; //keep track of last fresh broadcast
int freshf = 1; // flip bit to send different message each time
int fresho = 30; // number of loops to run before sending signal. might change code later to be based on watchdog timer

////// SETUP //////

void setup() {

pinMode(p1,INPUT_PULLUP); //define liquid level pin mode
  
}

//// LOOP ////

void loop() {
  
freshb = false;
  
s1 = digitalRead(p1);
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
