#include <iostream>
#include <random>

int playerNumGenerator(int);
int playerDataGenerator(int);
char playerColor(int);
int boardGenerator();
int main();
int playerMovement(int, int);
bool checkValidOrKillMovement(int, int);
void sliderKillCheck(char, int);
bool sliderCheckAndMove(int, int);
int cardDraw();
char playerColorTurn(int);
int playerMovementInput(char);
bool checkIfPlayerWon(char);
void sorryCardActivation(char, int);

int playerCount = 2;
char teamColor[] = {'r', 'b', 'g', 'y'};
int pieceIdentifier[16] = { 999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999 };
int piecePosition[16] = { 999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999 };
int sliders[] = { 57, 0, 5, 9,     12, 15, 20, 24,         27, 30, 35, 39,           42, 45, 50, 54 };
int gameBoard[84] = {};
int one(5), two(4), three(4), four(4), five(4), six(4), seven(4), eight(4), nine(4), ten(4), eleven(4), twelve(4), sorry(4); //cardAmounts


int playerNumGenerator (int a) { //generates a number of each piece based off the numbers of players
	static int pieceNumber = 0;
	pieceIdentifier[a] = pieceNumber;
	pieceNumber++;
	return 0;
}
char playerColor(int pieceNum) { //function used to determine the color of a piece
	return teamColor[pieceNum / 4];
} 
int playerDataGenerator(int playerCount) { //Function that will load all data necessary for the game
	for (int a = 0; a < (playerCount * 4); a++) { //Generates the player pieces and assigns them to their base
		playerNumGenerator(a);
		switch (playerColor(a)) {
			case 'r':
				piecePosition[a] = -1;
				break;
			case 'b':
				piecePosition[a] = -2;
				break;
			case 'g':
				piecePosition[a] = -3;
				break;
			case 'y':
				piecePosition[a] = -4;
				break;
		}
	}


	return 0;
}
int boardGenerator() { //Generates a board (I think this may be useless honestly)
	int b = 0;
	do {
		static int a = 0;
		gameBoard[a] = a;
		a++;
		b++;
	} while (b < 84);
	return 0;
}
int playerMovement(int pieceNumber, int movementLeft) { //This function will move the pieces and check validity with other functions (the movement function)
	int originalPositionForIllegalReset = piecePosition[pieceNumber];
	if (piecePosition[pieceNumber] == 66 || piecePosition[pieceNumber] == 72 || piecePosition[pieceNumber] == 78 || piecePosition[pieceNumber] == 84) {
		movementLeft = 0;
	}	
	if (movementLeft == 13) {
		movementLeft = 0;
		sorryCardActivation(playerColor(pieceNumber), pieceNumber);
	}
	if (movementLeft == 4) {
		movementLeft = -4;
	}

	if (piecePosition[pieceNumber] == -1 || piecePosition[pieceNumber] == -2 || piecePosition[pieceNumber] == -3 || piecePosition[pieceNumber] == -4) {
		if (movementLeft == 1 || movementLeft == 2) {
			movementLeft = 0;
			switch (playerColor(pieceNumber)) {
			case 'r':
				if (((checkValidOrKillMovement(1, pieceNumber)))) {
					piecePosition[pieceNumber] = 1;
					break;
				}
			case 'b':
				if (((checkValidOrKillMovement(16, pieceNumber)))) {
					piecePosition[pieceNumber] = 16;
					break;
				}
			case 'g':
				if (((checkValidOrKillMovement(31, pieceNumber)))) {
					piecePosition[pieceNumber] = 31;
					break;
				}
			case 'y':
				if (((checkValidOrKillMovement(46, pieceNumber)))) {
					piecePosition[pieceNumber] = 46;
					break;
				}
			}
		} else {
			movementLeft = 0;
		}
	}
	if (movementLeft > 0) { 
		for (int x = 0; x < movementLeft; x++) {
			piecePosition[pieceNumber] += 1;
			switch (playerColor(pieceNumber)) {
				case 'r':
					if (piecePosition[pieceNumber] == 59 && playerColor(pieceNumber) == 'r') {
						piecePosition[pieceNumber] = 61;
					}
					break;
				case 'b':
					if (piecePosition[pieceNumber] == 14 && playerColor(pieceNumber) == 'b') {
						piecePosition[pieceNumber] = 67;
					}
					break;
				case 'g':
					if (piecePosition[pieceNumber] == 29 && playerColor(pieceNumber) == 'g') {
						piecePosition[pieceNumber] = 73;
					}
					break;
				case 'y':
					if (piecePosition[pieceNumber] == 44 && playerColor(pieceNumber) == 'y') {
						piecePosition[pieceNumber] = 79;
					}
					break;
			}
			if (piecePosition[pieceNumber] == 59) {
				piecePosition[pieceNumber] = 0;
			}
			if (piecePosition[pieceNumber] == 66 || piecePosition[pieceNumber] == 72 || piecePosition[pieceNumber] == 78 || piecePosition[pieceNumber] == 84) {
				movementLeft = 0;
			}
		}
	}
	else if (movementLeft < 0) {
		for (int x = 0; x > movementLeft; x--) {
			piecePosition[pieceNumber] -= 1;
			switch (playerColor(pieceNumber)) {
			case 'r':
				if (piecePosition[pieceNumber] == 60) {
					piecePosition[pieceNumber] = 58;
				}
			case 'b':
				if (piecePosition[pieceNumber] == 66) {
					piecePosition[pieceNumber] = 13;
				}
			case 'g':
				if (piecePosition[pieceNumber] == 29) {
					piecePosition[pieceNumber] = 28;
				}
			case 'y':
				if (piecePosition[pieceNumber] == 78) {
					piecePosition[pieceNumber] = 43;
				}
			}
			if (piecePosition[pieceNumber] == -1) {
				piecePosition[pieceNumber] = 59;
			}
		}
	}
	if (piecePosition[pieceNumber] == 57 || piecePosition[pieceNumber] == 5 || piecePosition[pieceNumber] == 12 || piecePosition[pieceNumber] == 20 || piecePosition[pieceNumber] == 27 || piecePosition[pieceNumber] == 35 || piecePosition[pieceNumber] == 42 || piecePosition[pieceNumber] == 50) {
		if (!(sliderCheckAndMove(piecePosition[pieceNumber], pieceNumber))) {
			std::cout << pieceNumber << std::endl;
			std::cout << piecePosition[pieceNumber] << std::endl;
			piecePosition[pieceNumber] = originalPositionForIllegalReset;
			std::cout << "Illigal move" << std::endl;
		}
	}
	else  {
		if (!(checkValidOrKillMovement(piecePosition[pieceNumber], pieceNumber))) {
			piecePosition[pieceNumber] = originalPositionForIllegalReset;
			std::cout << "Illigal move" << std::endl;
		}
	}
	return 0;
}
bool checkValidOrKillMovement(int currentPlayingPiecePosition, int currentPieceNum) { //Checks if a move is legal or not and if it will kill a piece or not
	for (int x = 0; x < (playerCount * 4); x++) {
		if (currentPlayingPiecePosition == piecePosition[x] && currentPieceNum != x) {
			if (currentPlayingPiecePosition == 66 || currentPlayingPiecePosition == 72 || currentPlayingPiecePosition == 78 || currentPlayingPiecePosition == 84) {
				return true;
			}
			else {
				if (x != currentPieceNum) {
					switch (playerColor(currentPieceNum)) {
					case 'r':
						if (playerColor(x) == 'r') {
							return false;
						}
						else if (playerColor(x) == 'b') {
							piecePosition[x] = -2;
							return true;
						}
						else if (playerColor(x) == 'g') {
							piecePosition[x] = -3;
							return true;
						}
						else if (playerColor(x) == 'y') {
							piecePosition[x] = -4;
							return true;
						}
					case 'b':
						if (playerColor(x) == 'r') {
							piecePosition[x] = -1;
							return true;
						}
						else if (playerColor(x) == 'b') {
							return false;
						}
						else if (playerColor(x) == 'g') {
							piecePosition[x] = -3;
							return true;
						}
						else if (playerColor(x) == 'y') {
							piecePosition[x] = -4;
							return true;
						}
					case 'g':
						if (playerColor(x) == 'r') {
							piecePosition[x] = -1;
							return true;
						}
						else if (playerColor(x) == 'b') {
							piecePosition[x] = -2;
							return true;
						}
						else if (playerColor(x) == 'g') {
							return false;
						}
						else if (playerColor(x) == 'y') {
							piecePosition[x] = -4;
							return true;
						}
					case 'y':
						if (playerColor(x) == 'r') {
							piecePosition[x] = -1;
							return true;
						}
						else if (playerColor(x) == 'b') {
							piecePosition[x] = -2;
							return true;
						}
						else if (playerColor(x) == 'g') {
							piecePosition[x] = -3;
							return true;
						}
						else if (playerColor(x) == 'y') {
							return false;
						}
					}
				}
			}
		}
	}
}
void sliderKillCheck(char pieceColor, int sliderPositionCheck) { //Checks if there are any kills on a slider path
	for (int x = 0; x < (playerCount * 4); x++) {
		if (piecePosition[x] == sliderPositionCheck && (pieceColor != playerColor(x))) {
			switch (playerColor(x)) {
			case 'r':
				piecePosition[x] = -1;
				break;
			case 'b':
				piecePosition[x] = -2;
				break;
			case 'g':
				piecePosition[x] = -3;
				break;
			case 'y':
				piecePosition[x] = -4;
				break;
			}
		}
	}
	return;
}
bool sliderCheckAndMove(int currentPlayingPiecePosition, int currentPieceNum) { //Checks if a pice is on the start of a slider and will move them to the end while also checking for kills and legality
	switch (playerColor(currentPieceNum)) {
		case 'r':
			if (currentPlayingPiecePosition == 12 && (!(checkValidOrKillMovement(15, currentPieceNum)))) {
				sliderKillCheck((playerColor(currentPieceNum)), 13);
				sliderKillCheck((playerColor(currentPieceNum)), 14);
				sliderKillCheck((playerColor(currentPieceNum)), 15);
				piecePosition[currentPieceNum] = 15;
				return true;
			}
			else if (currentPlayingPiecePosition == 20 && ((checkValidOrKillMovement(24, currentPieceNum)) != false)) {
				sliderKillCheck((playerColor(currentPieceNum)), 21);
				sliderKillCheck((playerColor(currentPieceNum)), 22);
				sliderKillCheck((playerColor(currentPieceNum)), 23);
				sliderKillCheck((playerColor(currentPieceNum)), 24);
				piecePosition[currentPieceNum] = 24;
				return true;
			}
			else if (currentPlayingPiecePosition == 27 && ((checkValidOrKillMovement(30, currentPieceNum)) != false)) {
				sliderKillCheck((playerColor(currentPieceNum)), 28);
				sliderKillCheck((playerColor(currentPieceNum)), 29);
				sliderKillCheck((playerColor(currentPieceNum)), 30);
				piecePosition[currentPieceNum] = 30;
				return true;
			}
			else if (currentPlayingPiecePosition == 35 && ((checkValidOrKillMovement(39, currentPieceNum)) != false)) {
				sliderKillCheck((playerColor(currentPieceNum)), 36);
				sliderKillCheck((playerColor(currentPieceNum)), 37);
				sliderKillCheck((playerColor(currentPieceNum)), 38);
				sliderKillCheck((playerColor(currentPieceNum)), 39);
				piecePosition[currentPieceNum] = 39;
				return true;
			}
			else if (currentPlayingPiecePosition == 42 && ((checkValidOrKillMovement(45, currentPieceNum)) != false)) {
				sliderKillCheck((playerColor(currentPieceNum)), 43);
				sliderKillCheck((playerColor(currentPieceNum)), 44);
				sliderKillCheck((playerColor(currentPieceNum)), 45);
				piecePosition[currentPieceNum] = 45;
				return true;
			}
			else if (currentPlayingPiecePosition == 50 && ((checkValidOrKillMovement(54, currentPieceNum)) != false)) {
				sliderKillCheck((playerColor(currentPieceNum)), 51);
				sliderKillCheck((playerColor(currentPieceNum)), 52);
				sliderKillCheck((playerColor(currentPieceNum)), 53);
				sliderKillCheck((playerColor(currentPieceNum)), 54);
				piecePosition[currentPieceNum] = 54;
				return true;
			}
			else if (currentPlayingPiecePosition == 57) {
				return checkValidOrKillMovement(57, currentPieceNum);
			}
			else if (currentPlayingPiecePosition == 5) {
				return checkValidOrKillMovement(5, currentPieceNum);
			}
			else {
				return false;
			}
		case 'b':
			if (currentPlayingPiecePosition == 57 && ((checkValidOrKillMovement(0, currentPieceNum)) != false)) {
				sliderKillCheck((playerColor(currentPieceNum)), 58);
				sliderKillCheck((playerColor(currentPieceNum)), 59);
				sliderKillCheck((playerColor(currentPieceNum)), 0);
				piecePosition[currentPieceNum] = 0;
				return true;
			}
			else if (currentPlayingPiecePosition == 5 && ((checkValidOrKillMovement(9, currentPieceNum)) != false)) {
				sliderKillCheck((playerColor(currentPieceNum)), 6);
				sliderKillCheck((playerColor(currentPieceNum)), 7);
				sliderKillCheck((playerColor(currentPieceNum)), 8);
				sliderKillCheck((playerColor(currentPieceNum)), 9);
				piecePosition[currentPieceNum] = 9;
				return true;
			}
			else if (currentPlayingPiecePosition == 27 && ((checkValidOrKillMovement(30, currentPieceNum)) != false)) {
				sliderKillCheck((playerColor(currentPieceNum)), 28);
				sliderKillCheck((playerColor(currentPieceNum)), 29);
				sliderKillCheck((playerColor(currentPieceNum)), 30);
				piecePosition[currentPieceNum] = 30;
				return true;
			}
			else if (currentPlayingPiecePosition == 35 && ((checkValidOrKillMovement(39, currentPieceNum)) != false)) {
				sliderKillCheck((playerColor(currentPieceNum)), 36);
				sliderKillCheck((playerColor(currentPieceNum)), 37);
				sliderKillCheck((playerColor(currentPieceNum)), 38);
				sliderKillCheck((playerColor(currentPieceNum)), 39);
				piecePosition[currentPieceNum] = 39;
				return true;
			}
			else if (currentPlayingPiecePosition == 42 && ((checkValidOrKillMovement(45, currentPieceNum)) != false)) {
				sliderKillCheck((playerColor(currentPieceNum)), 43);
				sliderKillCheck((playerColor(currentPieceNum)), 44);
				sliderKillCheck((playerColor(currentPieceNum)), 45);
				piecePosition[currentPieceNum] = 45;
				return true;
			}
			else if (currentPlayingPiecePosition == 50 && ((checkValidOrKillMovement(54, currentPieceNum)) != false)) {
				sliderKillCheck((playerColor(currentPieceNum)), 51);
				sliderKillCheck((playerColor(currentPieceNum)), 52);
				sliderKillCheck((playerColor(currentPieceNum)), 53);
				sliderKillCheck((playerColor(currentPieceNum)), 54);
				piecePosition[currentPieceNum] = 54;
				return true;
			}
			else if (currentPlayingPiecePosition == 12) {
				return checkValidOrKillMovement(12, currentPieceNum);
			}
			else if (currentPlayingPiecePosition == 20) {
				return checkValidOrKillMovement(20, currentPieceNum);
			}
			else {
				return false;
			}
		case 'g':
			if (currentPlayingPiecePosition == 57 && ((checkValidOrKillMovement(0, currentPieceNum)) != false)) {
				sliderKillCheck((playerColor(currentPieceNum)), 58);
				sliderKillCheck((playerColor(currentPieceNum)), 59);
				sliderKillCheck((playerColor(currentPieceNum)), 0);
				piecePosition[currentPieceNum] = 0;
				return true;
			}
			else if (currentPlayingPiecePosition == 5 && ((checkValidOrKillMovement(9, currentPieceNum)) != false)) {
				sliderKillCheck((playerColor(currentPieceNum)), 6);
				sliderKillCheck((playerColor(currentPieceNum)), 7);
				sliderKillCheck((playerColor(currentPieceNum)), 8);
				sliderKillCheck((playerColor(currentPieceNum)), 9);
				piecePosition[currentPieceNum] = 9;
				return true;
			}
			else if (currentPlayingPiecePosition == 12 && ((checkValidOrKillMovement(15, currentPieceNum)) != false)) {
				sliderKillCheck((playerColor(currentPieceNum)), 13);
				sliderKillCheck((playerColor(currentPieceNum)), 14);
				sliderKillCheck((playerColor(currentPieceNum)), 15);
				piecePosition[currentPieceNum] = 15;
				return true;
			}
			else if (currentPlayingPiecePosition == 20 && ((checkValidOrKillMovement(24, currentPieceNum)) != false)) {
				sliderKillCheck((playerColor(currentPieceNum)), 21);
				sliderKillCheck((playerColor(currentPieceNum)), 22);
				sliderKillCheck((playerColor(currentPieceNum)), 23);
				sliderKillCheck((playerColor(currentPieceNum)), 24);
				piecePosition[currentPieceNum] = 24;
				return true;
			}
			else if (currentPlayingPiecePosition == 42 && ((checkValidOrKillMovement(45, currentPieceNum)) != false)) {
				sliderKillCheck((playerColor(currentPieceNum)), 43);
				sliderKillCheck((playerColor(currentPieceNum)), 44);
				sliderKillCheck((playerColor(currentPieceNum)), 45);
				piecePosition[currentPieceNum] = 45;
				return true;
			}
			else if (currentPlayingPiecePosition == 50 && ((checkValidOrKillMovement(54, currentPieceNum)) != false)) {
				sliderKillCheck((playerColor(currentPieceNum)), 51);
				sliderKillCheck((playerColor(currentPieceNum)), 52);
				sliderKillCheck((playerColor(currentPieceNum)), 53);
				sliderKillCheck((playerColor(currentPieceNum)), 54);
				piecePosition[currentPieceNum] = 54;
				return true;
			}
			else if (currentPlayingPiecePosition == 27) {
				return checkValidOrKillMovement(27, currentPieceNum);
			}
			else if (currentPlayingPiecePosition == 35) {
				return checkValidOrKillMovement(35, currentPieceNum);
			}
			else {
				return false;
			}
		case 'y':
			if (currentPlayingPiecePosition == 57 && ((checkValidOrKillMovement(0, currentPieceNum)) != false)) {
				sliderKillCheck((playerColor(currentPieceNum)), 58);
				sliderKillCheck((playerColor(currentPieceNum)), 59);
				sliderKillCheck((playerColor(currentPieceNum)), 0);
				piecePosition[currentPieceNum] = 0;
				return true;
			}
			else if (currentPlayingPiecePosition == 5 && ((checkValidOrKillMovement(9, currentPieceNum)) != false)) {
				sliderKillCheck((playerColor(currentPieceNum)), 6);
				sliderKillCheck((playerColor(currentPieceNum)), 7);
				sliderKillCheck((playerColor(currentPieceNum)), 8);
				sliderKillCheck((playerColor(currentPieceNum)), 9);
				piecePosition[currentPieceNum] = 9;
				return true;
			}
			else if (currentPlayingPiecePosition == 12 && ((checkValidOrKillMovement(15, currentPieceNum)) != false)) {
				sliderKillCheck((playerColor(currentPieceNum)), 13);
				sliderKillCheck((playerColor(currentPieceNum)), 14);
				sliderKillCheck((playerColor(currentPieceNum)), 15);
				piecePosition[currentPieceNum] = 15;
				return true;
			}
			else if (currentPlayingPiecePosition == 20 && ((checkValidOrKillMovement(24, currentPieceNum)) != false)) {
				sliderKillCheck((playerColor(currentPieceNum)), 21);
				sliderKillCheck((playerColor(currentPieceNum)), 22);
				sliderKillCheck((playerColor(currentPieceNum)), 23);
				sliderKillCheck((playerColor(currentPieceNum)), 24);
				piecePosition[currentPieceNum] = 24;
				return true;
			}
			else if (currentPlayingPiecePosition == 27 && ((checkValidOrKillMovement(30, currentPieceNum)) != false)) {
				sliderKillCheck((playerColor(currentPieceNum)), 28);
				sliderKillCheck((playerColor(currentPieceNum)), 29);
				sliderKillCheck((playerColor(currentPieceNum)), 30);
				piecePosition[currentPieceNum] = 30;
				return true;
			}
			else if (currentPlayingPiecePosition == 35 && ((checkValidOrKillMovement(39, currentPieceNum)) != false)) {
				sliderKillCheck((playerColor(currentPieceNum)), 36);
				sliderKillCheck((playerColor(currentPieceNum)), 37);
				sliderKillCheck((playerColor(currentPieceNum)), 38);
				sliderKillCheck((playerColor(currentPieceNum)), 39);
				piecePosition[currentPieceNum] = 39;
				return true;
			}
			else if (currentPlayingPiecePosition == 42) {
				return checkValidOrKillMovement(42, currentPieceNum);
			}
			else if (currentPlayingPiecePosition == 50) {
				return checkValidOrKillMovement(50, currentPieceNum);
			}
			else {
				return false;
			}
	}
}
int cardDraw() {
	int cardNumber;
	bool availableCard = false;
	if (one == 0 && two == 0 && three == 0 && four == 0 && five == 0 && six == 0 && seven == 0 && eight == 0 && nine == 0 && ten == 0 && eleven == 0 && twelve == 0 && sorry == 0) {
		one = (5);
		two = (4);
		three = (4);
		four = (4);
		five = (4);
		six = (4);
		seven = (4);
		eight = (4);
		nine = (4);
		ten = (4);
		eleven = (4);
		twelve = (4);
		sorry = (4);
	}
	do {
		std::mt19937 rng;
		rng.seed(std::random_device()());
		std::uniform_int_distribution<std::mt19937::result_type> random(1, 13); // distribution in range [1, 6] 
		cardNumber = random(rng);
		switch (cardNumber) {
		case 1:
			if (one >= 1) {
				one--;
				availableCard = true;
			}
			break;
		case 2:
			if (two >= 1) {
				two--;
				availableCard = true;
			}
			break;
		case 3:
			if (three >= 1) {
				three--;
				availableCard = true;
			}
			break;
		case 4:
			if (four >= 1) {
				four--;
				availableCard = true;
			}
			break;
		case 5:
			if (five >= 1) {
				five--;
				availableCard = true;
			}
			break;
		case 6:
			if (six >= 1) {
				six--;
				availableCard = true;
			}
			break;
		case 7:
			if (seven >= 1) {
				seven--;
				availableCard = true;
			}
			break;
		case 8:
			if (eight >= 1) {
				eight--;
				availableCard = true;
			}
			break;
		case 9:
			if (nine >= 1) {
				nine--;
				availableCard = true;
			}
			break;
		case 10:
			if (ten >= 1) {
				ten--;
				availableCard = true;
			}
			break;
		case 11:
			if (eleven >= 1) {
				eleven--;
				availableCard = true;
			}
			break;
		case 12:
			if (twelve >= 1) {
				twelve--;
				availableCard = true;
			}
			break;
		case 13:
			if (sorry >= 1) {
				sorry--;
				availableCard = true;
			}
			break;
		}
	} while (availableCard == false);
	return cardNumber;
}
char playerColorTurn(int cardNumber) {
	static int turn;
	if (playerCount == 4) {
		turn++;
		if (turn > 4) {
			turn = 1;
		}
	} else if (playerCount == 3) {
		turn++;
		if (turn > 3) {
			turn = 1;
		}
	} else if (playerCount == 2) {
		turn++;
		if (turn > 2) {
			turn = 1;
		}
	}
	
	switch (turn) {
		case 1:
			if (cardNumber == 2) {
				turn--;
			}
			return 'r';
			break;
		case 2:
			if (cardNumber == 2) {
				turn--;
			}
			return 'b';
			break;
		case 3:
			if (cardNumber == 2) {
				turn--;
			}
			return 'g';
			break;
		case 4:
			if (cardNumber == 2) {
				turn--;
			}
			return 'y';
			break;
	}
}
int playerMovementInput(char colorOfPlayer) {
	std::cout << "Input what piece you would like to move." << std::endl;
		bool intCheck = false;
		int input = 0;
		do {
			std::cout << "Make sure it's either 1, 2, 3 or 4!\n";
			std::cin >> input;
			if ((input == 1 || input == 2 || input == 3 || input == 4)) {
				intCheck = true;
			}
			std::cin.clear();
			std::cin.ignore();
		} while (!(intCheck));
		switch (input) {
		case 1:
			if (colorOfPlayer == 'r') {
				return 0;
			}
			else if (colorOfPlayer == 'b') {
				return 4;
			}
			else if (colorOfPlayer == 'g') {
				return 8;
			}
			else if (colorOfPlayer == 'y') {
				return 12;
			}
		case 2:
			if (colorOfPlayer == 'r') {
				return 1;
			}
			else if (colorOfPlayer == 'b') {
				return 5;
			}
			else if (colorOfPlayer == 'g') {
				return 9;
			}
			else if (colorOfPlayer == 'y') {
				return 13;
			}
		case 3:
			if (colorOfPlayer == 'r') {
				return 2;
			}
			else if (colorOfPlayer == 'b') {
				return 6;
			}
			else if (colorOfPlayer == 'g') {
				return 10;
			}
			else if (colorOfPlayer == 'y') {
				return 14;
			}
		case 4:
			if (colorOfPlayer == 'r') {
				return 3;
			}
			else if (colorOfPlayer == 'b') {
				return 7;
			}
			else if (colorOfPlayer == 'g') {
				return 11;
			}
			else if (colorOfPlayer == 'y') {
				return 15;
			}
		}
}
bool checkIfPlayerWon(char colorOfPlayer) {
	switch (colorOfPlayer) {
	case 'r':
		if (piecePosition[0] == 66 && piecePosition[1] == 66 && piecePosition[2] == 66 && piecePosition[3] == 66) {
			return true;
		}
		else {
			return false;
		}
	case 'b':
		if (piecePosition[4] == 72 && piecePosition[5] == 72 && piecePosition[6] == 72 && piecePosition[7] == 72) {
			return true;
		}
		else {
			return false;
		}
	case 'g':
		if (piecePosition[8] == 78 && piecePosition[9] == 78 && piecePosition[10] == 78 && piecePosition[11] == 78) {
			return true;
		}
		else {
			return false;
		}
	case 'y':
		if (piecePosition[12] == 84 && piecePosition[13] == 84 && piecePosition[14] == 84 && piecePosition[15] == 84) {
			return true;
		}
		else {
			return false;
		}
	}
}
void sorryCardActivation(char currentPlayerColor, int currentPieceNumber) { //Function for sorry card
	bool pieceInStart = false;
	bool pieceOnBoard = false;
	for (int x = 0; x < playerCount * 4; x++) {
		if (currentPlayerColor == playerColor(x)) {
			switch (currentPlayerColor) {
			case 'r':
				if (piecePosition[x] == -1) {
					pieceInStart = true;
				} break;
			case 'b':
				if (piecePosition[x] == -2) {
					pieceInStart = true;
				} break;
			case 'g':
				if (piecePosition[x] == -3) {
					pieceInStart = true;
				} break;
			case 'y':
				if (piecePosition[x] == -4) {
					pieceInStart = true;
				} break;
			}
		}
		if (currentPlayerColor != playerColor(x)) {
			switch (currentPlayerColor) {
			case 'r':
				if (piecePosition[x] >= 0 && piecePosition[x] <= 59) {
					pieceOnBoard = true;
				} break;
			case 'b':
				if (piecePosition[x] >= 0 && piecePosition[x] <= 59) {
					pieceOnBoard = true;
				} break;
			case 'g':
				if (piecePosition[x] >= 0 && piecePosition[x] <= 59) {
					pieceOnBoard = true;
				} break;
			case 'y':
				if (piecePosition[x] >= 0 && piecePosition[x] <= 59) {
					pieceOnBoard = true;
				} break;
			}
		}
	}
	if (pieceOnBoard == true && pieceInStart == true) {
		int currentClosestDistance = 999;
		int currentClosestPieceNum;
		for (int j = 0; j < playerCount * 4; j++) {
			if (currentPlayerColor != playerColor(j)) {
				if (piecePosition[j] >= 0 && piecePosition[j] <= 59) {
					int positionToTest;
					switch (currentPlayerColor) {
						case 'r':
							positionToTest = 59 - piecePosition[j];
							if (positionToTest >= 0) {
								if (positionToTest < currentClosestDistance) {
									currentClosestDistance = positionToTest;
									currentClosestPieceNum = j;
								}
							}
							if (positionToTest < 0 && currentClosestDistance < 0) {
								if (positionToTest < currentClosestDistance) {
									currentClosestDistance = positionToTest;
									currentClosestPieceNum = j;
								}
							}
							break;
						case 'b':
							positionToTest = 14 - piecePosition[j];
							if (positionToTest >= 0) {
								if (positionToTest < currentClosestDistance) {
									currentClosestDistance = positionToTest;
									currentClosestPieceNum = j;
								}
							}
							if (positionToTest < 0 && currentClosestDistance < 0) {
								if (positionToTest < currentClosestDistance) {
									currentClosestDistance = positionToTest;
									currentClosestPieceNum = j;
								}
							}
							break;
						case 'g':
							positionToTest = 29 - piecePosition[j];
							if (positionToTest >= 0) {
								if (positionToTest < currentClosestDistance) {
									currentClosestDistance = positionToTest;
									currentClosestPieceNum = j;
							}
							}
							if (positionToTest < 0 && currentClosestDistance < 0) {
								if (positionToTest < currentClosestDistance) {
									currentClosestDistance = positionToTest;
									currentClosestPieceNum = j;
								}
							}
							break;
						case 'y':
							positionToTest = 44 - piecePosition[j];
							if (positionToTest >= 0) {
								if (positionToTest < currentClosestDistance) {
									currentClosestDistance = positionToTest;
									currentClosestPieceNum = j;
								}
							}
							if (positionToTest < 0 && currentClosestDistance < 0) {
								if (positionToTest < currentClosestDistance) {
									currentClosestDistance = positionToTest;
									currentClosestPieceNum = j;
								}
							}
					}
				}
			}
		}
		piecePosition[currentPieceNumber] = piecePosition[currentClosestPieceNum];
		switch (playerColor(currentClosestPieceNum)) {
		case 'r':
			piecePosition[currentClosestPieceNum] = -1;
			break;
		case 'b':
			piecePosition[currentClosestPieceNum] = -2;
			break;
		case 'g':
			piecePosition[currentClosestPieceNum] = -3;
			break;
		case 'y':
			piecePosition[currentClosestPieceNum] = -4;
			break;
		}
	}
}
void swapPosition(char playerColorCheck) {
	bool intCheck = false;
	bool intCheck2 = false;
	int input = 0;
	int input2 = 0;
	do {
		std::cout << "What two would you like to swap? \nType any number (Your piece) from 1 to 16:\n1-Red 1, 2-Red 2, 3-Red 3, 4-Red 4                         5-Blue 1, 6-Blue 2, 7-Blue 3, 8-Blue 4\n";
		std::cout << "9-Green 1, 10-Green 2, 11-Green 3, 12-Green 4              13-Yellow 1, 14-Yellow 2, 15-Yellow 3, 16-Yellow 4\n";
		std::cin >> input;
		if ((input == 1 || input == 2 || input == 3 || input == 4 || input == 5 || input == 6 || input == 7 || input == 8 || input == 9 || input == 10 || input == 11 || input == 12 || input == 13 || input == 14 || input == 15 || input == 16)) {
			intCheck = true;
		}
		std::cin.clear();
		std::cin.ignore();
	} while (!(intCheck));
	do {
		std::cout << "What two would you like to swap? \nType any number (Any piece you wish to swap with) from 1 to 16:\n 1 - Red 1, 2 - Red 2, 3 - Red 3, 4 - Red 4                5-Blue 1, 6 - Blue 2, 7 - Blue 3, 8 - Blue 4\n";
		std::cout << "9-Green 1, 10-Green 2, 11-Green 3, 12-Green 4              13-Yellow 1, 14-Yellow 2, 15-Yellow 3, 16-Yellow 4\n";
		std::cin >> input2;
		if ((input2 == 1 || input2 == 2 || input2 == 3 || input2 == 4 || input2 == 5 || input2 == 6 || input2 == 7 || input2 == 8 || input2 == 9 || input2 == 10 || input2 == 11 || input2 == 12 || input2 == 13 || input2 == 14 || input2 == 15 || input2 == 16)) {
			intCheck2 = true;
		}
		std::cin.clear();
		std::cin.ignore();
	} while (!(intCheck2));
	input--;
	input2--;
	if (piecePosition[input] == -1 || piecePosition[input] == -2 || piecePosition[input] == -3 || piecePosition[input] == -4 || piecePosition[input2] == -1 || piecePosition[input2] == -2 || piecePosition[input2] == -3 || piecePosition[input2] == -4 || piecePosition[input2] > 59 || piecePosition[input] > 59) {
		std::cout << "Invalid Swap Detected!\n";
		return;
	}
	if (playerColor(input) != playerColorCheck) {
		std::cout << "Invalid Swap Detected!\n";
		return;
	}
	int tempNumStoring;
	tempNumStoring = piecePosition[input];
	piecePosition[input] = piecePosition[input2];
	piecePosition[input2] = tempNumStoring;
	return;
}
bool userSwapOrMove(char playerColorCheck) {
	bool intCheck = false;
	int input = 0;
	do {
		std::cout << "Would you like to swap? Type 1 for yes or 2 for no.\n";// 1, 2, 3 or 4!\n";
		std::cin >> input;
		if ((input == 1 || input == 2)) {
			intCheck = true;
		}
		std::cin.clear();
		std::cin.ignore();
	} while (!(intCheck));
	switch (input) {
	case 1:
		swapPosition(playerColorCheck);
		return true;
	case 2:
		return false;
	}
}

