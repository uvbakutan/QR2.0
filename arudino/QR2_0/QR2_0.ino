#include <ADXL345.h>
#include <HMC58X3.h>
#include <L3G4200D.h>
#include <I2Cdev.h>
#include <EEPROM.h>

//#define DEBUG
#include "DebugUtils.h"
#include "CommunicationUtils.h"
#include "FreeIMU.h"
#include <Wire.h>
#include <SPI.h>

char cmd;
float ypr[3];

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
  my3IMU.getYawPitchRoll(ypr);
  
  if(Serial1.available()>0)
    readSerial();
  
   
  if(i++%10==0){
    Serial1.print("eul: ");
    Serial1.print(ypr[0]);
    Serial1.print("  ");
    Serial1.print(ypr[1]);
    Serial1.print("  ");
    Serial1.println(ypr[2]);
     Serial1.print("  ");
     
     bat=analogRead(3);
    Serial1.println(float(bat*0.009765625));
  }
  
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
    char input;
    input = Serial1.read();
    Serial1.print("recieved ");
    Serial1.println(input);
    
    switch (input){
      case 'z' : {
          analogWrite(5,0);
          analogWrite(6,0);
          analogWrite(9,0);
          analogWrite(10,0);
      } break ;
      
      case 'f' : {
          analogWrite(5,255);
          analogWrite(6,255);
          analogWrite(9,255);
          analogWrite(10,255);
      } break ;
      
      case 'h' : {
          analogWrite(5,150);
          analogWrite(6,150);
          analogWrite(9,150);
          analogWrite(10,150);
      } break ;
      
      case 's' : {
          analogWrite(5,30);
          analogWrite(6,30);
          analogWrite(9,30);
          analogWrite(10,30);
      } break ;
      
      default : {
          analogWrite(5,0);
          analogWrite(6,0);
          analogWrite(9,0);
          analogWrite(10,0);   
      }break;
    }
}

