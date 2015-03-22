void readSerial(){
    int startT(0);
    int endT(0);
    int testVal;
    int testTyp;

    startT=Serial1.read();
    if( startT!=0xc5){
      Serial1.flush();
      Serial1.println("flushing");
      return;
    }
    
    testTyp = Serial1.read();
    testVal = Serial1.read();
    endT = Serial1.read();
    
    if(endT==0x5c && (testTyp>0 && testTyp<7) && (testVal>=0 && testVal <= 255) ){
      typ=testTyp;
      switch(testTyp){
        case 1:
          val=testVal;
          break;
        case 2:
          pidRateCoef=testVal;
          pidPitchRate.setGainsK(pidRateCoef/1000.0, 0.0, 0.0);
          pidRollRate.setGainsK(pidRateCoef/1000.0, 0.0, 0.0);
          pidYawRate.setGainsK(pidRateCoef/1000.0, 0.0, 0.0);
          break;
        case 3:
          pidCoef=testVal;
          pidPitch.setGainsK(pidCoef/10.0, 0.0, 0.0);
          pidRoll.setGainsK(pidCoef/10.0, 0.0, 0.0);
          pidYaw.setGainsK(pidCoef/10.0, 0.0, 0.0);
          break;
        case 4:
          desiredRate=(testVal-45)*10;
          break;
        case 5:
          desiredRoll=testVal-45;
          break;
        case 6:
          desiredPitch=testVal-45;
          break;
        default:  
          break;
      }
    }
    else{
      Serial1.println("error");
      return;
    }
}

void writeSerial(){
  bat=analogRead(3);
    
  Serial1.print("msg,");
  Serial1.print(ypr[0]);
  Serial1.print(",");
  Serial1.print(ypr[1]);
  Serial1.print(",");
  Serial1.print(ypr[2]);
  Serial1.print(",");
  Serial1.print(float(bat*0.009765625));
  Serial1.print(",");
  Serial1.print(val);
  Serial1.print(",");
  Serial1.print(pidRateCoef);
  Serial1.print(",");
  Serial1.print(pidCoef);
  Serial1.print(",");
  Serial1.print(desiredRate);
  Serial1.print(",");
  Serial1.print(desiredRoll);
  Serial1.print(",");
  Serial1.print(desiredPitch);
  Serial1.print(",");
  Serial1.println(typ);
}
