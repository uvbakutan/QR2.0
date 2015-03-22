#ifndef Pid_h
#define Pid_h

#include "Arduino.h"

class Pid{
  int maxOutput, minOutput;
  long lastT;
  float kp,ki,kd, lastError;
  public:
   Pid():maxOutput(0), minOutput(0),lastT(millis()),kp(0),kd(0),ki(0), lastError(0){}
   
   void setMaxMin(int Max, int Min){ maxOutput = Max; minOutput = Min; }
   void setGainsK(float p, float i, float d){ kp = p; ki = i; kd = d; }
   void resetPid() { lastT=millis(); lastError=0; }
   int compute(int error) {
     int pwm;
     float time( (millis()-lastT)/1000.0 );
     
     pwm = int( kp*error + (ki*time*(error+lastError)/2.0) + (kd*(error-lastError)/time));
     
     if(pwm>maxOutput) pwm=maxOutput;
     if(pwm<minOutput) pwm=minOutput;
    
     lastError=error;
     return pwm;
  }

};

#endif
