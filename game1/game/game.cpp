#include <iostream>
#include <conio.h>  //позволяет отслеживать без доп команд
#include <ctime>
#include <windows.h>

using namespace std;

HANDLE hConsole;
bool gameOver;
const int width = 20;
const int height = 20;
int x, y, fruitX, fruitY, nTail, score;
int tailX[100], tailY[100];
enum eDirection{STOP=0,LEFT,RIGHT,UP,DOWN};
eDirection dir;

void Setup() {
    gameOver = false;
    dir = STOP; //изначально некуда не двигаемся
    x = width / 2 - 1;
    y = height / 2 - 1;
    srand(time(0));
    fruitX = 1 + rand() % (width - 2);
    fruitY = 1 + rand() % (height - 2);
    score = 0;
}

void Draw() {
    system("cls");  //очищает терминал при вызове draw
    for (int i = 0; i <= width;++i) {
        cout << "#";
    }
    cout << endl;

    for (int i = 1; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0 || j == width - 1)
                cout << "#";
            if (i == y && j == x)
                cout << "\x1b[32m0\x1b[0m";
            else if (i == fruitY && j == fruitX)
                cout << "\x1b[35mF\x1b[0m";
            else {
                bool print = false;
                for (int k = 0; k < nTail; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        print = true;
                        cout << "\x1b[32mo\x1b[0m";

                    }

                }
                if (!print)
                    cout << " ";
            }
        }
        cout << endl;
    }
    for (int i = 0; i <= width; i++) {
        cout << "#";
    }
    cout << endl;
    cout << "Score: " << score << endl;
    Sleep(200);
}

void Input() {
    if (_kbhit()) { //нажал ли на кнопку
        switch (_getch())   //какую кнопку нажал
        {
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
    case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'x':
            gameOver = true;
            break;
        }

    }
}

void Logic() {
    int prevX = tailX[0]; // предыдущие значение х
    int prevY = tailY[0];
    tailX[0] = x;
    tailY[0] = y;
    int prev2X, prev2Y;
    for (int i = 1; i < nTail; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch (dir)
    {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    }
    if (x >= width-1)
        x = 0;
    else if (x < 0) {
        x = width - 2;
    }
    if (y >= height)
        y = 0;
    else if (y < 0) {
        y = height - 1;
    }
    for (int i = 0; i < nTail; i++) {
        if (tailX[i] == x && tailY[i] == y)
            gameOver = true;
    }
    if (x == fruitX && y == fruitY) {
        score += 2;
        srand(time(0));
        fruitX = 1 + rand() % (width - 2);
        fruitY = 1 + rand() % (height - 2);
        nTail++;
    }
}

int main()
{
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE); //Получение дескриптора окна
    Setup();
    while (!gameOver) {
        Draw();
        Input();
        Logic();

    }
    return 0;
}