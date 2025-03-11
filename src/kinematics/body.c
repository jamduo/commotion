#include "body.h"

#include "../common/defs.h"

void body_draw(Body *b, Body *target) {
    if (b == NULL) return;

    if (target == b) {
        DrawCircle(b->state.position.x, b->state.position.y, b->radius + b->radius*0.25, YELLOW);
    }

    DrawCircle(b->state.position.x, b->state.position.y, b->radius, b->color);
}

void body_add_force(Body *b, Vec2 f) {
    if (b == NULL) return;

    // add a force scaled from pixel to world space
    b->state.force = vec2_addv(b->state.force, vec2_mulr(f, METER_SCALE_PX));
}

void body_clear_forces(Body *b) {
    if (b == NULL) return;
    
    b->state.force = (Vec2){0.0f, 0.0f};
}

void body_integrate(Body *b, float dt) {
    if (b == NULL) return;

    b->state.acceleration = vec2_divr(b->state.force, b->state.mass);

    b->state.velocity = vec2_addv(b->state.velocity, vec2_mulr(b->state.acceleration, dt));
    b->state.position = vec2_addv(b->state.position, vec2_mulr(b->state.velocity, dt));

    body_clear_forces(b);
}
