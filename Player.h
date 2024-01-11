#ifndef PLAYER_H
#define PLAYER_H

#include "GameMechs.h"
#include "objPos.h"
#include "objPosArrayList.h"



class Player
{

    public:
        enum Dir {UP, DOWN, LEFT, RIGHT, STOP};  // This is the direction state

        Player(GameMechs* thisGMRef);
        ~Player();

        void getPlayerPos(objPosArrayList &returnPosList); 
        void updatePlayerDir();
        void movePlayer();


        bool checkFoodConsumption();


        //bool checkFoodConsumption(Food food); // Modify to take a Food object and return a boolean
        //void consumeFood(Food food); // Add this method

        void increasePlayerLength();
        bool checkSelfCollision(objPos newHead);


        void getPlayerDir(Dir &returnDir);

        objPosArrayList* getPlayerPosList();









    private:      
        enum Dir myDir;
        bool hasEatenFood;

        // Need a reference to the Main Game Mechanisms
        GameMechs* mainGameMechsRef;


        objPos playerPos;
        objPosArrayList* playerPosList;


};

#endif