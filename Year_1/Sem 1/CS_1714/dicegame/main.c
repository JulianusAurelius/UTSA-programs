#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"dicegame.h"

int main(int argc, char *argv[])
{
  //Init random, as well as all needed variables
  srand((int)time(0)); //Giving random seed from time
  int player1Points = 0; //Starting player 1 points
  int player2Points = 0; //Starting player 2 points
  int currentPlayerInt = getRandomNumber(0,1); //Randomly chooses a player to start... NOTE: Player 1 is Player '0', and Player 2 is player '1' for boolean calculations
  int* currentPlayer = (currentPlayerInt) ? &player2Points : &player1Points; //Single line if statement to set a pointer equal to the point variable for the current player
  int numRounds;
  int type;
  int dice;
  int points;
  int i;
  enum ROUNDTYPE t;

  //Pregame logic, get number of rounds, print initial values
  printf("Enter number of rounds: ");
  scanf("%d", &numRounds);
  printPlayerPoints(player1Points, player2Points);

	// Call printPlayerPoints() function to print the initial player points which will be 0

	for(i = 0; i < numRounds; ++i)
	{
    //Print header
		printf("\nROUND %d\n--------\n", i+1);
		printf("PLAYER  : %d\n", currentPlayerInt+1); //Prints the current player, but since they are stored as player0 and player1, basically, we add 1 to get the proper human-readable form

    //Set up round
    t = getRoundType();
    dice = getRandomNumber(1,6);
    points = getRoundPoints(t);
    printRoundInfo(t, dice, points);

    //Game logic
    if (dice%2 != (currentPlayerInt)) //If dice is odd (remainder 1) and the player is 0, then this is true and the player wins. Same for remainder 0 and player 1
    {
      *currentPlayer += points; //Points are added to the point variable that the currentPlayer pointer  is pointing to
    }
    else //Else player loses
    {
      *currentPlayer -= points; //Player loses the points instead through the pointer variable
      currentPlayerInt = (currentPlayerInt + 1) % 2; //Current player is changed by adding 1 ( 0->1 || 1->2 ) and taking modulo ( 1->1 || 2-> 0 ), so players change from ( 0->1 || 1->0 )
      currentPlayer = (currentPlayerInt) ? &player2Points : &player1Points; //Single line if statement based on player0 or player1 (boolean from int), to properly assign currentPlayer pointer
    }

    //Print points at the end of the current round
    printPlayerPoints(player1Points, player2Points);

	}
	printf("\nGAME OVER!!\n");

  //Print out winner
  if (player1Points == player2Points)
  {
    printf("TIE!"); //If it is a tie, print tie
  }
  else{
    (player1Points > player2Points) ? printf("P1 WON!\n") : printf("P2 WON!\n"); //Single line if/else statmement to print out winner
  }

	return 0;
}
