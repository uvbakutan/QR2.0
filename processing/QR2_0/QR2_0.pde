slider s1,s2,s3;

void setup(){
  size(600,400);
  background(255);
  s1 = new slider( "test",width/2-100, height/2-100, 200, 7);
  s2 = new slider( "test1",width/2-100, height/2+0, 50, 7);
  s3 = new slider( "test2",width/2-100, height/2+100, 300, 7);
}

void draw(){
  s1.display();
  s2.display();
  s3.display();
}
