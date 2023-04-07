#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int shotNumber=0;
int firstX=0;
int lastX=0;
int firstY=0;
int lastY=0;
int pCounter=0;
int kCounter=0;

void displayOne(int board[10][10])
{
    printf("  ");
    for(int i=0;i<10;i++)
        printf(" %d", i+1);
    printf("\n");
    for(int i=0;i<10;i++)
    {
        printf("%*d ", 2, i+1);
        for(int j=0;j<10;j++)
        {
            if(board[i][j] == -1)//pudlo
                printf("\033[0;31m- ");
            else if(board[i][j] == 1)//statek
                printf("\033[0;32m# ");
            else if(board[i][j] == -2)//otoczenie wokó³ statku, w którym nie mo¿na stawiaæ innych statków
                printf("\033[0;31m- ");
            else if(board[i][j] == 0)//woda
                printf("\033[0;34m. ");
            else if(board[i][j] == 2)//trafiony
                printf("\033[0;33m+ ");
            else if(board[i][j] == 3)//zatopiony
                printf("\033[0;37mX ");
        }
        printf("\033[0m");
        printf("\n");
    }
}
void displaystart(int board[10][10])
{
    printf("  ");
    for(int i=0;i<10;i++)
        printf(" %d", i+1);
    printf("\n");
    for(int i=0;i<10;i++)
    {
        printf("%*d ", 2, i+1);
        for(int j=0;j<10;j++)
        {
            if(board[i][j] == 0)//woda
                printf(". ");

        }
        printf("\n");
    }
}

void displayTwo(int board1[10][10], int board2[10][10])
{
    printf("  ");
    for(int i=0;i<10;i++)
        printf(" %d", i+1);
    printf("      ");
    printf("  ");
    for(int i=0;i<10;i++)
        printf(" %d", i+1);
    printf("\n");

    for(int i=0;i<10;i++)
    {
        printf("%*d ", 2, i+1);
        for(int j=0;j<10;j++)
        {
            if(board1[i][j] == -1)
                printf("\033[0;31m- ");
            else if(board1[i][j] == 1)
                printf("\033[0;32m# ");
            else if(board1[i][j] == -2)
                printf("\033[0;31m- ");
            else if(board1[i][j] == 0)
                printf("\033[0;34m. ");
            else if(board1[i][j] == 2)
                printf("\033[0;33m+ ");
            else if(board1[i][j] == 3)
                printf("\033[0;37mX ");
        }
        printf("\033[0m");
        printf("      ");
        printf("%*d ", 2, i+1);
        for(int j=0;j<10;j++)
        {
            if(board2[i][j] == -1)
                printf("\033[0;31m- ");
            else if(board2[i][j] == 1)
                printf("\033[0;32m# ");
            else if(board2[i][j] == 0)
                printf("\033[0;34m. ");
            else if(board2[i][j] == -2)
                printf("\033[0;31m- ");
            else if(board2[i][j] == 2)
                printf("\033[0;33m+ ");
            else if(board2[i][j] == 3)
                printf("\033[0;37mX ");
        }
        printf("\033[0m");

        printf("\n");
    }
}

void clearTwoLines()
{
    printf("\33[2K\r");
    printf("\33[2K\r");
}

void placeShip(int board[10][10], int n, int orientation, int x, int y, int number)
{
    for(int i=0;i<n;i++)
    {
        if(orientation == 1)
        {
            if(i==0)
            {
                if(x>1)
                {
                    if(y>1)
                        board[y-2][x-2] = -2;
                    board[y-1][x-2] = -2;
                    if(y<10)
                        board[y][x-2] = -2;
                }
            }
            if(y>1)
                board[y-2][x+i-1] = -2;
            if(y<10)
                board[y][x+i-1] = -2;
            board[y-1][x-1+i] = number;
            if(i==n-1&&x+i!=10)
            {
                if(x<10)
                {
                    if(y>1)
                        board[y-2][x+i] = -2;
                    board[y-1][x+i] = -2;
                    if(y<10)
                        board[y][x+i] = -2;
                }
            }
        }
        else
        {
            if(i==0)
            {
                if(y>1)
                {
                    if(x>1)
                        board[y-2][x-2] = -2;
                    board[y-2][x-1] = -2;
                    if(x<10)
                        board[y-2][x] = -2;
                }
            }
            if(x>1)
                board[y+i-1][x-2] = -2;
            if(x<10)
                board[y+i-1][x] = -2;
            board[y-1+i][x-1] = number;
            if(i==n-1&&y+i!=10)
            {
                if(y<10)
                {
                    if(x>1)
                        board[y+i][x-2] = -2;
                    board[y+i][x-1] = -2;
                    if(x<10)
                        board[y+i][x] = -2;
                }
            }
        }
    }
}

