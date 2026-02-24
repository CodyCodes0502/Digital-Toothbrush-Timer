#include <Arduino.h>

#include <Wire.h>
#include <MD_MAX72xx.h>
#include <MD_Parola.h>
#include <MPU6500_WE.h>

#define DEBUG 1 //Debug flag 

#if DEBUG
  #define DEBUG_PRINTLN(x) Serial.println(x)
  #define DEBUG_PRINT(x) Serial.print(x)
#else
  #define DEBUG_PRINTLN(x)
  #define DEBUG_PRINT(x)
#endif

#define DATAPIN 8
#define CSPIN 9
#define CLKPIN 10

MPU6500_WE mpu = MPU6500_WE(0x68);

uint8_t numDisplays = 2;

//Test Message to be displayed on the LED matrix
//String testMessage = "A long time ago in a galaxy far, far away...";

//MD_MAX72XX display = MD_MAX72XX(MD_MAX72XX::GENERIC_HW, DATAPIN, CLKPIN, CSPIN, numDisplays);
//MD_Parola parola = MD_Parola(MD_MAX72XX::GENERIC_HW, DATAPIN, CLKPIN, CSPIN, numDisplays);

// put function declarations here:
void print_roll_pitch_yaw();

void setup() {
  // put your setup code here, to run once:
  //display.begin();
  //display.clear();
  Serial.begin(115200);
  Wire.begin();
  delay(2000);

  //Initialize the mpu, sending a debug error message if it fails.
  if(!mpu.init()){
    DEBUG_PRINTLN("MPU setup failed. Check Connections, please.");
    while(1) {
      delay(10);
    }
  }

  //Calibrate the MPU while it is still on a flat surface, delaying for a second before starting callibration
  DEBUG_PRINTLN("MPU Found!");
  DEBUG_PRINTLN("Calibrating MPU, Do not move device.");
  DEBUG_PRINTLN("Callibrating....");
    
  delay(1000);
  mpu.autoOffsets();

  DEBUG_PRINTLN("Calibration Complete");


  //Enable digital low pass filter.
  mpu.enableGyrDLPF();
  mpu.setGyrDLPF(MPU6500_DLPF_6); //DLPF can be from 0-6, with 6 achiving the lowest noise level with the highest delay.

  mpu.setSampleRateDivider(5);
  mpu.setGyrRange(MPU6500_GYRO_RANGE_250);
  mpu.setAccRange(MPU6500_ACC_RANGE_2G);

  mpu.enableAccDLPF(true);
  mpu.setAccDLPF(MPU6500_DLPF_6);
  delay(200);
}

void loop() {
  xyzFloat gValue = mpu.getGValues();
  xyzFloat gyr = mpu.getGyrValues();
  float temp = mpu.getTemperature();
  float resultantG = mpu.getResultantG(gValue);

  Serial.println("Acceleration in g (x,y,z):");
  Serial.print(gValue.x);
  Serial.print("   ");
  Serial.print(gValue.y);
  Serial.print("   ");
  Serial.println(gValue.z);
  Serial.print("Resultant g: ");
  Serial.println(resultantG);

  Serial.println("Gyroscope data in degrees/s: ");
  Serial.print(gyr.x);
  Serial.print("   ");
  Serial.print(gyr.y);
  Serial.print("   ");
  Serial.println(gyr.z);

  Serial.print("Temperature in °C: ");
  Serial.println(temp);

  Serial.println("********************************************");

  delay(1000);
  

  
}

// put function definitions here:
void print_roll_pitch_yaw() {

}