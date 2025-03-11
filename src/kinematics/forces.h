#ifndef FORCES_H
#define FORCES_H

#include "../common/defs.h"
#include "../math/vec2.h"
#include "body.h"

real spring(real x0, real x, float v, real k, real damp);
Vec2 gravity(real mass);
Vec2 orbit(Body *a, Body *b, real G);

#endif // FORCES_H