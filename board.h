#include "ship.h"
#include <iomanip>
#include <iostream>

using namespace std;

#ifndef BOARD_H
#define BOARD_H

class Board {
private:
  string boardArr[Ship::lenGrid][Ship::lenGrid];
  static vector<int> guessedColumns;
  static vector<int> guessedRows;

  bool locationAlreadyGuessed(int col, int row) {
    for (int i = 0; i < guessedColumns.size(); ++i) { // for each existing guess
      if ((guessedColumns[i] == col) &&
          (guessedRows[i] == row)) // does it match up with one?
        return true;
    }
    return false;
  }

public:
  static int missedShots;
  static bool sentinelCalled;

  Board(Ship shipArr[], int lenShipArr) { // Constructor to set up board

    for (int r = 0; r < Ship::lenGrid; r++) {
      for (int c = 0; c < Ship::lenGrid; c++)
        boardArr[r][c] = "[ ]";
    }

    //Make ships visible for testing
    // for (int i = 0; i < lenShipArr; i++) { // for each ship
    //   switch (shipArr[i].getDirection()) {
    //   case 0:                                            // if north
    //     for (int j = 0; j < shipArr[i].getLength(); j++) // for each quad
    //       boardArr[shipArr[i].getRow() - j][shipArr[i].getColumn()] =
    //           string("[") + shipArr[i].getLetter() + "]";
    //     break;

    //   case 1:                                            // if east
    //     for (int j = 0; j < shipArr[i].getLength(); j++) // for each quad
    //       boardArr[shipArr[i].getRow()][shipArr[i].getColumn() - j] =
    //           string("[") + shipArr[i].getLetter() + "]";
    //     break;

    //   case 2:                                            // if south
    //     for (int j = 0; j < shipArr[i].getLength(); j++) // for each quad
    //       boardArr[shipArr[i].getRow() + j][shipArr[i].getColumn()] =
    //           string("[") + shipArr[i].getLetter() + "]";
    //     break;

    //   case 3:                                            // if west
    //     for (int j = 0; j < shipArr[i].getLength(); j++) // for each quad
    //       boardArr[shipArr[i].getRow()][shipArr[i].getColumn() + j] =
    //           string("[") + shipArr[i].getLetter() + "]";
    //     break;

    //   default:
    //     cout << "issue";
    //   }
    // }
    // Comment all above
  }

  void drawBoard() {
    cout << "     A  B  C  D  E  F  G  H  I  J\n";

    for (int r = 0; r < Ship::lenGrid; r++) {

      cout << right << setw(3) << r + 1 << " ";

      for (int c = 0; c < Ship::lenGrid; c++) {
        cout << boardArr[r][c];
      }

      cout << " ~";

          cout
           << endl;
    }

    cout << "     ~  ~  ~  ~  ~  ~  ~  ~  ~  ~\n";
  }

  void guessPlace(Ship shipArr[]) {
    string fullGuess;
    int guessedCol;
    int guessedRow;
    bool validGuess = true;
    bool newGuess = true;

    do {
      newGuess = true;
      do {
        do {
          do {
            if (cin.fail() || !validGuess) {
              cout << "Invalid guess. Please try again. Enter a coordinate; A "
                      "capital letter from 'A' and 'J', then a number from 1 "
                      "and "
                      "10, such as B5 or J2.\n";
              cin.clear();
              cin.ignore(10000, '\n');
            }
            cout << "\nGuess a position on the board (ex: A4): \n";
            cin >> fullGuess;
          } while (cin.fail());

          if (fullGuess == "-1") {
            sentinelCalled = true;
            return;
          } else if (fullGuess.length() == 2) {
            if (!isalpha(fullGuess[0]) || !isdigit(fullGuess[1])) {
              validGuess = false;
            } else
              validGuess = true;
          } else if (fullGuess.length() == 3) {
            if (!isalpha(fullGuess[0]) || !isdigit(fullGuess[1]) ||
                !isdigit(fullGuess[2])) {
              validGuess = false;
            } else
              validGuess = true;
          } else
            validGuess = false;
        } while (!validGuess);

        guessedCol = fullGuess[0] - 'A'; // for ascii
        guessedRow = stoi(fullGuess.substr(1)) - 1;

        if (guessedRow < 0 || guessedRow > 9 || guessedCol < 0 ||
            guessedCol > 9) {
          cout << "Please enter a a capital letter from 'A' and 'J', then a "
                  "number "
                  "from 1 and 10.\n";
        }
      } while (guessedRow < 0 || guessedRow > 9 || guessedCol < 0 ||
               guessedCol > 9);

      if (locationAlreadyGuessed(guessedCol, guessedRow)) {
        cout << "You have already guessed this spot.\n";
        newGuess = false;
      } else {
        if (shipArr[0].locationSingleSpotTaken(guessedCol, guessedRow)) {
          boardArr[guessedRow][guessedCol] = "[X]";
          cout << "\nA part of a ship has been detected at this location!\n";
          missedShots = 0; // resets the missing streak
        } else {
          boardArr[guessedRow][guessedCol] = "[O]";
          cout << "\nNothing's there...\n";
          missedShots += 1;
        }

        guessedColumns.push_back(guessedCol);
        guessedRows.push_back(guessedRow);
      }
    } while (!newGuess);
  }
};

#endif