void trojmasztowiec(int board[10][10])
{
    printf("\nTrojmasztowiec:\n");
    printf("Wybierz ustawnienie statku (pionowo-0, poziomo-1):\n");
    int orientation = 0;
    scanf("%d", &orientation);
    while(orientation != 0 && orientation != 1)
    {
        clearTwoLines();
        printf("Bledne dane (pionowo-0, poziomo-1):\n");
        scanf("%d", &orientation);
    }
    printf("Podaj koordynaty statku:\n");
    int x=0,y=0;
    scanf("%d %d", &x, &y);
    if(orientation == 1)
    {
        int collision = 0;
        for(int i=0;i<3;i++)
        {
            if(board[y-1][x-1+i] == -2 || board [y-1][x-1+i] == 1)
            {
                collision = 1;
                break;
            }
        }
        while(y<=0 || y>10 || x<=0 || x>8 || collision==1)
        {
            clearTwoLines();
            printf("Bledne dane, podaj jeszcze raz:\n");
            scanf("%d %d", &x, &y);
            collision = 0;
            for(int i=0;i<3;i++)
            {
                if(board[y-1][x-1+i] == -2 || board [y-1][x-1+i] == 1)
                {
                    collision = 1;
                    break;
                }
            }
        }
    }
    else
    {
        int collision = 0;
        for(int i=0;i<3;i++)
        {
            if(board[y-1+i][x-1] == -2 || board [y-1+i][x-1] == 1)
            {
                collision = 1;
                break;
            }
        }
        while(x<=0 || x>10 || y<=0 || y>8 || collision==1)
        {
            clearTwoLines();
            printf("Bledne dane, podaj jeszcze raz:\n");
            scanf("%d %d", &x, &y);
            collision = 0;
            for(int i=0;i<3;i++)
            {
                if(board[y-1+i][x-1] == -2 || board [y-1+i][x-1] == 1)
                {
                    collision = 1;
                    break;
                }
            }
        }
    }

    placeShip(board, 3, orientation, x, y, 1);
    system("cls");
    displayOne(board);
}

void dwumasztowiec(int board[10][10])
{
    printf("\nDwumasztowiec:\n");
    printf("Wybierz ustawnienie statku (pionowo-0, poziomo-1):\n");
    int orientation = 0;
    scanf("%d", &orientation);
    while(orientation != 0 && orientation != 1)
    {
        clearTwoLines();
        printf("Bledne dane (pionowo-0, poziomo-1):\n");
        scanf("%d", &orientation);
    }
    printf("Podaj koordynaty statku:\n");
    int x=0,y=0;
    scanf("%d %d", &x, &y);
    if(orientation == 1)
    {
        int collision = 0;
        for(int i=0;i<2;i++)
        {
            if(board[y-1][x-1+i] == -2 || board [y-1][x-1+i] == 1)
            {
                collision = 1;
                break;
            }
        }
        while(y<=0 || y>10 || x<=0 || x>9 || collision==1)
        {
            clearTwoLines();
            printf("Bledne dane, podaj jeszcze raz:\n");
            scanf("%d %d", &x, &y);
            collision = 0;
            for(int i=0;i<2;i++)
            {
                if(board[y-1][x-1+i] == -2 || board [y-1][x-1+i] == 1)
                {
                    collision = 1;
                    break;
                }
            }
        }
    }
    else
    {
        int collision = 0;
        for(int i=0;i<2;i++)
        {
            if(board[y-1+i][x-1] == -2 || board [y-1+i][x-1] == 1)
            {
                collision = 1;
                break;
            }
        }
        while(x<=0 || x>10 || y<=0 || y>9 || collision==1)
        {
            clearTwoLines();
            printf("Bledne dane, podaj jeszcze raz:\n");
            scanf("%d %d", &x, &y);
            collision = 0;
            for(int i=0;i<2;i++)
            {
                if(board[y-1+i][x-1] == -2 || board [y-1+i][x-1] == 1)
                {
                    collision = 1;
                    break;
                }
            }
        }
    }

    placeShip(board, 2, orientation, x, y, 1);
    system("cls");
    displayOne(board);
}

