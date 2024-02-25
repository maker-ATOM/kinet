#include <iostream>
#include <ncurses.h>
#include <cmath>
#include <unistd.h>
#include <cstring>
#include <sstream>
#include <vector>

using namespace std;

#define ANGLE_STEP 0.1  // rads
#define TRAIL_STEP 0.02 // rads

#define TIME_STEP 100 // ms

#define DEFAULT_TRAIL 120 // degree

void help()
{
    // print help
    printf("Options:\n");
    printf("-t degrees   Trail angle in degrees ranging from 0 to 180\n");
    printf("-b r,g,b     RGB color for background ranging from 0 to 255\n");
    printf("-f r,g,b     RGB color for foreground ranging from 0 to 255\n");
    printf("---\n");
    printf("Supported terminal emulators:\n");
    printf("- gnome-terminal\n");
    printf("- terminator\n");
    exit(0);
}

vector<int> parseColor(string scolor)
{
    char delimiter = ',';

    vector<int> color;
    istringstream stream(scolor);
    string token;

    int count = 0;

    while (getline(stream, token, delimiter))
    {
        int element = stoi(token) * 1000 / 255;
        if (element > 1000 or element < 0)
        {
            help();
        }
        else
        {
            color.push_back(element);
        }
        count++;
    }

    if (count != 3)
    {
        help();
    }
    return color;
}

int main(int argc, char *argv[])
{

    // const char *term = std::getenv("TERM");
    // const char *colorterm = std::getenv("COLORTERM");

    // if (term != nullptr && colorterm != nullptr)
    // {
    //     if (std::string(term) == "xterm" && std::string(colorterm) == "truecolor")
    //     {
    //         std::cout << "Gnome Terminal is likely in use." << std::endl;
    //     }
    //     else if (std::string(term) == "xterm-256color" && std::string(colorterm) == "truecolor")
    //     {
    //         std::cout << "Terminator is likely in use." << std::endl;
    //     }
    //     else
    //     {
    //         std::cout << "Unable to determine the terminal emulator." << std::endl;
    //     }
    // }
    // else
    // {
    //     std::cout << "Unable to determine the terminal emulator." << std::endl;
    // }

    // return 0;

    float TRAIL = DEFAULT_TRAIL * M_PI / 180.0;
    vector<int> bg = {0, 0, 0};
    vector<int> fg = {1000, 1000, 1000};

    if (argc % 2 == 0)
    {
        help();
    }

    for (int i = 1; i < argc; i += 2)
    {

        if (strcmp(argv[i], "-t") == 0)
        {
            int angle = stoi(argv[i + 1]);
            if (angle < 0 or angle > 180)
            {
                help();
            }
            TRAIL = angle * M_PI / 180.0;
        }

        if (strcmp(argv[i], "-b") == 0)
        {
            bg = parseColor(argv[i + 1]);
        }

        if (strcmp(argv[i], "-f") == 0)
        {
            fg = parseColor(argv[i + 1]);
        }
    }

    initscr();

    start_color();

    // Defintion for non-alphanumeric keys
    // keypad(stdscr, true);

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
        int r = i * ((fg[0] - bg[0]) / (TRAIL / TRAIL_STEP)) + bg[0];
        int g = i * ((fg[1] - bg[1]) / (TRAIL / TRAIL_STEP)) + bg[1];
        int b = i * ((fg[2] - bg[2]) / (TRAIL / TRAIL_STEP)) + bg[2];
        init_color(i, r, g, b);
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