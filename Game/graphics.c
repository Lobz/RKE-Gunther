#include "headers.h"

void applySurface(SDL_Surface *destination, SDL_Surface *source){
	if(destination && source)
		SDL_BlitSurface(source, NULL, destination, NULL);
}

SDL_Surface *loadBMP(char *file){
	SDL_Surface *image = NULL;
	char fullname[MAXLEN] = IMAGEDIR;

	strcat(fullname, file);

	image = SDL_LoadBMP(fullname);

	if(image == NULL){
		printf("File '%s' not found\n", file);
		return NULL;
    }

	/* Color key surface - background color is BR BG BB */
	SDL_SetColorKey( image, SDL_SRCCOLORKEY, SDL_MapRGB( image->format, BR, BG, BB ) );

	return image;
}



void applyDoubleInfoClip(SDL_Surface *destination, SDL_Surface *source, SDL_Rect clip[][2], int choice){
	if(destination && source && (int)clip[0][0].x != -1)
		SDL_BlitSurface(source, &(clip[choice][0]), destination, &(clip[choice][1]));
}




void loadDoubleInfoClip(char *file, SDL_Rect clip[][2]){
	int i, j, num;
	int x, y, w, h;
	SDL_Rect *p;
	FILE *F;
	char fullname[MAXLEN] = IMAGEDIR;
	
	strcat(fullname, file);

	F = fopen(fullname, "r");

	if(F == NULL){
		printf("File '%s' not found\n", file);
		clip[0][0].x = -1;
		return;
	}
	else{	
		fscanf(F, " %d", &num);
		for(i = 0; i < 2; i++){
			for(j = 0; j < num; j++){
				fscanf(F, " %d %d %d %d", &x, &y, &w, &h);
				p = &clip[j][i];
				p->x = x;
				p->y = y;
				p->w = w;
				p->h = h;
			}
		}
		fclose(F);
	}
}

void safeFreeSurface(SDL_Surface *dead){
	if(dead)
		SDL_FreeSurface(dead);
}

void applyClip( SDL_Surface *destination, SDL_Surface *source, int x, int y, SDL_Rect clip){
	SDL_Rect offset;
	if(destination && source && (int)clip.x != -1){
		offset.x = x;
		offset.y = y;
		SDL_BlitSurface (source, &clip, destination, &offset);
	}
}
	
void applyClipToBoard( SDL_Surface *destination, SDL_Surface *source, int board_x, int board_y, SDL_Rect clip){
	SDL_Rect offset;
	if(destination && source && (int)clip.x != -1){
		offset.x = board_x*TILE_WIDTH;
		offset.y = board_y*TILE_HEIGHT;
		offset.w = TILE_WIDTH;
		offset.h = TILE_HEIGHT;
		SDL_BlitSurface (source, &clip, destination, &offset);
	}
}
