#include <iostream>
#include <stdlib.h> // For the random numbers
#include <time.h> // For the time function

using namespace std;

char bgChar = ' ';
char playerChar = 'X';
char enemyChar = 'O';
char board[9] = { bgChar, bgChar, bgChar, bgChar, bgChar, bgChar, bgChar, bgChar, bgChar };
int gameState = 0; // 1 - you won; -1 - AI won; 0 - draw \\ useful for the minimax function.
int minmaxSearches = 0;

void drawBoard(){
	int i = 0;
	for(int y = 0; y < 3 * 2; y++){
		if(y % 2 != 0){
			cout << " | ";
		}
		else{
			cout << "  ";
		}
		for(int x = 0; x < 3; x++){
			if(y % 2 == 0){
				cout << "----";
			}
			else{
				cout << board[i] << " | ";
				i++;	
			}
		}
		cout << endl;
	}
	cout << "  -----------";
}

bool checkEnd(char board[9]){
	
	// check if someone won
	// horizontal
	int s = 0;
	while(s < 9){
		if(board[s] == board[s+1] && board[s] == board[s+2]){
			if(board[s] == playerChar) { gameState = 1; return true; }
			else if(board[s] == enemyChar) { gameState = -1; return true; }
		}
		s += 3;
	}
	
	// vertical
	s = 0;
	while(s < 3){
		if(board[s] == board[s+3] && board[s] == board[s+6]){
			if(board[s] == playerChar) { gameState = 1; return true; }
			else if(board[s] == enemyChar) { gameState = -1; return true; }
		}
		s += 1;
	}
	
	// diagonals
	if(board[0] == board[4] && board[0] == board[8]){
		if(board[0] == playerChar) { gameState = 1; return true; }
		else if(board[0] == enemyChar) { gameState = -1; return true; }
	}
	if(board[2] == board[4] && board[2] == board[6]){
		if(board[2] == playerChar) { gameState = 1; return true; }
		else if(board[2] == enemyChar) { gameState = -1; return true; }
	}
	
	// check if it's full, and if it is then it's a draw.
	for(int i = 0; i < 9; i++){
		if(board[i] == bgChar){ return false; }
	}
	gameState = 0;
	return true;
}

bool isTileAvailable(char n){
	return board[n] == bgChar;
}

void playerMove(){
	int choice;
	cout << "\n\nYour turn! Choose a square on the board to play." << endl;
	cin >> choice;
	while (!isTileAvailable(choice - 1)){
		cout << "\nThe square is occupied! Try again." << endl;
		cin >> choice;
	}
	board[choice-1] = playerChar;
}

int minimax(char board[9], int depth, bool maximizingPlayer){
	minmaxSearches += 1;
	char position[9];
	for(int i = 0; i < 9; i++){
		position[i] = board[i];
	}
	if(depth == 0 || checkEnd(position)) { checkEnd(position); return gameState; }

	if(maximizingPlayer){
		int maxEval = -99999;
		for(int i = 0; i < 9; i++){
			if (isTileAvailable(i)){
				position[i] = playerChar;
				int eval = minimax(position, depth - 1, false);
				position[i] = ' ';
				maxEval = max(maxEval, eval);
			}
		}
		return maxEval;
	}
	else{
		int minEval = 99999;
		for(int i = 0; i < 9; i++){
			if (isTileAvailable(i)){
				position[i] = enemyChar;
				int eval = minimax(position, depth - 1, true);
				position[i] = ' ';
				minEval = min(minEval, eval);
			}
		}
		return minEval;
	}
}

void enemyMove(){
	// Since the AI is the minimizing player:
	int bestScore = 99999;
	int score;
	int move;
	for(int i = 0; i < 9; i++){
		if(isTileAvailable(i)){
			board[i] = enemyChar;
			score = minimax(board, 4, true);
			board[i] = ' ';
			if(score < bestScore){
				bestScore = score;
				move = i;
			}
		}
	}
	cout << "Searched " << minmaxSearches << " positions.";
	minmaxSearches = 0;
	board[move] = enemyChar;
}

int main() {
	srand(time(NULL)); // Initialize the randomizer
	while(!checkEnd(board)){
		drawBoard();
		if(!checkEnd(board)) playerMove();
		if(!checkEnd(board)) enemyMove();	
		//system("cls");
	}
	//system("cls");
	drawBoard();
	if(gameState == 1){
		cout << "\n\nYou won!";
	}
	if(gameState == -1){
		cout << "The AI won! Better luck next time.";
	}
	if(gameState == 0){
		cout << "It's a draw!";
	}
	return 0;
}
