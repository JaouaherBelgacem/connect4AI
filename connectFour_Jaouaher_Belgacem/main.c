#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>

#include "Headers.h"


void welcome_screen()
{
    printf(">>>>>>>> Welcome To Connect four 2-player and 1-player minimax are implemented in this version <<<<<<<<\n\n");
    do
    {
        printf("Select 1 for  confirming Solo mode or 2 for two players mode\n\n");
        scanf("%d", &playMode);
    } while (playMode < 1 || playMode > 2);
}
void chooseColor() // this function is in case we implemented the interface
{
    printf ("*************************************************************************************************\n");
    printf("Please choose a color for your coin as the main player 1\n\n");
    printf(" R: Red \n or \n Y: Yellow\n");
    while (true)
    {
        scanf("%c",&playerColor);
         if (playerColor == 'R' || playerColor =='Y')
         {
             if (playerColor == 'R')
                {
                    printf(" the main player 1 chose the color: Red \n\n");
                    aiColor= 'Y';
                    // second player could be player2 or bot player
                    printf(" the second player  will play with the color: Yellow \n\n");
                    printf ("*************************************************************************************************\n");
                }
            else if (playerColor =='Y')
                {
                    printf(" Human player chose the color: Yellow \n\n");
                    aiColor='R';
                    printf(" the second player will play with the color: Red \n\n");
                    printf ("*************************************************************************************************\n");
                }
            break;
         }

           // colorCheck = true;
    }

}

void display_matrix()
{
    for (int i = rowsLength-1; i >= 0; i--)
    {
        for (int j = 0; j < columnsLength; j++)
        {
            printf(" %d ", matrix[i][j]);
        }
        printf("\n");
    }

    printf("\n");
    printf("\n");
}

void check_winner(int isBotVariable)
{
    // isBotVariable == 1 means the computer is playing
    if ((playerIndex % 2 + 1) == 1)
        printf("Player 1 Wins! \n");
    if ((playerIndex % 2 + 1) == 2)
    {
        if (isBotVariable == 0)
            printf("Player 2 Wins! \n");
        else
            printf("The Computer Wins! \n");
    }
    display_matrix();
    playerIndex = -5; // To Prevent the program from looping again
}

int occ_num_horiz(int x, int y, int playerIndex)
{
    int totPoints = 1;
    // go left search
    for (int i = y - 1; i >= 0; i--)
    {
        if (matrix[x][i] == playerIndex)
            totPoints++;
        else
            break;
    }
    // go right search
    for (int i = y + 1; i < columnsLength; i++)
    {
        if (matrix[x][i] == playerIndex)
            totPoints++;
        else
            break;
    }

    return totPoints;
}
// added
int occ_num_vert(int x, int y, int coinIndex)
{
    int count = 0;
    int points = 0;
    int isMatching = coinIndex;

    while (matrix[count][y] > 0)
    {
        if (matrix[count][y] != isMatching)
        {
            isMatching = matrix[count][y];
            points = 1;
        }
        else
        {
            points++;
        }
        count++;
    }
    // printf("\nAmount of points : %d\n", points);
    return points;
}
int occ_num_diag(int x, int y, int playerIndex)
{
/*
 to implement the
 [1 0 0 0]
 [0 1 0 0]
 [0 0 1 0]*/
    int totPoints = 1;
    int isNewPoint0 = 0;
    int isNewPoint1 = 0;

    for (int i = 1; i < columnsLength; i++)
    {
        // check diagonal top left to buttom right correct
        if ((x + i < rowsLength) && (y + i < columnsLength))
        {
            if (matrix[x + i][y + i] == playerIndex && isNewPoint0 == 0)
                totPoints++;
            else
                isNewPoint0 = 1;
        }
        if ((x - i >= 0) && (y - i >= 0))
        {
            if (matrix[x - i][y - i] == playerIndex && isNewPoint1 == 0)
                totPoints++;
            else
                isNewPoint1 = 1;
        }
    }
    return totPoints;
}

int occ_num_diag_2(int x, int y, int playerIndex)
{ /*
 to implement the
 [0 0 1 0]
 [0 1 0 0]
 [1 0 0 0]*/
    int totPoints = 1;
    int isNewPoint0 = 0;
    int isNewPoint1 = 0;

    for (int i = 1; i < columnsLength; i++)
    {
        if ((x - i >= 0) && (y + i < columnsLength))
        {
            if (matrix[x - i][y + i] == playerIndex && isNewPoint0 == 0)
            {
                totPoints++;
            }
            else
            {
                isNewPoint0 = 1;
            }
        }
        if ((y - i >= 0) && (x + i < columnsLength))
        {
            if (matrix[x + i][y - i] == playerIndex && isNewPoint1 == 0)
                totPoints++;
            else
                isNewPoint1 = 1;
        }
    }
    return totPoints;
}