void jednomasztowiec(int board[10][10])
{
    printf("\nJednomasztowiec:\n");
    printf("Podaj koordynaty statku:\n");
    int x=0,y=0;
    scanf("%d %d", &x, &y);
    while(y<=0 || y>10 || x<=0 || x>10 || board[y-1][x-1] == 1 || board[y-1][x-1] == -2)
    {
        clearTwoLines();
        printf("Bledne dane, podaj jeszcze raz:\n");
        scanf("%d %d", &x, &y);
    }

    placeShip(board, 1, 0, x, y, 1);
    system("cls");
    displayOne(board);
}
void userPlaceShips(int board[10][10])
{
    displaystart(board);
    printf("\nUstaw swoja flote\n");
    printf("Czteromasztowiec:\n");
    printf("Wybierz ustawnienie statku (pionowo-0, poziomo-1):\n");
    int orientation = 0;
    scanf("%d", &orientation);
    while(orientation != 0 && orientation != 1)
    {
        clearTwoLines();
        printf("Bledne dane (pionowo-0, poziomo-1):\n");
        scanf("%d", &orientation);
    }
    int x=0,y=0;
    printf("Podaj koordynaty statku:\n");
    scanf("%d %d", &x, &y);
    if(orientation == 1)
    {
        while(y<=0 || y>10 || x<=0 || x>7)
        {
            clearTwoLines();
            printf("Bledne dane, podaj jeszcze raz:\n");
            scanf("%d %d", &x, &y);
        }
    }
    else
    {
        while(x<=0 || x>10 || y<=0 || y>7)
        {
            clearTwoLines();
            printf("Bledne dane, podaj jeszcze raz:\n");
            scanf("%d %d", &x, &y);
        }
    }

    placeShip(board, 4, orientation, x, y, 1);
    system("cls");
    displayOne(board);

    trojmasztowiec(board);
    trojmasztowiec(board);

    dwumasztowiec(board);
    dwumasztowiec(board);
    dwumasztowiec(board);

    jednomasztowiec(board);
    jednomasztowiec(board);
    jednomasztowiec(board);
    jednomasztowiec(board);
}

void AItrojmasztowiec(int board[10][10])
{
    int orientation = rand () % 2;

    if(orientation == 1)
    {
        int collision = 0;
        int x = 1+rand() % 8, y = 1+rand() % 10;

        for(int i=0;i<3;i++)
        {
            if(board[y-1][x-1+i] == -2 || board [y-1][x-1+i] == 1)
            {
                collision = 1;
                break;
            }
        }
        while(collision==1)
        {
            x = 1+rand() % 8;
            y = 1+rand() % 10;
            collision = 0;
            for(int i=0;i<3;i++)
            {
                if(board[y-1][x-1+i] == -2 || board [y-1][x-1+i] == 1)
                {
                    collision = 1;
                    break;
                }
            }
        }
        placeShip(board, 3, orientation, x, y, 1);
    }
    else
    {
        int  x = 1+rand() % 10, y = 1+rand() % 8;
        int collision = 0;

        for(int i=0;i<3;i++)
        {
            if(board[y-1+i][x-1] == -2 || board [y-1+i][x-1] == 1)
            {
                collision = 1;
                break;
            }
        }
        while(collision==1)
        {
            x = 1+rand() % 10;
            y = 1+rand() % 8;
            collision = 0;
            for(int i=0;i<3;i++)
            {
                if(board[y-1+i][x-1] == -2 || board [y-1+i][x-1] == 1)
                {
                    collision = 1;
                    break;
                }
            }
        }
        placeShip(board, 3, orientation, x, y, 1);
    }
}

