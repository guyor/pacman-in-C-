#pragma once
#include "DynamicIcon.h"

const int HEALTH_COOKIE_TIME = 14;
const int POISON_COOKIE_TIME = 7;

class Pacman : public DynamicIcon
{
public:
	Pacman();

	void SetPosition(sf::Vector2f new_pos);
	void SetColor(Color_t new_color);
	void setDirection(sf::Keyboard::Key direction);
	
	void draw(sf::RenderWindow &window, float passedTime);
	void move(float passedTime, sf::Vector2f boardSize);
	Direction_t getDirection();
	int getLife();
	bool getPacmanState();
	void setPacmanState();
	void setCookieCounter(int x);
	int getCookies() const;
	int getScore() const;
	void setLife(int x);
	void setScore(int x);

	virtual void collide(Icon * object, Level & m_level) {};
	virtual void collide(Pacman * object, Level & m_level) {};
	virtual void collide(Demon * object, Level & m_level) ;
	virtual void collide(Cookie * object, Level & m_level) ;
	virtual void collide(Wall * object, Level & m_level);

private:
	void checkSpeacialCookie(float passedTime);
	float m_healthCookieTimer;
	float m_poisonCookieTimer;
	int m_cookieCounter = 0;
	Color_t m_color;
	float m_speed = 5;
	int m_sourceX = 0;
	Direction_t m_newDirection;
	int m_score = 0;
	int m_life = 3;
	bool m_isEaten;
	int m_numOfDemons;
	sf::Sound m_sounds[NUM_OF_SOUNDS-2];
};


