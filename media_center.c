#include <stdio.h>
#include <stdlib.h>
#include "LPC17xx.h"                       
#include "GLCD.h"
#include "LED.h"
#include "KBD.h"

#include "Dog.c" 
#include "Lamb.c" 
#include "Fox.c"
#include "Tiger.c"


#define __FI        1                   /* Font index 16x24         */
#define __USE_LCD   0										/* Uncomment to use the LCD */

//ITM Stimulus Port definitions for printf //////////////////
#define ITM_Port8(n)    (*((volatile unsigned char *)(0xE0000000+4*n)))
#define ITM_Port16(n)   (*((volatile unsigned short*)(0xE0000000+4*n)))
#define ITM_Port32(n)   (*((volatile unsigned long *)(0xE0000000+4*n)))

#define DEMCR           (*((volatile unsigned long *)(0xE000EDFC)))
#define TRCENA          0x01000000

struct __FILE { int handle;  };
FILE __stdout;
FILE __stdin;

int fputc(int ch, FILE *f) {
  if (DEMCR & TRCENA) {
    while (ITM_Port32(0) == 0);
    ITM_Port8(0) = ch;
  }
  return(ch);
}


char text[10];
char text_l[10];

//FOR THE GAME
char square[10] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
const char square2[10] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' }; //to clear the screen
int choice = 0;
int choice2 = 0;
int checkwin();
void board();
void clear_board();
char text1[20];
char text2[20];
char text3[20];
char text4[20];
char text5[20];

uint32_t direction = 1; //Current direction
int main(void) {
	
 
  uint32_t prev_dir; 
  LED_Init();                    /* LED Initialization            */
  KBD_Init();   				 /* Joystick initialization       */
  
	#ifdef __USE_LCD
  GLCD_Init();                               /* Initialize graphical LCD (if enabled */

  GLCD_Clear(White);                         /* Clear graphical LCD display   */
  GLCD_SetBackColor(Blue);
  GLCD_SetTextColor(White);
  GLCD_DisplayString(0, 0, __FI, "      Main Menu                 ");
  GLCD_DisplayString(1, 0, __FI, "   Use Joystick to           ");
  GLCD_DisplayString(2, 0, __FI, "       Navigate              ");

  
	
	GLCD_SetBackColor(White);
  GLCD_SetTextColor(Blue);
  GLCD_DisplayString(5, 0, __FI, "Select Option");
	GLCD_DisplayString(6, 0, __FI, "-------------");
	GLCD_DisplayString(7, 0, __FI, "Photo Gallery - Left");
	GLCD_DisplayString(8, 0, __FI, "MP3 Player - Up");
	GLCD_DisplayString(9, 0, __FI, "Game - Right");


#endif


while (1) {       
	
//int counter = 0; //To determine Which application to execute once KBD_Select is pressed
	
	direction = get_button();
//navigate through 3 options counter =1,2,3
//after 3 times, should go back to start, so counter = 1 again then

		
switch (direction)
{
	
	case KBD_LEFT:{
	//Highlight Photo Gallery	
	GLCD_SetBackColor(Red);
  GLCD_SetTextColor(White);	
	GLCD_DisplayString(7, 0, __FI, "Photo Gallery - Left");
	GLCD_SetBackColor(White);
  GLCD_SetTextColor(Blue);
	GLCD_DisplayString(8, 0, __FI, "MP3 Player - Up");
	GLCD_DisplayString(9, 0, __FI, "Game - Right");

		prev_dir= KBD_LEFT;
	break;
	}
	case KBD_UP:{
	//Highlight MP3 Player
 	
  GLCD_SetBackColor(White);
  GLCD_SetTextColor(Blue);	
	GLCD_DisplayString(7, 0, __FI, "Photo Gallery - Left");
	GLCD_SetBackColor(Red);
  GLCD_SetTextColor(White);
	GLCD_DisplayString(8, 0, __FI, "MP3 Player - Up");;
	GLCD_SetBackColor(White);
  GLCD_SetTextColor(Blue);
	GLCD_DisplayString(9, 0, __FI, "Game - Right");	

		prev_dir= KBD_UP;
	break;
	}
	case KBD_RIGHT:{
	//Highlight Game

  GLCD_SetBackColor(White);
  GLCD_SetTextColor(Blue);	
	GLCD_DisplayString(7, 0, __FI, "Photo Gallery - Left");
	GLCD_SetBackColor(White);
  GLCD_SetTextColor(Blue);
	GLCD_DisplayString(8, 0, __FI, "MP3 Player - Up");;
	GLCD_SetBackColor(Red);
  GLCD_SetTextColor(White);
	GLCD_DisplayString(9, 0, __FI, "Game - Right");
	GLCD_SetBackColor(White);
  GLCD_SetTextColor(Red);
	
		prev_dir= KBD_RIGHT;
	break;
	}
	
	case KBD_SELECT:{
		if (prev_dir == KBD_LEFT){ //PHOTO
			GLCD_Clear(White);
    	photo();
		 
		}
		else if (prev_dir == KBD_UP){ //MP3
	GLCD_DisplayString(3,0,__FI,"Not Implemented");

	}
		else if (prev_dir == KBD_RIGHT){ //GAME
		GLCD_Clear(White);
		game(); 
	}
}
 }//switch(direction)

 
 #ifdef __USE_LCD
    GLCD_SetTextColor(Red);
		GLCD_DisplayString(4,  0, __FI,  (unsigned char *)text);

		
 #endif		
	}	//while(1)
}//int main

