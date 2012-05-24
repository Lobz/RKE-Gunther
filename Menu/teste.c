#include "headers.h"

int main(){
	SDL_Surface *screen = NULL;
	SDL_Surface *image1 = NULL, *image2 = NULL;
	SDL_Event event;
	bool quit = false;

	SDL_Init(SDL_INIT_EVERYTHING);

	screen = SDL_SetVideoMode(WIDTH,HEIGHT,RESOLUTION,SDL_SWSURFACE);

	if(screen == NULL) return 1;

	image1 = loadBMP("TitleText.bmp");
	image2 = loadBMP("TitleBackground.bmp");

	if(image1 == NULL || image2 == NULL) return 2;

	applySurface(image1,image2);
	SDL_BlitSurface(image2,NULL,screen,NULL);

	SDL_Flip(screen);

    //While the user hasn't quit
    while( quit == false )
    {
        //While there's an event to handle
        while( SDL_PollEvent( &event ) )
        {
            //If the user has Xed out the window
            if( event.type == SDL_QUIT )
            {
                //Quit the program
                quit = true;
            }
        }
    }

	SDL_FreeSurface(image1);
	SDL_Quit();
	return 0;
}
