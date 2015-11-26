/** @file   startEndDisplay.c
    @author Kanyakorn Kitisopakul 18582950
            Lukpla Worathongchai  65098184
    @team   Team_25 - Blink it on
    @date   15 October 2015
    @brief module for display message - before or after game begins
		@note		This formatting is for Atom.

    This module implements functions associated with displaying message either
    at the begining of the game or at the end of the game.
*/

#include "timer.h"
#include "pacer.h"
#include "tinygl.h"
#include "system.h"
#include "../fonts/font3x5_1.h"
#include "../fonts/font5x7_1.h"


#ifndef TIMER_CLOCK_DIVISOR
#define TIMER_CLOCK_DIVISOR 256
#endif


/** Rate in Hz that the timer is incremented. */
#define MESSAGE_RATE 10
#define TIMER_RATE (F_CPU / TIMER_CLOCK_DIVISOR)


/** Countdown with a message '3 2 1' */
void countdown(void){
  tinygl_point_t origin = {0, 0};

  system_init();
  tinygl_init (500);
  tinygl_font_set (&font5x7_1);
  tinygl_text_speed_set (MESSAGE_RATE);
  tinygl_draw_message("321",origin ,1);


  timer_tick_t now;
  now = timer_get();
  timer_tick_t timeUp;
  timeUp = now + (timer_tick_t)(TIMER_RATE * 10);


  while(now < timeUp){
    pacer_wait();
    tinygl_update();
    now = timer_get();
  }
}


/** Set 2 digits score to be displayed
    @param char fitst digit of score
    @param char second digit of score. */
void setScoreForDisplay (char firstDigit, char secondDigit)
{
  char buffer[3];
  buffer[0] = firstDigit;
  buffer[1] = secondDigit;
  buffer[2] = '\0';
  tinygl_text (buffer);
}


/** use setScoreForDisplay and display score
    until the game is reset.
    @param score, score to be shown. */
void displayScore (int point)
{
   /* Set the font to use into smaller size
      so the text will able to display two digits of number. */
  tinygl_font_set (&font3x5_1);
  tinygl_text_dir_set (TINYGL_TEXT_DIR_ROTATE);
  tinygl_text_speed_set (MESSAGE_RATE);


  char firstDigit = ((point /10 ) % 10) + '0';
  char secondDigit = (point % 10) + '0';

  while(1){
      pacer_wait();
      tinygl_update ();
      setScoreForDisplay(firstDigit, secondDigit);
  }
}
