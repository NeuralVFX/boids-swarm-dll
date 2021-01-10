#include "export_wrapper.h"
#include "boids.h"


boids boids_util = boids();


int InitNet(int count, int width, int height, int depth,
	float min_dist, float max_dist, float vel_mult,
	float min_vel, float  max_vel, float maxacc)
{
	return boids_util.init(count, width, height, depth,
		min_dist, max_dist, vel_mult,
		min_vel, max_vel, maxacc);
}


void CloseNet()
{
	boids_util.close();
}


bool Run(float* pos, float* vel, float gx, float gy, float gz, float ax, float ay, float az, float t_mult, float a_mult, float a_dist, int ticket)
{
	return boids_util.run(pos, vel, gx, gy, gz, ax, ay, az, t_mult, a_mult, a_dist, ticket);
}
