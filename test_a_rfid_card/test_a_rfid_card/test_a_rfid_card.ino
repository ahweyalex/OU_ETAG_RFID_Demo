#include "logger.h"
#define DEMOD_OUT_PIN   30 //PB03_RFIDIN
#define SHD_PIN         8 //PA06
#define MOD_PIN         0
#define READY_CLOCK_PIN 0
logger L(DEMOD_OUT_PIN,SHD_PIN,MOD_PIN,READY_CLOCK_PIN);   //pins are set for the board in the library
#define Serial SerialUSB
#define LED_RFID 31

byte tagData[5]; //Holds the ID numbers from the tag
unsigned long tagID;
const String greeting PROGMEM = "Please swipe your RFID Tag.";

void setup()
{
  pinMode(SHD_PIN, OUTPUT);
  digitalWrite(SHD_PIN, HIGH);   // turn the LED on (HIGH is the voltage level)

  pinMode(LED_RFID, OUTPUT);
  digitalWrite(LED_RFID, HIGH);   // turn the LED on (HIGH is the voltage level)

  Serial.begin(115200);
  while (!Serial)
  {
    delay(500);
    digitalWrite(LED_RFID, LOW);   // turn the LED on (HIGH is the voltage level)
    delay(500);
    digitalWrite(LED_RFID, HIGH);   // turn the LED on (HIGH is the voltage level)

  }
  digitalWrite(LED_RFID, LOW);   // turn the LED on (HIGH is the voltage level)
  Serial.println(greeting);
  //digitalWrite(LED_RFID, LOW);   // turn the LED on (HIGH is the voltage level)
}

void loop()
{
  digitalWrite(SHD_PIN, LOW);
  //scan for a tag - if a tag is sucesfully scanned, return a 'true' and proceed
  if (L.scanForTag(tagData) == true) {
    Serial.print("RFID Tag Data: "); //print a header to the Serial port.
    for (int n = 0; n < 5; n++) {
      Serial.print(tagData[n], HEX);
    }
    Serial.print("\n\rRFID Tag ID: ");
    tagID = ((long)tagData[1] << 24) + ((long)tagData[2] << 16) + ((long)tagData[3] << 8) + tagData[4];
    Serial.println(tagID);
    Serial.println();
    delay(L.get_RFID_READ_FREQ());
  }
}// end loop()
