/** @file   waitingRoom.h
    @author Lukpla Worathongchai  65098184
    	      Kanyakorn Kitisopakul 18582950
    @team   Team_25 - Blink it on
    @date   15 October 2015
    @brief  module for blue led before game.
    @note		This formatting is for Atom.

    This module called 'waitingRoom' are used for both players to confirm
    their readiness before the game begins.

    Player1 and player2 will perform different tasks in the function getReady.
    Any player that pushes the navswitch push button first will become
    player1.
    Player1:
    push navswitch -> blue led on -> waits for player2 to send signal(trigger by push) -> blue led off
    Player2:
    waits for player1 to send signal(trigger by push) -> blue led on
    -> push navswitch -> blue led off
*/


#include "led.h"
#include "pacer.h"
#include "system.h"
#include "ir_uart.h"
#include "navswitch.h"


/** Turn on blue led and sends signal to light other player's microcontroller
blue led when the player pushes navswitch. It then waits to receive the signal
from the other player's controller to turn off its blue led.
    @return player - which player? 1 or 2 */
int getReady(void);
