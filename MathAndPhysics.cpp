#include "MathAndPhysics.h"
float lerp(float source, float target, float weight) {
	return source + (target - source) * weight;
}
