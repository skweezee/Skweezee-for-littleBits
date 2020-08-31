int recording [3] = {1024,1024,1024};
bool pressed = false;

void setup() {
    Serial.begin(9600); // baud rate 9600 bps
    pinMode(PD2, INPUT);
    pinMode(PD5, OUTPUT);
}

void loop() {
  
  int left = analogRead(PC0);
  int center = analogRead(PC1);
  int right = analogRead(PC2);

  //Butten pressed -> pressed = true
  if(digitalRead(PD2) == HIGH)
  {
    pressed = true;
  }
  
  //Do processing
  if(pressed == true) {
    recording[0] = left;
    recording[1] = center;
    recording[2] = right;

    delay(10);
    digitalWrite(PD5, LOW);
    pressed = false;
  }
  else if((left < recording[0]+75) && (left > recording[0]-75) && (center < recording[1]+75) && (center > recording[1]-75) && (right < recording[2]+75) && (right > recording[2]-75)) 
  {
    delay(10);
    digitalWrite(PD5, HIGH);
  }
  else
  {
    delay(10);
    digitalWrite(PD5, LOW);
  }
}
