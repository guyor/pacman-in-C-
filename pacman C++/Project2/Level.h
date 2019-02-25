#pragma once
#include "Pacman.h"
#include "Demon.h"
#include "Cookie.h"
#include "Wall.h"
#include "FileManager.h"
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include "SmartDemon.h"
#include "RandomDemon.h"

using std::ifstream;
using std::string;

class Level
{
public:
	Level(Pacman & pac,vector<std::unique_ptr<Demon>>& m_demons, int levelNumber);

	sf::Vector2f getBoardSize();
	void read_level(Pacman & pac, vector<std::unique_ptr<Demon>>& m_demons, int levelNumber);
	void setPacman(Pacman & pac, Color_t color , sf::Vector2f pos);
	void setDemon(vector<std::unique_ptr<Demon>>& m_demons, Color_t color, sf::Vector2f pos);
	StaticIcon * getIcon(sf::Vector2f pos);
	vector <vector<std::unique_ptr<StaticIcon>>> & setBoard();
	void drawStatic(sf::RenderWindow & window);

private:
	void open_file(ifstream& input, int levelNumber);
	void add_to_board(char c,size_t i, size_t j, Pacman & pac, vector<std::unique_ptr<Demon>>& m_demons);
	void setBoardSize(int rows, int cols);
	vector <vector<std::unique_ptr<StaticIcon>>> m_board;


};


