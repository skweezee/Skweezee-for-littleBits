float window[5] = {0,0,0,0,0};

void setup() {
  Serial.begin(9600); // baud rate 9600 bps
}

void loop() {
  float valPreviousBit = analogRead(PC1)>>2;

  window[0] = window[1];
  window[1] = window[2];
  window[2] = window[3];
  window[3] = window[4];
  window[4] = valPreviousBit;

  //Do processing
  float sum = 0;
  
  for(int i = 0; i < 5; i++) {
    sum += window[i];
  }

  int result = sum/5;

  delay(10);
  
  analogWrite(PD5, result);
}
