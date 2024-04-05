#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include "conio.h"
typedef enum {FRONT=1, BACK, UP, DOWN, RIGHT, LEFT}T_SIDE;
typedef enum {W=1, Y, B, G, R, O, LG}T_COLOR;

typedef struct
{
    int type_face;
    int** face;
}FACE;

void select_color_conio(FACE** rubiks,int i,int j, int k);
int side_to_index(FACE** rubiks, T_SIDE side_name);
FACE* create_rubiks(void);
void free_rubiks(FACE** rubikscube);
void init_rubiks(FACE** rubikscube);
void blank_rubiks(FACE ** rubikscube);
void display_rubiks(FACE** rubikscube);
int fill_rubiks(FACE ** rubikscube);
int choose_color(FACE ** rubikscube);
int scramble_rubiks(FACE** rubikscube);
void vertical_rotation(FACE** rubikscube);
void horizontal_rotation(FACE**rubikscube);
int choose_face(void);
int check_rubiks_colors(FACE** rubikscube);
int adjacent_rubiks_check(FACE** rubikscube,int i, int j, int k);
int main(void)
{
    int i;



        printf("CHOISIR LES FONCTIONS INDIQUEES CI-DESSOUS");
        printf("1:INITIALISER un RUBIKS CUBE");
        printf("2: GRISER un RUBIKS CUB ");
        printf("3:MELANGER ALEATOIREMENT UN RUBIX CUBE");
        printf("4:ATTRIBUTION MANUELLE DE COULEUR AUX CASES ");
        printf("5:TOURNER RUBIX CUBE");
        printf("JOUER AU RUBIX CUBE");
        FACE* rubikscube;
    rubikscube = create_rubiks();
        init_rubiks(&rubikscube);
        display_rubiks(&rubikscube);
        vertical_rotation(&rubikscube);
        display_rubiks(&rubikscube);


        fill_rubiks(&rubikscube);
        free_rubiks(&rubikscube);




}
void select_color_conio(FACE** rubikscube,int i,int j, int k)

{
    if ((*rubikscube + i)->face[j][k]==0){
        c_textcolor(LIGHTGRAY);
    }
    if ((*rubikscube + i)->face[j][k]==1){
        c_textcolor(WHITE);
    }
    if ((*rubikscube + i)->face[j][k]==2){
        c_textcolor(YELLOW);
    }
    if ((*rubikscube + i)->face[j][k]==3){
        c_textcolor(BLUE);
    }
    if ((*rubikscube + i)->face[j][k]==4){
        c_textcolor(GREEN);
    }
    if ((*rubikscube + i)->face[j][k]==5){
        c_textcolor(RED);
    }
    if ((*rubikscube + i)->face[j][k]==6){
        c_textcolor(LIGHTRED);
    }
}


int side_to_index(FACE** rubikscube, T_SIDE side_name)
{
    int i;

    for (i=0; i<6; i++)
    {
        if ((*rubikscube+i)->type_face == side_name)
        {
            return i;
        }
    }
    return -1;
}


FACE* create_rubiks(void)
{
    int i, j;

    FACE* rubikscube;

    rubikscube = (FACE*)malloc(6*sizeof(FACE));

    for(i=0; i<6; i++)
    {
        (rubikscube+i)->type_face = i+1;
        (rubikscube+i)->face = (int**)malloc(3*sizeof(int*));

        for(j=0; j<3; j++)
        {
            (rubikscube+i)->face[j] = (int*)malloc(3*sizeof(int));
        }
    }
    return rubikscube;
}

void free_rubiks(FACE** rubikscube)
{
    int i, j;

    for (i=0; i<6; i++)
    {
        for (j=0; j<3; j++)
        {
            free((*rubikscube+i)->face[j]);
        }
        free(*rubikscube+i);
    }
    free(*rubikscube);

}

void init_rubiks(FACE** rubikscube)
{
    int i, j, k;

    for (i=0; i<6; i++)
    {
        (*rubikscube+i)->type_face = i+1;

        for (j=0; j<3; j++)
        {
            for (k=0; k<3; k++)
            {
                (*rubikscube+i)->face[j][k] = i+1;
            }
        }
    }
}


