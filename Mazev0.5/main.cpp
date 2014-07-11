#include <stdio.h>
#include <stdlib.h>
#include "maze.h"
#include "sdl.h"
#include "sdl_ttf.h"

/****************************
	key function table
	F1  help
	F2 clear map
	D	deep search
	A	a start search
	W	wide search
	S	step 
	C	coninue
	L	load map
	M	save map
	SPASE clear tables and flags
	R	random map
	P	print map
	T	trace 
	X	draw path
	G	go for search
*****************************/

const int SCREEN_WIDTH = 900;
const int SCREEN_HEIGHT = 700;
const int SCREEN_BPP = 32;
 

SDL_Surface *background = NULL;
SDL_Surface *screen = NULL;
SDL_Surface *message = NULL;

SDL_Surface *upMessage =NULL;
SDL_Surface *downMessage  =NULL;
SDL_Surface *leftMessage =NULL;
SDL_Surface *rightMessage =NULL;
SDL_Surface *infoMessage =NULL;
SDL_Event event;

TTF_Font *font = NULL;
SDL_Thread *thread = NULL;

SDL_Color textColor = { 0, 0xff, 0 };

SDL_Surface *stepbmp=NULL;
SDL_Surface *block=NULL;
SDL_Surface *noblock=NULL;
SDL_Surface *startimg=NULL;
SDL_Surface *endimg=NULL;

struct node* opentable=NULL;
struct node* closetable=NULL;
int map[MAZEROW][MAZECOL];
int startx;
int starty;
int endx;
int endy;
int step;
int searchway=0;

int drawx;
int drawy;

bool quit = false;
bool traceflage=false;
bool drawpathflage=false;
bool searchfinishflage=false;
bool isfirstdrawflage=true;
bool leftbtnflage=false;
bool rightbtnflage=false;

int main(int argc,char* argv[]){
	
	init_sdl();
	draw_map();
	if( SDL_Flip( screen ) == -1 )
	{
		return -1;    
	} 

	init();
	print_map();
	draw_map();
	
	thread = SDL_CreateThread( my_thread, NULL );
    key_process();

	return 0;
}