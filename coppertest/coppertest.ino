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

elapsedMillis timer = 0;

/*
touchedA is a 16 bit unsigned integers, with the state of the 12 pins of 
the cap-touch board represented as the binary bits of that integer.
That is, either as a 0 for "not-touched" or a 1 for "touched". 

For example:
  If pin 0 was touched, and pin 1 to pin 11 were not touched, then the variable 
  touchedA would be:
  0000 0000 0000 0001 which is equal to the decimal value 2^0 = 1

  If pin 0, pin 3, pin 7 were touched, and all other pins were not touched, then the variable 
  touchedA would be:
  0000 0000 1000 1001 which is equal to the decimal value 2^0 + 2^3 + 2^7 = 1 + 8 + 128 = 137

  Later in the code we'll look at the individual bits to determine the states of each pin
  on the cap-touch board.
*/

// the MIDI channel to send messages on
int channel = 1;

// Notes played for each cap touch board
// these are identifed using the standard MIDI note numbers
// Middle C is note 60

// We only have 7 touch pads...we also don't use pin 0, so start at pin 1
// These correspond to pins:
              // 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11
int notesA[] = { 0, 55, 57,59,62,66,76, 0,0, 0, 0, 0};
//int notesA[] = { 0, 36,48,52,55,60, 64, 0,0, 0, 0, 0}; //this is the mapping for a C chord

// Some common scale intervals
//dorian       = "2,1,2,2,2,1,2"
//phrygian     = "1,2,2,2,1,2,2"
//lydian       = "2,2,2,1,2,2,1"
//mixolydian   = "2,2,1,2,2,1,2"
//aeolian      = "2,1,2,2,1,2,2"
//locrian      = "1,2,2,1,2,2,2"

// The velocity you want to play the note with (value from 0-127)
int vel = 120;

// Set up integers to store the state of the potentiometer values
int currPotValue = 0;
int prevPotValue = 0;
int CCpot = 90; // Send CC values from the potentiometer on CC channel 90
int CCcap = 91; // Send CC values from the capacitor on CC channel 91
//
////////our stuff
const int VolumePin = A16;
const int sP1 = A15;
const int openNote = 48;
int velocity[] = {50, 90, 127}; // three volume ranges 
int volumeIndex = 0;
int SensorReading = 0; 
int currNote = openNote;
const int distance = 50;
int RawVal1, notestep = 0;
const int cycle=50;
const int intervals[]={0,4,7,12,16,19};
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
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  
}

// the main loop
void loop() {
  //Serial.println(notestep);
  // Get the currently touched pads
  currstateA = capA.touched();
  Serial.println(currstateA);
  getNote();
  // Check the state of the cap-touch board and turn on/off notes as needed
  checkCap();
  prevstateA = currstateA;
}

// Function to check the cap-touch board and send turn on/off notes as needed
void checkCap(){
  //Serial.println("checkCap");
  // Loop through the 12 touch points on the board
  // We use pin 0 for cap touch CC later, so skip that one and start at n = 1
  for(int n = 1; n <7; n++){
  
    // Compare the current state to the previous state
    // If it has changed you need to do something
    if(bitRead(currstateA,n) ==1 && bitRead(prevstateA,n) != 1){
      
      // If it has changed and is TRUE, then turn on that note
     
        // Send out a MIDI message on both usbMIDI and hardware MIDI ports
        
        usbMIDI.sendNoteOn(currNote + intervals[n-1],velocity[volumeIndex],channel);
        Serial.print("playing:"); 
        Serial.println(currNote);

    }
  }
    delay(cycle);
  
    usbMIDI.sendNoteOff(currNote,0,channel); 
    usbMIDI.sendNoteOff(currNote + 4,0,channel); 
    usbMIDI.sendNoteOff(currNote + 7,0,channel); 
    usbMIDI.sendNoteOff(currNote + 12,0,channel); 
    usbMIDI.sendNoteOff(currNote + 16,0,channel); 
    usbMIDI.sendNoteOff(currNote + 19,0,channel); 

  
}


void getNote(){
  //read linear pot for note value
  RawVal1 = analogRead(sP1);
  SensorReading = analogRead(VolumePin); 
  volumeIndex = map(SensorReading, 0, 900, 0, 2);
  Serial.print("Volume: ");
  Serial.println(volumeIndex);
  Serial.println(RawVal1);
  if (RawVal1 >=200 && RawVal1 <=800){
//    notestep = (RawVal1 - 100)/distance;
//    currNote = openNote + notestep;
    currNote = constrain(map(RawVal1, 200, 800, 49, 80),49,80);
  }else{
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
