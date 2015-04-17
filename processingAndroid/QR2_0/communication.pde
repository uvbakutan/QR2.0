//Call back method to manage data received
void onBluetoothDataEvent(String who, byte[] data){
  String [] temp;
  float batteryTemp = 0;
  readMessage = new String(data, 0, data.length);
  
  if(readMessage!=null){
     temp=split(readMessage,',');
     if(temp!=null&&temp.length>1)
        try{
         batteryTemp = Float.parseFloat(temp[1]);
         if(batteryTemp>6.0 && batteryTemp<8.5)
           battery = batteryTemp;
         }
        catch(NumberFormatException e){}
     
  }  
}

void sendData(){
  if(j1.valueXChanged())
     writeValue(j1.getXvalue(),2);
  if(j1.valueYChanged())
    writeValue(j1.getYvalue(),1);
    
  if(j2.valueXChanged())
    writeValue(j2.getXvalue(),4);
  if(j2.valueYChanged())
    writeValue(j2.getYvalue(),3);
}

void writeValue(int data, int type){
  byte [] btData = new byte [4];
  btData[0] = (byte)0xc5; // start
  btData[1] = (byte)(type >> 0); // type of data
  btData[2] = (byte)(data >> 0); // byte of data
  btData[3] = (byte)0x5c; // end
  bt.broadcast(btData);
  println("printing data "+ data);
}

