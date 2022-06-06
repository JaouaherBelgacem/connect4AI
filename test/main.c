#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>
#include <conio.h>

//#define r  6
//#define c  7
#define ROWS    6
#define COL     7
int playingMode, playingLevel;
int playerTurn = 0, aiTurn= 1;
char playerColor, aiColor;
char playerColor1='X', aiColor1= 'O';
//char playBoard [r][c];
char positionIndicator[]= " 0   1   2   3   4   5   6 ";
char playBoard [6][7];
bool colorCheck= false, gameOver = false, winner= false;


void welcomeBoard()
{
    printf ("\n\n");
    printf ("                                                                                          XXX   \n");
    printf ("    XXXXXXX   XXXXXXX  XXXX    XX  XXXX    XX  XXXXXXX  XXXXXXX  XXXXXXXXXX             XXXXX   \n");
	printf ("    XX        XX   XX  XX XX   XX  XX XX   XX  XX       XX           XX               XX   XX   \n");
	printf ("    XX        XX   XX  XX  XX  XX  XX  XX  XX  XXXXXXX  XX           XX              XX    XX   \n");
	printf ("    XX        XX   XX  XX   XX XX  XX   XX XX  XX       XX           XX             XXXXXXXXX   \n");
	printf ("    XXXXXXX   XXXXXXX  XX    XXXX  XX    XXXX  XXXXXXX  XXXXXXX      XX                    XX   \n");
	printf ("\n\n");
	printf ("  *RULES OF THE GAME:\n\n");
    printf ("   1:Play only one coin per turn:\n");
    printf ("   2:place your coin only in an empty position:\n");
    printf ("\n\n");
    printf ("  *GAME Instructions:\n\n");
    printf("    1: Choose a playing mode\n");
    printf("    2: Choose a color\n");
    printf("    3: Choose an available spot to place your coin\n");
    printf("    4: Choose an available spot to place your coin\n");
    printf ("\n\n\n\n");

}
void chooseMode()
{
    int choice;
    printf ("Please choose a game mode\n 1: 1 player mode \n 2: 2 players mode\n");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
        printf (" welcome to the one player mode!\n Are you ready to challenge the AI?\n\n the player has to choose a color symbol first!\n\n Please choose one of these:\n");
        // call the functions related to one player mode
        break;
    case 2:
        printf (" welcome to the two player mode!\n Are you ready for starting the game?\n\n");
        //call functions related to 2 players mode
        break;
    default:
        break;
    }
}
void chooseColor()
{

    while (true)
    {
        printf(" R: Red \n or \n Y: Yellow\n");
        scanf("%c",&playerColor);
         if (playerColor == 'R' || playerColor =='Y')
         {
             if (playerColor == 'R')
                {
                    printf(" Human player chose the color: Red \t it will be represented by symbol X\n\n");
                    aiColor= 'Y';
                    printf(" AI player will play with the color: Yellow  \t it will be represented by symbol O\n\n");
                }
            else if (playerColor =='Y')
                {
                    printf(" Human player chose the color: Yellow  \t it will be represented by symbol X\n\n");
                    aiColor='R';
                    printf(" AI player will play with the color: Red \ \t it will be represented by symbol O n\n");
                }
            break;
         }

           // colorCheck = true;
    }

}


void initiazePlayingBoard()
{
    int i,j;
    for(i=0; i<6; i++)
    {

        for(j=0; j<7; j++)
        {
           playBoard[i][j]=' ';
        }
        printf("\n");
    }
}

