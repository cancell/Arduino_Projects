#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

int msg[3];
const uint64_t pipe = 0xE8E8F0F0E1LL;

RF24 radio(9, 10);


int hiz1 = 100;
int hiz2 = 100;


const int enablePin = 6;
const int enablePin2 = 5;

const int in1Pin = 8;
const int in2Pin = 4;
const int in3Pin = 3;
const int in4Pin = 2;



void setup(void) {
  Serial.begin(9600);

  radio.begin();
  radio.openReadingPipe(1, pipe);
  radio.startListening();



  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);
  pinMode(in3Pin, OUTPUT);
  pinMode(in4Pin, OUTPUT);

  pinMode(enablePin, OUTPUT);
  pinMode(enablePin2, OUTPUT);
}

void loop(void) {
  if (radio.available()) {
    radio.read(msg, sizeof(msg));
    sinyal(msg[0], msg[1], msg[2]);
    Serial.println("Baglaniyor");
  }
  else {
    Serial.println("No radio available");


    analogWrite(enablePin, 0);
    digitalWrite(in1Pin, LOW);
    digitalWrite(in2Pin, LOW);
    analogWrite(enablePin2, 0);
    digitalWrite(in3Pin, LOW);
    digitalWrite(in4Pin, LOW);

  }
}




void sinyal(bool empty1, bool empty2, bool empty3) {

  //****************************WAIT************************//
  if ((empty1 == false) & (empty2 == false) & (empty3 == false)) {
    analogWrite(enablePin, 0);
    digitalWrite(in1Pin, LOW);
    digitalWrite(in2Pin, LOW);
    analogWrite(enablePin2, 0);
    digitalWrite(in3Pin, LOW);
    digitalWrite(in4Pin, LOW);
  }

  //**********************1. ODA**********************//
  if ((empty1 == true) & (empty2 == false) & (empty3 == false)) {
    analogWrite(enablePin, hiz1);   //1. ODA için biraz ileri gidip 1 sn sonra sağa dönüyor, 1 sn sonra yine sağa dönüyor.
    digitalWrite(in1Pin, HIGH);
    digitalWrite(in2Pin, LOW);
    analogWrite(enablePin2, hiz1);
    digitalWrite(in3Pin, HIGH);
    digitalWrite(in4Pin, LOW);
    delay(1000);
    analogWrite(enablePin, hiz2);
    digitalWrite(in1Pin, LOW);
    digitalWrite(in2Pin, HIGH);
    analogWrite(enablePin2, hiz2);
    digitalWrite(in3Pin, HIGH);
    digitalWrite(in4Pin, LOW);
    delay(1000);
    analogWrite(enablePin, hiz2);
    digitalWrite(in1Pin, LOW);
    digitalWrite(in2Pin, HIGH);
    analogWrite(enablePin2, hiz2);
    digitalWrite(in3Pin, HIGH);
    digitalWrite(in4Pin, LOW);
    delay(1000);
    empty1= false;
  }

  //**********************2. ODA**********************//
  if ((empty1 == false) & (empty2 == true) & (empty3 == false)) {
    analogWrite(enablePin, hiz1); //2. ODA için biraz ileri gidip 1 sn sonra sağa dönüyor, 2 sn sonra yine sağa dönüyor.
    digitalWrite(in1Pin, HIGH);
    digitalWrite(in2Pin, LOW);
    analogWrite(enablePin2, hiz1);
    digitalWrite(in3Pin, HIGH);
    digitalWrite(in4Pin, LOW);
    delay(1000);
    analogWrite(enablePin, hiz2);
    digitalWrite(in1Pin, LOW);
    digitalWrite(in2Pin, HIGH);
    analogWrite(enablePin2, hiz2);
    digitalWrite(in3Pin, HIGH);
    digitalWrite(in4Pin, LOW);
    delay(2000);
    analogWrite(enablePin, hiz2);
    digitalWrite(in1Pin, LOW);
    digitalWrite(in2Pin, HIGH);
    analogWrite(enablePin2, hiz2);
    digitalWrite(in3Pin, HIGH);
    digitalWrite(in4Pin, LOW);
    delay(1000);
    empty2= false;
  }
  //**********************3. ODA**********************//
  if ((empty1 == false) & (empty2 == false) & (empty3 == true)) {
    analogWrite(enablePin, hiz1);   //3. ODA için biraz ileri gidip 1 sn sonra sağa dönüyor, 1 sn sonra yine sağa dönüyor.
    digitalWrite(in1Pin, HIGH);
    digitalWrite(in2Pin, LOW);
    analogWrite(enablePin2, hiz1);
    digitalWrite(in3Pin, HIGH);
    digitalWrite(in4Pin, LOW);
    delay(1000);
    analogWrite(enablePin, hiz2);
    digitalWrite(in1Pin, LOW);
    digitalWrite(in2Pin, HIGH);
    analogWrite(enablePin2, hiz2);
    digitalWrite(in3Pin, HIGH);
    digitalWrite(in4Pin, LOW);
    delay(3000);
    analogWrite(enablePin, hiz2);
    digitalWrite(in1Pin, LOW);
    digitalWrite(in2Pin, HIGH);
    analogWrite(enablePin2, hiz2);
    digitalWrite(in3Pin, HIGH);
    digitalWrite(in4Pin, LOW);
    delay(1000);
    empty3= false;
  }
 
}
