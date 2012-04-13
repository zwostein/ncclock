#include <ncurses.h>

#include "draw.h"
#include "clock.h"


int main( int argc, char ** argv )
{
	initscr();
	halfdelay( 5 );
	keypad( stdscr, TRUE );
	noecho();

	start_color();
	clock_init();

	while( getch() != 'q' )
	{
		int x = 0, y = 0;
		int centerX = 0, centerY = 0, radius = 0;
		time_t rawtime;
		struct tm * timeinfo;

		time( &rawtime );
		timeinfo = localtime( &rawtime );

		draw_getScreenSize( &x, &y );
		centerX = x/2;
		centerY = y/2;
		radius = (((x>y)?y:x)-1)/2;
		clear();
		mvprintw( 0, 0, "%s", asctime(timeinfo) );
		clock_draw( centerX, centerY, radius, timeinfo );
		move( 0, 0 );
		refresh();
	}

	endwin();

	return 0;
}
