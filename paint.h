/** @file   paint.h
    @author Lukpla Worathongchai  65098184
    	      Kanyakorn Kitisopakul 18582950
    @team   Team_25 - Blink it on
    @date   15 October 2015
    @brief  module for players to paint the territory.
		@note		This formatting is for Atom.

    This module implements functions to paint the territory with red led
    whenever the navswitch North, South, East, or West from either
    player1 or player2 is used.
    The function also call other module score.h to update point and territory
    for player
    Point Rule:
      -	if landed in own territory, point won't be count
      -	if landed in empty territory, point will be + 1
      - if landed in other player territory, point will be + 2
*/


#include "led.h"
#include "timer.h"
#include "score.h"
#include "pacer.h"
#include "tinygl.h"
#include "system.h"
#include "ir_uart.h"
#include "navswitch.h"
#include "../fonts/font5x7_1.h"


typedef struct pen pen_t;
/** Define the state and position for pen. */
struct pen
{
  /* Current position of pen. */
  tinygl_point_t pos;
  /* Current state of pen. */
  bool state;
};

/* Define pen for player1 and player2. */
pen_t player1_pen;
pen_t player2_pen;

/* Define paint. red led on as 1 and red led on off as 0. */
int paintP1;
int paintP2;


/** Assign which pen belongs to which player
    if player=1 then assigns to player1_pen pen
    else assigns to player2_pen pen
    @param player - which player are you? */
void initPenP1(int player);


/** Assign which pen belongs to which player
    if player=1 then assigns to player2_pen pen
    else assigns to player2_pen pen
    @param player - which player are you? */
void initPenP2(int player);


/** Initialise pen for both player
    use setPenP1 and setPenP2
    Pen position for player1 is [top-left]
    Pen position for player2 is [bottom-right]
    @param player - which player are you? */
void initPen(int player);


/** Update the score and territory
 		whenever the North, South, East, or West navswitch is pushed
		Increment score if landed in an empty territory(no red led yet),
		No score if landed in your own territory,
		Special score if landed in other player territory
		Also sending and receiving infrared communication to make
    sure both mattrix boards are updated consistently. */
void painting(void);
