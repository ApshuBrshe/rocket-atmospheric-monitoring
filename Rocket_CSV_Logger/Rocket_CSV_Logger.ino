#include <Wire.h>
#include <Adafruit_BMP280.h>
#include <SPI.h>
#include <SD.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <MQ135.h>

#define CS_PIN 10
#define DHTPIN 8
#define DHTTYPE DHT11

Adafruit_BMP280 bmp;
DHT dht(DHTPIN, DHTTYPE);
MQ135 mq135(A1);

File dataFile;

void setup() {
  Serial.begin(9600);
  SD.begin(CS_PIN);
  bmp.begin(0x76);
  dht.begin();

  // Write CSV header if the file is new
  dataFile = SD.open("datalog.csv", FILE_WRITE);
  if (dataFile && dataFile.size() == 0) {
    dataFile.println("time,temperature,height,gas,humidity");
    dataFile.close();
  }
}

void loop() {
  float temperature = bmp.readTemperature();
  float height = bmp.readAltitude(101325.0);
  float ppm = mq135.getPPM();
  float humidity = dht.readHumidity();

  unsigned long currentTime = millis();

  dataFile = SD.open("datalog.csv", FILE_WRITE);
  if (dataFile) {
    dataFile.print(currentTime); dataFile.print(",");
    dataFile.print(temperature); dataFile.print(",");
    dataFile.print(height); dataFile.print(",");
    dataFile.print(ppm); dataFile.print(",");
    dataFile.print(humidity);
    dataFile.close();
  }

  delay(1000);
}
