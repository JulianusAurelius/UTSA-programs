#include <stdio.h>
#include <stdlib.h>
#include "champion.h"

Champion* createChampion()
{
    Champion* champion = (Champion*)malloc(sizeof(Champion)); // Allocate memory for the champion
    int random = rand() % 4; // Generate a random number between 0 and 3 to choose role with 25% chance of each
    int level; 
    switch (random)
    {
    case 0: // sets role to mage, level is between 5 and 8
        champion->role = MAGE;
        level = rand() % 4 + 5;
        champion->level = level;
        break;
    
    case 1: // sets role to fighter, level is between 1 and 4
        champion->role = FIGHTER;
        level = rand() % 4 + 1;
        champion->level = level;
        break;

    case 2: // sets role to support, level is between 3 and 6
        champion->role = SUPPORT;
        level = rand() % 4 + 3;
        champion->level = level;
        break;
    
    case 3: // sets role to tank, level is between 1 and 8
        champion->role = TANK;
        level = rand() % 8 + 1;
        champion->level = level;
        break;
    }

    champion->next = NULL;
    return champion;
}

Champion* addChampion(Champion* head, Champion* champion)
{
    if (head == NULL) // if list is empty
    {
        head = champion; // set head to the new champion
    }
    else if (head->next == NULL) // if list has 1 element
    {
        if (head->level > champion->level) // set the next element to the new champion if lower than head
        {
            head->next = champion;
        }
        else // if the new champion is higher level than the head, set the new champion to the head
        {
            champion->next = head;
            head = champion;
        }
    }
    else // if list has more than 1 element
    {
        if (champion->level > head->level) // if new champion level is higher than head
        {
            champion->next = head; // set the head to the new champion
            head = champion;
        }
        else
        {
            Champion* current = head->next;
            Champion* previous = head;
            // goes through the list until it finds the an element with a lower level,
            // then adds the new champion *before* that element using the previous champion
            while (current->next != NULL)
            {
                if (current->level <= champion->level) // if the current champion's level is less
                {
                    previous->next = champion; // insert the new champion before the current
                    champion->next = current;
                    return head;
                }
                previous = current;
                current = current->next;
            }
            if (current->level <= champion->level) // if the current champion's level is less
            {
                previous->next = champion; // insert the new champion before the current
                champion->next = current;
            }
            else
            {
                current->next = champion; // when the new champion's level is the lowest, add it to the end
            }
        }
    }
    return head;
}

Champion* buildChampionList(int n)
{
    Champion* head = NULL;
    int i;
    for (i = 0; i < n; i++) // builds the list of n champions
    {
        Champion* champion = createChampion(); // create a new champion
        head = addChampion(head, champion); // add the champion to the list
    }
    return head;
}

void printChampionList(Champion* head)
{
    Champion* current = head;
    while (current != NULL) // goes through the list until it reaches the end
    {
        switch (current->role) // prints the role of the champion
        {
        case 0:
            printf("M");
            break;
        case 1:
            printf("F");
            break;
        case 2:
            printf("S");
            break;
        case 3:
            printf("T");
            break;
        }
        printf("%d ", current->level); // prints the level of the champion
        current = current->next; // moves to the next champion
    }
}

Champion* removeChampion(Champion* head)
{
    if (head == NULL) // if list is empty, do nothing
    { //implemented this way to avoid a segfault when the list has only one element, but you try to remove 2 when support loses to mage
        return NULL;
    }
    else
    {
        Champion* current = head->next; // set current to the second element to remove head
        free(head); // free the first element
        return current; // return the second element
    }
}

Champion* destroyChampionList(Champion* head)
{
    Champion* current = head;
    if (head != NULL)
    {
        destroyChampionList(current->next); // recursively moves to the end of the list to free from the end to the beginning
        free(current); // frees current element (back to front of list)
        return NULL;
    }
    
}