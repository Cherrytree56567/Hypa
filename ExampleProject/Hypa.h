#pragma once

#ifdef HYPA_API
#define HYPA_API __declspec(dllexport)
#else
#define HYPA_API __declspec(dllimport)
#endif // HYPA_API

HYPA_API int fnHypa();