class slider {
  String    sName;
  int       sWidth;              // width of bar
  float     xPos, yPos;          // x and y position of bar
  float     sPos, newsPos;       // x position of slider
  float     sPosMin, sPosMax;    // max and min values of slider
  float     circleR, circleOr;   // inner and outer circle diameter
  int       dC;                  // damping coefficient
  boolean   over;                // is the mouse over the slider?
  boolean   locked;              // captures the new position for the slider
  color     backgroundColor;     // background color for the slider
  color     sliderActivColor;    
  color     sliderInactivColor;  
  PFont     font;                

  slider (String sn, float xp, float yp, int sw, int dc) {
    sName = sn;
    sWidth = sw;
    xPos = xp;
    yPos = yp;
    sPos = xPos + sWidth/2;
    newsPos = sPos;
    sPosMin = xPos;
    sPosMax = xPos + sWidth;
    circleR=10;
    circleOr=25;
    dC = dc;
    backgroundColor =255;
    sliderActivColor = #009688;
    sliderInactivColor = #bdbdbd;
    font = createFont("Calibri", 5, true); 
  }

  void update() {
    if (overEvent()) 
      over = true;
    else
      over = false;
    
    if (mousePressed && over)
      locked = true;
    
    if (!mousePressed) 
      locked = false;
    
    if (locked){
      if(mouseX<xPos)
        newsPos=xPos;
      else if(mouseX>xPos+sWidth)
        newsPos=xPos+sWidth;
      else
        newsPos = mouseX;
    }
        
   if(abs(newsPos-sPos)>1)         //because it would be stuck at 0.9999
    sPos = sPos + (newsPos-sPos)/dC;
   else
    sPos=newsPos;
  }

  boolean overEvent() {
    if (mouseX > xPos-10 && mouseX < xPos+sWidth+10 &&
       mouseY > yPos-10 && mouseY < yPos+10) {
      return true;
    } 
    else 
      return false;
  }
  
  int getPrecent() {
    return int(((sPos-xPos)/sWidth) * 100);
  }

  void display() {
    
    this.update();   
    
    noStroke();
    textAlign(CENTER);
    fill(backgroundColor);
    rect(xPos-circleOr/2,yPos-circleOr,sWidth+circleOr+10,2*circleOr+3);
    
    fill(sliderInactivColor);
    rect(xPos, yPos-1, sWidth,2);

    text("0", xPos,yPos+circleOr); 
    text(sWidth, xPos+sWidth,yPos+circleOr);
    
    fill(sliderActivColor);
    rect(xPos, yPos-1, sPos-xPos,2);
    
    text(sName, xPos,yPos-circleOr/2-3);    
    text(int(sPos-xPos), xPos+sWidth/2,yPos+circleOr);

    

    
    if (over) {
      text(getPrecent()+"%", xPos+sWidth,yPos-circleOr/2-3);
      
      if (locked){      
        fill(sliderActivColor);
        ellipse(sPos, yPos, circleR+4,circleR+4);
      }
      else{
        fill(sliderActivColor,70);
        ellipse(sPos, yPos, circleOr,circleOr);
      }
    }
    fill(sliderActivColor); 
    ellipse(sPos, yPos, circleR,circleR);
  }
}
