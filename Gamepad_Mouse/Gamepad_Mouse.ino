//
// The digital pins 2 - 6 are grounded when they are pressed.
// Pin 2 = UP
// Pin 3 = RIGHT
// Pin 4 = DOWN
// Pin 5 = LEFT
// Pin 6 = FIRE
//
// NOTE: This sketch file is for use with Arduino Leonardo and
//
// Modified by: Luis Leon - Originally by: Matthew Heironimus
// 2017-March-26
//--------------------------------------------------------------------

#include <Joystick.h>
#include "Mouse.h"

// For mouse
int range = 2;              // output range of X or Y movement; affects movement speed
const int upButton = 2;
const int downButton = 3;
const int leftButton = 4;
const int rightButton = 5;
const int mouseButton = 6;

// For joystick
Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,JOYSTICK_TYPE_GAMEPAD,
  6, 0,                  // Button Count, Hat Switch Count
  true, true, false,     // X and Y, but no Z Axis
  false, false, false,   // No Rx, Ry, or Rz
  false, false,          // No rudder or throttle
  false, false, false);  // No accelerator, brake, or steering

void setup() {
  // Initialize Button Pins
  for(int i = 2; i<12; i++)
    pinMode(i, INPUT_PULLUP);

  // Mode pin
  pinMode(A0, INPUT);

  // Initialize Joystick Library
  Joystick.begin();
  Joystick.setXAxisRange(-1, 1);
  Joystick.setYAxisRange(-1, 1);
}

// Last state of the buttons
int lastButtonState[10] = {0,0,0,0,0,0,0,0,0,0};

void loop() {
  // Verify mode
  int mouseMode = digitalRead(A0);
  // Read pin values
  for (int index = 0; index < 10; index++)
  {
    int mouseMode = digitalRead(A0);
    int currentButtonState = !digitalRead(index + 2);
    if (currentButtonState != lastButtonState[index])
    {
      if(!mouseMode)
        switch (index) {
          case 0: // UP
            if (currentButtonState == 1) {
              Joystick.setYAxis(-1);
            } else {
              Joystick.setYAxis(0);
            }
            break;
          case 1: // RIGHT
            if (currentButtonState == 1) {
              Joystick.setXAxis(1);
            } else {
              Joystick.setXAxis(0);
            }
            break;
          case 2: // DOWN
            if (currentButtonState == 1) {
              Joystick.setYAxis(1);
            } else {
              Joystick.setYAxis(0);
            }
            break;
          case 3: // LEFT
            if (currentButtonState == 1) {
              Joystick.setXAxis(-1);
            } else {
              Joystick.setXAxis(0);
            }
            break;
          case 4: // Button 0
            Joystick.setButton(0, currentButtonState);
            break;
          case 5:  // Button 1
            Joystick.setButton(1, currentButtonState);
            break;
          case 6:  // Button 2
            Joystick.setButton(2, currentButtonState);
            break;
          case 7:  // Button 3
            Joystick.setButton(3, currentButtonState);
            break;
          case 8:  // Button 4
            Joystick.setButton(4, currentButtonState);
            break;
          case 9:  // Button 5
            Joystick.setButton(5, currentButtonState);
            break;
        }
      lastButtonState[index] = currentButtonState;
    }
    if(mouseMode)
    {
      switch (index){
           case 0:  // Up
              if(currentButtonState) Mouse.move(0, -range, 0);
              break;
           case 1:  // Right
              if(currentButtonState) Mouse.move(range, 0, 0);
              break;
           case 2:  // Down
              if(currentButtonState) Mouse.move(0, range, 0);
              break;
           case 3:  // Left
              if(currentButtonState) Mouse.move(-range, 0, 0);
              break;
           case 4: // Left click
              if (currentButtonState == 1) {
                if (!Mouse.isPressed(MOUSE_LEFT)) {
                  Mouse.press(MOUSE_LEFT);
                }
              } else {
                if (Mouse.isPressed(MOUSE_LEFT)) {
                  Mouse.release(MOUSE_LEFT);
                }
              }
           case 5: // Right click
              if (currentButtonState == 1) {
                if (!Mouse.isPressed(MOUSE_RIGHT)) {
                  Mouse.press(MOUSE_RIGHT);
                }
              } else {
                if (Mouse.isPressed(MOUSE_RIGHT)) {
                  Mouse.release(MOUSE_RIGHT);
                }
              }
        }  
    }
  }

  delay(10);
}

