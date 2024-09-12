// Natalie Forte

#include "board.h"
#include "ship.h"
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>

using namespace std;

void introducePlayer();

const int amtShips = 5;

int main() {
  introducePlayer();

  Ship::setSeed();
  Ship battleShips[amtShips] = {Ship(2, 'F'), Ship(3, 'S'), Ship(3, 'D'),
                                Ship(4, 'B'), Ship(5, 'A')};

  for (int i = 0; i < amtShips; i++) {
    battleShips[i].placeShipRandomly();
  }

  Board myBoard(battleShips, amtShips);
  bool gameWon = false;

  while (Board::missedShots < 15 && !Board::sentinelCalled && !gameWon) {
    if (Board::missedShots >= 10)
      cout << "\nWarning: You have missed 10 or more times in a row. Your enemy is getting closer to you. Be careful.\n";
    else if (Board::missedShots >= 5)
      cout << "\nHave caution. 5 or more missed shots in a row.\n";
    cout << right << setw(35) << "Missing streak: " << Board::missedShots
         << endl;
    myBoard.drawBoard();
    myBoard.guessPlace(battleShips);
    gameWon = battleShips[0].allShipsFound();
  };

  if (gameWon) {
    myBoard.drawBoard();
    cout << "\nAll enemy ships have been successfully located. You have won battleship.";
  } else if (Board::missedShots == 15) {
    cout << endl;
    myBoard.drawBoard();
    cout << "\nUnfortunately, your shots have missed 15 times in a row. Time has run out, and your enemy closes in on you. Game over.";
  } else
    cout << "\nYour troops retreat. Play again soon.";

  return 0;
}

vector<int> Ship::takenColumns;
vector<int> Ship::takenRows;

int Ship::seed = 0;

void Ship::setSeed() {
  seed = time(0);
  srand(seed);
}

int Board::missedShots = 0;
bool Board::sentinelCalled = false;
vector<int> Board::guessedColumns;
vector<int> Board::guessedRows;

void introducePlayer() {
  cout << "Welcome to Battleship!\n";
  int choice = 0;

  while (choice != 1) {
    cout << "Input '1' to begin, '2' for the rules, or '3' for credits.\n";
    cin >> choice;
    switch (choice) {
    case 1:
      cout << "\nThe U.S.S. John Paul Jones is alone out at sea.\n\nHowever, "
              "you know the enemy is approaching beyond your sight.\n\n";
      break;
    case 2:
      cout << "\nYou transform into a commander, leading the U.S.S. John Paul Jones. Your goal is to locate all five of the enemy ships. \n\nHowever, an issue arises. The satellites are unresponsive, leading your crew to rely on sonar. \n\nHere are your enemy's ships: \naircraft carrier (length 5)\ndestroyer (length 3)\nbattleship (length 4)\nsubmarine (length 3)\nfrigate (length 2)\n\nEach shot, the sonar register informs you if the shot hit ('X') or missed ('O'). \n\nIf you, the commander, guesses incorrectly times in a row, the enemy locates your U.S.S. John Paul Jones and the game is lost.\n\nIf you are not up to the challenge, use '-1' to retreat. Good luck. \n\n";
      break;
    case 3:
      cout << "\nThe original Battleship concept was created by Milton Bradley.\n\n";
      cout << "This program was created by Natalie Forte, for Professor Stevens' Spring 2024 CSIS-297-0505\n\n";
      break;
    default:
      cout << "Invalid input. Please try again, entering '1', '2', or '3'.\n\n";
      break;
    }
  }
}