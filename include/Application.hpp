#pragma once
#include "Timer.hpp"
#include "OutputSignal.hpp"
#include "InputSignal.hpp"
#include "utils.hpp"

template<typename T>
void updateArgs(T && arg) {
    arg.update();
}

template<typename T, typename... Types>
void updateArgs(T && arg, Types &&... args) {
    arg.update();
    updateArgs(args...);
}

template<unsigned time = 100, typename... Types>
auto make_app(Types &&... args) {
    return interval<time>([&]{
        updateArgs(args...);
    });
}

template<typename T>
void setupArgs(T && arg) {
    arg.setup();
}

template<typename T, typename... Types>
void setupArgs(T && arg, Types &&... args) {
    arg.setup();
    setupArgs(args...);
}


#define APPLICATION(interval, ...) \
auto app = make_app< interval >( __VA_ARGS__ ) ;\
void setup() { \
    setupArgs( __VA_ARGS__ ); \
} \
void loop() { \
    app.update(); \
}

