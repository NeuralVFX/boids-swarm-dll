#define DataStorage_API __declspec(dllexport)
#ifdef __cplusplus 


extern "C"
{
#endif

	DataStorage_API int InitNet(int count, int width, int height, int depth,
		float min_dist, float max_dist, float vel_mult,
		float min_vel, float  max_vel, float maxacc);

#ifdef __cplusplus
}


extern "C"
{
#endif

	DataStorage_API void CloseNet();

#ifdef __cplusplus
}


extern "C"
{
#endif

	DataStorage_API bool Run(float* pos, float* vel, float gx, float gy, float gz, float ax, float ay, float az, float t_mult, float a_mult, float a_dist, int ticket);

#ifdef __cplusplus
}

#endif