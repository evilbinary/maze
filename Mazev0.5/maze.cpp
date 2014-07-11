#include "maze.h"
#include "sdl_ttf.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>


void make_map(){
	for(int i=0;i<MAZEROW;i++){
		for(int j=0;j<MAZECOL;j++){
			map[i][j]=0;
		}
	}
	map[0][1]=1;
	map[1][1]=1;
	map[1][6]=1;
	//map[1][7]=1;
	
	map[0][2]=1;
	map[4][0]=1;
	map[7][1]=1;
	map[3][6]=1;
	map[2][7]=1;
	map[3][6]=1;
	map[4][6]=1;
	map[5][6]=1;
	map[7][6]=1;
	//map[7][5]=1;
	map[6][6]=1;
	//map[2][2]=1;
	//map[2][3]=1;
	map[2][4]=1;
	map[2][6]=1;
	map[2][7]=0;
	
	map[3][2]=1;
	map[3][3]=1;
	map[3][4]=1;
	
	map[4][2]=1;
	//map[4][3]=1;
	map[4][4]=1;
	
	//map[5][2]=1;
	map[5][3]=1;
	map[5][4]=1;
	
	//map[6][2]=1;
	map[6][3]=1;
	map[6][4]=1;
	
	for(  i=1;i<=19;i++){
		map[i][18]=1;
	}
	for(  i=0;i<19;i++){
		map[i][16]=1;
	}
	
	for(  i=7;i<16;i++){
		map[7][i]=1;
	}
	for(  i=8;i<16;i++){
		map[i][10]=1;
	}
	//make_random_map();
}

void make_random_map(){
	//srand(time(0));
	int a=rand()%2;
	for(int i=0;i<MAZEROW;i++){
		for(int j=0;j<MAZECOL;j++){
			if(rand()%2==0){
				map[i][j]=rand()%2;
			}else{
				
				map[i][j]=0;
			}
			
		}
	}
	
	endy=MAZEROW-1;
	endx=MAZECOL-1;
	map[starty][startx]=0;
	map[endy][endx]=0;
	
}
void init(){
	step=0;
	endy=MAZEROW-1;
	endx=MAZECOL-1;
	map[starty][startx]=0;
	map[endy][endx]=0;
	make_map();
	//make_random_map();
}

int evaluate(int x,int y,int s){
	int xx=abs(endx-x);
	int yy=abs(endy-y);
	return xx+yy+s;
	//return xx*xx+yy*yy+s*s;
	
}