int photo(void){
GLCD_SetTextColor(Blue);
GLCD_DisplayString (5,0,__FI,"     Use Joystick");
GLCD_DisplayString (6,0,__FI,"       to scroll");


while(1){	
		GLCD_SetTextColor(Red);	
    GLCD_DisplayString (9,0,__FI,"   SELECT for Menu");	
direction = get_button();	
	if (direction == KBD_DOWN){
		GLCD_Clear(White);
		GLCD_Bitmap(80,70,DOG_WIDTH,DOG_HEIGHT,(unsigned char*)DOG_pixel_data); 
			}	
	if (direction == KBD_LEFT){
		GLCD_Clear(White);
		GLCD_Bitmap(80,70,LAMB_WIDTH,LAMB_HEIGHT,(unsigned char*)LAMB_pixel_data); 
	}
	if (direction == KBD_UP){
		GLCD_Clear(White);
		GLCD_Bitmap(80,70,FOX_WIDTH,FOX_HEIGHT,(unsigned char*)FOX_pixel_data); 
	}
	if (direction == KBD_RIGHT){
		GLCD_Clear(White);
		GLCD_Bitmap(80,70,TIGER_WIDTH,TIGER_HEIGHT,(unsigned char*)TIGER_pixel_data); 
	}
 if (direction == KBD_SELECT){
	 GLCD_Clear(White);
	 main();
 }
}
}


int game()
{
		
    int player = 1, i;
		
		int done;
    int upper = 9;
    int lower = 1; 
    char mark;
		//int allowed1 = 0; //Player
		//int allowed2 = 0; //Comp

while (1){	

	do
	{
			
		while (player == 1){
			 mark = 'X';
       board(); 

		   choice = get_value();

		   if (choice == 1 && square[1] == '1'){
            square[1] = mark;
				 		 done=1;
						
				}
        else if (choice == 2 && square[2] == '2'){
            square[2] = mark;
				 done=1;
				}
        else if (choice == 3 && square[3] == '3'){
            square[3] = mark;
				 done=1;
				}
        else if (choice == 4 && square[4] == '4'){
            square[4] = mark;
					 done=1;
				}
        else if (choice == 5 && square[5] == '5'){
            square[5] = mark;
					 done=1;
				}
        else if (choice == 6 && square[6] == '6'){
            square[6] = mark;
					 done=1;
				}
        else if (choice == 7 && square[7] == '7'){
            square[7] = mark;
					 done=1;
				}
        else if (choice == 8 && square[8] == '8'){
            square[8] = mark;
					 done=1;
				}
        else if (choice == 9 && square[9] == '9'){
            square[9] = mark;
			  done=1;
				}
					else
        {
            GLCD_DisplayString(9, 4,__FI,"Invalid move");
          }		

				
		   while (done == 1){
				 mark = 'O';
				 
				 choice2 = (rand()% (upper + lower -1))+ lower;
				if (choice2 == 1 && square[1] == '1'){
						square[1] = mark;
				 done=0;
						
				}
        else if (choice2 == 2 && square[2] == '2'){
            square[2] = mark;
				 done=0;
				}
        else if (choice2 == 3 && square[3] == '3'){
            square[3] = mark;
				 done=0;
				}
        else if (choice2 == 4 && square[4] == '4'){
            square[4] = mark;
					 done=0;
				}
        else if (choice2 == 5 && square[5] == '5'){
            square[5] = mark;
					 done=0;
				}
        else if (choice2 == 6 && square[6] == '6'){
            square[6] = mark;
					 done=0;
				}
        else if (choice2 == 7 && square[7] == '7'){
            square[7] = mark;
					 done=0;
				}
        else if (choice2 == 8 && square[8] == '8'){
            square[8] = mark;
					 done=0;
				}
        else if (choice2 == 9 && square[9] == '9'){
            square[9] = mark;
			  done=0;
				}
				
			 }
				  i = checkwin();
					if (i != -1)
						player++;
					else	
						player =1;
			}	
		
			
				

    } while (i == -1);

    board(); //to show final move 

    if (i == 1) {
			GLCD_SetTextColor(Red);
     GLCD_DisplayString(9,0,__FI,"Game Over,Pls Wait");
			for (int wait; wait<=60000000;wait++){
			}
		clear_board(); //resets board for next game
			main();
			
        
        //exit to main menu after 5 sec
    }
    else {
        GLCD_DisplayString(9,0,__FI,"Draw Game,Pls Wait");
					for (int wait; wait<=60000000;wait++){
			}
			clear_board(); //resets board for next game
       main();
    }
    //_getch();
	
		
		}
return 0;
}

