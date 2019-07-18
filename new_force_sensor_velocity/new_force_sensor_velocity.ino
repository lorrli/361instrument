int SensorPin = A16; //analog pin 0
int velocity[] = {50, 90, 127};

void setup(){
  Serial.begin(9600);
}

 

void loop(){
  int SensorReading = analogRead(SensorPin); 
  int mfsr_r18 = map(SensorReading, 0, 900, 0, 2);
  Serial.println(mfsr_r18);

  Serial.println(SensorReading);
  usbMIDI.sendNoteOn(60,velocity[mfsr_r18],1); 
  delay(100); 
  usbMIDI.sendNoteOff(60,velocity[mfsr_r18],1); 
  delay(100); 
}
