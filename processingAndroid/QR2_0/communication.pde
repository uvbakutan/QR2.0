void writeValue(int data, int type){
  byte [] btData = new byte [4];
  btData[0] = (byte)0xc5; // start
  btData[1] = (byte)(type >> 0); // type of data
  btData[2] = (byte)(data >> 0); // byte of data
  btData[3] = (byte)0x5c; // end
  bt.broadcast(btData);
  println("printing data "+ data);
}

