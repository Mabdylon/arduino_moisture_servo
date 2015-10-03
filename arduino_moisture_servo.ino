#include <Servo.h>
#include <JeeLib.h>

const int pinMoistureAnalog = A0;
const int pinMoistureDigital = 5;
const int pinServoAlert = 7;
Servo servoAlert;
int mappedMoisture;
int lastMappedMoisture;

ISR(WDT_vect) { Sleepy::watchdogEvent(); }

void setup() {
  pinMode(pinMoistureAnalog,INPUT);
  pinMode(pinMoistureDigital,INPUT);
  servoAlert.attach(pinServoAlert);
  Serial.begin(9600);
}

void loop() {
  int analogMoisture = analogRead(pinMoistureAnalog);
  int digitalMoisture = digitalRead(pinMoistureDigital);
  mappedMoisture = map(analogMoisture, 0, 1023, 0, 180);
  if(lastMappedMoisture != mappedMoisture) {
    servoAlert.write(mappedMoisture);
    lastMappedMoisture = mappedMoisture;  
  }
  delay(2000);

  //Sleepy::loseSomeTime(60000);
  
  Serial.print("Analog Moisture : ");
  Serial.println(analogMoisture);
  Serial.print("Digital Moisture : ");
  Serial.println(digitalMoisture);
  Serial.println("-----------------------");
  
  
}

