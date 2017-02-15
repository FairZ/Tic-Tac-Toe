#include "SDLHandler.h"


SDLHandler::SDLHandler()
{
	//initialize SDL
	SDL_Init(SDL_INIT_VIDEO);
	//assign values for SDL_Rect's
	m_source.x = 0;
	m_source.y = 0;
	m_source.w = 200;
	m_source.h = 200;
	m_grid[0].x = 0;
	m_grid[0].y = 0;
	m_grid[0].w = 200;
	m_grid[0].h = 200;
	m_grid[1].x = 200;
	m_grid[1].y = 0;
	m_grid[1].w = 200;
	m_grid[1].h = 200;
	m_grid[2].x = 400;
	m_grid[2].y = 0;
	m_grid[2].w = 200;
	m_grid[2].h = 200;
	m_grid[3].x = 0;
	m_grid[3].y = 200;
	m_grid[3].w = 200;
	m_grid[3].h = 200;
	m_grid[4].x = 200;
	m_grid[4].y = 200;
	m_grid[4].w = 200;
	m_grid[4].h = 200;
	m_grid[5].x = 400;
	m_grid[5].y = 200;
	m_grid[5].w = 200;
	m_grid[5].h = 200;
	m_grid[6].x = 0;
	m_grid[6].y = 400;
	m_grid[6].w = 200;
	m_grid[6].h = 200;
	m_grid[7].x = 200;
	m_grid[7].y = 400;
	m_grid[7].w = 200;
	m_grid[7].h = 200;
	m_grid[8].x = 400;
	m_grid[8].y = 400;
	m_grid[8].w = 200;
	m_grid[8].h = 200;
	//create a window and renderer
	m_window = SDL_CreateWindow("Tic Tac Toe", 50, 50, 600, 600, SDL_WINDOW_SHOWN);
	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	//load in images and assign them to textures
	m_menu = SDL_LoadBMP("Menu.bmp");
	m_cross = SDL_LoadBMP("Cross.bmp");
	m_naught = SDL_LoadBMP("Naught.bmp");
	m_naughtWin = SDL_LoadBMP("NaughtWin.bmp");
	m_crossWin = SDL_LoadBMP("CrossWin.bmp");
	m_draw = SDL_LoadBMP("Draw.bmp");
	m_menuTex = SDL_CreateTextureFromSurface(m_renderer, m_menu);
	m_crossTex = SDL_CreateTextureFromSurface(m_renderer, m_cross);
	m_naughtTex = SDL_CreateTextureFromSurface(m_renderer, m_naught);
	m_naughtWinTex = SDL_CreateTextureFromSurface(m_renderer, m_naughtWin);
	m_crossWinTex = SDL_CreateTextureFromSurface(m_renderer, m_crossWin);
	m_drawTex = SDL_CreateTextureFromSurface(m_renderer, m_draw);
}

SDLHandler::~SDLHandler()
{
	//necessary SDL cleanup
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
	SDL_DestroyTexture(m_crossTex);
	SDL_DestroyTexture(m_naughtTex);
	SDL_DestroyTexture(m_menuTex);
	SDL_DestroyTexture(m_crossWinTex);
	SDL_DestroyTexture(m_naughtWinTex);
	SDL_DestroyTexture(m_drawTex);
	//quit SDL
	SDL_Quit();
}

