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
const int sP1 = A15;
const int butt1 = A9;
int RawVal1 = 0, cycle = 200;
const int C = 60;
const int distance = 50;
void setup() {
  // Set MIDI baud rate:
  Serial1.begin(31250);
  Serial1.begin(9600);
  //Serial1.begin(9600);
  pinMode(sP1, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  pinMode(butt1, INPUT);
}
int lastnote = 0, note = 0, notestep = 0;
int lastButt1State = 0, butt1State = 0;
void loop() {
  RawVal1 = analogRead(sP1);
  notestep = (RawVal1 - distance)/distance;
  Serial.print(" Linpot: ");
  Serial.print(RawVal1);
  Serial.print(" notestep:: ");
  Serial.println(notestep);
  note = C + notestep -1; 
  butt1State = digitalRead(butt1);
  
  if(butt1State == HIGH){
    //Serial.print("   Note: ");
    //Serial.println(note);
    //usbMIDI.sendNoteOn(note,99,1);
    if(notestep < 18 && notestep > 0 && lastButt1State != 1){
      usbMIDI.sendNoteOn(note,99,1);
      Serial.println("Playing a note");
    }
  }
  //lastnote = note;
  lastButt1State = butt1State;
  Serial.print("Last Button state:");
  Serial.print(lastButt1State);
  delay(cycle);
}

// plays a MIDI note. Doesn't check to see that cmd is greater than 127, or that
// data values are less than 127:
void noteOn(int cmd, int pitch, int velocity) {
  Serial1.write(cmd);
  Serial1.write(pitch);
  Serial1.write(velocity);
  
}
