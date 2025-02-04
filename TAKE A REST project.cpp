#include <iostream>
#include <conio.h>
#include <cstring>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <iomanip>
#include <stdio.h>
#include <algorithm>
#include <time.h>
#include <windows.h>

using namespace std;

struct choice {
    string word, score;
    int WIDTH;
};

//x_o
struct Game
{
    string Playername;
    char Playerchar;
    int Playerscore;
}P[2];


class Info {
private:
    string username;
    string password;
    int guess_number, snake, bong, x_o;
public:
    Info()
    {
        username = "\0";
        password = "\0";
        snake = bong = x_o = 0;
        guess_number = -100;
    }
    void setName(string name)
    {
        username = name;
    }
    void setPassword(string pass)
    {
        password = pass;
    }
    void setguess_number(int score)
    {
        guess_number = score;
    }
    void setsnake(int score)
    {
        snake = score;
    }
    void setbong(int score)
    {
        bong = score;
    }
    void setx_o(int score)
    {
        x_o = score;
    }

    string getName()
    {
        return username;
    }
    string getPassowrd()
    {
        return password;
    }
    int getguess_number()
    {
        return guess_number;
    }
    int getsnake()
    {
        return snake;
    }
    int getbong()
    {
        return bong;
    }
    int getx_o()
    {
        return x_o;
    }
};

Info user;
int DD;
void login();
void reg();
void shape(choice* coo, int size, int arrow);
bool check_username(string name);
string pass();
void confirm_password(string password);
bool check_password(string name, string password);
void forget_password(string check_name);
void getdata(string name, string password);
void update(int* scores, int n);
void games(Info player);
void guess_number();
void snake();
void bong();
int x_o();

//for x_o
void getread();
void choose1();
void choose2();
void choose3();
void menu1(int);
void menu2(int);
void hold(int);
void XOGame();
char m, s, o;
int i;
int maxchoose = 2;
int r = 0, c = 0;
char XO[3][3];
void menu(int r, int c);
char checkXO();
void Display();

//////////////////// FOR BONG GAME
//Enumeration for Direction and we wrote the integers cause it is seem to be
//easy for debugging

//start of base functionality of the movement of the ball
enum eDir {
    STOP = 0, LEFT = 1, UPLEFT = 2, DOWNLEFT = 3, RIGHT = 4, UPRIGHT = 5
    , DOWNRIGHT = 6
};

class cBall
{
private:
    //Varaibles to store the position of the ball
    int x, y;
    int originalX, originalY;
    //Direction of the ball
    eDir direction;

public:
    //Constructor X and Y Coordinates
    cBall(int posX, int posY)
    {
        //those will save the original position of the ball so we can
        //reset the game later
        originalX = posX;
        originalY = posY;

        //the current position of the ball
        x = posX;
        y = posY;
        direction = STOP;

    }
    //to reset the game
    void Reset()
    {
        //this will give x , y  the original position
        x = originalX;
        y = originalY;
        direction = STOP;
    }
    //To change the direction of the ball
    void changeDirection(eDir d)
    {
        // d is the new direction of the ball
        direction = d;

    }
    //change the direction randomly
    void randomDirection()
    {
        // to generate random numbers from 1 => 6 cause we only have six directions
        //STOP is when the ball is not change its direction so there is no moving
        direction = (eDir)((rand() % 6) + 1);
    }
    //Public functions to get the current x and y coordinates
    inline int getX() { return x; }
    inline int getY() { return y; }
    inline eDir getDirection() { return direction; }
    // this function is consider as the main function for ball for moving
    void Move()
    {
        // x is incresing to the right and y is increasing to bottom
        // because the main position starts from the top left
        switch (direction)
        {
        case STOP:
            break;

        case LEFT:
            x--;
            break;

        case RIGHT:
            x++;
            break;

        case UPLEFT:
            x--; y--;
            break;

        case DOWNLEFT:
            x--; y++;
            break;

        case UPRIGHT:
            x++; y--;
            break;

        case DOWNRIGHT:
            x++; y++;
            break;

        default:
            break;
        }
    }
    friend ostream& operator << (ostream& o, cBall c)
    {
        o << "Ball [" << c.x << "," << c.y << "][" << c.direction << "]";
        return o;
    }
};
//End of base functionality of the movement of the ball

//Start of player controlable "PADDLE"
//the paddle is moving the player up and down and bounce the ball
class cPaddle
{
    //private variables for the positioning
private:
    int x, y;
    //variables so we can reset the original position of the paddle
    int originalX, originalY;

public:
    //constructor
    cPaddle()
    {
        x = y = 0;

    }
    //constructor
    cPaddle(int posX, int posY) : cPaddle()
    {
        //every time we reset the game it will start from the original position
        originalX = posX;
        originalY = posY;
        x = posX;
        y = posY;
    }
    //inline function to return the player to the start of the game
    inline void Reset() { x = originalX; y = originalY; }

    //inline function to return the x ,y coordinates
    inline int getX() { return x; }
    inline int getY() { return y; }

    //since the paddles only moves up and down so
    //we do not need to make another inline directions function
    //moving up and down refers to the Y coordinates
    inline void moveUp() { y--; }
    inline void moveDown() { y++; }

    friend ostream& operator << (ostream& o, cPaddle c)
    {
        o << "Paddle [" << c.x << "," << c.y << "]";
        return o;
    }
};

