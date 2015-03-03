import processing.serial.*;
boolean enableSerial=false;
Serial myPort;  // Create object from Serial class
final String serialPort = "COM16"; // replace this with your serial port

float [] YPR = new float[] {0,0,0}; // Yaw Pitch Roll angles

slider s1;
String s;

void setup(){
  size(600,400,OPENGL);
  background(255);
  s1 = new slider( "motorSpeed",width/2-100, height/2-100, 255, 7);
  
  if(enableSerial)
    myPort = new Serial(this, serialPort,115200);
}

void draw(){
  background(255);
  s1.display();


  if(enableSerial && myPort.available()>10)
    readValue();
    
    
  drawCube(radians(YPR[2]),radians(-YPR[0]),radians(YPR[1]));
    
 if (frameCount % 5 == 0 && enableSerial) {
    thread("sendData");
  }
}

void sendData(){
  writeValue(s1.getValue(),int(s1.getValue()>158));
}
