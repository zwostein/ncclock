#ifndef __NCCLOCK_DRAW_H_INCLUDED__
#define __NCCLOCK_DRAW_H_INCLUDED__

#ifndef DRAW_ASPECTCORRECTION
#define DRAW_ASPECTCORRECTION	2
#endif

void draw_getScreenSize( int * x, int * y );
void draw_pixel( int x, int y, const char * c );
void draw_circle( int centerX, int centerY, int radius, const char * c );
void draw_line( int x0, int y0, int x1, int y1, const char * c );

#endif
