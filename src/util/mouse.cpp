#include "mouse.hpp"
#include <cstdint>
#include <iostream>

//bool Mouse::isLeftPressed()  { return leftButton;  }
//bool Mouse::isRightPressed() { return rightButton; }

bool Mouse::isButtonPressed(int b) {
    if(b == LEFT_Button) return leftButton; 
    else                 return rightButton;
}

//void Mouse::pressLeft()    { leftButton  = 1; }
//void Mouse::pressRight()   { rightButton = 1; }

void Mouse::pressButton(int b) {
    if(b == LEFT_Button) leftButton  = true; 
    else                 rightButton = true;
}

//void Mouse::releaseLeft()  { leftButton  = 0; }
//void Mouse::releaseRight() { rightButton = 0; }

void Mouse::releaseButton(int b) {
    if(b == LEFT_Button) leftButton  = false; 
    else                 rightButton = false;
}