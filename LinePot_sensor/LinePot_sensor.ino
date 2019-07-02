const int sP1 = A15;
int RawVal1 = 0, onDelay = 200;
float vVal1 = 0;
float res1 = 0;

const int channel = 1;
const int dChannel = 2;
const int eChannel = 3;
const int fChannel = 4;
const int gChannel = 5;
const int aChannel = 6;
const int bChannel = 7;
const int highCChannel = 8;

int note = 0;
int lastnote = 0;

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
int maxVal = increment * 9;

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
  Serial.print("lastnote = ");
  Serial.println(lastnote);
  //  Serial.print("\t Voltage 1 = ");
  //  Serial.println(vVal1);
  //  Serial.print("\t Resistance 1 = ");
  //  Serial.println(res1);
    usbMIDI.sendNoteOff(c, velocity, channel);
    usbMIDI.sendNoteOff(d, velocity, channel);
    usbMIDI.sendNoteOff(e, velocity, channel);
    usbMIDI.sendNoteOff(f, velocity, channel);
    usbMIDI.sendNoteOff(g, velocity, channel);
    usbMIDI.sendNoteOff(a, velocity, channel);
    usbMIDI.sendNoteOff(b, velocity, channel);
    usbMIDI.sendNoteOff(highc, velocity, channel);


  if (RawVal1 > maxVal || RawVal1 < increment) {
    Serial.print("OFF");
    Serial.println();

  }
  else if (RawVal1 > increment & RawVal1 < increment * 2) {
    note = c;
  }
  else if (RawVal1 > increment * 2 & RawVal1 < increment * 3) {
    note = d;
  }
  else if (RawVal1 > increment * 3 & RawVal1 < increment * 4) {
    note = e;
  }
  else if (RawVal1 > increment * 4 & RawVal1 < increment * 5) {
    note = f;
  }
  else if (RawVal1 > increment * 5 & RawVal1 < increment * 6) {
    note = g;
  }
  else if (RawVal1 > increment * 6 & RawVal1 < increment * 7) {
    note = a;
  }
  else if (RawVal1 > increment * 7 & RawVal1 < increment * 8) {
    note = b;
  }
  else if (RawVal1 > increment * 8 & RawVal1 < increment * 9) {
    note = highc;
  }

  if (note != lastnote) {
    usbMIDI.sendNoteOn(note, velocity, channel);
  }
  lastnote = note;
  Serial.println();
  delay(onDelay);
}
