#include "Player.h"
#include "objPosArrayList.h"
#include "objPos.h"





Player::Player(GameMechs* thisGMRef)
{
    // initialize the player position
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    // initialize the player position
    playerPos.x = mainGameMechsRef->getBoardSizeX()/2;
    playerPos.y = mainGameMechsRef->getBoardSizeY()/2;

    
    // initialize the player position list
    playerPosList = new objPosArrayList();
    playerPosList->insertHead(playerPos);

    hasEatenFood = false;


}



Player::~Player()
{
    // delete any heap members here
    delete playerPosList;



}

void Player::getPlayerPos(objPosArrayList &returnPosList)
{
    // return the reference to the playerPos arrray list

    returnPosList = *playerPosList;
}



void Player::updatePlayerDir()
{
    // get the input from the main game mechanics
    char input = mainGameMechsRef->getInput();
    // PPA3 input processing logic      
    if(input != 0)  // if not null character
    {
        switch(input)
        {                      
            case ' ':  // exit
                mainGameMechsRef->setExitTrue();
                break;
            
            case 'w': // up
                if (myDir == LEFT || myDir == RIGHT || myDir == STOP){
                    myDir = UP;
                    
                }   
                break;

            case 'a': // left
                if (myDir == UP || myDir == DOWN || myDir == STOP){
                    myDir = LEFT;
                }   
                break;

            case 's': // down
                if (myDir == LEFT || myDir == RIGHT || myDir == STOP){
                    myDir = DOWN;
                }
                break;

            case 'd': // right
                if (myDir == UP || myDir == DOWN || myDir == STOP){
                    myDir = RIGHT;
                }
                break;
            
        }

        mainGameMechsRef->clearInput(); // clear the input

    }



}


void Player::movePlayer() {
    objPos newHead; // Create an objPos object to store the new head position
    
    playerPosList->getHeadElement(newHead); // Get the current head position and store in newHead


    // Calculate new position based on the direction of the snake
    switch (myDir) {

            case UP: 
                newHead.y = (newHead.y - 1 + mainGameMechsRef->getBoardSizeY() - 2) % (mainGameMechsRef->getBoardSizeY() - 2);
                break;
            case DOWN:
                newHead.y = (newHead.y + 1) % (mainGameMechsRef->getBoardSizeY() - 2);
                break;
            case LEFT:
                newHead.x = (newHead.x - 1 + mainGameMechsRef->getBoardSizeX() - 2) % (mainGameMechsRef->getBoardSizeX() - 2);
                break;
            case RIGHT:
                newHead.x = (newHead.x + 1) % (mainGameMechsRef->getBoardSizeX() - 2);
                break;
            default:
                break;
        }

    // Adjusting position if snake head goes over the border
    if (newHead.x <= 0) newHead.x += (mainGameMechsRef->getBoardSizeX() - 2);
    if (newHead.y <= 0) newHead.y += (mainGameMechsRef->getBoardSizeY() - 2);

    // Check if the new position is valid
    if (checkSelfCollision(newHead)) {
        mainGameMechsRef->setLoseFlag();
        return;
    }

    // Update the player position list
    playerPosList->insertHead(newHead);


    // Check if the player has eaten food
    if (!hasEatenFood) {
        playerPosList->removeTail();
    } else {
        hasEatenFood = false; // Reset the flag after growing
    }

}


void Player::getPlayerDir(Dir &returnDir)
{
    // return the reference to the playerPos arrray list
    returnDir = myDir;

}


bool Player::checkFoodConsumption() 
{
    // Check if the player has eaten food and update the flag
    objPos foodPos;
    mainGameMechsRef->getFoodPos(foodPos);
    objPos headPos;
    playerPosList->getObjPos(0, headPos);

    return (headPos.x == foodPos.x && headPos.y == foodPos.y); // Return true if the player has eaten food
}



bool Player::checkSelfCollision(objPos newHead)
{
    // Check if the new head position is colliding with the player body
    for (int i = 1; i < playerPosList->getSize(); i++) {
        objPos checkPos;
        playerPosList->getObjPos(i, checkPos);
        if (newHead.x == checkPos.x && newHead.y == checkPos.y) {
            return true;
        }
    }
    return false;
}
void Player::increasePlayerLength()
{
    objPos tempPos;

    playerPosList->getObjPos(playerPosList->getSize() - 1, tempPos);

    // Calculate new position based on the direction of the snake
    switch (myDir){
        case LEFT:
            tempPos.y -= 1;
            break;
        case RIGHT:
            tempPos.y += 1;
            break;
        case UP:
            tempPos.x -= 1;
            break;
        case DOWN:
            tempPos.x += 1;
            break;
        default:
            break;
    }

    // Check if the new position is valid
    if (tempPos.x < 0 || tempPos.x >= mainGameMechsRef->getBoardSizeX() || tempPos.y < 0 || tempPos.y >= mainGameMechsRef->getBoardSizeY()) {
        // The new position is out of the board
        return;
    }
    // Check if the new position is colliding with the player body
    for (int i = 0; i < playerPosList->getSize(); i++) {
        objPos checkPos;
        playerPosList->getObjPos(i, checkPos);
        if (tempPos.x == checkPos.x && tempPos.y == checkPos.y) {
            return;
        }
    }

    playerPosList->insertTail(tempPos);


}



objPosArrayList* Player::getPlayerPosList()
{
    return playerPosList;
}
