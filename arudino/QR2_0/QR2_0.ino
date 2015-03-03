#include <ADXL345.h>
#include <HMC58X3.h>
#include <L3G4200D.h>
#include <I2Cdev.h>
#include <EEPROM.h>

#define DEBUG
#include "DebugUtils.h"
#include "CommunicationUtils.h"
#include "FreeIMU.h"
#include <Wire.h>
#include <SPI.h>

char cmd;
float ypr[3];
int value(0);
int type(0);

int i=0;
int bat = 0;

// Set the FreeIMU object
FreeIMU my3IMU = FreeIMU();

void setup() {
  Serial1.begin(115200);
  while (!Serial1){}
  initializeMotors();
  Wire.begin();
  my3IMU.init(true);
}


void loop() {
  //my3IMU.getYawPitchRoll(ypr);
  my3IMU.getEuler(ypr);
  
  if(Serial1.available()>3)
    readSerial();
 
    if(i++%10==0)
     writeSerial();
}


void initializeMotors(){
  pinMode(10,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(17,OUTPUT);
  
  analogWrite(5,0);
  analogWrite(6,0);
  analogWrite(9,0);
  analogWrite(10,0);
}

void readSerial(){
    int startT(0);
    int endT(0);

    startT=Serial1.read();
    if( startT!=0xc5){
      Serial1.flush();
      Serial1.println("flushing");
      return;
    }
    
    type = Serial1.read();
    value = Serial1.read();
    endT = Serial1.read();
    
    if(endT!=0x5c){
      Serial1.println("error");
      return;
    }
    
    analogWrite(5,value);
    analogWrite(6,value);
    analogWrite(9,value);
    analogWrite(10,value);   
}

void writeSerial(){
  Serial1.print("msg,");
  Serial1.print(ypr[0]);
  Serial1.print(",");
  Serial1.print(ypr[1]);
  Serial1.print(",");
  Serial1.print(ypr[2]);
   
  bat=analogRead(3);
  Serial1.print(",");
  Serial1.print(float(bat*0.009765625));
  Serial1.print(",");
  Serial1.print(value);
  Serial1.print(",");
  Serial1.println(type);
}

