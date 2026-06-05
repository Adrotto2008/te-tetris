#ifdef _WIN32

#include "controller_windows.hpp"

#include <windows.h>
#include <Xinput.h>

#include <SFML/Window/Joystick.hpp>

#include <algorithm>

#ifdef _MSC_VER
#pragma comment(lib, "Xinput.lib")
#endif

namespace {
constexpr int kAxisMax = 32767;

int scaleTrigger(BYTE value) {
    return (static_cast<int>(value) * kAxisMax) / 255;
}

int scaleAxis(float value) {
    value = std::max(-100.f, std::min(100.f, value));
    return static_cast<int>((value / 100.f) * kAxisMax);
}

int scaleAxisPositive(float value) {
    value = std::max(0.f, std::min(100.f, value));
    return static_cast<int>((value / 100.f) * kAxisMax);
}

int dpadAxis(bool negative, bool positive) {
    if (negative == positive) {
        return 0;
    }
    return negative ? -kAxisMax : kAxisMax;
}
} // namespace

bool Controller::init() {
    connected = false;
    backend = Backend::None;

    for (unsigned int i = 0; i < 4; ++i) {
        XINPUT_STATE state{};
        if (XInputGetState(i, &state) == ERROR_SUCCESS) {
            connected = true;
            backend = Backend::XInput;
            index = i;
            return true;
        }
    }

    sf::Joystick::update();
    for (unsigned int i = 0; i < sf::Joystick::Count; ++i) {
        if (sf::Joystick::isConnected(i)) {
            connected = true;
            backend = Backend::Sfml;
            index = i;
            return true;
        }
    }
    return connected;
}

void Controller::update() {
    if (!connected) {
        connected = init();
        if (!connected) return;
    }

    if (backend == Backend::XInput) {
        XINPUT_STATE state{};
        if (XInputGetState(index, &state) != ERROR_SUCCESS) {
            connected = false;
            backend = Backend::None;
            return;
        }

        const XINPUT_GAMEPAD &pad = state.Gamepad;

        // Buttons mapping
        buttons[0] = (pad.wButtons & XINPUT_GAMEPAD_A) != 0;
        buttons[1] = (pad.wButtons & XINPUT_GAMEPAD_B) != 0;
        buttons[2] = (pad.wButtons & XINPUT_GAMEPAD_X) != 0;
        buttons[3] = (pad.wButtons & XINPUT_GAMEPAD_Y) != 0;
        buttons[4] = (pad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) != 0;
        buttons[5] = (pad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) != 0;
        buttons[6] = (pad.wButtons & XINPUT_GAMEPAD_BACK) != 0;
        buttons[7] = (pad.wButtons & XINPUT_GAMEPAD_START) != 0;
        buttons[8] = (pad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB) != 0;
        buttons[9] = (pad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB) != 0;

        // Axes mapping: left stick, right stick, triggers, dpad
        axes[0] = static_cast<int>(pad.sThumbLX);
        axes[1] = static_cast<int>(pad.sThumbLY);
        axes[2] = static_cast<int>(pad.sThumbRX);
        axes[3] = static_cast<int>(pad.sThumbRY);
        axes[4] = scaleTrigger(pad.bLeftTrigger);
        axes[5] = scaleTrigger(pad.bRightTrigger);
        axes[6] = dpadAxis((pad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) != 0,
                           (pad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) != 0);
        axes[7] = dpadAxis((pad.wButtons & XINPUT_GAMEPAD_DPAD_UP) != 0,
                           (pad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) != 0);
        return;
    }

    if (backend == Backend::Sfml) {
        sf::Joystick::update();
        if (!sf::Joystick::isConnected(index)) {
            connected = false;
            backend = Backend::None;
            return;
        }

        std::fill(std::begin(buttons), std::end(buttons), false);
        std::fill(std::begin(axes), std::end(axes), 0);

        const unsigned int buttonCount = std::min(32u, sf::Joystick::getButtonCount(index));
        for (unsigned int i = 0; i < buttonCount; ++i) {
            buttons[i] = sf::Joystick::isButtonPressed(index, i);
        }

        const bool hasX = sf::Joystick::hasAxis(index, sf::Joystick::X);
        const bool hasY = sf::Joystick::hasAxis(index, sf::Joystick::Y);
        if (hasX) axes[0] = scaleAxis(sf::Joystick::getAxisPosition(index, sf::Joystick::X));
        if (hasY) axes[1] = scaleAxis(sf::Joystick::getAxisPosition(index, sf::Joystick::Y));

        const bool hasU = sf::Joystick::hasAxis(index, sf::Joystick::U);
        const bool hasV = sf::Joystick::hasAxis(index, sf::Joystick::V);
        if (hasU) axes[2] = scaleAxis(sf::Joystick::getAxisPosition(index, sf::Joystick::U));
        if (hasV) axes[3] = scaleAxis(sf::Joystick::getAxisPosition(index, sf::Joystick::V));

        const bool hasZ = sf::Joystick::hasAxis(index, sf::Joystick::Z);
        const bool hasR = sf::Joystick::hasAxis(index, sf::Joystick::R);

        if (hasZ && hasR && (hasU || hasV)) {
            axes[4] = scaleAxisPositive(sf::Joystick::getAxisPosition(index, sf::Joystick::Z));
            axes[5] = scaleAxisPositive(sf::Joystick::getAxisPosition(index, sf::Joystick::R));
        } else if (hasZ && (hasU || hasV)) {
            float z = sf::Joystick::getAxisPosition(index, sf::Joystick::Z);
            if (z >= 0.f) {
                axes[5] = scaleAxisPositive(z);
            } else {
                axes[4] = scaleAxisPositive(-z);
            }
        } else if (!hasU && !hasV && (hasZ || hasR)) {
            if (hasZ) axes[2] = scaleAxis(sf::Joystick::getAxisPosition(index, sf::Joystick::Z));
            if (hasR) axes[3] = scaleAxis(sf::Joystick::getAxisPosition(index, sf::Joystick::R));
        }

        if (sf::Joystick::hasAxis(index, sf::Joystick::PovX)) {
            axes[6] = scaleAxis(sf::Joystick::getAxisPosition(index, sf::Joystick::PovX));
        }
        if (sf::Joystick::hasAxis(index, sf::Joystick::PovY)) {
            axes[7] = scaleAxis(sf::Joystick::getAxisPosition(index, sf::Joystick::PovY));
        }
        return;
    }

    connected = false;
    backend = Backend::None;
}

bool Controller::buttonPressed(int id) {
    if (id < 0 || id >= 32) return false;
    return buttons[id];
}

int Controller::axisValue(int id) {
    if (id < 0 || id >= 32) return 0;
    return axes[id];
}

#endif
