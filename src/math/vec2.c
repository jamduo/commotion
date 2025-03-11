#include "vec2.h"


Vec2 vec2(real x, real y) {
	return (Vec2){
		.x = x,
		.y = y
	};
}

Vec2 vec2_addv(Vec2 a, Vec2 b) {
	return (Vec2){
		.x = a.x + b.x,
		.y = a.y + b.y,
	};
}

Vec2 vec2_addr(Vec2 a, real v) {
	return (Vec2){
		.x = a.x + v,
		.y = a.y + v,
	};
}

Vec2 vec2_subv(Vec2 a, Vec2 b) {
	return (Vec2){
		.x = a.x - b.x,
		.y = a.y - b.y,
	};
}

Vec2 vec2_subr(Vec2 a, real v) {
	return (Vec2){
		.x = a.x - v,
		.y = a.y - v,
	};
}

real vec2_mag(Vec2 a) {
	return sqrtf(a.x*a.x+a.y*a.y);
}

Vec2 vec2_unit(Vec2 a) {
	real mag = vec2_mag(a);
	return (Vec2){
		.x = a.x/mag,
		.y = a.y/mag,
	};
}

Vec2 vec2_mulr(Vec2 a, real f) {
	return (Vec2){
		.x = a.x*f,
		.y = a.y*f,
	};
}

Vec2 vec2_divr(Vec2 a, real f) {
	return (Vec2){
		.x = a.x/f,
		.y = a.y/f,
	};
}

real vec2_dotv(Vec2 a, Vec2 b) {
	return a.x*b.x+a.y*b.y;
}
