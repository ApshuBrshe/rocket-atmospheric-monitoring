#include <Wire.h>  
#include <Adafruit_BMP280.h>
#include <Adafruit_HMC5883_U.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <MQ135.h>

#define DHTPIN 8
#define DHTTYPE DHT11

Adafruit_BMP280 bmp;
Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(12345);
DHT dht(DHTPIN, DHTTYPE);
MQ135 mq135(A1);

void setup() {
  Serial.begin(9600);
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

  // Send all sensor readings to the Serial Monitor
  Serial.print("Temperature (BMP280): "); Serial.print(temperature); Serial.print(" C, ");
  Serial.print("Pressure: "); Serial.print(pressure); Serial.print(" Pa, ");
  Serial.print("DHT Temperature: "); Serial.print(dhtTemperature); Serial.print(" C, ");
  Serial.print("Humidity: "); Serial.print(humidity); Serial.print(" %, ");
  Serial.print("Air Quality (MQ-135): "); Serial.print(ppm); Serial.print(" ppm, ");
  Serial.print("Magnetometer X: "); Serial.print(mag_x); Serial.print(" uT, ");
  Serial.print("Magnetometer Y: "); Serial.print(mag_y); Serial.print(" uT, ");
  Serial.print("Magnetometer Z: "); Serial.print(mag_z); Serial.print(" uT, ");
  Serial.print("Magnetometer (Modulus): "); Serial.print(mag_mod); Serial.println(" uT");
  
  delay(1000);
}
