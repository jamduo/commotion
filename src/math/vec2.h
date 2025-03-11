#ifndef VEC2_H
#define VEC2_H

#include "../common/defs.h"
#include <math.h>

typedef struct Vec2 {
	real x;
	real y;
} Vec2;

Vec2 vec2(real x, real y);

real vec2_dotv(Vec2 a, Vec2 b);
Vec2 vec2_addv(Vec2 a, Vec2 b);
Vec2 vec2_addr(Vec2 a, real v);
Vec2 vec2_subv(Vec2 a, Vec2 b);
Vec2 vec2_subr(Vec2 a, real v);
real vec2_mag(Vec2 a);
Vec2 vec2_unit(Vec2 a);
Vec2 vec2_mulr(Vec2 a, real f);
Vec2 vec2_divr(Vec2 a, real f);

#endif // VEC2_h