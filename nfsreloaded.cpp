/***************************************************************************
***************************** All Header Files *****************************
***************************************************************************/

#include <conio.h>    //'gotoxy','getch;,'kbhit',
#include <ctype.h>    //'toupper'
#include <dos.h>      //'delay','sound'
#include <fstream.h>  // file operations,'cout'-iostream.h also included
#include <graphics.h> //'initgraph',various designs and colors
#include <stdio.h>    //'gets','rename' file,'remove' file
#include <stdlib.h>   // random functions
#include <string.h>   //'strcpy'

/***************************************************************************
***************************** The Main Program *****************************
***************************************************************************/
struct data {
    char name[21];
    int score;
    int level;
};

class game {
private:
    data currentplayer;
    int maxx, maxy;
    int c1, c2, c3, c4;         // the positions of car in game
    int mx, my1, my2, my3, my4; // coordinates of menu positions
    int rxb, rxe, ry1b, ry2b, ry3b, ry4b,
        ry1e, ry2e, ry3e, ry4e; // coordinates of rectangles in game screen
    int currentj;
    int escp, pausep;

public:
    game();
    void menu();
    int moveselection();
    void play();
    void highscores();
    void help();
    void checkscore();
    void car(int, int, int);
    void music(int x);
    void inttochar(int&, int, int, int, char);
};

game::game()
{
    maxx = getmaxx();
    maxy = getmaxy();

    c1 = (maxx / 2) - 75;
    c2 = (maxx / 2) - 25;
    c3 = (maxx / 2) + 25;
    c4 = (maxx / 2) + 75;

    mx = 200;
    my1 = 170;
    my2 = 220;
    my3 = 270;
    my4 = 320;

    rxb = c4 + 20;
    rxe = maxx - 20;
    ry1b = (maxy / 5) - 25;
    ry2b = (maxy / 5 * 2) - 25;
    ry3b = (maxy / 5 * 3) - 25;
    ry4b = (maxy / 5 * 4) - 25;
    ry1e = (maxy / 5) + 25;
    ry2e = (maxy / 5 * 2) + 25;
    ry3e = (maxy / 5 * 3) + 25;
    ry4e = (maxy / 5 * 4) + 25;

    currentj = my1;

    escp = maxy / 2 - 15;
    pausep = maxy / 2 + 15;

    int status = 0;

    ifstream file("scores.nfs", ios::in | ios::binary | ios::nocreate);
    if (file.bad())
        status = 1;
    file.close();

    if (status == 1) {
        status = 0;
        data n[10];

        strcpy(n[0].name, "Siddhartha Sahu");
        n[0].score = 990;
        n[0].level = 7;
        strcpy(n[1].name, "Samir Pramanik");
        n[1].score = 920;
        n[1].level = 7;
        strcpy(n[2].name, "Aaditya Anand");
        n[2].score = 890;
        n[2].level = 6;
        strcpy(n[3].name, "Jeet Harshal");
        n[3].score = 850;
        n[3].level = 6;
        strcpy(n[4].name, "Vikas Suman");
        n[4].score = 840;
        n[4].level = 6;
        strcpy(n[5].name, "Ankit Jain");
        n[5].score = 800;
        n[5].level = 6;
        strcpy(n[6].name, "Gourav Kumar");
        n[6].score = 780;
        n[6].level = 6;
        strcpy(n[7].name, "Rishi Chauhan");
        n[7].score = 740;
        n[7].level = 5;
        strcpy(n[8].name, "Khuswant Pandey");
        n[8].score = 60;
        n[8].level = 1;
        strcpy(n[9].name, "Pankaj Tripathy");
        n[9].score = 50;
        n[9].level = 1;

        ofstream fi("scores.nfs", ios::out | ios::binary);
        for (int i = 0; i < 10; i++)
            fi.write((char*)&n[i], sizeof(n[i]));
        fi.close();
    }
}

void game::menu()
{
    int ret = 2;
    do {
        if (ret == 2) {
            cleardevice();
            setcolor(RED);
            settextstyle(4, 0, 6);
            outtextxy(45, 50, "Need for Speed Reloaded");
            outtextxy(48, 70, "----------------");
            setlinestyle(0, 0, 3);
            rectangle(0, 0, maxx, maxy);

            settextstyle(3, 0, 4);
            setcolor(YELLOW);
            outtextxy(mx, my1, "1. New Game");
            outtextxy(mx, my2, "2. Help");
            outtextxy(mx, my3, "3. High Scores");
            outtextxy(mx, my4, "4. Exit");
            setcolor(RED);
            switch (currentj) {
            case 170:
                outtextxy(mx, my1, "1. New Game");
                break;
            case 220:
                outtextxy(mx, my2, "2. Help");
                break;
            case 270:
                outtextxy(mx, my3, "3. High Scores");
                break;
            case 320:
                outtextxy(mx, my4, "4. Exit");
                break;
            }
        }
        ret = moveselection();
    } while (ret != 3);
}