//this class is to manage all the game and score of the game
//actully all aspects of the game
class cGameManger
{
private:
    //the area of the game
    int width, height;
    //score of players
    int score1, score2;
    //used in order to move the two players up and down
    char up1, down1, up2, down2;
    //boolean to quit the game when pressing a specific character
    bool quit;
    //pointer so we can initiallize the ball and create the ball object
    cBall* ball;
    //A paddle object for every player
    cPaddle* player1;
    cPaddle* player2;


public:
    //the constructor for the game manger class
    cGameManger(int w, int h)
    {

        srand(time(NULL));
        // quit is false to run the game
        quit = false;
        up1 = 'w';
        up2 = 'i';
        down1 = 's';
        down2 = 'k';
        score1 = score2 = 0;
        width = w;
        height = h;
        //To place the ball at the middle of the game
        ball = new cBall(w / 2, h / 2);
        //To place the paddle at the middle of its side in the game
        player1 = new cPaddle(1, h / 2 - 3);
        player2 = new cPaddle(w - 2, h / 2 - 3);
    }
    //the destructor because now we have a dynamic memory so that not creating memory leak
    ~cGameManger()
    {
        delete ball;
        delete player1;
        delete player2;
    }
    //
    void ScoreUp(cPaddle* player)
    {
        //if the addresses are the same then we increase the score
        if (player == player1)
        {
            score1++;
        }
        else if (player == player2)
        {
            score2++;
        }
        //to reset the ball and players to its default positions
        ball->Reset();
        player1->Reset();
        player2->Reset();
    }
    //function to draw things in the game
    void Draw()
    {
        HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
        //system(“cls”): This command is used to make the screen/terminal clear.
        //system("cls");
        SetConsoleCursorPosition(h, { 0,0 });
        //print the walls for the game
        // j : is x coordinates... i : is the Y coordinates
        for (int i = 0; i < width + 2; i++) {
            SetConsoleTextAttribute(h, 7);
            cout << "_";
        }
        cout << endl;

        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                //these variables will get the x , y coordinates of the object ball
                //that we initialized in the cGameManger
                int ballx = ball->getX();
                int bally = ball->getY();

                //these variables will get the x , y coordinates of both players
                //that we initialized in the cGameManger
                int player1x = player1->getX();
                int player2x = player2->getX();
                int player1y = player1->getY();
                int player2y = player2->getY();

                //if condition for the first character on the screen
                if (j == 0)
                {
                    cout << "|";
                }
                //if conditions for the logic for printing the actual content of the map

                if (ballx == j && bally == i)
                {
                    SetConsoleTextAttribute(h, 7);
                    cout << "O"; //Ball
                }
                else if (player1x == j && player1y == i)
                {
                    SetConsoleTextAttribute(h, 14);
                    cout << "\xDB"; //Player1
                }
                else if (player2x == j && player2y == i)
                {
                    SetConsoleTextAttribute(h, 10);
                    cout << "\xDB"; //Player2
                }
                //===============
                else if (player1x == j && player1y + 1 == i)
                {
                    SetConsoleTextAttribute(h, 14);
                    cout << "\xDB"; //Player1
                }
                else if (player1x == j && player1y + 2 == i)
                {
                    SetConsoleTextAttribute(h, 14);
                    cout << "\xDB"; //Player1
                }
                else if (player1x == j && player1y + 3 == i)
                {
                    SetConsoleTextAttribute(h, 14);
                    cout << "\xDB"; //Player1
                }
                //===============
                else if (player2x == j && player2y + 1 == i)
                {
                    SetConsoleTextAttribute(h, 10);
                    cout << "\xDB"; //Player2
                }
                else if (player2x == j && player2y + 2 == i)
                {
                    SetConsoleTextAttribute(h, 10);
                    cout << "\xDB"; //Player2
                }
                else if (player2x == j && player2y + 3 == i)
                {
                    SetConsoleTextAttribute(h, 10);
                    cout << "\xDB"; //Player2
                }

                else
                    cout << " ";
                //if condition to print the wall again
                if (j == width - 1)
                {
                    SetConsoleTextAttribute(h, 7);
                    cout << "|";
                }
            }
            cout << endl;
        }


        for (int i = 0; i < width + 2; i++)
        {
            SetConsoleTextAttribute(h, 7);
            cout << "-";
        }
        cout << endl;
        SetConsoleTextAttribute(h, 14);
        cout << "Score1: " << score1;
        SetConsoleTextAttribute(h, 10);
        cout << "  Score2 : " << score2 << endl;
    }
    void input()
    {
        ball->Move();
        int ballx = ball->getX();
        int bally = ball->getY();
        int player1x = player1->getX();
        int player2x = player2->getX();
        int player1y = player1->getY();
        int player2y = player2->getY();

        // kbhit() functionality is basically for the Keyboard Hit.
        // This function deals with keyboard pressing.
        if (_kbhit())
        {
            char current = _getch();
            if (current == up1)
            {
                if (player1y > 0)
                    player1->moveUp();
            }
            if (current == up2)
            {
                if (player2y > 0)
                    player2->moveUp();
            }
            if (current == down1)
            {
                if (player1y + 4 < height)
                    player1->moveDown();
            }
            if (current == down2)
            {
                if (player2y + 4 < height)
                    player2->moveDown();
            }
            if (ball->getDirection() == STOP)
            {
                ball->randomDirection();
            }
            if (current == 'q')
            {
                //quit = true;
                games(user);
            }
        }
    }

    //we need to a function that will do the call logic detection of the game
    void Logic()
    {
        int ballx = ball->getX();
        int bally = ball->getY();
        int player1x = player1->getX();
        int player2x = player2->getX();
        int player1y = player1->getY();
        int player2y = player2->getY();

        //left paddle
        for (int i = 0; i < 4; i++)
            if (ballx == player1x + 1)
                if (bally == player1y + i)
                    ball->changeDirection((eDir)((rand() % 3) + 4));

        //right paddle
        for (int i = 0; i < 4; i++)
            if (ballx == player2x - 1)
                if (bally == player2y + i)
                    ball->changeDirection((eDir)((rand() % 3) + 1));

        //bottom wall
        if (bally == height - 1)
            ball->changeDirection(ball->getDirection() == DOWNRIGHT ? UPRIGHT : UPLEFT);

        //top wall
        if (bally == 0)
            ball->changeDirection(ball->getDirection() == UPRIGHT ? DOWNRIGHT : DOWNLEFT);

        //right wall
        if (ballx == width - 1)
            ScoreUp(player1);

        //left wall
        if (ballx == 0)
            ScoreUp(player2);
    }

    void Run()
    {
        while (!quit)
        {
            Draw();
            input();
            Logic();
            Sleep(40);
        }
    }
};

////////////////////// for snake game////////////////////////

int snake_speed = 90;
int snake_score_adder = 10;
bool gameover = false;
int x = 25, y = 9, Fruitx, Fruity, score = 0;
int tailx[100], taily[100];
int	LengthOfTail = 0;
enum diriction { stop = 0, Left, Right, up, down };
diriction dir = stop;
//functions declaring
void ChoiceForGame();
void menu_for_sanke(int);
void print();
void input();
void logic();
void run_game();
void structions();
void ChoiceForSnakeSpeed();
void menu_for_sanke_speed(int);

