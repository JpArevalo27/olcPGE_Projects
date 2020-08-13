#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

enum{XMARK, YMARK};

struct Tile{

	int x, y;
	bool clicked = false;
	char mark;

	Tile(int i, int j){
		x = i;
		y = j;
	}
	
};

class TicTacToe : public olc::PixelGameEngine{
private:
	int blankCells = 9;
	bool playing = true;
	bool winner = false;
	bool xTurn = true;
	int tileWidth, tileHeight;
	std::vector<Tile> board;

public:

	TicTacToe(){};

	void DrawBoard(){
		for(int i = 0; i < board.size(); i++){
			int x = board[i].x;
			int y = board[i].y;
			FillRect(x * tileWidth, y * tileHeight, tileWidth, tileHeight, olc::GREY);
			DrawRect(x * tileWidth, y * tileHeight, tileWidth, tileHeight, xTurn ? olc::BLUE : olc::RED);
			if(board[i].clicked){
				std::string mark = "" + board[i].mark;
				DrawString(x * tileWidth + 0.4*tileWidth, y * tileHeight + 0.4*tileHeight, mark);
			}
		}
	}

	bool OnUserCreate(){
		tileWidth = ScreenWidth() / 3;
		tileHeight = ScreenHeight() / 3;

		for(int x = 0; x < 3; x++)
			for(int y = 0; y < 3; y++)
				board.push_back(Tile(x, y));

		return true;
	}

	bool OnUserUpdate(float elapsedTime){

		Clear(xTurn ? olc::BLUE : olc::RED);

		// Take input
		if(GetMouse(0).bReleased || GetKey(olc::SPACE).bReleased){
			int x = GetMouseX() / tileWidth;
			int y = GetMouseY() / tileHeight;
			if(!board[x * 3 + y].clicked){
				board[x * 3 + y].clicked = true;
				board[x * 3 + y].mark = xTurn ? 'X' : 'O';
				xTurn = !xTurn;
			}
		}

		DrawBoard();
		return true;
	}
};


int main(){

	TicTacToe game;
	if(game.Construct(202, 202, 2, 2))
		game.Start();


	return 0;
}
