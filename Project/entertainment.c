/*
 * entertainment.c
 *
 *  Created on: Apr 15, 2018
 *      Author: alkoenen
 */

#include "open_interface.h"
#include "uart.h"



void init_Songs(){
    //setup
        unsigned char song[5] = {69,70,71,72,'\0'};
        unsigned char songdur[5] = {15,15,15,45,'\0'};
        oi_loadSong(0, 4, song, songdur);
}

void playSong(int num){
    oi_play_song(num);
}

void flash_leds(){
    int i;
    for(i=0; i<5; i++){
        oi_setLeds(1, 0, 255, 255);
        timer_waitMillis(1000);
        oi_setLeds(1, 0, 0, 255);
        timer_waitMillis(1000);
    }
}