void SDLHandler::DrawGrid()
{
	//clear renderer
	SDL_SetRenderDrawColor(m_renderer, 0xff, 0xff, 0xff, 0xff);
	SDL_RenderClear(m_renderer);
	//draw gridlines
	SDL_SetRenderDrawColor(m_renderer, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderDrawLine(m_renderer, 200, 0, 200, 600);
	SDL_RenderDrawLine(m_renderer, 400, 0, 400, 600);
	SDL_RenderDrawLine(m_renderer, 0, 200, 600, 200);
	SDL_RenderDrawLine(m_renderer, 0, 400, 600, 400);
	//present renderer to screen
	SDL_RenderPresent(m_renderer);
}

void SDLHandler::DrawMenu()
{
	//clear renderer
	SDL_SetRenderDrawColor(m_renderer, 0xff, 0xff, 0xff, 0xff);
	SDL_RenderClear(m_renderer);
	//draw menu texture
	SDL_RenderCopy(m_renderer,m_menuTex,NULL,NULL);
	//present renderer to screen
	SDL_RenderPresent(m_renderer);
}

void SDLHandler::DrawWin(bool _player)
{
	//clear renderer
	SDL_SetRenderDrawColor(m_renderer, 0xff, 0xff, 0xff, 0xff);
	SDL_RenderClear(m_renderer);
	//draw correct win texture
	if (_player)
	{
		SDL_RenderCopy(m_renderer,m_crossWinTex,NULL,NULL);
	}
	else
	{
		SDL_RenderCopy(m_renderer,m_naughtWinTex,NULL,NULL);
	}
	//present renderer to screen
	SDL_RenderPresent(m_renderer);
	//hold program for 2 seconds
	SDL_Delay(2000);
}

void SDLHandler::DrawDraw()
{
	//clear renderer
	SDL_SetRenderDrawColor(m_renderer, 0xff, 0xff, 0xff, 0xff);
	SDL_RenderClear(m_renderer);
	//draw the tied texture
	SDL_RenderCopy(m_renderer,m_drawTex,NULL,NULL);
	//present renderer to screen
	SDL_RenderPresent(m_renderer);
	//hold the program for 2 seconds
	SDL_Delay(2000);
}

void SDLHandler::DrawPlayerTurn(char* _grid){
	//clear renderer
	SDL_SetRenderDrawColor(m_renderer, 0xff, 0xff, 0xff, 0xff);
	SDL_RenderClear(m_renderer);
	//step through the grid and draw naughts or crosses where applicable
	for (int i=0; i<9; i++)
	{
		if(_grid[i] == 1)
		{
			SDL_RenderCopy(m_renderer,m_crossTex,&m_source,&m_grid[i]);
		}
		else if (_grid[i] == -1)
		{
			SDL_RenderCopy(m_renderer,m_naughtTex,&m_source,&m_grid[i]);
		}
	}
	//draw grid lines
	SDL_SetRenderDrawColor(m_renderer, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderDrawLine(m_renderer, 200, 0, 200, 600);
	SDL_RenderDrawLine(m_renderer, 400, 0, 400, 600);
	SDL_RenderDrawLine(m_renderer, 0, 200, 600, 200);
	SDL_RenderDrawLine(m_renderer, 0, 400, 600, 400);
	//present renderer to screen
	SDL_RenderPresent(m_renderer);
}

int SDLHandler::HandleInputMenu(bool &_play)
{
	SDL_Event incomingEvent;
	int retval = NULL;
	while (SDL_PollEvent(&incomingEvent))
	{
		//handle input for menu and return appropriate value or exit
		switch (incomingEvent.type)
		{
		case SDL_QUIT:
			_play = false;
			break;
		case SDL_KEYDOWN:
			switch(incomingEvent.key.keysym.sym)
			{
			case SDLK_1:
				retval = 1;
				break;
			case SDLK_2:
				retval = 2;
				break;
			case SDLK_3:
				retval = 3;
				break;
			}
		}
	}
	return retval;
}

int SDLHandler::HandlePlayerInput(bool &_play)
{
	SDL_Event incomingEvent;
	int retval = 10;
	while(retval == 10)
	{
		//handle input for player's turn and return appropriate value or quit
		while (SDL_PollEvent(&incomingEvent))
		{
			switch(incomingEvent.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				retval = 0;
				_play = false;
				break;
			case SDLK_KP_1:
				retval = 7;
				break;
			case SDLK_KP_2:
				retval = 8;
				break;
			case SDLK_KP_3:
				retval = 9;
				break;
			case SDLK_KP_4:
				retval = 4;
				break;
			case SDLK_KP_5:
				retval = 5;
				break;
			case SDLK_KP_6:
				retval = 6;
				break;
			case SDLK_KP_7:
				retval = 1;
				break;
			case SDLK_KP_8:
				retval = 2;
				break;
			case SDLK_KP_9:
				retval = 3;
				break;
			}
		}
	}
	return retval;
}