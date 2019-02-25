#include "Pacman.h"

#include <iostream>
#include "Demon.h"
#include "Cookie.h"
#include "Wall.h"
#include "Level.h"

// Pacman c-tor

Pacman::Pacman()
{
	m_sprite.setTexture(*(FileManager::instance().getIconTexture(PACMAN)));
	m_sprite.setOrigin(getCenter(m_sprite.getPosition()));
	SetPosition(m_sprite.getOrigin());
	m_sounds[MUNCH].setBuffer(*(FileManager::instance().getPacmanSound(MUNCH)));
	m_sounds[DEATH].setBuffer(*(FileManager::instance().getPacmanSound(DEATH)));
	m_sounds[POISON_COOKIE].setBuffer(*(FileManager::instance().getPacmanSound(POISON_COOKIE)));
	m_sounds[HEALTH_COOKIE].setBuffer(*(FileManager::instance().getPacmanSound(HEALTH_COOKIE)));
}

// this function sets the pacmans position

void Pacman::SetPosition(sf::Vector2f new_pos)
{
	m_sprite.setPosition(getCenter(new_pos));
}

// this function sets the pacman's color
void Pacman::SetColor(Color_t new_color)
{
	m_color = new_color;
	m_sourceX = m_color * 2;
}

// this function sets the pacman's direction
void Pacman::setDirection(sf::Keyboard::Key direction)
{
	switch (direction)
	{
	case sf::Keyboard::Left:
		m_newDirection = LEFT;
		break;
	case sf::Keyboard::Right:
		m_newDirection = RIGHT;
		break;
	case sf::Keyboard::Up:
		m_newDirection = UP;
		break;
	case sf::Keyboard::Down:
		m_newDirection = DOWN;
		break;
		
	}
}

// this function draws the pacman
void Pacman::draw(sf::RenderWindow & window, float passedTime)
{
	if (m_cookieCounter == 0 || m_isEaten)
	{
		m_direction = RIGHT;
		m_speed = REGULAR_SPEED;
	}
	m_frameCounter += passedTime*m_speed;
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

// this function checks the timers of the special cookies 
void Pacman::checkSpeacialCookie(float passedTime)
{
	
	if (m_healthCookieTimer > 0)
		m_healthCookieTimer -= passedTime;
	else if (m_poisonCookieTimer > 0)
		m_poisonCookieTimer -= passedTime;
	else
		m_speed = REGULAR_SPEED;
}

// this function moves the pacman
void Pacman::move(float passedTime,sf::Vector2f boardSize)
{
	m_prevPos = m_sprite.getPosition();
	checkSpeacialCookie(passedTime);
	float distance = m_speed * passedTime;

	if (isCentered(m_sprite.getPosition(), getCenter(m_sprite.getPosition())))
		m_direction = m_newDirection;

	switch (m_direction)
	{
	case UP:
		m_sprite.move(0, -distance);
		break;
	case DOWN:
		m_sprite.move(0, distance);
		break;
	case RIGHT:
		m_sprite.move(distance, 0);
		break;
	case LEFT:
		m_sprite.move(-distance, 0);
		break;
	}

	if (outOfBoard(boardSize))
		m_sprite.setPosition(getCenter(m_prevPos));
	m_pos = m_sprite.getPosition();
}

// this function returns the pacman's direction
Direction_t Pacman::getDirection()
{
	return m_direction;
}

// this function returns the pacman's lives number
int Pacman::getLife()
{
	return m_life;
}

// this function return if the pacman was eaten by a demon
bool Pacman::getPacmanState()
{
	return m_isEaten;
}

// this function sets the pacman's state
void Pacman::setPacmanState()
{
	m_isEaten = false;
}

// this function sets the cookie counter
void Pacman::setCookieCounter(int x)
{
	m_cookieCounter += x;
}

// this function return the cookie counter
int Pacman::getCookies() const
{
	return m_cookieCounter;
}

// this function return the player's score
int Pacman::getScore() const
{
	return m_score;
}

// this function sets the player's lives
void Pacman::setLife(int x)
{
	if(m_life < 3)
		m_life += x;
}

// this function sets the player's score
void Pacman::setScore(int x)
{
	m_score += x;
}

// this function signs a collision with a demon
void Pacman::collide(Demon * object, Level & m_level)
{
	m_life--;
	m_isEaten = true;
	m_sounds[DEATH].play();

}

// this function signs a collision with a cookie
void Pacman::collide(Cookie * object, Level & m_level)
{
	sf::Vector2f objPos;
	objPos.x = object->getPosition().x*P_SIZE + P_SIZE/2;
	objPos.y = object->getPosition().y*P_SIZE + P_SIZE/2;

	if (abs(m_sprite.getPosition().x - objPos.x) < P_SIZE / 2 &&
		abs(m_sprite.getPosition().y - objPos.y) < P_SIZE / 2)
	{
		if (object->getCookieColor() == sf::Color::Green)
		{
			if(m_speed <= 150)
				m_speed *= 1.2;
			m_healthCookieTimer = HEALTH_COOKIE_TIME;
			m_poisonCookieTimer = 0;
			m_sounds[HEALTH_COOKIE].play();
		}
		else if (object->getCookieColor() == sf::Color::Red)
		{
			m_speed *= 0.9;
			m_poisonCookieTimer = POISON_COOKIE_TIME;
			m_healthCookieTimer = 0;
			m_sounds[POISON_COOKIE].play();
		}
		else
		{
			m_score += (m_numOfDemons + 1) * 2;
			m_cookieCounter--;
			m_sounds[MUNCH].play();
		}
		m_level.setBoard()[object->getPosition().y][object->getPosition().x] = nullptr;
	}
}

// this function signs a collision with a wall
void Pacman::collide(Wall * object, Level & m_level)
{
	m_sprite.setPosition(getCenter(m_prevPos));
}


