// platformer_basic.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Coin.h"
#include "obstacles.h"
#include <sstream>
#include <SFML/Window/mouse.hpp>
#include <assert.h>
#include <windows.h>
#include <list>

//Simple pop-front method for std::vectors
//not efficient for large lists!

template<typename T>
void pop_front(std::vector<T>& vec)
{
	assert(!vec.empty());
	vec.erase(vec.begin());
}

int main() {
	//----------------------------
	//Window dimensions
	//----------------------------
	float windowDimensionX = 1000;
	float windowDimensionY = 700;
	//----------------------------
	//Obstacle Position
	//----------------------------
	float obstPos = 100;
	float obstacleWidth = 50;
	float passageWidth = 200;
	bool boolRun = true;
	bool oppositeHurdle = true;
	float hurdle1_2ht, hurdle2_2ht, hurdle3_2ht, hurdle4_2ht, hurdle5_2ht;
	//----------------------------
	//Player attributes
	//----------------------------
	float doggoPosition = 0.0f;
	float doggoVelocity = 0.0f;
	float doggoAcceleration = 0.0f;
	float myGravity = 100.0f;
	
	int nAttemptCount = 0;
	int nFlapCount = 0;
	int nMaxFlapCount = 0;

	//----------------------------
	//Create Window
	//----------------------------
	sf::RenderWindow window;
	sf::Vector2i centerWindow((sf::VideoMode::getDesktopMode().width / 2) - 445, (sf::VideoMode::getDesktopMode().height / 2) - 480);

	window.create(sf::VideoMode(windowDimensionX, windowDimensionY), "One flappy good-boi", sf::Style::Titlebar | sf::Style::Close);
	window.setPosition(centerWindow);
	window.setKeyRepeatEnabled(true);

	//player object:
	Player player({ 40, 40 });
	player.setPos({ 50, 700 });

	//hurdle objects:
	std::vector<obstacles*> obstacleVector;
	std::vector<float> obstacleHt;

	
	//----------------------------
	// Hurdle 1
	//----------------------------

	float myRandomValue = rand() % 500 + 1;
	if (myRandomValue <10)
	{
		myRandomValue = 0;
		oppositeHurdle = false;
	}

	if (!oppositeHurdle) { hurdle1_2ht = 0; }
	else {
		hurdle1_2ht = windowDimensionY - myRandomValue - passageWidth;
	}

	obstacles hurdle1_1({ obstacleWidth, myRandomValue});
	obstacles hurdle1_2({ obstacleWidth, hurdle1_2ht});
	obstacleHt.push_back(myRandomValue);
	oppositeHurdle = true;
	
	hurdle1_1.setPos({ obstPos,0 });
	hurdle1_2.setPos({ obstPos,myRandomValue+passageWidth});

	//----------------------------
	// Hurdle 2
	//----------------------------

	myRandomValue = rand() % 500 + 1;
	if (myRandomValue <10)
	{
		myRandomValue = 0;
		oppositeHurdle = false;
	}

	if (!oppositeHurdle) { hurdle2_2ht = 0; }
	else {
		hurdle2_2ht = windowDimensionY - myRandomValue - passageWidth;
	}

	obstacles hurdle2_1({ obstacleWidth, myRandomValue});
	obstacles hurdle2_2({ obstacleWidth, hurdle2_2ht});
	obstacleHt.push_back(myRandomValue);
	oppositeHurdle = true;
	
	hurdle2_1.setPos({ obstPos+250,0 });
	hurdle2_2.setPos({ obstPos+250,myRandomValue+passageWidth});

	
	
	//----------------------------
	// Hurdle 3
	//----------------------------

	myRandomValue = rand() % 500 + 1;
	if (myRandomValue <10)
	{
		myRandomValue = 0;
		oppositeHurdle = false;
	}

	if (!oppositeHurdle) { hurdle3_2ht = 0; }
	else {
		hurdle3_2ht = windowDimensionY - myRandomValue - passageWidth;
	}

	obstacles hurdle3_1({ obstacleWidth, myRandomValue});
	obstacles hurdle3_2({ obstacleWidth, hurdle1_2ht});
	obstacleHt.push_back(myRandomValue);
	oppositeHurdle = true;
	
	hurdle3_1.setPos({ obstPos+500,0 });
	hurdle3_2.setPos({ obstPos+500,myRandomValue+passageWidth});

	//----------------------------
	// Hurdle 4
	//----------------------------
	myRandomValue = rand() % 500 + 1;
	if (myRandomValue <10)
	{
		myRandomValue = 0;
		oppositeHurdle = false;
	}

	if (!oppositeHurdle) { hurdle4_2ht = 0; }
	else {
		hurdle4_2ht = windowDimensionY - myRandomValue - passageWidth;
	}

	obstacles hurdle4_1({ obstacleWidth, myRandomValue});
	obstacles hurdle4_2({ obstacleWidth, hurdle4_2ht});
	obstacleHt.push_back(myRandomValue);
	oppositeHurdle = true;
	
	hurdle4_1.setPos({ obstPos+750,0 });
	hurdle4_2.setPos({ obstPos+750,myRandomValue+passageWidth});

	//----------------------------
	// Hurdle 5
	//----------------------------

	myRandomValue = rand() % 500 + 1;
	if (myRandomValue <10)
	{
		myRandomValue = 0;
		oppositeHurdle = false;
	}

	if (!oppositeHurdle) { hurdle5_2ht = 0; }
	else {
		hurdle5_2ht = windowDimensionY - myRandomValue - passageWidth;
	}

	obstacles hurdle5_1({ obstacleWidth, myRandomValue});
	obstacles hurdle5_2({ obstacleWidth, hurdle5_2ht});
	obstacleHt.push_back(myRandomValue);
	oppositeHurdle = true;
	
	hurdle5_1.setPos({ obstPos+1000,0 });
	hurdle5_2.setPos({ obstPos+1000,myRandomValue+passageWidth});

	
	//Store obstacles for collision detection!
	obstacleVector.push_back(&hurdle1_1);
	obstacleVector.push_back(&hurdle1_2);
	obstacleVector.push_back(&hurdle2_1);
	obstacleVector.push_back(&hurdle2_2);
	obstacleVector.push_back(&hurdle3_1);
	obstacleVector.push_back(&hurdle3_2);
	obstacleVector.push_back(&hurdle4_1);
	obstacleVector.push_back(&hurdle4_2);
	obstacleVector.push_back(&hurdle5_1);
	obstacleVector.push_back(&hurdle5_2);

	//Gravity Variables:
	const int groundHeight = 700;
	const float gravitySpeed = 0.3;
	bool isJumping = false;
	int counter = 0;
	//----------------------------------------
	//Obstacle display loop1
	while (window.isOpen()) {
		
		int iter2 = 0;
		if (counter % 300 == 0) {
			myRandomValue = rand() % 500 + 1;
			pop_front(obstacleHt);
			obstacleHt.push_back(myRandomValue);
			
			for (int i = 0; i < 9; i++) {
				if (i % 2 == 0) {
					obstacleVector[i]->setSize({ obstacleWidth, obstacleHt[iter2] });
					obstacleVector[i + 1]->setSize({ obstacleWidth, windowDimensionY - obstacleHt[iter2]-passageWidth});
					obstacleVector[i+1]->setPos({obstPos+(iter2*250),obstacleHt[iter2]+passageWidth});
					iter2++;
				}
			}
		}

		sf::Event Event;
		const float moveSpeed = 0.2;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)&& doggoVelocity>=myGravity/10.0f) {
			//Character control features go here!
			doggoAcceleration = 0.0f;
			doggoVelocity = -myGravity / 4.0f;
				nFlapCount++;
				if (nFlapCount > nMaxFlapCount)
					nMaxFlapCount = nFlapCount;
								
		}
			
		else
				doggoAcceleration += myGravity * fElapsedTime;

			if (doggoAcceleration >= myGravity)
				doggoAcceleration = myGravity;

			doggoVelocity += doggoAcceleration * fElapsedTime;
			doggoPosition += doggoVelocity * fElapsedTime;			
			
			
			player.move({ 0, -moveSpeed });
			isJumping = true;
		
		

		//Event Loop:
		while (window.pollEvent(Event)) {
			switch (Event.type) {

			case sf::Event::Closed:
				window.close();

			case sf::Event::KeyReleased:
				isJumping = false;
			}
		}

		//Gravity Logic:
		if (player.getY() < groundHeight && isJumping == false) {
			player.move({ 0, gravitySpeed });
		}

		window.clear();
		player.drawTo(window);
		hurdle1_1.drawTo(window);
		hurdle2_1.drawTo(window);
		hurdle3_1.drawTo(window);
		hurdle4_1.drawTo(window);
		hurdle1_2.drawTo(window);
		hurdle2_2.drawTo(window);
		hurdle3_2.drawTo(window);
		hurdle4_2.drawTo(window);
		window.display();
		counter++;
	}
}