int game::moveselection()
{
    int ch = 0;
    ch = getch();
    music(3);
    switch (ch) {
    case 80: // down arrow key
        if (currentj == my1) {
            currentj = my2;
            setcolor(RED);
            outtextxy(mx, my2, "2. Help");
            setcolor(YELLOW);
            outtextxy(mx, my1, "1. New Game");
        } else if (currentj == my2) {
            currentj = my3;
            setcolor(RED);
            outtextxy(mx, my3, "3. High Scores");
            setcolor(YELLOW);
            outtextxy(mx, my2, "2. Help");
        } else if (currentj == my3) {
            currentj = my4;
            setcolor(RED);
            outtextxy(mx, my4, "4. Exit");
            setcolor(YELLOW);
            outtextxy(mx, my3, "3. High Scores");
        } else if (currentj == my4) {
            currentj = my1;
            setcolor(RED);
            outtextxy(mx, my1, "1. New Game");
            setcolor(YELLOW);
            outtextxy(mx, my4, "4. Exit");
        }
        break;

    case 72: // up arrow key
        if (currentj == my1) {
            currentj = my4;
            setcolor(RED);
            outtextxy(mx, my4, "4. Exit");
            setcolor(YELLOW);
            outtextxy(mx, my1, "1. New Game");
        } else if (currentj == my2) {
            currentj = my1;
            setcolor(RED);
            outtextxy(mx, my1, "1. New Game");
            setcolor(YELLOW);
            outtextxy(mx, my2, "2. Help");
        } else if (currentj == my3) {
            currentj = my2;
            setcolor(RED);
            outtextxy(mx, my2, "2. Help");
            setcolor(YELLOW);
            outtextxy(mx, my3, "3. High Scores");
        } else if (currentj == my4) {
            currentj = my3;
            setcolor(RED);
            outtextxy(mx, my3, "3. High Scores");
            setcolor(YELLOW);
            outtextxy(mx, my4, "4. Exit");
        }
        break;

    case 13: // enter key
        if (currentj == my1) {
            play();
        } else if (currentj == my2) {
            help();
        } else if (currentj == my3) {
            highscores();
        } else if (currentj == my4)
            ch = 27;
        break;

    case 49: // number 1 key
        play();
        break;

    case 50: // number 2 key
        help();
        break;

    case 51: // number 3 key
        highscores();
        break;

    case 52: // number 4 key
        break;

    case 27: // escape key
        break;
    default:
        break;
    }

    if (ch == 72 || ch == 80)
        return 1;
    else if (ch == 13 || ch == 49 || ch == 50 || ch == 51)
        return 2;
    else if (ch == 27 || ch == 52)
        return 3;
    else
        return 0;
}

