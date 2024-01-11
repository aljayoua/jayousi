#include "objPosArrayList.h"


objPosArrayList::objPosArrayList()
{
    // initialize the array list
    aList = new objPos[ARRAY_MAX_CAP]; //256 elements on the heap
    listSize = 0; 
    arrayCapacity = ARRAY_MAX_CAP; 
    
}

objPosArrayList::~objPosArrayList()
{
    delete[] aList; 
}                   

int objPosArrayList::getSize()
{
    return listSize;
}

void objPosArrayList::insertHead(objPos thisPos)
{
    //still need error check - what if listSize is capacity
    if (listSize == ARRAY_MAX_CAP)
    {
        return; 
    }
    for (int i = listSize; i > 0; i--)
    {
        aList[i].setObjPos(aList[i-1]); //this will shuffle all the elements towards the tails
    }
    aList[0].setObjPos(thisPos);

    listSize++;
}

void objPosArrayList::insertTail(objPos thisPos)
{
    aList[listSize++].setObjPos(thisPos); 
}

void objPosArrayList::removeHead()
{
    if (listSize > 0)
    {
        for (int i = 0; i < listSize - 1; i++)
        {
            aList[i].setObjPos(aList[i + 1]);
        }
        listSize--;
    }
}

void objPosArrayList::removeTail()
{

    listSize--;
}

void objPosArrayList::getHeadElement(objPos &returnPos)
{
    returnPos.setObjPos(aList[0]);
}

void objPosArrayList::getTailElement(objPos &returnPos)
{
    returnPos.setObjPos(aList[listSize - 1]);
}

void objPosArrayList::getElement(objPos &returnPos, int index)
{
    returnPos.setObjPos(aList[index]);
}

bool objPosArrayList::getObjPos(int index,objPos &returnPos)
{
    if (index < 0 || index >= listSize)
    {
        return false;
    }
    else
    {
        returnPos.setObjPos(aList[index]);
        return true;
    }
}