// A basic Sketch to send MIDI messages using the USB MIDI protocol
// You need to have installed TEENSYDUINO,
// https://www.pjrc.com/teensy/td_download.html (don't forget the udev rules link at the
// top of the page for LINUX people)..., selected Tools/Board/Teensy 3.5
// and Tools/USB Type/MIDI for this to program (if you're using the Teensy 3.5)
// When you select USB Type/MIDI it automatically includes the USB MIDI libraries
// See https://www.pjrc.com/teensy/td_midi.html for more MIDI commands you can use
// Use a program like https://www.snoize.com/MIDIMonitor/ to monitor your MIDI communication
// bus to see if what you're sending is actually working

const int channel = 1; // Defines the MIDI channel to send messages on (values from 1-16)
int velocity = 99; // Defines the velocity that the note plays at (values from 0-127)
int ledPin = 13;


void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin, OUTPUT);
}

void loop() {
    randNote();
}

void randNote() {
  //  int note = random(0,12);
  for (int i = 0; i <= 8 ; i = i + 2) {
    usbMIDI.sendNoteOn(60 + i, velocity, channel); // Turn a note on!
    digitalWrite(ledPin, HIGH);
    delay(500);
    usbMIDI.sendNoteOff(60 + i, velocity, channel); // Make sure to turn it off!
    digitalWrite(ledPin, LOW);
    
//    delay(500);
    if (i == 4 ) {
      i--;
    }
  }
}
