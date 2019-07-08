const int sP1 = A14;
int RawVal1 = 0, onDelay = 50;
float vVal1 = 0;
float res1 = 0;


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

}
