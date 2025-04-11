#pragma once
#define Drizzle_EXPORTS
#ifdef Drizzle_EXPORTS
#define Drizzle_API __declspec(dllexport)
#else
#define Drizzle_API __declspec(dllexport)
#endif

struct Stats {
    float frametime;
    int triangle_count;
    int drawcall_count;
    float scene_update_time;
    float mesh_draw_time;
};

extern struct Stats engineStats;