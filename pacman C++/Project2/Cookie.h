#pragma once
#include "StaticIcon.h"


class Pacman;
class Wall;
class Demon;
class Level;

class Cookie : public StaticIcon
{
public:
	Cookie();
	Cookie(sf::Color color,sf::Vector2i Pos);
	void draw(sf::RenderWindow &window, sf::Vector2f pos)
	{
		m_sprite.setColor(m_color);
		m_sprite.setPosition(pos);
		window.draw(m_sprite);
	}
	~Cookie();
	virtual void collide(Icon * object, Level & m_level) ;
	virtual void collide(Pacman * object, Level & m_level);
	virtual void collide(Demon * object, Level & m_level) {};
	virtual void collide(Cookie * object, Level & m_level) {};
	virtual void collide(Wall * object, Level & m_level) {};
	sf::Vector2i getPosition();
	sf::Color getCookieColor();


private:
	
	sf::Color m_color;
	sf::Vector2i m_pos;
};


