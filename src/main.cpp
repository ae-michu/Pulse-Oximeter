#include <Arduino.h>
#include <display.h>
#include <sensor.h>

// #define DEBUG                    // uncomment to enable writing data to monitor

#define BUTTON1         5           // pin number of first button (bpm)
#define BUTTON2         6           // pin number of second button (o2)

#define DISPLAY_DC      8           // pin number od display dc pin
#define DISPLAY_CS      10          // pin number of display cs pin
#define DISPLAY_RESET   9           // pin number of display reset pin

// init display and sensor objects
Display display(U8G2_R0, DISPLAY_CS, DISPLAY_DC, DISPLAY_RESET);
Sensor sensor;

// set global variables
bool screen = false;              // false - bpm screen, true - o2 screen
bool changeScreenFlag = true;     // false when screen change should occur
int lastBpm = 0;                  // store last bpm value
int lastO2 = 0;                   // store last o2 value

void setup() {

  #ifdef DEBUG
    Serial.begin(115200);
  #endif

  // set buttons as inputs
  pinMode(BUTTON1, INPUT);
  pinMode(BUTTON2, INPUT);

  // start display and clear it
  display.begin();
  display.clearDisplay();

  display.startAnimation();      // display splash animation

  display.clearDisplay();
  sensor.init();                // start sensor
}

void loop() {
  // detect if button was pressed, if so then set screen flag corresponding to button pressed
  // and set changeScreenFlag to signalize that screen change should occur 
  if (!digitalRead(BUTTON1)) {
    if (screen) {
      screen = false;
      changeScreenFlag = true;
    }
  }

  if (!digitalRead(BUTTON2)) {
    if (!screen) {
      screen = true;
      changeScreenFlag = true;
    }
  }

  // change screens when changeScreenFlag is set, and reset the flag
  if (changeScreenFlag) {
    changeScreenFlag = false;

    display.firstPage();
    do {
      if (!screen) {
        display.drawBPMScreen();
        display.drawBPMValue(0);
      } else {
        display.drawO2Screen();
      }
    } while (display.nextPage());
  }

  #ifdef DEBUG
    float bpmData = sensor.getBPMData();
    float o2Data = sensor.getO2Data();
  #endif

  #ifndef DEBUG
    sensor.getBPMData();
    sensor.getO2Data();
  #endif

  // display values based on selected screen
  if (!screen) {
    float bpm = sensor.getBPM();

    if (((int)bpm != lastBpm) && ((int)bpm != NAN)) {
      lastBpm = (int)bpm;

      display.firstPage();
      do {
        display.drawBPMScreen();
        display.drawBPMValue((int)bpm);
      } while (display.nextPage());
    }

    #ifdef DEBUG
      Serial.print("bpmData: ");
      Serial.print(bpmData);
      Serial.print(", bpm: ");
      Serial.println(bpm);
    #endif
  } else {
    float o2 = sensor.getO2();

    if (((int)o2 != lastO2) && ((int)o2 >= 0)) {
      lastO2 = (int)o2;

      display.firstPage();
      do {
        display.drawO2Screen();
        display.drawO2Value((int)o2);
      } while (display.nextPage());
    }

    #ifdef DEBUG
      Serial.print("o2Data: ");
      Serial.print(o2Data);
      Serial.print(", o2: ");
      Serial.println(o2);
    #endif
  }

  delay(10);
}