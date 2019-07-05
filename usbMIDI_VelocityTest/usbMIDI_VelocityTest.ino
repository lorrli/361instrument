const int C = 60;
int velocity = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.print("Velocity: ");
  Serial.print(velocity);
  usbMIDI.sendNoteOn(67,velocity,1);
  delay(1000);
  usbMIDI.sendNoteOff(67,velocity,1);
  delay(1000);
  velocity = velocity + 10;
}
