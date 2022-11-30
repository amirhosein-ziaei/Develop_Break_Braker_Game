#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define PI 3.14159265
#define step 0.0001
int map[200][300];
int Sp = 0; //emtiaz
int size;   //size safhe
int row = -1;
int loader = 0;
int checkFileExists(char *filename)
{
    /* to open file to read */
    FILE *file;
    if (file = fopen(filename, "r"))
    {
        fclose(file);
        return 1;
    }
    return 0;
}

void addToMap(int Ri, int n)
{
    int column;
    while (1 == 1)
    {

        column = rand() % (2 * n);
        if (map[0][column] == 0)
        {
            map[0][column] = Ri;
            break;
        }
    }
}

void show(int level, int Sp, int n, int row)
{

    printf("Level %d:\t\t\t Score: %d\n", level, Sp);
    printf("\tBricks:\n");
    int i, j;
    for (i = 0; i < row + 1; i++)
    {
        printf("\t\tRow %d:\n", 3 * n - i);
        printf("\t\t");
        int j;
		for (j = 0; j < 2 * n; j++)
        {
            printf("%d ", map[i][j]);
        }
        printf("\n");
    }
    printf("---------------------------------------------\n");
}

int shoot(int shootPoint, int phi, int n, int k)
{
    shootPoint--;
    int direction = 0;
    double tangent;
    double y = (3 * n) - 1;
    double x = (double)shootPoint;
    if (phi == 90)
    {
        direction = 0;
        tangent = 2;
    }
    else if (phi > 90)
    {
        direction = -1;
        tangent = tan((PI / 180) * phi);
    }
    else
    {
        direction = 1;
        tangent = tan((PI / 180) * phi);
    }
    while (1 == 1)
    {
        x += step * direction;
        y -= step * fabs(tangent);
        int xTarget = (int)x;
        int yTarget = (int)y;
        if (x - xTarget > 0.49)
        {
            xTarget += 1;
        }
        if (y - yTarget > 0.51)
        {
            yTarget += 1;
        }
        

        if (xTarget < 0 || yTarget < 0 || xTarget >= 2 * n) //check boundaries!
        {
            return 0;
        }

        if (map[yTarget][xTarget] == 0)
        {
            continue;
        }
        else if (map[yTarget][xTarget] == -1)
        {

            map[yTarget][xTarget] = 0;
            int counter = 0;

            if (yTarget - 1 >= 0 && map[yTarget - 1][xTarget] > 0)
            { //bala
                map[yTarget - 1][xTarget] -= k;
                if (map[yTarget - 1][xTarget] <= 0)
                {
                    map[yTarget - 1][xTarget] = 0;
                    counter++;
                }
            }
            if (yTarget - 1 >= 0 && xTarget + 1 < 2 * size && map[yTarget - 1][xTarget + 1] > 0)
            { //bala rast
                map[yTarget - 1][xTarget + 1] -= k;
                if (map[yTarget - 1][xTarget + 1] <= 0)
                {
                    map[yTarget - 1][xTarget + 1] = 0;
                    counter++;
                }
            }
            if (xTarget + 1 < 2 * n && map[yTarget][xTarget + 1] > 0)
            { //rast
                map[yTarget][xTarget + 1] -= k;
                if (map[yTarget][xTarget + 1] <= 0)
                {
                    map[yTarget][xTarget + 1] = 0;
                    counter++;
                }
            }
            if (yTarget + 1 < 3 * n && xTarget + 1 < 2 * n && map[yTarget + 1][xTarget + 1] > 0)
            { //pain rast
                map[yTarget + 1][xTarget + 1] -= k;
                if (map[yTarget + 1][xTarget + 1] <= 0)
                {
                    map[yTarget + 1][xTarget + 1] = 0;
                    counter++;
                }
            }
            if (yTarget + 1 < 3 * n && map[yTarget + 1][xTarget] > 0)
            { //pain
                map[yTarget + 1][xTarget] -= k;
                if (map[yTarget + 1][xTarget] <= 0)
                {
                    map[yTarget + 1][xTarget] = 0;
                    counter++;
                }
            }
            if (yTarget + 1 < 3 * n && xTarget - 1 >= 0 && map[yTarget + 1][xTarget - 1] > 0)
            { //pain chap
                map[yTarget + 1][xTarget - 1] -= k;
                if (map[yTarget + 1][xTarget - 1] <= 0)
                {
                    map[yTarget + 1][xTarget - 1] = 0;
                    counter++;
                }
            }
            if (xTarget - 1 >= 0 && map[yTarget][xTarget - 1] > 0)
            { //chap
                map[yTarget][xTarget - 1] -= k;
                if (map[yTarget][xTarget - 1] <= 0)
                {
                    map[yTarget][xTarget - 1] = 0;
                    counter++;
                }
            }
            if (yTarget - 1 >= 0 && xTarget - 1 >= 0 && map[yTarget - 1][xTarget - 1] > 0)
            { //bala chap
                map[yTarget - 1][xTarget - 1] -= k;
                if (map[yTarget - 1][xTarget - 1] <= 0)
                {
                    map[yTarget - 1][xTarget - 1] = 0;
                    counter++;
                }
            }
            if (counter > 0)
            {
                return counter;
            }
            else
            {
                return -1;
            }
        }
        else
        {

            map[yTarget][xTarget]--;
            if (map[yTarget][xTarget] == 0)
            {
                return 1;
            }
        }
    }
}
void beginGame()
{

    int level = 1;
    int k = 1;         //te'dade tir
    int lastRow = row; //radifi ke ajorha be an ezafe mishavand
    int phi = 0;    //zavieye harekat
    int shootPoint; //sotoone noghteye partab
    while (1 == 1)
    {
        lastRow++;
        if (lastRow == (3 * size) - 1)
        {
            show(level, Sp, size, lastRow - 1);
            printf("----You Lose---\n");
            break;
        }

        int i, j;
        if (loader == 0)
        {
            //jabejaie satrha
            for (i = 0; i < lastRow; i++)
            {
                for (j = 0; j < 2 * size; j++)
                {
                    map[lastRow - i][j] = map[lastRow - i - 1][j];
                }
            }
            for (j = 0; j < 2 * size; j++)
            {
                map[0][j] = 0;
            }

            time_t t;   
            /* Intializes random number generator */
            srand((unsigned) time(&t));

            int Tb = (rand() % ((2 * size) - 1)) + 1; //te'dade ajor haye jadid
            for (i = 0; i < Tb; i++)
            {
                int Ri = (rand() % (Sp + 1)) + 1;
                addToMap(Ri, size);
            }
            double g = (double)(rand() % 100) / 100;
            if (g + ((double)Tb / (2 * size)) > 1)
            {
                addToMap(-1, size);
            }
        }
        else{
            loader = 0;
        }
        show(level, Sp, size, lastRow);
        printf("\tphi: (-1) to save and (-2) to exit\n\tphi: ");
        while (1 == 1)
        {

            scanf("%d", &phi);
            if (phi == -1)
            {
                row = lastRow - 1;
                saveFile();
                printf("\tphi: (-1) to save and (-2) to exit\n\tphi: ");
                continue;
            }
            else if(phi == -2){
                printf("******************* Thank You For Playing *******************\n");
                exit(0);
                
            }
            else if (phi >= 0 && phi <= 180)
                break;
            else
            {
                printf("\tEnter valid phi: ");
            }
        }

        printf("\tEnter Shoot Point: (-1) to save and (-2) to exit\n\tShoot Point: ");
        while (1 == 1)
        {
            scanf("%d", &shootPoint);
            if (shootPoint == -1)
            {
                row = lastRow - 1;
                saveFile();
                printf("\tphi = %d\n\n",phi);
                printf("\tEnter Shoot Point: (-1) to save and (-2) to exit\n\tShoot Point: ");
                continue;
            }
            else if(shootPoint == -2){
                printf("******************* Thank You For Playing *******************\n");
                exit(0);
                
            }
            else if (shootPoint >= 1 && shootPoint <= 2 * size)
                break;
            else
            {
                printf("\tEnter valid shoot point: ");
            }
        }
        int counter = 0;
        int shot = 0;
        for (i = 0; i < Sp + 1; i++)
        {
            shot = shoot(shootPoint, phi, size, Sp + 1 - i);
            if (shot < 0)
                break;
            counter += shot;
            if (shot > 1) //bomb!
                break;
        }
        Sp += counter;
        level++;

        while (lastRow != 0)
        {
            int count = 0;
            for (j = 0; j < 2 * size; j++)
            {
                if (map[lastRow][j] != 0)
                {
                    break;
                }
                count++;
            }
            if (count == 2 * size)
                lastRow--;
            else
                break;
        }
    }
}

