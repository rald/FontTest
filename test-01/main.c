#include <stdlib.h>
#include <stdarg.h>
#include <stdbool.h>
#include <time.h>




#include "palette.h"
#include "font.h"

#define GRAPHICS_IMPLEMENTATION
#include "graphics.h"



#define GAME_TITLE "SDL Test"

#define PIXEL_SIZE 2
#define BUF_WIDTH 40
#define BUF_HEIGHT 25

#define SCREEN_WIDTH FONT_WIDTH*BUF_WIDTH*PIXEL_SIZE
#define SCREEN_HEIGHT FONT_HEIGHT*BUF_HEIGHT*PIXEL_SIZE

SDL_Texture *texture;
bool quit = false;	

int r=0,g=0,b=0;

unsigned char buf[BUF_WIDTH*BUF_HEIGHT];int bufx=0;
int bufy=0;




void die(int c,char *f,...) {
	va_list a;
	va_start(a,f);
	vprintf(f,a);
	va_end(a);	
	exit(c);
}



int sgn(int x) {
	return x<0?-1:x>0?1:0;
}


int rnd(int x) {
	return rand()%x;
}


void SDL_RenderDrawChar(SDL_Renderer *renderer,unsigned char *f,int w,int h,int ch,int x,int y,int s,SDL_Color fg,SDL_Color bg) {
	for(int j=0;j<h;j++) {
		for(int i=0;i<w;i++) {
			int k=f[ch*w*h+j*w+i];
			if(k==1) {
				SDL_SetRenderDrawColor(renderer,fg.r,fg.g,fg.b,fg.a);
				SDL_RenderFillRect(renderer,&(SDL_Rect){i*s+x,j*s+y,s,s});
			} else {
				SDL_SetRenderDrawColor(renderer,bg.r,bg.g,bg.b,bg.a);
				SDL_RenderFillRect(renderer,&(SDL_Rect){i*s+x,j*s+y,s,s});
			}
		}
	}	
}


int main(void) {

	srand(time(NULL));



	SDL_Screen(GAME_TITLE,SCREEN_WIDTH,SCREEN_HEIGHT);

	texture = SDL_CreateTexture(renderer,SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, SCREEN_WIDTH, SCREEN_HEIGHT);

	SDL_SetTextureBlendMode(texture,SDL_BLENDMODE_BLEND);

		SDL_SetRenderDrawColor( renderer, 0x00, 0x00, 0x00, 0x08 );

		SDL_RenderFillRect(renderer,&(SDL_Rect){0,0,SCREEN_WIDTH,SCREEN_HEIGHT});

	while( !quit ) {

		while( SDL_PollEvent( &event ) != 0 ) {
			if( event.type == SDL_QUIT ) {
				quit = true;
			}
		}

		SDL_SetRenderTarget(renderer,texture);

		r=rnd(256);
		g=rnd(256);
		b=rnd(256);


		SDL_SetRenderDrawColor( renderer, r, g, b, 255 );



		SDL_RenderDrawChar(renderer,font_pixels,FONT_WIDTH,FONT_HEIGHT,rnd(128),rnd(BUF_WIDTH)*FONT_WIDTH*PIXEL_SIZE,rnd(BUF_HEIGHT)*FONT_HEIGHT*PIXEL_SIZE,PIXEL_SIZE,palette[rnd(16)],palette[rnd(16)]);



		SDL_SetRenderTarget(renderer,NULL);
		SDL_RenderCopy(renderer,texture,NULL,NULL);		
		SDL_RenderPresent( renderer );
		
	}

	SDL_DestroyTexture( texture );
	SDL_DestroyRenderer( renderer );
	SDL_DestroyWindow( window );

	SDL_Quit();

	return 0;
}


