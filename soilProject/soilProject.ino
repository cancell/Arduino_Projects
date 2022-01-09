#define BLYNK_PRINT Serial
#include <SPI.h>
#include <RFID.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SimpleTimer.h>
#include <DHT.h>

char auth[] = "ef9d86b880da43feb15f5546e95b0afa"; //Enter the Auth code
char ssid[] = "Cancel";
char pass[] = "cansel1635.";

#define DHTPIN 2          // Digital pin 4
#define DHTTYPE DHT11

#define SS_PIN D0
#define RST_PIN D1

RFID rfid (SS_PIN, RST_PIN);
int cardNum;

int soilPin = A0;
int soilValue;
int led = D3;
int buzzer = D2;


DHT dht(DHTPIN, DHTTYPE);
SimpleTimer timer;

void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); 

  if (isnan(h) || isnan(t)) {
    return;
  }
  Blynk.virtualWrite(V5, h);  //V5 is for Humidity
  Blynk.virtualWrite(V6, t);  //V6 is for Temperature

  if (t > 25) {
    Blynk.email("cansel.kucuk@gmail.com", "ESP8266 Alert", "Sıcaklık 25C'nin üzerine çıktı.");
    Blynk.notify("Sıcaklık 25C'nin üzerinde!");
  }
}

void soilControl(int pin) {
  soilValue = analogRead(pin);
  if (soilValue > 900) {
    digitalWrite(led, HIGH);
    //Blynk.notify("Toprak nem değeri düştü!");
  }
  else {
    digitalWrite(led, LOW);
  }
}


void rfidRead() {
  if (rfid.isCard()) {
    if (rfid.readCardSerial()) {
      cardNum = rfid.serNum[0];
      Serial.print("Card number: ");
      Serial.println(cardNum);
      if (cardNum == 196) {
        digitalWrite(buzzer, LOW);
        Serial.println("Kapı aciliyor...");
      }
      else {
        digitalWrite(buzzer, HIGH);
        delay(50);
        digitalWrite(buzzer, LOW);
        delay(50);
        Blynk.notify("Hırsız olabilir!!!");
      }
      delay(500);
    }
  }
}

void setup()
{
  // Debug console
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  pinMode(led, OUTPUT);
  pinMode(buzzer, OUTPUT);
  SPI.begin();
  rfid.init();
  dht.begin();
  timer.setInterval(1000L, sendSensor);
}

void loop()
{
  rfidRead();
  soilControl(soilPin);
  sendSensor();
  Blynk.run();
  timer.run();
}