void game::play()
{
    cleardevice();
    settextstyle(1, 0, 3);
    setcolor(RED);
    outtextxy(200, 130, "Enter your Name");
    gotoxy(30, 12);
    gets(currentplayer.name);
    currentplayer.name[0] = toupper(currentplayer.name[0]);
    delay(100);
    cleardevice();
    settextstyle(1, 0, 4);
    setcolor(RED);
    outtextxy(100, 50, "Hello ");
    outtextxy(190, 50, currentplayer.name);
    settextstyle(1, 0, 3);
    setcolor(BLUE);
    outtextxy(100, 120, "Welcome to");
    settextstyle(1, 0, 4);
    setcolor(GREEN);
    outtextxy(100, 150, "NEED FOR SPEED RELOADED !!!");
    setcolor(YELLOW);
    settextstyle(1, 0, 2);
    outtextxy(maxx / 2 - 90, maxy - 80, "Loading.....");
    rectangle(maxx / 2 - 90, maxy - 30, maxx / 2 + 100, maxy - 20);
    for (int i = 0; i <= 75; i++) {
        setcolor(LIGHTBLUE);
        setfillstyle(1, LIGHTBLUE);
        bar(getmaxx() / 2 - 88, getmaxy() - 28, getmaxx() / 2 - 52 + i * 2,
            getmaxy() - 22);
        delay(15);
    }
    setcolor(0);
    outtextxy(maxx / 2 - 90, maxy - 80, "Loading.....");
    rectangle(maxx / 2 - 90, maxy - 30, maxx / 2 + 100, maxy - 20);
    for (i = 0; i <= 75; i++) {
        setfillstyle(1, 0);
        bar(maxx / 2 - 88, maxy - 28, maxx / 2 - 52 + i * 2, maxy - 22);
    }
    setcolor(YELLOW);
    outtextxy(maxx / 2 - 150, maxy - 80, "Press any key to continue...");
    getch();

    cleardevice();
    setbkcolor(3);
    setcolor(1);
    rectangle(0, 0, maxx, maxy);
    setlinestyle(0, 0, 3);
    setcolor(4);
    rectangle(c1 - 3, 0, c4 + 3, maxy);
    setcolor(0);
    line(c1 - 1, 0, c4 + 1, 0);
    line(c1 - 1, maxy, c4 + 1, maxy);

    setcolor(12);
    setlinestyle(0, 0, 0);
    rectangle(rxb, ry1b, rxe, ry1e);
    rectangle(rxb, ry2b, rxe, ry2e);
    rectangle(rxb, ry3b, rxe, ry3e);
    rectangle(rxb, ry4b, rxe, ry4e);
    settextstyle(10, 0, 1);
    setcolor(1);
    outtextxy(rxb + 30, ry1b + 5, currentplayer.name);
    settextstyle(1, 0, 4);
    setcolor(14);
    outtextxy(rxb + 15, ry2b + 5, "Level - ");
    outtextxy(rxb + 15, ry3b + 5, "Lives - ");
    outtextxy(rxb + 15, ry4b + 5, "Score - ");

    settextstyle(0, 0, 2);
    setcolor(5);
    outtextxy(20, 425, "Developed By");
    outtextxy(19, 438, "------------");
    settextstyle(3, 0, 1);
    setcolor(1);
    outtextxy(50, 443, "Siddhartha Sahu");

    setcolor(4);
    settextstyle(7, 0, 1);
    outtextxy(10, escp, "Press <Esc> to Exit");
    outtextxy(10, pausep, "Press < P >  to Pause");

    setcolor(BLUE);
    settextstyle(1, 0, 7);
    music(2);
    outtextxy(80, 80, "3");
    delay(1100);
    setcolor(0);
    outtextxy(80, 80, "3");
    setcolor(BLUE);
    music(2);
    outtextxy(80, 80, "2");
    delay(1100);
    setcolor(0);
    outtextxy(80, 80, "2");
    setcolor(BLUE);
    music(2);
    outtextxy(80, 80, "1");
    delay(1100);
    setcolor(0);
    outtextxy(80, 80, "1");
    setcolor(BLUE);
    outtextxy(80, 80, "GO");
    music(1);
    setcolor(0);
    outtextxy(80, 80, "GO");

    int life = 3;
    currentplayer.level = 1;
    currentplayer.score = 0;
    int x = c2, y = maxy - 81;
    int complete = 0;
    inttochar(currentplayer.level, rxb + 150, ry2b + 5, 0, 'n');
    randomize();
    do {
        for (int i = 1; i <= 15 && life > 0 && complete == 0; i++) {
            int accident = 0;

            inttochar(life, rxb + 150, ry3b + 5, 0, 'n');
            inttochar(currentplayer.score, rxb + 135, ry4b + 5, 0, 'n');

            int y1 = 0;
            int x1 = c1 + (random(3) * 50);
            int y2 = 0;
            int x2 = c1 + (random(3) * 50);

            do {
                car(x1, y1, 0);
                car(x2, y2, 0);
                y1++;
                y2++;
                gotoxy(2, 3);
                car(x1, y1, BLUE);
                car(x2, y2, BLUE);
                car(x, y, BLUE);
                delay(7 - currentplayer.level);
                if (kbhit()) {
                    switch (getch()) {
                    case 27:
                        setcolor(BLUE);
                        settextstyle(2, 0, 5);
                        outtextxy(30, 80, "Processing your Score...");
                        complete = 1;
                        delay(2000);
                        setbkcolor(0);
                        cleardevice();
                        checkscore();
                        highscores();
                        break;
                    case 75:
                        music(3);
                        if (x > c1) {
                            car(x, y, 0);
                            x = x - 50;
                            car(x, y, BLUE);
                        }
                        break;
                    case 77:
                        music(3);
                        if (x < c3) {
                            car(x, y, 0);
                            x = x + 50;
                            car(x, y, BLUE);
                        }
                        break;
                    case 112:
                        music(3);
                        setcolor(0);
                        settextstyle(7, 0, 1);
                        outtextxy(10, pausep, "Press < P >  to Pause");
                        setcolor(4);
                        outtextxy(10, pausep, "Press any key to Play");
                        getch();
                        setcolor(0);
                        outtextxy(10, pausep, "Press any key to Play");
                        setcolor(4);
                        outtextxy(10, pausep, "Press < P >  to Pause");
                        break;
                    default:
                        break;
                    }
                }
                if (x == x1 || x == x2) {
                    if ((((y + 80) - (y1 - 20)) > 1
                            && ((y + 80) - (y1 - 20)) < 199)
                        || (((y + 80) - (y2 - 20)) > 1
                               && ((y + 80) - (y1 - 20)) < 199)) {
                        accident = 1;
                        complete = 1;
                    }
                }
            } while (y1 < maxy + 51 && life > 0 && complete == 0);
            if (accident == 1) {
                accident = 0;
                complete = 0;
                inttochar(life, rxb + 150, ry3b + 5, 1, '-');
                if (life != 0) {
                    setcolor(5);
                    settextstyle(1, 0, 1);
                    outtextxy(6, 55, "you have lost 1 life");
                    delay(2000);
                    car(x1, y1, 0);
                    car(x2, y2, 0);
                    car(x, y, BLUE);
                    setcolor(0);
                    outtextxy(6, 55, "you have lost 1 life");
                } else if (life == 0) {
                    setcolor(5);
                    settextstyle(7, 0, 1);
                    outtextxy(6, 55, "GAME OVER");
                    settextstyle(2, 0, 5);
                    outtextxy(30, 80, "Processing your Score...");
                    delay(2000);
                    setbkcolor(0);
                    cleardevice();
                    checkscore();
                    highscores();
                    complete = 1;
                }
            } else if (complete == 0) {
                inttochar(currentplayer.score, rxb + 135, ry4b + 5, 10, '+');
            }
        }
        if (currentplayer.level < 7 && life > 0 && complete == 0) {
            setcolor(5);
            settextstyle(1, 0, 1);
            outtextxy(6, 55, "Next Level...");
            delay(2000);
            setcolor(0);
            outtextxy(6, 55, "Next Level...");
        }
        inttochar(currentplayer.level, rxb + 150, ry2b + 5, 1, '+');
    } while (currentplayer.level <= 7 && life > 0 && complete == 0);
    if (currentplayer.level == 8)
        inttochar(currentplayer.level, maxx + 50, maxy + 50, 1, '-');
    setbkcolor(0);
    if (currentplayer.level == 7 && life > 0) {
        cleardevice();
        checkscore();
        setbkcolor(BLUE);
        setcolor(GREEN);
        setlinestyle(0, 0, 3);
        rectangle(0, 0, getmaxx(), getmaxy());
        setcolor(RED);
        settextstyle(4, 0, 5);
        outtextxy(50, 55, "Congratulations!     ");
        outtextxy(50, 100, "you have completed the game!!!   ");
        setcolor(GREEN);
        settextstyle(6, 0, 4);
        outtextxy(55, 200, "Press <1> to see your score...");
        outtextxy(55, 230, "Press <Esc.> to exit to main menu...");
        int ch;
        do {
            ch = getch();
            if (ch == 49) {
                ch = 27;
                setbkcolor(0);
                highscores();
            }
        } while (ch != 27);
    }
    setbkcolor(0);
}

