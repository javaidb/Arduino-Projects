/*
 * created by Rui Santos, http://randomnerdtutorials.com
 * Ultrasonic Sensor with LED's bar graph and buzzer 
*/
#include "pitches.h"

int tonePin = 4;    //Tone - Pin connected to TONE of Ultrasonic
int trigPin = 10;    //Trig - Pin connected to TRIG of Ultrasonic
int echoPin = 9;   //Echo - Pin connected to ECHO of Ultrasonic
int clockPin = 11;  //IC Pin 11
int latchPin = 12;  //IC Pin 12
int dataPin = 13;   //IC Pin 14
 
byte possible_patterns[9] = {
B00000000, 
B00000001,
B00000011,
B00000111,
B00001111,
B00011111,
B00111111, 
B01111111, 
B11111111,
};
int proximity=0;
int duration;
int distance;

int jawsmelody[] = {
  NOTE_D4, NOTE_DS4
};


int tempo1[] = {
  2, 6
};

int tempo2[] = {
  3, 3
};

int tempo3[] = {
  6, 6
};

int size = sizeof(jawsmelody) / sizeof(int);

void setup() {
  //Serial Port
  Serial.begin (9600);
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(tonePin, OUTPUT);
}
 
void loop() {
  digitalWrite(latchPin, LOW);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(1000);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  
  //Serial Monitor to see distance
  if (distance >= 20 || distance <= 0){
    Serial.println("Out of range");
  }
  else {
    Serial.print(distance);
    Serial.println(" cm");
  }
  
  proximity=map(distance, 0, 20, 8, 0);
  //Serial.println(proximity);

  //Buzzer Proximity settings to sound at a certain distance/LEDs lit
  if (proximity <= 0){
    proximity=0;
  }
  else if (proximity >= 2 && proximity < 3){
    for (int thisNote = 0; thisNote < size; thisNote++) {
        int duration = 1000/tempo1[thisNote];  
        tone(tonePin, jawsmelody[thisNote], duration);
        int pause = duration *1.3;
        // Delay between each successive note
        delay(pause);
    }
    delay(1000);
  }
  else if (proximity >= 3 && proximity <= 5){
    for (int thisNote = 0; thisNote < size; thisNote++) {
        int duration = 1000/tempo2[thisNote];  
        tone(tonePin, jawsmelody[thisNote], duration);
        int pause = duration *1.3;
        // Delay between each successive note
        delay(pause);
    }
  }
  else if (proximity >= 6 && proximity <= 8){
    for (int thisNote = 0; thisNote < size; thisNote++) {
        int duration = 1000/tempo3[thisNote];  
        tone(tonePin, jawsmelody[thisNote], duration);
        int pause = duration *1.3;
        // Delay between each successive note
        delay(pause);
    }
  }
  shiftOut(dataPin, clockPin, MSBFIRST, possible_patterns[proximity]);
  digitalWrite(latchPin, HIGH);
 
  
  //delay(500);
  noTone(tonePin);
}