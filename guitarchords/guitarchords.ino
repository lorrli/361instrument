//A script written to use an MPR121 cap-touch board and a Teensy 3.2 board as a MIDI device
// In the Arduino Tools/USB-type menu select "MIDI" when programming the board
// This script will play different notes as you touch each cap-touch pin
// It also uses a pad as a capacitive potentiometer to send CC
// Make sure to program your Teensy 3.2 in MIDI mode

// You need to include two libraries:
// the I2C "Wire.h" library,
// the Adafruit MPR121 Cap-touch Board "Adafruit_MPR121.h" library

#include <Wire.h>
#include "Adafruit_MPR121.h"

// Define Analog Input
#define pot1 A0

// Create the cap-touch board variables
// You can have up to 4 boards on one I2C bus (because there are 4 different board addresses)
Adafruit_MPR121 capA = Adafruit_MPR121();

// use unsigned integers in binary format to represent the state of touched pins

// current and previous state of the system
uint16_t currstateA = 0;
uint16_t prevstateA = 0;

// Create variables for the pressure sesnsing pad
uint16_t currcap = 0;
uint16_t prevcap = 0;

// the MIDI channel to send messages on
int channel = 1;

// Notes played for each cap touch board
// these are identifed using the standard MIDI note numbers
// Middle C is note 60

// We only have 7 touch pads...we also don't use pin 0, so start at pin 1
// These correspond to pins:
// 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11

// Some common scale intervals
//dorian       = "2,1,2,2,2,1,2"
//phrygian     = "1,2,2,2,1,2,2"
//lydian       = "2,2,2,1,2,2,1"
//mixolydian   = "2,2,1,2,2,1,2"
//aeolian      = "2,1,2,2,1,2,2"
//locrian      = "1,2,2,1,2,2,2"

// The velocity you want to play the note with (value from 0-127)
int vel = 120;

////////our stuff
const int VolumePin = A16;
const int sP1 = A15;
const int MUTE_PIN = A17;
const int openNote = 0;

int velocity[] = {50, 90, 127}; // three volume ranges
int volumeIndex = 0;
int noteVolume = 0;
int SensorReading = 0;
int currNote = openNote;
const int distance = 50;
int fretReading, notestep = 0;
const int cycle = 50;
const int intervals[] = {0, 4, 7, 12, 16, 19};
int muteReading = 0;
const int MUTE_THRESHOLD = 200;


/////////chord note stuff
int chordType = 0;
int chords[][12][6] =
  //major
{ //major
                {{48,48,52,55,60, 64},
                {41,49,53,56,61,65},
                {45,50,57,62,66,69},
                {46,51,58,63,67,70},
                {40,47,52,56,59,64},
                {41,48,53,57,60,65},
                {42,49,54,58,61,66},
                {43,47,50,55,59,66},
                {44,51,56,60,63,68},
                {40,45,52,57,61,64},
                {42,47,54,59,63,66},
                {41,46,53,58,62,65}},
                //minor
                {{43,48,55,60,63,67},
                {44,49,56,61,64,68},
                {45,50,57,62,65,69},
                {46,51,58,63,66,70},
                {40,47,52,55,59,64},
                {41,48,53,56,60,65},
                {42,49,54,57,61,66},
                {43,50,55,58,62,67},
                {44,51,56,59,63,68},
                {40,45,52,57,60,64},
                {41,46,53,58,61,65}, 
                {42,47,54,59,62,66}}
};
// Setup loop that intitiates the I2C hardware and the hardware MIDI
void setup() {
  Serial.begin(9600);
  // start the "A" cap-touch board - 0x5A is the I2C address
  capA.begin(0x5A);
  if (!capA.begin(0x5A)) {
    Serial.println("MPR121 not found, check wiring?");
    while (1);
  }
  pinMode(VolumePin, INPUT);
  pinMode(sP1, INPUT);
  pinMode(MUTE_PIN, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
}

// the main loop
void loop() {

  //Serial.println(notestep);
  // Get the currently touched pads
  currstateA = capA.touched();
  Serial.println(currstateA);
  if(analogRead(MUTE_PIN) < MUTE_THRESHOLD){
    usbMIDI.sendControlChange(7,0,channel);
  }else{
    usbMIDI.sendControlChange(7,noteVolume,channel);
    getNote();
  // Check the state of the cap-touch board and turn on/off notes as needed
    checkCap();
    prevstateA = currstateA;
  }
}

// Function to check the cap-touch board and send turn on/off notes as needed
void checkCap() {
  //Serial.println("checkCap");
  // Loop through the 12 touch points on the board
  // We use pin 0 for cap touch CC later, so skip that one and start at n = 1
  for (int n = 1; n < 7; n++) {

    // Compare the current state to the previous state
    // If it has changed you need to do something
    if (bitRead(currstateA, n) == 1 && bitRead(prevstateA, n) != 1) {

      // If it has changed and is TRUE, then turn on that note

      // Send out a MIDI message on both usbMIDI and hardware MIDI ports
      //chords[0-major,1-minor][base chord note][stringpressed]
      usbMIDI.sendNoteOn(chords[chordType][currNote][n - 1], noteVolume, channel);
      Serial.print("playing:");
      Serial.println(chords[chordType][currNote][n - 1]);

    }
  }
  delay(cycle);
  for (int n = 1; n < 7; n++) {

    // Compare the current state to the previous state
    // If it has changed you need to do something

    // If it has changed and is TRUE, then turn on that note

    // Send out a MIDI message on both usbMIDI and hardware MIDI ports
    //chords[0-major,1-minor][base chord note][stringpressed]
    usbMIDI.sendNoteOff(chords[chordType][currNote][n - 1], 0, channel);
  }
}


void getNote() {
  //read linear pot for note value
  fretReading = analogRead(sP1);
  SensorReading = analogRead(VolumePin);
  //volumeIndex = map(SensorReading, 0, 1024, 0, 2);
  noteVolume = map(SensorReading, 0, 1024, 30, 127);
  Serial.print("Volume: ");
  Serial.println(noteVolume);
  Serial.println(fretReading);
  if (fretReading >= 200 && fretReading <= 800) {
    //    notestep = (RawVal1 - 100)/distance;
    //    currNote = openNote + notestep;
    currNote = constrain(map(fretReading, 200, 800, 1, 11), 1, 11);
  } else {
    currNote = openNote;
  }
  Serial.print(currNote);
}
/*********************************************************
  This is a library for the MPR121 12-channel Capacitive touch sensor

  Designed specifically to work with the MPR121 Breakout in the Adafruit shop
  ----> https://www.adafruit.com/products/

  These sensors use I2C communicate, at least 2 pins are required
  to interface

  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
**********************************************************/
