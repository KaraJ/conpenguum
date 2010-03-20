#ifndef RESOURCEDEFINITIONS_H
#define RESOURCEDEFINITIONS_H
#include <string>
struct ResourceDefinition
{
    int id;
};

struct ShipDefinition : public ResourceDefinition
{
    int velocity_thrust;
    int velocity_shot;
    int velocity_max;
    int rotation_rate;
    int ship_hit_dist;
    std::string texture;
    float texture_xoffset;
    float texture_yoffset;
    float texture_width;
    float texture_height;
    int object_width;
    int object_height;
};

struct ShotDefinition : public ResourceDefinition
{
    std::string texture;
    float texture_xoffset;
    float texture_yoffset;
    float texture_width;
    float texture_height;
    int object_width;
    int object_height;
};

#endif // RESOURCEDEFINITIONS_H
