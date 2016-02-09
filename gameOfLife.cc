/*
* gameOfLife.cc - Implementation of the game of Life
* CPS222 Project 1
*
* Copyright (c) 2016 - Jonathan Manos, Alonzo Ouzts
*
*/

#include <iostream>
#include <string>
#include <sstream>

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



//Constants
static const int totalRows = 18;
static const int totalCols = 50;

//test value of deleting same node twice
int main(int argc, char * argv [])
{

  enum Organism {NONE, GESTATING, LIVING, DYING};

  Organism board[totalRows][totalCols];

  Organism currentOrganism;

  for (int i = 0; i < totalRows; i++)
  {
    for (int j = 0; j < totalCols; j++)
    {
      board[i][j] = NONE;
    }
  }

  std::stringstream st;

  // Set amount of organisms
  std::cerr << "\nHow many organisms initially? ";
  getline(cin, organismInput);
  st.str(organismInput);
  st >> amountOrganisms;
  st.clear();


    // Set locations of organisms
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

    board[locationRow-1][locationCol-1] = LIVING;
  }


  // Set value to the string for new person
  std::cerr << "\nGenerations? ";
  getline(cin, generationsInput);
  st.str(generationsInput);
  st >> amountGenerations;
  st.clear();

  std::cerr << "\n";



  for (int i = 0; i < totalCols; i++)
  {
    dashes.append("- ");
    if(i == totalCols-1)
    dashes.append("+");
  }


  for (int g = 0; g < amountGenerations + 1; g++)
  {

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
          {
            board[i][j] = LIVING;
          }
          if(board[i][j] == DYING)
          {
            board[i][j] = NONE;
          }
        }
      }
    }


    if(g!=0)
    {
      std::cout << "Generation "
      << g << ":" << std::endl;
    }

    for (int i = 0; i < totalRows; i++)
    {
      organismLine.append("| ");

      if(i==0)
      {
        std::cerr << dashes << std::endl;
      }

      for (int j = 0; j < totalCols; j++)
      {
        


          surroundingCounter+= (board[i-1][j-1] == LIVING || board[i-1][j-1] == DYING);
          surroundingCounter+= (board[i-1][j] == LIVING || board[i-1][j] == DYING);
          surroundingCounter+= (board[i-1][j+1] == LIVING || board[i-1][j+1] == DYING);
          surroundingCounter+= (board[i][j-1] == LIVING || board[i][j-1] == DYING);
          surroundingCounter+= (board[i][j+1] == LIVING || board[i][j+1] == DYING);
          surroundingCounter+= (board[i+1][j-1] == LIVING || board[i+1][j-1] == DYING);
          surroundingCounter+= (board[i+1][j] == LIVING || board[i+1][j] == DYING);
          surroundingCounter+= (board[i+1][j+1] == LIVING || board[i+1][j+1] == DYING);

          if((surroundingCounter < 2 || surroundingCounter > 3) && board[i][j] == LIVING)
          {
            board[i][j] = DYING;

          }
          if(surroundingCounter == 3 && board[i][j] == NONE)
          {
            board[i][j] = GESTATING;
          }
          surroundingCounter = 0;



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


      organismLine.append("|");
      std::cerr << organismLine << std::endl;
      organismLine = "";

      if(i == totalRows-1)
      {
        std::cerr << dashes << std::endl;
      }

    }

    if(g != amountGenerations)
    {
      std::cout << "Press RETURN to continue";
      while (cin.get() != '\n') ;
    }

  }
}
