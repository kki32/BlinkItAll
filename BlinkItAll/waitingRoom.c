/** @file   waitingRoom.c
    @author Lukpla Worathongchai  65098184
    	      Kanyakorn Kitisopakul 18582950
    @team   Team_25 - Blink it on
    @date   15 October 2015
    @brief  module for blue led before game
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
    @note		This formatting is for Atom.
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
int getReady(void){

  int whichPlayer = 0;
  bool readyP1 = false;
  bool readyP2 = false;


  while (!readyP1)
  {
      navswitch_update();
    /* for receive reply. */
    if (ir_uart_read_ready_p()){
      /* receiver uses this. */
      if(ir_uart_getc() == true && readyP1 == false){
          readyP1 = true;
          led_set(LED1, 1);
      }
    }

    if(navswitch_push_event_p(NAVSWITCH_PUSH)){
        /* sender uses this. */
        readyP1 = true;
        ir_uart_putc(readyP1);
        led_set(LED1, 1);
	       whichPlayer = 1;
      }
    }


  while(!readyP2){
    navswitch_update();
    if(navswitch_push_event_p(NAVSWITCH_PUSH)){
      readyP2 = true;
      led_set(LED1, 0);
      ir_uart_putc(readyP2);
	    pacer_wait();
	    whichPlayer = 2;
    }
    if (ir_uart_read_ready_p()){
      if(ir_uart_getc() == true && readyP2 == false){
      readyP2 = true;
      led_set(LED1, 0);
      }
    }
  }
return whichPlayer;
}
