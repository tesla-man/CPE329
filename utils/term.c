/*
 * terminal.c
 *
 *  Created on: May 14, 2018
 *      Author: Contovasilis
 */

#include "term.h"


void termDmmSplash(void){
    printf("\033[2J");       //clear terminal
    printf("\033[H");        //home cursor
    printf("\033)2");
    //printf("\033[%dm", 44); //set cyan bg
    printf("\033[5;%dm", 97); //set white text
    printf("bold");

}

void termDmmDC(void){

}

void termDmmAC(void){

}

void termDmmBargraph(void){

}




