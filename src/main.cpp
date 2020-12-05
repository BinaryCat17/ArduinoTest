#include "Application.hpp"

auto lamp = output_signal<13>();

auto button = input_signal<52>(blank, []{ lamp.reverse(); });

APPLICATION(100, lamp, button)
