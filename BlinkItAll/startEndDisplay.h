/** @file   startEndDisplay.h
    @author Kanyakorn Kitisopakul 18582950
            Lukpla Worathongchai  65098184
    @team   Team_25 - Blink it on
    @date   15 October 2015
    @brief module for display message - before or after game begins.
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


#define TIMER_RATE (F_CPU / TIMER_CLOCK_DIVISOR)


/** Define speed which message will be displayed. */
#define MESSAGE_RATE 10


/** Countdown with a message '3 2 1'*/
void countdown(void);

/** Set 2 digits score to be displayed
    @param char fitst digit of score
    @param char second digit of score. */
void setScoreForDisplay (char firstDigit, char secondDigit);


/** use setScoreForDisplay and display score
    until the game is reset.
    @param score, score to be shown */
void displayScore (int score);
