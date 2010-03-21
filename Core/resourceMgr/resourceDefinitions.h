#ifndef RESOURCEDEFINITIONS_H
#define RESOURCEDEFINITIONS_H
#include <string>


struct ResourceDefinition
{
    int id;
    std::string texture;
    float texture_xoffset; // moved these up since they are saved in both JL.
    float texture_yoffset;
    float texture_width;
    float texture_height;
    int object_width;
    unsigned int textureLocation;
    int object_height;
};

struct ShipDefinition : public ResourceDefinition
{
    int velocity_thrust;
    int velocity_shot;
    int velocity_max;
    int rotation_rate;
    int ship_hit_dist;

};

struct ShotDefinition : public ResourceDefinition
{
};

#endif // RESOURCEDEFINITIONS_H
