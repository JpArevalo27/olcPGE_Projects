#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"


struct Tile{
	int x, y;
	bool bomb = false;
	int numNeihbors = 0; 

	Tile(){
		x = 0;
		y = 0;
		bomb = false;
		numNeihbors = 0;
	}

	Tile(int i, int j){
		x = i;
		y = j;
		bomb = false;
		numNeihbors = 0;
	}



};

class Minesweeper : public olc::PixelGameEngine{
private:
	int rows, cols;
	std::vector<Tile> board;

public:

	Minesweeper(int i, int j){
		rows = i;
		cols = j;
		sAppName = "Minesweeper";
	}

	void DrawBoard(){
		int tileWidth = ScreenWidth() / cols;
		int tileHeight = ScreenHeight() / rows;
		for(int x = 0; x < cols; x++){
			for(int y = 0; y < rows; y++){
				FillRect(board[x * rows + y].x * tileWidth, board[x * rows + y].y * tileHeight, tileWidth, tileHeight, olc::GREY);
				DrawRect(board[x * rows + y].x * tileWidth, board[x * rows + y].y * tileHeight, tileWidth, tileHeight, olc::VERY_DARK_GREY);
			}
		}
	}

	bool OnUserCreate() override{
		
		for(int x = 0; x < cols; x++){
			for(int y = 0; y < rows; y++){
				board.push_back(Tile(x, y));
			}
		}
		return true;
	}

	bool OnUserUpdate(float elapsedTime) override{
		
		DrawBoard();
		return true;
	}



};




int main(){

	Minesweeper game(10, 10);
	if(game.Construct(401, 301, 2, 2))
		game.Start();

	return 0;
}

