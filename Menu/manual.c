#include "manual.h"


int manual(SDL_Surface *screen,int mode){
	bool quit = false, quitman = false;
	int page, pagenum;
	char monsterFile[50];
	FILE *F;

	SDL_Event event;

	SDL_Surface *ManPage = NULL;
	SDL_Surface *Monsters[50];

	ManPage = loadBMP("ManPage.bmp");
	
	F = fopen("monsters.txt","r");
	if(F == NULL) return -90;

	for(pagenum = 0; fscanf(F," %s",monsterFile) != EOF; pagenum++){
		Monsters[pagenum] = loadBMP(monsterFile);
	}

	fclose(F);

	page = 0;
	while(quitman == false){
		
		while(SDL_PollEvent(&event)){
			if(event.type == SDL_QUIT){
				quit = true;
				quitman = true;
				break;
			}
			else if(event.type == SDL_KEYDOWN){
				switch(event.key.keysym.sym){
					case SDLK_LEFT:
						if(page > 0) page--;
						break;
					case SDLK_RIGHT:
						if(page+1 < pagenum) page++;
						break;
					case SDLK_RETURN:
						quitman = true;
						break;
					case SDLK_ESCAPE:
						quitman = true;
						quit = true;
						break;
					default:;
				}
			}
		}

		applySurface(screen,ManPage);
		applySurface(screen,Monsters[page]);
		SDL_Flip(screen);
	}

	safeFreeSurface(ManPage);

	for(page = 0; page < pagenum; page++){
		safeFreeSurface(Monsters[page]);
	}

	if(quit)
		return QUIT;

	else
		return TITLE;
}

/*		Page = getManPage(data,chapter,page);

		applySurface(screen,Page->image);

		if(pressEnter) function(selectedButton);

		if(mouseClick)
			for(i = 0; i < Page->buttonNum; i++){
				if(hitButton(Page->button[i]))
					function(i);
*/		
		
