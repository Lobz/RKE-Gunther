#include "headers.h"

bool initSDL(SDL_Surface **screen){
	
	if( SDL_Init(SDL_INIT_EVERYTHING) == -1){
		return false;		
	}

	*screen = SDL_SetVideoMode(WIDTH, HEIGHT, RESOLUTION, SDL_SWSURFACE);

	if(*screen == NULL){
		return false;
	}

	return true;

void applySurface(SDL_Surface *source, SDL_Surface *destination){
	SDL_BlitSurface(source, NULL, destination, NULL);
}

void applyClip(SDL_Surface *source, SDL_Surface *destination, SDL_Rect clip, int choice){
	SDL_BlitSurface(source,&clip[CLIPSOURCE][choice],destination, &clip[CLIPDEST][choice]);
}

SDL_Surface *loadBMP(char *file){
	SDL_Surface *image = NULL;

	image = SDL_LoadBMP(file);

	return image;
}

void loadClip(char *file, SDL_Surface *image, SDL_Rect *clip){
	int i,j,n;
	FILE *F;

	F = fopen(file,"r");

	if(F == NULL){
		printf("File %s not found\n",file);
		return;
	}

	fscanf(F," %d",&n);
	for(i = 0; i < 2; i++){
		for(j = 0; j < n; j++){
			fscanf(F," %d %d %d %d",&(clip[i][j].x), &(clip[i][j].y), &(clip[i][j].w), &(clip[i][j].h));
		}
	}
	
	fclose(F);
}
				
