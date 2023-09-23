#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DX 3

int main(int argc, char **argv)
{
    WINDOW *win;
    initscr();
    noecho();
    cbreak();
    refresh();

    if (argc < 2)
    {
        printf("Provide filename\n");
        return 1;
    }
    char *filename = argv[1];
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        printf("Couldn't open file\n");
        return 1;
    }
    fseek(file, 0L, SEEK_END);
    size_t size = ftell(file);
    fseek(file, 0L, SEEK_SET);
    char *contents = malloc(size * sizeof(char));
    int n;
    if ((n = fread(contents, sizeof(char), size, file)) != size)
    {
        printf("Couldn't read from file, read %d symbols\n", n);
        return 1;
    }
    printw("File: %s; size: %d\n", filename, size);
    refresh();

    win = newwin(LINES - 2 * DX, COLS - 2 * DX, DX, DX);
    keypad(win, TRUE);
    scrollok(win, TRUE);
    box(win, 0, 0);
    wrefresh(win);

    char c;
    size_t begin = 0, end = 0, line_num = 1;
    wmove(win, 1, 1);
    while ((c = wgetch(win)) != 27)
    {
        if (c == ' ')
        {
            if (contents[end] == 0)
            {
                continue;
            }
            while (contents[end] != '\n' && contents[end] != 0)
            {
                ++end;
            }

            bool first_line = true;
            while (end - begin + 1 > COLS - 2 * DX - 5)
            {
                if (first_line)
                {
                    wprintw(win, "%3lu", line_num);
                    first_line = false;
                }
                wprintw(win, " %.*s\n", COLS - 2 * DX - 6, &contents[begin]);
                begin += COLS - 2 * DX - 6;
            }
            if (first_line)
            {
                wprintw(win, "%3lu", line_num);
                first_line = false;
            }
            wprintw(win, " %.*s\n", end - begin, &contents[begin]);
            ++line_num;

            if (contents[end] != 0)
            {
                begin = ++end;
            }
            int y = getcury(win);
            wmove(win, y, 1);
            box(win, 0, 0);
            wrefresh(win);
        }
    }

    endwin();
    fclose(file);
    return 0;
}
