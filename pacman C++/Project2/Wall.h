#pragma once
#include "StaticIcon.h"



class Pacman;
class Cookie;
class Demon;
class Level;

class Wall : public StaticIcon
{
public:
	Wall();
	void draw(sf::RenderWindow &window, sf::Vector2f pos);
	Wall(sf::Color color);
	~Wall();
	virtual void collide(Icon * object, Level & m_level);
	virtual void collide(Pacman * object, Level & m_level);
	virtual void collide(Demon * object, Level & m_level);
	virtual void collide(Cookie * object, Level & m_level) {};
	virtual void collide(Wall * object, Level & m_level) {};

private:

};


