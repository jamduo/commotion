#include <assert.h>

#include "../../common/defs.h"
#include "../../math/vec2.h"
#include "../../kinematics/body.h"
#include "../../kinematics/bodies.h"
#include "../../kinematics/forces.h"
#include "../demo.h"

// PHYSICAL CONSTANTS
#define G ((real) 6.67430E-11)
#define EARTH_MASS ((real) 5.972E24)
#define EARTH_RADIUS ((real) 6371E3)
#define MOON_MASS ((real) 7.35E22)
#define MOON_RADIUS ((real) 1737.5E3)
#define LUNAR_DISTANCE ((real) 385000E3)

static Body* earth = NULL;
static Body* moon = NULL;
static Body* a = NULL;

void demo_init(Camera2D *camera) {
    camera->offset = (Vector2){
		HALF_SCREEN_WIDTH,
		HALF_SCREEN_HEIGHT
	};
	camera->target = (Vector2){0};
	camera->rotation = 0.0f;
	camera->zoom = 0.45E-6f;

    earth = bodies_add(vec2(0, 0), EARTH_MASS, EARTH_RADIUS * VISUAL_SCALING_FACTOR);
    assert(earth);

    moon = bodies_add(vec2(LUNAR_DISTANCE, 0), MOON_MASS, MOON_RADIUS * VISUAL_SCALING_FACTOR);
    assert(moon);

    a = bodies_add(vec2(LUNAR_DISTANCE+5E7, 0), MOON_MASS/2, MOON_RADIUS/2 * VISUAL_SCALING_FACTOR);
    assert(a);

    #define ROTATION_FORCE 1E32
    // https://gamedev.stackexchange.com/questions/70075/how-can-i-find-the-perpendicular-to-a-2d-vector
    Vec2 direction = vec2_subv(moon->state.position, earth->state.position);
    Vec2 clockwise_orbit = vec2_unit(vec2(direction.y, -direction.x));
    Vec2 force = vec2_mulr(clockwise_orbit, ROTATION_FORCE);
    body_add_force(moon, force);
    body_add_force(a, vec2_mulr(force, 0.8));
    #undef ROTATION_FORCE
}

void demo_update(real dt) {
    body_add_force(earth, orbit(moon, earth, G));
    body_add_force(earth, orbit(a, earth, G));

    body_add_force(moon, orbit(earth, moon, G));
    body_add_force(moon, orbit(a, moon, G));

    body_add_force(a, orbit(earth, a, G));
    body_add_force(a, orbit(moon, a, G));
}