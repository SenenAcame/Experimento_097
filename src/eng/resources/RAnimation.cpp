#include "RAnimation.hpp"
#include "../resource_gestor.hpp"

#include <iostream>
#include <vector>

RAnimation::RAnimation() {

}

RAnimation::RAnimation(std::string name) {
    name_ = name;
    //animTimer.start();
}

RAnimation::~RAnimation() {

}

// FUNCTIONS____________________________________
//______________________________________________

void RAnimation::draw(Mat4 mat, int *currentAnim) {

    int tmpCAnim = *currentAnim;

    if(tmpCAnim >= 0) {
        if(tmpCAnim != lastAnim) {
            currentFrame = 0;
            lastAnim = tmpCAnim;
        }
        //if(animTimer.ellapsed_seconds() >= 1.0f/24.0f) {
            currentFrame++;
            //animTimer.start();
            if(currentFrame >= animations_.at(tmpCAnim).size()) {
                *currentAnim = -1;
                currentFrame = 0;
            }
        //}
        animations_.at(tmpCAnim).at(currentFrame).draw(mat);
    }
}

void RAnimation::addAnimation(std::vector<RMesh> animation) {
    animations_.push_back(animation);
}

//GETTTTTTE

int RAnimation::getFrames(int animation) {
    return animations_.at(animation).size();
}