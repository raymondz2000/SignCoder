#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "display.h"
/* ----Raymondzhu 101158903 -- */
/* --------------------------------- function and constant prototype -------------------------------- */
unsigned char *findhorizontal(unsigned char vertical[]);
unsigned char *getvertical(char letter);
#define MAX_MESSAGE_SIZE  100;
/* ----------------------------- vertical array ----------------------------- */
unsigned char verticalarray[28][9]={
                                {16,40,68,68,124,68,68,238},//A
                                {248,68,72,124,66,66,66,252},//B
                                {58,70,130,128,128,130,70,58},//C
                                {248,68,66,66,66,66,68,248},//D
                                {254,66,64,120,64,64,66,254},//E
                                {254,66,66,72,120,72,64,224},//F
                                {62,66,128,158,146,130,66,60},//G
                                {238,68,68,124,68,68,68,238},//H
                                {254,16,16,16,16,16,16,254},//I
                                {62,8,8,8,200,136,136,112},//J
                                {238,68,72,112,72,68,68,238},//K
                                {224,64,64,64,64,64,66,254},//L
                                {198,108,84,84,68,68,68,238},//M
                                {206,100,84,84,76,68,68,238},//N
                                {56,68,130,130,130,130,68,56},//O
                                {252,66,66,126,64,64,64,224},//P
                                {124,130,130,130,130,146,124,16},//Q
                                {252,66,66,126,80,72,68,238},//R
                                {122,134,130,120,4,130,194,188},//S
                                {254,146,16,16,16,16,16,56},//T
                                {238,68,68,68,68,68,68,56},//U
                                {238,68,68,68,68,68,40,16},//V
                                {238,68,68,68,84,84,84,40},//W
                                {238,68,40,16,16,40,68,238},//X
                                {238,68,68,40,16,16,16,56},//Y
                                {254,130,4,24,32,64,130,254},//Z
                                {0,0,0,0,0,0,192,192},//DOT
                                {0,0,0,0,0,0,0,0},//SOACE
                                };

/* ------------------------- find horizontal function ------------------------ */
 unsigned char *findhorizontal(unsigned char vertical[]){
    unsigned char *horizontal=(unsigned char *)malloc(sizeof(unsigned char)*8);
    horizontal=calloc(8,sizeof(char));
    int i ,j;
    for(i=0; i<8; ++i){
        for(j=0; j<8; ++j){
            horizontal[i] = ( ( (vertical[j] & (1 << (7-i) ) ) >> (7-i) ) << j ) | horizontal[i];
        }
    }
  return horizontal;
 }

/* -------------------------- get vertical  array ------------------------- */
 unsigned char *getvertical(char letter){
     //check ASCII FOR SPACE AND DOT
    if ( letter >63){
        int d = letter;
        int vit = d-65; 
        return verticalarray[vit];
     }
     else{
        if(letter== ' '){
        return verticalarray[27];
       }
       if(letter=='.'){
        return verticalarray[26];
        }
     }
 }

/* -----------------------MAIN--------------------------------- */
int main() {
    char string[112]; 
    char orientation; 
    int numChars; 
     
    printf("Please Enter Your Orientation ('H' or 'V'):\n");
    scanf("%c", &orientation);
    printf("Please Enter Your Number:\n");
    scanf("%d", &numChars);
     
    numChars = numChars < 1 ? 1:numChars;
    numChars = numChars > MAX_CHARACTERS ? MAX_CHARACTERS:numChars;

    //count character
    int i = 0, j=0,count=0;
   
    memset(string, ' ',  112);
    string[numChars] = 0;

    while(getchar() != '\n');//CLEAR BUFFER
  
    printf("Please Enter Your Message:\n");
 
    int counter  = 0;
      //increment the index of the character array and receive less than 100 character,
      // also check uppercase
    while((string[i]=getchar())!='\n'&&(i<100)){
        if('a'<=string[i] && string[i] <= 'z'){
            string[i] -= 'a'-'A';
        }
        else if(string[i] == '.' || 'A'<=string[i] && string[i] <= 'Z'){
        }
        else{
            string[i] = ' ';
        }
        counter++;
	i++;
  }
	string[i]='\0';  //terminate string

    unsigned char *message=(unsigned char *)malloc(sizeof(unsigned char)*(12*(counter+numChars)));
    message=calloc((12*(counter+numChars)),sizeof(char));
	
    if(orientation=='V'||orientation=='v'){
        initializeWindow(VERTICAL, numChars);
        while(string[j]!='\0'){
            for(int i=0; i<9; ++i){
               message[count] = getvertical(string[j])[i];  
                count++;
            }
		j++;
	    }
    }
    else {
        initializeWindow(HORIZONTAL, numChars);
        while(string[j]!='\0'){
            for(int i=0; i<8; ++i){
               message[count] = findhorizontal(getvertical(string[j]))[i];    
                count++;
            } 
		j++;
	    }
    }
	
       displaySign(message, (12*(counter+numChars)));
    return 0;
}