void AIdwumasztowiec(int board[10][10])
{
    int orientation = rand () % 2;

    if(orientation == 1)
    {
        int x = 1+rand() % 9, y = 1+rand() % 10;
        int collision = 0;
        for(int i=0;i<2;i++)
        {
            if(board[y-1][x-1+i] == -2 || board [y-1][x-1+i] == 1)
            {
                collision = 1;
                break;
            }
        }
        while(collision==1)
        {
            x = 1+rand() % 9;
            y = 1+rand() % 10;
            collision = 0;
            for(int i=0;i<2;i++)
            {
                if(board[y-1][x-1+i] == -2 || board [y-1][x-1+i] == 1)
                {
                    collision = 1;
                    break;
                }
            }
        }
        placeShip(board, 2, orientation, x, y, 1);
    }
    else
    {
        int x = 1+rand() % 10, y = 1+rand() % 9;
        int collision = 0;
        for(int i=0;i<2;i++)
        {
            if(board[y-1+i][x-1] == -2 || board [y-1+i][x-1] == 1)
            {
                collision = 1;
                break;
            }
        }
        while(collision==1)
        {
            x = 1+rand() % 10;
            y = 1+rand() % 9;
            collision = 0;
            for(int i=0;i<2;i++)
            {
                if(board[y-1+i][x-1] == -2 || board [y-1+i][x-1] == 1)
                {
                    collision = 1;
                    break;
                }
            }
        }
        placeShip(board, 2, orientation, x, y, 1);
    }
}

void AIjednomasztowiec(int board[10][10])
{
    int x = 1+rand() % 10, y = 1+rand() % 10;
    int collision = 0;
    for(int i=0;i<1;i++)
    {
        if(board[y-1][x-1+i] == -2 || board [y-1][x-1+i] == 1)
        {
            collision = 1;
            break;
        }
    }
    while(collision==1)
    {
        x=1+rand() % 10;
        y=1+rand() % 10;
        collision = 0;
        for(int i=0;i<1;i++)
        {
            if(board[y-1][x-1+i] == -2 || board [y-1][x-1+i] == 1)
            {
                collision = 1;
                break;
            }
        }
    }
    placeShip(board, 1, 1, x, y, 1);
}


void AIPlaceShips(int board[10][10])
{
    srand(time(NULL));
    int orientation = rand () % 2;

    if(orientation == 1)
    {
        int x=1+rand() % 7,y=1+rand() % 10;
        placeShip(board, 4, orientation, x, y, 1);
    }
    else
    {
        int x=1+rand() % 10,y=1+rand() % 7;
        placeShip(board, 4, orientation, x, y, 1);
    }

    AItrojmasztowiec(board);
    AItrojmasztowiec(board);

    AIdwumasztowiec(board);
    AIdwumasztowiec(board);
    AIdwumasztowiec(board);

    AIjednomasztowiec(board);
    AIjednomasztowiec(board);
    AIjednomasztowiec(board);
    AIjednomasztowiec(board);
}


