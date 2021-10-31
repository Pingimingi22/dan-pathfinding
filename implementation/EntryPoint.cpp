#include "SDL.h"
#include "Dijkstra.h"
#include "NavMap.h"
#undef main

#include "Grid.h"

int main(int argc, char* args[])
{

	SDL_Init(SDL_INIT_VIDEO);

	SDL_Window* window = SDL_CreateWindow("Test of Dan-Pathfinding", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 500, SDL_WINDOW_SHOWN);

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(renderer, 125, 125, 125, 255);

	NavMap test(5, 5);

	bool isRunning = true;


	NavMap navMap(SQUARE_GRID_WIDTH, SQUARE_GRID_HEIGHT);
	Grid world(&navMap);
	//world.m_Grid[3][4].m_Passable = false;
	
	std::vector<Node*> path;
	world.m_Grid[1][0].SetPassable(false);
	world.m_Grid[2][0].SetPassable(false);
	world.m_Grid[3][0].SetPassable(false);
	path = Dijkstra::GetShortestPath(world.m_Grid[0][0].m_Node, world.m_Grid[4][0].m_Node);

	// Colouring the path.
	world.ColourPath(path);


	SDL_Event e;
	while (isRunning)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
				isRunning = false;
		}


		SDL_SetRenderDrawColor(renderer, 125, 125, 125, 255);
		SDL_RenderClear(renderer);



		SDL_SetRenderDrawColor(renderer, 0, 125, 125, 255);
		world.Draw(renderer);


		SDL_RenderPresent(renderer);

	}



	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}