void blank_rubiks(FACE ** rubikscube)
{
    int i, j, k;

    for (i=0; i<6; i++)
    {
        for (j=0; j<3; j++)
        {
            for (k=0; k<3; k++)
            {
                if (j == 1 && k == 1)
                {
                    (*rubikscube+i)->face[j][k] = i+1;
                }
                else
                {
                    (*rubikscube+i)->face[j][k] = 0;
                }
            }
        }
    }

}

void display_rubiks(FACE** rubikscube)
{
    int i, j;

    for (i=0; i<3; i++)
    {
        printf("     ");
        for (j=0; j<3; j++)
        {
            select_color_conio(rubikscube,UP-1,i,j);
            printf("%d", (*rubikscube+UP-1)->face[i][j]);
        }
        printf("\n");
    }

    for (i=0; i<3; i++)
    {
        printf(" ");
        for (j=0; j<3; j++)
        {
            select_color_conio(rubikscube,LEFT-1,i,j);
            printf("%d", (*rubikscube+LEFT-1)->face[i][j]);
        }
        printf(" ");
        for (j=0; j<3; j++)
        {
            select_color_conio(rubikscube,FRONT-1,i,j);
            printf("%d", (*rubikscube+FRONT-1)->face[i][j]);
        }
        printf(" ");
        for (j=0; j<3; j++)
        {
            select_color_conio(rubikscube,RIGHT-1,i,j);
            printf("%d", (*rubikscube+RIGHT-1)->face[i][j]);
        }
        printf(" ");
        for (j=0; j<3; j++)
        {
            select_color_conio(rubikscube,BACK-1,i,j);
            printf("%d", (*rubikscube+BACK-1)->face[i][j]);
        }
        printf("\n");
    }

    for (i=0; i<3; i++)
    {
        printf("     ");
        for (j=0; j<3; j++)
        {
                select_color_conio(rubikscube,DOWN-1,i,j);
                printf("%d", (*rubikscube+DOWN-1)->face[i][j]);
        }
        printf("\n");
    }
}

//remplit le rubiks
//Paramètres le rubiks
int fill_rubiks(FACE** rubikscube)
{
    blank_rubiks(rubikscube);
    int o,i,j,k,verif1,verif2,a,b;
    for (o=0;o<3*3*3;o++)
    {


        printf("Choisir la face");
        i=choose_face();
        printf("Choisir la ligne et colonne");
        do {

            verif1 = scanf("%d", &j);
            verif2 = scanf("%d",&k);
            fflush(stdin);
        }while (j,k < -1 || j,k > 3 || verif1,verif2 == 0);


        (*rubikscube+i-1)->face[j][k] = choose_color(rubikscube);
        if ((check_rubiks_colors(rubikscube)==0))
        {
            do {
                printf("Couleur impossible veuillez ressaisir un nouveau \n");
                (*rubikscube+i-1)->face[j][k] = choose_color(rubikscube);
                a =(check_rubiks_colors(rubikscube));


            }while (a==0);
        }
    }
}

