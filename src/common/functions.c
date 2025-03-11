#include "functions.h"

Color random_colour() {
	// SetRandomSeed(GetTime());

	return (Color){
		.r = GetRandomValue(0, 255),
		.g = GetRandomValue(0, 255),
		.b = GetRandomValue(0, 255),
		.a = 255
	};
}
