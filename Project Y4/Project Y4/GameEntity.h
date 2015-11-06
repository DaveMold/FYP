#ifndef _GameEntity_
#define _GameEntity_

//includes
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <vector>

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
	GameEntity(float size, float sides, sf::Vector2f pos);
	void Draw(sf::RenderWindow &w);
	void SetPos(sf::RenderWindow &w);
	void Update();
	void SetColor(sf::Color color);

	//SAT methods
	virtual std::pair<bool, sf::Vector2f> Collision(sf::RenderWindow &w, GameEntity* shape2);
	sf::Vector2f ProjectOnToAxis(sf::Vector2f axis) const;
	std::pair<bool, double> checkOverlap(const sf::Vector2f &A, const sf::Vector2f &B);
	float vectorDotProduct(const sf::Vector2f &A, const sf::Vector2f &B) const;
	sf::Vector2f vectorNormalize(const sf::Vector2f &V);
	sf::Vector2f GetDirection();
	std::vector<sf::Vector2<float>> GetAxis();
};
#endif