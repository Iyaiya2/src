#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Position
{
    int x;
    int y;
} Position;

typedef enum BoatOrientation
{
    BOAT_HORIZONTAL,
    BOAT_VERTICAL
} BoatOrientation;

typedef struct Boat
{
    Position position;
    int length;
    int orientation;
    int hit;
    int sunk;
} Boat;

typedef struct
{

    char **board_template;
    int board_lines;
    int board_columns;

} Board;

void print_just_board(Board *board)
{
    for (int i = 0; i < board->board_lines + 1; i++)
    {
        for (int j = 0; j < board->board_columns + 1; j++)
        {
            if(i > 9 && j == 0)
            {
                printf("%d\t", i);
            }
            else
            {
                printf("%c\t", board->board_template[i][j]);
            }   
        }
        printf("\n");
    }
}

// Affiche le plateau de jeu de la bataille navale
void printf_board(Board *board)
{
    printf("Veuillez entrer le nombre de lignes du plateau : ");
    scanf("%d", &(board->board_lines));

    while (board->board_lines > 26 || board->board_lines < 5)
    {
        if (board->board_lines > 26)
            printf("Erreur vous ne pouvez pas avoir un plateau plus grand que la taille 26. Veuillez recommencez !\n");
        else
            printf("Erreur vous ne pouvez pas avoir un plateau plus petit que la taille 5. Veuillez recommencez !\n");

        printf("Veuillez entrer le nombre de lignes du plateau : ");
        scanf("%d", &(board->board_lines));
    }

    board->board_columns = board->board_lines;

    board->board_template = malloc(sizeof(char *) * (board->board_lines + 1));
    for (int i = 0; i < board->board_lines + 1; i++)
    {
        board->board_template[i] = malloc(sizeof(char) * (board->board_columns + 1));
        for (int j = 0; j < board->board_columns + 1; j++)
        {
            if (i == 0 && j == 0)
                board->board_template[i][j] = ' ';
            else if (j == 0 && i > 0)
                board->board_template[i][j] = '0' + i;
            else if (i == 0 && j > 0)
                board->board_template[i][j] = 'A' + (j - 1);
            else
                board->board_template[i][j] = '.';
            //printf("%c\t", board->board_template[i][j]);
        }
        //printf("\n");
    }
    //print_just_board(board);
}



// Affichage des navires en dur
void printf_boat(Board *board, char *type_Boat) /*, char *croiseur, char *destroyer, char *torpilleur*/
{

    if (strcmp(type_Boat, "PA") == 0)
    {
        int size_type_boat = 5;

        for(int i = 1; i < size_type_boat + 1; i++)
        {
            board->board_template[1][i] = 'P';
        }
        
    }
    else if (strcmp(type_Boat, "CR") == 0)
    {
        int size_type_boat = 4;

        for(int i = 2; i < size_type_boat + 2; i++)
        {
            board->board_template[i][4] = 'C';
        }
    }
    else if (strcmp(type_Boat, "DE") == 0)
    {
        int size_type_boat = 3;

        for(int i= 2; i < size_type_boat + 2; i++)
        {
            
            board->board_template[i][3] = 'D';
        }
    }
    else if (strcmp(type_Boat, "TO") == 0)
    {
        int size_type_boat = 2;

        for(int j= 1; j < size_type_boat + 1; j++)
        {
            board->board_template[3][j] = 'T';
        }
    }
        
    print_just_board(board);
    
}

char *demande_Type_Boat()
{
    char *demande;
    demande = malloc(sizeof(char) * 3);
    printf("Veuillez entrer le type de bateau que vous souhaitez (PA, CR, DE, TO) : ");
    scanf("%s", demande);

    while (strcmp(demande, "PA") != 0 && strcmp(demande, "CR") != 0 && strcmp(demande, "DE") != 0 && strcmp(demande, "TO") != 0)
    {
        printf("Erreur vous ne pouvez pas entrer ce type de bateau. Veuillez recommencez !\n");

        printf("Veuillez entrer le type de bateau que vous souhaitez (PA, CR, DE, TO) : ");
        scanf("%s", demande);
    }

   return demande;
}

int main()
{

    Board board2;

    printf_board(&board2);

    // char *type_Boat;

    int cTB = 0;

    while(cTB < 5)
    {
        char *type_Boat = demande_Type_Boat();
        printf_boat(&board2, type_Boat);
        cTB++;
    }

    return 0;
}