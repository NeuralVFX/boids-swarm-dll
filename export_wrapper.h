#define DataStorage_API __declspec(dllexport)
#ifdef __cplusplus 


extern "C"
{
#endif

	DataStorage_API int InitNet(struct AttributeData attributes);

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

	DataStorage_API bool Run(float* pos, float* vel, struct TickData tick_attrs);

#ifdef __cplusplus
}

#endif