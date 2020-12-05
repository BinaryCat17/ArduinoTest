#pragma once
#include <Arduino.h>
#include "utils.hpp"

template<unsigned pin, typename VoltageF, typename OnVoltageF, typename OffVoltageF>
class InputSignal {
public:
    explicit InputSignal(VoltageF &&f1, OnVoltageF &&f2, OffVoltageF &&f3) :
        voltageF(forward<VoltageF>(f1)), onVoltageF(forward<OnVoltageF>(f2)),
        offVoltageF(forward<OffVoltageF>(f3)) {
    }

    void setup() {
        pinMode(pin, INPUT);
    }

    void update() {
        auto pressed = !digitalRead(pin);
        if (pressed) {
            voltageF();
            if (!lastPressed) {
                onVoltageF();
            }
        } else if (lastPressed) {
            offVoltageF();
        }
        lastPressed = pressed;
    }

private:
    bool lastPressed = false;
    VoltageF voltageF;
    OnVoltageF onVoltageF;
    OffVoltageF offVoltageF;
};

template<unsigned pin, typename VoltageF, typename OnVoltageF = decltype(blank)*, typename OffVoltageF = decltype(blank)*>
auto input_signal(VoltageF &&f1, OnVoltageF &&f2 = blank, OffVoltageF &&f3 = blank) {
    return InputSignal<pin, VoltageF, OnVoltageF, OffVoltageF>(
        forward<VoltageF>(f1),
        forward<OnVoltageF>(f2),
        forward<OffVoltageF>(f3));
}
