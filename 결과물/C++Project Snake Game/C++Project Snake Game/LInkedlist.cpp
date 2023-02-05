#include "stdafx.h"
Linkedlist::Linkedlist()//It is a constructor, which creates a head and a body, and stores the location.
{
	if (Head == NULL)
	{
		Snake * temp = new Snake;
		temp->x = MapHorizontalityMax /2;
		temp->y = MapVerticalityMax /2;
		temp->next = new Snake;
		temp->next->x = (MapHorizontalityMax / 2+1);
		temp->next->y = MapVerticalityMax / 2;
		temp->next->next = new Snake;
		temp->next->next->x = (MapHorizontalityMax / 2+2);
		temp->next->next->y = MapVerticalityMax / 2;
		temp->next->next->next = NULL;
		Head = temp;
		

	}
	

}

void Linkedlist::AddSnake(int xPre, int yPre)//Function to add body.
{
	
	Snake * Newtemp = new Snake;
	Newtemp->x = xPre;
	Newtemp->y = yPre;
	Newtemp->next = Head->next;
	Head->next = Newtemp;

}
