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
	int flags = 0;
	int numOpenCells = 0;
	int tileWidth;
	int tileHeight;
	bool debug = false;
	bool playing = true;
	bool gameLost = false;

	int numMinesDrawn = 0;
	
	
	std::vector<Tile> board;

public:

	Minesweeper(int i, int j, int m){
		rows = i;
		cols = j;
		numMines = m;
		
		sAppName = "Minesweeper";
	}

	void RestartGame(){
		playing = true;
		gameLost = false;
		numOpenCells = 0;
		for(int i = 0; i < board.size(); i++){
			board[i].open = false;
			board[i].bomb = false;
			board[i].flagged = false;
		}

		flags = 0;

		FillMines();
	}

	void DrawStatusBar(){
		int minesLeft = numMines - flags;
		std::string mines = "Mines: " + std::to_string(minesLeft);
		DrawString(10, ScreenHeight() - 20, mines, olc::RED, 1);

		FillRect(ScreenWidth() - 80, ScreenHeight() - 30, 70, 29, olc::BLUE);
		DrawRect(ScreenWidth() - 80, ScreenHeight() - 30, 70, 29, olc::VERY_DARK_BLUE);
		DrawString(ScreenWidth() - 72, ScreenHeight() - 20, "Restart", olc::RED, 1);
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
					if((board[i].x + x) >= 0 && (board[i].x + x) < cols && (board[i].y + y) >= 0 && (board[i].y + y) < rows)
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
			if(!t.bomb){
				t.open = true;
				numOpenCells++;
				if(t.numNeihbors == 0){
					for(int x = -1; x <= 1; x++)
						for(int y = -1; y <= 1; y++)
							if((t.x + x) >= 0 && (t.x + x) < cols && (t.y + y) >= 0 && (t.y + y) < rows)
								OpenCells(board[(t.x + x) * cols + (t.y + y)]);
				}
			} else{
				t.open = true;
				playing = false;
				gameLost = true;
			}
		}
	}

	
	bool OnUserCreate() override{

		tileWidth = ScreenWidth() / cols;
		tileHeight = (ScreenHeight() - 30) / rows;

		
		for(int x = 0; x < cols; x++){
			for(int y = 0; y < rows; y++){
				board.push_back(Tile(x, y));
			}
		}

		FillMines();

		return true;
	}


	

	bool OnUserUpdate(float elapsedTime) override{

		Clear(olc::BLACK);

		// Check win
		if((rows * cols - numOpenCells) == numMines) playing = false;

		if(GetKey(olc::SPACE).bPressed) debug = !debug;

		if(GetKey(olc::R).bPressed) RestartGame();

		if(GetMouse(0).bReleased){
			if(GetMouseY() < ScreenHeight() - 30 && playing){
				int x = GetMouseX() / tileWidth;
				int y = GetMouseY() / tileHeight;
				std::cout << "pressed the (" << x << ", " << y << ") tile with " << board[x * cols + y].numNeihbors << std::endl;

				OpenCells(board[x * cols + y]);				
			}//FillRect(ScreenWidth() - 80, ScreenHeight() - 30, 70, 29, olc::BLUE);
			else if(GetMouseY() > ScreenHeight() - 30 && GetMouseX() > (ScreenWidth() - 80) && GetMouseX() < (ScreenWidth() - 10) ){
				RestartGame();
			}
		}

		if(GetMouse(1).bReleased && GetMouseY() < ScreenHeight() - 30){
			int x = GetMouseX() / tileWidth;
			int y = GetMouseY() / tileHeight;
			//std::cout << "pressed the (" << x << ", " << y << ") tile with " << board[x * cols + y].numNeihbors << std::endl;
			if(!board[x * cols + y].open && !board[x * cols + y].flagged){
				board[x * cols + y].flagged = true;
				flags++;
			} else if(board[x * cols + y].flagged){
				board[x * cols + y].flagged = false;
				flags--;
			}
		}

		DrawBoard();
		DrawStatusBar();
		if(!playing)
			if(gameLost) DrawString(ScreenWidth() / 2 - 40, ScreenHeight() - 20, "Game Over :(", olc::RED);
			else if(!gameLost) DrawString(ScreenWidth() / 2 - 40, ScreenHeight() - 20, "Game Over! :D", olc::RED);
		return true;
	}



};




int main(){

	Minesweeper game(10, 10, 10);
	if(game.Construct(401, 331, 2, 2))
		game.Start();

	return 0;
}

