void readValue(){
  String [] temp;
  s=myPort.readString();
  //println(s);
  if(s!=null){
      temp=split(s,',');
     if(temp!=null&&temp.length>3){
      for(int i=1; i<4;i++){
        try{
         YPR[i-1] = Float.parseFloat(temp[i]);
         }
        catch(NumberFormatException e){}
      }
      if(temp.length>4)
        println(temp[4]);  
     }
  }  

}

void writeValue(int data, int type){
  myPort.write(0xc5); // start
  myPort.write(type); // type of data
  myPort.write(data); // byte of data
  myPort.write(0x5c); // end
  println("printing data "+ data);
}
