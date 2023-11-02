/**********************************************************************************
 *  TITLE: Control 1 Relay with ESP32 Touch (in-built)
 *  Click on the following links to learn more. 
 *  YouTube Video: https://youtu.be/DvKC7BM126w
 *  Related Blog : https://iotcircuithub.com/esp32-projects/
 *  by Tech StudyCell
 *  Preferences--> Aditional boards Manager URLs : 
 *  https://dl.espressif.com/dl/package_esp32_index.json, http://arduino.esp8266.com/stable/package_esp8266com_index.json
 *  
 *  Download Board ESP32 : https://github.com/espressif/arduino-esp32
 *
 *  Download the libraries : NA
 **********************************************************************************/

#include "Arduino.h"

int threshold = 40;
bool touchActive = false;
bool lastTouchActive = false;
bool testingLower = true;

// define the GPIO connected with Relays and switches
#define RelayPin1 13  //D23

#define TouchPin1 T7  //D27

void gotTouchEvent(){
  if (lastTouchActive != testingLower) {
    touchActive = !touchActive;
    testingLower = !testingLower;
    // Touch ISR will be inverted: Lower <--> Higher than the Threshold after ISR event is noticed
    touchInterruptSetThresholdDirection(testingLower);
  }
}

void setup() {
  Serial.begin(115200);
  delay(1000); // give me time to bring up serial monitor
  pinMode(RelayPin1, OUTPUT);

  //During Starting all Relays should TURN OFF
  digitalWrite(RelayPin1, HIGH);
  
  Serial.println("ESP32 Touch Interrupt Test");
  touchAttachInterrupt(TouchPin1, gotTouchEvent, threshold);

  // Touch ISR will be activated when touchRead is lower than the Threshold
  touchInterruptSetThresholdDirection(testingLower);
}

void loop(){
  if(lastTouchActive != touchActive){
    lastTouchActive = touchActive;
    if (touchActive) {
      Serial.println("  ---- Touch was Pressed");
    } else {
      Serial.println("  ---- Touch was Released");
      digitalWrite(RelayPin1, !digitalRead(RelayPin1));
    }
  }
  Serial.println(digitalRead(RelayPin1));
  //Serial.printf(" ...");
  Serial.printf("T7 pin27 = %d \n", touchRead(TouchPin1));
  delay(125);
}
