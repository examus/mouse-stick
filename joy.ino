// Thumb Joystick example
// Mike Grusin, SparkFun Electronics 3/11
// This code is free, baby. Use it however you like.

// This sketch shows the basic operation of the Thumb Joystick (COM-09032) and breakout board (BOB-09110).
// The joystick outputs two analog voltages (VERT and HORIZ), and one digital signal (SEL) for the pushbutton.

// Connections to joystick (change if you use different pins):

const int VERT = 0; // analog
const int HORIZ = 1; // analog
const int SEL = 2; // digital
const double K = 0.05;
const int Xzero = 500;
const int Yzero = 507;

const int ClickDelay = 10;
int clickd = 0;
int cstate = 0;
// Also connect the joystick VCC to Arduino 5V, and joystick GND to Arduino GND.

// This sketch outputs serial data at 9600 baud (open Serial Monitor to view).

struct {
    uint8_t buttons;
    int8_t x;
    int8_t y;
    int8_t wheel;   /* Not yet implemented */
} mouseReport;

uint8_t nullReport[4] = { 0, 0, 0, 0 };

void setup()
{
  // make the SEL line an input
  pinMode(SEL,INPUT);
  // turn on the pull-up resistor for the SEL line (see http://arduino.cc/en/Tutorial/DigitalPins)
  digitalWrite(SEL,HIGH);

  // set up serial port for output
  Serial.begin(9600);
}

void loop()
{
  int vertical, horizontal, select;
  
  vertical = analogRead(VERT); // will be 0-1023
  horizontal = analogRead(HORIZ); // will be 0-1023
  select = digitalRead(SEL); // will be HIGH (1) if not pressed, and LOW (0) if pressed
  
  mouseReport.x = (horizontal-Xzero)*K;
  mouseReport.y = -(vertical-Yzero)*K;

  mouseReport.buttons = cstate;
  if (clickd == 0) {
    if(select == LOW) {
      if (cstate == 0) {
          clickd = ClickDelay;   
      }
      mouseReport.buttons = 1;
      cstate = 1;
    } else {
      if (cstate == 1) {
          clickd = ClickDelay;   
      }
      mouseReport.buttons = 0;
      cstate = 0;
    }
  } else {
    clickd--;
  }

  Serial.write((uint8_t *)&mouseReport, 4);
  Serial.write((uint8_t *)&nullReport, 4);
  
}  
