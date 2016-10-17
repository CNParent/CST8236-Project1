#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Windmill.h"
/******************************************************************************
It was naught but windmills dancing in the tranquility found above the 
stormclouds that brought enlightenment to our intrepid hero.
******************************************************************************/
float rng(float min, float max);

int main(int argc, char* argv) {
	sf::RenderWindow window(sf::VideoMode(600, 600), "Windmills");

    // Background
    sf::Texture texture;
    texture.loadFromFile("Clouds.png");
    texture.setRepeated(true);
    sf::Sprite clouds;
    clouds.setTexture(texture);
    sf::IntRect cloudRect = clouds.getTextureRect();
    cloudRect.width = 600;
    cloudRect.height = 600;
    clouds.setTextureRect(cloudRect);

    // Windmills
    Windmill* selected[3];
    Windmill* windmills[3];
    windmills[0] = new Windmill(200.0f, 300.0f);
    windmills[1] = new Windmill(300.0f, 300.0f);
    windmills[2] = new Windmill(400.0f, 300.0f);
    selected[0] = nullptr;
    selected[1] = nullptr;
    selected[2] = nullptr;

    // Audio
    sf::Music bgm;
    bgm.openFromFile("HEYAYA.flac");
    bgm.play();

    sf::Clock deltaTime;
    sf::Event sfEvent;
    
    float mouseX = 0.0f;
    float mouseY = 0.0f;
	float t = 0.0f;
    float accumulatedT = 0.0f;
    float next = rng(0.5f, 3.0f);
    float scrollRateX = rng(-2000.0f, 2000.0f);
    float scrollRateY = rng(-2000.0f, 2000.0f);
	while (window.isOpen()) {
		deltaTime.restart();
        while (window.pollEvent(sfEvent)) {
            if (sfEvent.type == sf::Event::Closed) window.close();
            if (sfEvent.type == sf::Event::KeyPressed) {
                if (sfEvent.key.code == sf::Keyboard::Num4 || sfEvent.key.code == sf::Keyboard::A){
                    selected[0] = windmills[0];
                    selected[1] = windmills[1];
                    selected[2] = windmills[2];
                    windmills[0]->AddSatellite(windmills[1]);
                    windmills[1]->AddSatellite(windmills[2]);
                }
                else {
                    if (sfEvent.key.code == sf::Keyboard::Num1) selected[0] = windmills[0];
                    else if (sfEvent.key.code == sf::Keyboard::Num2) selected[0] = windmills[1];
                    else if (sfEvent.key.code == sf::Keyboard::Num3) selected[0] = windmills[2];
                    selected[1] = nullptr;
                    selected[2] = nullptr;
                    windmills[0]->RemoveSatellite(windmills[1]);
                    windmills[1]->RemoveSatellite(windmills[2]);
                }
            }
            if (sfEvent.type == sf::Event::MouseMoved) {
                for (int i = 0; i < 3; i++){
                    if (selected[i] == nullptr) continue;
                    selected[i]->Rotate(mouseY - sfEvent.mouseMove.y);
                    selected[i]->Orbit(mouseX - sfEvent.mouseMove.x);
                }
                mouseY = sfEvent.mouseMove.y;
                mouseX = sfEvent.mouseMove.x;
            }
        }

        accumulatedT += t;
        if (accumulatedT > 0.01f){
            cloudRect = clouds.getTextureRect();
            cloudRect.left -= scrollRateX * accumulatedT;
            if (cloudRect.left < -300.0f) cloudRect.left += 300.0f;
            else if (cloudRect.left > 300.0f) cloudRect.left -= 300.0f;
            cloudRect.top -= scrollRateY * accumulatedT;
            if (cloudRect.top < -300.0f) cloudRect.left += 300.0f;
            else if (cloudRect.top > 300.0f) cloudRect.top -= 300.0f;
            clouds.setTextureRect(cloudRect);
            accumulatedT = 0.0f;
        }

        next -= t;
        if (next < 0.0f){
            next = rng(0.5f, 3.0f);
            scrollRateX = rng(-2000.0f, 2000.0f);
            scrollRateY = rng(-2000.0f, 2000.0f);
        }

        window.clear();
        window.draw(clouds);
        windmills[0]->Draw(&window);
        if (selected[1] == nullptr) windmills[1]->Draw(&window);
        if (selected[2] == nullptr) windmills[2]->Draw(&window);

        for each(Windmill* w in windmills){
            w->RotateBlades(180.0f * t);
        }

		window.display();
		t = deltaTime.getElapsedTime().asSeconds();
	}

	return 0;
}

float rng(float min, float max){
    return rand() % (int)(max - min) + min;
}
