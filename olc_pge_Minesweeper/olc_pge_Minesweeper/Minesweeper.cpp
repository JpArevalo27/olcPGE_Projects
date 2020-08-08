#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"




struct Tile{
	int x, y;
	bool bomb = false;
	bool open = false;
	int numNeihbors = 0; 
	bool flagged = false;

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
	int rows, cols, numMines;
	int tileWidth;
	int tileHeight;
	bool debug = false;
	
	std::vector<Tile> board;

public:

	Minesweeper(int i, int j, int m){
		rows = i;
		cols = j;
		numMines = m;
		
		sAppName = "Minesweeper";
	}

	void RestartGame(){
		for(int i = 0; i < board.size(); i++){
			board[i].open = false;
			board[i].bomb = false;
		}

		FillMines();
	}

	void DrawBoard(){
		// Draw Cells
		for(int i = 0; i < board.size(); i++){
			int X = board[i].x;
			int Y = board[i].y;
			if(debug || board[i].open){ //If open paint red
				FillRect(X * tileWidth, Y * tileHeight, tileWidth, tileHeight, board[i].bomb ? olc::RED : olc::DARK_GREY);
				if(board[i].numNeihbors > 0)
					DrawString(X * tileWidth + tileWidth * 0.4, Y * tileHeight + tileHeight * 0.4, std::to_string(board[i].numNeihbors));
			} else //If closed paint grey
				FillRect(X * tileWidth, Y * tileHeight, tileWidth, tileHeight, olc::GREY);
			if(board[i].flagged)
				FillTriangle(X * tileWidth + tileWidth * 0.5, Y * tileHeight + tileHeight * 0.1,
					X * tileWidth + tileWidth * 0.1, Y * tileHeight + tileHeight * 0.9,
					X * tileWidth + tileWidth * 0.9, Y * tileHeight + tileHeight * 0.9,
					olc::MAGENTA);
			DrawRect(X * tileWidth, Y * tileHeight, tileWidth, tileHeight, debug ? olc::DARK_GREEN : olc::VERY_DARK_GREY);
		}



	}

	void CountNeighbors(){
		for(int i = 0; i < board.size(); i++){
			if(board[i].bomb){
				board[i].numNeihbors = -1;
				continue;				
			}
			int count = 0;
			for(int x = -1; x <= 1; x++)
				for(int y = -1; y <= 1; y++)
					if((i + (x * cols + y)) >= 0 && (i + (x * cols + y)) < board.size())
						if(board[i + (x * cols + y)].bomb) count++;

			board[i].numNeihbors = count;

		}
	}

	void FillMines(){
		int total = 0;
		std::srand(std::time(nullptr)); // use current time as seed for random generator
		while(total < numMines){
			int pos = std::rand() % board.size();
			if(!board[pos].bomb){
				board[pos].bomb = true;
				total++;
			}
		}

		CountNeighbors();
	}

	void OpenCells(Tile& t){
		if(!t.open && !t.flagged){
			t.open = true;
			if(t.numNeihbors == 0){
				for(int x = -1; x <= 1; x++)
					for(int y = -1; y <= 1; y++)
						if((t.x + x) * cols + (t.y + y) >= 0 && (t.x + x) * cols + (t.y + y) < board.size())
							OpenCells(board[(t.x + x) * cols + (t.y + y)]);
			}
		}
	}

	
	bool OnUserCreate() override{

		tileWidth = ScreenWidth() / cols;
		tileHeight = ScreenHeight() / rows;

		for(int x = 0; x < cols; x++){
			for(int y = 0; y < rows; y++){
				board.push_back(Tile(x, y));
			}
		}

		FillMines();

		return true;
	}


	

	bool OnUserUpdate(float elapsedTime) override{

		if(GetKey(olc::SPACE).bPressed) debug = !debug;

		if(GetKey(olc::R).bPressed) RestartGame();

		if(GetMouse(0).bReleased){
			int x = GetMouseX() / tileWidth;
			int y = GetMouseY() / tileHeight;
			std::cout << "pressed the (" << x << ", " << y << ") tile with " << board[x * cols + y].numNeihbors << std::endl;
			
			OpenCells(board[x * cols + y]);
		}

		if(GetMouse(1).bReleased){
			int x = GetMouseX() / tileWidth;
			int y = GetMouseY() / tileHeight;
			//std::cout << "pressed the (" << x << ", " << y << ") tile with " << board[x * cols + y].numNeihbors << std::endl;
			if(!board[x * cols + y].open)
				board[x * cols + y].flagged = !board[x * cols + y].flagged;
		}

		
		DrawBoard();
		return true;
	}



};




int main(){

	Minesweeper game(10, 10, 10);
	if(game.Construct(401, 301, 2, 2))
		game.Start();

	return 0;
}

