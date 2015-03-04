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
    
    if(endT==0x5c && (testTyp==1 || testTyp==2 || testTyp==3) && (testVal>=0 && testVal <= 255) ){
      typ=testTyp;
      switch(testTyp){
        case 1:
          val=testVal;
          break;
        case 2:
          rotateR=testVal;
          pidPitchRate.setGainsK(rotateR/100.0, 0.0, 0.0);
          pidRollRate.setGainsK(rotateR/100.0, 0.0, 0.0);
          break;
        case 3:
          rateA=testVal;
          pidPitch.setGainsK(rateA/10.0, 0.0, 0.0);
          pidRoll.setGainsK(rateA/10.0, 0.0, 0.0);
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
  Serial1.print(val);
  Serial1.print(",");
  Serial1.print(rotateR);
  Serial1.print(",");
  Serial1.print(rateA);
  Serial1.print(",");
  Serial1.println(typ);
}
