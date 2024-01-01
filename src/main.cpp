#include <iostream>
#include <ncurses.h>
#include <cmath>
#include <algorithm>
#include <unistd.h>

using namespace std;

#define ANGLE_STEP 0.1
#define TRAIL_STEP 0.02

#define TIME_STEP 100
int main()
{
    float TRAIL = 120 * M_PI / 180.0;

    initscr();

    start_color();

    // Defintion for non-alphanumeric keys
    // keypad(stdscr, TRUE);

    // Time out for getch
    // timeout(0);

    // Key press are not shown on the window
    noecho();

    // Turn off blinking cursor
    curs_set(0);

    int rows, cols;
    getmaxyx(stdscr, rows, cols);

    int r = min(rows, cols) / 3;

    char pixel = ' ';

    for (int i = 1; i < (TRAIL / TRAIL_STEP); i++)
    {
        int color = i * (1000 / (TRAIL / TRAIL_STEP));
        init_color(i, color, color, color);
        init_pair(i, COLOR_BLACK, i);
    }

    while (1)
    {

        for (float theta = 0; theta < 2 * M_PI; theta += ANGLE_STEP)
        {

            getmaxyx(stdscr, rows, cols);
            int r = min(rows, cols) / 3;
            
            clear();
            int color_step = 0;

            for (float trail = theta; (trail - theta) < TRAIL; trail += TRAIL_STEP)
            {
                color_step += 1;

                int x = 2 * r * cos(trail);

                int y_1 = r * sin(trail);
                int y_2 = r * sin(-trail);

                attron(COLOR_PAIR(color_step));

                mvaddch((rows / 2) + y_1, (cols / 2) + x, pixel);
                mvaddch((rows / 2) + y_2, (cols / 2) + x, pixel);

                attroff(COLOR_PAIR(color_step));

                refresh();
            }

            usleep(TIME_STEP * 1000);
        }
    }

    endwin();

    return 0;
}