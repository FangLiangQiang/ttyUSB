#include<ncurses.h>
int main(int argc,char *argv[])
{
	WINDOW *wp;
	initscr();
	refresh();
	noecho();
	keypad(stdscr,TRUE);
	wp = newwin(5,51,5,0);
	box(wp,0,0);
	wrefresh(wp);
	mvwprintw(wp,1,1,"hello1");
	mvwprintw(wp,2,1,"hello2");
	mvwprintw(wp,3,1,"hello3");
	wrefresh(wp);
	scrollok(wp,TRUE);

	int ch;
	while((ch=getch())!=KEY_F(2))
	{
		switch(ch)
		{
			case KEY_DOWN:mvprintw(10,0,"Key_down press");
						  refresh();
						  wscrl(wp,1);
						  //scrollok(wp,TRUE);
						  box(wp,0,0);
						  wrefresh(wp);
						  break;

			case KEY_UP:mvprintw(10,0,"key_up press");
						refresh();
						wscrl(wp,-1);	
						//scrollok(wp,TRUE);
						box(wp,0,0);
						wrefresh(wp);
						break;

			default:break;
		}
	}

	delwin(wp);
	endwin();
	return 0;
}
