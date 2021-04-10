#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <chrono>


uint8_t pixels[32 * 224] = {true};
uint8_t scale = 2;
const int width = 256 * scale;
const int height = 224 * scale;

SDL_Surface* gWindowSurface = NULL;
SDL_Renderer* gRenderer = NULL;
SDL_Window* gWindow = NULL;

bool setupGraphics();
void drawGraphics();
void close();

bool onlyOnce = true;

int main(){
	if(!setupGraphics()){return 1;}

	bool quit = false;
	SDL_Event e;
	srand( 3);
	printf("Ready!\n");
	while(!quit){
	while(SDL_PollEvent(&e) != 0){
		if(e.type == SDL_QUIT){ quit=true;break;}
		else if(e.type == SDL_KEYDOWN){
			if((e.key.keysym.sym == SDLK_SPACE) && onlyOnce){
				//onlyOnce=false;
				drawGraphics();
			}
		}
	}


	}
	close();
	return 0;
}

bool setupGraphics(){
	bool success = true;

	if(SDL_Init(SDL_INIT_VIDEO) < 0){
		printf("Could not initialise SDL: %s\n", SDL_GetError());
		success = false;
	} else {
		gWindow = SDL_CreateWindow("Rendering efficiency test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
		if(gWindow == NULL){
			printf("Cant create window: %s\n", SDL_GetError());
			success = false;
		} else {
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if(gRenderer == NULL){
				printf("Cant create renderer: %s\n", SDL_GetError());
				success = false;
			}
		}
	}
	for(int x=0;x<(32*224);++x){pixels[x]=0xFF;}
	return success;
}

void drawGraphics(){
	printf("Rendering!\n");
	std::chrono::high_resolution_clock::time_point ts = std::chrono::high_resolution_clock::now();
	//drawing stuff	
	SDL_SetRenderDrawColor( gRenderer, 0xFF, 0x00, 0xDD, 0xFF);
	SDL_RenderClear(gRenderer);
	
	SDL_Rect pixel = {0,0,scale,scale};
	for(int y = 0; y < 224; ++y){
		for(int x = 0; x < 32; ++x){
			for(uint8_t shift = 0; shift < 8; ++shift){
 				if(pixels[y*32+x] & (0x80 >> shift)){
					SDL_SetRenderDrawColor(gRenderer, (rand() % 255), (rand() % 255), (rand() % 255),0xFF);
					//printf("X: %d | Y: %d | shift: %d\n", x, y, shift);
					pixel.x = (x * 8 + shift) * scale;
					pixel.y = y * scale;
					SDL_RenderFillRect( gRenderer, &pixel);
				}
			}
		}
	}
	SDL_RenderPresent(gRenderer);

	std::chrono::high_resolution_clock::time_point te = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(te-ts);
	printf("Time taken: %f\n", time_span.count());
}

void close(){
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	SDL_DestroyRenderer(gRenderer);
	gRenderer = NULL;
	SDL_Quit;
}
