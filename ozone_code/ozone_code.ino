/**
 * Two O3 sensors, one NO2 sensor, one temperature sensor
 * O3 and NO2 sensors need a cooldown period of 15 s. Alternate readings between both O3 sensors
 * Take measurements every half a second
 * Teensy
 * The file will stay open for 160 s
 * This code is for testing purposes only and needs to be revamped
 */
#include <SD.h>
#include <SPI.h>

File dataFile;

// Input pins
int temperaturePin = 18;
int O3aPin = 16;
int O3bPin = 16;
int NO2Pin = 15;
int PM25Pin = 17;

// Voltage per respective pin
int temperatureVolt;
int O3Volt;
int NO2Volt;
int PM25;

// Read from pins at this interval
unsigned long readInterval = 500;

// PM25 variables
int LED = 5;
int V0 = 17;
int PM25Volt;

//SD Card variables
int ss = 10;

int count = 1;
unsigned long tic = millis();
unsigned long toc;

bool flag = true;

void setup() {
  Serial.begin(9600);

  pinMode(temperaturePin, INPUT);
  pinMode(O3aPin, INPUT);
  pinMode(O3bPin, INPUT);
  pinMode(NO2Pin, INPUT);
  pinMode(PM25Pin, INPUT);

  // PM25 LED pulse
  pinMode(LED, OUTPUT);
  pinMode(ss, OUTPUT);

  if(!SD.begin(ss)){
    Serial.println("Initialization failed!");
    return;
    }
Serial.println("Initialization done");

dataFile = SD.open("ozone_data.txt", FILE_WRITE);

if(dataFile){
  Serial.print("File opened successfully.");
  dataFile.println("Project Ozone Data Collection");
  dataFile.println(" ");
  }
}

//opens the file

void loop() {
  toc = millis();
  if ((toc - tic) > readInterval) {
    temperatureVolt = analogRead(temperaturePin);
    digitalWrite(LED, HIGH);
    delayMicroseconds(320);
    digitalWrite(LED, LOW);
    PM25Volt = analogRead(V0);
    delay(9.68);
    tic = millis();

    if (dataFile) {
      dataFile.println("T = ");
      dataFile.print(temperatureVolt);
      dataFile.print(", ");
      dataFile.print("NO2 = ");
      dataFile.print(NO2Volt);
      dataFile.print(", ");
      dataFile.print("O3 = ");
      dataFile.print(O3Volt);
      dataFile.print(", ");
      dataFile.print("PM2.5 = ");
      dataFile.print(PM25Volt);    
      }
  }

  if (millis() / 8000 >= count) {
    if (flag) {
      O3Volt = analogRead(O3aPin);
    } else {
      O3Volt = analogRead(O3bPin);
      NO2Volt = analogRead(NO2Pin);
    }
    flag = !flag;
    count++;
  }

  if (toc - tic >= 5400000) { // an hour and a half for the test
    dataFile.println(" ");
    dataFile.println("Data collection finished");
    dataFile.close();
    Serial.end();
  }
}