///////////////Guess number//////////////
int Arandom_number();
int* NumToDigits(int);
void run();
void menu_for_guesscode(int);
void ChoiceFor_GuessGame();

int main()
{
    system("color 7");
    //Info player;
    DD = 0;
    const int n = 2;
    choice choose[n];
    choose[0].word = "Login";
    choose[0].WIDTH = 8;

    choose[1].word = "Register";
    choose[1].WIDTH = 10;

    //choose and call function
    int i = 1;
    char ch;
    shape(choose, n, 1);
    while (1)
    {
        ch = _getch();

        switch (ch)
        {
        case 115:
            if (i != 1)
            {
                i--;
                shape(choose, n, i);
            }
            else {
                i = 2;
                shape(choose, n, i);
            }
            break;

        case 119:
            if (i != 2)
            {
                i++;
                shape(choose, n, i);
            }
            else {
                i = 1;
                shape(choose, n, i);
            }
            break;
        case 32:
            if (i == 1)
            {
                login();
            }
            else if (i == 2)
            {
                reg();
            }
            break;
        }
    }

    return 0;
}


//for choose and shap of words
void shape(choice* coo, int size, int arrow)
{
    system("cls");
    //for welcome to user
    string hello = "Take a rest";
    cout.width(50);          //to start after 50 space
    if (DD == 0)
    {
        cout << hello << endl << endl;
    }
    else if (DD == 1)
    {
        cout << hello << endl;
        cout.width(46);
        cout << "Hello, " << user.getName() << endl;
    }

    for (int i = 0; i < size; i++)
    {
        int WIDTH = coo[i].WIDTH;
        string WORD = coo[i].word;
        string SCORE = coo[i].score;

        cout.width(10);
        for (int w = 0; w < WIDTH; w++)
        {
            if (w == 0)
                cout << char(201);

            cout << char(205);
            if (w == WIDTH - 1)
                cout << char(187);
        }
        cout.width(10);
        cout << endl;
        //Make coloumn right and left for one time -------> 1
        for (int h = 0; h < 0; h++)
        {
            for (int w = 0; w < WIDTH; w++)
            {
                if (w == 0)
                    cout << char(186);
                cout << " ";
                if (w == WIDTH - 1)
                    cout << char(186);
            }
            cout << endl;
        }
        //print arrow in appropriate place
        if (arrow == i + 1)
        {
            cout.width(0);
            cout << "-->";
            cout.width(7);
        }
        cout << char(186);
        //print word and shaoe
        if (WIDTH == 8)
        {
            cout.width(6);
            cout << WORD;
            cout.width(3);
            cout << char(186) << endl;
        }
        else {
            cout.width(9);
            cout << WORD;
            cout.width(2);
            cout << char(186) << endl;
        }
        cout.width(10);
        //Make coloumn right and left for one time -------> 2
        for (int h = 0; h < 0; h++)
        {
            for (int w = 0; w < WIDTH; w++)
            {
                if (w == 0)
                    cout << char(186);

                cout << " ";

                if (w == WIDTH - 1)
                    cout << char(186);
            }
            cout << endl;
        }

        for (int w = 0; w < WIDTH; w++)
        {
            if (w == 0)
                cout << char(200);
            cout << char(205);

            if (w == WIDTH - 1)
                cout << char(188);
        }
        cout << endl;

        if (DD == 1)
        {
            cout.width(30);
            cout << SCORE << endl;
        }
    }
    return;
}

//for register
void reg()
{
    system("cls");
    fstream data;
    data.open("data.csv", ios::app);

    //Info player;
    string name, password;
    bool check_name = false;
    
    do {
        cout << "Enter username: ";
        cin >> name;
        check_name = check_username(name);
        if (check_name)
        {
            cout << "Username Exists before!\n";
        }
        else {
            password = pass();
            confirm_password(password);
            data << name << "," << password << "," << -100 << "," << 0 << "," << 0 << "," << 0 << endl;
            user.setName(name);
            user.setPassword(password);
            getdata(name, password);
            games(user);
        }
    } while (check_name);

    data.close();
    return;
}

//for login
void login()
{
    system("cls");
    string name, password;
    bool check_name, check_pass;
    char ch, c;
    char ss, s;
    do {
        cout << "Enter username: ";
        cin >> name;
        check_name = check_username(name);
        if (!check_name)
        {
            cout << "Username does not exist!\n";
            cout << "If you need to register press Y else press N: ";
            cin >> ch;
            c = tolower(ch);
            if (c == 'y')
            {
                reg();
                break;
            }
        }
        else {
            do {
                cout << "Enter password: ";
                cin >> password;
                check_pass = check_password(name, password);
                if (check_pass)
                {
                    getdata(user.getName(), user.getPassowrd());
                    games(user);
                }
                else {
                    cout << "Password is wrong!\n";
                    cout << "If you forget pasword press Y else N: ";
                    cin >> ss;
                    s = tolower(ss);
                    if (s == 'y')
                    {
                        forget_password(name);
                        games(user);
                    }
                }
            } while (s == 'n');
        }
    } while (!check_name);

    return;
}

//check if username exist or not
bool check_username(string name)
{
    fstream data;
    ifstream readme("data.csv");
    data.open("data.csv", ios::app);
    string text;

    while (getline(readme, text)) {
        int len = text.find(",");
        string fname = text.substr(0, len);
        if (fname == name)
        {
            data.close();
            return true;
        }
    }
    data.close();
    return false;
}

//for input password
string pass()
{
    string password;
    bool check_password = false;
    cin.ignore();
    do {
        cout << "Password must it consists of at least 8 characters, including: at least one of * ! @ % and not include ',' \n";
        cout << "Enter password: ";
        getline(cin, password);
        for (int i = 0; i < password.length(); i++)
        {
            if (password[i] == '#' || password[i] == '*' || password[i] == '!' || password[i] == '@' || password[i] == '%')
            {
                check_password = true;
            }
            if (password[i] == ',')
                check_password = false;
        }
    } while (!check_password || password.length() < 8);

    return password;
}

//for confirm password
void confirm_password(string password)
{
    string confirm_pass;
    char ch, c;
    do {
        cout << "Enter confirm password: ";
        cin >> confirm_pass;

        if (password != confirm_pass)
        {
            cout << "invalid confirm password" << endl;
            cout << "If you need to Enter password again Press Y else Enter N: ";
            cin >> ch;
            c = tolower(ch);
            if (c == 'y')
            {
                password = pass();
            }
        }
    } while (password != confirm_pass);

    return;
}

