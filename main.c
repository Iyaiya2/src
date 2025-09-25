#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Position {
    int x;
    int y;
} Position;

typedef enum BoatOrientation {
    BOAT_HORIZONTAL,
    BOAT_VERTICAL
} BoatOrientation;

typedef struct Boat {
    Position position;
    int length;
    int orientation;
    int hit;
    int sunk;
} Boat;

typedef struct {

    char **board_template;
    int board_lines;
    int board_columns;

}Board;

void printf_board(Board *board)
{
    Board board1 = {
        .board_template = NULL,
        .board_lines = 0,
        .board_columns = 0      
    };

    
    printf("Veuillez entrer le nombre de lignes du plateau : ");
    fflush(stdin);
    scanf("%d", &(board1.board_lines));

    while(board1.board_lines > 26 )
    {
        printf("Veuillez recommencez !");

        printf("Veuillez entrer le nombre de lignes du plateau : ");
        fflush(stdin);
        scanf("%d", &(board1.board_lines));
    }

    board1.board_columns = board1.board_lines;

    char **boardL = malloc(sizeof(char*) * (board1.board_lines + 1));

    for(int i = 0; i < board1.board_lines+1; i++)
    {
        boardL[i] = malloc(sizeof(char) * (board1.board_columns + 1));

        for(int j = 0; j < board1.board_columns+1; j++)
        {
            if(i == 0 && j == 0){
                boardL[i][j] = ' ';
                printf("%c\t", boardL[i][j]);
            }
            else if(j == 0 && i > 0)
            {
                boardL[i][1] = 1;
                printf("%d\t", i);
            }
            else if(i == 0 && j > 0)
            {
                boardL[0][j] = 'A'+ (j-1);
                printf("%c\t", boardL[0][j]);
            }
            else
            {
                boardL[i][j] = '.';
                printf("%c\t", boardL[i][j]); 
            }
        }

        printf("\n");
        printf("\n");
    }


    for(int i = 0; i < board1.board_lines; i++)
    {
        free(boardL[i]);
    }
    
    free(boardL);
}


int main(void) {
    
    Board board2;

    printf_board(&board2);
    
    return 0;
}