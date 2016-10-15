#ifndef _WINDMILL_H
#define _WINDMILL_H

#include <SFML/Graphics.hpp>
#include "TransformNode.h"

class Windmill{
public:

    Windmill(float x, float y);
    void AddSatellite(Windmill* windmill);
    void Draw(sf::RenderTarget *target);
    TransformNode* GetRootNode();
    void Move();
    void Orbit(float r);
    void RemoveSatellite(Windmill* windmill);
    void Reset();
    void Rotate(float r);
    void RotateBlades(float r);

protected:
    
    sf::RectangleShape* bounding;
    sf::RectangleShape* body;
    sf::RectangleShape* blades[4];

    TransformNode* boundingNode;
    TransformNode* bodyNode;
    TransformNode* bladeNodes[4];

    float ox;
    float oy;

};

#endif
