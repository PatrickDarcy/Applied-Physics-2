#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif 
#pragma comment(lib,"opengl32.lib") 
#pragma comment(lib,"glu32.lib") 

#include "SFML/Graphics.hpp" 
#include "SFML/OpenGL.hpp" 
#include <math.h>

#include <iostream>


int main()
{
	float pixelsToMeters = 10.0f;
	float angleInRads = 0.0f;
	float angleInDegrees = 360.0f;
	sf::RenderWindow window(sf::VideoMode(800, 800), "Go Physics!!");

	sf::RectangleShape ground;
	ground.setFillColor(sf::Color::Red);
	ground.setPosition(0, 700);
	ground.setSize(sf::Vector2f{ 800,100 });

	sf::CircleShape shape(10.0f);
	shape.setFillColor(sf::Color::Green);

	sf::Vector2f velocity(0, 0);
	sf::Vector2f position(100, 680);

	sf::Vector2f gravity(0.0f, 9.8f * pixelsToMeters);

	sf::Time currentTime;
	sf::Text timeInAir;
	sf::Text maxHeight;
	sf::Text predictTime;
	sf::Font font;

	if (!font.loadFromFile("game_over.ttf"))
	{
		std::string s("Error loading texture");
		throw std::exception(s.c_str());
	}

	timeInAir.setCharacterSize(50);
	timeInAir.setFillColor(sf::Color::White);
	timeInAir.setFont(font);
	timeInAir.setPosition(50, 105);

	maxHeight.setCharacterSize(50);
	maxHeight.setFillColor(sf::Color::White);
	maxHeight.setFont(font);
	maxHeight.setPosition(50, 50);

	predictTime.setCharacterSize(50);
	predictTime.setFillColor(sf::Color::White);
	predictTime.setFont(font);
	predictTime.setPosition(50, 160);

	float m_maxHeight = 0.0f;
	float m_predictTime = 0.0f;

	sf::Clock clock;

	const float FPS = 60.0f;
	const sf::Time timePerFrame = sf::seconds(1.0f / 60.0f);
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	clock.restart();

	while (window.isOpen())
	{

		//read keyboard inout
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && position.y >= 680)
			{
				//velocity = { cos(angleOfProj),-104.27f };
				currentTime = sf::seconds(0.0f);

				velocity = { 12.0f * pixelsToMeters, -12.0f * pixelsToMeters } ;
				//m_maxHeight = (velocity.y * velocity.y) / (2.0 * gravity.y);
				//m_predictTime = (2.0 * -velocity.y) / gravity.y;

				maxHeight.setString("Max Height: " + std::to_string(m_maxHeight));
				predictTime.setString("Predicted Time: " + std::to_string(m_predictTime));
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
			{
				position = { 100, 680 };
				velocity = { 0,0 };
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y))
			{
				angleInRads = angleInDegrees * (3.14 / 180);

			}
		}



		//get the time since last update and restart the clock
		timeSinceLastUpdate += clock.restart();
		//update every 60th of a second
		if (timeSinceLastUpdate > timePerFrame)
		{

			if (position.y + 20 <= ground.getPosition().y || velocity.y < 0)
			{
				velocity = velocity + gravity * timeSinceLastUpdate.asSeconds();
				position = position + velocity * timeSinceLastUpdate.asSeconds() + (20.0f * gravity * (timeSinceLastUpdate.asSeconds() * timeSinceLastUpdate.asSeconds()));
				currentTime += timeSinceLastUpdate;

				timeInAir.setString("Time: " + std::to_string(currentTime.asSeconds()));

			}



			window.clear();

			// update position and velocity here using equations in lab sheet using timeChange as  timeSinceLastUpdate.asSeconds().


			//update shape on screen
			shape.setPosition(position);


			window.draw(shape);
			window.draw(ground);
			window.draw(timeInAir);
			window.draw(maxHeight);
			window.draw(predictTime);

			window.display();
			timeSinceLastUpdate = sf::Time::Zero;
		}



	}

	return 0;
}
