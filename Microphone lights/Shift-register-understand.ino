/*
  Circuit:

          LED  D12       D11
      5V   0   MISO GND  MOSI  D9  5V
      |    |    |    |    |    |    |    |
   |--|----|----|----|----|----|----|----|--|
   |  VCC  Q0   DS  OE  ST_CP SH_CP MR  Q7' |
   |                                        |
   |  Q1   Q2   Q3  Q4    Q5   Q6   Q7  GND |
   |--|----|----|----|----|----|----|----|--|
      |    |    |    |    |    |    |    |
     LED  LED  LED  LED  LED  LED  LED  GND
      1    2    3    4    5    6    7
*/
int tDelay   = 100;
int dataPin  = 12;      //    DS - data serial on 74HC595
int latchPin = 11;      // ST_CP - storage register clock pin on 74HC595
int clockPin = 9;       // SH_CP - shift register clock pin on 74HC595 - Why not D13 SCK pin?

bool DirectionState = 0;

byte leds;

//---------------------------------INIT MIC-------------------------------------------
int micPin = A0;          // pin that the mic is attached to
int gndPin = A1;
int powerPin = A2;
int micValue1 = 0;
int micValue2 = 0; // the Microphone value
int led1 = 13;
boolean lightOn = false;

//-------------------------------------end--------------------------------------------

void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin,  OUTPUT);
  pinMode(clockPin, OUTPUT);

  //-------------------MIC---------------------
  pinMode(led1, OUTPUT);
  pinMode(powerPin, OUTPUT);
  pinMode(gndPin, OUTPUT);
  pinMode(micPin, INPUT);
  digitalWrite(gndPin, LOW);
  delay(500);
  digitalWrite(powerPin, HIGH);
  Serial.begin(9600);
  //-------------------end---------------------
}


void loop() {
  //--------------------------------MIC---------------------------------
  micValue1 = (analogRead(micPin) - 501); // read pin value
  Serial.println(micValue1);
  //--------------------------------end--------------------------------
  if (micValue1 <= 0) {
    leds = 0B00000000;
    updateShiftRegister(leds);
    //delay(tDelay);
  } else if (micValue1 > 0 && micValue1 <= 1) {
    leds = 0B10000000;
    updateShiftRegister(leds);
  } else if (micValue1 > 1 && micValue1 <= 2) {
    leds = 0B11000000;
    updateShiftRegister(leds);
  } else if (micValue1 > 2 && micValue1 <= 3) {
    leds = 0B11100000;
    updateShiftRegister(leds);
  } else if (micValue1 > 3 && micValue1 <= 4) {
    leds = 0B11110000;
    updateShiftRegister(leds);
  } else if (micValue1 > 4 && micValue1 <= 5) {
    leds = 0B11111000;
    updateShiftRegister(leds);
  } else if (micValue1 > 5 && micValue1 <= 6) {
    leds = 0B11111100;
    updateShiftRegister(leds);
  } else if (micValue1 > 6 && micValue1 <= 7) {
    leds = 0B11111110;
    updateShiftRegister(leds);
  } else if (micValue1 > 7 && micValue1 <= 8) {
    leds = 0B11111111;
    updateShiftRegister(leds);
  }

}
void updateShiftRegister(byte leds) {
  digitalWrite(latchPin, LOW);
  if (DirectionState == false) {
    shiftOut(dataPin, clockPin, LSBFIRST, leds);
  } else {
    shiftOut(dataPin, clockPin, MSBFIRST, leds);
  }
  digitalWrite(latchPin, HIGH);
}
