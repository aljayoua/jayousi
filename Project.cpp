#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "objPosArrayList.h"
#include "GameMechs.h"
#include "Player.h"
//#include "Food.h"



using namespace std;

#define DELAY_CONST 100000

bool exitFlag;
char input;

GameMechs* gameMechs;
Player* player;
objPos foodPos;
objPosArrayList playerPosList;

//Food* food;










void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);
void PrintEndGameScreen(void);



int main(void)
{

    Initialize();

    while(gameMechs->getExitFlagStatus() == false)  
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();

}


void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();


    exitFlag = false;
    
    input = ' ';
    gameMechs = new GameMechs(30, 15);
    player = new Player(gameMechs);


    srand(time(NULL));

    objPosArrayList* playerBody = player->getPlayerPosList();
    objPos headPos;

    //playerBody->insertHead(headPos);
    

    gameMechs->generateFood(headPos);


    
    




}

void GetInput(void)
{
    gameMechs->getInput();

}

void RunLogic(void)
{

    //check if player has eaten food
    objPosArrayList* playerBody = player->getPlayerPosList();
    objPos headPos;

    playerBody->getElement(headPos, 0);
    if(player->checkFoodConsumption()) {
        gameMechs->incrementScore();
        gameMechs->generateFood(headPos);
        player->increasePlayerLength();
    }

    player->updatePlayerDir();
    player->movePlayer();

    //check if player has collided with itself

    objPos newHead;
    playerBody->getElement(newHead, 0);

    
    if(player->checkSelfCollision(newHead)) {
        gameMechs->setLoseFlag();
        gameMechs->setExitTrue();
        return;
    }

}


void DrawScreen(void) {

    MacUILib_clearScreen();

    objPosArrayList* playerBody = player->getPlayerPosList();
    objPos foodPos;
    gameMechs->getFoodPos(foodPos);

    for (int i = 0; i < gameMechs->getBoardSizeY(); i++) {
        for (int j = 0; j < gameMechs->getBoardSizeX(); j++) {

            bool drawn = false;

            // Debugging: Print each segment's position
            for (int k = 0; k < playerBody->getSize(); k++) {
                objPos segment;
                playerBody->getElement(segment, k);

                if (j == segment.x && i == segment.y) {
                    //MacUILib_printf("%c", segment.symbol);
                    MacUILib_printf("@");
                    drawn = true;
                    break;
                }

            }

            if (drawn) continue;

            // Draw the walls
            if (i == 0 || i == gameMechs->getBoardSizeY() - 1 || j == 0 || j == gameMechs->getBoardSizeX() - 1) {
                MacUILib_printf("#");
            }
            // Draw the food
            else if (j == foodPos.x && i == foodPos.y) {
                MacUILib_printf("F");
            }
            // Draw empty space
            else {
                MacUILib_printf(" ");
            }

        }
        switch (i){

                case 1:
                    MacUILib_printf("\t\t\tInstructions:");
                    break;

                case 2:
                    MacUILib_printf("\t|~ Use WASD keys to move the snake head around the board");
                    break;    

                case 3:
                    MacUILib_printf("\t|~ The snake will follow the head and can only move in 4 directions");
                    break;

                case 4:
                    MacUILib_printf("\t|~ The snake cannot pass through itself");
                    break;

                case 5:
                    MacUILib_printf("\t|~ Press SPACE to exit");
                    break;
                
                case 6:
                    MacUILib_printf("\t| Have fun! (plz give us 100)");
                    break;
                case 7:
                    MacUILib_printf("\t|");
                    break;
                case 8:
                    MacUILib_printf("\t|-------------- Game Stats: ----------------");
                    break;
                case 9:
                    MacUILib_printf("\t|");
                    break;

                case 10:
                    MacUILib_printf("\t|Player Score: %d", gameMechs->getScore());
                    break;
                case 11:
                    MacUILib_printf("\t|");
                    break;  

                case 12:
                    MacUILib_printf("\t|Food Location: (%d, %d)", foodPos.x, foodPos.y);
                    break;
                case 13:
                    MacUILib_printf("\t|");
                    break;

                case 14:
                    MacUILib_printf("\t © Made by: Yazan Qwasmi and Abdullah Al-Jayousi");

                    
                    break;

                default:
                    break;
        }
        MacUILib_printf("\n");
    }   
    
    

    if(gameMechs->getLoseFlagStatus() == true){
        PrintEndGameScreen();
        gameMechs->setExitTrue();
    }

    
      
}


void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();    
  
    MacUILib_uninit();

    delete gameMechs;

    delete player;



}

void PrintEndGameScreen(void){
    MacUILib_clearScreen();
    int k;

    for(k=0; k<3; k++){ 
            MacUILib_printf("----------------------------------------\n");
            MacUILib_printf("\\   .       \t\t\t.       /\n");
            MacUILib_printf("/\t    .      \t\t\t\\\n");
            MacUILib_printf("\\      . \t\t\t\t/\n");
            MacUILib_printf("/\t\t\t\t      . \\\n");
            MacUILib_printf("\\\t\tYOU LOSE!   .    \t/\n");
            MacUILib_printf("/\t      Final Score: %d\t\t\\\n", gameMechs->getScore());
            MacUILib_printf("\\\t\t\t\t   .    /\n");
            MacUILib_printf("/       .\t\t\t  .     \\\n");
            MacUILib_printf("\\ .      \t\t.          \t/\n");
            MacUILib_printf("----------------------------------------\n");
            
            MacUILib_Delay(1000000);
            MacUILib_clearScreen();
            MacUILib_printf("----------------------------------------\n");
            MacUILib_printf("/\t\t\t.          \t\\\n");
            MacUILib_printf("\\   .       \t\t\t\t/\n");
            MacUILib_printf("/\t\t\t\t      . \\\n");
            MacUILib_printf("\\\t  .        \t\t\t/\n");
            MacUILib_printf("/\t\tYOU LOSE!\t.       \\\n");
            MacUILib_printf("\\\t      Final Score: %d\t\t/\n", gameMechs->getScore());
            MacUILib_printf("/\t\t\t  .        \t\\\n");
            MacUILib_printf("\\     .     \t\t\t\t/\n");
            MacUILib_printf("/    .      \t\t\t   .    \\\n");
            MacUILib_printf("----------------------------------------\n");

            MacUILib_Delay(1000000);
            MacUILib_clearScreen();

        }

  





}