bool check_password(string name, string password)
{
    fstream data;
    ifstream readme("data.csv");
    data.open("data.csv", ios::app);
    string text;

    while (getline(readme, text)) {
        int len_n = text.find(",");
        string fname = text.substr(0, len_n);

        int len_p = text.find(",", len_n + 1);
        string check_pass = text.substr(len_n + 1, len_p - len_n - 1);
        if (fname == name)
        {
            if (check_pass == password)
            {
                user.setName(name);
                user.setPassword(password);

                data.close();
                return true;
            }
        }
    }
    data.close();
    return false;
}

void forget_password(string check_name)
{
    system("cls");
    string name;
    cin.ignore();
    do {
        cout << "Enter username: ";
        getline(cin, name);
        if (check_name != name)
        {
            cout << "Username is wrong!";
        }

    } while (name != check_name);

    string password = pass();
    confirm_password(password);

    fstream data;
    ifstream readme("data.csv");
    data.open("data.csv", ios::app);
    string text;

    while (getline(readme, text)) {
        int len_n = text.find(",");
        string fname = text.substr(0, len_n);

        int len_p = text.find(",", len_n + 1);
        string check_pass = text.substr(len_n + 1, len_p - len_n - 1);
        if (fname == name)
        {
            user.setName(name);
            user.setPassword(password);

            int len_1 = text.find(",", len_p + 1);
            string sguess_number = text.substr(len_p + 1, len_1 - len_p - 1);
            int guess_number = stoi(sguess_number);

            int len_2 = text.find(",", len_1 + 1);
            string ssnake = text.substr(len_1 + 1, len_2 - len_1 - 1);
            int snake = stoi(ssnake);

            int len_3 = text.find(",", len_2 + 1);
            string sbong = text.substr(len_2 + 1, len_3 - len_2 - 1);
            int bong = stoi(sbong);

            int len_4 = text.find(",", len_3 + 1);
            string sx_o = text.substr(len_3 + 1, len_4 - len_3 - 1);
            int x_o = stoi(sx_o);

            if (guess_number >= user.getguess_number() && snake >= user.getsnake())
            {
                user.setguess_number(guess_number);
                user.setsnake(snake);
                user.setbong(bong);
                user.setx_o(x_o);
            }
        }
    }
    data << user.getName() << "," << user.getPassowrd() << "," << user.getguess_number() << "," << user.getsnake() << "," << user.getbong() << "," << user.getx_o() << endl;
    data.close();
    return;
}


void update(int* scores, int n)
{
    fstream data;
    ifstream readme("data.csv");
    data.open("data.csv", ios::app);
    string text;

    if (scores[0] == 1)
    {
        if (scores[1] > user.getguess_number())
        {

            user.setguess_number(scores[1]);
            data << user.getName() << "," << user.getPassowrd() << "," << user.getguess_number() << "," << user.getsnake() << "," << user.getbong() << "," << user.getx_o() << endl;
        }
    }
    else if (scores[0] == 2)
    {
        if (scores[1] > user.getsnake())
        {
            user.setsnake(scores[1]);
            data << user.getName() << "," << user.getPassowrd() << "," << user.getguess_number() << "," << user.getsnake() << "," << user.getbong() << "," << user.getx_o() << endl;
        }
    }
    data.close();
    return;
}


void getdata(string name, string password)
{
    fstream data;
    ifstream readme("data.csv");
    data.open("data.csv", ios::app);
    string text;

    while (getline(readme, text)) {
        int len_n = text.find(",");
        string fname = text.substr(0, len_n);

        int len_p = text.find(",", len_n + 1);
        string check_pass = text.substr(len_n + 1, len_p - len_n - 1);
        if (fname == name)
        {
            if (check_pass == password)
            {
                int len_1 = text.find(",", len_p + 1);
                string sguess_number = text.substr(len_p + 1, len_1 - len_p - 1);
                int guess_number = stoi(sguess_number);

                int len_2 = text.find(",", len_1 + 1);
                string ssnake = text.substr(len_1 + 1, len_2 - len_1 - 1);
                int snake = stoi(ssnake);

                int len_3 = text.find(",", len_2 + 1);
                string sbong = text.substr(len_2 + 1, len_3 - len_2 - 1);
                int bong = stoi(sbong);

                int len_4 = text.find(",", len_3 + 1);
                string sx_o = text.substr(len_3 + 1, len_4 - len_3 - 1);
                int x_o = stoi(sx_o);

                if (guess_number >= user.getguess_number() && snake >= user.getsnake())
                {
                    user.setName(name);
                    user.setPassword(password);
                    user.setguess_number(guess_number);
                    user.setsnake(snake);
                    user.setbong(bong);
                    user.setx_o(x_o);
                }
            }
        }
    }
    data.close();
    return;
}


//for choose game
void games(Info user) {
    system("cls");
    system("color 9");

    //cout<<"Games"<<endl;
    /*cout<<user.getName()<<endl;
    cout<<user.getPassowrd()<<endl;
    cout<<user.getbong()<<endl;
    cout<<user.getx_o()<<endl;*/

    int const n = 5;
    choice game[n];
    game[0].word = "Guess Number";
    game[0].WIDTH = 13;
    game[0].score = "High score: " + to_string(user.getguess_number());

    game[1].word = " Snake";
    game[1].WIDTH = 8;
    game[1].score = "High score: " + to_string(user.getsnake());

    game[2].word = "Bong";
    game[2].WIDTH = 8;

    game[3].word = "X-O ";
    game[3].WIDTH = 8;

    game[4].word = "EXIST";
    game[4].WIDTH = 8;

    DD = 1;
    int i = 1;
    char ch;
    shape(game, n, 1);
    while (1)
    {
        ch = _getch();

        switch (tolower(ch))
        {
        case 119:
            if (i != 1)
            {
                i--;
                shape(game, n, i);
            }
            else {
                i = 5;
                shape(game, n, i);
            }
            break;

        case 115:
            if (i != 5)
            {
                i++;
                shape(game, n, i);
            }
            else {
                i = 1;
                shape(game, n, i);
            }
            break;

        case 32:
            if (i == 1)
            {
                guess_number();
            }
            else if (i == 2)
            {
                snake();
            }
            else if (i == 3)
            {
                bong();
            }
            else if (i == 4)
            {
                x_o();
            }
            else if (i == 5)
            {
                main();
            }
            break;
        }
    }
}

