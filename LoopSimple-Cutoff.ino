//periodically checks for radio message. If recieve kill signal, flip relay module. Send Confirmation that relay has been engaged.

///////////////////////////

////// VARIABLES //////

int p11 = 11; //define "read" Pin to confirm relay has been flipped

int r10 = 10; //define "write" pins to control Relay module

int s11 = digitalRead(11);  //to handle data of current State of the relay

int b11;  //to temporarily remember the last Broadcast data of the realy

int bedtime = 0; //1= its time for bed. 0= its time to stay awake.

int ST = 5; //minutes of radio inactivity before XBEE goes into sleep mode

int SP = 25; //minutes XBEE will sleep before waking the radio back up

////// SETUP //////

void setup() {

pinMode(r10, OUTPUT); //SET PINS AS OUTPUT TO RELAY MODULE

digitalWrite(r10, LOW);  //ground ignition at startup for safety. verify connection before allowing engine to run.
  //if battery dies overnighht well will be down in the morning.
    
}

///// LOOP /////

void loop() {

while (bedtime=0){

Serial.begin(9600);                       //START COMMUNICATING WITH XBEE

delay(5000);                              //wait 5 seconds  
  
while (Serial.available()>0){             //if message available...
    
char RXbyte = char(Serial.read());        //read message...
  
  if (RXbyte == 'K') {                    //if message is "K"...
    digitalWrite(r10, LOW);               //close iginition circuit
    Serial.print('k');                    //send "k" message to confirm relay has been flipped
    timeout=1;
  }
if (RXbyte == 'A') {                      //if message is "A"...
    digitalWrite(r1, HIGH);               //open iginition circuit
    Serial.print('a');                    //send "a" message to confirm relay has been flipped
    timeout=1;
  }

if (RXbyte == 'Z') {                      //when level box recieves confirmation is sends "Z" 
    Serial.print('z');                    //send "z" to confirm
    timeout=1;
  }

if (RXbyte == 'z') {
    Serial.end(9600);                    //end communication with xbee
    bedtime=1;                           //initiate bedtime next loop
    timeout=1;
  }

  delay(5000);
  timeout++;
  
  if (timeout>720000) {                   //if timout count is greater than 1 hour....
    digitalWrite(r10, LOW);               //close iginition circuit, kill engine
    Serial.print('k');                    //send "k" message to confirm relay has been flipped
  }

} //end awake while

while (bedtime=1){
  
tickSleep();  //puts arduino to sleep for about 8 seconds
  
if (tick8>1800){
  Serial.begin(9600);

  while (bedtime=1){
          
  Serial.print('W');
    wdt_reset();
    delay(5000);

    while (Serial.available()>0){        
char RXbyte = char(Serial.read());
    
    if (RXbyte == 'w') {
    bedtime=0;
} //end if "w"
      
} //end serial while
    
} //end nested bedtime while  

} //end if tick8  
} //end bedtime while
  
} //end main loop

void tickSleep()   
{
    set_sleep_mode(SLEEP_MODE_PWR_DOWN); 
    sleep_enable();
    sei();  //enable interrupts
    sleep_mode();
//after about 8 seconds the Watchdog Interupt will progress the code to the disable sleep command
    sleep_disable();             
}

ISR(WDT_vect)
{
    tick8 ++; //for each Watchdog Interupt, adds 1 to the number of 8 second ticks counted so far
}
