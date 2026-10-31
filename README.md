# Rocket Atmospheric Monitoring System

**Green Guardian | 2023–2025**

This was a school engineering project I worked on with my friend **Lev Svetoshev**. We built a rocket with an onboard sensor system to collect atmospheric data during flight. We worked together on the electronics, programming, assembly, and testing. We also made parts of the rocket in 3D and used flight simulation while developing it.

We launched the rocket and collected data during flight. The full project also used a radio link to send readings to a laptop on the ground. The radio code is not part of the files I managed to recover.

## What's in this repository

I found several Arduino sketches from the project and decided to keep them here. They are different versions we used while developing the system, not a single finished program.

| File | What it does |
| --- | --- |
| `Rocket_Sensor_Monitor/Rocket_Sensor_Monitor.ino` | Displays live sensor readings in Serial Monitor |
| `Rocket_SD_Data_Logger/Rocket_SD_Data_Logger.ino` | Saves sensor readings to `datalog.txt` on an SD card |
| `Rocket_CSV_Logger/Rocket_CSV_Logger.ino` | An early attempt at writing readings in CSV format |

The sketches use a BMP280 pressure sensor, DHT11 temperature/humidity sensor, MQ-135 gas sensor, and, in some versions, an HMC5883 magnetometer. The logging versions also use an SD card module.

## Using the code

Open one of the `.ino` files in Arduino IDE, install the libraries used in that sketch, and select the correct board and port. Serial output is set to **9600 baud**.

The original board model still needs to be confirmed. The code uses D8 for DHT11, A1 for MQ-135, D10 for the SD card, and `0x76` for BMP280. Check the wiring and voltage requirements before connecting hardware.

Libraries used across the sketches include `Wire`, `SPI`, `SD`, `Adafruit BMP280 Library`, `Adafruit Unified Sensor`, `Adafruit HMC5883 Unified`, `DHT sensor library`, and `MQ135` (with the `getPPM()` API).

## A few notes

These are old files from our student project, not a cleaned-up production release. I haven't tested them again on the original hardware. In particular, the CSV sketch has a line-ending issue that can join multiple records together. The sensor readings also shouldn't be treated as calibrated scientific measurements without checking the sensors; for example, MQ-135 readings are not automatically accurate CO₂ measurements.

We also had 3D models and other hardware files. I'll add them separately if I can recover and sort them out.

Our project took first place at the **Sozvezdie 2025** competition in Korolyov, Russia. Lev presented it there on behalf of our team.

## Team

- **Stanislav Kim** — co-developer
- **Lev Svetoshev** — co-developer

We worked on the main engineering parts together. Lev also developed a separate AI-based tool for analyzing collected data; that work isn't included in this repository.
