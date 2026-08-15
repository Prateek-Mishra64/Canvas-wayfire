#pragma once

#include <stdint.h>
#include <wayfire/view.hpp>
#include <wayland-server-core.h>

namespace wf
{

/* lifecycle */

int canvas_initialize(int argc, char **argv);
void canvas_shutdown();


/* queries */

uint32_t canvas_get_modifiers();
bool canvas_cursor_position(int32_t *x, int32_t *y);
void canvas_focus_view(wayfire_view view);

/* pointer events */

/* pointer state */

struct canvas_pointer_state
{
    int32_t x = 0;
    int32_t y = 0;
    uint32_t time = 0;

    bool left = false;
    bool middle = false;
    bool right = false;

    bool button_held = false;

    uint32_t axis = 0;
    double delta = 0.0;
    uint32_t axis_time = 0;
};

const canvas_pointer_state& canvas_get_pointer_state();

struct canvas_keyboard_state
{
    uint32_t key = 0;
    bool pressed = false;
    bool held = false;
    uint32_t modifiers = 0;
};

const canvas_keyboard_state& canvas_get_keyboard_state();

void canvas_keyboard_key(uint32_t key,
                         bool pressed,
                         uint32_t modifiers);

/* pointer events from Wayfire */

void canvas_pointer_motion(int32_t x,
                           int32_t y,
                           uint32_t time);

void canvas_pointer_button(uint32_t button,
                           bool pressed,
                           uint32_t time);

void canvas_pointer_axis(uint32_t axis,
                         double delta,
                         uint32_t time);
/* keyboard events */


}
