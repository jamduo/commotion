#ifndef BODIES_H
#define BODIES_H

#define MAX_BODIES (512)

#include <raylib.h>

#include "../common/defs.h"
#include "body.h"

extern Body bodies[MAX_BODIES];
extern size_t num_bodies;

Body* bodies_add(Vec2 position, real mass, real radius);
// bool bodies_remove(Body* b); // kinda broken do not use
bool bodies_get_body(Body* b, Vec2 position);
void bodies_clear();

Body* bodies_nearest(Vec2 position); // TODO: find nearest to position

#endif // BODIES_H