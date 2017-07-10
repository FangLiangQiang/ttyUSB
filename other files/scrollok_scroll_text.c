#include <ncurses.h>
#include <unistd.h>
#include <fcntl.h>
#define dir "/home/lq/Files/codesrc/C/tty/out/test.txt"							
							
int main(int argc,char *argv[])
{
	initscr();
	refresh();
	noecho();
	keypad(stdscr,TRUE);
	scrollok(stdscr,TRUE);
	
	int fd;
	fd = open(dir,O_RDONLY);
	if(fd<0) return -1;
	
	char buff[1024*2];
	read(fd,buff,1023*2);
	printw("%s",buff);
	refresh();
	
	int ch;
	while((ch=getch())!=KEY_F(2))
	{
		switch(ch)
		{
			case KEY_DOWN:
						 
						  wscrl(stdscr,1);		
						  refresh();
						  break;

			case KEY_UP:
						wscrl(stdscr,-1);	
						refresh();
						break;

			default:break;
		}
	}
	close(fd);
	endwin();
	return 0;
}
