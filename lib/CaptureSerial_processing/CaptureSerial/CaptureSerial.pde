import processing.serial.*;

PrintWriter output;
Serial udSerial;

Button button;
void setup() {
  size(80, 26);
  button = new Button(0, 0, "Parar Captura");
  udSerial = new Serial(this, Serial.list()[0], 9600);
  output = createWriter ("log/"+year()+"-"+month()+"-"+day()+"_"+hour()+"-"+minute()+"-SERIAL.log");
  surface.setTitle("Captura Log");
}
void draw() {
  background(250);
  button.draw();
  if (udSerial.available() > 0) {
    String SenVal = udSerial.readStringUntil('\n');
    if (SenVal != null) {
      output.print(SenVal);
    }
  }
  output.flush();
}
void mousePressed() {
  if (button.over()) {
    output.flush();
    output.close();
    exit();
  }
}
class Button {
  int x, y;
  String label;
  Button(int x, int y, String label) {
    this.x = x;
    this.y = y;
    this.label = label;
  }
  void draw() {
    fill(200);
    if (over()) {
      fill(255);
    }
    rect(x, y, textWidth(label), 25);
    fill(0);
    text(label, x+2, y + 20);
  }
  boolean over() {
    if (mouseX >= x && mouseY >= y && mouseX <= x + textWidth(label) && mouseY <= y + 22) {
      return true;
    }
    return false;
  }
}