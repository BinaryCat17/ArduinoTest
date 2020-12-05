#pragma once
#include "Arduino.h"

template<unsigned pin>
class OutputSignal {
public:
    void setup() {
        pinMode(pin, OUTPUT);
    }

    void update() {
        digitalWrite(pin, mState);
    }

    void reverse() {
        if (state()) {
            off();
        } else {
            on();
        }
    }

    void on() {
        mState = HIGH;
    }

    void off() {
        mState = LOW;
    }

    void state(bool value) {
        mState = value;
    }

    bool state() const {
        return mState;
    }

private:
    bool mState = false;
};

template<unsigned pin>
auto output_signal() {
    return OutputSignal<pin>();
}
