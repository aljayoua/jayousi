#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "MacUILib.h"


//************** declarations *****************
struct objPos
{
    int x;		// x-coordinate of an object
    int y;		// y-coordinate of an object
    char symbol;	// The ASCII symbol of the object to be drawn on the screen
};


const int mystry = 12;




// ************ Random Number Generator ****************
int myrand(int max)
{
    int rnd = 0;

    while(1){
        rnd = rand() % max;
        if (rnd != 0) break;
    }
    return rnd;
}


// ************ Mystry String Initializer ****************
void generateMS(char *mystryStr)
{

    for (int i=0; i < mystry; i++){

        *(mystryStr + i) = '?';
    }

    *(mystryStr + mystry) = '\0'; // NULL

}

// ************ Item Bin X-Y Generator ****************
void initIB(struct objPos list[], const int listSize)
{
    for (int i = 0; i < listSize; i++)
    {
        (list + i)->x = 0;
        (list + i)->y = 0;
        (list + i)->symbol = ' ';
    }
}


// ************ Item Bin X-Y Generator ****************
void GenerateItemsXY(struct objPos *playerObj, struct objPos list[], const int listSize, const int xRange, const int yRange)
{
    int i, j, x, y, tag;

    i = 0;

    while (i < listSize)
    {
        x = myrand(xRange - 1);  // returns a value between 1 and 18
        y = myrand(yRange - 1);     // returns a value between 1 and 8

        if (!(x == playerObj->x && y == playerObj->y)) // make sure that generated x,y are not overlaping with player location
        {
            for (j=0; j < i; j++)
            {
                if (x == (list + j)->x && y == (list + j)->y) 
                {
                    break; // generated x,y overlaps with list x,y
                }
            }

            if (i == j)  // if i = j then no overlap found
            {
                (list + i)->x = x;  // assign the x value to the item
                (list + i)->y = y;  // assign the y value to the item
                i++; // get next item x-y coordinates
            }
        }

    }
}

// ************ Item Bin SYMBOL Generator ****************

void GenerateItemsSYM(struct objPos list[], const int listSize, const char* str)
{

    int i, j, sym, tag;

    i = 0;
    while (i < listSize)
    {

        tag = 1;

        sym = rand() % mystry; // returns a value between 0 and 11

        for(j = 0; j < i; j++)
        {

            if ((str[sym] == (list + j)->symbol))
            {
                break; // overlap found
            }
        }

        if (i == j) // no overlap found
        {
            (list + i)->symbol = str[sym];

            i++; // get next item symbol
        }

    }

}

// ************ Item List Generator ****************
void GenerateItems(struct objPos *playerObj, struct objPos list[], const int listSize, const int xRange, const int yRange, const char* str, char * mystryStr)
{
    int i, j, cntr;

    initIB(list, listSize);

    srand(time(NULL)); // seed with time()

    GenerateItemsXY(playerObj, list, listSize, xRange, yRange);

    while (1)
    {
        GenerateItemsSYM(list, listSize, str);

        cntr = 0;

        for(i = 0; i < listSize; i++) //count how many matches between new item list symbols and mystry string
        {
            for(j = 0; j < mystry; j++)
            {
                if((list+i)->symbol == mystryStr[j])
                {
                    cntr++; // symbol is already revealed
                }
            }
        }

        if (cntr < listSize) // if true, then there is at least one symbol that is not revealed yet
        {
            break; //break the while loop 
        }
    }

}


// ************ Display Game Board ****************
void drawscreen(int counter, struct objPos *playerObj, struct objPos list[], const int listSize, const int xRange, const int yRange, char *mystryStr)
{
    int tag;

    MacUILib_clearScreen();

    MacUILib_printf("\n####################\n");

    for(int y = 1; y < (yRange - 1); y++)
    {
        MacUILib_printf("#"); // print left border

        for(int x = 1; x < (xRange-1); x++)
        {
            tag = 1;

            if(x == playerObj->x && y == playerObj->y)
            {
                MacUILib_printf("%c", playerObj->symbol);
                tag = 0; // don't print a space at x,y
            }
            
            else // check list locations
            {

                for(int k=0; k < listSize; k++)
                {
                    if(x == (list+k)->x && y == (list+k)->y)
                    {
                        MacUILib_printf("%c", (list+k)->symbol);
                        tag = 0; // don't print a space at x,y
                    }
                }

            }

            if(tag)
            {
                
                MacUILib_printf(" "); // print a space at x,y
            }
        }

        MacUILib_printf("#\n"); // print right border
    }

    MacUILib_printf("####################\n"); // print bottom border

    MacUILib_printf("Mystry String: %s", mystryStr);
    MacUILib_printf("\nMove Count %d\n", counter);
}


