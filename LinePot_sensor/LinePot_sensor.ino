const int sP1 = A15;
int RawVal1 = 0, onDelay = 200;
float vVal1 = 0;
float res1 = 0;
int maxVal = 1023;

const int cChannel = 1;
const int dChannel = 2;
const int eChannel = 3;
const int fChannel = 4;
const int gChannel = 5;
const int aChannel = 6;
const int bChannel = 7;
const int highCChannel = 8;

const int c = 60;
const int d = 62;
const int e = 64;
const int f = 65;
const int g = 67;
const int a = 69;
const int b = 71;
const int highc = 72;
int velocity = 99;
int increment = 100;

void setup() {
  Serial.begin(9600);
  pinMode(sP1, INPUT);
}

void loop() {
  RawVal1 = analogRead(sP1);
  vVal1 = (RawVal1 * 5.0) / 1024.0;
  res1 = 5000.0 * (RawVal1 / 2024.0);
  Serial.print("Raw Value 1 = ");
  Serial.println(RawVal1);
  //  Serial.print("\t Voltage 1 = ");
  //  Serial.println(vVal1);
  //  Serial.print("\t Resistance 1 = ");
  //  Serial.println(res1);

  if (RawVal1 > maxVal) {
    Serial.print("OFF");
    Serial.println();
    usbMIDI.sendNoteOff(c, velocity, cChannel);
    usbMIDI.sendNoteOff(d, velocity, dChannel);
    usbMIDI.sendNoteOff(e, velocity, eChannel);
    usbMIDI.sendNoteOff(f, velocity, fChannel);
    usbMIDI.sendNoteOff(g, velocity, gChannel);
    usbMIDI.sendNoteOff(a, velocity, aChannel);
    usbMIDI.sendNoteOff(b, velocity, bChannel);
    usbMIDI.sendNoteOff(highc, velocity, highCChannel);
  }
  else if (RawVal1 > 0 & RawVal1 < increment) {
    usbMIDI.sendNoteOn(c, velocity, cChannel);
    usbMIDI.sendNoteOff(d, velocity, dChannel);
    usbMIDI.sendNoteOff(e, velocity, eChannel);
    usbMIDI.sendNoteOff(f, velocity, fChannel);
    usbMIDI.sendNoteOff(g, velocity, gChannel);
    usbMIDI.sendNoteOff(a, velocity, aChannel);
    usbMIDI.sendNoteOff(b, velocity, bChannel);
    usbMIDI.sendNoteOff(highc, velocity, highCChannel);
  }
  else if (RawVal1 > increment & RawVal1 < increment * 2) {
    usbMIDI.sendNoteOn(d, velocity, dChannel);
    usbMIDI.sendNoteOff(c, velocity, cChannel);
    usbMIDI.sendNoteOff(e, velocity, eChannel);
    usbMIDI.sendNoteOff(f, velocity, fChannel);
    usbMIDI.sendNoteOff(g, velocity, gChannel);
    usbMIDI.sendNoteOff(a, velocity, aChannel);
    usbMIDI.sendNoteOff(b, velocity, bChannel);
    usbMIDI.sendNoteOff(highc, velocity, highCChannel);
  }
  else if (RawVal1 > increment * 2 & RawVal1 < increment * 4) {
    usbMIDI.sendNoteOn(e, velocity, eChannel);
    usbMIDI.sendNoteOff(d, velocity, dChannel);
    usbMIDI.sendNoteOff(c, velocity, cChannel);
    usbMIDI.sendNoteOff(f, velocity, fChannel);
    usbMIDI.sendNoteOff(g, velocity, gChannel);
    usbMIDI.sendNoteOff(a, velocity, aChannel);
    usbMIDI.sendNoteOff(b, velocity, bChannel);
    usbMIDI.sendNoteOff(highc, velocity, highCChannel);
  }
  else if (RawVal1 > increment * 6 & RawVal1 < increment * 8) {
    usbMIDI.sendNoteOn(f, velocity, fChannel);
    usbMIDI.sendNoteOff(d, velocity, dChannel);
    usbMIDI.sendNoteOff(e, velocity, dChannel);
    usbMIDI.sendNoteOff(c, velocity, cChannel);
    usbMIDI.sendNoteOff(g, velocity, gChannel);
    usbMIDI.sendNoteOff(a, velocity, aChannel);
    usbMIDI.sendNoteOff(b, velocity, bChannel);
    usbMIDI.sendNoteOff(highc, velocity, highCChannel);
  }
  else if (RawVal1 > increment * 8 & RawVal1 < increment * 10) {
    usbMIDI.sendNoteOn(g, velocity, gChannel);
    usbMIDI.sendNoteOff(d, velocity, dChannel);
    usbMIDI.sendNoteOff(e, velocity, eChannel);
    usbMIDI.sendNoteOff(f, velocity, fChannel);
    usbMIDI.sendNoteOff(c, velocity, cChannel);
    usbMIDI.sendNoteOff(a, velocity, aChannel);
    usbMIDI.sendNoteOff(b, velocity, bChannel);
    usbMIDI.sendNoteOff(highc, velocity, highCChannel);
  }
  else if (RawVal1 > increment * 10 & RawVal1 < increment * 12) {
    usbMIDI.sendNoteOff(g, velocity, gChannel);
    usbMIDI.sendNoteOff(d, velocity, dChannel);
    usbMIDI.sendNoteOff(e, velocity, eChannel);
    usbMIDI.sendNoteOff(f, velocity, fChannel);
    usbMIDI.sendNoteOff(c, velocity, cChannel);
    usbMIDI.sendNoteOn(a, velocity, aChannel);
    usbMIDI.sendNoteOff(b, velocity, bChannel);
    usbMIDI.sendNoteOff(highc, velocity, highCChannel);
  }
  else if (RawVal1 > increment * 12 & RawVal1 < increment * 14) {
    usbMIDI.sendNoteOff(g, velocity, gChannel);
    usbMIDI.sendNoteOff(d, velocity, dChannel);
    usbMIDI.sendNoteOff(e, velocity, eChannel);
    usbMIDI.sendNoteOff(f, velocity, fChannel);
    usbMIDI.sendNoteOff(c, velocity, cChannel);
    usbMIDI.sendNoteOff(a, velocity, aChannel);
    usbMIDI.sendNoteOn(b, velocity, bChannel);
    usbMIDI.sendNoteOff(highc, velocity, highCChannel);
  }
  else if (RawVal1 > increment * 14 & RawVal1 < increment * 16) {
    usbMIDI.sendNoteOff(g, velocity, gChannel);
    usbMIDI.sendNoteOff(d, velocity, dChannel);
    usbMIDI.sendNoteOff(e, velocity, eChannel);
    usbMIDI.sendNoteOff(f, velocity, fChannel);
    usbMIDI.sendNoteOff(c, velocity, cChannel);
    usbMIDI.sendNoteOff(a, velocity, aChannel);
    usbMIDI.sendNoteOff(b, velocity, bChannel);
    usbMIDI.sendNoteOn(highc, velocity, highCChannel);
  }
  Serial.println();
//  delay(onDelay);



}
