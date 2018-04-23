/*
 * entertainment.c
 *
 *  Created on: Apr 15, 2018
 *      Author: alkoenen
 */

#include "open_interface.h"
#include "uart.h"
#include <entertainment.h>

/**
 * Function that set up the notes for the songs that the bot would play,
 * along with the duration
 */
void init_Songs(){
    //setup
        unsigned char song[5] = {69,70,71,72,'\0'};
        unsigned char songdur[5] = {15,15,15,45,'\0'};
		
		unsigned char song2[12] = {69,69,69,69,70,
									70,70,70,71,70,
									69, '\0'};
		unsigned char song2dur[12] = {10,10,10,10,
										10,10,10,10,
										15,15,25,'\0'};
        oi_loadSong(0, 4, song, songdur);
		oi_loadSong(1, 11, song2, song2dur);
}

/**
 * Function that played the song over the open interface of the robot
 */
void playSong(int num){
    oi_play_song(num);
}

/**
 * Function would flash the leds when the robot would enter the goal of the maze
 */
void flash_leds(){
    int i;
    for(i=0; i<5; i++){
        oi_setLeds(1, 0, 255, 255);
        timer_waitMillis(1000);
        oi_setLeds(1, 0, 0, 255);
        timer_waitMillis(1000);
    }
}


