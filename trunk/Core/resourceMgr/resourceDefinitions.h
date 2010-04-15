#ifndef RESOURCEDEFINITIONS_H
#define RESOURCEDEFINITIONS_H
#include <string>

struct ResourceDefinition
{
    int id;
};

struct TexturedResourceDefinition : public ResourceDefinition
{
    std::string texture;
    float texture_xoffset; // moved these up since they are saved in both JL.
    float texture_yoffset;
    float texture_width;
    float texture_height;
    int object_width;
    unsigned int textureLocation;
    int object_height;
};

struct ShipDefinition : public TexturedResourceDefinition
{
    int velocity_thrust;
    int velocity_shot;
    int velocity_max;
    int rotation_rate;
    int ship_hit_dist;

};

#endif // RESOURCEDEFINITIONS_H
