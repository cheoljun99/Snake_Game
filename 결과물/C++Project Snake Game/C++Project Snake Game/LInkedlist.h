#pragma once
#include "stdafx.h"
class Linkedlist//The header of the class for storing the snake's body as a linked list
{
public:
	Snake * Head=NULL;
	Linkedlist();//It is a constructor, which creates a head and a body, and stores the location.
	void AddSnake(int xPre, int yPre);////Function to add body.

};