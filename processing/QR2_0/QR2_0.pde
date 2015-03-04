import processing.serial.*;
boolean enableSerial=false;
Serial myPort;  // Create object from Serial class
final String serialPort = "COM16"; // replace this with your serial port

float [] YPR = new float[] {0,0,0}; // Yaw Pitch Roll angles

slider s1,s2,s3;
String s;

void setup(){
  size(800,400,OPENGL);
  background(255);
  s1 = new slider( "motorSpeed",100, 100, 255, 7);
  s2 = new slider( "rotateK",100, 190, 100, 7);
  s3 = new slider( "angleK",100, 280, 100, 7);
  
  if(enableSerial)
    myPort = new Serial(this, serialPort,115200);
}

void draw(){
  background(255);
  s1.display();
  s2.display();
  s3.display();


  if(enableSerial && myPort.available()>10)
    readValue();
    
    
  drawCube(radians(YPR[2]),radians(-YPR[0]),radians(YPR[1]));
    
 if (frameCount % 5 == 0 && enableSerial) {
    thread("sendData");
  }
}

void sendData(){
  if(s1.valueChanged())
    writeValue(s1.getValue(),1);
  if(s2.valueChanged())
    writeValue(s2.getValue(),2);
  if(s3.valueChanged())
    writeValue(s3.getValue(),3);
}