void pShooting(int ships[10][10], int shots[10][10], int toDisplay[10][10])
{
    system("cls");
    displayTwo(toDisplay, shots);
    printf("\nPodaj koordynaty strzalu:\n");
    int x=0, y=0;
    scanf("%d %d", &x, &y);
    while(x<1 || x>10 || y<1 || x>10 || shots[y-1][x-1]!=0)
    {
        clearTwoLines();
        printf("Bledne dane\n");
        scanf("%d %d", &x, &y);
    }
    if(ships[y-1][x-1]==1)
    {
        shots[y-1][x-1] = 2;
        ships[y-1][x-1] = 2;
        int size=1;
        int hits=1;
        int i=1;

        while(x+i<11)
        {
            if(ships[y-1][x+i-1]==1 || ships[y-1][x+i-1]==2)
            {
                size++;
                if(ships[y-1][x+i-1]==2)
                    hits++;
            }
            else
                break;
            i++;
        }
        i=1;
        while(x-i>0)
        {
            if(ships[y-1][x-i-1]==1 || ships[y-1][x-i-1]==2)
            {
                size++;
                if(ships[y-1][x-i-1]==2)
                    hits++;
            }
            else
                break;
            i++;
        }
        i=1;
        while(y+i<11)
        {
            if(ships[y+i-1][x-1]==1 || ships[y+i-1][x-1]==2)
            {
                size++;
                if(ships[y+i-1][x-1]==2)
                    hits++;
            }
            else
                break;
            i++;
        }
        i=1;
        while(y-i>0)
        {
            if(ships[y-i-1][x-1]==1 || ships[y-i-1][x-1]==2)
            {
                size++;
                if(ships[y-i-1][x-1]==2)
                    hits++;
            }
            else
                break;
            i++;
        }

        if(size == hits)
        {
            pCounter++;
            int orientation=0;
            while (x-1>0 && ships[y-1][x-2]==2)
            {
                x--;
                orientation = 1;
            }
            while (y-1>0 && ships[y-2][x-1]==2)
            {
                y--;
            }
            if (ships[y-1][x]==2 && x<10)
            {
                orientation = 1;
            }
            placeShip(ships, size, orientation, x, y, 3);
            placeShip(shots, size, orientation, x, y, 3);
        }
    }
    else if(ships[y-1][x-1]==0 || ships[y-1][x-1]==-2)
        shots[y-1][x-1] = -1;

}

void kShooting(int ships[10][10], int shots[10][10])
{
    int x=0,y=0;
    if(firstX)
    {
        if(lastX)
        {
            if(lastX<firstX)
            {
                int tmp = lastX;
                lastX = firstX;
                firstX = tmp;
            }
            if(lastY<firstY)
            {
                int tmp = lastY;
                lastY = firstY;
                firstY = tmp;
            }
            if(firstX == lastX)
            {
                if(shotNumber == 0)
                {
                    if(firstY == 1 || shots[firstY-2][firstX-1]==1)
                        shotNumber++;
                    else
                    {
                        x = firstX;
                        y = firstY - 1;
                        if(ships[y-1][x-1]==1)
                            firstY = firstY - 1;
                    }

                }
                if(shotNumber == 1)
                {
                    x = firstX;
                    y = lastY + 1;
                    if(ships[y-1][x-1]==1)
                        lastY = lastY + 1;
                }
            }
            else if(firstY == lastY)
            {
                if(shotNumber == 0)
                {
                    if(firstX == 1 || shots[firstY-1][firstX-2]==1)
                        shotNumber++;
                    else
                    {
                        x = firstX - 1;
                        y = firstY;
                        if(ships[y-1][x-1]==1)
                            firstX = firstX - 1;
                    }

                }
                if(shotNumber == 1)
                {
                    x = lastX + 1;
                    y = firstY;
                    if(ships[y-1][x-1]==1)
                        lastX = lastX + 1;
                }
            }
        }
        else
        {
            if((firstY==1 || shots[firstY-2][firstX-1]==-2) && shotNumber==0)
                shotNumber++;
            else if((firstX==10 || shots[firstY-1][firstX]==-2) && shotNumber==1)
                shotNumber++;
            else if((firstY==10 || shots[firstY][firstX-1]==-2) && shotNumber==2)
                shotNumber++;

            switch(shotNumber)
            {
            case 0:
                x = firstX;
                y = firstY-1;
                break;
            case 1:
                x = firstX+1;
                y = firstY;
                break;
            case 2:
                x = firstX;
                y = firstY+1;
                break;
            case 3:
                x = firstX-1;
                y = firstY;
            }
        }

    }
    else
    {
        x = 1 + rand() % 10;
        y = 1 + rand() % 10;
        while(shots[y-1][x-1]!=0)
        {
            x = 1 + rand() % 10;
            y = 1 + rand() % 10;
        }
    }
    if(ships[y-1][x-1]==1)
    {
        if(firstX && !lastX)
        {
            lastX = x;
            lastY = y;
            shotNumber = 0;
        }
        else if(!firstX)
        {
            firstX = x;
            firstY = y;
        }
        shots[y-1][x-1] = 2;
        ships[y-1][x-1] = 2;
        int size=1;
        int hits=1;
        int i=1;

        while(x+i<11)
        {
            if(ships[y-1][x+i-1]==1 || ships[y-1][x+i-1]==2)
            {
                size++;
                if(ships[y-1][x+i-1]==2)
                    hits++;
            }
            else
                break;
            i++;
        }
        i=1;
        while(x-i>0)
        {
            if(ships[y-1][x-i-1]==1 || ships[y-1][x-i-1]==2)
            {
                size++;
                if(ships[y-1][x-i-1]==2)
                    hits++;
            }
            else
                break;
            i++;
        }
        i=1;
        while(y+i<11)
        {
            if(ships[y+i-1][x-1]==1 || ships[y+i-1][x-1]==2)
            {
                size++;
                if(ships[y+i-1][x-1]==2)
                    hits++;
            }
            else
                break;
            i++;
        }
        i=1;
        while(y-i>0)
        {
            if(ships[y-i-1][x-1]==1 || ships[y-i-1][x-1]==2)
            {
                size++;
                if(ships[y-i-1][x-1]==2)
                    hits++;
            }
            else
                break;
            i++;
        }
        if(size == hits)
        {
            kCounter++;
            firstX=0;
            lastX=0;
            firstY=0;
            lastY=0;
            shotNumber=0;

            int orientation=0;
            while (x-1>0 && ships[y-1][x-2]==2)
            {
                x--;
                orientation = 1;
            }
            while (y-1>0 && ships[y-2][x-1]==2)
            {
                y--;
            }
            if (ships[y-1][x]==2 && x<10)
            {
                orientation = 1;
            }
            placeShip(ships, size, orientation, x, y, 3);
            placeShip(shots, size, orientation, x, y, 3);
        }
    }
    else if(ships[y-1][x-1]==0 || ships[y-1][x-1]==-2)
    {
        shots[y-1][x-1] = -1;
        if(firstX)
            shotNumber++;
    }

}

