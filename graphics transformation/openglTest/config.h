#pragma once

#define PI 3.14159265358
#define SEGMENT_NUM 20
#define WINDOW_HEIGHT 500
#define WINDOW_WIDTH 500

double random(double start, double end)
{
	return start + (end - start)*rand() / (RAND_MAX - 1.0);
}