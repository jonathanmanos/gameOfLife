/*
 * person.h - Implementation of person in the game of life
 * CPS222 Project 1
 *
 * Copyright (c) 2016 - Jonathan Manos
 *
 */

#include <iostream>
#include <cmath>
#include <string>



// Basic Constants

#define RODENT_DAILY_RATE 1
#define BIRD_DAILY_RATE 2

class Person
{


    public:
        Person(){}

        void setState(std::string s)
        {
            state = s;
        }

        std::string getState()
        {
            return state;
        }

    private:

      std::string state;

};

        // Accessor for ASCII code for ith individual character of the value

/*        int getCode(int i) const
        {
            return (int) _value[i];
        }
*/
