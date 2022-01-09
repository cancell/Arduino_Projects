#include  <SPI.h> // SPI Arayüzünü dahil ettik.
#include "nRF24L01.h" // RF24 kütüpanelerini dahil ettik.
#include "RF24.h" // RF24 kütüpanelerini dahil ettik.
int trig1 = 2;
int echo1 = 3;
int trig2 = 4;
int echo2 = 5;
int trig3 = 6;
int echo3 = 7;
int duration1;
int duration2;
int duration3;
int distance1;
int distance2;
int distance3;
RF24 radio(9, 10); //RF24 kütüphanesi tarafından kullanılacak olan 2 pinin 9. ve 10. pinlerin olduğunu belirttik.

bool msg[3]; //Göndereceğimiz mesaj değişkenini oluşturduk.
const uint64_t pipe = 0xE8E8F0F0E1LL; // Pipe (kanal) tanımlamasını yaptık.

bool empty1 = false;
bool empty2 = false;
bool empty3 = false;

void setup() {
  Serial.begin(9600);

  radio.begin(); // Kablosuz iletişimi başlattık.
  radio.openWritingPipe(pipe);
  pinMode(trig1, OUTPUT);
  pinMode(trig2, OUTPUT);
  pinMode(trig3, OUTPUT);
  pinMode(echo1, INPUT);
  pinMode(echo2, INPUT);
  pinMode(echo3, INPUT);
}

void loop() {
  digitalWrite(trig1, LOW);
  delayMicroseconds(2);
  digitalWrite(trig1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig1, LOW);
  duration1 = pulseIn(echo1, HIGH);
  distance1 = (duration1 / 2) / 29.1;
  digitalWrite(trig2, LOW);
  delayMicroseconds(2);
  digitalWrite(trig2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig2, LOW);
  duration2 = pulseIn(echo2, HIGH);
  distance2 = (duration2 / 2) / 29.1;
  digitalWrite(trig3, LOW);
  delayMicroseconds(2);
  digitalWrite(trig3, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig3, LOW);
  duration3 = pulseIn(echo3, HIGH);
  distance3 = (duration3 / 2) / 29.1;
  Serial.print("distance1:");
  Serial.println(distance1);
  Serial.print("distance2:");
  Serial.println(distance2);
  Serial.print("distance3:");
  Serial.println(distance3);
  delay(200);
  //sedye odaya girdi mi? (did the device make it alive till the room?)
  if (distance1 > 0 and distance1 < 20) {
    empty1 = false;
  }
  else if (distance1 >= 20) {
    empty1 = true;
  }
  if (distance2 > 0 and distance2 < 20) {
    empty2 = false;
  }
  else if (distance2 >= 20) {
    empty2 = true;
  }
  if (distance3 > 0 and distance3 < 20) {
    empty3 = false;
  }
  else if (distance3 >= 20) {
    empty3 = true;
  }

  msg[0] = empty1;
  msg[1] = empty2;
  msg[2] = empty3;

  radio.write(msg, sizeof(msg));



}
