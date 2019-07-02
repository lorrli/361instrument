#include "MIDIUSB.h"

const int sP1 = A15;
int RawVal1 = 0, onDelay = 50;
float vVal1 = 0;
float res1 = 0;

const int channel = 1;
const int velocity = 99;

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

  //  midiEventPacket_t noteOff = {0x08, 0x80 | channel, note, velocity};
  //  MidiUSB.sendMIDI(noteOff);

  if (RawVal1 > maxVal || RawVal1 < increment) {
    Serial.print("OFF");
    Serial.println();
    usbMIDI.sendNoteOff(lastnote, velocity, channel);
    usbMIDI.sendNoteOff(note, velocity, channel);
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
    //    midiEventPacket_t noteOn = {0x09, 0x90 | channel, note, velocity};
    //    MidiUSB.sendMIDI(noteOn);
   usbMIDI.sendNoteOn(note, velocity, channel);
   usbMIDI.sendNoteOff(lastnote, velocity, channel);
  }
  
  lastnote = note;
  Serial.println();
  delay(onDelay);
}
