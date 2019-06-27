/*
   created by Rui Santos, https://randomnerdtutorials.com

   Complete Guide for Ultrasonic Sensor HC-SR04

    Ultrasonic sensor Pins:
        VCC: +5VDC
        Trig : Trigger (INPUT) - Pin11
        Echo: Echo (OUTPUT) - Pin 12
        GND: GND
*/
int readTest = 0;
int ledPin = 13;
int trigPin = 10;    // Trigger
int echoPin = 11;    // Echo
long duration, cm, inches;
const int channel = 1; // Defines the MIDI channel to send messages on (values from 1-16)
int velocity = 99; // Defines the velocity that the note plays at (values from 0-127)
int initialInch = 17;

const int cChannel = 1;
const int dChannel = 2;
const int eChannel = 3;
const int fChannel = 4;
const int gChannel = 5;

const int c = 60;
const int d = 62;
const int e = 64;
const int f = 65;
const int g = 67;

void setup() {
  //Serial Port begin
  Serial.begin (9600);
  //Define inputs and outputs
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(readTest, INPUT);
}

void loop() {
  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(ledPin, HIGH);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  digitalWrite(ledPin, LOW);

  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);

  // Convert the time into a distance
  cm = (duration / 2) / 29.1;   // Divide by 29.1 or multiply by 0.0343
  inches = (duration / 2) / 74; // Divide by 74 or multiply by 0.0135

  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();

  if (inches > initialInch+10) {
    Serial.print("OFF");
    Serial.println();
    usbMIDI.sendNoteOff(c, velocity, cChannel);
    usbMIDI.sendNoteOff(d, velocity, dChannel);
    usbMIDI.sendNoteOff(e, velocity, eChannel);
    usbMIDI.sendNoteOff(f, velocity, fChannel);
    usbMIDI.sendNoteOff(g, velocity, gChannel);
  }
  else if (inches > initialInch & inches < initialInch + 2) {
    usbMIDI.sendNoteOn(c, velocity, cChannel);
    usbMIDI.sendNoteOff(d, velocity, dChannel);
    usbMIDI.sendNoteOff(e, velocity, eChannel);
    usbMIDI.sendNoteOff(f, velocity, fChannel);
    usbMIDI.sendNoteOff(g, velocity, gChannel);
  }
  else if (inches > initialInch + 2 & inches < initialInch + 4) {
    usbMIDI.sendNoteOn(d, velocity, dChannel);
    usbMIDI.sendNoteOff(c, velocity, cChannel);
    usbMIDI.sendNoteOff(e, velocity, eChannel);
    usbMIDI.sendNoteOff(f, velocity, fChannel);
    usbMIDI.sendNoteOff(g, velocity, gChannel);
  }
  else if (inches > initialInch + 4 & inches < initialInch + 6) {
    usbMIDI.sendNoteOn(e, velocity, eChannel);
    usbMIDI.sendNoteOff(d, velocity, dChannel);
    usbMIDI.sendNoteOff(c, velocity, cChannel);
    usbMIDI.sendNoteOff(f, velocity, fChannel);
    usbMIDI.sendNoteOff(g, velocity, gChannel);
  }
  else if (inches > initialInch + 6 & inches < initialInch + 8) {
    usbMIDI.sendNoteOn(f, velocity, fChannel);
    usbMIDI.sendNoteOff(d, velocity, dChannel);
    usbMIDI.sendNoteOff(e, velocity, dChannel);
    usbMIDI.sendNoteOff(c, velocity, cChannel);
    usbMIDI.sendNoteOff(g, velocity, gChannel);
  }
  else if (inches > initialInch + 8 & inches < initialInch + 10) {
    usbMIDI.sendNoteOn(g, velocity, gChannel);
    usbMIDI.sendNoteOff(d, velocity, dChannel);
    usbMIDI.sendNoteOff(e, velocity, eChannel);
    usbMIDI.sendNoteOff(f, velocity, fChannel);
    usbMIDI.sendNoteOff(c, velocity, cChannel);
  }

  delay(100);
}
