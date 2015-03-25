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
    
    if(endT==0x5c && (testTyp>0 && testTyp<4) && (testVal>=0 && testVal <= 255) ){
      typ=testTyp;
      switch(testTyp){
        case 1:
          val=testVal;
          break;
        case 2:
          desiredPitch=(testVal-10)*2;
          break;
        case 3:
          desiredRoll=(testVal-10)*2;
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
  Serial1.print(float(bat*0.009765625));
  Serial1.print(",");
  Serial1.print(val);
  Serial1.print(",");
  Serial1.print(desiredPitch);
  Serial1.print(",");
  Serial1.print(desiredRoll);
  Serial1.print(",");
  Serial1.println(typ);
}
