/** @file   paint.c
    @author Lukpla Worathongchai  65098184
    	      Kanyakorn Kitisopakul 18582950
    @team   Team_25 - Blink it on
    @date   15 October 2015
    @brief  module for players to paint the territory
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

/** Define rate for updating tinygl. */
#define LOOP_RATE 2000
/** Define rate for updating message display. */
#define MESSAGE_RATE 10

typedef struct pen pen_t;


/* Define pen for player1 and player2. */
pen_t player1_pen;
pen_t player2_pen;


/* Define paint. red led on as 1 and red led on off as 0. */
int paintP1;
int paintP2;


/** Define the state and position for pen. */
struct pen
{
    /* Current pos of pen.  */
    tinygl_point_t pos;
    /* Current state of pen.  */
    bool state;
};


/** Assign which pen belongs to which player
    if player=1 then assigns to player1_pen pen
    else assigns to player2_pen pen
    @param player - which player are you? */
void initPenP1(int player){
  if(player == 1){
    player1_pen.pos.x = TINYGL_WIDTH - 1;
    player1_pen.pos.y = TINYGL_HEIGHT - 1;
    player1_pen.state = true;
  }
  else{
    player1_pen.pos.x = 0;
    player1_pen.pos.y = 0;
    player1_pen.state = true;
  }
}


/** Assign which pen belongs to which player
    if player=1 then assigns to player2_pen pen
    else assigns to player2_pen pen
    @param player - which player are you? */
void initPenP2(int player){
  if(player == 1){
    player2_pen.pos.x = 0;
    player2_pen.pos.y = 0;
    player2_pen.state = true;
  }
  else{
    player2_pen.pos.x = TINYGL_WIDTH - 1;
    player2_pen.pos.y = TINYGL_HEIGHT - 1;
    player2_pen.state = true;
  }

}


/** Initialise pen for both player
    use setPenP1 and setPenP2
    Pen position for player1 is [top-left]
    Pen position for player2 is [bottom-right]
    @param player - which player are you? */
void initPen(int player){
  paintP1 = 0;
  paintP2 = 0;

  initPenP1(player);
  initPenP2(player);

  tinygl_init (LOOP_RATE);
  //light red led on both players origin
  //player1 [top-left] player2 [bottom-right]
  tinygl_draw_point (player1_pen.pos, player1_pen.state);
  tinygl_draw_point (player2_pen.pos, player2_pen.state);

  //turn blue led on to indicate game starts
  led_set (LED1, player1_pen.state);
}




void painting(void){
  //receive from other players
  if (ir_uart_read_ready_p ()){
      paintP2 = 1;
      //get their position from the signal
      player2_pen.pos.x = ir_uart_getc();
      player2_pen.pos.y = ir_uart_getc();

      /* update the information about other player territory. */
      setTerritoryP2(player2_pen.pos.y, player2_pen.pos.x);
      tinygl_update ();
}

if (navswitch_push_event_p (NAVSWITCH_NORTH) && player1_pen.pos.y > 0)
{
    player1_pen.pos.y--;
    paintP1= 1;

     ir_uart_putc(player1_pen.pos.x);
     ir_uart_putc(player1_pen.pos.y);

     //check if the player lands on their own territory
     if(!isTerritoryTakenP1(player1_pen.pos.y, player1_pen.pos.x)){
       //check if the player lands on other player territory
        if(isTerritoryTakenP2(player1_pen.pos.y, player1_pen.pos.x)){
           specialScore();
        }
        //the player lands on territory that hasn't been painted
        else{
          incrementScore();
        }
     }
     //update information about the player territory
         setTerritoryP1(player1_pen.pos.y, player1_pen.pos.x);

}

if (navswitch_push_event_p (NAVSWITCH_SOUTH) && player1_pen.pos.y < TINYGL_HEIGHT - 1)
{
    player1_pen.pos.y++;
    paintP1= 1;

       ir_uart_putc(player1_pen.pos.x);
       ir_uart_putc(player1_pen.pos.y);

       //check if the player lands on their own territory
       if(!isTerritoryTakenP1(player1_pen.pos.y, player1_pen.pos.x)){
          //check if the player lands on other player territory
          if(isTerritoryTakenP2(player1_pen.pos.y, player1_pen.pos.x)){
             specialScore();
          }
          //the player lands on territory that hasn't been painted
          else{
            incrementScore();
          }
       }
       //update information about the player territory
       setTerritoryP1(player1_pen.pos.y, player1_pen.pos.x);
}
if (navswitch_push_event_p (NAVSWITCH_EAST) && player1_pen.pos.x < TINYGL_WIDTH - 1)
{
    player1_pen.pos.x++;
    paintP1= 1;

     ir_uart_putc(player1_pen.pos.x);
     ir_uart_putc(player1_pen.pos.y);

     //check if the player lands on their own territory
     if(!isTerritoryTakenP1(player1_pen.pos.y, player1_pen.pos.x)){
        //check if the player lands on other player territory
        if(isTerritoryTakenP2(player1_pen.pos.y, player1_pen.pos.x)){
           specialScore();
        }
        //the player lands on territory that hasn't been painted
        else{
          incrementScore();
        }
     }
   //update information about the player territory
   setTerritoryP1(player1_pen.pos.y, player1_pen.pos.x);

}

if(navswitch_push_event_p(NAVSWITCH_WEST) && player1_pen.pos.x > 0)
{
  player1_pen.pos.x--;
  paintP1= 1;

  ir_uart_putc(player1_pen.pos.x);
  ir_uart_putc(player1_pen.pos.y);

  //check if the player lands on their own territory
  if(!isTerritoryTakenP1(player1_pen.pos.y, player1_pen.pos.x)){
     //check if the player lands on other player territory
     if(isTerritoryTakenP2(player1_pen.pos.y, player1_pen.pos.x)){
        specialScore();
     }
     //the player lands on territory that hasn't been painted
     else{
       incrementScore();
     }
  }
  //update information about the player territory
   setTerritoryP1(player1_pen.pos.y, player1_pen.pos.x);
}


    if (paintP1)
        tinygl_draw_point (player1_pen.pos, player1_pen.state);
        tinygl_update();


   if (paintP2)
        tinygl_draw_point (player2_pen.pos, player2_pen.state);
        tinygl_update();
}