///////////////////Guess number///////////////
void guess_number()
{
    system("cls");
    ChoiceFor_GuessGame();

}

int Arandom_number()
{

    srand(time(0));
    int rnum = rand() % 8999 + 1000;

    return rnum;
}
int* NumToDigits(int y)
{
    int* p = new int[4];
    int div = 1000;
    for (int i = 0; i < 4; i++)
    {
        p[i] = y / div;
        y = y - p[i] * div;
        div = div / 10;
    }
    return p;
}

void run()
{
playagain:
    system("cls");
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    int arrto_guessgame_score[2];
    arrto_guessgame_score[0] = 1;
    int tries = 0;
    int guess;
    int randomnum = Arandom_number();
    int* point = NumToDigits(randomnum);
    int* gptr;
    int t = 0;
    bool before = false;
    cout << "please enter your Guessed number consisting of  4 digit : ";

    while (true)
    {
        SetConsoleTextAttribute(h, 7);
        cin >> guess;
        gptr = NumToDigits(guess);
        if (guess == randomnum)
        {
            cout << "\twinner" << endl;
            arrto_guessgame_score[1] = tries;
            update(arrto_guessgame_score, 2);
            break;
        }
        for (int i = 0; i < 4; i++)
        {
            if (gptr[i] == point[i])
            {
                SetConsoleTextAttribute(h, 10);
                cout << "+";
                before = true;
            }
            else
            {
                for (int j = 0; j < 4; j++)
                {
                    if (gptr[i] == point[j])
                    {
                        SetConsoleTextAttribute(h, 14);
                        cout << "$";
                        break;
                    }
                    else
                        t++;
                }
                if (t == 4) {
                    SetConsoleTextAttribute(h, 12);
                    cout << "-";
                }
            }
            t = 0;
            before = false;
        }
        cout << endl;
        tries--;
    }
    cout << "\t\tpress y if you Want to play again ?" << endl;
    if (_getch() == 'y') goto playagain;
    else ChoiceFor_GuessGame();
}

void structions_for_guesscode() {
    system("cls");
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, 7);
    cout << "\t\t\t\t HOW TO PLAY " << endl;
    cout << "\t GUESS THE CODE is a game where you are trying to guess a four digit's number" << endl;
    cout << "\t When you guess a digit there is 3 possibilities  " << endl;
    cout << "\t First possibility ";
    SetConsoleTextAttribute(h, 10);
    cout << "+ ";
    SetConsoleTextAttribute(h, 7);
    cout << ":\n\t\t the digit exsits and its in the right place\n\t Second possibility ";
    SetConsoleTextAttribute(h, 14);
    cout << "$ ";
    SetConsoleTextAttribute(h, 7);
    cout << ": \n\t\t the digit exsits but it is in wrong place\n\t third possibility ";
    SetConsoleTextAttribute(h, 12);
    cout << "- ";
    SetConsoleTextAttribute(h, 7);
    cout << ":\n\t\t the digit NOT exsits ";
    cout << "\n\n\t You WIN if you guessed the code correctly" << endl;
    cout << "\tSCORE works different here the highest possible score you can get is zero \n\t\t every time you guess incorrectly score decreasing by 1 " << endl;
    cout << "\tThat is all for now " << "\n\t\t ENJOY THE GAME " << endl;
    cout << "\t press ( w ) or ( s ) to go back \n" << endl;
}

void menu_for_guesscode(int arrow) {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    system("cls");
    string words[3] = { "Start game","How to play","Back" };
    for (int i = 0; i < 3; i++)
    {
        if (arrow - 1 == i) {
            SetConsoleTextAttribute(h, 10);
            cout << "-->" << words[i] << endl;
        }
        else {
            SetConsoleTextAttribute(h, 7);
            cout << words[i] << endl;
        }
    }

}

void ChoiceFor_GuessGame() {

    menu_for_guesscode(0);
    int arrowposition = 1;
    while (true) {

        switch (_getch())
        {
        case 'w':
            arrowposition--;
            if (arrowposition < 1)
            {
                arrowposition = 3;
                menu_for_guesscode(arrowposition);
            }
            else menu_for_guesscode(arrowposition);
            break;
        case 's':
            arrowposition++;
            if (arrowposition > 3)
            {
                arrowposition = 1;
                menu_for_guesscode(arrowposition);
            }
            else menu_for_guesscode(arrowposition);
            break;
            case char(32) :
                if (arrowposition == 1) {
                    run();
                }
                else if (arrowposition == 2) {
                    structions_for_guesscode();
                }
                else if (arrowposition == 3) {
                    //put here the prev func before chossing snake
                    games(user);
                }
            default:
                break;
        }
    }

}


