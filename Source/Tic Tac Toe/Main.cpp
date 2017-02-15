#include "BinaryTreeTemplate.h"
#include "AI.h"
#include "SDLHandler.h"

#undef main

void PlayerVsPlayer(SDLHandler &_SDL);
void PlayerVsAi(SDLHandler &_SDL);

int main(void)
{

	#pragma region BST_DEMO

	//a simple demo of my BST template class, the output of PrintTree() will be in the console
	int intArray[10] = {6,2,3,9,8,1,4,7,10,0};
	std::vector<int> intData(intArray, intArray + sizeof intArray / sizeof intArray[0]);
	float floatArray[10] = {0.1,5.3,2.6,4.5,6.1,10.5,-1.5,-3.5,9.9,12.7};
	std::vector<float> floatData(floatArray, floatArray + sizeof floatArray / sizeof floatArray[0]);
	BinarySearchTree<int> intTree(5,intData);
	BinarySearchTree<float> floatTree(5.5,floatData);
	intTree.PrintTree();
	floatTree.PrintTree();

	#pragma endregion 


	bool play = true;
	SDLHandler SDL;
	//menu loop
	while (play)
	{
		SDL.DrawMenu();

		//input handling for entering into either game loop
		switch(SDL.HandleInputMenu(play))
		{
		case 1:
			PlayerVsPlayer(SDL);
			break;
		case 2:
			PlayerVsAi(SDL);
			break;
		default:
			break;
		}
	}
	return 0;
}

void PlayerVsPlayer(SDLHandler &_SDL)
{
	Node gameState;
	bool play = true;
	bool player = 0;
	int choice;
	//game loop
	while(play)
	{
		//draw call for grid
		_SDL.DrawPlayerTurn(gameState.GetData());
		//the programstalls in this function until an iput is recieved
		choice = _SDL.HandlePlayerInput(play);
		if (choice != 0)
		{
			//attempt to put the player's mark into the correct position if it cannot be done retry until it can be
			while(!gameState.PlaceMark(choice, player))
			{
				choice = _SDL.HandlePlayerInput(play);
			}
		}
		//calculate the score for the current game board
		gameState.SetScore();
		//if someone won or the game was a tie, display the correct information and return to the menu
		if ((gameState.GetScore() == 10)||(gameState.GetScore() == -10))
		{
			_SDL.DrawWin(player);
			play = false;
		}
		else if (gameState.CheckFull())
		{
			_SDL.DrawDraw();
			play = false;
		}
		//switch the current player at the end of each round
		player = !player;
	}

}

void PlayerVsAi(SDLHandler &_SDL)
{
	Node gameState;
	AI AI;
	bool play = true;
	bool player = 0;
	int choice;
	//game loop
	while(play)
	{
		//draw call for grid
		_SDL.DrawPlayerTurn(gameState.GetData());
		//if it is the players turn allow them to make a move
		if (player == 0)
		{
			choice = _SDL.HandlePlayerInput(play);
			if (choice != 0)
			{
				while(!gameState.PlaceMark(choice, player))
				{
					choice = _SDL.HandlePlayerInput(play);
				}
			}
		}
		//if it is the AI's turn allow them to make a move
		else
		{
			AI.NewRound(&gameState);
			gameState = AI.BestMove();
		}
		
		//calculate the score for the current game board
		gameState.SetScore();
		//if someone won or the game was a tie, display the correct information and return to the menu
		if ((gameState.GetScore() == 10)||(gameState.GetScore() == -10))
		{
			_SDL.DrawWin(player);
			play = false;
		}
		else if (gameState.CheckFull())
		{
			_SDL.DrawDraw();
			play = false;
		}
		//switch between AI and player's turn
		player = !player;
	}
}