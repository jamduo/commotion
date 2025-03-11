#include "forces.h"

real spring(real x0, real x, float v, real k, real damp) {
	return -k*(x - x0)-damp*v;
}

Vec2 gravity(real mass) {
	return (Vec2){
		.x = 0,
		.y = 9.81f * mass
	};
}

Vec2 orbit(Body *a, Body *b, real G) {
	if (a == NULL || b == NULL) return vec2(0, 0);
	
	Vec2 dir = vec2_subv(a->state.position, b->state.position); // direction vector from b to a

	// distance between center of bodies
	real d = vec2_mag(dir);

	// scalar force in r direction 'dir'
	real sf = (G*a->state.mass*b->state.mass)/(d*d);
	Vec2 f = vec2_mulr(dir, sf);

	return f;
}