/////////////snake game//////////////////////
void snake()
{
    system("cls");
    ChoiceForGame();
}
void set() {
    score = 0;
    x = 25, y = 9;
    gameover = false;
    dir = stop;
    LengthOfTail = 0;
}
void print() {
    // srand(time(0));

    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    //print the top
    //system("cls");
    SetConsoleCursorPosition(h, { 0,0 });
    std::cout << "\t\t";
    for (int i = 0; i < 50; i++)
    {
        cout << "_";
    }
    for (int i = 0; i < 20; i++)
    {
        cout << endl << "\t\t";
        //print the side
        for (int u = 0; u < 50; u += 49)
        {
            SetConsoleTextAttribute(h, 15);
            cout << "|";
            if (u == 49)break;
            //print the field ,snake and fruit
            for (int j = 1; j < 49; j++)
            {
                //print snake
                if (y == i && x == j) {
                    SetConsoleTextAttribute(h, 142);
                    cout << "0";
                }
                //print fruit
                else if (Fruitx == j && Fruity == i) {
                    SetConsoleTextAttribute(h, 143);
                    cout << '*';
                }
                //print field and tail
                else {
                    bool tailprint = false;
                    for (int k = 1; k < LengthOfTail; k++)
                    {

                        if (tailx[k] == j && taily[k] == i)
                        {
                            SetConsoleTextAttribute(h, 142);
                            cout << "o";
                            tailprint = true;
                        }

                    }
                    if (!tailprint)
                    {
                        SetConsoleTextAttribute(h, 130);
                        cout << " ";
                    }
                }

            }
        }
    }
    cout << "\n";
    cout << setfill(' ') << setw(16) << " ";
    //print the bottom
    for (int i = 0; i < 50; i++)
    {
        cout << "-";
    }
    cout << endl;
    cout << "score  " << score << endl;
}
void input() {
    if (_kbhit()) {

        switch (_getch())
        {
        case 'w':
            dir = up;
            break;
        case 's':
            dir = down;
            break;
        case 'd':
            dir = Right;
            break;
        case 'a':
            dir = Left;
            break;

            case char(27) :
                gameover = true;
                break;
        }
    }

}
void logic() {
    tailx[0] = x;
    taily[0] = y;
    int prevX, prevY;
    prevX = tailx[0];
    prevY = taily[0];
    int temptailX, temptailY;
    for (int i = 1; i < LengthOfTail; i++)
    {
        temptailX = tailx[i];
        temptailY = taily[i];
        tailx[i] = prevX;
        taily[i] = prevY;
        prevX = temptailX;
        prevY = temptailY;
    }
    switch (dir)
    {

    case Left:
        x--;
        break;
    case Right:
        x++;
        break;
    case up:
        y--;
        break;
    case down:
        y++;
        break;

    default:
        break;
    }
    for (int i = 0;i < LengthOfTail;i++) {
        if (tailx[i] == x && taily[i] == y) gameover = true;
    }
    if (x == Fruitx && y == Fruity) {
        score = score + snake_score_adder;
        Fruitx = rand() % 34 + 16;
        Fruity = rand() % 20;
        LengthOfTail++;
    }

    if (x > 48 || x < 0 || y>19 || y < 0) {
        gameover = true;
    }

}
void structions() {

    cout << "\t\t\t CONTROLS " << endl;
    cout << "\t To move upward press 'w' button" << endl;
    cout << "\t To move downward press 's' button" << endl;
    cout << "\t To move right press 'd' button" << endl;
    cout << "\t To move left press 'a' button" << endl;
    cout << "\t To exsit the game press 'Esc' button" << endl << endl;
    cout << "\t\t\t HOW TO PLAY " << endl;
    cout << "\t Move the SNAKE by controls buttons\n\t Try to eat the FRUIT" << endl;
    cout << "\t After SNAKE'S TAIL appears if you go backward you will lose so BE CAREFUL " << endl;
    cout << "\t That is all for this update \t Enjoy the game :) \n\t GET YOUR BEST HIGHSCORE NOW !!" << endl;
    cout << "\t press ( w ) or ( s ) to go back \n" << endl;
}
void run_game()
{
    int arrfor_snake_score[2];
    arrfor_snake_score[0] = 2;

    srand(time(0));
    Fruitx = rand() % 34 + 16;
    Fruity = rand() % 19 + 1;
    char ch = 'r';
    cout << "welcome to snake game ";


    system("cls");
playagain:
    while (gameover != true) {
        print();
        input();
        logic();
        Sleep(snake_speed);
    }
    while (gameover == true && ch != 'y') {
        cout << "you lose  " << endl;
        arrfor_snake_score[1] = score;
        //put high score function here
        update(arrfor_snake_score, 2);
        cout << "press y if you want to play again" << endl;
        cin >> ch;
        if (ch == 'y') {
            system("cls");
            set();
            ch = 'x';
            goto playagain;
        }
        else {
            set();  ChoiceForGame(); goto playagain;
        }
    }

}


void menu_for_sanke(int arrow) {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    system("cls");
    string words[4] = { "Start game","How to play","Option (Snake speed)","Back" };
    for (int i = 0; i < 4; i++)
    {
        if (arrow - 1 == i) {
            SetConsoleTextAttribute(h, 10);
            cout << "-->" << words[i] << endl;
        }
        else {
            SetConsoleTextAttribute(h, 7);
            cout << words[i] << endl;
        }
    }

}
void ChoiceForGame() {

    menu_for_sanke(0);
    int arrowposition = 1;
    while (true) {

        switch (_getch())
        {
        case 'w':
            arrowposition--;
            if (arrowposition < 1)
            {
                arrowposition = 4;
                menu_for_sanke(arrowposition);
            }
            else menu_for_sanke(arrowposition);
            break;
        case 's':
            arrowposition++;
            if (arrowposition > 4)
            {
                arrowposition = 1;
                menu_for_sanke(arrowposition);
            }
            else menu_for_sanke(arrowposition);
            break;
            case char(32) :
                if (arrowposition == 1) {
                    run_game();
                }
                else if (arrowposition == 2) {
                    structions();
                }
                else if (arrowposition == 3) {
                    ChoiceForSnakeSpeed();
                }
                else if (arrowposition == 4) {
                    //put here the prev func before chossing snake
                    games(user);
                }
            default:
                break;
        }
    }

}

void menu_for_sanke_speed(int arrow) {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    system("cls");
    string words[5] = { "SONIC SNAKE !!!","FAST","MEDIUM","SLOW","BACK" };
    for (int i = 0; i < 5; i++)
    {
        if (arrow - 1 == i) {
            SetConsoleTextAttribute(h, 10);
            cout << "-->" << words[i] << endl;
        }
        else {
            SetConsoleTextAttribute(h, 7);
            cout << words[i] << endl;
        }
    }

}

