#include <wayfire/canvas-input.hpp>

#include "core/core-impl.hpp"
#include <wayfire/seat.hpp> 
#include <linux/input-event-codes.h>
#include "main.hpp"

namespace wf
{

static canvas_pointer_state pointer_state;
static canvas_keyboard_state keyboard_state;

const canvas_pointer_state& canvas_get_pointer_state()
{
    return pointer_state;
}

const canvas_keyboard_state& canvas_get_keyboard_state()
{
    return keyboard_state;
}

int canvas_initialize(int argc, char **argv)
{
    return wayfire_initialize_and_run(argc, argv);
}

void canvas_shutdown()
{
    compositor_core_impl_t::deallocate_core();
}

bool canvas_pointer_position(int32_t *x, int32_t *y)
{
    if (!x || !y)
        return false;

    *x = pointer_state.x;
    *y = pointer_state.y;
    return true;
}

void canvas_pointer_motion(int32_t x, int32_t y, uint32_t time)
{
    pointer_state.x = x;
    pointer_state.y = y;
    pointer_state.time = time;
}

void canvas_pointer_button(uint32_t button, bool pressed, uint32_t time)
{
    pointer_state.time = time;

    switch (button)
    {
        case BTN_LEFT:
            pointer_state.left = pressed;
            break;

        case BTN_MIDDLE:
            pointer_state.middle = pressed;
            break;

        case BTN_RIGHT:
            pointer_state.right = pressed;
            break;
    }

    pointer_state.button_held =
        pointer_state.left ||
        pointer_state.middle ||
        pointer_state.right;
}

void canvas_pointer_axis(uint32_t axis, double delta, uint32_t time)
{
    pointer_state.axis = axis;
    pointer_state.delta = delta;
    pointer_state.axis_time = time;
}

void canvas_keyboard_key(uint32_t key,
                         bool pressed,
                         uint32_t modifiers)
{
    keyboard_state.key = key;
    keyboard_state.pressed = pressed;
    keyboard_state.held = pressed;
    keyboard_state.modifiers = modifiers;
}




} // namespace wf
   //
   //
