#include <Adafruit_NeoPixel.h>

#define PIN 3

#define NUM_LEDS 7

#define BRIGHTNESS 50

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);

int RedVal[45] = {255, 238, 221, 204, 187, 170, 153, 136, 119, 102, 85, 68, 51, 34, 17, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 17, 34, 51, 68, 85, 102, 119, 136, 153, 170, 187, 204, 221, 238};
int GreenVal[45] = {0, 17, 34, 51, 68, 85, 102, 119, 136, 153, 170, 187, 204, 221, 238, 255, 238, 221, 204, 187, 170, 153, 136, 119, 102, 85, 68, 51, 34, 17, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int BlueVal[45] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 17, 34, 51, 68, 85, 102, 119, 136, 153, 170, 187, 204, 221, 238, 255, 238, 221, 204, 187, 170, 153, 136, 119, 102, 85, 68, 51, 34, 17};
int light = analogRead(1);
int scaleVal = 1;
int readSkip = 1;

void setup() {
  pixels.begin();
  Serial.begin(9600);
}

void loop() {
  light = analogRead(1);
  Serial.println(light);

  if (digitalRead(4) == LOW) {
    Serial.println("Ayyy  ");
    if (scaleVal == 4) {
      readSkip = 15;
      scaleVal = 1;
    }
    else if (scaleVal == 3) {
      readSkip = 5;
      scaleVal = 4;
    }
    else if (scaleVal == 2) {
      readSkip = 3;
      scaleVal = 3;
    }
    else if (scaleVal == 1) {
      readSkip = 1;
      scaleVal = 2;
    }
    Serial.print("scaleVal:  ");  Serial.print('\t'); Serial.println(scaleVal);
    Serial.print("readSkip:  ");  Serial.print('\t'); Serial.println(readSkip);
    delay(100);
  }
  if (light < 850) {
    Serial.println("Lights On!");
    for (int i = 0; i < NUM_LEDS; i++) {
      int val = i * readSkip;
      pixels.setPixelColor(i, pixels.Color(RedVal[val], GreenVal[val], BlueVal[val]));
      pixels.show();
      delay(10);
    }
delay(20);
  }
  else {
    for (int i = 0; i < NUM_LEDS; i++) {
      pixels.setPixelColor(i, pixels.Color(0,0,0));
      pixels.show();
      delay(10);
    }
  }
  int LastRed = RedVal[44];
  int LastGreen = GreenVal[44];
  int LastBlue = BlueVal[44];

  for (int x = 44; x > -1; x--) {
    RedVal[x] = RedVal[x - 1];
    GreenVal[x] = GreenVal[x - 1];
    BlueVal[x] = BlueVal[x - 1];
  }
  RedVal[0] = LastRed ;
  GreenVal[0] = LastGreen;
  BlueVal[0] = LastBlue;


  /*  for (int n = 0; n < 45; n++) {
     Serial.print(RedVal[n]); Serial.print('\t');
      Serial.print(GreenVal[n]); Serial.print('\t');
      Serial.print(BlueVal[n]);  Serial.println('\t');
    }*/


}
