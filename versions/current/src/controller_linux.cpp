#include "controller_linux.hpp"
#include <fcntl.h>
#include <unistd.h>
#include <cstring>

bool Controller::init(){

    memset(buttons, 0, sizeof(buttons));
    memset(axes, 0, sizeof(axes));

    fd = open("/dev/input/js0", O_RDONLY | O_NONBLOCK);

    return fd >= 0;
}

void Controller::update(){

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