char gamePlayingFunction() {
	std::cout << "How many players?\n";
	std::cin >> playerCount;
	playerDataGenerator(playerCount);
	boardGenerator();
	char currentPlayingColor;
	do {
		//Draws the card
		//Takes input from user to allow the movement and decision of what piece to move
		int cardDrawn = cardDraw();
		bool didSwitch = false;
		currentPlayingColor = playerColorTurn(cardDrawn);
		std::cout << "\nYou drew a " << cardDrawn << std::endl;
		std::cout << "\nYour color is " << currentPlayingColor << std::endl;
		if (cardDrawn == 11) {
			didSwitch = userSwapOrMove(currentPlayingColor);
		}
		if (didSwitch == false) {
			playerMovement(playerMovementInput(currentPlayingColor), cardDrawn); //Will move pieces and checks for the kills and sliders
		}

		//This for loop is simply here to test the game and see if it is running or not
		//Will be deleted later

		for (int x = 0; x < playerCount * 4; x++) {
			if (x == 0) {
				std::cout << "Red : ";
			}
			else if (x == 4) {
				std::cout << "\nBlue : ";
				}
			else if (x == 8) {
				std::cout << "\nGreen : ";
			}
			else if (x == 12) {
				std::cout << "\nYellow : ";
			}
			std::cout << piecePosition[x] << ",   ";
		}
	} while (checkIfPlayerWon(currentPlayingColor) == false);
	return currentPlayingColor;
}

int main() { //main function
	//title screen could go here
	std::cout << "SORRY!" << std::endl;
		

	switch (gamePlayingFunction()) {
	case 'r':
		std::cout << "Red is the winner!" << std::endl;
		break;
	case 'b':
		std::cout << "Blue is the winner!" << std::endl;
		break;
	case 'g':
		std::cout << "Green is the winner!" << std::endl;
		break;
	case 'y':
		std::cout << "Yellow is the winner!" << std::endl;
		break;
	}
	system("pause");
	return 0;
}