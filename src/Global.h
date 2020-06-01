#pragma once 

#define RATIO 30.0f
#define PIXELS_PER_METER RATIO

// 64 pixels (sfml) = 1 meter (box2d)
#define UNRATIO (1.0F/RATIO)
#define METERS_PER_PIXEL UNRATIO

//1 degrees = (radians * (pi/180))
#define RADTODEG (b2_pi / 180.0)

#define WIDTH 1920
#define HEIGHT 1080