int get_coin_placement_row(int matrixToTest[rowsLength][columnsLength], int coinIndex)
{
    int count = 0;
    int isMatching = matrixToTest[count][coinIndex];
    int recentCoint = matrixToTest[count][coinIndex];

    while (matrixToTest[count][coinIndex] > 0)
    {
        if (matrixToTest[count][coinIndex] != isMatching)
        {
            isMatching = matrixToTest[count][coinIndex];
        }
        count++;
    }
    return count;
}

int win_case(int row, int inputColumn)
{
    int currentOcc, maxOcc = 0;
    currentOcc = occ_num_horiz(row, inputColumn, playerIndex % 2 + 1);
    maxOcc = currentOcc;

    if (currentOcc >= connectLengthToWin)
    {
        return 100;
    }
    currentOcc = occ_num_diag(row, inputColumn, playerIndex % 2 + 1);
    if (maxOcc < currentOcc)
        maxOcc = currentOcc;

    if (currentOcc >= connectLengthToWin)
    {
        return 100;
    }
    currentOcc = occ_num_diag_2(row, inputColumn, playerIndex % 2 + 1);
    if (maxOcc < currentOcc)
        maxOcc = currentOcc;

    if (currentOcc >= connectLengthToWin)
    {
        return 100;
    }
    currentOcc = occ_num_vert(row, inputColumn, playerIndex % 2 + 1);
    if (maxOcc < currentOcc)
        maxOcc = currentOcc;

    if (currentOcc >= connectLengthToWin)
    {
        return 100;
    }

    return maxOcc;
}

void input_coin()
{
    int coinIndex = 0;
    int isMatching = -1;
    int points = 0;
    int coinPlacedRow = 0;
    do
    {
        printf("Press one of the options:\n");

        for (int i = 0; i < columnsLength; i++)
        {
            printf(" %d ", i);
        }
        printf("\n");
        scanf("%d", &coinIndex);
        coinPlacedRow = get_coin_placement_row(matrix, coinIndex);
    } while (coinIndex < 0 || coinIndex >= columnsLength || coinPlacedRow >= rowsLength);

    matrix[coinPlacedRow][coinIndex] = playerIndex % 2 + 1;

    if (win_case(coinPlacedRow, coinIndex) == 100)
        check_winner(0);
}

// AI Bot Section

int take_decision_min_max_based(int depth)
{
    // in this section we will give the bot the ability to priorotize the decision
    // by returning the column that will be played
    int maxEval = 0, maxEvalIndex = 0;

    for (int i = 0; i < columnsLength; i++)
    {
        if (evaluatedDecisionArray[depth][i] == 100)
            return i; // Best play of the bot

        if (maxEval < evaluatedDecisionArray[depth][i])
        {
            maxEvalIndex = i;
            maxEval = evaluatedDecisionArray[depth][i];
        }
    }
    return maxEvalIndex;
}

void copy_matrix()
{
    for (int i = 0; i < rowsLength; i++)
    {
        for (int j = 0; j < columnsLength; j++)
        {
            auxMatrix[i][j] = matrix[i][j];
        }
    }
}

void copy_to_simulated_matrix()
{
    for (int i = 0; i < rowsLength; i++)
    {
        for (int j = 0; j < columnsLength; j++)
        {
            simulatedMatrix[i][j] = matrix[i][j];
        }
    }
}
void back_to_normal_matrix_from_simulated()
{
    for (int i = 0; i < rowsLength; i++)
    {
        for (int j = 0; j < columnsLength; j++)
        {
            matrix[i][j] = simulatedMatrix[i][j];
        }
    }
}
void back_to_normal_matrix()
{
    for (int i = 0; i < rowsLength; i++)
    {
        for (int j = 0; j < columnsLength; j++)
        {
            matrix[i][j] = auxMatrix[i][j];
        }
    }
}

void evaulate_games(int depth)
{
    copy_matrix();
    int coinPlacedRow;
    printf("\n");
    for (int i = 0; i < columnsLength; i++)
    {
        coinPlacedRow = get_coin_placement_row(matrix, i);
        if (coinPlacedRow < rowsLength)
        {
            matrix[coinPlacedRow][i] = playerIndex % 2 + 1;
            if (depth % 2 == 0) // Bot level
                evaluatedDecisionArray[depth][i] = win_case(coinPlacedRow, i);
            else // Player Level
                evaluatedDecisionArray[depth][i] = -win_case(coinPlacedRow, i);
            printf("Depth %d Eval: %d \n", depth, evaluatedDecisionArray[depth][i]);
          // display_matrix(); // unlock the comment if you want to see how the bot thinks
            back_to_normal_matrix();
        }
    }
    printf("\n");
}