// ************ Calculate New Player Location ****************
void playerloc(struct objPos *playerObj, char *input, char *direction, int *exit)
{
    // [TODO] : First, process the input by mapping
    //          WASD to the corresponding change in player object movement direction

    if(*input != 0)  // if not null character
    {
        switch(*input)
        {                      
            case ' ':  // exit
                *exit = 1;
                break;

            // Add more key processing here
            case 'w':
       
            case 's':
                if(*direction != 's' && *direction != 'w' )
                {
                    *direction = *input;
                }
                break;
            
            case 'd':
  
            case 'a':
                if(*direction != 'a' && *direction != 'd' )
                {
                    *direction = *input;
                }
                break;
                 
            default:
                break;
        }

        *input = 0;
    }
 
        switch(*direction){

            case 'w':
                playerObj->y -=1;
                if(playerObj->y == 0)
                {
                    playerObj->y = 8;
                }
                break;

            case 's':
                playerObj->y +=1;
                if(playerObj->y == 9)
                {
                    playerObj->y = 1;
                }
                break;

            case 'a':
                playerObj->x -=1;
                if(playerObj->x == 0)
                {
                    playerObj->x = 18;
                }
                break;
         
            case 'd':
                playerObj->x +=1;
                if(playerObj->x == 19)
                {
                    playerObj->x = 1;

                }
                break;

                default:
                break;
     }


    // [TODO] : Next, you need to update the player location by 1 unit 
    //          in the direction stored in the program

    // [TODO] : Heed the border wraparound!!!

}



void runlogic(struct objPos *playerObj, struct objPos list[], int *exitFlag, const int listSize, const int xRange, const int yRange, const char* str, char * mystryStr)
{

int i, j;

    for (i = 0; i < listSize; i++)  // check for overlap
    {
        if ( (*playerObj).x == (list + i)->x && (*playerObj).y == (list + i)->y)
        {
            break; // found a match
        }
    }

    if (i == listSize) // no overlap
    {
        return;
    }
    else // there is overlap
    {
        for (j = 0; j < mystry; j++)  // see if the symbol is already revealed
        {
            if (mystryStr[j] == (list + i)->symbol)
            {
                return; // symbol already revealed
            }
        }
    }

    for (j = 0; j < mystry; j++) // add new symbol to mystry string
    {
        if ((list + i)->symbol == str[j])
        {
            mystryStr[j] = str[j];
        }
    }

    for (j = 0; j < mystry; j++)  // see if the mystry string is completed
    {
        if (mystryStr[j] == '?')
        {
            // symbol ? found
            GenerateItems(playerObj, list, listSize, xRange, yRange, str, mystryStr); //generate a new distribution
            return; 
        }
    }
                
    if (j == mystry) // mystry string is completed. exist game
    {
        *exitFlag = 2; // Game Completed
        return;
    }

}
        



// ************ Read User Input ****************

void GetInput(char *inchar)
{
    // [TODO] : Implement Asynchronous Input - non blocking character read-in    
    //          (Same as PPA1)
if(MacUILib_hasChar() != 0){
        *inchar = MacUILib_getChar();
 
    }


}

// INITIALIZATION ROUTINE
// ===============================
void Initialize(void)
{
    MacUILib_init();

    MacUILib_clearScreen();

    // [COPY AND PASTE FROM PPA2] Copy your initialization routine from PPA2 and paste them below

    
    // [TODO] Initialize any global variables as required.
    //exitFlag = 0;  // 0 - do not exit, non-zero - exit the program

    
    // [TODO] Allocated heap memory for on-demand variables as required.  Initialize them as required.

    // [TODO] Seed the random integer generation function with current time.

    // [TODO] Generate the initial random items on the game board at the start of the game.

    
}


// DELAY ROUTINE
// ===============================
void LoopDelay(void)
{
    MacUILib_Delay(200000); // 0.1s delay
}

// cleanup routine

void CleanUp(void)
{
    // [TODO]   To prevent memory leak, free() any allocated heap memory here
    //          Based on the PPA3 requirements, you need to at least deallocate one heap variable here.

    // Insert any additional end-game actions here.
    

    MacUILib_uninit();
}


// ******************************************
//                MAIN
// ******************************************
int main(void){

   
    struct objPos *list;  // declare objects list
    struct objPos playerObj = {8, 4, '@'}; // declare playerObj object

    const int listSize = 5;
    const int xRange = 20; // this is the x-axis (x values)
    const int yRange = 10; // this is the y-axix (y values)
    const char goalString[] = "McMaster-ECE";

    int counter = 0;
    char input = 0;
    int exitFlag = 0;
    char direction = 'w';
    char *mystryString;

  

    mystryString = (char *) malloc((mystry+1) * sizeof(char));     // Allocate mystry string memory space
    list = (struct objPos*) malloc(listSize * sizeof(struct objPos));    // Allocate item bin memory space
    
    Initialize();


 
    generateMS(mystryString); // Generate mystry string and initialize it with '?' characters

    GenerateItems(&playerObj, list, listSize, xRange, yRange, goalString, mystryString); // Generate item bin (Initialization)

    while(!exitFlag)
    {

        drawscreen(counter, &playerObj, list, listSize, xRange, yRange, mystryString); // Print the game board

        GetInput(&input); // read player input

        playerloc(&playerObj, &input, &direction, &exitFlag); // calculate player new location

        counter++; // increment move counter

        runlogic(&playerObj, list, &exitFlag, listSize, xRange, yRange, goalString, mystryString);

        LoopDelay(); // add some delay 
        

    }
    
    drawscreen(counter, &playerObj, list, listSize, xRange, yRange, mystryString); // Print the game board for the last time

    if(exitFlag == 1)
    {
        MacUILib_printf("You just quit the game... LOSER!");
    }
    else if (exitFlag == 2)
    {
        MacUILib_printf("WoW... We have a WINNER!");
    }

    // Freeing the allocated memory in heap
    free(mystryString);
    free(list);

    CleanUp();

    return 0;

}

