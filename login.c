#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void get_input (WINDOW *win, int y, int x, const char *prompt, 
           char *buffer, int buffer_size);

void writeToFile (char *name, char *email, char *grade_level, 
                  char *grade_section, char *gwa, char *username,
                  FILE *fp, WINDOW *win);


int 
main() 
{
    initscr();
    cbreak();
    noecho();
    curs_set(1);

    char name[100], email[100], grade_level[10], grade_section[100], gwa[99], username[100];
    char filename[999];
    char theclearening[999] = "                                         ";

    int width = 70;
    int height = 20;
    int win_x = 55;
    int win_y = 20;

    WINDOW *win = newwin(height, width, win_y, win_x);
    box(win, 0, 0);

    while (true) {
        mvwprintw(win, 1, (width / 2) - 11, "CS ALA Registration Form");
        mvwhline(win, 2, 1, '/', width - 2);

        get_input(win, 5, 2, "Name:             ", name, sizeof(name));
        get_input(win, 6, 2, "Username:         ", username, sizeof(username));
        get_input(win, 7, 2, "Email:            ", email, sizeof(email));
        get_input(win, 8, 2, "Grade Level:      ", grade_level, sizeof(grade_level));
        get_input(win, 9, 2, "Grade Section:    ", grade_section, sizeof(grade_section));
        get_input(win, 10, 2, "GWA (last known): ", gwa, sizeof(gwa));

        strcat(filename, username);
        strcat(filename, "_member.txt");

        FILE *fp = fopen(filename, "w");
        writeToFile(name, email, grade_level, grade_section, gwa, username, fp, win);

        memset(name, 0, sizeof(name));
        memset(username, 0, sizeof(username));
        memset(email, 0, sizeof(email));
        memset(grade_level, 0, sizeof(grade_level));
        memset(grade_section, 0, sizeof(grade_section));
        memset(gwa, 0, sizeof(gwa));
        filename[0] = '\0';

        mvwprintw(win, 14, 2, "Press any button to restart..");
        wrefresh(win);
        wgetch(win);
        
        mvwprintw(win, 5, 20, "%s", theclearening);
        mvwprintw(win, 6, 20, "%s", theclearening);
        mvwprintw(win, 7, 20, "%s", theclearening);
        mvwprintw(win, 8, 20, "%s", theclearening);
        mvwprintw(win, 9, 20, "%s", theclearening);
        mvwprintw(win, 10, 20, "%s", theclearening);
        mvwprintw(win, 12, 2, "%s", theclearening);
        mvwprintw(win, 14, 2, "%s", theclearening);

    }

    endwin();
    return 0;
}

void 
get_input (WINDOW *win, int y, int x, const char *prompt, 
           char *buffer, int buffer_size) 
{
    mvwprintw(win, y, x, "%s", prompt);
    wrefresh(win);
    echo();
    mvwgetnstr(win, y, x + strlen(prompt), buffer, buffer_size - 1);
    noecho();
}

void
writeToFile (char *name, char *email, char *grade_level, 
             char *grade_section, char *gwa, char *username,
             FILE *fp, WINDOW *win)
{
    if (fp != NULL) {
        fprintf(fp, "Name: %s\n", name);
        fprintf(fp, "Username: %s\n", username);
        fprintf(fp, "Email: %s\n", email);
        fprintf(fp, "Grade Level: %s\n", grade_level);
        fprintf(fp, "Grade Section: %s\n", grade_section);
        fprintf(fp, "GWA: %s\n", gwa);
        fclose(fp);
        mvwprintw(win, 12, 2, "User registered.");
    } else {
        mvwprintw(win, 12, 2, "Error occured.");
    }
}