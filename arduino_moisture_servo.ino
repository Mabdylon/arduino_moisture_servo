#include <VarSpeedServo.h>
#include <JeeLib.h>

const int pinMoistureAnalog = A0;
const int pinMoistureDigital = 5;
const int pinSerovMesure = 7;
const int pinSerovAlert = 6;
VarSpeedServo servoMesure;
VarSpeedServo servoAlert;
int mappedMoisture = 0;
int lastMappedMoisture = 0;
int digitalMoisture = 0;
int lastDigitalMoisture = 0;

ISR(WDT_vect) { Sleepy::watchdogEvent(); }

void setup() {
  pinMode(pinMoistureAnalog,INPUT);
  pinMode(pinMoistureDigital,INPUT);
  servoMesure.attach(pinSerovMesure);
  servoAlert.attach(pinSerovAlert);
  Serial.begin(9600);
}

void loop() {
  int analogMoisture = analogRead(pinMoistureAnalog);
  digitalMoisture = digitalRead(pinMoistureDigital);
  mappedMoisture = map(analogMoisture, 0, 1023, 0, 180);
  if(lastMappedMoisture != mappedMoisture) {
    servoMesure.write(mappedMoisture, 20, true);
    lastMappedMoisture = mappedMoisture;  
  }
  if(digitalMoisture != lastDigitalMoisture) {
       int flagAlertPosition = (digitalMoisture == 0 ? 90 : 180);
       servoAlert.write(flagAlertPosition, 40, true);
       lastDigitalMoisture = digitalMoisture;
    }

  Serial.print("Analog Moisture : ");
  Serial.println(analogMoisture);
  Serial.print("Digital Moisture : ");
  Serial.println(digitalMoisture);
  Serial.println("-----------------------");
  
  Sleepy::loseSomeTime(5000);
  
  
}