int main()
{
    char start;
    srand(time(NULL));
    int pShips[10][10];
    for(int i=0;i<10;i++)
        for(int j=0;j<10;j++)
            pShips[i][j] = 0;

    int pShots[10][10];
    for(int i=0;i<10;i++)
        for(int j=0;j<10;j++)
            pShots[i][j] = 0;

    int kShips[10][10];
    for(int i=0;i<10;i++)
        for(int j=0;j<10;j++)
            kShips[i][j] = 0;

    int kShots[10][10];
    for(int i=0;i<10;i++)
        for(int j=0;j<10;j++)
            kShots[i][j] = 0;
    printf("\n WITAJ W GRZE W STATKI, TWOIM ZADANIEM JEST ZATOPIENIE OKRETOW KOMPUTERA. JEZELI ZATOPISZ\n RAZEM 10 STATKOW, WYGRYWASZ. Z DRUGIEJ STRONY, JEZELI KOMPUTER SZYBCIEJ ZATOPI TWOJE 10\n STATKOW, TO PRZEGRYWASZ. \n POWODZENIA! \n\n WCISNIJ 0, ABY KONTYNUOWAC: ");
    scanf("%c", &start);
    switch(start)
      {
        case '0':
        userPlaceShips(pShips);
        AIPlaceShips(kShips);

        while(1)
        {
          pShooting(kShips, pShots, pShips);
          if(pCounter == 10)
            {
              system("cls");
              printf("Plansza gracza\n");
              displayOne(pShips);
              printf("\nPlansza komputera\n");
              displayOne(kShips);
              printf("\nWygrywa gracz!!!");
              break;
            }
          kShooting(pShips, kShots);
          if(kCounter == 10)
            {
              system("cls");
              printf("Plansza gracza\n");
              displayOne(pShips);
              printf("\nPlansza komputera\n");
              displayOne(kShips);
              printf("\nWygrywa komputer!!!");
              break;
            }
        }
        default:
        return 0;
      }

}

