#pragma once
#define Drizzle_EXPORTS
#ifdef Drizzle_EXPORTS
#define Drizzle_API __declspec(dllexport)
#else
#define Drizzle_API __declspec(dllexport)
#endif