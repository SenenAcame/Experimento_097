#include "mouse.hpp"
#include <cstdint>

//uint8_t Mouse::isLeftPressed()  { return leftButton;  }
//uint8_t Mouse::isRightPressed() { return rightButton; }

uint8_t Mouse::isButtonPressed(int b) {
    if(LEFT_Button) return leftButton; 
    else            return rightButton;
}

//void Mouse::pressLeft()    { leftButton  = 1; }
//void Mouse::pressRight()   { rightButton = 1; }

void Mouse::pressButton(int b) {
    if(LEFT_Button) leftButton  = 1; 
    else            rightButton = 1;
}

//void Mouse::releaseLeft()  { leftButton  = 0; }
//void Mouse::releaseRight() { rightButton = 0; }

void Mouse::releaseButton(int b) {
    if(LEFT_Button) leftButton  = 0; 
    else            rightButton = 0;
}