void print_map(){
	for(int i=0;i<MAZEROW;i++){
		for(int j=0;j<MAZECOL;j++){
			printf("%d ",map[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}


void insert_opentable(struct node* node){
	struct node* tmp=opentable;
	if(opentable==NULL){	//没有节点的时候
		opentable=node;
	}else{
		if(tmp->next==NULL){	//有1个
			if(node->fn<tmp->fn){
				node->next=tmp;
				opentable=node;
			}else{
				tmp->next=node;
			}
		}else{
			if(node->fn<tmp->fn){
				node->next=tmp;
				opentable=node;
			}else{
				while(tmp->next!=NULL){
					if(node->fn<tmp->next->fn){
						node->next=tmp->next;
						tmp->next=node;
						return;
					} 
					tmp=tmp->next;
				}
				tmp->next=node;
			}
		}
	}
	
	
}

void insert_opentable_wide(struct node* node){
	node->fn=node->step;
	struct node* tmp=opentable;
	if(opentable==NULL){	//没有节点的时候
		opentable=node;
	}else{
		if(tmp->next==NULL){	//有1个
			if(node->fn<tmp->fn){
				node->next=tmp;
				opentable=node;
			}else{
				tmp->next=node;
			}
		}else{
			if(node->fn<tmp->fn){
				node->next=tmp;
				opentable=node;
			}else{
				while(tmp->next!=NULL){
					if(node->fn<tmp->next->fn){
						node->next=tmp->next;
						tmp->next=node;
						return;
					} 
					tmp=tmp->next;
				}
				tmp->next=node;
			}
		}
	}
	
	
}



struct node* remove_opentable(struct node* node){
	struct node* tmp=opentable;
	if(opentable==NULL){	//没有节点的时候
		return NULL;
	}else{
		if(tmp->next==NULL){	//有1个
			if(node->x==tmp->x&&node->y==tmp->y){
				opentable=NULL;
				return tmp;	
			}else{
				return NULL;
			}
		}else{
			if(node->x==tmp->x&&node->y==tmp->y){	//有两个
				opentable=tmp->next;
				tmp->next=NULL;
				return tmp;		 
			}else{
				while (tmp->next!=NULL) {
					if(node->x==tmp->next->x&&node->y==tmp->next->y){
						struct node* tnext=tmp->next;
						tmp->next=tmp->next->next;
						tnext->next=NULL;
						return tnext;
						break;
					}
					tmp=tmp->next;
				}
				return tmp;	
			}
		}
	}
	return tmp;
}

bool is_in_opentable(struct node* node){
	struct node* tmp=opentable;
	while (tmp!=NULL) {
		if(tmp->x==node->x&&tmp->y==node->y){
			return true;
		}
		tmp=tmp->next;
	}
	return false;
}

void insert_closetable(struct node* node){
	struct node* tmp=closetable;
	if(closetable==NULL){
		closetable=node;
	}else{
		if(tmp->next==NULL){	
			tmp->next=node;
		}else{
			while (tmp->next!=NULL) {
				tmp=tmp->next;
			}
			tmp->next=node;
		}
	}
	
}
bool is_in_closetable(struct node* node){
	struct node* tmp=closetable;
	while (tmp!=NULL) {
		if(tmp->x==node->x&&tmp->y==node->y){
			return true;
		}
		tmp=tmp->next;
	}
	return false;
}
void remove_closetable(struct node* node){
	
}

void clear_opentable(){//未实现
	struct node* tmp=opentable;
	while (tmp!=NULL) {
		
		
		tmp=tmp->next;
	}
	opentable=NULL;	
}
void clear_closetable(){//未实现
	struct node* tmp=closetable;
	while (tmp!=NULL) {
		
		
		tmp=tmp->next;
	}
	closetable=NULL;	
}

void print_opentable(){
	struct node* tmp=opentable;
	int count=0;
	while (tmp!=NULL) {
		printf("%d[%d,%d] ",tmp->fn,tmp->y,tmp->x);
		count++;
		tmp=tmp->next;
	}
	printf("Open Table count=%d\n",count);
}

void print_closetable(){
	int count=0;
	struct node* tmp=closetable;
	while (tmp!=NULL) {
		printf("%d[%d,%d] ",tmp->fn,tmp->y,tmp->x);
		count++;
		tmp=tmp->next;
	}
	printf("Close Table count=%d\n",count);
}


void new_opennode(){
	struct node* head=new struct node;
	head->fn=opentable->fn;
	head->next=NULL;
	head->x=opentable->x;
	head->y=opentable->y;
	head->step=opentable->step;
	head->parent=opentable->parent;
	
	struct node* tt=remove_opentable(head);

	insert_closetable(tt);	 
 
	
	//left
	if (head->x>0&&head->x<=(MAZECOL-1)&&map[head->y][head->x-1]!=1){
		struct node *left=new struct node;
		left->fn=evaluate(head->x-1,head->y,head->step);
		left->x=head->x-1;
		left->y=head->y;
		left->step=step;
		left->parent=head;
		left->next=NULL;
		if(!is_in_closetable(left)&&!is_in_opentable(left)){
			switch(searchway){
			case 0:
				insert_opentable(left);			//A* 算法搜索插入排序
				break;
			case 1:								//广度搜索插入排序
				insert_opentable_wide(left);
				break;
			case 2:								//深度搜索插入排序
				break;
			}
		}
			
	}
	//right
	if(head->x>=0&&head->x<(MAZECOL-1)&&map[head->y][head->x+1]!=1){
		struct node *right=new struct node;
		right->fn=evaluate(head->x+1,head->y,head->step);
		right->x=head->x+1;
		right->y=head->y;
		right->step=step;
		right->parent=head;
		right->next=NULL;
		if(!is_in_closetable(right)&&!is_in_opentable(right)){
			switch(searchway){
			case 0:
				insert_opentable(right);			//A* 算法搜索插入排序
				break;
			case 1:								//广度搜索插入排序
				insert_opentable_wide(right);
				break;
			case 2:								//深度搜索插入排序
				break;
			}
		}
		
	}
	//up
	if(head->y>0&&head->y<=(MAZEROW-1)&&map[head->y-1][head->x]!=1){
		struct node *up=new struct node;
		up->fn=evaluate(head->x,head->y-1,head->step);
		up->x=head->x;
		up->y=head->y-1;
		up->step=step;
		up->parent=head;
		up->next=NULL;
		if(!is_in_closetable(up)&&!is_in_opentable(up)){
				switch(searchway){
			case 0:
				insert_opentable(up);			//A* 算法搜索插入排序
				break;
			case 1:								//广度搜索插入排序
				insert_opentable_wide(up);
				break;
			case 2:								//深度搜索插入排序
				break;
			}
		}
		
		
	} 
	//down
	if(head->y>=0&&head->y<(MAZEROW-1)&&map[head->y+1][head->x]!=1){
		struct node* down=new struct node;
		down->fn=evaluate(head->x,head->y+1,head->step);
		down->x=head->x;
		down->y=head->y+1;
		down->step=step;
		down->parent=head;
		down->next=NULL;
		if(!is_in_closetable(down)&&!is_in_opentable(down)){
				switch(searchway){
			case 0:
				insert_opentable(down);			//A* 算法搜索插入排序
				break;
			case 1:								//广度搜索插入排序
				insert_opentable_wide(down);
				break;
			case 2:								//深度搜索插入排序
				break;
			}
		}
		
	}	
	
	
}



void do_search(){
	bool successflage=false;
	struct node* t=new struct node;
	t->x=startx;
	t->y=starty;
	t->fn=evaluate(startx,starty,step);
	t->step=step;
	t->next=NULL;
	t->parent=NULL;
	insert_opentable(t);
	
	while (true) {
		new_opennode();
		if(opentable==NULL){
			successflage=false;
			break;
		}
		//SDL_Delay( 200 );
		//draw_trace();
		if(opentable->x==endx&&opentable->y==endy){
			new_opennode();
			print_opentable();
			
			printf("\n\n");
			successflage=true;
			break;
		}
		/*	
		printf("Open Table\n");
		print_opentable();
		printf("\n\nClose Table\n");
		print_closetable();
		printf("\n\n");
		*/
		step++;
		if(step>MAZEROW*800){
			
			printf("Faile too long bug .\n");
			break;
		}
		
	} 
	
	if(successflage==true){
		printf("Close Table step:%d\n",step);
		print_closetable();
		printf("Depth=%d\n",step);
	}else{
		printf("no way step:%d\n",step);
	}
}
void do_astart_search(){
	searchway=0;
}
void do_wide_search(){
	searchway=1;
}
void do_deep_search(){
	searchway=2;
}

void draw_trace(){
	
	struct node* tmp=closetable;
	while (tmp!=NULL) {
		//printf("%d[%d,%d] ",tmp->fn,tmp->y,tmp->x);
		apply_surface(30 +endy*30+endy,30 +endx*30+endx,endimg,screen,NULL);	
		if(tmp->y==starty&&tmp->x==startx){
			apply_surface(30 +starty*30+starty, 30 +startx*30+startx,startimg,screen,NULL);
		} else{
				apply_surface(30+ tmp->x*30+tmp->x,30+  tmp->y*30+tmp->y,stepbmp,screen,NULL);
		}
		
		if(isfirstdrawflage){
			SDL_Delay( 50 );
			if( SDL_Flip( screen ) == -1 )
			{
				return ;    
			}
		}
		
		tmp=tmp->next;
	}
	
	 apply_surface(30 +endx*30+endx,30 +endy*30+endy,endimg,screen,NULL);
	
	
	
}
void draw_path(){
	int countstep=0;
	char msg[20];
	struct node* tmp=closetable;
	if(tmp==NULL)
		return;
	while(tmp->next!=NULL){
		
		tmp=tmp->next;
	}
	tmp=tmp->parent;
	while (tmp!=NULL) {
		//printf("%d[%d,%d] ",tmp->fn,tmp->y,tmp->x);
		if(tmp->y==starty&&tmp->x==startx){
			apply_surface(30 +starty*30+starty, 30 +startx*30+startx,startimg,screen,NULL);
		} else{
			apply_surface(30+ tmp->x*30+tmp->x,30+  tmp->y*30+tmp->y,stepbmp,screen,NULL);
		}
		if(isfirstdrawflage){
			SDL_Delay( 100 );
			
			if( SDL_Flip( screen ) == -1 )
			{
				return ;    
			}
		}
		countstep++;
		tmp=tmp->parent;
	}
	
	sprintf(msg,"countstep=%d",countstep);
	message=TTF_RenderText_Solid( font,msg, textColor );
	apply_surface(30 +endx*30+endx,30 +endy*30+endy,endimg,screen,NULL);
}





void apply_surface(int x,int y,SDL_Surface* source,SDL_Surface* destination,SDL_Rect* clip){
	SDL_Rect offset;
	offset.x=x;
	offset.y=y;
	SDL_BlitSurface(source,clip,destination,&offset);
}

bool init_sdl(){
	SDL_Color blueColor={0x00,00,0xff};
		SDL_Color redColor={0xff,00,0x00};
	//Initialize all SDL subsystems
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        return false;    
    }
    
    //Set up the screen
    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );
    
    //If there was an error in setting up the screen
    if( screen == NULL )
    {
        return false;    
    }
    //Initialize SDL_ttf
    if( TTF_Init() == -1 )
    {
        return false;    
    }
    
    //Set the window caption
    SDL_WM_SetCaption( "Maze", NULL );
    
    //If everything initialized fine
	init();
	load_files();
	block=load_image("block.bmp");
	noblock=load_image("noblock.bmp");
	stepbmp=load_image("step.bmp");
	background=load_image("background.bmp");
	startimg=load_image("start.bmp");
	endimg=load_image("end.bmp");
	upMessage =TTF_RenderText_Solid( font, "Do a start search.", textColor );;
	downMessage  =TTF_RenderText_Solid( font, "Do trace.", textColor );;
	leftMessage =TTF_RenderText_Solid( font, "Do clear opentable closetable.", textColor );;
	rightMessage =TTF_RenderText_Solid( font, "Down was pressed.", textColor );
	wchar_t msg[] =L"            迷失的森林  08计算机2班 小E同学";
	infoMessage=TTF_RenderUNICODE_Solid( font,(const Uint16 *)msg, redColor );
	
    return true;
}

void clean_up()
{
    //Free the surfaces
    SDL_FreeSurface( background );
    //SDL_FreeSurface( message );
    
    //Close the font that was used
    TTF_CloseFont( font );
    
    //Quit SDL_ttf
    TTF_Quit();
    
    //Quit SDL
    SDL_Quit();
}


void key_process(){
	
	while ( SDL_WaitEvent(&event) >= 0 ) {
		
        switch (event.type) 
		{
		case SDL_ACTIVEEVENT:
			
			if ( event.active.state & SDL_APPACTIVE ) {
				if ( event.active.gain ) {
					printf("App activated\n");
				} else {
					printf("App iconified\n");
				}
			}
			
			break;
		case SDL_MOUSEMOTION:
			
			if(leftbtnflage){	
				map[drawy][drawx]=1;
				if(!drawpathflage){
					draw_map();
					if( SDL_Flip( screen ) == -1 )
					{
						return ;    
					}
				}
				
				
			}else if(rightbtnflage){
				
				map[drawy][drawx]=0;
				if(!drawpathflage){
					draw_map();
					if( SDL_Flip( screen ) == -1 )
					{
						return ;    
					}
				}
				
				
			}
			drawx=(event.motion.x-30)/31;
			drawy=(event.motion.y-30)/31;
			
			break;
		case SDL_MOUSEBUTTONDOWN: 
			
			Uint8 *keys;
			
			keys = SDL_GetKeyState(NULL);
			if ( keys[SDLK_ESCAPE] == SDL_PRESSED ) {
				printf("Bye bye...\n");
				exit(0);
			}
			if(!drawpathflage)
			{
				
				switch(event.button.button)
				{
				case SDL_BUTTON_LEFT:
					leftbtnflage=true;
					//printf("x:%d y:%d\n",(event.motion.x-30)/31,(event.motion.y-30)/31);
					map[drawy][drawx]=1;
					draw_map();
					if( SDL_Flip( screen ) == -1 )
					{
						return ;    
					} 
					
					
					break;
				case SDL_BUTTON_RIGHT:
					rightbtnflage=true;
					map[drawy][drawx]=0;
					draw_map();
					if( SDL_Flip( screen ) == -1 )
					{
						return ;    
					} 
					break;
					
				}
			}
			break;
		case SDL_MOUSEBUTTONUP: 
			if(!drawpathflage)
			{
				switch(event.button.button)
				{
				case SDL_BUTTON_LEFT:
					leftbtnflage=false;
					//printf("x:%d y:%d\n",(event.motion.x-30)/31,(event.motion.y-30)/31);
					//map[(event.motion.y-30)/31][(event.motion.x-30)/31]=1;
					draw_map();
					if( SDL_Flip( screen ) == -1 )
					{
						return ;    
					} 
					
					
					break;
				case SDL_BUTTON_RIGHT:
					rightbtnflage=false;
					//map[(event.motion.y-30)/31][(event.motion.x-30)/31]=0;
					draw_map();
					if( SDL_Flip( screen ) == -1 )
					{
						return ;    
					} 
					break;
					
				}
			}
			break;
		case SDL_KEYDOWN:
			switch(event.key.keysym.sym) 
			{
			case SDLK_r:
				make_random_map();
				
				printf("Random map...\n");
				clear_opentable();
				clear_closetable();
				step=0;
				message=leftMessage;
				isfirstdrawflage=true;
				drawpathflage=false;
				traceflage=false;
				break;
			case SDLK_m:
				save_map();
				break;
			case SDLK_l:
				read_map();
				break;
			case SDLK_p:
				print_map();
				break;
			case SDLK_c:
				isfirstdrawflage=false;
				break;
			case SDLK_s:
				isfirstdrawflage=true;
				break;
			case SDLK_F1:
				print_help();
				break;
			case SDLK_F2:
				clear_map();
				drawpathflage=false;
				traceflage=false;
				break;
			}
			break;
			case SDL_KEYUP:
				switch( event.key.keysym.sym )
				{
				case SDLK_a: 
					printf("Set as a start search.\n");
					do_astart_search();
					message=upMessage;
					break;
				case SDLK_w:
					printf("Set as a wide search.\n");
					do_wide_search();
					break;
					
				case SDLK_d:
					printf("Set as deep search.\n");
					do_deep_search();
					break;
				case SDLK_g:
					printf("Starting Serach....\n");
					do_search();
					break;
					
				case SDLK_t:  
					printf("Do trace...\n");
					message=downMessage;
					traceflage=true;
					drawpathflage=true;
					break;
				case SDLK_SPACE: 
					printf("Clear opentable closetable...\n");
					clear_opentable();
					clear_closetable();
					step=0;
					message=leftMessage;
					drawpathflage=false;
					isfirstdrawflage=true;
					traceflage=false;
					break;
				case SDLK_x: 
					printf("Draw path...\n");
					drawpathflage=true;
					traceflage=false;
					
					
				}
				//PrintKeyInfo( &event.key );
				break;	
				case SDL_QUIT: {
					printf("Quit requested, quitting.\n");
					exit(0);
							   }
					break;
		}
		
		
		
    }
}

int my_thread( void *data )
{
	
    while( quit == false )
    {
		
        SDL_WM_SetCaption( "Maze is running", NULL );
        SDL_Delay( 10 );
		
		SDL_WM_SetCaption( "Maze is running.", NULL );
		SDL_Delay( 100 );
        
		SDL_WM_SetCaption( "Maze is running..", NULL );
		SDL_Delay( 100);
        
		SDL_WM_SetCaption( "Maze is running...", NULL );
		SDL_Delay( 100 );
		
		apply_surface( 0, 0, background, screen ,NULL);
		if( message != NULL )
		{
			
			apply_surface( 0, 0, message, screen,NULL );	
			message = NULL;
		}
		apply_surface( 0, 0, infoMessage, screen,NULL );
		draw_map();
		if(traceflage){
			draw_trace();
			//isfirstdrawflage=false;
			//traceflage=false;
		}else if(drawpathflage){
			draw_path();
			//isfirstdrawflage=false;
			//drawpathflage=false;
		}
		
		if( SDL_Flip( screen ) == -1 )
		{
			return -1;    
		} 
    }
    
    return 0;    
}


void draw_map(){
	for(int i=0;i<MAZEROW;i++){
		for(int j=0;j<MAZECOL;j++){
			if(map[i][j]==0){
				apply_surface(30 +j*30+j, 30 +i*30+i,noblock,screen,NULL);
			}else{
				apply_surface(30 +j*30+j, 30 +i*30+i,block,screen,NULL);
			}
			
			
		}
	}
	apply_surface(30 +endx*30+endx,30 +endy*30+endy,endimg,screen,NULL);
	apply_surface(30 +startx*30+startx, 30 +starty*30+starty,startimg,screen,NULL);
	
	
}

SDL_Surface *load_image(char* filename){
	SDL_Surface* loadedImage=NULL;
	SDL_Surface* optimizedImage=NULL;
	loadedImage=SDL_LoadBMP(filename);
	if(loadedImage!=NULL){
		optimizedImage = SDL_DisplayFormat( loadedImage );
		SDL_FreeSurface( loadedImage );
	}
	return optimizedImage;
	
}


bool load_files()
{
    //Load the background image
    background = load_image( "background.png" );
    
    //Open the font
    font = TTF_OpenFont( "lazy.ttf", 28 );
    
    //If there was a problem in loading the background
    if( background == NULL )
    {
        return false;    
    }
    
    //If there was an error in loading the font
    if( font == NULL )
    {
        return false;
    }
    
    //If everything loaded fine
    return true;    
}

void save_map(){
	printf("Save map in 1.map\n");
	FILE *fp;
    if((fp=fopen("1.map","wb"))==NULL)
    {
        printf("can not open file.\n");
		
        return;
    }
	for(int i=0;i<MAZECOL;i++){
		for(int j=0;j<MAZEROW;j++){
			fprintf(fp,"%d ",map[i][j]);
		}
		fprintf(fp,"\n");
	}
	
	fclose(fp);
	
}
void read_map(){
	printf("Open map 1.map\n");
	FILE *fp;
    if((fp=fopen("1.map","rb"))==NULL)
    {
        printf("can not open file.\n");
		
        return;
    }
	for(int i=0;i<MAZECOL;i++){
		for(int j=0;j<MAZEROW;j++){
			fscanf(fp,"%d ",map[i][j]);
		}
		fscanf(fp,"\n");
	}
	
	fclose(fp);
}

void print_help(){
	printf("=====================\n");
	printf("Key function table\n");
	printf("F1	help\n");
	printf("F2  clear map\n");
	printf("D	deep search\n");
	printf("A	a start search\n");
	printf("W	wide search\n");
	printf("S	step \n");
	printf("C	coninue\n");
	printf("L	load map\n");
	printf("M	save map\n");
	printf("SPASE clear tables and flags\n");
	printf("R	random map\n");
	printf("P	print map\n");
	printf("T	trace \n");
	printf("X	draw path\n");
	printf("G	go for search\n");
	printf("=====================\n\n");
}

void clear_map(){
	for(int i=0;i<MAZEROW;i++){
		for(int j=0;j<MAZECOL;j++){
			map[i][j]=0;
		}
	}
}