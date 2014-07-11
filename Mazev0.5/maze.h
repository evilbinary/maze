#ifndef _MAZE_H
#define _MAZE_H
#include "sdl.h"
#include "sdl_ttf.h"

#define MAZEROW 20
#define MAZECOL 25

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT ;
extern const int SCREEN_BPP;


extern SDL_Surface *background;
extern SDL_Surface *screen ;
extern SDL_Event event;
extern SDL_Surface *message ;
extern SDL_Surface *upMessage;
extern SDL_Surface *downMessage;
extern SDL_Surface *leftMessage;
extern SDL_Surface *rightMessage ;
extern SDL_Surface *infoMessage;

extern SDL_Thread *thread ;
extern SDL_Surface *stepbmp;
extern SDL_Surface *block;
extern SDL_Surface *noblock;
extern TTF_Font *font;
extern SDL_Color textColor ;

extern SDL_Surface *startimg ;
extern SDL_Surface *endimg ;

extern int map[MAZEROW][MAZECOL];			//地图

extern int startx;				//开始坐标
extern int starty;				//
extern int endx;				//结束坐标
extern int endy;
extern int step;					//走的步数
extern int searchway;

extern int drawx;
extern int drawy;

extern bool quit ;
extern bool traceflage;
extern bool searchfinishflage;
extern bool drawpathflage;
extern bool isfirstdrawflage;

extern bool leftbtnflage;
extern bool rightbtnflage;

extern struct node* opentable ;
extern struct node* closetable ;

struct node {
	int x;
	int y;
	int fn;
	int step;
	struct node* parent;
	struct node* next;
};


void init();
void make_map();
void make_random_map();
int evaluate(int x,int y,int s);
void print_map();
void insert_opentable(struct node* node);
void insert_closetable(struct node* node);
struct node* remove_opentable(struct node* node);
bool is_in_closetable(struct node* node);

void save_map();
void read_map();

void clear_opentable();
void clear_closetable();

void print_closetable();
void print_opentable();
void new_opennode();

void do_search();
void do_astart_search();
void do_wide_search();
void do_deep_search();


void draw_map();
void draw_trace();
void draw_path();

void clear_map();
void print_help();
void apply_surface(int x,int y,SDL_Surface* source,SDL_Surface* destination,SDL_Rect* clip);
bool init_sdl();
void clean_up();
void key_process();
int my_thread( void *data );
SDL_Surface *load_image(char* filename);
bool load_files();


#endif