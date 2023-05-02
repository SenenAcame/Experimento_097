#pragma once
#include <cstdint>

#define LEFT_Button  0x1111
#define RIGHT_Button 0x2222

struct Mouse {
    //bool isLeftPressed();
    //bool isRightPressed();

    bool isButtonPressed(int b);

    //void pressLeft();
    //void pressRight();

    void pressButton(int b);

    //void releaseLeft();
    //void releaseRight();

    void releaseButton(int b);
private: 
    bool leftButton  { false };
    bool rightButton { false };
};