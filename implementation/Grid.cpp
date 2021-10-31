#include "Grid.h"


Grid::Grid(NavMap* nav)
{
	m_NavMap = nav;

	for (int i = 0; i < SQUARE_GRID_WIDTH; i++)
	{
		for (int j = 0; j < SQUARE_GRID_HEIGHT; j++)
		{
			m_Grid[i][j] = Square(5 + i * 50, 5 + j * 50, 15);
			m_Grid[i][j].m_Node = nav->m_Grid[i][j];
		}
	}
}

void Grid::Draw(SDL_Renderer* renderer)
{
	for (int i = 0; i < SQUARE_GRID_WIDTH; i++)
	{
		for (int j = 0; j < SQUARE_GRID_HEIGHT; j++)
		{
			m_Grid[i][j].Draw(renderer);
		}
	}
}

void Grid::ColourPath(std::vector<Node*> path)
{
	for (int i = 0; i < path.size(); i++)
	{
		int indexX = path[i]->m_XIndex;
		int indexY = path[i]->m_YIndex;

		m_Grid[indexX][indexY].SetColour(0, 255, 125);
	}
}