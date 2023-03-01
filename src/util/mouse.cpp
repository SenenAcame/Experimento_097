#include "mouse.hpp"

uint8_t Mouse::isLeftPressed()  { return leftButton;  }
uint8_t Mouse::isRightPressed() { return rightButton; }
void Mouse::pressLeft()    { leftButton  = 1; }
void Mouse::pressRight()   { rightButton = 1; }
void Mouse::releaseLeft()  { leftButton  = 0; }
void Mouse::releaseRight() { rightButton = 0; }