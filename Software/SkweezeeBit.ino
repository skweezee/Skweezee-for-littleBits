// first define the functions of the digital I/O pins
// the following pins control the multiplexers (enable and select)
#define EN 11
#define S_A0 8
#define S_A1 9
#define S_A2 10

float valPreviousBit = 0;
float val = 0; // variable to store the value read
float raw[5]; // set of raw values in one sensing cycle

void setup() {
  Serial.begin(9600); // baud rate 9600 bps
  pinMode(EN, OUTPUT);
  pinMode(S_A0, OUTPUT);
  pinMode(S_A1, OUTPUT);
  pinMode(S_A2, OUTPUT);
  TCCR2B = (TCCR2B & 0b11111000) | 0x03;
}

void loop() {
  int rawIndex = 0;
  
  // Enable the multiplexer
  digitalWrite(EN, HIGH);
  
  // Loop through all the relevant combinations of the multiplexers
  for (int i = 0; i<5; i++) {
    digitalWrite(S_A2, bitRead(i,2) );
    digitalWrite(S_A1, bitRead(i,1) );
    digitalWrite(S_A0, bitRead(i,0) );
    
    delayMicroseconds(30); // time needed to go from L to H
    val = analogRead(PC0)>>2;
    valPreviousBit = analogRead(PC1)>>2;
        
    raw[rawIndex] = val;
    rawIndex++;
  }

  // Now disable the multiplexer (not really necessary)
  digitalWrite(EN, LOW);
  delay(10);

  makeSignal();
  
}

void makeSignal() {
  float blue = float(raw[1]+raw[2])/2/255;
  float yellow = float(raw[0])/255;
  float red = float(raw[3]+raw[4])/2/255;

  blue = 255-(blue*valPreviousBit);
  yellow = 255-(yellow*valPreviousBit);
  red = 255-(red*valPreviousBit);

  analogWrite(PD6, blue); //Links
  analogWrite(PD5, yellow); //Midden
  analogWrite(PD3, red); //Rechts
}