void ChoiceForSnakeSpeed() {

    menu_for_sanke_speed(0);
    int arrowpositionForSpeedMenu = 1;
    while (true) {

        switch (_getch())
        {
        case 'w':
            arrowpositionForSpeedMenu--;
            if (arrowpositionForSpeedMenu < 1)
            {
                arrowpositionForSpeedMenu = 5;
                menu_for_sanke_speed(arrowpositionForSpeedMenu);
            }
            else menu_for_sanke_speed(arrowpositionForSpeedMenu);
            break;
        case 's':
            arrowpositionForSpeedMenu++;
            if (arrowpositionForSpeedMenu > 5)
            {
                arrowpositionForSpeedMenu = 1;
                menu_for_sanke_speed(arrowpositionForSpeedMenu);
            }
            else menu_for_sanke_speed(arrowpositionForSpeedMenu);
            break;
            case char(32) :
                if (arrowpositionForSpeedMenu == 1) {
                    snake_speed = 0;
                    snake_score_adder = 50;
                    system("cls");
                    cout << "\t\t\tSPEED : SONIC SNAKE !!! IS SELECTED " << endl;
                    Sleep(2000);
                    ChoiceForSnakeSpeed();
                }
                else if (arrowpositionForSpeedMenu == 2) {
                    snake_speed = 40;
                    snake_score_adder = 20;
                    system("cls");
                    cout << "\t\t\tSPEED : FAST IS SELECTED " << endl;
                    Sleep(2000);
                    ChoiceForSnakeSpeed();
                }
                else if (arrowpositionForSpeedMenu == 3) {
                    snake_speed = 90;
                    snake_score_adder = 10;
                    system("cls");
                    cout << "\t\t\tSPEED : MEDIUM IS SELECTED " << endl;
                    Sleep(2000);
                    ChoiceForSnakeSpeed();
                }
                else if (arrowpositionForSpeedMenu == 4) {
                    snake_speed = 180;
                    snake_score_adder = 1;
                    system("cls");
                    cout << "\t\t\tSPEED : SLOW IS SELECTED " << endl;
                    Sleep(2000);
                    ChoiceForSnakeSpeed();
                }
                else if (arrowpositionForSpeedMenu == 5) {
                    ChoiceForGame();
                }
            default:
                break;
        }
    }

}


////////////////////////FOR GAME BONG//////////////////////
void bong()
{
    system("cls");
    //TEST_CASES
    // cBall c(0 , 0) ;
    // cout << c << endl;
    // c.randomDirection() ;
    // cout << c << endl;
    // c.Move() ;
    // cout << c << endl;
    // c.randomDirection() ;
    // c.Move() ;
    // cout << c << endl;
    // c.randomDirection() ;
    // c.Move() ;
    // cout << c << endl;

    // cPaddle p1(0 , 0) ;
    // cPaddle p2(10 , 0) ;
    // cout << p1 << endl;
    // cout << p2 << endl;
    // p1.moveUp() ;
    // p2.moveDown() ;
    // cout << p1 << endl;
    // cout << p2 << endl;

    cGameManger c(40, 20);

    //c.Draw() ;
    c.Run();

}

/////////////FOR GAME X_O////////////////////////////////

int x_o()
{
    system("cls");
Exist:
    choose1();
    if (i == 2)
        games(user);
How:
    choose2();
    if (i == 1)
    {
        getread();
        do
        {
            XOGame();
            if (i == 3)
                goto Exist;
            Display();
        } while (s == 'R');
    }
    else if (i == 2)
    {
        system("cls");
        cout << "\033[3;32mFor movement within the game use : \n";
        cout << "\033[7;32m [ W ] : \033[3;32m To move upward.\033[0m\n";
        cout << "\033[7;32m [ S ] : \033[3;32m To move down.\033[0m\n";
        cout << "\033[7;32m [ A ] : \033[3;32m To move to the left.\033[0m\n";
        cout << "\033[7;32m [ D ] : \033[3;32m To move to the right.\033[0m\n";
        cout << "\033[7;32m [ Space ] : \033[3;32m To Enter.\033[0m\n";
        system("pause");
        goto How;
    }
    goto Exist;

}

