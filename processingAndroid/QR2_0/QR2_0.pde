import android.view.MotionEvent;

int TouchEvents;
float xTouch[];
float yTouch[];
int currentPointerId = 0;
boolean printFPS;


joystick j1,j2;


void setup() {
  size(displayWidth, displayHeight);
  orientation(LANDSCAPE);
  textAlign(CENTER);
  background(255);

  xTouch = new float[2];
  yTouch = new float[2]; // Don't use more than ten fingers!
  
  j1 = new joystick(200, 350, 1, true);
  j2 = new joystick(displayWidth - 200, 350, 1, false);

}

//-----------------------------------------------------------------------------------------

void draw() {
  background(255);
  
  j1.display();
  j2.display();
  
  //println(actionMask);
}

//-----------------------------------------------------------------------------------------

public boolean surfaceTouchEvent(MotionEvent event) {
  int actionMask;
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
