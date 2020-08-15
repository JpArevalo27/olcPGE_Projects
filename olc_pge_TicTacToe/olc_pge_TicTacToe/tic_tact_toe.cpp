#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include <iostream>

enum mark_t {none, x, o};
struct Tile{

	int x, y;
	bool clicked = false;
	mark_t mark = none;

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
				switch(board[i].mark){
				case mark_t::x:
					DrawLine(x * tileWidth + 0.11*tileWidth, y * tileHeight + 0.11*tileHeight, (x+1) * tileWidth - 0.11*tileWidth, (y+1) * tileHeight - 0.11*tileHeight, olc::BLUE);
					DrawLine((x+1) * tileWidth - 0.11*tileWidth, y * tileHeight + 0.11*tileHeight, x * tileWidth + 0.11*tileWidth, (y+1) * tileHeight - 0.11*tileHeight, olc::BLUE);
					break;
				case mark_t::o:
					DrawCircle(x * tileWidth + 0.5*tileWidth, y * tileHeight + 0.5*tileHeight, tileWidth*0.4, olc::RED);
					break;
				}
			}
		}

		if(winner){
			if(xTurn){ // If it's X's turn, then O won
				DrawString(ScreenWidth() * 0.2, ScreenHeight() * 0.5, "CIRCLE WINS!", olc::WHITE, 2);
			} else{
				DrawString(ScreenWidth() * 0.2, ScreenHeight() * 0.5, "CROSS WINS!", olc::WHITE, 2);
			}
		}
	}

	int CheckWin(){
		// Horizontal
		for(int i = 0; i < 3; i++){
			if(board[0 * 3 + i].mark != mark_t::none && (board[0 * 3 + i].mark == board[1 * 3 + i].mark) && (board[1 * 3 + i].mark == board[2 * 3 + i].mark)){
				std::cout << "board[0 * 3 + " << i << "].mard = " << board[0 * 3 + i].mark << std::endl;
				std::cout << "board[1 * 3 + " << i << "].mard = " << board[1 * 3 + i].mark << std::endl;
				std::cout << "board[2 * 3 + " << i << "].mard = " << board[2 * 3 + i].mark << std::endl;
				std::cout << "Winner Triggered in Horizontal check " << i << std::endl;
				return board[0 * 3 + i].mark;
			}
		}

		// Vertical
		for(int i = 0; i < 3; i++){
			if(board[i * 3 + 0].mark != mark_t::none && (board[i * 3 + 0].mark == board[i * 3 + 1].mark) && (board[i * 3 + 1].mark == board[i * 3 + 2].mark)){
				std::cout << "Winner Triggered in Vertical check " << i << std::endl;
				return board[i * 3 + 0].mark;
			}
		}

		//Diagonal
		if(board[0].mark != mark_t::none && (board[0].mark == board[4].mark) && (board[4].mark == board[8].mark)){
			std::cout << "Winner Triggered in first diagonal check " << std::endl;
			return board[0].mark;
		}

		if(board[2].mark != mark_t::none && (board[2].mark == board[4].mark) && (board[4].mark == board[6].mark)){
			std::cout << "Winner Triggered in first diagonal check " << std::endl;
			return board[2].mark;
		}

		return mark_t::none;
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
		if(playing)
			if(GetMouse(0).bReleased || GetKey(olc::SPACE).bReleased){
				int x = GetMouseX() / tileWidth;
				int y = GetMouseY() / tileHeight;
				if(!board[x * 3 + y].clicked){
					board[x * 3 + y].clicked = true;
					board[x * 3 + y].mark = xTurn ? mark_t::x : mark_t::o;
					xTurn = !xTurn;
				}
			}

		// Check win
		if(CheckWin() != mark_t::none){
			playing = false;
			winner = true;
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
