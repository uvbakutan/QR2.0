class joystick {
  float     xLocation, yLocation;  // lostacion of joystick
  float     xPos, yPos;            // x and y position of joystick
  float     xPrevious, yPrevious;  // x and y position of joystick
  float     xNewPos,yNewPos;       // x and y new position
  float     posMax;                // max distance for joystick
  float     circleR, circleEr;     // inner and outer circle diameter
  int       dC;                    // damping coefficient
  boolean   over;                  // is the mouse over the joystick?
  boolean   mode;                  // changes mode for flying
  color     backgroundColor;       // background color for the slider
  color     joystickColor,edgeColor;
  PFont     font;

  joystick (float xL, float yL,int dc, boolean md) {
    xLocation = xL;
    yLocation = yL;

    posMax = 255;
    circleR = 100;
    circleEr = 255; 
    dC = dc;
    over=false;
    mode = md;
    backgroundColor = 255;
    joystickColor = #009688;
    edgeColor = #bdbdbd;
    
    xPos = xL;
    yPos = (mode)? yL+circleEr/2:yL;
    xNewPos = xPos;
    yNewPos = yPos;
    xPrevious = xPos;
    yPrevious = yPos;
    
    font = createFont("Calibri", 5, true); 
  }

  void update() {
    isOverEvent();
    
    xPrevious = xPos;
    yPrevious = yPos;
        
    if(abs(xNewPos-xPos)>0.2 || abs(xNewPos-xPos)>0.2 ){
      xPos = xPos + (xNewPos-xPos)/dC;
      yPos = yPos + (yNewPos-yPos)/dC;
    }
    else{
      xPos = xNewPos;
      yPos = yNewPos;
    }
 }
 
void isOverEvent() {
boolean over = false ;
  for (int i = 0; i < 2; i++) 
    if (dist(xTouch[i],yTouch[i],xLocation,yLocation)<circleEr/2+25) {     // is it inside the edge
      xNewPos = xTouch[i];
      yNewPos = yTouch[i];
      over = true;
    }
    
    if(!over){
      xNewPos=xLocation;
      if(!mode)
        yNewPos=yLocation;
    }
}
  
 //  int getPrecent() {
 //   return int(((sPos-xPos)/sWidth) * 100);
 // }
  
 int getYvalue() {
   if(mode)
     return constrain((int)map(yPos,yLocation-circleEr/2,yLocation+circleEr/2,150,0),0,150);
   else
     return constrain((int)map(yPos,yLocation-circleEr/2,yLocation+circleEr/2,20,0),0,20);
  }
  
 int getXvalue() {
     return constrain((int)map(xPos,xLocation-circleEr/2,xLocation+circleEr/2,20,0),0,20);
  }
  
  boolean valueXChanged(){
    return (abs(xPos-xPrevious))>0;
  }
  
  boolean valueYChanged(){
    return (abs(yPos-yPrevious))>0;
  }

  void display() {
    
    this.update(); 
    

    stroke(edgeColor);
    strokeWeight(2);
    if(mode){
      line(xLocation - circleEr/2-25, yLocation, xLocation + circleEr/2+25, yLocation);
      fill(backgroundColor);
      ellipse(xLocation,yLocation,circleEr,circleEr);
      line(xLocation, yLocation - circleEr/2-25, xLocation , yLocation + circleEr/2+25);
    }
    else{
      line(xLocation - (circleEr/2+30)*0.7071, yLocation - (circleEr/2+30)*0.7071, xLocation + (circleEr/2+30)*0.7071,yLocation + (circleEr/2+30)*0.7071);
      line(xLocation - (circleEr/2+30)*0.7071, yLocation + (circleEr/2+30)*0.7071, xLocation + (circleEr/2+30)*0.7071,yLocation - (circleEr/2+30)*0.7071);
      fill(backgroundColor);
      ellipse(xLocation,yLocation,circleEr,circleEr);
    }
    
    fill(joystickColor);
    noStroke();
    ellipse(xPos, yPos, circleR,circleR);
    
    textAlign(CENTER);
    
    if(mode){
      text("motorSpeed "+getYvalue(), xLocation+circleEr/2+45,yLocation-25);
      text("yaw "+ (getXvalue()-10), xLocation+circleEr/2+25,yLocation+25);
    }
    else{
      text("roll "+ (getYvalue()-10), xLocation-circleEr/2-25,yLocation-25);
      text("pitch "+ (getXvalue()-10), xLocation-circleEr/2-25,yLocation+25);
    }
      
    
      
    //   if (locked){      
    //     fill(sliderActivColor);
    //     ellipse(sPos, yPos, circleR+4,circleR+4);
    //   }
    //   else{
    //     fill(sliderActivColor,70);
    //     ellipse(sPos, yPos, circleOr,circleOr);
    //   }
    // }
    // fill(sliderActivColor); 
    // ellipse(sPos, yPos, circleR,circleR);
  }
} 
