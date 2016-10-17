#include "TransformNode.h"
#include "Windmill.h"

Windmill::Windmill(float x, float y){
    ox = x;
    oy = y;

    bodyTexture;
    bodyTexture.loadFromFile("Body.png");
    bodyTexture.setRepeated(true);

    bounding = new sf::RectangleShape(sf::Vector2<float>(1.0f, 1.0f));
    bounding->setFillColor(sf::Color::Transparent);
    bounding->setOrigin(0.0f, 50.0f);
    bounding->move(x, y);
    boundingNode = new TransformNode(bounding);

    body = new sf::RectangleShape(sf::Vector2<float>(20.0f, 50.0f));
    body->setTexture(&bodyTexture);
    body->setOrigin(10.0f, 25.0f);
    bodyNode = new TransformNode(body);
    boundingNode->Add(bodyNode);

    bladeTexture;
    bladeTexture.loadFromFile("Blades.png");
    bladeTexture.setRepeated(true);
    for (int i = 0; i < 4; i++){
        blades[i] = new sf::RectangleShape(sf::Vector2<float>(10.0f, 30.0f));
        blades[i]->setTexture(&bladeTexture);
        blades[i]->setOrigin(2.5f, 30.0f);
        blades[i]->move(10.0f, 10.0f);
        blades[i]->rotate(i * 90.0f);
        bladeNodes[i] = new TransformNode(blades[i]);
        bodyNode->Add(bladeNodes[i]);
    }
}

void Windmill::AddSatellite(Windmill* windmill){
    boundingNode->Add(windmill->GetRootNode());
    windmill->Move();
}

void Windmill::Draw(sf::RenderTarget* target){
    boundingNode->Draw(target);
}

TransformNode* Windmill::GetRootNode(){
    return boundingNode;
}

void Windmill::Move(){
    bounding->setPosition(0.0f, 0.0f);
}

void Windmill::Orbit(float r){
    bounding->rotate(r);
}

void Windmill::RemoveSatellite(Windmill* windmill){
    boundingNode->Remove(windmill->GetRootNode());
    windmill->Reset();
}

void Windmill::Reset(){
    bounding->setPosition(ox, oy);
}

void Windmill::Rotate(float r){
    body->rotate(r);
}

void Windmill::RotateBlades(float r){
    for (int i = 0; i < 4; i++)
        blades[i]->rotate(r);
}
