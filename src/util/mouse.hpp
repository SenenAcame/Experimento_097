#pragma once
#include <cstdint>

#define LEFT_Button  0x1111
#define RIGHT_Button 0x2222

struct Mouse {
    //uint8_t isLeftPressed();
    //uint8_t isRightPressed();

    uint8_t isButtonPressed(int b);

    //void pressLeft();
    //void pressRight();

    void pressButton(int b);

    //void releaseLeft();
    //void releaseRight();

    void releaseButton(int b);
private: 
    uint8_t leftButton  { 0 };
    uint8_t rightButton { 0 };
};