void playingBoard()
{
    //system("cls");
    printf("%s\n", positionIndicator);
    int i, j;
    printf("\n");
    for(i=0; i<6; i++)
    {
        if (i)
        {
           printf("-----------------------------\n");
        }
        for(j=0; j<7; j++)
        {
            if(j)
            {
                printf("|");
            }
            printf(" ");
            if(playBoard[i][j]==' ')
                {
             printf(" ");
                }
            else
            {
                printf("%c", playBoard[i][j]);
            }
            printf(" ");
        }
        printf("\n");
    }
    printf("\n");
}
void playerMove()
{


     while(true)
     {
         int cell, level;
         printf("Please enter an empty cell number (0 - 6) where you want to place your coin\n\n");
         scanf("%d", &cell);


             if (cell >= 0 && cell <= 6 && playBoard[0][cell] == ' ' )
                {
                    for (level= ROWS-1; level >=0; level --) // to display symbols form the bottom to the top
                    {
                        if (playBoard[level][cell] == ' ')
                        {
                            playBoard[level][cell] = playerColor1;
                            break;
                        }

                    }
//
                }
                playingBoard();

         break;
     }


}
/*void*/
int win(char playBoard[6][7])
{

    int i, j;

     // check for horizontal
    //for(i=0; i<6; i++)
    for (i= ROWS-1; i >=0; i --)
    {
        for(j=0; j<4; j++)
        {
             if (playBoard[i][j]=='X' &&playBoard[i][j+1]=='X' && playBoard[i][j+2]=='X' && playBoard[i][j+3]=='X')
             {
                winner= true;
                printf("Human player is the winner");
                return -2;
            }
           else if (playBoard[i][j]=='O' &&playBoard[i][j+1]=='O' && playBoard[i][j+2]=='O' && playBoard[i][j+3]=='O')
             {
                winner= true;
                printf("AI player is the winner");
                return 2;
            }
        }
    }

         // check for vertical
    for(j=0; j<7; j++)
    {
       // for(i=0; i<5; i++)
       for (i= ROWS-1; i >=2; i --)
        {
             if (playBoard[i][j]=='X' &&playBoard[i+1][j]=='X' && playBoard[i+2][j]=='X' && playBoard[i+3][j]=='X')
             {
                winner= true;
                printf("Human player is the winner");
                return -2;
            }
           else if (playBoard[i][j]=='O' &&playBoard[i+1][j]=='O' && playBoard[i+2][j]=='O' && playBoard[i+3][j]=='O')
             {
                winner= true;
                printf("AI player is the winner");
                return 2;
            }
        }
    }

    // check for diagonal
    for (int i = 0; i < 4; i++)
        {
                for (int j = 0; j < 4; j++)
                {

                        if (playBoard[i][j]== 'X' && playBoard[i+1][j+1] == 'X' && playBoard[i+2][j+2]== 'X' && playBoard[i+3][j+3]== 'X')
                            {
                                winner= true;
                                printf("Human player is the winner");
                                return -2;
                            }
                        else if (playBoard[i][j]== 'O' && playBoard[i+1][j+1] == 'O' && playBoard[i+2][j+2]== 'O' && playBoard[i+3][j+3]== 'O')
                            {
                                winner= true;
                                printf("AI player is the winner");
                                return 2;
                            }

                        else if (playBoard[6-i][j]== 'X' && playBoard[5-i][j+1]== 'X' && playBoard[4-i][j+2]== 'X' && playBoard[3-i][j+3]== 'X')
                            {
                                winner= true;
                                printf("Human player is the winner");
                                return -2;
                            }
                        else if (playBoard[6-i][j]== 'O' && playBoard[5-i][j+1]== 'O' && playBoard[4-i][j+2]== 'O' && playBoard[3-i][j+3]== 'O')
                            {
                                winner= true;
                                printf("AI player is the winner");
                                return 2;
                            }
                        else if (playBoard[i][5-j]== 'X' && playBoard[i+1][4-j]== 'X' && playBoard[i+2][3-j]== 'X' && playBoard[i+3][2-j]== 'X')
                            {
                                winner= true;
                                printf("Human player is the winner");
                                return -2;
                            }
                        else if (playBoard[i][5-j]== 'O' && playBoard[i+1][4-j]== 'O' && playBoard[i+2][3-j]== 'O' && playBoard[i+3][2-j]== 'O')
                            {
                                winner= true;
                                printf("AI player is the winner");
                                return 2;
                            }
                        else if (playBoard[6-i][5-j]== 'X' && playBoard[5-i][4-j]== 'X' && playBoard[4-i][3-j]== 'X' && playBoard[3-i][2-j]== 'X')
                            {
                                winner= true;
                                printf("Human player is the winner");
                                return -2;
                            }
                            else if (playBoard[6-i][5-j]== 'O' && playBoard[5-i][4-j]== 'O' && playBoard[4-i][3-j]== 'O' && playBoard[3-i][2-j]== 'O')
                            {
                                winner= true;
                                printf("AI player is the winner");
                                return 2;
                            }
                }
        }
}
int checkGameOver(char playBoard[6][7])
{
    // game could be over if the board it full and no winner
    for (int i= 0; i<6; i++)
    {
        for(int j= 0; j<7; j++)
        {


            if (playBoard[i][j] == ' ')
            {

               gameOver= false;
               return 0 ;// game not finished
            }

        }
        if (gameOver)
        {
            return 1;
        }

    }
    return 0;
}
bool checkWin()
{
    // game  over once we have a winner

    win(playBoard[6][7]);

    if (winner == true)
    {
        return true;
    }
    else
    {
        return false;
    }

}
  //firstAttempt to know the recursive
