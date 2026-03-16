#pragma once

#include <linux/joystick.h>

class Controller {

private:
    int fd;
    js_event e;

    bool buttons[32];
    int axes[32];

public:

    bool init();
    void update();

    bool buttonPressed(int id);
    int axisValue(int id);

};