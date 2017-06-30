#include <ncurses.h>
#include <stdlib.h>

#define MAXLEN 128

typedef struct Line {
    char contents[MAXLEN];
    struct Line *prev, *next;
} Line;

Line *head, *curr;

int nr_lines;
int curr_line;

int term_rows, term_cols;

void load(const char *filename);
void draw(Line *l);

int main(int argc, char **argv)
{
    if (argc == 1)
    {
        fputs("less: No file to open\n", stderr);
        return 1;
    }

    initscr();
    noecho();
    keypad(stdscr, TRUE);   // for KEY_UP, KEY_DOWN
    getmaxyx(stdscr, term_rows, term_cols);
    addstr("Reading text...\n");

    load(argv[1]);

    curr = head;
    curr_line = 0;
    draw(curr);

    int ch;
    while ((ch = getch()) != EOF && ch != 'q')
    {
        if (ch == KEY_UP && curr->prev != NULL)
        {
            curr_line--;
            curr = curr->prev;
        }
        else if (ch == KEY_DOWN && curr->next != NULL
            && curr_line + term_rows < nr_lines)
        {
            curr_line++;
            curr = curr->next;
        }
        draw(curr);
    }

    endwin();
    return 0;
}

void load(const char *filename)
{
    FILE *fp = fopen(filename, "r");
    Line *lp;

    head = malloc(sizeof(Line));
    head->prev = head->next = NULL;
    curr = head;

    while (fgets(curr->contents, MAXLEN, fp))
    {
        lp = malloc(sizeof(Line));
        lp->prev = curr;
        curr->next = lp;
        curr = lp;
        nr_lines++;
    }
    curr->next = NULL;
}

void draw(Line *l)
{
    int i;
    clear();
    for (i = 0; i < term_rows && l != NULL; i++, l = l->next)
        addstr(l->contents);
}
