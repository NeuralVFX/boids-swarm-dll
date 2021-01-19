#include <stdio.h>

#include "torch/torch.h"
#include <torch/script.h>
#include <memory>


/** Struct to hold attribute data needed to initialize simulation */
struct AttributeData
{
	/** Count and dimensions */
	int count, width, height, depth;

	/** Velocity limits */
	float min_dist, max_dist, vel_mult;
	float min_vel, max_vel, maxacc;
};


/** Struct to hold attribute data which can change per tick */
struct TickData
{
	/** Goal and avoid targets */
	float gx, gy, gz;
	float ax, ay, az;

	/** Multipliers and distance cut-off */
	float t_mult, a_mult, a_dist;

	/** Index of which model to lookup */
	int ticket;
};


/** Class to manage loading and running of Boids Libtorch model */
class boids
{
public:

	/** Torch model loader array */
	std::vector<torch::jit::script::Module> modules;

public:

	boids();

	/**
	 * Create Libtorch model and set attributes.
	 * @param attributes - Set of attributes required for initialization.
	 * @return interger of what index in the model array the new model is assigned.
	 */
	int init(AttributeData attributes);

	/**
	 * Empty the Libtorch model array.
	 */
	void close();

	/**
	 * Run single tick of Boids simulation.
	 * @param pos - Array to ouput new position values to.
	 * @param vel - Array to ouput new velocity values to.
	 * @param tick_attrs - Set of attributes required for tick.
	 * @return Whether the operatio was successful.
	 */
	bool run(float* pos, float* vel, TickData tick_attrs);

	~boids();
};