void game::highscores()
{
    cleardevice();
    setcolor(RED);
    setlinestyle(0, 0, 5);
    rectangle(0, 0, maxx, maxy);

    settextstyle(10, 0, 4);
    setcolor(RED);
    outtextxy(15, 5, "Need for Speed Reloaded");
    outtextxy(13, 40, "-------------------");
    setcolor(GREEN);
    settextstyle(2, 0, 8);
    outtextxy(50, 85, "Name");
    outtextxy(50, 100, "----");
    outtextxy(390, 85, "Score");
    outtextxy(390, 100, "-----");
    outtextxy(530, 85, "Level");
    outtextxy(530, 100, "-----");
    setcolor(WHITE);
    ifstream file("scores.nfs", ios::in | ios::binary);
    data x;
    settextstyle(0, 0, 2);
    for (int i = 0; i < 10; i++) {
        file.read((char*)&x, sizeof(x));
        outtextxy(50, 125 + (i * 32), x.name);
        gotoxy(53, 9 + (i * 2));
        cout << x.score;
        gotoxy(72, 9 + (i * 2));
        cout << x.level;
    }
    setcolor(YELLOW);
    outtextxy(50, maxy - 25, "Press <Esc.> to exit...");
    int ch;
    do {
        ch = getch();
    } while (ch != 27);
}

