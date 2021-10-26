#include <Arduino.h>
#include "runtimer.h"

const int LED = 10; // pin for led
const int LDR = A5; //pin for photoresistor
int ambient;
int lightVal;

int inputVal=0; //variable for values to be read from A1
int outVal =0; //variable for output value from A1

intervalTimer writeOutputTimer(200U);
intervalTimer readInputTimer(50U);
intervalTimer displayValuesTimer(1000U);

void setup() {

  delay(200U);
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  pinMode(LDR, INPUT);

}

void loop() {

  if (readInputTimer.expired()){
    inputVal = analogRead(LDR); 
    outVal = map(inputVal, 0, 380, 255, 0); //The 0-1023 can be changed depending on light from your setup; for the phototransistor since it's analog read
  }

  if (writeOutputTimer.expired()){
    lightVal = constrain(outVal, 0,255);//to contain output values within 0-255 range for the LED
    analogWrite(LED, lightVal);
  }

  if (displayValuesTimer.expired())
  {
    ambient = analogRead(LDR);
    Serial.print("ambient = ");
    Serial.print(ambient);
    Serial.println("brightness = ");
    Serial.print(lightVal);
  }   
    //delay (500);
}