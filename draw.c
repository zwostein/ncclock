#include <stdlib.h>
#include <ncurses.h>

#include "draw.h"


void draw_getScreenSize( int * x, int * y )
{
	getmaxyx( stdscr, (*y), (*x) );
	(*y) *= DRAW_ASPECTCORRECTION;
}


void draw_pixel( int x, int y, const char * c )
{
	mvprintw( y/DRAW_ASPECTCORRECTION, x, c );
}


static void draw_circle_plot4( int centerX, int centerY, int x, int y, const char * c )
{
	draw_pixel( centerX+x, centerY+y, c );
	if( x ) draw_pixel( centerX-x, centerY+y, c );
	if( y ) draw_pixel( centerX+x, centerY-y, c );
	if( x && y ) draw_pixel( centerX-x, centerY-y, c );
}


static void draw_circle_plot8( int centerX, int  centerY, int x, int y, const char * c )
{
	draw_circle_plot4( centerX, centerY, x, y, c );
	if( x != y ) draw_circle_plot4( centerX, centerY, y, x, c );
}


void draw_circle( int centerX, int centerY, int radius, const char * c )
{
	int error = -radius;
	int x = radius;
	int y = 0;
	while( x >= y )
	{
		draw_circle_plot8( centerX, centerY, x, y, c );
		error += y;
		y++;
		error += y;
		if( error >= 0 )
		{
			x--;
			error -= 2*x;
		}
	}
}


void draw_line( int x0, int y0, int x1, int y1, const char * c )
{
	int dx = abs( x1 - x0 );
	int dy = abs( y1 - y0 );
	int stepX = ( x0 < x1 ) ? 1 : -1;
	int stepY = ( y0 < y1 ) ? 1 : -1;
	int error = dx - dy;

	while( true )
	{
		draw_pixel( x0, y0, c );
		if( x0==x1 && y0==y1 )
			return;
		int error2 = 2*error;
		if( error2 > -dy )
		{
			error -=  dy;
			x0 += stepX;
		}
		if( error2 < dx )
		{
			error += dx;
			y0 += stepY;
		}
	}
}
