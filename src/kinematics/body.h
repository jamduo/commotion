#ifndef BODY_H
#define BODY_H

#include <stdio.h> // temp
#include <stddef.h>

#include "../math/vec2.h"

// TODO: drawing should happen outside of the kinematics
//       logic.
#include <raylib.h>

// TODO: implement angular kinematics
// 
// polar: r, angular velocity, angular acceleration 
// inertia tensor
// 
// TODO: implement rectangular kinematics
// 
typedef struct State {
    // rect: position, velocity, acceleration
    Vec2 position, velocity, acceleration;

    float mass; // kg

    Vec2 force;
} State;

typedef struct Body {
    State state;
    float radius; // TODO: add ability to define shapes...
    Color color;
} Body;

void body_draw(Body *b, Body *target);
void body_add_force(Body *b, Vec2 f);
void body_clear_forces(Body *b);
void body_integrate(Body *b, float dt);

#endif // BODY_H