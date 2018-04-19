/*
 * sensors.c
 *
 *  Created on: Apr 15, 2018
 *      Author: alkoenen
 */
#include "open_interface.h"
#include "uart.h"

uint16_t Cliff = 0;
uint16_t Boundary = 0;

int closeTo(int value, int target, int range){
    if((value >= (target-range))
            && (value <= (target+range))){
        return 1;
    }
    else{
        return 0;
    }
}

int sensors_CheckCliff(oi_t *sensor_data){
    int cliffFL = sensor_data->cliffFrontLeft;
    int cliffFR = sensor_data->cliffFrontRight;
    int cliffL = sensor_data->cliffLeft;
    int cliffR = sensor_data->cliffRight;
    //add uart controls here
    Cliff = 0;
    if(cliffFL && cliffFR){
        uart_sendStr("Drop Center\n\r");
        Cliff = 1;
    }
    else if(cliffFL){
        uart_sendStr("Drop Leftcenter\n\r");
        Cliff = 1;
    }
    else if(cliffFR){
        uart_sendStr("Drop Rightcenter\n\r");
        Cliff = 1;
    }
    if(cliffL){
        uart_sendStr("Drop Left\n\r");
        Cliff = 1;
    }
    if(cliffR){
        uart_sendStr("Drop Right\n\r");
        Cliff = 1;
    }
    if(Cliff){
        return 1;
    }
    else{
        return 0;
    }
}

int sensors_CheckBorder(oi_t *sensor_data){
    int borderFL = sensor_data->cliffFrontLeftSignal;
    int borderFR = sensor_data->cliffFrontRightSignal;
    int borderL = sensor_data->cliffLeftSignal;
    int borderR = sensor_data->cliffRightSignal;
    //add uart controls here
    int tape = 2770;
    int range = 50;

    Boundary = 0;
    if((closeTo(borderFL, tape, range) == 1)  && (closeTo(borderFR, tape, range) == 1)){
        uart_sendStr("Tape Center\n\r");
        Boundary = 1;
    }
    else if(closeTo(borderFL, tape, range) == 1){
        uart_sendStr("Tape Leftcenter\n\r");
        Boundary = 1;
    }else if(closeTo(borderFR, tape, range) == 1){
        uart_sendStr("Tape Rightcenter\n\r");
        Boundary = 1;
    }
    if(closeTo(borderL, tape, range) == 1){
        uart_sendStr("Tape Left\n\r");
        Boundary = 1;
    }
    if(closeTo(borderR, tape, range) == 1){
        uart_sendStr("Tape Right\n\r");
        Boundary = 1;
    }
    if(Boundary){
        return 1;
    }
    else{
        return 0;
    }
}