//choisit la face
int choose_face(void)
{
    int face, verif;
    printf("1: FRONT \n 2: BACK \n 3: UP \n 4: DOWN \n 5: RIGHT \n 6: LEFT");
    do {

        verif = scanf("%d", &face);
        fflush(stdin);
    }while (face > 6 || face < 1 || verif == 0);



    if (face == 1){
        return FRONT;
    }
    else if (face ==2)
    {
        return BACK;
    }
    else if (face == 3)
    {
        return UP;
    }
    else if (face == 4){
        return DOWN;
    }
    else if (face == 5)
    {
        return RIGHT;
    }
    else if (face == 6)
        return LEFT;



}
//choisit la couleur
int choose_color(FACE ** rubikscube)
{
    int color, verif;
    display_rubiks(rubikscube);

    printf("\n");
    printf("1: Blanc");
    printf("   ");
    printf("2: Jaune");
    printf("   ");
    printf("3: Bleu");
    printf("   ");
    printf("4: Vert");
    printf("   ");
    printf("5: Rouge");
    printf("   ");
    printf("6: Orange");
    printf("   ");
    printf("\n\n");

    do
    {
        verif = scanf("%d", &color);
        fflush(stdin);
    }while (color > 6 || color < 1 || verif == 0);

    return color;
}
//Fonction qui limite les couleurs
//Parametres : Rubiks
//Sortie :  0 ou 1
int check_rubiks_colors(FACE** rubikscube)
{
    int color_count[] = {0, 0, 0, 0, 0, 0};
    int i, j, k;

    for (i=0; i<6; i++)
    {
        for (j=0; j<3; j++)
        {
            for (k=0; k<3; k++)
            {
                color_count[((*rubikscube+i)->face[j][k])-1]++;
            }
        }
    }

    for (i=0; i<6; i++)
    {
        if (color_count[i]>9)
        {
            return 0;
        }
    }
    return 1;
}
//mélange le rubikscube
int scramble_rubiks(FACE** rubikscube)
{
    int n = rand()%9; // nombre entre 0 et 9
    int j = rand()%7+1; // nombre entre 1 et 6
    if (n==0){
        FRONT_clockwise(rubikscube)
    }
    if (n==1) {
        horizontal_rotation(rubikscube);
    }
    if (n==2)
    {
        vertical_rotation(rubikscube);
    }
}





//retourne horizontalement
//Paramètres le rubiks
void horizontal_rotation(FACE**rubikscube) {
    int i, j, k, valeur[3][3];

    for (i = 0; i < 5; i++) {
        for (j = 0; j < 3; j++) {
            for (k = 0; k < 3; k++) {
                valeur[j][k]=(*rubikscube+i)->face[j][k];
                (*rubikscube + i)->face[j][k] = (*rubikscube + i + 1)->face[j][k];
                (*rubikscube+i+1)->face[j][k] = valeur[j][k];
            }
        }
    }


}
//Paramètres le rubiks
void vertical_rotation(FACE** rubikscube)
{
    int i, j, k, valeur[3][3];

    for (i = 1; i < 6; i++) {
        for (j = 0; j < 3; j++) {
            for (k = 0; k < 3; k++) {
                valeur[j][k]=(*rubikscube+i)->face[j][k];
                (*rubikscube + i)->face[j][k] = (*rubikscube + i - 1)->face[j][k];
                (*rubikscube+i-1)->face[j][k] = valeur[j][k];
            }
        }
    }


}

