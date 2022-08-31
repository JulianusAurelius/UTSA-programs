#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "champion.h"

int main(int argc, char *argv[])
{
    srand((int)time(0)); // seed the random number generator
    if (argc != 2) //check if the user entered the correct number of arguments
    {
        printf("Usage: %s <number of champions>\n", argv[0]);
        return 1;
    }
    if (atoi(argv[1]) < 1) //check if the user entered a valid number of champions
    {
        printf("Number of champions must be greater than 0\n");
        return 1;
    }

    
    int num_champions = atoi(argv[1]); //get the number of champions from the user
    Champion* player; //create a pointer to a champion object for each player
    Champion* enemy; //I named this enemy instead of player 2
    player = buildChampionList(num_champions); //build the list of champions for each player
    enemy = buildChampionList(num_champions);

    // initialize the proper variables
    int round = 1;
    int remove_p; //these are used to loop over remove or add functions at the end of each round
    int remove_e; //Because sometimes there is no reward or penalty, and sometimes it's double (SUPPORT)
    int add_p;
    int add_e;
    int i; //used for looping, init here to avoid constant reinit


    printf("\n============= PLAYER 1 V PLAYER 2 SHOWDOWN ============\n\n");

    while ( (player != NULL) && (enemy != NULL) )
    {
        // reset round variables
        remove_p = 0;
        remove_e = 0;
        add_p = 0;
        add_e = 0;

        // prints out round info
        printf("----- ROUND %d -----\n", round++); // post-increments the round so no need for another line
        printf("Player 1: ");
        printChampionList(player);
        printf("\n");
        printf("Player 2: ");
        printChampionList(enemy);
        printf("\n");

        // prints out current role of both players
        printf("Player 1 is a %s ", player->role == MAGE ? "MAGE" : player->role == FIGHTER ? "FIGHT" : player->role == SUPPORT ? "SUPPORT" : "TANK");
        printf("and Player 2 is a %s\n", player->role == MAGE ? "MAGE" : player->role == FIGHTER ? "FIGHT" : player->role == SUPPORT ? "SUPPORT" : "TANK");

        // prints out the possible permutations of the roles, and modifies the variables accordingly
        // nested switch statements are used to make it easier to read, used extra spacing
        switch (player->role)
        {


        case 0:
            switch (enemy->role)
            {

            case 0:
                if (player->level > enemy->level)
                {
                    printf("Player 1 (MAGE) wins and gains one new champion.\n");
                    printf("Player 2 (MAGE) loses one champion.\n");
                    add_p = 1;
                    remove_e = 1;
                }
                else if (player->level < enemy->level)
                {
                    printf("Player 1 (MAGE) loses one champion.\n");
                    printf("Player 2 (MAGE) wins and gains one new champion.\n");
                    add_e = 1;
                    remove_p = 1;
                }
                else
                {
                    printf("Player 1 (MAGE) and Player 2 (MAGE) tie, nothing happens\n");
                }
                break;

            case 1:
                if (player->level > enemy->level)
                {
                    printf("Player 1 (MAGE) wins and gains one new champion.\n");
                    printf("Player 2 (FIGHTER) loses but with no penalty.\n");
                    add_p = 1;
                }
                else if (player->level < enemy->level)
                {
                    printf("Player 1 (MAGE) loses one champion.\n");
                    printf("Player 2 (FIGHTER) wins but with no reward.\n");
                    remove_p = 1;
                }
                else
                {
                    printf("Player 1 (MAGE) and Player 2 (FIGHTER) tie, nothing happens\n");
                }
                break;
            
            case 2:
                if (player->level > enemy->level)
                {
                    printf("Player 1 (MAGE) wins and gains one new champion.\n");
                    printf("Player 2 (SUPPORT) loses two champions.\n");
                    add_p = 1;
                    remove_e = 2;
                }
                else if (player->level < enemy->level)
                {
                    printf("Player 1 (MAGE) loses one champion.\n");
                    printf("Player 2 (SUPPORT) wins and gains two new champions.\n");
                    remove_p = 1;
                    add_e = 2;
                }
                else
                {
                    printf("Player 1 (MAGE) and Player 2 (SUPPORT) tie, nothing happens\n");
                }
                break;
            
            case 3:
                printf("Player 1 (MAGE) wins and gains a new champion.\n");
                printf("Player 2 (TANK) loses one champions.\n");
                add_p = 1;
                remove_e = 1;
            }
            break;


        case 1:
            switch (enemy->role)
            {
            case 0:
                if (player->level > enemy->level)
                {
                    printf("Player 1 (FIGHTER) wins but with no reward.\n");
                    printf("Player 2 (MAGE) loses one champion.\n");
                    remove_e = 1;
                }
                else if (player->level < enemy->level)
                {
                    printf("Player 1 (FIGHTER) loses one champion.\n");
                    printf("Player 2 (MAGE) wins but with no penalty.\n");
                    add_e = 1;
                }
                else
                {
                    printf("Player 1 (FIGHTER) and Player 2 (MAGE) tie, nothing happens.\n");
                }
                break;

            case 1:
                printf("Both players gain a new champion.\n");
                add_p = 1;
                add_e = 1;
                break;
            
            case 2:
                if (player->level > enemy->level)
                {
                    printf("Player 1 (FIGHTER) wins but with no reward.\n");
                    printf("Player 2 (SUPPORT) loses one champion.\n");
                    remove_e = 1;
                }
                else if (player->level < enemy->level)
                {
                    printf("Player 1 (FIGHTER) loses but with no penalty.\n");
                    printf("Player 2 (SUPPORT) wins and gains one new champion.\n");
                    add_e = 1;
                }
                else
                {
                    printf("Player 1 (FIGHTER) and Player 2 (SUPPORT) tie, nothing happens.\n");
                }
                break;
            
            case 3:
                printf("Player 1 (FIGHTER) wins and gains a new champion.\n");
                printf("Player 2 (TANK) loses but with no penalty.\n");
                add_p = 1;
                break;
            }
            break;
        

        case 2:
            switch (enemy->role)
            {
            case 0:
                if (player->level > enemy->level)
                {
                    printf("Player 1 (SUPPORT) wins and gains two new champions.\n");
                    printf("Player 2 (MAGE) loses one champion.\n");
                    add_p = 2;
                    remove_e = 1;
                }
                else if (player->level < enemy->level)
                {
                    printf("Player 1 (SUPPORT) loses two champions.\n");
                    printf("Player 2 (MAGE) wins and gains one new champion.\n");
                    remove_p = 2;
                    add_e = 1;
                }
                else
                {
                    printf("Player 1 (SUPPORT) and Player 2 (MAGE) tie, nothing happens\n");
                }
                break;
            
            case 1:
                if (player->level > enemy->level)
                {
                    printf("Player 1 (SUPPORT) wins and gains one new champion.\n");
                    printf("Player 2 (FIGHTER) loses but with no penalty.\n");
                    add_p = 1;
                }
                else if (player->level < enemy->level)
                {
                    printf("Player 1 (SUPPORT) loses one champion.\n");
                    printf("Player 2 (FIGHTER) wins but with no reward.\n");
                    remove_p = 1;
                }
                else
                {
                    printf("Player 1 (SUPPORT) and Player 2 (FIGHTER) tie, nothing happens.\n");
                }
                break;
            
            case 2:
                printf("Both players lose the next champion.\n");
                remove_p = 1;
                remove_e = 1;
                break;
            
            case 3:
                printf("Player 1 (SUPPORT) loses but with no penalty.\n");
                printf("Player 2 (TANK) wins and gains a new champion.\n");
                remove_p = 1;
                break;
            }
            break;
        

        case 3:
            switch (enemy->role)
            {
            case 0:
                printf("Player 1 (TANK) loses one champion.\n");
                printf("Player 2 (MAGE) wins and gains a new champion.\n");
                remove_p = 1;
                add_e = 1;
                break;
            
            case 1:
                printf("Player 1 (TANK) loses but with no penalty.\n");
                printf("Player 2 (FIGHTER) wins and gains a new champion.\n");
                add_e = 1;
                break;
            
            case 2:
                printf("Player 1 (TANK) wins and gains a new champion.\n");
                printf("Player 2 (SUPPORT) loses but with no penalty.\n");
                add_p = 1;
                break;
            
            case 3:
                printf("Nothing happens - no penalty or reward.\n");
                break;
            }
            break;
        }

        // removes the current champion from the round
        player = removeChampion(player);
        enemy = removeChampion(enemy);
        
        // adds or removes champions based on the results of the round, to the amount needed (0, 1 or 2)
        for (i = 0; i < add_p; i++)
        {
            player = addChampion(player, createChampion()); //use createChampion() inside addChampion()
        }
        for (i = 0; i < add_e; i++)
        {
            enemy = addChampion(enemy, createChampion());
        }
        for (i = 0; i < remove_p; i++)
        {
            player = removeChampion(player);
        }
        for (i = 0; i < remove_e; i++)
        {
            enemy = removeChampion(enemy);
        }
        printf("\n\n");

    }

    // prints the final results of the game
    printf("============ GAME OVER  =============");
    printf("\n\n");
    printf("Player 1 ending list: ");
    printChampionList(player);
    printf("\n");
    printf("Player 2 ending list: ");
    printChampionList(enemy);
    printf("\n\n");

    // prints the winner
    if (player == NULL)
    {
        if (enemy == NULL)
        {
            // if both players are out of champions, it's a tie
            printf("TIE -- both players ran out of champions.\n");
        }
        else
        {
            // if player 1 null, then they are out of champions, player 2 wins
            printf("Player 1 ran out of champions. Player 2 wins.\n");
        }
    }
    else
    {
        // if player 2 null, then they are out of champions, player 1 wins
        printf("Player 2 ran out of champions. Player 1 wins.\n");
    }
    printf("\n"); // extra spacing, looks nice

    // frees the memory used by the champions
    destroyChampionList(player);
    destroyChampionList(enemy);

    return 0;
}