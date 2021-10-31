#pragma once
#define SQUARE_GRID_WIDTH 5
#define SQUARE_GRID_HEIGHT 5

#include "Square.h"
#include "SDL.h"
#include "NavMap.h"

class Grid
{
public:

	Square m_Grid[SQUARE_GRID_WIDTH][SQUARE_GRID_HEIGHT];
	NavMap* m_NavMap;

	Grid(NavMap* nav);
	void Draw(SDL_Renderer* renderer);

	void ColourPath(std::vector<Node*> path);

};