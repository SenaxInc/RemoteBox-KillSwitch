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
