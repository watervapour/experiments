#include <SDL.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <chrono>


const int width = 800;
const int height = 640;

char data[0x2000];
int8_t ramPage = 0;
uint8_t rowCount = 32;
uint8_t colCount = 32;
uint8_t pageCount = 8;
uint16_t pageElementCount;

SDL_Surface* gWindowSurface = NULL;
SDL_Renderer* gRenderer = NULL;
SDL_Window* gWindow = NULL;

bool setupGraphics();
void drawGraphics();
void close();

bool onlyOnce = true;

int main(int argc, char** argv){
	if(!setupGraphics()){return 1;}

	bool quit = false;
	SDL_Event e;
	srand( 3);
	printf("Ready!\n");
	drawGraphics();
	while(!quit){
	while(SDL_PollEvent(&e) != 0){
		if(e.type == SDL_QUIT){ quit=true;}
		else if(e.type == SDL_KEYDOWN){
			if((e.key.keysym.sym == SDLK_SPACE) && onlyOnce){
				drawGraphics();
			} else if (e.key.keysym.sym == SDLK_q){ quit = true; 
			} else if (e.key.keysym.sym == SDLK_RIGHT){ 
				ramPage++; 
				if(ramPage == pageCount)
					ramPage = 0;
				drawGraphics();
			} else if (e.key.keysym.sym == SDLK_LEFT){ 
				ramPage--; 
				if(ramPage < 0)
					ramPage = (pageCount - 1);
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
		gWindow = SDL_CreateWindow("Text", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
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

	pageElementCount = rowCount * colCount;	
	TTF_Init();
	return success;
}

void drawGraphics(){
	data[rand()%0x2000] += 1;

	printf("Rendering!\n");
	std::chrono::high_resolution_clock::time_point ts = std::chrono::high_resolution_clock::now();

	SDL_SetRenderDrawColor( gRenderer, 0x10, 0x10, 0x10, 0xFF);
	SDL_RenderClear(gRenderer);

	TTF_Font* font = TTF_OpenFont("font.ttf", 12);
	SDL_Color fontColor = {200, 200, 255};

	// addr + ": " + "val "
	char text[6 + 2 + (3 * colCount)];
	
	
	//printf("text length: %d\n", ( sizeof(text)/sizeof(text[0]) ));

	for(int i=0;i<(sizeof(text)/sizeof(text[0])); ++i ){
		//printf("text[%d] = %dd, %Xh\n", i, text[i], text[i]);
		text[i] = 'x';
	}
	

	text[0] = ' ';
	text[1] = ' ';
	text[2] = ' ';
	text[3] = ' ';
	text[4] = ' ';
	text[5] = ' ';
	text[6] = ' ';
	text[7] = ' ';
	for(int col = 0; col < colCount; ++col){
		char upperByte = (col & 0xF0) >> 4;
		char lowerByte = (col & 0x0F);
		upperByte += (upperByte < 10)? 48 : 55;
		lowerByte += (lowerByte < 10)? 48 : 55;
		text[8 + 3*col] = upperByte;
		text[8 + 3*col + 1] = lowerByte;
		text[8 + 3*col + 2] = ' ';	
	}

	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, text, fontColor);
	SDL_Texture* message = SDL_CreateTextureFromSurface(gRenderer, surfaceMessage);
	
	int sWidth = surfaceMessage->w;
	int sHeight = surfaceMessage->h;
	SDL_Rect mRect;
	mRect.x = 0;
	mRect.y = 0;
	mRect.w = sWidth;
	mRect.h = sHeight;
	printf("dimensions: %dw, %dh\n", mRect.w, mRect.h);
	SDL_FreeSurface(surfaceMessage);
	SDL_RenderCopy(gRenderer, message, NULL, &mRect);



	uint16_t startAddr = 0x0000;
	for(int row = 0; row < rowCount; ++row){
		//printf("row: %X ", row);
		uint16_t trueRow = (row * colCount) + (pageElementCount *  ramPage);
		//set preheader
		text[0]='0';text[1]='x';
		text[2]=((trueRow & 0xF000)>>12) + ((((trueRow & 0xF000) >> 12) < 10) ? 48 : 55);	
		text[3]=((trueRow & 0x0F00)>>8)  + ((((trueRow & 0x0F00) >> 8) < 10) ? 48 : 55);	
		text[4]=((trueRow & 0x00F0)>>4)  + ((((trueRow & 0x00F0) >> 4) < 10) ? 48 : 55);	
		text[5]=((trueRow & 0x000F))	 + ((((trueRow & 0x000F)) < 10) ? 48 : 55);
		text[6]=':';
		text[7]=' ';
		for(int col = 0; col < colCount; ++col){
			//printf("col: %X ", col);
			uint16_t val = trueRow + col;
			//printf("val: %d\n", val);
			char upperByte = (data[val] & 0xF0) >> 4;
			char lowerByte = (data[val] & 0x0F);
			upperByte += (upperByte < 10)? 48 : 55;
			lowerByte += (lowerByte < 10)? 48 : 55;
			text[8 + 3*col] = upperByte;
			text[8 + 3*col + 1] = lowerByte;
			text[8 + 3*col + 2] = ' ';	
		}
		SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, text, fontColor);
		SDL_Texture* message = SDL_CreateTextureFromSurface(gRenderer, surfaceMessage);
		
		int sWidth = surfaceMessage->w;
		int sHeight = surfaceMessage->h;
		SDL_Rect mRect;
		mRect.x = 0;
		mRect.y = row*12 + 12;
		mRect.w = sWidth;
		mRect.h = sHeight;
		SDL_FreeSurface(surfaceMessage);
		SDL_RenderCopy(gRenderer, message, NULL, &mRect);
		
		//for(int i =0;i<520;++i){printf("val[%d] = %d\n", (i), text[i]);	}
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
