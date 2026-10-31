#include <Wire.h>
#include <Adafruit_BMP280.h>
#include <Adafruit_HMC5883_U.h>
#include <SPI.h>
#include <SD.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <MQ135.h>

#define CS_PIN 10
#define DHTPIN 8
#define DHTTYPE DHT11

Adafruit_BMP280 bmp;
Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(12345);
DHT dht(DHTPIN, DHTTYPE);
MQ135 mq135(A1);

File dataFile;

void setup() {
  Serial.begin(9600);
  SD.begin(CS_PIN);
  bmp.begin(0x76);
  mag.begin();
  dht.begin();
}

void loop() {
  float temperature = bmp.readTemperature();
  float pressure = bmp.readPressure();
  float dhtTemperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  float ppm = mq135.getPPM();
  sensors_event_t event;
  mag.getEvent(&event);
  float mag_x = event.magnetic.x;
  float mag_y = event.magnetic.y;
  float mag_z = event.magnetic.z;
  float mag_mod = sqrt(mag_x * mag_x + mag_y * mag_y + mag_z * mag_z);

  dataFile = SD.open("datalog.txt", FILE_WRITE);
  if (dataFile) {
    dataFile.print("Temperature (BMP280): "); dataFile.print(temperature); dataFile.print(" C, ");
    dataFile.print("Pressure: "); dataFile.print(pressure); dataFile.print(" Pa, ");
    dataFile.print("DHT Temperature: "); dataFile.print(dhtTemperature); dataFile.print(" C, ");
    dataFile.print("Humidity: "); dataFile.print(humidity); dataFile.print(" %, ");
    dataFile.print("Air Quality (MQ-135): "); dataFile.print(ppm); dataFile.print(" ppm, ");
    dataFile.print("Magnetometer (Modulus): "); dataFile.print(mag_mod); dataFile.println(" uT");
    dataFile.println("---------------------------------------------------");
    dataFile.close();
  }
  delay(1000);
}
