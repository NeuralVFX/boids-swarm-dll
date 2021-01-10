#include "boids.h"


boids::boids()
{

}


int boids::init(int count, int width, int height, int depth,
	float min_dist, float max_dist, float vel_mult,
	float min_vel, float  max_vel, float maxacc)
{

	// Add Model To Model Array
	modules.emplace_back(torch::jit::load("C:/ML/boids_dll/boids.ptc"));

	// Set Model Parameters
	modules.back().run_method("set_attrs", count, width, height, depth,
		min_dist, max_dist, vel_mult,
		min_vel, max_vel, maxacc);

	// Place Model on GPU, Set to Eval Mode
	modules.back().to(torch::kCUDA);
	modules.back().eval();

	// Return Ticket Numer, Used to LookUp Model During Inference
	return modules.size() - 1;

}


void boids::close()
{
}


bool boids::run(float* pos, float * vel, float gx,
	float gy, float gz, float ax, float ay,
	float az, float t_mult, float a_mult,
	float a_dist, int ticket)
{

	torch::NoGradGuard no_grad_;
	try {

		// Make GPU Tensor For Goal and Avoidance Targets
		auto goal = torch::tensor({ gx,gy,gz }).to(torch::kCUDA);
		auto avoid = torch::tensor({ ax,ay,az }).to(torch::kCUDA);

		// Run Model
		auto output = modules[ticket].run_method("forward", goal, avoid, t_mult, a_mult, a_dist);

		// Copy Result to GPU
		auto position = output.toTuple()->elements()[0].toTensor().detach().to(torch::kCPU);;
		auto velocity = output.toTuple()->elements()[1].toTensor().detach().to(torch::kCPU);;

		// Copy Tensor Data Into Pointer
		std::memcpy(pos, position.contiguous().data<float>(), sizeof(float) *position.numel());
		std::memcpy(vel, velocity.contiguous().data<float>(), sizeof(float) *velocity.numel());

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