void loadGame(char *name)
{
    FILE *file;
    file = fopen(name, "r");

    fscanf(file, "%d", &Sp);
    fscanf(file, "%d", &size);
    fscanf(file, "%d", &row);
    loader = 1;
    int i, j;
    for (i = 0; i < 200; i++)
    {
        for (j = 0; j < 300; j++)
        {
            fscanf(file, "%d", &map[i][j]); //read map in file
        }
    }
    return;
}

void makeMap()
{
    int i, j;
    for (i = 0; i < 200; i++)
    {
        for (j = 0; j < 300; j++)
        {
            map[i][j] = 0;
        }
    }
}

int addToFile(char name[])
{
    FILE *file;
    file = fopen(name, "w");
    fprintf(file, "%d\n", Sp);   //save sp in file
    fprintf(file, "%d\n", size); //save sp in file
    fprintf(file, "%d\n", row);  //save last row in file
    int i, j;
    for (i = 0; i < 200; i++)
    {
        for (j = 0; j < 300; j++)
        {
            fprintf(file, "%d \n", map[i][j]); //save map in file
        }
    }
    // fputs(,file);
    // add to file
    fclose(file);
    printf("********** Saved The Name is %s !! **********\n", name);
    return 1;
}

void saveFile()
{
    char name[50];
    FILE *file;
    int counter = 1;

    printf("Please Enter File Name To Save Or Enter \"Auto\" For Auto Save:\n");
    scanf("%s", name);
    if (strcmp(name, "Auto") == 0)
    {
        while (1 == 1)
        {
            name[0] = 's';
            name[1] = 'h';
            name[2] = 'a';
            name[3] = 't';
            name[4] = 'n';
            name[5] = 'a';
            name[6] = 'r';
            name[7] = 'd';
            char temp[10];
            itoa(counter, temp, 10);
            name[8] = temp[0];
            name[9] = temp[1];

            if (checkFileExists(name) == 1)
            {
                counter++;
            }
            else
            {
                addToFile(name);
                loadGame(name);
                return;
            }
        }
    }
    else
    {
        addToFile(name);
        loadGame(name);
        return;
    }
    return;
}

void start()
{
    int order;
    char fileName[20];
    FILE *file;

    printf("\n\n\n******************* WelCome To Game *******************\n\n\n");
    printf("What Do You Want To Do?\n\n");
    printf("\t1-Start New Game\n");
    printf("\t2-Load Game\n");
    printf("\t3-Exit Game\n");
    scanf("%d", &order);
    while (1 == 1)
    {
        if (order == 1)
        {
            printf("Enter size: ");
            scanf("%d", &size);
            Sp = 0;
            beginGame();
            return;
        }
        else if (order == 2)
        {
            while (1 == 1)
            {
                printf("Enter File Name: \n");
                scanf("%s", &fileName);
                int check = checkFileExists(fileName);
                if (check != 1)
                {
                    printf("There Is Not File With This Name\n");
                    continue;
                }
                loadGame(fileName);
                beginGame();
                return;
            }
        }
        else if (order == 3)
        {
            printf("******************* Thank You For Playing *******************\n");
            exit(0);
        }
        else
        {
            printf("Please Enter Valid Number\n");
        }
    }
}

void main(int argc, char **argv)
{
    while (1 == 1)
    {
        makeMap();
        start();
    }
}
