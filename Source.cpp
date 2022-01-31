#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

using namespace sf;

int unu = 1;
int N = 20, M = 9;
int size1 = 64;
int w = size1 * N;
int h = size1 * M;

int dir, xp, yp, gameover, okmeniu = 0, okes, xr, yr;
int ma[100][100], x = 2, y = 2, a, b, l = 1, d, lv = 1, okm, alg, okin = 0;
char c;
struct
{
    int x1, x2;
}v[100];

void meniu();
void meniumape();

void punct()
{
    int ok = 0;
    while (!ok)
    {
        ok = 1;
        a = rand() % 9 + 1;
        b = rand() % 19 + 1;
        if (ma[b][a] == 4)ok = 0;
        for (int j = 1; j <= l && ok; ++j)
        {
            if (b == v[j].x1 && a == v[j].x2)ok = 0;
        }
    }
    xp = b;
    yp = a;
}
void mananca()
{
    l++;
    v[l].x1 = x;
    v[l].x2 = y;
    ma[x][y] = 1;
    punct();
}
void retrage()
{
    for (int i = 1; i < l; ++i)v[i].x1 = v[i + 1].x1, v[i].x2 = v[i + 1].x2;
    v[l].x1 = x;
    v[l].x2 = y;
    ma[x][y] = 1;
}
void delayy(int milli_seconds)
{
    clock_t start_time = clock();
    while (clock() < start_time + milli_seconds);
}
void joc()
{

    if (dir == 1)x--; if (dir == 2)y++; if (dir == 3)x++; if (dir == 4)y--;
    if (ma[x][y] == 4 || ma[x][y] == 1)
    {
        gameover = 1;
        if (v[1].x1 == x && v[1].x2 == y)gameover = 0;
    }
    if (!gameover)
    {
        if (y > 9 || x < 1 || x>20 || y < 1)
        {
            if (x > 20)x = 1;
            if (y > 9)y = 1;
            if (x < 1)x = 20;
            if (y < 1)y = 9;
        }
        ma[v[1].x1][v[1].x2] = 0;
        if (x == xp && y == yp)mananca();
        else if (!ma[x][y])retrage();
    }

}
void GenerareNivel()
{
    for (int i = 0; i <= 200; ++i)v[i].x1 = v[i].x2 = 0;
    for (int i = 0; i <= 22; ++i)
        for (int j = 0; j <= 22; ++j)ma[i][j] = 0;
    if (lv == 2)
    {
        for (int i = 1; i <= 20; ++i)ma[i][9] = ma[i][1] = 4;
        for (int j = 1; j <= 9; ++j)ma[20][j] = ma[1][j] = 4;
    }
    if (lv == 3)
    {
        ma[1][1] = ma[2][1] = ma[1][2] = 4;
        ma[20][9] = ma[19][9] = ma[20][8] = 4;
        ma[1][9] = ma[2][9] = ma[1][8] = 4;
        ma[20][1] = ma[20][2] = ma[19][1] = 4;
        for (int i = 1; i <= 4; ++i)
            ma[8 + i][4] = ma[8 + i][6] = 4;
    }
    if (lv == 4)
    {
        for (int i = 1; i <= 10; ++i)ma[i][7] = 4;
        for (int i = 1; i <= 5; ++i)ma[9][i] = 4;
        for (int i = 12; i <= 20; ++i)ma[i][3] = 4;
        for (int i = 5; i <= 9; ++i)ma[13][i] = 4;
    }
    if (lv == 5)
    {
        for (int i = 1; i <= 9; ++i)ma[20][i] = ma[1][i] = 4;
        for (int j = 1; j <= 20; ++j)ma[j][9] = ma[j][1] = 4;
        ma[1][5] = ma[20][5] = 0;
        for (int i = 3; i <= 7; ++i)ma[8][i] = ma[14][i] = 4;
    }
    if (lv == 6)
    {
        ma[1][1] = ma[2][1] = ma[1][2] = ma[2][1] = 4;
        for (int i = 1; i <= 20; ++i)ma[i][4] = 4;
        ma[9][4] = ma[10][4] = 0;
        for (int i = 5; i <= 17; ++i)ma[i][1] = 4;
        for (int i = 1; i <= 4; ++i)ma[8][i] = 4;
        for (int i = 1; i <= 20; ++i)ma[i][7] = 4;
        ma[11][8] = ma[11][9] = 4;
    }
    if (lv == 7)
    {
        for (int i = 1; i <= 20; ++i)ma[i][5] = 4;
        for (int i = 1; i <= 9; ++i)ma[11][i] = 4;
    }
    if (lv == 8)
    {
        for (int i = 1; i <= 20; ++i)ma[i][5] = 4;
        for (int i = 5; i <= 9; ++i)ma[7][i] = ma[14][i] = 4;
    }
}

