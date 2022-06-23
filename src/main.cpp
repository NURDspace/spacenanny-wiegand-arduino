#include <Arduino.h>
#include <EEPROM.h>
#include <Wiegand.h>

#define PIN_WG_D0 2
#define PIN_WG_D1 3
#define PIN_WG_LED 4
#define PIN_WG_BEEP 5

Wiegand wg( PIN_WG_D0, PIN_WG_D1); 

void initBeep() {
  digitalWrite(PIN_WG_BEEP, 0);
  delay(50);
  digitalWrite(PIN_WG_BEEP, 1);
  delay(50);
  digitalWrite(PIN_WG_BEEP, 0);
  delay(50);
  digitalWrite(PIN_WG_BEEP, 1);
  delay(50);
  digitalWrite(PIN_WG_LED, 1); // turn led off
}


void setup() {
  pinMode(PIN_WG_LED, OUTPUT);
  pinMode(PIN_WG_BEEP, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(9600);
  wg.begin();
  
  if (wg.hasDevice()) {
    Serial.println("INFO: Device available.");
    initBeep(); // Play an initialization beep
  
  } else{
    Serial.println("ERROR: Device not available.");
    
    // Just keep constantly emitting a beep when we can't init the WG device
    digitalWrite(LED_BUILTIN, 1);
    while(1) {
    digitalWrite(PIN_WG_BEEP, 0);
    delay(100);
    digitalWrite(PIN_WG_BEEP, 1);
    delay(100);
    }
  }
}

void loop() {
   if ( wg.available()) {
      digitalWrite(LED_BUILTIN, 1);
      Serial.print(wg.getTagCode());
      Serial.print(0x0D); // carriage return
      digitalWrite(LED_BUILTIN, 0);
   }
}