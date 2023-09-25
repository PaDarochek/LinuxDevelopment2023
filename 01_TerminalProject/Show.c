#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DX 3

void draw_screen(WINDOW *win, char **contents, size_t from_line, size_t to_line, size_t from_col)
{
    werase(win);
    wmove(win, 1, 0);
    for (int32_t i = from_line; i < to_line; ++i)
    {
        if (from_col < strlen(contents[i]))
        {
            wprintw(win, " %3lu %.*s", i + 1, COLS - 2 * DX - 6, &contents[i][from_col]);
            if (strlen(contents[i]) - from_col > COLS - 2 * DX - 6)
            {
                waddch(win, '\n');
            }
        }
        else
        {
            wprintw(win, " %3lu\n", i + 1);
        }
    }
    box(win, 0, 0);
    wrefresh(win);
}

int main(int argc, char **argv)
{
    // Init
    WINDOW *win;
    initscr();
    noecho();
    cbreak();
    refresh();

    // Open file
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

    // Get filesize and number of lines
    fseek(file, 0L, SEEK_END);
    size_t size = ftell(file);
    fseek(file, 0L, SEEK_SET);
    char c;
    int32_t num_lines = 0;
    while ((c = fgetc(file)) != EOF)
    {
        if (c == '\n')
        {
            num_lines++;
        }
    }

    // Read lines to contents
    fseek(file, 0L, SEEK_SET);
    char **contents = calloc(num_lines, sizeof(char *));
    for (int32_t i = 0; i < num_lines; ++i)
    {
        size_t n;
        if ((n = getline(&contents[i], &n, file)) == -1)
        {
            printf("Couldn't read from file, read %lu symbols on %d line\n", n, i);
            return 1;
        }
    }

    // Print file info
    printw("File: %s; size: %d\n", filename, size);
    refresh();

    // Create window
    win = newwin(LINES - 2 * DX, COLS - 2 * DX, DX, DX);
    keypad(win, TRUE);
    scrollok(win, TRUE);
    box(win, 0, 0);
    wrefresh(win);

    // Eval loop
    int x;
    int32_t line_num = -1, col_num = 0;
    while ((x = wgetch(win)) != 27)
    {
        switch (x)
        {
        case ' ':
        case KEY_DOWN:
        {
            if (line_num < num_lines - 1)
            {
                line_num++;
            }
            draw_screen(win, contents, line_num,
                        line_num + LINES - 2 * DX - 2 < num_lines
                            ? line_num + LINES - 2 * DX - 2
                            : num_lines,
                        col_num);
            break;
        }
        case KEY_UP:
        {
            if (line_num > 0)
            {
                line_num--;
            }
            draw_screen(win, contents, line_num,
                        line_num + LINES - 2 * DX - 2 < num_lines
                            ? line_num + LINES - 2 * DX - 2
                            : num_lines,
                        col_num);
            break;
        }
        case KEY_RIGHT:
        {
            col_num++;
            draw_screen(win, contents, line_num,
                        line_num + LINES - 2 * DX - 2 < num_lines
                            ? line_num + LINES - 2 * DX - 2
                            : num_lines,
                        col_num);
            break;
        }
        case KEY_LEFT:
        {
            if (col_num > 0)
            {
                col_num--;
            }
            draw_screen(win, contents, line_num,
                        line_num + LINES - 2 * DX - 2 < num_lines
                            ? line_num + LINES - 2 * DX - 2
                            : num_lines,
                        col_num);
            break;
        }
        case KEY_PPAGE:
        {
            if (line_num - (LINES - 2 * DX - 2) >= 0)
            {
                line_num -= (LINES - 2 * DX - 2);
            }
            else
            {
                line_num = 0;
            }
            draw_screen(win, contents, line_num,
                        line_num + LINES - 2 * DX - 2 < num_lines
                            ? line_num + LINES - 2 * DX - 2
                            : num_lines,
                        col_num);
            break;
        }
        case KEY_NPAGE:
        {
            if (line_num == -1)
            {
                line_num++;
            }
            if (line_num + LINES - 2 * DX - 2 < num_lines - 1)
            {
                line_num += (LINES - 2 * DX - 2);
            }
            else
            {
                line_num = num_lines - 1;
            }
            draw_screen(win, contents, line_num,
                        line_num + LINES - 2 * DX - 2 < num_lines
                            ? line_num + LINES - 2 * DX - 2
                            : num_lines,
                        col_num);
            break;
        }
        default:
        {
            break;
        }
        }
    }

    for (int32_t i = 0; i < num_lines; ++i)
    {
        free(contents[i]);
    }
    free(contents);
    endwin();
    fclose(file);
    return 0;
}