int checkwin()
{
    if (square[1] == square[2] && square[2] == square[3])
        return 1;

    else if (square[4] == square[5] && square[5] == square[6])
        return 1;

    else if (square[7] == square[8] && square[8] == square[9])
        return 1;

    else if (square[1] == square[4] && square[4] == square[7])
        return 1;

    else if (square[2] == square[5] && square[5] == square[8])
        return 1;

    else if (square[3] == square[6] && square[6] == square[9])
        return 1;

    else if (square[1] == square[5] && square[5] == square[9])
        return 1;

    else if (square[3] == square[5] && square[5] == square[7])
        return 1;

    else if (square[1] != '1' && square[2] != '2' && square[3] != '3' &&
        square[4] != '4' && square[5] != '5' && square[6] != '6' && square[7]
        != '7' && square[8] != '8' && square[9] != '9')

        return 0;
    else
        return  -1;
}
//1 = Winner
//-1 = In progress
//O = Draw


//Update board after every move
void board()
{
    //change to print glcd command
    GLCD_Clear(White); //clears screen, replace with glcd clear screen
    
    GLCD_SetTextColor(Blue);
    GLCD_DisplayString(0,4,__FI, "Tic Tac Toe");
   GLCD_DisplayString(1, 4, __FI, "Enter Value");

    sprintf(text1, " %c  |  %c  |  %c ", square[1], square[2], square[3]);

    GLCD_DisplayString(4,0,__FI, "  _______________");


    sprintf(text2, " %c  |  %c  |  %c ", square[4], square[5], square[6]);

    GLCD_DisplayString(6,0,__FI, "  _______________");


    sprintf(text3, " %c  |  %c  |  %c ", square[7], square[8], square[9]);
	 sprintf(text5,"Last Choice = %d",choice); 
#ifdef __USE_LCD
    GLCD_SetTextColor(Blue);
		GLCD_DisplayString(3,  2, __FI,  (unsigned char *)text1);
GLCD_DisplayString(5,  2, __FI,  (unsigned char *)text2);
GLCD_DisplayString(7,  2, __FI,  (unsigned char *)text3);
	GLCD_DisplayString(8,0,__FI,(unsigned char*) text5);

 #endif	
}

void clear_board() {
    for (int x = 1; x <= 9; x++)
        square[x] = square2[x];
	
   }


int get_value(){
	
	int a = 0;
	int temp=0;
	
		#ifdef __USE_LCD
		GLCD_SetTextColor(Red);
		GLCD_DisplayString(2,  2, __FI,  (unsigned char *)text4);
	  #endif	
	
//direction = KBD_DOWN;	
		while (temp == 0){
			direction = get_button();
				if (direction == KBD_DOWN){
					a++;
					if(a == 10)
						a = 1;
			
					board();
				}
				else if (direction == KBD_SELECT){ //reset
					clear_board();
					main();
				}
				else if (direction == KBD_RIGHT){
					temp = 1;
				}
		}
	
	return a; 	
}	

