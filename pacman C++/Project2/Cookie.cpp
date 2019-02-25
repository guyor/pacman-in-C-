#include "Cookie.h"
#include "Pacman.h"
#include "Demon.h"
#include "Wall.h"


//this class inherates from the Static icon class

//......the cookie consructor........
Cookie::Cookie()
{
}

//..........func 1..............
//  each cookie gets color, position, size
Cookie::Cookie(sf::Color color, sf::Vector2i pos)
{
	m_pos = pos;
	m_color = color;
	m_sprite.setTexture(*(FileManager::instance().getIconTexture(COOKIE)));
	m_sprite.setScale(sf::Vector2f(((float)P_SIZE / m_sprite.getGlobalBounds().height),
		((float)P_SIZE / m_sprite.getGlobalBounds().height)));
}

//......the cookie consructor..........

Cookie::~Cookie()
{
}

//..........func 2..............
//  defines the collision of the cookie with icons
void Cookie::collide(Icon * object, Level & m_level)
{
	object->collide(this, m_level);
}

//..........func 3..............
//  defines the collision of the cookie with the pacman
void Cookie::collide(Pacman * object, Level & m_level)
{
	object->collide(this, m_level);
}

//..........func 4..............
// return the position of the cookie

sf::Vector2i Cookie::getPosition()
{
	return m_pos;
}

//..........func 5..............
// return the color of the cookie
sf::Color Cookie::getCookieColor()
{
	return m_color;
}

