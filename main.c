#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

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
} Board;



void print_just_board(Board *board) {
    for (int i = 0; i < board->board_lines + 1; i++) {
        for (int j = 0; j < board->board_columns + 1; j++) {
            if (i > 9 && j == 0)
                printf("%d\t", i);
            else
                printf("%c\t", board->board_template[i][j]);
        }
        printf("\n");
    }
}

// ==================== VALIDATION / PLACEMENT ====================

int can_place_ship(Board *board, int start_row, int start_col, int length, int orientation) {
    if (orientation == BOAT_HORIZONTAL) {
        if (start_col + length - 1 > board->board_columns)
            return 0;
        for (int c = start_col; c < start_col + length; c++)
            if (board->board_template[start_row][c] != '.')
                return 0;
    } else {
        if (start_row + length - 1 > board->board_lines)
            return 0;
        for (int r = start_row; r < start_row + length; r++)
            if (board->board_template[r][start_col] != '.')
                return 0;
    }
    return 1;
}

void place_ship(Board *board, int start_row, int start_col, int length, int orientation, char symbol) {
    if (orientation == BOAT_HORIZONTAL) {
        for (int j = start_col; j < start_col + length; j++)
            board->board_template[start_row][j] = symbol;
    } else {
        for (int i = start_row; i < start_row + length; i++)
            board->board_template[i][start_col] = symbol;
    }
}



int place_ship_randomly(Board *board, int ship_size, char symbol) {
    int attempts = 0;

    while (attempts < 100) {
        int row = rand() % (board->board_lines + 1);
        int col = rand() % (board->board_columns + 1);
        int direction = rand() % 2; // 0 = horizontal, 1 = vertical

        if (can_place_ship(board, row, col, ship_size, direction)) {
            place_ship(board, row, col, ship_size, direction, symbol);
            return 1;
        }
        attempts++;
    }
    return 0;
}



void place_ships_manually(Board *board) {
    int ship_sizes[] = {5, 4, 3, 3, 2};
    char ship_symbols[] = {'P', 'C', 'D', 'D', 'T'};
    char *ship_names[] = {"Porte-avions", "Croiseur", "Destroyer 1", "Destroyer 2", "Torpilleur"};

    for (int i = 0; i < 5; i++) {
        int valid = 0;
        while (!valid) {
            printf("\nPlacez votre %s (%d cases)\n", ship_names[i], ship_sizes[i]);

            char pos[4];
            char orient_char;
            int row, col, orientation;

            printf("Position de départ (ex: B3) : ");
            scanf("%3s", pos);

            col = toupper(pos[0]) - 'A' + 1;
            row = atoi(&pos[1]);

            printf("Orientation (H = horizontal, V = vertical) : ");
            scanf(" %c", &orient_char);
            orient_char = toupper(orient_char);
            orientation = (orient_char == 'H') ? BOAT_HORIZONTAL : BOAT_VERTICAL;

            if (can_place_ship(board, row, col, ship_sizes[i], orientation)) {
                place_ship(board, row, col, ship_sizes[i], orientation, ship_symbols[i]);
                valid = 1;
                print_just_board(board);
            } else {
                printf("Placement invalide (collision ou hors plateau). Réessayez !\n");
            }
        }
    }
}



void init_board(Board *board) {
    printf("Veuillez entrer le nombre de lignes du plateau : ");
    scanf("%d", &(board->board_lines));

    while (board->board_lines > 26 || board->board_lines < 5) {
        if (board->board_lines > 26)
            printf("Erreur : max = 26. Recommencez !\n");
        else
            printf("Erreur : min = 5. Recommencez !\n");

        printf("Veuillez entrer le nombre de lignes du plateau : ");
        scanf("%d", &(board->board_lines));
    }

    board->board_columns = board->board_lines;

    board->board_template = malloc(sizeof(char *) * (board->board_lines + 1));
    for (int i = 0; i < board->board_lines + 1; i++) {
        board->board_template[i] = malloc(sizeof(char) * (board->board_columns + 1));
        for (int j = 0; j < board->board_columns + 1; j++) {
            if (i == 0 && j == 0)
                board->board_template[i][j] = ' ';
            else if (j == 0 && i > 0)
                board->board_template[i][j] = '0' + i;
            else if (i == 0 && j > 0)
                board->board_template[i][j] = 'A' + (j - 1);
            else
                board->board_template[i][j] = '.';
        }
    }
}



int main() {
    srand(time(NULL));

    Board board2;
    init_board(&board2);

    printf("Comment voulez-vous initialiser ? (0 = manuel, 1 = aléatoire) : ");
    int mode;
    scanf("%d", &mode);

    if (mode == 1) {
        place_ship_randomly(&board2, 5, 'P'); // Porte-avions
        place_ship_randomly(&board2, 4, 'C'); // Croiseur
        place_ship_randomly(&board2, 3, 'D'); // Destroyer 1
        place_ship_randomly(&board2, 3, 'D'); // Destroyer 2
        place_ship_randomly(&board2, 2, 'T'); // Torpilleur
        printf("Bateaux placés aléatoirement !\n");
        print_just_board(&board2);
    } else {
        place_ships_manually(&board2);
    }

    return 0;
}