void getread()
{
    system("cls");
    char k;
    for (int i = 0; i < 2; i++)
    {
        cout << "Enter Name Player " << i + 1 << " : ";
        cin >> P[i].Playername;

        cout << "Enter char of Player " << i + 1 << " (X or O) : ";
    ll:
        k = _getch();
        k = toupper(k);
        if (k != 'X' && k != 'O')
            goto ll;
        if (i == 1)
        {
            if (k == P[0].Playerchar)
                goto ll;
        }
        cout << k << endl;
        P[i].Playerchar = k;
    }
    P[i].Playerscore = 0;
}
void choose1()
{
    system("cls");
    i = 1;
    menu1(1);
    while (1)
    {
        m = _getch();
        switch (m)
        {
        case 115:
        {
            if (i != 2)
            {
                i++;
                menu1(i);
            }
            else
            {
                i = 1;
                menu1(i);
            }
            break;
        }
        case 119:
        {
            if (i != 1)
            {
                i--;
                menu1(i);
            }
            else
            {
                i = 2;
                menu1(i);
            }
            break;
        }
        case ' ':
            break;
        }
        if ((m == ' ') && (i == 1))
            break;
        else if ((m == ' ') && (i == 2))
            break;
    }
}
void choose2()
{
    system("cls");
    i = 1;
    menu2(1);
    while (1)
    {
        m = _getch();
        switch (m)
        {
        case 115:
        {
            if (i != 2)
            {
                i++;
                menu2(i);
            }
            else
            {
                i = 1;
                menu2(i);
            }
            break;
        }
        case 119:
        {
            if (i != 1)
            {
                i--;
                menu2(i);
            }
            else
            {
                i = 2;
                menu2(i);
            }
            break;
        }
        case ' ':
            break;
        }
        if ((m == ' ') && (i == 1))
            break;
        else if ((m == ' ') && (i == 2))
            break;
    }
}
void choose3()
{
    system("cls");
    i = 1;
    hold(1);
    while (1)
    {
        m = _getch();
        switch (m)
        {
        case 115:
        {
            if (i != 3)
            {
                i++;
                hold(i);
            }
            else
            {
                i = 1;
                hold(i);
            }
            break;
        }
        case 119:
        {
            if (i != 1)
            {
                i--;
                hold(i);
            }
            else
            {
                i = 3;
                hold(i);
            }
            break;
        }
        case ' ':
            break;
        }
        if ((m == ' ') && (i == 1))
            break;
        else if ((m == ' ') && (i == 2))
            break;
        else if ((m == ' ') && (i == 3))
            break;

    }
}
void menu1(int c)
{
    system("cls");
    int i;
    const char* w[2] = { "\033[3;36mStart Game\033[0m","\033[3;36mExist\033[0m" };
    cout << setw(150) << "\033[3;5;7;35mWelcome To XO Game\033[0m" << endl;
    for (i = 0; i < maxchoose; i++)
    {
        if (i + 1 == c)
            cout << "\033[3;5;36m-->\t" << w[i] << endl;
        else
            cout << "\t" << w[i] << endl;
    }
}
void menu2(int c)
{
    system("cls");
    int i;
    const char* w[2] = { "\033[3;36mPlay with Friend","\033[3;36mHow to Play" };
    for (i = 0; i < maxchoose; i++)
    {
        if (i + 1 == c)
            cout << "\033[3;5;36m-->\t\033[0m" << w[i] << endl;
        else
            cout << "\t" << w[i] << endl;
    }
}
void hold(int c)
{
    system("cls");
    int i;
    const char* w[3] = { "\033[3;36mContinue playing\033[0m","\033[3;36mTo play with the same names\033[0m","\033[3;36mExit\033[0m" };
    for (i = 0; i < 3; i++)
    {
        if (i + 1 == c)
            cout << "\033[3;5;36m-->\t" << w[i] << endl;
        else
            cout << "\t" << w[i] << endl;
    }
}
void menu(int r, int c)
{
    system("cls");
    int i, j;
    cout << "\033[3;31mPlayer 1 :" << P[0].Playername << "\033[0m\t\t\t" << "\033[3;34mPlayer 2 :" << P[1].Playername << "\033[0m\t\t\t\033[7;33m || (Esc)\033[0m" << endl;
    cout << "\033[3;31mScore Player 1 :" << P[0].Playerscore << "\033[0m\t\t\t" << "\033[3;34mScore Player 2 :" << P[1].Playerscore << "\033[0m" << endl << endl;
    for (i = 0; i < 3; i++)
    {
        cout << "\t";
        for (j = 0; j < 3; j++)
        {
            if ((i == r) && (j == c))
                cout << "\033[3;5;32m-->\t\033[0m" << XO[i][j];
            else
                cout << "\t" << XO[i][j];
        }
        cout << endl << endl;
    }
}
void XOGame()
{
    int l = 0, k = 49;
    char f;
    if (P[0].Playerscore == P[1].Playerscore)
    {
        cout << "Who are you like to play first : ";
    RR:
        f = _getch();
        if ((f != 49) && (f != 50))
            goto RR;

    }
    else if (P[0].Playerscore > P[1].Playerscore)
        f = 49;
    else if (P[0].Playerscore < P[1].Playerscore)
        f = 50;
Again:
    system("cls");
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            XO[i][j] = k;
            k++;
        }
    }

    while (1)
    {
        menu(r, c);
        m = _getch();
        switch (m)
        {
        case 115:
        {
            if (r != 2)
            {
                r++;
                menu(r, c);
            }
            else
            {
                r = 0;
                menu(r, c);
            }
            break;
        }
        case 100:
        {
            if (c != 2)
            {
                c++;
                menu(r, c);
            }
            else
            {
                c = 0;
                menu(r, c);
            }
            break;
        }
        case 119:
        {
            if (r != 0)
            {
                r--;
                menu(r, c);
            }
            else
            {
                r = 2;
                menu(r, c);
            }
            break;
        }
        case 97:
        {
            if (c != 0)
            {
                c--;
                menu(r, c);
            }
            else
            {
                c = 2;
                menu(r, c);
            }
            break;
        }
        case ' ':
            break;
        case 27:
            break;
        }
        if ((m == ' ') && (XO[r][c] != 'X') && (XO[r][c] != 'O'))
        {
            if ((f == 49) && (l % 2 == 0))
                XO[r][c] = P[0].Playerchar;
            else if (f == 49)
                XO[r][c] = P[1].Playerchar;
            else if ((f == 50) && (l % 2 == 0))
                XO[r][c] = P[1].Playerchar;
            else if (f == 50)
                XO[r][c] = P[0].Playerchar;
            l++;
            r = 0;
            c = 0;
        }
        else if (m == 27)
        {
            choose3();
            if (i == 2)
            {
                P[0].Playerscore = 0;
                P[1].Playerscore = 0;
                k = 49;
                goto Again;
            }
            else if (i == 3)
                break;
        }
        if (l > 3)
        {
            o = checkXO();
            if (o == 'X')
            {
                if (P[0].Playerchar == 'X')
                {
                    cout << endl << "\t\033[3;31m" << P[0].Playername << " win the game.\033[0m\n";
                    system("pause");
                    P[0].Playerscore++;
                }
                else
                {
                    cout << endl << "\t\033[3;34m" << P[1].Playername << " win the game.\033[0m\n";
                    system("pause");
                    P[1].Playerscore++;
                }
                break;
            }
            else if (o == 'O')
            {
                if (P[0].Playerchar == 'O')
                {
                    cout << endl << "\t\033[3;31m" << P[0].Playername << " Win the game.\033[0m\n";
                    system("pause");
                    P[0].Playerscore++;
                }
                else
                {
                    cout << endl << "\t\033[3;34m" << P[1].Playername << " Win the game.\033[0m\n";
                    system("pause");
                    P[1].Playerscore++;
                }
                break;
            }
        }
        if (l == 8)
        {
            cout << endl << "\t" << "\033[3;35mDo not Win anyone.\033[0m\n";
            system("pause");
            break;
        }
    }
}
char checkXO()
{
    int j, i, rx, ro, cx, co, Dx = 0, Do = 0;
    for (i = 0; i < 3; i++)
    {
        rx = 0;
        ro = 0;
        cx = 0;
        co = 0;
        for (j = 0; j < 3; j++)
        {
            if (XO[i][j] == 'X')
                rx++;
            if (XO[i][j] == 'O')
                ro++;
            if (XO[j][i] == 'X')
                cx++;
            if (XO[j][i] == 'O')
                co++;
            if (i == j)
            {
                if (XO[i][j] == 'X')
                    Dx++;
                if (XO[i][j] == 'O')
                    Do++;
            }
        }
        if ((rx == 3) || (cx == 3) || (Dx == 3))
            return 'X';
        else if ((ro == 3) || (co == 3) || (Do == 3))
            return 'O';
    }
    if ((XO[2][0] == 'X') && (XO[1][1] == 'X') && (XO[0][2] == 'X'))
        return 'X';
    else if ((XO[2][0] == 'O') && (XO[1][1] == 'O') && (XO[0][2] == 'O'))
        return 'O';
    return 'n';
}
void Display()
{
    system("cls");
    for (int i = 0; i < 3; i++)
    {
        cout << "\t\033[3;4;32m";
        for (int j = 0; j < 3; j++)
        {
            cout << '\t' << XO[i][j];
        }
        cout << endl << endl;
    }
    cout << endl << "\033[0m" << setw(50);
    cout << "\033[3;4;32mIf you went play agein click on R or r : \033[0m";
    cin >> s;
    s = toupper(s);
}
