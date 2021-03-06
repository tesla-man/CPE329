/*
 * terminal.c
 *
 *  Created on: May 14, 2018
 *      Author: Contovasilis
 */

#include "term.h"
#include "delay.h"
#include "uart.h"
#include "string.h"



void termDmmSplash(void){
    float voltage = 1.254;
    uint8_t i = 255;
    printf("\033c");            //full reset
    textColor(WHITE, BLUE);
    printf("\033[2J");          //clear terminal
    printf("\033[H");           //home cursor
    printf("\033[?25l");        //hide cursor
    printf("\033[2h");
    printf("\033[8l");
    printf("\033[?1000h");      //enable click tracking

    bigText(0, 7, "Digital Multimeter");
    drawBox(0, 9, 10, 42);
    highlight(29, 9, 70, 18, YELLOW);
    text(0, 12, "CPE329-Jeff Gerfen");
    text(0, 13, "John Contovasilis & Andes Le");
    text(0, 14, "May 18, 2018");

}

void termMain(void){


    textColor(WHITE, BLUE);
    printf("\033[2J");          //clear terminal
    printf("\033[H");           //home cursor

    bigText(0,5,"");
    bigText(0,7,"");
    drawBox(3, 5, 3, 8);
    drawBox(13, 5, 3, 4);
    drawBarGraph(6, 10, 60);
    drawBarGraph(6, 15, 60);
    drawBarGraph(6, 20, 60);
    drawBarGraph(6, 24, 60);
}

void updateTermMode(uint8_t mode){
    printf("\033(B");
    switch(mode){
    case(0):
        textColor(WHITE, GREEN);
        bigText(4,6,"ACV/DCV");
        textColor(WHITE, BLUE);
        bigText(14,6,"FRQ");
        break;

    case(1):
        textColor(WHITE, GREEN);
        bigText(14,6,"FRQ");
        textColor(WHITE, BLUE);
        bigText(4,6,"ACV/DCV");
        break;
    }

}

void drawBox(uint8_t x, uint8_t y, uint8_t height, uint8_t width){
    if(x==0){
        x = (TERM_COL - width)/2;
    }
    printf("\033(0");
    printf("\033[%d;%dfl",y,x);
    printf("\033[%d;%dfk",y,x+width);
    printf("\033[%d;%dfj",y+height,x+width);
    printf("\033[%d;%dfm",y+height,x);


    drawHLine(x+1, y, width-1);
    drawHLine(x+1, y+height, width-1);
    drawVLine(x, y+1, height-1);
    drawVLine(x+width, y+1, height-1);
    printf("\033(B");
}

void drawHLine(uint8_t x, uint8_t y, uint8_t width){
    printf("\033(0");

    while(width){
        printf("\033[%d;%dfq",y,x+width-1);
        width--;
    }
    printf("\033(B");
}

void drawVLine(uint8_t x, uint8_t y, uint8_t height){
    printf("\033(0");
    while(height){
        printf("\033[%d;%dfx",y+height-1,x);
        height--;
    }
    printf("\033(B");
}

void text(uint8_t x, uint8_t y, char *string){
    if(x==0){
        x = (TERM_COL - strlen(string))/2;
    }
    printf("\033[%d;%df%s", y, x, string);
}

void bigText(uint8_t x, uint8_t y, char *string){
    if(x==0){
        x = (TERM_COL/2 - strlen(string))/2 + 1;
    }
    printf("\033[%d;%df\033#3%s", y, x, string);
    printf("\033[%d;%df\033#4%s", y+1, x, string);
}

void textColor(uint8_t fcolor, uint8_t bcolor){
    printf("\033[1;%d;%dm", fcolor+30, bcolor+40);
}


void highlight(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t color){
    uint8_t x;
    while(y2 > y1){
        x = x2;
        while(x > x1){
            printf("\033[%dm\033[%d;%df ", color+40, y2, x);
            x--;
        }
        y2--;
    }
}

void drawBarGraph(uint8_t x, uint8_t y, uint8_t width){
    printf("\033(0");
    printf("\033[%d;%dfx",y+1,x-1);
    printf("\033[%d;%dfx",y+1,x+width);
    while(width){
        printf("\033[%d;%dfs",y,x+width-1);
        printf("\033[%d;%dfo",y+2,x+width-1);
        width--;
    }
    printf("\033(B");
}

void updateRMS(uint16_t rms){
    uint8_t bars = 0, i = 0;
    uint8_t bararray[58];

    bars = (((rms*1000)/3000)*60)/1000 - bars;

    while(i < 57){
        if(i <= bars) bararray[i] = 'a';
        else if(i > bars) bararray[i] = ' ';
        i++;
    }
    printf("\033(0\033[%d;%df%s",11,6,bararray);
    printf("\033(B\033[10;30f\%5.3f Vrms", (float)rms/1000);

}

void updateFREQ(uint16_t freq){

    uint8_t bars = 0, i = 0;
    uint8_t bararray[58];

    bars = (freq*60)/1000 - bars;

    while(i < 57){
        if(i <= bars) bararray[i] = 'a';
        else if(i > bars) bararray[i] = ' ';
        i++;
    }
    printf("\033(0\033[%d;%df%s",16,6,bararray);
    printf("\033(B\033[15;30f\%5d Hz", freq);
}

void updatedcavg(int dcavg){

    uint8_t bars = 0, i = 0;
    uint8_t bararray[58];

    bars = ((((uint16_t)dcavg*1000)/3000)*60)/1000 - bars;

    while(i < 57){
        if(i <= bars) bararray[i] = 'a';
        else if(i > bars) bararray[i] = ' ';
        i++;
    }
    printf("\033(0\033[%d;%df%s",21,6,bararray);
    printf("\033(B\033[20;30f\%5.3f Vdc", (float) dcavg/1000);
}

void updatevpp(int vpp){

    uint8_t bars = 0, i = 0;
    uint8_t bararray[58];

    bars = ((((uint16_t)vpp*1000)/6000)*60)/1000 - bars;

    while(i < 57){
        if(i <= bars) bararray[i] = 'a';
        else if(i > bars) bararray[i] = ' ';
        i++;
    }
    printf("\033(0\033[%d;%df%s",25,6,bararray);
    printf("\033(B\033[24;30f\%5.3f Vpp", (float) vpp/1000);
}
