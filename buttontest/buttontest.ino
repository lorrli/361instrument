/*
  MIDI note player

  This sketch shows how to use the serial transmit pin (pin 1) to send MIDI note data.
  If this circuit is connected to a MIDI synth, it will play the notes
  F#-0 (0x1E) to F#-5 (0x5A) in sequence.

  The circuit:
  - digital in 1 connected to MIDI jack pin 5
  - MIDI jack pin 2 connected to ground
  - MIDI jack pin 4 connected to +5V through 220 ohm resistor
  - Attach a MIDI cable to the jack, then to a MIDI synth, and play music.

  created 13 Jun 2006
  modified 13 Aug 2012
  by Tom Igoe

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Midi
*/


const int linPot = A16; // Change this value to prototype: Slide = A14 , Rotate = A16
const int sP1 = A15;
int volumeVal = 0;
const int butt1 = A9, butt2 = A8, butt3 = A7, butt4 = A6, butt5 = A3;
int RawVal1 = 0, cycle = 50;
const int C = 60;
const int distance = 50;
void setup() {
  // Set MIDI baud rate:
  //Serial1.begin(31250);
  Serial1.begin(9600);
  //Serial1.begin(9600);
  pinMode(linPot, INPUT);
  pinMode(sP1, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  pinMode(butt1, INPUT);
  pinMode(butt2, INPUT);
  pinMode(butt3, INPUT);
  pinMode(butt4, INPUT);
  pinMode(butt5, INPUT);

}
int lastnote = 0, note = 0, notestep = 0;
int lastButt1State = 0, butt1State = 0;
int lastButt2State = 0, butt2State = 0;
int lastButt3State = 0, butt3State = 0;
int lastButt4State = 0, butt4State = 0;
int lastButt5State = 0, butt5State = 0;


void loop() {
  RawVal1 = analogRead(sP1);
  notestep = (RawVal1 - distance)/distance;
  volumeVal = analogRead(linPot) / 8;
  Serial.print(" Linpot: ");
  Serial.print(RawVal1);
  Serial.print(" notestep:: ");
  Serial.println(notestep);
  Serial.print(" volume:: ");
  Serial.println(volumeVal);
  note = C + notestep -1; 
  butt1State = digitalRead(butt1);
  butt2State = digitalRead(butt2);
  butt3State = digitalRead(butt3);
  butt4State = digitalRead(butt4);
  butt5State = digitalRead(butt5);

  if(butt1State == HIGH){
    //Serial.print("   Note: ");
    //Serial.println(note);
    //usbMIDI.sendNoteOn(note,99,1);
    if(notestep < 18 && notestep > 0 && lastButt1State != 1){
      usbMIDI.sendNoteOn(note,volumeVal,1);
      Serial.println("Playing a note");
    }
  }
  if(butt2State == HIGH){
    //Serial.print("   Note: ");
    //Serial.println(note);
    //usbMIDI.sendNoteOn(note,99,1);
    if(notestep < 18 && notestep > 0 && lastButt2State != 1){
      usbMIDI.sendNoteOn(note+4,volumeVal,1);
      Serial.println("Playing a note");
    }
  }
  if(butt3State == HIGH){
    //Serial.print("   Note: ");
    //Serial.println(note);
    //usbMIDI.sendNoteOn(note,99,1);
    if(notestep < 18 && notestep > 0 && lastButt3State != 1){
      usbMIDI.sendNoteOn(note+7,volumeVal,1);
      Serial.println("Playing a note");
    }
  }
  if(butt4State == HIGH){
    //Serial.print("   Note: ");
    //Serial.println(note);
    //usbMIDI.sendNoteOn(note,99,1);
    if(notestep < 18 && notestep > 0 && lastButt4State != 1){
      usbMIDI.sendNoteOn(note+12,volumeVal,1);
      Serial.println("Playing a note");
    }
  }
  if(butt5State == HIGH){
    //Serial.print("   Note: ");
    //Serial.println(note);
    //usbMIDI.sendNoteOn(note,99,1);
    if(notestep < 18 && notestep > 0 && lastButt5State != 1){
      usbMIDI.sendNoteOn(note+16,volumeVal,1);
      Serial.println("Playing a note");
    }
  }
  //lastnote = note;
  lastButt1State = butt1State;
  lastButt2State = butt2State;
  lastButt3State = butt3State;
  lastButt4State = butt4State;
  lastButt5State = butt5State;

  Serial.print("Last Button1 state:");
  Serial.println(lastButt1State);
  Serial.print("Last Button2 state:");
  Serial.println(lastButt2State);
  Serial.print("Last Button3 state:");
  Serial.println(lastButt3State);
  Serial.print("Last Button4 state:");
  Serial.println(lastButt4State);
  Serial.print("Last Button5 state:");
  Serial.println(lastButt5State);
  delay(cycle);
}