//Paramètres le rubiks int type
void RIGHT_clockwise(FACE **rubikscube, int type) {

    int j, i;
    int tmp1[3];

    for (i = 0; i < type; i++) {
        for (j = 0; j < 3; j++) {
            tmp1[j] = (*rubikscube + FRONT - 1)->face[j][2];
        }
        for (j = 0; j < 3; j++) {
            (*rubikscube + FRONT - 1)->face[j][2] = (*rubikscube + UP - 1)->face[j][2];
        }
        for (j = 0; j < 3; j++) {
            (*rubikscube + UP - 1)->face[j][2] = (*rubikscube + BACK - 1)->face[j][2];
        }
        for (j = 0; j < 3; j++) {
            (*rubikscube + BACK - 1)->face[j][2] = (*rubikscube + DOWN - 1)->face[2 - j][0];
        }
        for (j = 0; j < 3; j++) {
            (*rubikscube + BACK - 1)->face[j][0] = tmp1[2 - j];
        }
    }
}
//Paramètres le rubiks int type
void FRONT_clockwise(FACE **rubikscube, int type) {
    int j, i;
    int tmp1[3];

    for (i = 0; i < type; i++) {
        for (j = 0; j < 3; j++) {
            tmp1[j] = (*rubikscube + LEFT - 1)->face[j][2];
        }
        for (j = 0; j < 3; j++) {
            (*rubikscube + LEFT - 1)->face[j][2] = (*rubikscube + DOWN - 1)->face[j][2];
        }
        for (j = 0; j < 3; j++) {
            (*rubikscube + DOWN - 1)->face[j][2] = (*rubikscube + RIGHT - 1)->face[j][2];
        }
        for (j = 0; j < 3; j++) {
            (*rubikscube + RIGHT - 1)->face[j][2] = (*rubikscube + UP - 1)->face[2 - j][0];
        }
        for (j = 0; j < 3; j++) {
            (*rubikscube + UP - 1)->face[j][0] = tmp1[2 - j];
        }
    }
}
//Paramètres le rubiks int type
void UP_clockwise(FACE **rubikscube, int type) {
    int j, i;
    int tmp1[3];

    for (i = 0; i < type; i++) {
        for (j = 0; j < 3; j++) {
            tmp1[j] = (*rubikscube + LEFT - 1)->face[j][2];
        }
        for (j = 0; j < 3; j++) {
            (*rubikscube + LEFT - 1)->face[j][2] = (*rubikscube + FRONT - 1)->face[j][2];
        }
        for (j = 0; j < 3; j++) {
            (*rubikscube + FRONT - 1)->face[j][2] = (*rubikscube + RIGHT - 1)->face[j][2];
        }
        for (j = 0; j < 3; j++) {
            (*rubikscube + RIGHT - 1)->face[j][2] = (*rubikscube + BACK - 1)->face[2 - j][0];
        }
        for (j = 0; j < 3; j++) {
            (*rubikscube + BACK - 1)->face[j][0] = tmp1[2 - j];
        }
    }
}
//Paramètres le rubiks int type
void DOWN_clockwise(FACE **rubikscube, int type) {
    int j, i;
    int tmp1[3];

    for (i = 0; i < type; i++) {
        for (j = 0; j < 3; j++) {
            tmp1[j] = (*rubikscube + LEFT - 1)->face[j][2];
        }
        for (j = 0; j < 3; j++) {
            (*rubikscube + LEFT - 1)->face[j][2] = (*rubikscube + FRONT - 1)->face[j][2];
        }
        for (j = 0; j < 3; j++) {
            (*rubikscube + FRONT - 1)->face[j][2] = (*rubikscube + RIGHT - 1)->face[j][2];
        }
        for (j = 0; j < 3; j++) {
            (*rubikscube + RIGHT - 1)->face[j][2] = (*rubikscube + BACK - 1)->face[2 - j][0];
        }
        for (j = 0; j < 3; j++) {
            (*rubikscube + BACK - 1)->face[j][0] = tmp1[2 - j];
        }
    }
}
//Paramètres le rubiks int type
void BACK_clockwise(FACE **rubikscube, int type) {
    int j, i, tmp1[3];
    for (i = 0; i < type; i++) {
        for (j = 0; j < 3; j++) {
            tmp1[j] = (*rubikscube + LEFT - 1)->face[j][2];
        }
        for (j = 0; j < 3; j++) {
            (*rubikscube + LEFT - 1)->face[j][2] = (*rubikscube + DOWN - 1)->face[j][2];
        }
        for (j = 0; j < 3; j++) {
            (*rubikscube + DOWN - 1)->face[j][2] = (*rubikscube + RIGHT - 1)->face[j][2];
        }
        for (j = 0; j < 3; j++) {
            (*rubikscube + RIGHT - 1)->face[j][2] = (*rubikscube + UP - 1)->face[2 - j][0];
        }
        for (j = 0; j < 3; j++) {
            (*rubikscube + UP - 1)->face[j][0] = tmp1[2 - j];
        }
    }
}
//Paramètres le rubiks int type
void LEFT_clockwise(FACE **rubikscube, int type) {
    int j, i;
    int tmp1[3];

    for (i = 0; i < type; i++) {
        for (j = 0; j < 3; j++) {
            tmp1[j] = (*rubikscube + FRONT - 1)->face[j][2];
        }
        for (j = 0; j < 3; j++) {
            (*rubikscube + FRONT - 1)->face[j][2] = (*rubikscube + UP - 1)->face[j][2];
        }
        for (j = 0; j < 3; j++) {
            (*rubikscube + UP - 1)->face[j][2] = (*rubikscube + BACK - 1)->face[j][2];
        }
        for (j = 0; j < 3; j++) {
            (*rubikscube + BACK - 1)->face[j][2] = (*rubikscube + DOWN - 1)->face[2 - j][0];
        }
        for (j = 0; j < 3; j++) {
            (*rubikscube + DOWN - 1)->face[j][0] = tmp1[2 - j];
        }
    }
}
//Paramètres le rubiks int type
void FRONT_anticlockwise(FACE **rubikscube, int type)
//Paramètres le rubiks int type
{
    FRONT_clockwise(rubikscube,3-type);
}
//Paramètres le rubiks int type
void UP_anticlockwise(FACE **rubikscube, int type) {
    UP_clockwise(rubikscube,3-type);
}
//Paramètres le rubiks int type
void DOWN_anticlockwise(FACE **rubikscube, int type) {
    DOWN_clockwise(rubikscube,3-type);
}
void BACK_anticlockwise(FACE **rubikscube, int type) {
    BACK_clockwise(rubikscube,3-type);
}
//Paramètres le rubiks int type
void RIGHT_anticlockwise(FACE **rubikscube, int type) {
    RIGHT_clockwise(rubikscube,3-type);
}
//Paramètres le rubiks int type
void LEFT_anticlockwise(FACE **rubikscube, int type) {
    LEFT_clockwise(rubikscube,3-type);
}
//Paramètres le rubiks int type
void move_rubiks(FACE **rubikscube) {
    int x, turn;
    printf("Mouvement horaire");
    printf("1: Front 2:Up 3:Down 4:Back 5:Left 6:Right");
    printf("anti horaire");
    printf("7:Front 8:Up 9:Down 10:Back 11:Left 12:Right");
    printf("Quelle mouvement voulez vous faire");
    printf("13: Vertical ou 14: Horizontal");
    scanf("%d", &x);
    printf("demitour ou un quart de tour");
    scanf("%d", &turn);
    if (turn <= 0 || turn >= 3) {
        printf("Pas possible!");
    }
    switch (x) {
        case 1:
            FRONT_clockwise(rubikscube, turn);
            return;
        case 2:
            UP_clockwise(rubikscube, turn);
            return;
        case 3:
            DOWN_clockwise(rubikscube, turn);
            return;
        case 4:
            BACK_clockwise(rubikscube, turn);
            return;
        case 5:
            LEFT_clockwise(rubikscube, turn);
            return;
        case 6:
            RIGHT_clockwise(rubikscube, turn);
            return;
        case 7:
            FRONT_anticlockwise(rubikscube, turn);
            return;
        case 8:
            FRONT_anticlockwise(rubikscube, turn);
            return;
        case 9:
            FRONT_anticlockwise(rubikscube, turn);
            return;
        case 10:
            FRONT_anticlockwise(rubikscube, turn);
            return;
        case 11:
            FRONT_anticlockwise(rubikscube, turn);
            return;
        case 12:
            FRONT_anticlockwise(rubikscube, turn);
            return;
        case 13:
            horizontal_rotation(rubikscube);
            return;
        case 14:
            vertical_rotation(rubikscube);
            return;
    }

//Paramètres le rubiks int type
    void Menu() {
        FACE *rubikscube = create_rubiks();
        init_rubiks(&rubikscube);
        display_rubiks(&rubikscube);
        int try = 0;
        while (try != 7) {
            printf(" 1:Scramble    2:RESET    3:BLANK    4:MOVE     5:FILL   6:SOLVE   7:QUIT");
            scanf("%d", &try);

            switch (try) {
                case 1:
                    scramble_rubiks(&rubikscube);
                    display_rubiks(&rubikscube);
                    break;
                case 2:
                    init_rubiks(&rubikscube);
                    display_rubiks(&rubikscube);
                    break;
                case 3:
                    blank_rubiks(&rubikscube);
                    display_rubiks(&rubikscube);
                    break;
                case 4:
                    move_rubiks(&rubikscube);
                    display_rubiks(&rubikscube);
                    break;
                case 5:
                    fill_rubiks(&rubikscube);
                    display_rubiks(&rubikscube);
                    break;
                case 6:
                    // résolution(&rubikscube);
                    display_rubiks(&rubikscube);
                    break;
                case 7:
                    break;
                default :
                    printf("Aucune action n'est défini!\n");
            }
        }
    }
}