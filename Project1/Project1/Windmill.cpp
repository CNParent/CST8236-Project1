#include "TransformNode.h"
#include "Windmill.h"

Windmill::Windmill(float x, float y){
    bounding = new sf::RectangleShape(sf::Vector2<float>(1.0f, 1.0f));
    bounding->setFillColor(sf::Color::Transparent);
    bounding->setOrigin(0.0f, 50.0f);
    bounding->move(x, y);
    boundingNode = new TransformNode(bounding);

    body = new sf::RectangleShape(sf::Vector2<float>(20.0f, 50.0f));
    body->setFillColor(sf::Color::Green);
    body->setOrigin(10.0f, 25.0f);
    bodyNode = new TransformNode(body);
    boundingNode->Add(bodyNode);

    for (int i = 0; i < 4; i++){
        blades[i] = new sf::RectangleShape(sf::Vector2<float>(10.0f, 30.0f));
        blades[i]->setFillColor(sf::Color::Red);
        blades[i]->setOrigin(2.5f, 30.0f);
        blades[i]->move(10.0f, 10.0f);
        blades[i]->rotate(i * 90.0f);
        bladeNodes[i] = new TransformNode(blades[i]);
        bodyNode->Add(bladeNodes[i]);
    }
}

void Windmill::Draw(sf::RenderTarget* target){
    boundingNode->Draw(target);
}

void Windmill::Orbit(float r){
    bounding->rotate(r);
}

void Windmill::Rotate(float r){
    body->rotate(r);
}

void Windmill::RotateBlades(float r){
    for (int i = 0; i < 4; i++)
        blades[i]->rotate(r);
}
