#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

using namespace std;

#ifndef SHIP_H
#define SHIP_H

class Ship {
public:
  static const int lenGrid = 10;

private:
  int shipLength, shipColumn, shipRow, shipDirection;
  // 0123 is NESW respectively
  char firstLetterofShipName;

  static vector<int> takenColumns;
  static vector<int> takenRows;
  static int seed;

  bool locationFullShipTaken(int col, int row,
                             int dir) { // Can this potential ship go on the
                                        // board without intersecting anything?
    for (int i = 0; i < takenColumns.size(); ++i) { // for each existing spot

      switch (dir) {
      case 0:                                  // if north facing
        for (int j = 0; j < shipLength; ++j) { // for each ship loc
          if ((takenColumns[i] == col) && (takenRows[i] == row - j))
            return true;
        }
        break;

      case 1:                                  // if east facing
        for (int j = 0; j < shipLength; ++j) { // for each ship loc
          if ((takenColumns[i] == col - j) && (takenRows[i] == row))
            return true;
        }
        break;

      case 2:                                  // if south facing
        for (int j = 0; j < shipLength; ++j) { // for each ship loc
          if ((takenColumns[i] == col) && (takenRows[i] == row + j))
            return true;
        }
        break;

      case 3:                                  // if west facing
        for (int j = 0; j < shipLength; ++j) { // for each ship loc
          if ((takenColumns[i] == col + j) && (takenRows[i] == row))
            return true;
        }
        break;

      default:
        cout << "bad";
      }
    }
    return false;
  }

  bool locationUnexistent(int col, int row, int dir) {
    if (((dir == 0) &&
         (row + shipLength <= lenGrid)) // ship faces north and does not fit col
                                        // + shipLength <= lenGrid
        || ((dir == 2) &&
            (shipLength <= (row + 1))) // ship faces south and does not fit
        || ((dir == 1) &&
            (col + shipLength <= lenGrid)) // ship faces east and does not fit
        || ((dir == 3) &&
            (shipLength <= (col + 1))) // ship faces west and does not fit
    )
      return true;
    else
      return false;
  }

  void appendTakenSpots() {

    switch (shipDirection) {
    case 0: // if north facing
      for (int j = 0; j < shipLength; ++j) {
        takenColumns.push_back(shipColumn);
        takenRows.push_back(shipRow - j);
      }
      break;

    case 1: // if east facing
      for (int j = 0; j < shipLength; ++j) {
        takenColumns.push_back(shipColumn - j);
        takenRows.push_back(shipRow);
      }
      break;

    case 2: // if south facing
      for (int j = 0; j < shipLength; ++j) {
        takenColumns.push_back(shipColumn);
        takenRows.push_back(shipRow + j);
      }
      break;

    case 3: // if west facing
      for (int j = 0; j < shipLength; ++j) {
        takenColumns.push_back(shipColumn + j);
        takenRows.push_back(shipRow);
      }
      break;

    default:
      cout << "bad";
    }
  }

public:
  static void setSeed();

  // Constructor
  Ship(int len, char letter) {
    shipLength = len;
    firstLetterofShipName = letter;
  }

  int getColumn() { return shipColumn; }

  int getRow() { return shipRow; }

  int getDirection() { return shipDirection; }

  int getLength() { return shipLength; }

  char getLetter() { return firstLetterofShipName; }

  void placeShipRandomly() {

    int tempCol, tempRow, tempDir;

    do {

      do {
        tempCol = (rand() % lenGrid);
        tempRow = (rand() % lenGrid);
        tempDir = (rand() % 4);
      } while (locationUnexistent(tempCol, tempRow, tempDir));

    } while (locationFullShipTaken(tempCol, tempRow, tempDir));

    shipColumn = tempCol;
    shipRow = tempRow;
    shipDirection = tempDir;

    appendTakenSpots();
  }

  bool locationSingleSpotTaken(int col, int row) {
    for (int i = 0; i < takenColumns.size();
         ++i) { // for each existing correct spot
      if ((takenColumns[i] == col) &&
          (takenRows[i] == row)) { // does it match up with one?
        takenColumns[i] = -1;      // to indicate they have been found
        takenRows[i] = -1;
        return true;
      }
    }
    return false;
  }

  bool allShipsFound() {
    for (int i = 0; i < takenColumns.size();
         ++i) { // for each existing correct spot
      if (takenColumns[i] != -1 ||
          takenRows[i] != -1) // a spot has not been passed through
                              // locationSingleSpotTaken successfully
        return false;
    }
    return true;
  }
};

#endif