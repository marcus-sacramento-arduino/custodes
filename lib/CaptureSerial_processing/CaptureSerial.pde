import processing.serial.*;

PrintWriter output;
Serial udSerial;

float x = 0;
float y = 0;
float w = 200;
float h = 50;


void setup() {
  udSerial = new Serial(this, Serial.list()[0], 9600);
  output = createWriter ("Serial_Custodes.log");
  frame.setTitle("Captura Log");
  size(200, 50);
  background(200);
  stroke(0);
  noFill();
}

void draw() {

  rect(x, y, w, h);
  fill(255);
  String s = "The quick brown fox jumped over the lazy dog.";
  if (mousePressed) {
    if (mouseX>x && mouseX <x+w && mouseY>y && mouseY <y+h) {
      fill(0);
      output.flush();
      output.close();
      exit();
    }
  }
  if (udSerial.available() > 0) {
    String SenVal = udSerial.readStringUntil('\n'); // readString();
    if (SenVal != null) {
      output.print(SenVal);
    }
  }
  output.flush();
}
