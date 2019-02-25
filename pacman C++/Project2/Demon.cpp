#include "Demon.h"
#include <iostream>
#include "Pacman.h"
#include "Cookie.h"
#include "Wall.h"


// this function sets the demon's position
void Demon::SetPosition(sf::Vector2f new_pos)
{
	m_sprite.setPosition(getCenter(new_pos));
}

// this function returns the demon's direction
Direction_t Demon::getDirection()
{
	return m_direction;
}
 

// this function signs a collision with a wall
void Demon::collide(Wall * object, Level & m_level)
{
	m_sprite.setPosition(getCenter(m_prevPos));
	wallCollision = true;
}

// this function  reutrns a random directio for the demon
Direction_t Demon::getRandDirection()
{
	Direction_t arr[] = { LEFT,RIGHT,UP,DOWN };
	return arr[rand() % 4];
}

// this function sets the demon's color
void Demon::SetColor(Color_t new_color)
{
	m_color = new_color;
	m_sourceX = m_color * 2;
}

// this function draws the demon
void Demon::draw(sf::RenderWindow & window, float passedTime)
{
  	m_frameCounter += passedTime*REGULAR_SPEED;
	if (m_frameCounter > SWITCH_FRAME)
	{
		m_frameCounter = 0;
		m_sourceX++;
		if (m_sourceX > m_color * 2 + 1)
			m_sourceX = m_color * 2;
	}
	m_sprite.setTextureRect(sf::IntRect(m_sourceX * P_SIZE, m_direction * P_SIZE, P_SIZE, P_SIZE));
	window.draw(m_sprite);
}


