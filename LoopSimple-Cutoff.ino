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

delay(2000);                              //wait 2 seconds  
  
while (Serial.available()>0){             //if message available...
    
char RXbyte = char(Serial.read());        //read message...
  
  if (RXbyte == 'K') {                    //if message is "K"...
    digitalWrite(r10, LOW);               //close iginition circuit
    Serial.print('k');                    //send "k" message to confirm relay has been flipped
  }
if (RXbyte == 'A') {                      //if message is "A"...
    digitalWrite(r1, HIGH);               //open iginition circuit
    Serial.print('a');                    //send "a" message to confirm relay has been flipped
  }

if (RXbyte == 'Z') {                      //when level box recieves confirmation is sends "Z" 
    Serial.print('z');                    //send "z" to confirm
  
  }

if (RXbyte == 'z') {
    Serial.end(9600);
    bedtime=1;

  /////// SLEEP MODE SETUP ///////////
  //SET AND START WATCHDOG TIMER
wdt_reset();   //reset watchdog
WDTCSR |= 0b00011000; 
WDTCSR = 0b00100001;
WDTCSR = WDTCSR | 0b01000000;  //put watchdog in interupt mode (interupt will happen every 8 seconds)
wdt_reset(); //reset watchdog - START COUNTING FROM ZERO
sei(); //enable interrupts
  //prepare for sleep - turn off some settings
    power_adc_disable(); //disable the clock to the ADC module
    ADCSRA &= ~(1<<ADEN);  //ADC hex code set to off
                         //can USART be turned off here? power_usart_disable()
//////////// BED TIME STARTS /////////
  
  }

  delay(5000);

 //////////add timeout here. if no communication after 30 minutes, kill engine. 
  
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