int minimax ( char playBoard[6][7],int depth, bool isMiximizing,  bool firstAttempt)
{
    firstAttempt= true;
    int notOver = checkGameOver(playBoard[6][7]);
    int result = win(playBoard[6][7]);
    if ( depth == 0 || notOver == 0 || result !=1)// depth 0 leave
    {
        return result;
    }

    if(isMiximizing)
    {   int finalBestScore = -50;
        int bestI, bestJ;
        for( int i=0; i<6; i++)
        {
            for(int j=0; j<7; j++)
            {
                if (playBoard[i][j]== ' ')
                {
                    playBoard[i][j]= 'X'; // play in the opponent side: maximizing
                    int score = minimax(playBoard, depth -1, false, false); // recursive min max
                    playBoard[i][j]= ' '; // remove the moves after calculating score
                    if ( score > finalBestScore)
                    {
                        finalBestScore = score;
                        bestI= i;
                        bestJ= j;
                    }
                    if(firstAttempt)
                    {
                         printf ("score", i, ",", j, ":", score, "\n\n");
                    }
                }
            }
        }
        return finalBestScore;
    }
    else
    {
        int finalBestScore = 50;
        int bestI, bestJ;
        for( int i=0; i<6; i++)
        {
            for(int j=0; j<7; j++)
            {
                if (playBoard[i][j]== ' ')
                {
                    playBoard[i][j]= 'O'; // minimizing
                    int score = minimax(playBoard, depth -1, true, false); // recursive min max
                    playBoard[i][j]= ' '; // remove the moves after calculating score
                    if ( score < finalBestScore)
                    {
                        finalBestScore = score;
                        bestI= i;
                        bestJ= j;
                    }
                    if(firstAttempt)
                    {
                         printf ("score", i, ",", j, ":", score, "\n");

                    }

                }
            }
        }
        if(firstAttempt)
        {
            playBoard[bestI][bestJ]= 'O';
        }
        return finalBestScore;
    }
}
void playGame()
{
   // while(true)
  // do {
        playerMove();
        playingBoard();
       // checkGameOver(playBoard);
      /*  if (gameOver == true)
        {
            printf("Game is over with no winner");
            return ;
        }
        else if (checkWin())
        {
                printf(" Game is over \n");
                return;
        }
        // break;
    //}
    }while(gameOver == false || winner== false);*/

}

int main (int argc, char *argv[])
{
    bool firstAttempt= true;
    bool gameOver= false;
    bool winner = false;
    int currentTurn =0;
    welcomeBoard();
    chooseMode();
    chooseColor();
    initiazePlayingBoard();
    //win(playBoard[6][7]);
    //checkGameOver(playBoard[6][7]);
    do
    {
        int playerTurn = 0, aiTurn= 1;
        if ( currentTurn == playerTurn)
        {
            playingBoard();
            //playerMove();

            playGame();
            win(playBoard[6][7]);
            checkGameOver(playBoard[6][7]);

            currentTurn += 1;
        }
        else if ( currentTurn == aiTurn)
        {
            playingBoard();
            minimax(playBoard,200,false, false );
            win(playBoard[6][7]);
            checkGameOver(playBoard[6][7]);

            currentTurn -= 1;
        }

    } while(gameOver == false || winner== false);
}
