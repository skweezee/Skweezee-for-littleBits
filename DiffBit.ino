float window[5] = {0,0,0,0,0};
int w[5] = {-1,8,0,-8,1};

void setup() {
  Serial.begin(9600); // baud rate 9600 bps
}

void loop() {
  float valPreviousBit = analogRead(PC1)>>2;
  float result = 0;

  window[0] = window[1];
  window[1] = window[2];
  window[2] = window[3];
  window[3] = window[4];
  window[4] = valPreviousBit;

  //Using five-point stencil
  if(window[4] != 0) {
    float sum = w[0]*window[0];
    sum += w[1]*window[1];
    sum += w[3]*window[3];
    sum += w[4]*window[4];
    result = sum/12;
  }

  delay(10);
  
  analogWrite(PD5, result);
}
