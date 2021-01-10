#include <stdio.h>

#include "torch/torch.h"
#include <torch/script.h>
#include <memory>


class boids
{
public:

	// Torch Model Loader
	std::vector<torch::jit::script::Module> modules;

public:

	boids();

	int init(int count, int width, int height, int depth,
		float min_dist, float max_dist, float vel_mult,
		float min_vel, float  max_vel, float maxacc);

	void close();

	bool run(float* pos, float* vel, float gx,
		float gy, float gz, float ax, float ay,
		float az, float t_mult, float a_mult,
		float a_dist, int ticket);

	~boids();
};

