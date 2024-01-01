#include <iostream>
#include <ncurses.h>
#include <cmath>
#include <algorithm>
#include <unistd.h>
#include <cstring>

using namespace std;

#define ANGLE_STEP 0.1
#define TRAIL_STEP 0.02

#define TIME_STEP 100

#define DEFAULT_TRAIL 120

void help()
{
    // print help
    printf("Options:\n");
    printf("-t degrees   Trail angle in degrees ranging from 0 to 180\n");
    printf("-b r,g,b     RGB color for background\n");
    printf("-f r,g,b     RGB color for foreground\n");
    printf("Options:\n");
}

int main(int argc, char *argv[])
{
    float TRAIL = DEFAULT_TRAIL * M_PI / 180.0;

    if (argc % 2 == 0)
    {
        help();
        exit(0);
    }

    for (int i = 1; i < argc; i += 2)
    {

        if (strcmp(argv[i], "-t") == 0)
        {
            int angle = stoi(argv[i + 1]);
            if (angle < 0 or angle > 180)
            {
                help();
                exit(0);
            }
            TRAIL = angle * M_PI / 180.0;
        }
    }

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