#ifndef _SDLHANDLER_H_
#define _SDLHANDLER_H_

#include <SDL2\SDL.h>
#include <array>

//SDLHandler class for the abstraction of SDL2 functions and increased readbility / structure to the main and game loop functions
class SDLHandler
{
private:
	//sdl resources to be loaded at beginning of game
	SDL_Window *m_window;
	SDL_Renderer *m_renderer;
	SDL_Surface *m_menu;
	SDL_Surface *m_cross;
	SDL_Surface *m_naught;
	SDL_Surface *m_naughtWin;
	SDL_Surface *m_crossWin;
	SDL_Surface *m_draw;
	SDL_Texture *m_menuTex;
	SDL_Texture *m_crossTex;
	SDL_Texture *m_naughtTex;
	SDL_Texture *m_naughtWinTex;
	SDL_Texture *m_crossWinTex;
	SDL_Texture *m_drawTex;
	std::array<SDL_Rect,9> m_grid;
	SDL_Rect m_source;

public:
	SDLHandler();
	~SDLHandler();
	void DrawPlayerTurn(char* _grid);
	void DrawWin(bool _player);
	void DrawDraw();
	void DrawAITurn(){};
	void DrawGrid();
	void DrawMenu();
	int HandleInputMenu(bool &_play);
	int HandlePlayerInput(bool &_play);
};




#endif