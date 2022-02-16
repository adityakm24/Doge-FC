#include <SD.h> //SD Card
//bmp280
#include <Wire.h>
#include "SPI.h" //Why? Because library supports SPI and I2C connection
#include <Adafruit_Sensor.h>
#include "Adafruit_BMP280.h"

//MPU
#include "I2Cdev.h"
#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"
//#include "MPU6050.h" // not necessary if using MotionApps include file


//bmp initialization
// define device I2C address: 0x76 or 0x77 (0x77 is library default address)
#define BMP280_I2C_ADDRESS  0x76
Adafruit_BMP280 bmp280;

const int chipSelect = 4; //SD Card Pin

void setup() {
  Serial.begin(9600);
  Serial.println(F("Arduino + BMP280"));
  
  if (!bmp280.begin(BMP280_I2C_ADDRESS))
  {  
    Serial.println("Could not find a valid BMP280 sensor, check wiring!");
    while (1);
  }
 //mpu code
  Wire.begin();
  Wire.beginTransmission(MPU6050_addr);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
  

  //SD Card init
  Serial.print("Initializing SD card...");

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    while (1);
  }
  Serial.println("card initialized.");
}


char text[14]; 
 



// main loop
void loop()
{
  // get temperature, pressure and altitude from library
  float temperature = bmp280.readTemperature();  // get temperature
  float pressure    = bmp280.readPressure();     // get pressure
  float altitude_   = bmp280.readAltitude(1013.25); // get altitude (this should be adjusted to your local forecast)
 
  // print data on the serial monitor software(bmp280)
  // 1: print temperature
  Serial.print("Temperature = ");
  Serial.print(temperature);
  Serial.println(" °C");
  // 2: print pressure
  Serial.print("Pressure    = ");
  Serial.print(pressure/100);
  Serial.println(" hPa");
  // 3: print altitude
  Serial.print("Approx Altitude = ");
  Serial.print(altitude_);
  Serial.println(" m");
    
  Serial.println();  // start a new line
  //delay(1000);   uncomment this if you need




  // print data on to the SD Card(bmp280)
  // 1: print temperature
  dataFile.print("Temperature = ");
  dataFile.print(temperature);
  dataFile.println(" °C");
  // 2: print pressure
  dataFile.print("Pressure    = ");
  dataFile.print(pressure/100);
  dataFile.println(" hPa");
  // 3: print altitude
  dataFile.print("Approx Altitude = ");
  dataFile.print(altitude_);
  dataFile.println(" m");
    
  dataFile.println();  // start a new line
  //delay(1000);   uncomment this if you need





  //mpu code
  Wire.beginTransmission(MPU6050_addr);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU6050_addr,14,true);
  AccX=Wire.read()<<8|Wire.read();
  AccY=Wire.read()<<8|Wire.read();
  AccZ=Wire.read()<<8|Wire.read();
  Temp=Wire.read()<<8|Wire.read();
  GyroX=Wire.read()<<8|Wire.read();
  GyroY=Wire.read()<<8|Wire.read();
  GyroZ=Wire.read()<<8|Wire.read();
  //serial printing MPU values
  Serial.print("AccX = "); Serial.print(AccX);
  Serial.print(" || AccY = "); Serial.print(AccY);
  Serial.print(" || AccZ = "); Serial.print(AccZ);
  Serial.print(" || Temp = "); Serial.print(Temp/340.00+36.53);
  Serial.print(" || GyroX = "); Serial.print(GyroX);
  Serial.print(" || GyroY = "); Serial.print(GyroY);
  Serial.print(" || GyroZ = "); Serial.println(GyroZ);
//serial printing MPU values
  dataFile.print("AccX = "); Serial.print(AccX);
  dataFile.print(" || AccY = "); Serial.print(AccY);
  dataFile.print(" || AccZ = "); Serial.print(AccZ);
  dataFile.print(" || Temp = "); Serial.print(Temp/340.00+36.53);
  dataFile.print(" || GyroX = "); Serial.print(GyroX);
  dataFile.print(" || GyroY = "); Serial.print(GyroY);
  dataFile.print(" || GyroZ = "); Serial.println(GyroZ);
  
}
// end of code.
 
 
