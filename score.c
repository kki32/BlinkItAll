/** @file   score.c
    @author Lukpla Worathongchai  65098184
    	      Kanyakorn Kitisopakul 18582950
    @team   Team_25 - Blink it on
    @date   15 October 2015
    @brief  Counting score for player in relation to the territory
    @note		This formatting is for Atom.

    This module implements functions to keep track or update score
    and territory.
*/


#include "system.h"
#include "tinygl.h"

/** Define the score for the current player. */
int total_score;

/** Define the state of territory for player1.*/
int player1_territory[7][5] = {{0,0,0,0,0},
{0,0,0,0,0},
{0,0,0,0,0},
{0,0,0,0,0},
{0,0,0,0,0},
{0,0,0,0,0},
{0,0,0,0,0}};


/** Define the state of territory for player2. */
int player2_territory[7][5] = {{0,0,0,0,0},
{0,0,0,0,0},
{0,0,0,0,0},
{0,0,0,0,0},
{0,0,0,0,0},
{0,0,0,0,0},
{0,0,0,0,0}};


/** Update the player1_territory from 0 to 1
    0 - the place where player1 hasn't paint yet
    1  - the place where player1 has painted
    @param row int territory row
    @param col int territory column */
void setTerritoryP1(int row, int col){
  player1_territory[row][col] = 1;
}


/** Update the player2_territory from 0 to 1
    0 - the place where player2 hasn't paint yet
    1  - the place where player2 has painted
    @param row int territory row
    @param col int territory column */
void setTerritoryP2(int row, int col){
  player2_territory[row][col] = 1;
}


/** Increment the score by 1. This is used when the player walks in
the territory that has no red led yet. */
void incrementScore(void){
  total_score += 1;
}


/** Add 2 to the current point.
    This is used when the player walks on the other player territory. */
void specialScore(void){
  total_score += 2;
}


/** Initialise the score for both players. */
void initScore(void){
  //player1 starts [top-left] and player2 starts [bottom-right]
  player1_territory[TINYGL_HEIGHT - 1][TINYGL_WIDTH - 1] = 1;
  player2_territory[0][0] = 1;
  //automatically earn score at the start
  incrementScore();
}


/** Check if the given territory has been painted by player1
    @param - row and column territory position
    @return - true if already painted by player1 and false otherwise. */
bool isTerritoryTakenP1(int row, int col){
  if(player1_territory[row][col] == 1){
    return true;
  }
  else{
    return false;
  }
}


/** Check if the given territory has been painted by player2
    @param row int territory row
    @param col int territory column
    @return - true if already painted by player2 and false otherwise. */
bool isTerritoryTakenP2(int row, int col){
  if(player2_territory[row][col] == 1){
    return true;
  }
  else{
    return false;
  }
}


/** Check if all territory has been painted or not
    When all the territory has been painted, this will indicate the ending of
    the game
    @return - true if all the territory has been painted and false otherwise  */
bool isAllTerritoryTaken(void){
  bool allTaken = true;
  int i = 0;
  int j = 0;

  //go through each row and column and check that the territory is taken by either
  //player1 or player2
  for(i = 0; i < 7; i++){
    for(j = 0; j < 5; j++){
      if((player1_territory[i][j] == 0) && (player2_territory[i][j] == 0)){
        allTaken = false;
     }
    }
  }
  return allTaken;
}


/** Getter for total score. Used to count score at the end of the game.
    @return - int total score. */
int getTotalScore(void){
  return total_score;
}
