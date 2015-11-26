/** @file   score.h
    @author Lukpla Worathongchai  65098184
    	      Kanyakorn Kitisopakul 18582950
    @team   Team_25 - Blink it on
    @date   15 October 2015
    @brief  Counting score for player in relation to the territory.
    @note		This formatting is for Atom.

    This module implements functions to keep track or update score
    and territory.
*/


#include "system.h"
#include "tinygl.h"

/** Define the score for the current player. */
typedef int total_score;

/** Define the state of territory for player1.*/
typedef int player1_territory[7][5];

/** Define the state of territory for player2. */
typedef int player2_territory[7][5];



/** Update the player1_territory from 0 to 1
    0 - the place where player1 hasn't paint yet
    1  - the place where player1 has painted
    @param row int territory row
    @param col int territory column */
void setTerritoryP1(int row, int col);


/** Update the player2_territory from 0 to 1
    0 - the place where player2 hasn't paint yet
    1  - the place where player2 has painted
    @param row int territory row
    @param col int territory column */
void setTerritoryP2(int row, int col);


/** Increment the score by 1. This is used when the player walks in
the territory that has no red led yet.*/
void incrementScore(void);


/** Add 2 to the current point.
    This is used when the player walks on the other player territory. */
void specialScore(void);


/** Initialise the score for both players. */
void initScore(void);


/** Check if the given territory has been painted by player1
    @param row int territory row
    @param col int territory column
    @return - true if already painted by player1 and false otherwise. */
bool isTerritoryTakenP1(int row, int col);


/** Check if the given territory has been painted by player2
    @param row int territory row
    @param col int territory column
    @return - true if already painted by player2 and false otherwise. */
bool isTerritoryTakenP2(int row, int col);


/** Check if all territory has been painted or not
    When all the territory has been painted, this will indicate the ending of
    the game
    @return - true if all the territory has been painted and false otherwise. */
bool isAllTerritoryTaken(void);


/** Getter for total score. Used to count score at the end of the game.
    @return - int total score. */
int getTotalScore(void);
