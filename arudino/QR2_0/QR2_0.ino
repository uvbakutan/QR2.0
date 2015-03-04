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
int rotateR(0);
int rateA(0);

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
  my3IMU.gyro.readGyro(gyro);;

  if(Serial1.available()>3)
    readSerial();

  if(i++%10==0)
    writeSerial();

   if(val>1){
    int pitch = pidPitch.compute(ypr[2]-0);
    int roll = pidRoll.compute(ypr[1]-0);
    int pitch_output =  pidPitchRate.compute(pitch-gyro[0]);
    int roll_output =   pidRollRate.compute(roll-gyro[1]);
    //int yaw_output =   pids[PID_YAW_RATE].get_pid(gyroYaw - rcyaw, 1);
    
//    Serial.print(pitch);
//    Serial.print("   ");
//    Serial.print(roll);
//    Serial.print("   ");
//    Serial.print(pitch_output);
//    Serial.print("   ");
//    Serial.println(roll_output);
    
    int yaw_output = 0;
    
    analogWrite(motorFr, val - roll_output + pitch_output);
    analogWrite(motorFl, val + roll_output + pitch_output);
    analogWrite(motorBr, val - roll_output - pitch_output);
    analogWrite(motorBl, val + roll_output - pitch_output);

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

 pidPitchRate.setMaxMin(5,-5);
 pidRollRate.setMaxMin(5,-5);
 pidYawRate.setMaxMin(5,-5);

 pidPitchRate.setGainsK(0.0, 0.0, 0.0);
 pidRollRate.setGainsK(0.0, 0.0, 0.0);
 pidYawRate.setGainsK(0.0, 0.0, 0.0);
 
 pidPitch.setMaxMin(100,-100);
 pidRoll.setMaxMin(100,-100);
 pidYaw.setMaxMin(100,-100);

 pidPitch.setGainsK(0.0, 0.0, 0.0);
 pidRoll.setGainsK(0.0, 0.0, 0.0);
 pidYaw.setGainsK(0.0, 0.0, 0.0);
}
