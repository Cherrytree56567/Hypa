#define HYPA_EXPORTS
#ifdef HYPA_EXPORTS
#define HYPA_API __declspec(dllexport)
#else
#define HYPA_API __declspec(dllexport)
#endif