#include "boids.h"


boids::boids()
{

}


int boids::init(AttributeData attributes)
{

	// Add Model To Model Array
	modules.emplace_back(torch::jit::load("C:/ML/boids_dll/boids.ptc"));

	// Set Model Parameters
	modules.back().run_method("set_attrs", attributes.count, attributes.width,
		attributes.height, attributes.depth, attributes.min_dist,
		attributes.max_dist, attributes.vel_mult, attributes.min_vel,
		attributes.max_vel, attributes.maxacc);

	// Place Model on GPU, Set to Eval Mode
	modules.back().to(torch::kCUDA);
	modules.back().eval();

	// Return Ticket Numer, Used to LookUp Model During Inference
	return modules.size() - 1;

}


void boids::close()
{
	modules.clear();
}


bool boids::run(float* pos, float * vel, TickData tick_attrs)
{

	torch::NoGradGuard no_grad_;

	try 
	{
		// Make GPU Tensor For Goal and Avoidance Targets
		auto goal = torch::tensor({ tick_attrs.gx,
			tick_attrs.gy,
			tick_attrs.gz }).to(torch::kCUDA);

		auto avoid = torch::tensor({ tick_attrs.ax,
			tick_attrs.ay,
			tick_attrs.az }).to(torch::kCUDA);

		// Run Model
		auto output = modules[tick_attrs.ticket].run_method("forward", goal,
			avoid, tick_attrs.t_mult,
			tick_attrs.a_mult,
			tick_attrs.a_dist);

		// Copy Result to GPU
		auto position = output.toTuple()->elements()[0].toTensor().detach().to(torch::kCPU);;
		auto velocity = output.toTuple()->elements()[1].toTensor().detach().to(torch::kCPU);;

		// Copy Tensor Data Into Pointer
		std::memcpy(pos, position.contiguous().data<float>(),
			sizeof(float) *position.numel());

		std::memcpy(vel, velocity.contiguous().data<float>(),
			sizeof(float) *velocity.numel());
	}

	catch (const c10::Error& e) 
	{
		std::cerr << "An error ocurred: " << e.what() << std::endl;
		return false;
	}
	return true;
}


boids::~boids()
{

}