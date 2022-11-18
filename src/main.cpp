extern "C"{
    #include "tinyPTC/tinyptc.h"
}

int main(){
    ptc_open("windows", 640, 360);

    for(;;);

    ptc_close();

    return 0;
}