import android.view.MotionEvent;

//required for BT enabling on startup
import android.content.Intent;
import android.os.Bundle;

import ketai.net.bluetooth.*;
import ketai.net.*;

KetaiBluetooth bt;
ArrayList<String> devicesDiscovered = new ArrayList();

boolean connectPressed = false; // for the button
boolean connected = false; // for the button
boolean discovered = false; // for the button
int actionMask;


//********************************************************************
// The following code is required to enable bluetooth at startup.
//********************************************************************
void onCreate(Bundle savedInstanceState) {
  super.onCreate(savedInstanceState);
  bt = new KetaiBluetooth(this);
}

void onActivityResult(int requestCode, int resultCode, Intent data) {
  bt.onActivityResult(requestCode, resultCode, data);
}

//********************************************************************



boolean foundDevice=false; //When true, the screen turns green.
boolean BTisConnected=false; //When true, the screen turns purple.
String readMessage;



int TouchEvents;
float xTouch[];
float yTouch[];
int currentPointerId = 0;
PFont fontD;


joystick j1,j2;


void setup() {
  size(displayWidth, displayHeight);
  orientation(LANDSCAPE);
  background(255);
  noStroke();

  xTouch = new float[2];
  yTouch = new float[2]; // Don't use more than ten fingers!
  
  j1 = new joystick(200, 350, 3, true);
  j2 = new joystick(displayWidth - 200, 350, 3, false);
  
  fontD = createFont("Calibri", 5, true); 
  
  bt.start();          //start listening for BT connections
}

//-----------------------------------------------------------------------------------------

void draw() {
  
  devicesDiscovered = bt.getDiscoveredDeviceNames();

  background(255);
  displayText();
  displayButton();
  j1.display();
  j2.display();
  
  //println(actionMask);
  
  if (frameCount % 5 == 0 && connected)
   sendData();

}

//-----------------------------------------------------------------------------------------

public boolean surfaceTouchEvent(MotionEvent event) {
  int actionIndex;

  // Number of places on the screen being touched:
  TouchEvents = event.getPointerCount();
  if(TouchEvents <3){

    // If no action is happening, listen for new events else 
    for (int i = 0; i < TouchEvents; i++) {
      int pointerId = event.getPointerId(i);
      xTouch[pointerId] = event.getX(i); 
      yTouch[pointerId] = event.getY(i);
      float siz = event.getSize(i);
    }
  
    actionMask = event.getActionMasked();
    actionIndex = event.getActionIndex();
  
    // ACTION_DOWN 
    if ( actionMask == 0 ) {
      print("Initial action detected. (ACTION_DOWN)");
      print("Action index: " +str(actionIndex));
    } 
    // ACTION_UP 
    else if ( actionMask == 1) {
      print("ACTION_UP");
      print("Action index: " +str(actionIndex));
    }
    //  ACTION_POINTER_DOWN 
    else if ( actionMask == 5) {
      print("Secondary pointer detected: ACTION_POINTER_DOWN");
      print("Action index: " +str(actionIndex));
    }
    // ACTION_POINTER_UP 
    else if ( actionMask == 6) {
      print("ACTION_POINTER_UP");
      print("Action index: " +str(actionIndex));

    }
    
    if(actionMask == 1 || actionMask == 6){                      // if finger is lifted the position is 0,0
      xTouch[event.getPointerId(actionIndex)] = 0.0;                  
      yTouch[event.getPointerId(actionIndex)] = 0.0;
    }

  }
  else{
  //text crazy
  }

  // If you want the variables for motionX/motionY, mouseX/mouseY etc.
  // to work properly, you'll need to call super.surfaceTouchEvent().
  return super.surfaceTouchEvent(event);
}

//Call back method to manage data received
void onBluetoothDataEvent(String who, byte[] data){
  
  readMessage = new String(data, 0, data.length);
}


void displayText(){
  textAlign(LEFT);
  text("found bluetooth device: ",50,60);
  for (int i=0; i < devicesDiscovered.size(); i++)
        text("["+i+"] "+devicesDiscovered.get(i).toString(),50,80+i*20);

  // if(BTisConnected)
  //   text("connected succesfully to" + discoveredDeviceName, 50,80);
   text("from arduino  "+readMessage, 300, 40);
}

void displayButton(){
    for (int i = 0; i < 2; i++) 
      if(dist(xTouch[i],yTouch[i],displayWidth/2,100)<80/2 && ( actionMask == 5 ||  actionMask == 0)){
        connectPressed=!connectPressed;
        // if(!connected && !connectPressed)
        //       bt.discoverDevices();
      }
      
    for (int i = 0; i < 2; i++) 
      if(dist(xTouch[i],yTouch[i],displayWidth/2,220)<80/2 && ( actionMask == 5 ||  actionMask == 0)){
         bt.discoverDevices();
      }
        
  if(connectPressed && !connected){
    if(devicesDiscovered.size()>0){
      bt.connectToDeviceByName("Bakatanio8");
      connected = true;
    }
  }
  // if(!connectPressed && connected){     
  //   bt.stop();
  //   bt.start();
  //   devicesDiscovered.clear();
  //   connected = false;
  // }
  
  
  fill((connectPressed)?#009688:#bdbdbd);
  ellipse(displayWidth/2,100,80,80);
  textAlign(CENTER,CENTER);
  fill(255);
  textSize(30);
  text("C",displayWidth/2,100);
  textSize(13);
  
  fill((devicesDiscovered.size()>0)?#009688:#bdbdbd);
  ellipse(displayWidth/2,220,80,80);
  textAlign(CENTER,CENTER);
  fill(255);
  textSize(30);
  text("D",displayWidth/2,220);
  textSize(13);

}

void sendData(){
  // if(j1.valueXChanged())
  //   writeValue(j1.getXvalue(),1);
  if(j1.valueYChanged())
    writeValue(j1.getYvalue(),1);
    
  if(j2.valueXChanged())
    writeValue(j2.getXvalue(),3);
  if(j2.valueYChanged())
    writeValue(j2.getYvalue(),2);
}
