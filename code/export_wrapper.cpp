#include "export_wrapper.h"
#include "boids.h"


boids boids_util = boids();


int InitNet(AttributeData attributes)
{
	return boids_util.init(attributes);
}


void CloseNet()
{
	boids_util.close();
}


bool Run(float* pos, float* vel, TickData tick_attrs)
{
	return boids_util.run(pos, vel, tick_attrs);
}