void game::help()
{
    cleardevice();
    settextstyle(1, 0, 5);
    setcolor(RED);
    settextstyle(1, 0, 6);
    outtextxy(15, 10, "Need for Speed Reloaded");
    setcolor(LIGHTGREEN);
    rectangle(50, 80, 600, 460);
    setcolor(LIGHTCYAN);
    rectangle(60, 90, 590, 450);
    setcolor(WHITE);
    settextstyle(1, 0, 2);
    outtextxy(80, 100, "      THIS GAME IS A DOS BASED GAME. ");
    outtextxy(80, 130, "  IN THIS GAME YOU HAVE TO SAVE YOUR CAR ");
    outtextxy(80, 160, " FROM THE DESCENDING CARS.YOU HAVE THREE");
    outtextxy(80, 190, "  LIVES.WHEN YOU SAVE YOUR CAR FROM THE ");
    outtextxy(80, 220, "OPPOSITE CARS,YOU GET 10 POINTS.WHEN YOU ");
    outtextxy(80, 250, " MAKE MAXIMUM POINTS,ENTER YOUR NAME.");
    setcolor(CYAN);
    outtextxy(80, 290, "   * NOTE:-YOU CAN'T SAVE THE GAME *");
    setcolor(WHITE);
    settextstyle(1, 0, 6);
    outtextxy(95, 310, " KEY CONTROLS: ");
    setcolor(CYAN);
    settextstyle(1, 0, 2);
    outtextxy(100, 370, "      ->KEY==RIGHT MOVE");
    outtextxy(100, 400, "      <-KEY==LEFT MOVE");
    getch();
}

void game::checkscore()
{
    data x;
    ifstream fi("scores.nfs", ios::in | ios::binary);
    ofstream fo("temp", ios::out | ios::binary);
    int flag = 0;

    while (!fi.eof()) {
        fi.read((char*)&x, sizeof(x));
        if (currentplayer.score >= x.score) {
            fo.write((char*)&currentplayer, sizeof(currentplayer));
            fo.write((char*)&x, sizeof(x));
            flag = 1;
            break;
        } else
            fo.write((char*)&x, sizeof(x));
    }
    if (flag == 0)
        fo.write((char*)&currentplayer, sizeof(currentplayer));
    else if (!fi.eof()) {
        while (!fi.eof()) {
            fi.read((char*)&x, sizeof(x));
            fo.write((char*)&x, sizeof(x));
        }
    }
    fi.close();
    fo.close();
    remove("scores.nfs");
    rename("temp", "scores.nfs");
}

void game::car(int x, int y, int i)
{
    setcolor(i);
    rectangle(x, y, x + 50, y + 80);
    rectangle(x, y - 20, x + 50, y + 60);
    line(x, y - 10, x + 50, y - 10);
}

void game::music(int x)
{
    float octave[7] = { 130.81, 146.83, 164.81, 174.61, 196, 220, 246.94 };
    int n, i;
    switch (x) {
    case 1:
        for (int w = 1; w < 22; w++) {
            n = random(7);
            sound(octave[n] * 4);
            delay(100);
        }
        break;
    case 2:
        for (i = 6; i >= 0; i--) {
            sound(octave[6] * 2);
            delay(50);
        }
        break;
    case 3:
        sound(octave[6] * 2);
        delay(10);
    }
    nosound();
}

void game::inttochar(int& num, int x, int y, int change, char ch)
{
    int n = num;
    settextstyle(1, 0, 4);
    char st[6];
    int i = 0;
    do {
        int t = n % 10;
        st[i] = '0' + t;
        n /= 10;
        i++;
    } while (n != 0);
    for (int j = 0; j < i / 2; j++) {
        char temp = st[j];
        st[j] = st[i - 1 - j];
        st[i - 1 - j] = temp;
    }
    st[i] = '\0';
    setcolor(0);
    outtextxy(x, y, st);
    switch (ch) {
    case '+':
        num += change;
        break;
    case '-':
        num -= change;
        break;
    case 'n':;
    }
    i = 0;
    n = num;
    do {
        int t = n % 10;
        st[i] = '0' + t;
        n /= 10;
        i++;
    } while (n != 0);
    for (j = 0; j < i / 2; j++) {
        int temp = st[j];
        st[j] = st[i - 1 - j];
        st[i - 1 - j] = temp;
    }
    st[i] = '\0';
    setcolor(RED);
    settextstyle(1, 0, 4);
    outtextxy(x, y, st);
}

void main()
{
    int gm, gd = DETECT;
    initgraph(&gd, &gm, "\\tc\\bgi");
    game ob;
    ob.menu();
}
