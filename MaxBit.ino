float maximum = 0;

void setup() {
    Serial.begin(9600); // baud rate 9600 bps
}

void loop() {
  float valPreviousBit = analogRead(PC1)>>2;
  float result = 0;

  //Do processing
  if(valPreviousBit > maximum) {
    maximum = valPreviousBit;
  }
  
  if(maximum != 0) result = maximum;
  
  delay(10);

  analogWrite(PD5, result);
}
