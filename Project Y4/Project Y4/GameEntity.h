#ifndef _GameEntity_H
#define _GameEntity_H

//includes
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <vector>
#include "Menu.h"

class GameEntity {
protected:
	//vairbles
	float DegreToRad;
	float numSides;
	float width, height;
	sf::ConvexShape shape;
	sf::Vector2f direction;
	sf::Transform rotation;
	sf::Vector2f posCentre;
	std::vector<sf::Vector2f> points;
	float rotateSpeed;
	float radius;
public:
	~GameEntity();
	GameEntity(float size, float sides, sf::Vector2f pos, Menu::ColorPresets preSet);
	GameEntity(float Width, float Height, float sides, sf::Vector2f pos, Menu::ColorPresets preSet);
	void Draw(sf::RenderWindow &w);
	void SetPos(sf::RenderWindow &w);
	void Update();
	void SetColor(sf::Color color);
	sf::Vector2f GetPos();
	float GetRadius();
	sf::ConvexShape getShape();

	//SAT methods
	virtual std::pair<bool, sf::Vector2f> CollisionWithPlayer(sf::RenderWindow &w, GameEntity* shape2);
	sf::Vector2f ProjectOnToAxis(sf::Vector2f axis) const;
	std::pair<bool, double> checkOverlap(const sf::Vector2f &A, const sf::Vector2f &B);
	sf::Vector2f GetDirection();
	std::vector<sf::Vector2f> GetAxis();
	void GetAxis(std::vector<sf::Vector2f> normalsList);
	std::vector<sf::Vector2f> ReverseVector(std::vector<sf::Vector2f> v);

	//vector methods
	float vectorDotProduct(const sf::Vector2f &A, const sf::Vector2f &B) const;
	sf::Vector2f vectorNormalize(const sf::Vector2f &V);
};
#endif