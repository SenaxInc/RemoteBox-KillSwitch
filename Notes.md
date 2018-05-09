## ToDo

  * send confirmation signal back to level monitor box, use to trigger sleep
  * sleep mode
      * see avr sleep example: https://github.com/dorkmo/ArduinoSMSTankAlarm/blob/master/TankAlarm072017.ino
      * see digi sleep mode: https://www.digi.com/resources/documentation/Digidocs/90001456-13/reference/r_wk_sleep_mode.htm
  * syncronize sleep/wake times
      * wake up every 30 minutes, broadcast till other box wakes up, do the business, then sleep for 30 minutes 

## Questions

  * can an arduino digital pin put out enough amps to power the relay module?
      * could power down relay module when not in use


## Sleep Routine

  * when transmition of kill or stay alive broadcast is complete and confirmed.
      * send "Z" to say ready for bed. When recieve "z" back, end all transmissions.
      * xbee sleep mode will engage after 2 minutes as predefined time in XCTU settings
      * arduino will go into avr sleep mode for 8 seconds at a time, keeping count.
      * after 28 minutes wakeup xbee as defined in XCTU sleep timer
      * after 30 minutes, end arduino avr sleep.
      * Broadcast "W" awake status every 1 minute using delay(). wait for "w" confirmation.
      * Broadcast status of liquid level switch. "K" to kill. "A" to stay alive.
      * Wait for Confirmation of "k", "a", or "E" for error. 
      * Broadcast "Z"

## Related Links

  * http://opensourceecology.org/wiki/MicroTrac_Controller_v17.10/Code

