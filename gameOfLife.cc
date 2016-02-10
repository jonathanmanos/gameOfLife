/*
* gameOfLife.cc - Implementation of the game of Life
* CPS222 Project 1
*
* Copyright (c) 2016 - Jonathan Manos, Alonzo Ouzts
*
*/

//include statements
#include <iostream>
#include <string>
#include <sstream>

//using cerr and cin
using std::cerr;
using std::cin;

//Global variables
std::string organismInput = "";
std::string locationInputRow = "";
std::string locationInputCol = "";
std::string generationsInput = "";
std::string dashes = "+ ";
std::string organismLine = "";
int locationRow = 0;
int locationCol = 0;
int amountGenerations = 0;
int amountOrganisms = 0;
int surroundingCounter = 0;

//Constants that set the board size
static const int totalRows = 18;
static const int totalCols = 50;

//main function of the game of life program
int main(int argc, char * argv [])
{
  //enum for an Organism so Organism doesn't need to be an object
  enum Organism {NONE, GESTATING, LIVING, DYING};

  //makes a board of organisms with constants totalRows and totalCols
  Organism board[totalRows][totalCols];

  //sets all the organisms on the board to NONE
  for (int i = 0; i < totalRows; i++)
  {
    for (int j = 0; j < totalCols; j++)
    {
      board[i][j] = NONE;
    }
  }

  //creates the stringstream object
  std::stringstream st;

  // Set amount of organisms from user input
  std::cerr << "\nHow many organisms initially? ";
  getline(cin, organismInput);
  st.str(organismInput);
  st >> amountOrganisms;
  st.clear();


  // Set locations of organisms from user input
  for(int i = 0; i < amountOrganisms; i++)
  {
    std::cerr << "\nLocation of organism " << i+1 << " is on row? ";
    getline(cin, locationInputRow);
    st.str(locationInputRow);
    st >> locationRow;
    st.clear();

    std::cerr << "\nLocation of organism " << i+1 << " is on column? ";
    getline(cin, locationInputCol);
    st.str(locationInputCol);
    st >> locationCol;
    st.clear();

    // set organism at that location to LIVING
    board[locationRow-1][locationCol-1] = LIVING;
  }


  // Set amount of generations from user input
  std::cerr << "\nGenerations? ";
  getline(cin, generationsInput);
  st.str(generationsInput);
  st >> amountGenerations;
  st.clear();

  //skip a line
  std::cerr << "\n";

  //create the string for the top and bottom border of the game
  for (int i = 0; i < totalCols; i++)
  {
    dashes.append("- ");
    if(i == totalCols-1)
    dashes.append("+");
  }

  //generation loop for the game to go through multiple generations
  for (int g = 0; g < amountGenerations + 1; g++)
  {
    //shows the board as initial before generations happen
    if(g==0)
    {
      std::cout << "Initial:" << std::endl;
    }

    //if person is GESTATING at start of generation they are now LIVING
    //if person is DYING at start of generation they are now NONE
    if(g!=0)
    {
      for (int i = 0; i < totalRows; i++)
      {
        for (int j = 0; j < totalCols; j++)
        {
          if(board[i][j] == GESTATING)
          board[i][j] = LIVING;
          if(board[i][j] == DYING)
          board[i][j] = NONE;
        }
      }
    }

    //shows the generation above the game board
    if(g!=0)
    {
      std::cout << "Generation "
      << g << ":" << std::endl;
    }
    //goes through each row of the game board
    for (int i = 0; i < totalRows; i++)
    {
      //makes the left border
      organismLine.append("| ");

      //makes the top border
      if(i==0)
      {
        std::cerr << dashes << std::endl;
      }

      //goes through each spot on the row of the game board
      for (int j = 0; j < totalCols; j++)
      {
        //game logic, checks surrounding organisms of a space and
        //adds to a counter, checks boundaries so organisms on
        //border do not go out of bounds.
        if(i-1 >= 0 && j-1 >=0)
        surroundingCounter+= (board[i-1][j-1] == LIVING || board[i-1][j-1] == DYING);
        if(i-1 >= 0)
        surroundingCounter+= (board[i-1][j] == LIVING || board[i-1][j] == DYING);
        if(i-1 >= 0 && j+1 < totalCols)
        surroundingCounter+= (board[i-1][j+1] == LIVING || board[i-1][j+1] == DYING);
        if(j-1 >= 0)
        surroundingCounter+= (board[i][j-1] == LIVING || board[i][j-1] == DYING);
        if(j+1 < totalCols)
        surroundingCounter+= (board[i][j+1] == LIVING || board[i][j+1] == DYING);
        if(i+1 <totalRows && j-1 >= 0)
        surroundingCounter+= (board[i+1][j-1] == LIVING || board[i+1][j-1] == DYING);
        if(i+1 < totalRows)
        surroundingCounter+= (board[i+1][j] == LIVING || board[i+1][j] == DYING);
        if(i+1 < totalRows && j+1 < totalCols)
        surroundingCounter+= (board[i+1][j+1] == LIVING || board[i+1][j+1] == DYING);

        //if a living organism is not surrounded by 2 or 3 organisms it dies
        if((surroundingCounter < 2 || surroundingCounter > 3) && board[i][j] == LIVING)
        {
          board[i][j] = DYING;
        }
        //if an empty space is surrounded by exactly 3 organisms a new child
        //is born
        if(surroundingCounter == 3 && board[i][j] == NONE)
        {
          board[i][j] = GESTATING;
        }
        //set the space counter back to 0 for the next space
        surroundingCounter = 0;


        //adds emptiness to the space if the space is nonliving
        //adds A to the space if the space is living or dying
        if(board[i][j] == NONE)
        {
          organismLine.append("  ");
          //std::cout << "NONE";
        }
        else if(board[i][j] == LIVING)
        {
          organismLine.append("A ");
          //std::cout << "LIVING";
        }
        else if(board[i][j] == GESTATING)
        {
          organismLine.append("  ");
        }
        else if(board[i][j] == DYING)
        {
          organismLine.append("A ");
        }
      }

      //makes the right border
      organismLine.append("|");
      //prints the string containing the full row of the game
      std::cerr << organismLine << std::endl;
      //sets the string for a row back to nothing
      organismLine = "";

      //if it is the final row, prints the bottom border
      if(i == totalRows-1)
      {
        std::cerr << dashes << std::endl;
      }
    }

    //asks for user to press return to see the next generation display
    if(g != amountGenerations)
    {
      std::cout << "Press RETURN to continue";
      while (cin.get() != '\n') ;
    }

  }
}
