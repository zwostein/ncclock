#include <math.h>
#include <ncurses.h>

#include "draw.h"

#include "clock.h"


void clock_init( void )
{
	init_pair( CLOCK_COLOR_FRAME, COLOR_CYAN, COLOR_BLUE );
	init_pair( CLOCK_COLOR_MARKS, COLOR_YELLOW, COLOR_BLACK );
	init_pair( CLOCK_COLOR_SECONDS, COLOR_RED, COLOR_BLACK );
	init_pair( CLOCK_COLOR_MINUTES, COLOR_GREEN, COLOR_BLACK );
	init_pair( CLOCK_COLOR_HOURS, COLOR_CYAN, COLOR_BLACK );
}


static void drawFinger( int centerX, int centerY, int radius, float lengthFrom, float lengthTo, float angle, const char * c )
{
	draw_line( centerX+sinf(angle)*radius*lengthFrom, centerY+cosf(angle)*radius*lengthFrom, centerX+sinf(angle)*radius*lengthTo, centerY+cosf(angle)*radius*lengthTo, c );
}


static float hours2angle( int minutes, int hours )
{
	hours %= 12;
	minutes %= 60;
	return -( ((2.0f*M_PI)/12.0f)*(float)hours + (((2.0f*M_PI)/12.0f)/60.0f)*(float)minutes + (M_PI) );
}


static float minutes2angle( int seconds, int minutes )
{
	minutes %= 60;
	seconds %= 60;
	return -( ((2.0f*M_PI)/60.0f)*(float)minutes + (((2.0f*M_PI)/60.0f)/60.0f)*(float)seconds + (M_PI) );
}


static float seconds2angle( int seconds )
{
	seconds %= 60;
	return -( ((2.0f*M_PI)/60.0f)*(float)seconds + (M_PI) );
}


void clock_draw( int centerX, int centerY, int radius, struct tm * timeinfo )
{
	int i;
	attron( COLOR_PAIR(CLOCK_COLOR_MARKS) );
	for( i=0; i<12; i++ )
	{
		drawFinger( centerX, centerY, radius, 0.75f, 0.9f, seconds2angle(i*5), "." );
	}
	attroff( COLOR_PAIR(CLOCK_COLOR_MARKS) );

	attron( COLOR_PAIR(CLOCK_COLOR_SECONDS) );
	drawFinger( centerX, centerY, radius, 0.6f, 0.9f, seconds2angle( timeinfo->tm_sec ), "s" );
	attroff( COLOR_PAIR(CLOCK_COLOR_SECONDS) );
	attron( COLOR_PAIR(CLOCK_COLOR_MINUTES) );
	drawFinger( centerX, centerY, radius, 0.0f, 0.8f, minutes2angle( timeinfo->tm_sec, timeinfo->tm_min ), "M" );
	attroff( COLOR_PAIR(CLOCK_COLOR_MINUTES) );
	attron( COLOR_PAIR(CLOCK_COLOR_HOURS) );
	drawFinger( centerX, centerY, radius, 0.0f, 0.6f, hours2angle( timeinfo->tm_min, timeinfo->tm_hour ), "H" );
	attroff( COLOR_PAIR(CLOCK_COLOR_HOURS) );

	attron( COLOR_PAIR(CLOCK_COLOR_FRAME) );
	draw_pixel( centerX, centerY, "O" );
	draw_circle( centerX, centerY, radius, ":" );
	attroff( COLOR_PAIR(CLOCK_COLOR_FRAME) );
}