int simulate_games_min_max_based()
{
    copy_to_simulated_matrix();
    int initPlayerIndex = playerIndex;
    int decisionCol;
    int coinPlacedRow;

    for (int depth = 0; depth < treeDepth; depth++)
    {
        evaulate_games(depth);
        decisionCol = take_decision_min_max_based(depth);
        coinPlacedRow = get_coin_placement_row(matrix, decisionCol);
        matrix[coinPlacedRow][decisionCol] = playerIndex % 2 + 1;
        playerIndex++;
    }
    back_to_normal_matrix_from_simulated();
    playerIndex = initPlayerIndex;
    return decisionCol;
}


void play_bot()
{
    // Here are the logic behind the AI play

    //Basic Bot

    if(difLevel ==1)
    {

    //treeDepth=0;
    evaulate_games(0);
    int decisionCol = take_decision_min_max_based(0);
    int coinPlacedRow = get_coin_placement_row(matrix, decisionCol);
    matrix[coinPlacedRow][decisionCol] = playerIndex % 2 + 1;

    if (win_case(coinPlacedRow, decisionCol) == 100)
        check_winner(1);
    }

    /* Min Max Implementation not working perfectly */
    if(difLevel ==2)
    {
        //int treeDepth=3;
        int finalDecision = simulate_games_min_max_based();
        int coinPlacedRow = get_coin_placement_row(matrix, finalDecision);
        matrix[coinPlacedRow][finalDecision] = playerIndex % 2 + 1;

        if (win_case(coinPlacedRow, finalDecision) == 100)
        {
            check_winner(1);
        }

    }
}

// End of AI Bot Section

void play()
{

       // display_matrix();
        if (playMode == 2)
        {
            // Solo Mode
            printf("Here is version2 of 2players mode with a different logic \nAre you ready to play beat the other player?\n\n");
            chooseColor();
            do
            {
            input_coin();
            playerIndex++;
            display_matrix();
            }while (playerIndex >= 0);
        }
        else
        {
            chooseColor();
            printf("Are ready to play against the bot\n\n");
            printf("Choose a difficulty level: 1-Basic or 2-Advanced\n");
            scanf("%d", &difLevel);

            // Bot Mode
            do{
            input_coin();
            playerIndex++;
            play_bot();
            playerIndex++;
            display_matrix();
            }while (playerIndex >= 0);
        }
        //display_matrix();
   // } while (playerIndex >= 0);
}

void main()
{
    int reply; // this for choosing to quit the game or to restart it
    do{
         system("cls");
        //printf("\nWelcome to 4 Wins\n\n");
        printf ("\n\n");
        printf ("                                                                                          XXX   \n");
        printf ("    XXXXXXX   XXXXXXX  XXXX    XX  XXXX    XX  XXXXXXX  XXXXXXX  XXXXXXXXXX             XXXXX   \n");
        printf ("    XX        XX   XX  XX XX   XX  XX XX   XX  XX       XX           XX               XX   XX   \n");
        printf ("    XX        XX   XX  XX  XX  XX  XX  XX  XX  XXXXXXX  XX           XX              XX    XX   \n");
        printf ("    XX        XX   XX  XX   XX XX  XX   XX XX  XX       XX           XX             XXXXXXXXX   \n");
        printf ("    XXXXXXX   XXXXXXX  XX    XXXX  XX    XXXX  XXXXXXX  XXXXXXX      XX                    XX   \n");
        printf ("                                                                                                by group Jaouaher Belgacem\n\n");
        printf ("\n\n");
        printf ("*************************************************************************************************\n");
        printf ("  *RULES OF THE GAME:\n\n");
        printf ("   1:Play only one coin per turn\n");
        printf ("   2:place your coin only in an empty position\n");
        printf ("\n\n");
        printf ("*************************************************************************************************\n");
        printf ("  *GAME Instructions:\n\n");
        printf("    1: Choose a playing mode\n");
        printf("    2: Choose a color\n");
        printf("    3: Choose an available spot to place your coin\n");
        printf("    4: Choose an available spot to place your coin\n");
        printf("    5: If the game is over press any number to choose to restart or to quit\n");
        printf ("\n\n");
        printf ("*************************************************************************************************\n");


    welcome_screen();
    play();
    scanf("%d", &playerIndex); // To block the cmd from closing
    printf("Do you want to restart the game or to quit, press\n 0: Quit \n any other key to restart");
        scanf("%d", &reply);
        // to reset my matrix in case of restart game
        for (int i = rowsLength-1; i >= 0; i--)
        {
            for (int j = 0; j < columnsLength; j++)
            {
                // player index could be changes with whatever form
                 matrix[i][j]=0;
            }
            printf("\n");
        }
        //
    } while( reply=! 0);
}
