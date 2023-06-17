#include <stdio.h>
//#include <conio.h>
#include "GLCD.h"
#include <time.h>
//#include "KBD.h" 
#define __FI        1


char square[10] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
const char square2[10] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' }; //to clear the screen
int checkwin();
void board();
void clear_board();
char text1[20];
char text2[20];
char text3[20];
char winner[20];



int game()
{

    int player = 1, i, choice;

    int upper = 9;
    int lower = 1; 
    char mark;
	
while(1){
	
	do
    {
        board();
        player = (player % 2) ? 1 : 2; //player 1 = user, player 2 = computer (automated)

        if (player == 1) {
	    GLCD_SetTextColor(Red);
        GLCD_DisplayString(1, 0, __FI, "Player 1 turn"); 
				
				//FUNCTION TO GET VALUE
				//get_value(choice); 

				choice = 1; 
				
        mark = 'X';

        if (choice == 1 && square[1] == '1')
            square[1] = mark;

        else if (choice == 2 && square[2] == '2')
            square[2] = mark;

        else if (choice == 3 && square[3] == '3')
            square[3] = mark;

        else if (choice == 4 && square[4] == '4')
            square[4] = mark;

        else if (choice == 5 && square[5] == '5')
            square[5] = mark;

        else if (choice == 6 && square[6] == '6')
            square[6] = mark;

        else if (choice == 7 && square[7] == '7')
            square[7] = mark;

        else if (choice == 8 && square[8] == '8')
            square[8] = mark;

        else if (choice == 9 && square[9] == '9')
            square[9] = mark;

        else
        {
            GLCD_DisplayString(9, 4,__FI,"Invalid move");

            player--;
           //_getch();
        }
        i = checkwin();

        player++;
        }
    //Computer Move
    else if (player == 2) {

        srand(time(NULL));
        choice = (rand() % (upper - lower + 1)) + lower;
        mark = 'O';
	int allowed = 0;

	//Only do the move if its a legitiment one
	while (allowed == 0){
        if (square[choice] != 'X' && square[choice != 'O']){
            square[choice] = mark;
	    allowed = 1;
	}
            choice = (rand() % (upper - lower + 1)) + lower;
	}
        //else
            //player--; //allows it to again
        
        i = checkwin();

        player++;

   }
    } while (i == -1);
	}//while (1)
    board(); //to show final move 

    if (i == 1) {
        sprintf(winner,"==>Player %d wins", --player);
        clear_board(); //resets board for next game
        get_input(); 
        //exit to main menu after 5 sec
    }
    else {
        GLCD_DisplayString(8,0,__FI,"==>\aGame draw");
        clear_board(); //resets board for next game
        //exit to main menu after 5 sec
				get_input(); 
    }
    //_getch();
		#ifdef __USE_LCD
GLCD_DisplayString(8,0,__FI,(unsigned char *)winner);
    #endif	
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
    //GLCD_Clear(White); //clears screen, replace with glcd clear screen
    
    GLCD_SetTextColor(Blue);
    GLCD_DisplayString(0,4,__FI, "Tic Tac Toe");
  

    sprintf(text1, " %c  |  %c  |  %c ", square[1], square[2], square[3]);

    GLCD_DisplayString(4,0,__FI, "_________________");


    sprintf(text2, " %c  |  %c  |  %c ", square[4], square[5], square[6]);

    GLCD_DisplayString(6,0,__FI, "_________________");


    sprintf(text3, " %c  |  %c  |  %c ", square[7], square[8], square[9]);
	
#ifdef __USE_LCD
GLCD_SetTextColor(Blue);
GLCD_DisplayString(3,  2, __FI,  (unsigned char *)text1);
GLCD_DisplayString(5,  2, __FI,  (unsigned char *)text2);
GLCD_DisplayString(7,  2, __FI,  (unsigned char *)text3);
 #endif	
}

void clear_board() {
    for (int x = 1; x <= 9; x++)
        square[x] = square2[x];
   }


int get_value(int a){

	int counter = 1;

 a = counter;
	return a;  
}
