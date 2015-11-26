/** @file   game.c
    @author Lukpla Worathongchai  65098184
    	      Kanyakorn Kitisopakul 18582950
    @team   Team_25 - Blink it on
    @date   15 October 2015
    @brief  This file is the core file which launches the game.
    @note		This formatting is for Atom.

    Blink it on is the game for two microcontrollers to compete for
    territory which is represented by red led on mattrix board.
    The game will start shortly after both players confirm
    their readiness by pushing navswitch push button.
    Initially, player1 will start at [top-left] while
    player2 will start at [bottom-right]. The game finishes when all
    territories on the mattrix board have been painted with
    red led. The score shows up for players to let the players decide
    who is the winner/loser.

    Point Rule:
      -	if landed in own territory, point won't be count
      -	if landed in empty territory, point will be + 1
      - if landed in other player territory, point will be + 2
*/


/* header files that are provided. */
#include "system.h"
#include "pacer.h"
#include "led.h"
#include "ir_uart.h"
#include "button.h"

/* our own header files. */
#include "paint.h"
#include "waitingRoom.h"
#include "startEndDisplay.h"
#include "score.h"

/* Define the rate which the pacer will update. */
#define PACER_RATE 1000
/* Define state for blue led. Off as 0.*/
#define OFF 0

int main (void)
{
  int whichPlayer;
  bool allTerritoryTaken = false;

  /** Initialise system. */
  system_init ();
  /** Initialise infrared uart driven. */
  ir_uart_init ();
  /** Initialise button. */
  button_init ();
  /** Initialise navswitch polling. */
  navswitch_init ();
  /** Initialise paced loop. */
  pacer_init (PACER_RATE);
  /** Initialise led driver. */
  led_init ();
  // ensure led is off
  led_set (LED1, OFF);

  /** Assign which player you are? player1 or player2. */
  whichPlayer = getReady();
  pacer_wait();

  /** Display 3 2 1 */
  countdown();

  /** Initialise pen for each player. */
  initPen(whichPlayer);
  /** Initialise score count for each player. */
  initScore();

  /** if all territory has been
    taken then game finishes. */
   while (!allTerritoryTaken)
   {
      pacer_wait();
      navswitch_update();
      //paint territory
      painting();
      //will be true when all red led on the mattrix board is on
      allTerritoryTaken = isAllTerritoryTaken();
   }
   /** Display the score for the player. */
   displayScore(getTotalScore());

return 0;
}
