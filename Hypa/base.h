#ifdef HYPA_EXPORTS
#define HYPA_API __declspec(dllexport)
#else
#define HYPA_API __declspec(dllimport)
#endif

HYPA_API int fnHypa();
