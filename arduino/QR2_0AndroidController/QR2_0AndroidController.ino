#define motorFr   10    // Front left
#define motorFl   9    // Front right
#define motorBr   6    // back left
#define motorBl   5    // back right

#include <ADXL345.h>
#include <HMC58X3.h>
#include <L3G4200D.h>
#include <I2Cdev.h>
#include <EEPROM.h>
#include <Pid.h>

//#define DEBUG
//#include "DebugUtils.h"
//#include "CommunicationUtils.h"
#include "FreeIMU.h"
#include <Wire.h>
#include <SPI.h>

float ypr[3];
float gyro[3];
int val(0);
int typ(0);
int desiredRoll(0);
int desiredPitch(0);

Pid pidPitchRate;
Pid pidRollRate;
Pid pidYawRate;
Pid pidPitch;
Pid pidRoll;
Pid pidYaw;

int i=0;
int bat = 0;

// Set the FreeIMU object
FreeIMU my3IMU = FreeIMU();

void setup() {
  Serial.begin(9600);
  Serial1.begin(115200);
  while (!Serial1){}
  initializeMotors();
  initializePID();
  Wire.begin();
  my3IMU.init(true);
}


void loop() {
  my3IMU.getYawPitchRoll(ypr);
  //my3IMU.getEuler(ypr);
  my3IMU.gyro.readGyro(gyro);

  if(Serial1.available()>3)
    readSerial();

  if(i++%10==0)
    writeSerial();

   if(val>1){
    int pitch = pidPitch.compute(desiredPitch-ypr[2]);
    int roll = pidRoll.compute(ypr[1]-desiredRoll);
    //int yaw = pidYaw.compute(ypr[0]-0);
    int pitch_output =   pidPitchRate.compute(pitch-gyro[0]);
    int roll_output  =   pidRollRate.compute(roll-gyro[1]);
    int yaw_output   =   pidYawRate.compute(0-gyro[2]);
    //int yaw_output   = 0;
    
    int motorFrOutput= (( val + roll_output - pitch_output - yaw_output)<0)?0: val + roll_output - pitch_output - yaw_output;
    int motorFlOutput= (( val - roll_output - pitch_output + yaw_output)<0)?0: val - roll_output - pitch_output + yaw_output;
    int motorBrOutput= (( val + roll_output + pitch_output + yaw_output)<0)?0: val + roll_output + pitch_output + yaw_output;
    int motorBlOutput= (( val - roll_output + pitch_output - yaw_output)<0)?0: val - roll_output + pitch_output - yaw_output;
    
//    Serial.print(pitch);
//    Serial.print("   ");
//    Serial.print(roll);
//    Serial.print("   ");
//    Serial.print(pitch_output);
//    Serial.print("   ");
//    Serial.print(roll_output);
//    Serial.print("   ");
//    Serial.print( motorFrOutput);
//    Serial.print("   ");
//    Serial.print( motorFlOutput);
//    Serial.print("   ");
//    Serial.print( motorBrOutput);
//    Serial.print("   ");
//    Serial.println( motorBlOutput);
    
    analogWrite(motorFr, motorFrOutput);
    analogWrite(motorFl, motorFlOutput);
    analogWrite(motorBr, motorBrOutput);
    analogWrite(motorBl, motorBlOutput);

   }
   else{
     analogWrite(motorFr,val);
     analogWrite(motorFl,val);
     analogWrite(motorBr,val);
     analogWrite(motorBl,val);

     pidPitchRate.resetPid();
     pidRollRate.resetPid();
     pidYawRate.resetPid();
     
     pidPitch.resetPid();
     pidRoll.resetPid();
     pidYaw.resetPid();
   }
}


void initializeMotors(){
  pinMode(motorFr,OUTPUT);
  pinMode(motorFl,OUTPUT);
  pinMode(motorBr,OUTPUT);
  pinMode(motorBl,OUTPUT);
  pinMode(17,OUTPUT);

  analogWrite(motorFr,0);
  analogWrite(motorFl,0);
  analogWrite(motorBr,0);
  analogWrite(motorBl,0);
}

void initializePID(){

 pidPitchRate.setMaxMin(25,-25);
 pidRollRate.setMaxMin(25,-25);
 pidYawRate.setMaxMin(45,-45);

 pidPitchRate.setGainsK(0.055, 0.0, 0.0);
 pidRollRate.setGainsK(0.055, 0.0, 0.0);
 pidYawRate.setGainsK(0.85, 0.0, 0.0);
 
 pidPitch.setMaxMin(250,-250);
 pidRoll.setMaxMin(250,-250);
 pidYaw.setMaxMin(250,-250);

 pidPitch.setGainsK(5, 0.0, 0.0);
 pidRoll.setGainsK(5, 0.0, 0.0);
 pidYaw.setGainsK(5, 0.0, 0.0);
}
