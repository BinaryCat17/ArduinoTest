#pragma once
#include <Arduino.h>
#include "utils.hpp"

template<unsigned interval, typename FnT>
class Timer {
public:
    explicit Timer(FnT && fn) : f(forward<FnT>(fn)) { }

    void update() {
        unsigned time = millis();

        if (time - lastTime >= interval) {
            lastTime = time;
            f();
        }
    }

private:
    unsigned lastTime = 0;
    FnT f;
};

template<unsigned i, typename FnT>
auto interval(FnT &&f1) {
    return Timer<i, FnT>(forward<FnT>(f1));
}
