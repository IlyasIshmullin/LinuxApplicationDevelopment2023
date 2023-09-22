#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DX 3

enum {
    TOP_PADDING = 1, LEFT_PADDING = 1,
};

void main(char* argc, char** argv)
{

    size_t len;
    size_t bufsize = 100;
    FILE* fptr;
    if ((fptr = fopen(argv[1], "r")) == NULL)
        printf("Can't open file");

    char** lines = calloc(150, sizeof(char) * bufsize);
    char* buffer = malloc(bufsize * sizeof(char));

    int cnt_lines = 0;
    while (getline(&lines[cnt_lines], &bufsize, fptr) != -1)
        cnt_lines++;

    // for (int i = 0; i < cnt_lines; i++) {
    //     printf("%s", lines[i]);
    // }
    WINDOW* win;
    int c = 0;

    initscr();
    noecho();
    cbreak();
    printw("%s", argv[1]);

    refresh();

    win = newwin(LINES - 2 * DX, COLS - 2 * DX, DX, DX);
    keypad(win, TRUE);
    scrollok(win, TRUE);
    box(win, 0, 0);
    wmove(win, 1, 0);
    // for (int conter = 0; conter < cnt_lines; conter++) {
    //     wprintw(win, "%d", conter);
    //     box(win, -1, 0);
    // }
    size_t height = LINES - 2 * DX - 2;
    size_t width = COLS - 2;
 
    for (int conter = 0; conter < cnt_lines && conter < height; conter++) {
        wprintw(win, " %d:\t%s", conter, lines[conter]);
        box(win, 0, 0);
    }
    int real_index = 0;
    while (true) {
        c = wgetch(win);
        switch (c) {
        case 32:
            real_index++;
            werase(win);
            for (int con = real_index; con < cnt_lines && con < height; con++) {
                wprintw(win, "%d:\t%s", con, lines[con]);
                box(win, 0, 0);
            }
            break;
        case 27:
            endwin();
            break;
        }
        wrefresh(win);
    }

    endwin();
}