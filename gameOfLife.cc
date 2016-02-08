/*
 * gameOfLife.cc - Implementation of person in the game of life
 * CPS222 Project 1
 *
 * Copyright (c) 2016 - Jonathan Manos
 *
 */

#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include "person.h"

using std::cerr;
using std::cin;

//test value of deleting same node twice
int main(int argc, char * argv [])
{
  std::string input = "";

  while(input != "0")
  {


  // Set value to the string for new person
  std::cerr << "Please enter a state for the first person" <<
    " in your village (enter 0 to exit): \n" << std::endl;
  getline(cin, input);

	// Creates and initializes a new person with pointer.
      	Person * p = new Person();

        p -> setState(input);

	// Creates and initializes a new node with pointer.
  //    	Node * q = p;


	// Delete the node pointer.
	//delete p;
	//delete q;
bool nonZero = (input!="0");
bool validState = (input=="happy" || input=="sad");

	// Write out the person's state.
    if(validState && nonZero)
    {
		    std::cerr << "\nYour first villager is "
		      <<  p -> getState()  << ".\n" << std::endl;
    }
    else if(!validState && nonZero)
    {
      std::cerr << "\n" << p -> getState() << " is not a valid state"
        << ".\n" << std::endl;
    }
  }
}
