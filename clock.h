#ifndef __NCCLOCK_CLOCK_H_INCLUDED__
#define __NCCLOCK_CLOCK_H_INCLUDED__

#include <time.h>

#ifndef CLOCK_COLOR_FRAME
#define CLOCK_COLOR_FRAME	1
#endif
#ifndef CLOCK_COLOR_MARKS
#define CLOCK_COLOR_MARKS	2
#endif
#ifndef CLOCK_COLOR_SECONDS
#define CLOCK_COLOR_SECONDS	3
#endif
#ifndef CLOCK_COLOR_MINUTES
#define CLOCK_COLOR_MINUTES	4
#endif
#ifndef CLOCK_COLOR_HOURS
#define CLOCK_COLOR_HOURS	5
#endif

void clock_init( void );
void clock_draw( int centerX, int centerY, int radius, struct tm * timeinfo );

#endif
