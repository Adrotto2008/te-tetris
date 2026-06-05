#pragma once

#ifdef _WIN32

#include <cstdint>

class Controller {
private:
    enum class Backend {
        None,
        XInput,
        Sfml
    };

    Backend backend = Backend::None;
    bool connected = false;
    unsigned int index = 0;
    bool buttons[32] = {false};
    int axes[32] = {0};

public:
    bool init();
    void update();

    bool buttonPressed(int id);
    int axisValue(int id);
};

#endif