int main()
{
    punct();

    ma[2][2] = 1; l = 1;
    v[1].x1 = 2; x = 2;
    v[1].x2 = 2; y = 2;

    RenderWindow window(VideoMode(w, h), "Snake");

    Texture t1, t2, t3, t4, t5, t6, t7, t8, t9, t10;
    t2.loadFromFile("images/greenmare.png");
    t1.loadFromFile("images/iarba.png");
    t3.loadFromFile("images/cobble.png");
    t4.loadFromFile("images/mar.png");
    t5.loadFromFile("images/mainmenu.png");
    t6.loadFromFile("images/arrow.png");
    t7.loadFromFile("images/meniumape.png");
    t8.loadFromFile("images/gameoverr.jpg");
    t9.loadFromFile("images/capdesarpe.png");
    t10.loadFromFile("images/despre.png");


    Sprite sprite5(t5);
    Sprite sprite1(t1);
    Sprite sprite2(t2);
    Sprite sprite3(t3);
    Sprite sprite4(t4);
    Sprite sprite6(t6);
    Sprite sprite7(t7);
    Sprite sprite8(t8);
    Sprite sprite9(t9);
    Sprite sprite10(t10);

    Music music;
    music.openFromFile("audio/snakemusic.ogg");
    music.setVolume(50);
    music.play();
    music.setLoop(true);
    Clock clock;
    float timer = 0, delay = 0.2;

    Font font;
    font.loadFromFile("Fonts/gatty1.ttf");
    Text text;
    text.setFont(font);
    text.setFillColor(Color::Black);
    text.setCharacterSize(24);
    text.setPosition(20, 90);
    text.setString("");

    while (window.isOpen())
    {
        if (okes == 0)
        {
            okmeniu = 0;
            // MENIU MENIU MENIU
            delayy(200);
            while (1)
            {
                {
                    ////// desen  ///////
                    window.clear();

                    sprite5.setPosition(0, 0);  window.draw(sprite5);

                    if (okmeniu == 0)
                        sprite6.setPosition(size1 * 1, size1 * 5 - 30), window.draw(sprite6);
                    else if (okmeniu == 1)
                        sprite6.setPosition(size1 * 1, size1 * 7 - 32), window.draw(sprite6);
                    else if (okmeniu == 2)
                        sprite6.setPosition(size1 * 8, size1 * 7 - 32), window.draw(sprite6);
                    window.display();

                    Event ev;
                    while (window.pollEvent(ev))
                    {
                        if (ev.type == Event::Closed)
                            window.close();
                    }

                    if (Keyboard::isKeyPressed(Keyboard::Up)) dir = 4;
                    if (Keyboard::isKeyPressed(Keyboard::Down)) dir = 2;
                    if (Keyboard::isKeyPressed(Keyboard::Return)) dir = 5;
                    if (dir == 2)
                    {
                        okmeniu++, dir = -1, delayy(200);
                    }
                    if (dir == 4)
                    {
                        okmeniu--, dir = -1, delayy(200);
                    }
                    if (okmeniu < 0)okmeniu = 2;
                    if (okmeniu > 2)okmeniu = 0;
                    if (dir == 5)
                    {
                        delayy(200);
                        dir = -1;
                        if (okmeniu == 1)return 0;
                        else if (okmeniu == 0) { okes = 1; break; }
                        else if (okmeniu == 2) { okes = 3; break; }

                    }

                }
            }

        }
        if (okes == 1)
        {
            // MENIU MAPE
            okmeniu = 0;
            delayy(200);
            while (1)
            {
                window.clear();

                sprite7.setPosition(0, 0);  window.draw(sprite7);
                if (okmeniu == 0)sprite6.setPosition(30, 0), window.draw(sprite6);
                if (okmeniu == 1)sprite6.setPosition(40, 50), window.draw(sprite6);
                if (okmeniu == 2)sprite6.setPosition(45, 110), window.draw(sprite6);
                if (okmeniu == 3)sprite6.setPosition(35, 160), window.draw(sprite6);
                if (okmeniu == 4)sprite6.setPosition(40, 220), window.draw(sprite6);
                if (okmeniu == 5)sprite6.setPosition(65, 285), window.draw(sprite6);
                if (okmeniu == 6)sprite6.setPosition(30, 340), window.draw(sprite6);
                if (okmeniu == 7)sprite6.setPosition(100, 410), window.draw(sprite6);
                if (okmeniu == 8)sprite6.setPosition(60, 470), window.draw(sprite6);

                window.display();
                Event eve;
                while (window.pollEvent(eve))
                {
                    if (eve.type == Event::Closed)
                        window.close();
                }

                if (Keyboard::isKeyPressed(Keyboard::Up)) dir = 4;
                if (Keyboard::isKeyPressed(Keyboard::Down)) dir = 2;
                if (Keyboard::isKeyPressed(Keyboard::Return)) dir = 5;
                if (dir == 4 && okmeniu == 0)okmeniu = 8, dir = -1, delayy(200);
                else if (dir == 4)okmeniu--, dir = -1, delayy(200);
                if (dir == 2 && okmeniu == 8)okmeniu = 0, dir = -1, delayy(200);
                else if (dir == 2)okmeniu++, dir = -1, delayy(200);
                if (dir == 5)
                {
                    delayy(200);
                    dir = -1;
                    if (okmeniu == 0) { okes = 0; break; }
                    else
                    {
                        lv = okmeniu;
                        GenerareNivel();
                        okes = 2;
                        break;
                    }
                }
            }
        }
        gameover = 0;
        if (okes == 2)
        {
            // joc
            float time = clock.getElapsedTime().asSeconds();
            clock.restart();
            timer += time;

            Event e;
            while (window.pollEvent(e))
            {
                if (e.type == Event::Closed)
                    window.close();
            }

            if (Keyboard::isKeyPressed(Keyboard::Left)) dir = 1;
            if (Keyboard::isKeyPressed(Keyboard::Right)) dir = 3;
            if (Keyboard::isKeyPressed(Keyboard::Up)) dir = 4;
            if (Keyboard::isKeyPressed(Keyboard::Down)) dir = 2;

            if (timer > delay) { timer = 0; joc(); }

            ////// desen  ///////
            window.clear();

            for (int i = 0; i < N; i++)
                for (int j = 0; j < M; j++)
                {
                    if (ma[i + 1][j + 1] == 4)
                        sprite3.setPosition(i * size1, j * size1), window.draw(sprite3);
                    else
                        sprite1.setPosition(i * size1, j * size1), window.draw(sprite1);
                }

            for (int i = 1; i < l; i++)
            {
                sprite2.setPosition((v[i].x1 - 1) * size1, (v[i].x2 - 1) * size1);  window.draw(sprite2);
            }

            //Afisare cap
            sprite9.setRotation(0); xr = yr = 0;
            if (dir == 2)sprite9.setRotation(90), yr = +1;
            if (dir == 1)sprite9.setRotation(180), xr = yr = +1;
            if (dir == 4)sprite9.setRotation(270), xr = +1;

            sprite9.setPosition((v[l].x1 - 1 + yr) * size1, (v[l].x2 - 1 + xr) * size1);  window.draw(sprite9);


            //Afisare mar
            sprite4.setPosition((xp - 1) * size1, (yp - 1) * size1);  window.draw(sprite4);

            window.display();
            if (gameover == 1)
            {

                while (1)
                {
                    window.clear();
                    if (Keyboard::isKeyPressed(Keyboard::Return)) dir = 5;
                    sprite8.setPosition(0, 0); window.draw(sprite8);
                    if (dir == 5) { dir = -1; break; }
                    window.display();

                }
                ma[2][2] = 1; l = 1;
                v[1].x1 = 2; x = 2;
                v[1].x2 = 2; y = 2;
                okes = 1;
            }
        }
        if (okes == 3)
        {
            while (1)
            {
                ////// desen  ///////
                window.clear();

                sprite10.setPosition(0, 0);  window.draw(sprite10);
                text.setPosition(20, 90);
                text.setString("Atestat Snake de Codreanu Catalin \n");
                window.draw(text);
                text.setPosition(20, 120);
                text.setString("Clasa : 12A Colegiul national 'Tudor Vladimirescu' Profesor indrumator : Nodea Eugen \n");
                window.draw(text);
                text.setPosition(20, 150);
                text.setString("Scurta istorie a jocului Snake : \n");
                window.draw(text);
                text.setPosition(20, 180);
                text.setString("Snake a luat nastere in 1976 in salile de jocuri de tip arcade. Jocul presupune un sarpe ce  \n");
                window.draw(text);
                text.setPosition(20, 210);
                text.setString("este controlat de jucator pentru a cumula puncte (de obicei sub forma de fructe) in urma  \n");
                window.draw(text);
                text.setPosition(20, 240);
                text.setString("carora lungimea sarpelui creste. Dupa aparitia jocului au aparut sute de variatii sub forma \n");
                window.draw(text);
                text.setPosition(20, 270);
                text.setString("de sarpe sau vierme pentru mai multe platforme. Dupa ce nokia a preluat ideea de joc si a \n");
                window.draw(text);
                text.setPosition(20, 300);
                text.setString("introdus-o ca o aplicatie predefinita pe nokia 3310 jocul a cunoscut o audienta mai larga. \n");
                window.draw(text);
                text.setPosition(20, 330);
                text.setString("In comparatie in prezent sunt peste 300 de variatii ale jocului doar pe IOS.  \n");
                window.draw(text);
                text.setPosition(20, 360);
                text.setString("Acest joc este inspirat din jocul snake de pe nokia, nivelurile si marimea hartilor fiind \n");
                window.draw(text);
                text.setPosition(20, 390);
                text.setString("aceleasi ca in jocul original, iar muzica este din snake 3, gasit tot pe telefoanele nokia. \n");
                window.draw(text);
                text.setPosition(20, 420);
                text.setString("Scopul jocului este de a acumula cat mai multe puncte. Jucatorul alege directia sarpelui \n");
                window.draw(text);
                text.setPosition(20, 450);
                text.setString("din sageti si trebuie sa ajunga cat mai eficient la mere. Finalul jocului este determinat \n");
                window.draw(text);
                text.setPosition(20, 480);
                text.setString("de mancarea proprii cozi sau prin lovirea unui obstacol. \n");
                window.draw(text);

                window.display();

                Event evente;
                while (window.pollEvent(evente))
                {
                    if (evente.type == Event::Closed)
                        window.close();
                }

                if (Keyboard::isKeyPressed(Keyboard::Return)) dir = 5;

                if (dir == 5)
                {
                    delayy(200);
                    dir = -1;
                    okes = 0;
                    break;

                }
            }
        }
    }
    return 0;
}
