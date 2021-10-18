#include "geesespotter_lib.h"


char *createBoard(std::size_t xdim, std::size_t ydim){
	char* array{ new char[xdim*ydim]{}};
	return array;
}
void computeNeighbors(char * board, std::size_t xdim, std::size_t ydim){
	for(std::size_t i{0}; i< ydim; ++i){
		for(std::size_t j{0}; j< xdim; ++j){
			if(board[xdim*i +j] != 9){
				std::size_t startx = j-1;
				std::size_t starty = i-1;
				std::size_t endx = j+1;
				std::size_t endy = i+1;

				if(j == 0){
					startx = 0;
				}
				if(i == 0){
					starty = 0;
				}
				if(j+1 > xdim -1){
					endx = j;
				}
				if(i+1 > ydim -1){
					endy = i;
				}

				int geese {0};

				for(std::size_t k{starty}; k <= endy; ++k){
					for(std::size_t q{startx}; q <= endx; ++q){
						if(board[xdim*k + q] == 9){
							geese+=1;
						}
					}
				}
				board[xdim*i + j] = (char)geese;
			}
		}
	}
}
void hideBoard(char * board, std::size_t xdim, std::size_t ydim){
	for(std::size_t i{0}; i< xdim*ydim; ++i){
		board[i]+= hiddenBit();
	}

}
void cleanBoard(char * board){
	delete[] board;
	board = nullptr;
}
void printBoard(char * board, std::size_t xdim, std::size_t ydim){
	for(std::size_t i{0}; i< ydim; ++i){
		for(std::size_t j{0}; j< xdim; ++j){

			if(board[xdim*i + j] & markedBit()){
				std::cout<< 'M';

			}
			else if(board[xdim*i + j] & hiddenBit()){
				std::cout<< '*';
			}
			else{
				std::cout << (int)board[xdim*i + j];
			}
		}
		std::cout<<std::endl;
	}

}
int reveal(char * board, std::size_t xdim, std::size_t ydim, std::size_t xloc, std::size_t yloc){
	if(board[xdim*yloc + xloc] & markedBit()){
		return 1;
	}
	else if((board[xdim*yloc + xloc] & 9) == 9){
		board[xdim*yloc + xloc] -= hiddenBit();
		return 9;
	}
	else if( !(board[xdim*yloc + xloc] & hiddenBit())){
		return 2;
	}
	else if(((board[xdim*yloc + xloc] ) & valueMask()) == 0){
		std::size_t startx = xloc-1;
		std::size_t starty = yloc-1;
		std::size_t endx = xloc+1;
		std::size_t endy = yloc+1;


		if(xloc == 0){
			startx = 0;
		}
		if(yloc == 0){
			starty = 0;
		}
		if(xloc+1 > xdim -1){
			endx = xloc;
		}
		if(yloc+1 > ydim -1){
			endy = yloc;
		}

		for(std::size_t k{starty}; k <= endy; ++k){
			for(std::size_t q{startx}; q <= endx; ++q){
				if((board[xdim*k + q] & markedBit()) == 0){
					board[xdim*k + q] -= hiddenBit();
				}
			}
		}
	}
	else{
		board[xdim*yloc + xloc] -= hiddenBit();
	}
	return 0;
}
int mark(char * board, std::size_t xdim, std::size_t ydim, std::size_t xloc, std::size_t yloc){

	if(board[yloc*xdim + xloc] & markedBit()){
		board[yloc*xdim + xloc] -= markedBit();
		return 0;
	}
	else if(board[yloc*xdim + xloc] & hiddenBit()){
		board[yloc*xdim + xloc] += markedBit();
		return 0;
	}

	return 2;
}
bool isGameWon(char * board, std::size_t xdim, std::size_t ydim){
	bool marked {false};
	bool hidden {false};
	for(std::size_t i{0}; i< xdim*ydim; ++i){

		if((board[i] & 9) != 9){
			if(board[i] & hiddenBit()){
				hidden = true;
			}
			else if(board[i] & markedBit()){
				hidden = true;
			}
			else{
				marked = true;
			}
		}else if((board[i] & 9) == 9){
			if(board[i] & markedBit()){
				marked = true;
			}
		}
	}
	if((marked == true )&& (hidden == false)){
		return true;
	}
	return false;
}
