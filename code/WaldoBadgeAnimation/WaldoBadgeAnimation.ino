#include <Bounce2.h>

#include "display.h"
#include "animations.h"

#define DISPLAY_INTERVAL_US 500
#define ANIMATION_INTERVAL_MS 100

uint32_t beacon_prevMillis = 0;
uint32_t display_prevMicros = 0;
uint32_t animation_prevMillis = 0;

Bounce debouncer0 = Bounce();
Bounce debouncer1 = Bounce();
Bounce debouncer2 = Bounce();
Bounce debouncer3 = Bounce();

void setup() {
  // put your setup code here, to run once:
  display_init();

  // button inputs
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);

  debouncer0.attach(A0);
  debouncer0.interval(5);

  debouncer1.attach(A1);
  debouncer1.interval(5);

  debouncer2.attach(A2);
  debouncer2.interval(5);

  debouncer3.attach(A3);
  debouncer3.interval(5);
}

void loop() {
  // put your main code here, to run repeatedly:

  static uint8_t animationNumber = 1;
  static uint8_t animationCountdown = 0;
  static uint8_t animationFrameNumber = 0;

  uint8_t buttonChangeFlag = 0;

  uint8_t newAnimationNumber = 0;
  uint8_t newAnimationFrameNumber = 0;

  debouncer0.update();
  debouncer1.update();
  debouncer2.update();
  debouncer3.update();

  if(debouncer0.read() == LOW) {
    newAnimationFrameNumber = 0;
    newAnimationNumber = 1;
  } else if(debouncer1.read() == LOW) {
    newAnimationFrameNumber = 0;
    newAnimationNumber = 5;
  } else if(debouncer2.read() == LOW) {
    newAnimationFrameNumber = 0;
    newAnimationNumber = 6;
  } else if(debouncer3.read() == LOW) {
    newAnimationFrameNumber = 0;
    newAnimationNumber = 9;
  } else {
    buttonChangeFlag = 0;
  }

  if(buttonChangeFlag == 0) {
    if(newAnimationNumber != 0) {
      animationNumber = newAnimationNumber;
      animationFrameNumber = newAnimationFrameNumber;
      buttonChangeFlag = 1;
    }
  }

  uint32_t currentMillis = millis();
  uint32_t currentMicros = micros();
  
  if(currentMicros - display_prevMicros > DISPLAY_INTERVAL_US) {
    display_prevMicros = currentMicros;
    display_update();
  }

  if(currentMillis - animation_prevMillis > ANIMATION_INTERVAL_MS) {
    animation_prevMillis = currentMillis;

    if(animationNumber == 0) {
      display_setFrame(0x00UL);
    } else {
      // run an animation
      display_setFrame(doAnimation(animationNumber, &animationFrameNumber));

      // timeout the animation
      animationCountdown--;
      if(animationCountdown == 0) {
        //animationNumber = 0;
        tone(13, 400, 500);
      }
    }
  }
}
