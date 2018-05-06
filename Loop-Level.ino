//used to monitor level height switch and send cut off signal to remote kill switch box. When recieve confirmation of cutoff, end sending message until level switch is reset.

///////////////////////

////// VARIABLES //////

int p1 = 1; //liquid level switch set to pin 1

int b1;  //to temporarily remember the last broadcast data for the switch

int s1 = digitalRead(1);  //to handle data of current state of a switch

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
if (s1 == LOW) {         //And If the current state of the switch is "low", AKA the switch is tripped...
                                      ////need to start and confirm serial connection here "Serial.begin(9600);"
    Serial.print('K');   //Send the Kill Signal
    b1 = LOW;            //After broadcasting kill signal, define "the last broadcast" as "low"
  } else {               //If the switch was not "low"...
    Serial.print('A');   //Send Alive Signal
    b1 = HIGH;           //After broadcasting alive signal, define "the last broadcast" as "high"
  }
  freshb = true;         //After broadcasting a new message, change "fresh broadcast" state to true
}
  
  
