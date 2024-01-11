#ifndef GAMEMECHS_H
#define GAMEMECHS_H

#include <cstdlib>
#include <time.h>
#include <vector>

#include "objPos.h"
#include "objPosArrayList.h"
//#include "Food.h" //delete this later



using namespace std;


class GameMechs
{
    // Construct the remaining declaration from the project manual.

    // Only some sample members are included here

    // You will include more data members and member functions to complete your design.

    private:
        char input;
        bool exitFlag;
        
        int boardSizeX;
        int boardSizeY;

        int score;
        bool loseFlag;

        objPos foodPos;
        
        
        //vector<Food> foodBucket; // New member variable




    public:
        GameMechs();
        GameMechs(int boardX, int boardY);
        ~GameMechs();
        
        
        bool getExitFlagStatus();
        bool getLoseFlagStatus();
        void setLoseFlag();
        void setExitTrue();

        char getInput();
        void setInput(char this_input);
        void clearInput();

        int getBoardSizeX();
        int getBoardSizeY();

        int getScore();
        void incrementScore();

        void generateFood(objPos blockOff);
        void getFoodPos(objPos &returnPos);



        //Food generateFood(objPos blockOff); // Modify to return a Food object
        //vector<objPos> getFoodPos(); // Modify to return a vector of objPos objects
        //vector<Food> getFoodBucket(); // Uncomment this line
        //void fillBucket(objPos blockOff); // Uncomment this line
};

#endif