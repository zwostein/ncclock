#include <ncurses.h>

#include "draw.h"
#include "clock.h"

#include <argp.h>

const char *argp_program_version = "ncclock - compiled on "__DATE__" "__TIME__;
const char *argp_program_bug_address = "<provisorisch@online.de>";
static char doc[] = "ncclock - A simple analog ncurses clock";

static struct argp_option options[] =
{
	{ "text",	't',	0,	0,	"Additionally, display time and date as text.",	0 },
	{ 0,		0,	0,	0,	0,					0 }
};

struct arguments
{
	int text;
};

static error_t parse_opt( int key, char * arg, struct argp_state * state )
{
	struct arguments *arguments = state->input;
	(void)arg;
	switch( key )
	{
		case 't':
			arguments->text = 1;
			break;

		case ARGP_KEY_ARG:
			if( state->arg_num > 0 )
				argp_usage( state );
			break;

		case ARGP_KEY_END:
			break;
		default:
			return ARGP_ERR_UNKNOWN;
	}
	return 0;
}

static struct argp argp = { options, parse_opt, 0, doc, 0, 0, 0 };


int main( int argc, char ** argv )
{
	struct arguments args;
	args.text = 0;

	argp_parse( &argp, argc, argv, 0, 0, &args );

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
		if( args.text )
			mvprintw( 0, 0, "%s", asctime(timeinfo) );
		clock_draw( centerX, centerY, radius, timeinfo );
		move( 0, 0 );
		refresh();
	}

	endwin();

	return 0;
}
