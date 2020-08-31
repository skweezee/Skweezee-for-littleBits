typedef struct {
    double r;       // a fraction between 0 and 1
    double g;       // a fraction between 0 and 1
    double b;       // a fraction between 0 and 1
} rgb;

typedef struct {
    double h;       // angle in degrees
    double s;       // a fraction between 0 and 1
    double v;       // a fraction between 0 and 1
} hsv;

static hsv   rgb2hsv(rgb in);
static rgb   hsv2rgb(hsv in);

void setup() {
  Serial.begin(9600); // baud rate 9600 bps
  TCCR2B = (TCCR2B & 0b11111000) | 0x03;
}

void loop() {
  int valHue = analogRead(PC0)>>2;
  int valSaturation = analogRead(PC1)>>2;
  int valValue = analogRead(PC2)>>2;
        
  //Do processing
  hsv input;
  input.h = double(valHue);
  input.s = double(valSaturation) / 255;
  input.v = double(valValue) / 255;
  rgb result = hsv2rgb(input);
  
  delay(10);

  analogWrite(9, (result.b*255)); 
  analogWrite(10, (result.g*255));
  analogWrite(11, (result.r*255));
  analogWrite(PD6, valHue);
  analogWrite(PD5, valSaturation);
  analogWrite(PD3, valValue);
}

//Code voor de omzetting van HSV(B) naar RGB:
//https://stackoverflow.com/questions/3018313/algorithm-to-convert-rgb-to-hsv-and-hsv-to-rgb-in-range-0-255-for-both
rgb hsv2rgb(hsv in)
{
    double      hh, p, q, t, ff;
    long        i;
    rgb         out;

    if(in.s <= 0.0) {       // < is bogus, just shuts up warnings
        out.r = in.v;
        out.g = in.v;
        out.b = in.v;
        return out;
    }
    hh = in.h;
    if(hh >= 360.0) hh = 0.0;
    hh /= 60.0;
    i = (long)hh;
    ff = hh - i;
    p = in.v * (1.0 - in.s);
    q = in.v * (1.0 - (in.s * ff));
    t = in.v * (1.0 - (in.s * (1.0 - ff)));

    switch(i) {
    case 0:
        out.r = in.v;
        out.g = t;
        out.b = p;
        break;
    case 1:
        out.r = q;
        out.g = in.v;
        out.b = p;
        break;
    case 2:
        out.r = p;
        out.g = in.v;
        out.b = t;
        break;

    case 3:
        out.r = p;
        out.g = q;
        out.b = in.v;
        break;
    case 4:
        out.r = t;
        out.g = p;
        out.b = in.v;
        break;
    case 5:
    default:
        out.r = in.v;
        out.g = p;
        out.b = q;
        break;
    }
    return out;     
}
