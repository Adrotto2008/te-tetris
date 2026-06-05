#ifdef __linux__

#include "controller_linux.hpp"
#include <fcntl.h>
#include <unistd.h>
#include <cstring>
#include <cstdio>

bool Controller::init(){

    memset(buttons, 0, sizeof(buttons));
    memset(axes, 0, sizeof(axes));

    // Prova ad aprire il primo device joystick disponibile (/dev/input/js0..js15)
    fd = -1;
    for(int i = 0; i < 16; ++i){
        char path[32];
        snprintf(path, sizeof(path), "/dev/input/js%d", i);
        int tmp = open(path, O_RDONLY | O_NONBLOCK);
        if(tmp >= 0){
            fd = tmp;
            break;
        }
    }

    return fd >= 0;
}

void Controller::update(){

    if(fd < 0) return;

    while(read(fd, &e, sizeof(e)) > 0){

        if(e.type == JS_EVENT_BUTTON){
            buttons[e.number] = e.value;
        }

        if(e.type == JS_EVENT_AXIS){
            axes[e.number] = e.value;
        }

    }
}

bool Controller::buttonPressed(int id){
    return buttons[id];
}

int Controller::axisValue(int id){
    return axes[id];
}

#endif