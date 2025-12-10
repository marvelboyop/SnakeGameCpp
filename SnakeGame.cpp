// Notes - 1. setup(), 2. draw(); , 3. input(); 4. logic();

#include <iostream>
#include <cstdlib>   //For rand() and srand()
#include <ctime>     // For time()
#include <conio.h>   // required for _kbhit and _getch
#include <windows.h> // used for Sleep() function

using namespace std;

const int width = 30;  // width of the map
const int height = 20; // height of the map
int score = 0;         // to save the score of the player
int gameSpeed = 90;    // milliseconds per frame (lower = faster)

int x, y;           // snake head position
int fruitX, fruitY; // fruit position

int tailX[100], tailY[100];
int nTail = 0;

int choice;
bool gameOver;

void hideCursor()
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursor;
    cursor.dwSize = 1;
    cursor.bVisible = FALSE;
    SetConsoleCursorInfo(h, &cursor);
}

void clearScreenSmooth()
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD position = {0, 0};
    SetConsoleCursorPosition(h, position);
}

enum Direction
{
    STOP = 0,
    LEFT,
    RIGHT,
    UP,
    DOWN
};
Direction dir;

void setup()
{
    dir = STOP;
    gameOver = false;

    // Start snake in the middle
    x = width / 2;
    y = height / 2;

    // Random fruit position
    do
    {
        fruitX = rand() % width;
        fruitY = rand() % height;
    } while (fruitX == x && fruitY == y);
}

void draw()
{
    clearScreenSmooth(); // removes flicker - puts cursor on the start of console

    // TOP WALL
    for (int i = 0; i < width + 2; i++)
    {
        cout << "#";
    }
    cout << endl;

    for (int i = 0; i < height; i++)
    {
        cout << "#"; // left wall

        for (int j = 0; j < width; j++)
        {
            // Snake head
            if (i == y && j == x)
            {
                cout << "O";
            }
            // Fruit
            else if (i == fruitY && j == fruitX)
            {
                cout << "F";
            }
            else
            {
                bool printedTail = false;

                // Loop through all tail segments
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << "o"; // print tail segment
                        printedTail = true;
                        break;
                    }
                }

                if (!printedTail)
                    cout << " "; // empty space
            }
        }

        cout << "#\n"; // right wall
    }

    // BOTTOM WALL
    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl
         << "Score = " << score;
    cout << endl;
}

void input()
{
    if (_kbhit()) // if keyboard is pressed (keyboard hit)
    {
        switch (_getch())
        {
        case 'a':
            if (dir != RIGHT)
                dir = LEFT;
            break;
        case 'd':
            if (dir != LEFT)
                dir = RIGHT;
            break;
        case 'w':
            if (dir != DOWN)
                dir = UP;
            break;
        case 's':
            if (dir != UP)
                dir = DOWN;
            break;
        case ' ':
            gameSpeed = 30; // Boost only while space is pressed
            break;
        case 'x':
            gameOver = true; // emergency exit
            break;
        }
    }

    // Reset speed automatically when space is NOT pressed
    if (!GetAsyncKeyState(VK_SPACE))
    {
        gameSpeed = 90;
    }

    //     if (GetAsyncKeyState(VK_SPACE))     // if pressed
    //     gameSpeed = 20;
    // else                                // if NOT pressed
    //     gameSpeed = 90;
}

void logic()
{
    // --- 1. SAVE OLD HEAD POSITION BEFORE MOVING ---
    int prevHeadX = x;
    int prevHeadY = y;

    // --- 2. MOVE HEAD ---
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
    default:
        break;
    }

    // --- 3. MOVE TAIL ---
    // first tail segment follows old head position

    int prevX = prevHeadX;
    int prevY = prevHeadY;
    int tempX, tempY;

    for (int i = 0; i < nTail; i++)
    {
        tempX = tailX[i];
        tempY = tailY[i];

        tailX[i] = prevX;
        tailY[i] = prevY;

        prevX = tempX;
        prevY = tempY;
    }

    // --- 4. EAT FRUIT ---
    if (x == fruitX && y == fruitY)
    {
        score++;

        // Add new tail segment at a dummy location
        if (nTail == 0)
        {
            tailX[0] = prevHeadX; // first tail segment follows the previous co-ords of head
            tailY[0] = prevHeadY;
        }
        else
        {
            tailX[nTail] = tailX[nTail - 1]; // every new tail segment follows its previous tail segment
            tailY[nTail] = tailY[nTail - 1];
        }

        nTail++;

        if (score % 5 == 0 && gameSpeed > 20)
        {
            gameSpeed -= 10;
        }

        // NEW FRUIT POSITION
        do
        {
            fruitX = rand() % width;
            fruitY = rand() % height;
        } while ((fruitX == x && fruitY == y)); // avoid spawning on head
    }
}

void gameOverFunc()
{
    // If snake hits the wall -> game over for now

    // ********** wall - mode ****************
    if (choice == 1)
    {
        if (x <= 0 || x >= width - 1 || y <= 0 || y >= height - 1)
            gameOver = true;
    }

    //************* Wrap-around mode/NO Wall Mode ****************
    else if (choice == 2)
    {
        if (x >= width)
            x = 0;
        else if (x < 0)
            x = width - 1;
        if (y >= height)
            y = 0;
        else if (y < 0)
            y = height - 1;
    }
    else
    {
        cout << "Invalid Choice!! Enter valid Input.";
    }

    // Tail collision
    for (int i = 0; i < nTail; i++)
    {
        if (tailX[i] == x && tailY[i] == y)
            gameOver = true;
    }
}

int main()
{
    srand(time(0));

    cout << "Enter 1 for wall mode and 2 for No-Wall Mode : ";
    cin >> choice;

    // validate once
    while (choice != 1 && choice != 2)
    {
        cout << "Invalid choice. Enter 1 for wall mode and 2 for No-Wall Mode: ";
        cin >> choice;
    }

    setup();
    hideCursor();

    while (!gameOver)
    {
        input();
        logic();        // first move the snake
        gameOverFunc(); // then check collision
        draw();
        Sleep(gameSpeed); //  to set moves per second
        if (score == 50)
        {
            cout << "\n\nYou win the Snake Game!!! Congartulations.\n";
            gameOver = true;
        }
    }

    return 0;
}
