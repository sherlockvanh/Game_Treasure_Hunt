#include "Common_Function.h"
#include "LoadObject.h"
#include "Character.h"
#include "MainCharacter.h"
#include "Enemy.h"
#include "Weapon.h"
#include "TextObject.h"
#include "Map1.h"
#include "Map2.h"
#include "Map4.h"
bool create_GRenderer() {
    GRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
                                      SDL_RENDERER_PRESENTVSYNC);

    if (GRenderer == nullptr) {
            logSDLError(std::cout, "CreateRenderer", true);
            return false;
    }
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(GRenderer, SCREEN_WIDTH, SCREEN_HEIGHT);
    return true;
}
bool create_PNG(){
    SDL_SetRenderDrawColor( GRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)){
        logSDLError(std::cout, "SDL_image could not be initialized", true);
        return false;
    }
    return true;
}
bool initSDL(SDL_Window* &window) {
    bool success = true;
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
        logSDLError(std::cout, "SDL_Init", true);
        return false;
    }
    else {
        window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,
           SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (window == NULL) {
            logSDLError(std::cout, "CreateWindow", true);
            return false;
        }
        else {
            success = create_GRenderer();
            if (! success) return false;
            success = create_PNG();
            if (! success) return false;
            if( TTF_Init() == -1 ){
                logSDLError(std::cout, "TTF could not be initialized", true);
                return false;
            }
        }
    }
    return true;
}
void close(){
    BackGround[4].free();
    SDL_DestroyRenderer(GRenderer);
    SDL_DestroyWindow(window);
    window = NULL;
	GRenderer = NULL;
	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}
bool loadFont(){
    gFont = TTF_OpenFont( "font/OpenSans-Regular.ttf", 15);
    LFont = TTF_OpenFont( "font/OpenSans-ExtraBold.ttf", 25);
	if( gFont == NULL )
	{
		printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
		return false;
	}
	return true;
}
bool loadMedia() {
    RMap = {0, 0, 1120, 630};
    return loadFont();

}
void LoadMap3(){
   BackGround[3].loadFromFile("GameHKI/Map3/Map33.png", GRenderer);
}
void CloseMap3(){}
void Intro3(){};
void RunMap3(){
    LoadMap3();
    Intro3();
    SDL_RenderClear(GRenderer);
    BackGround[3].render(0, 0, GRenderer, NULL);
    SDL_RenderPresent(GRenderer);
    SDL_Delay(5000);
}
void Loading(){
    LoadObject loading;
    TextObject Percent;
    loading.loadFromFile("GameHKI/lock.png", GRenderer);
    Percent.SetColor(TextObject::WHITE_TEXT);
    Uint64 stime = SDL_GetTicks64();
    int cur = 0;
    string str_val;
    while (cur != 100){
        if (SDL_GetTicks64() - stime >= 20){
            SDL_RenderClear(GRenderer);
            loading.render(0, 0, GRenderer, NULL);
            cur++;
            str_val = std::to_string(cur);
            str_val += "%";
            Percent.setText(str_val);
            Percent.LoadFromRenderText(LFont, GRenderer);
            Percent.RenderText(GRenderer, 532, 575);
            stime = SDL_GetTicks64();
            SDL_RenderPresent(GRenderer);
        }
    }
    loading.free(); Percent.Free();
}
bool LoadMainMenu(){
    LoadObject Start, Quit; SDL_Rect Rstart, Rquit;
    BackGround[0].loadFromFile("GameHKI/welcome.png", GRenderer);
    Start.loadFromFile("GameHKI/Start.png", GRenderer);
    Quit.loadFromFile("GameHKI/Quit.png", GRenderer);
    Rstart = {0, 0, 128, 64}; Rquit = {0, 0, 128, 64};
    bool Running = true;
    int x, y, inside = 0;
    SDL_Event e;
    while (Running){
        while( SDL_PollEvent( &e ) != 0 ){
            //User requests quit
            if( e.type == SDL_QUIT ){
                Running = false;
            }
            //Handle button events
            if(e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP){
                SDL_GetMouseState(&x, &y);
                inside = 0;
                if (x >= 300 && x <= 428 && y >= 500 && y <= 564) inside = 1;
                if (x >= 630 && x <= 758 && y >= 500 && y <= 564) inside = 2;
                if (e.type == SDL_MOUSEBUTTONDOWN && inside) {
                    if (inside == 1) Rstart.x = 128;
                    else Rquit.x = 128;
                }
                else {
                    Rstart.x = 0; Rquit.x = 0; inside = 0;
                }
            }
        }
        SDL_RenderClear(GRenderer);
        BackGround[0].render(0, 0, GRenderer, &RMap);
        Start.render(300, 500, GRenderer, &Rstart);
        Quit.render(630, 500, GRenderer, &Rquit);
        SDL_RenderPresent(GRenderer);
        if (inside) {
            SDL_Delay(500);
            break;
        }
    }
    BackGround[0].free(); Start.free(); Quit.free();
    return (inside == 1);
}
void LoadGameOver(){
    LoadObject Gover;
    SDL_RenderClear(GRenderer);
    Gover.loadFromFile("GameHKI/GameOver.png", GRenderer);
    Gover.render(0, 0, GRenderer, NULL);
    SDL_RenderPresent(GRenderer);
    SDL_Delay(1000);
    Gover.free();
}
int main(int argc, char* argv[])
{
    if (! initSDL(window)) {
        logSDLError(cout, "Can not initialize \n", 1);
    }
    else{
        WindowSurface = SDL_GetWindowSurface(window);
//    // Your drawing code here
//    // use SDL_RenderPresent(renderer) to show it
        if (!loadMedia()){
            logSDLError(cout, "Can not load media \n", 1);
        }
        else {
            bool Running = true;
            while (Running){
                if (LoadMainMenu()){
                    Loading();
//                    if (! RunMap1(GRenderer, gFont)) {
//                        SDL_Delay(1000);
//                        LoadGameOver();
//                        continue;
//                    }
//                    SDL_Delay(2000);
//                    CloseMap1();
//                    Loading();
//                    if (! RunMap2(GRenderer, LFont)){
//                        SDL_Delay(1000);
//                        LoadGameOver();
//                        CloseMap2(GRenderer);
//                        continue;
//                    }
//                    SDL_Delay(2000);
//                    CloseMap2();
//                    Loading();
 //                   RunMap3();
                      RunMap4(GRenderer, gFont);

                }
                else {

                    break;
                }
               // Loading();
    //            if (RunMap1()){
    //                Loading();
    //            }
//                if (RunMap4()){
//                    cout << "win";
//                }
//                else cout << "ga vai lon";
//                SDL_SetRenderDrawColor( GRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
//                SDL_RenderClear(GRenderer);
//                LoadBackGround("GameHKI/GameOver.png", GRenderer);
//                BackGround4.render(0, 0, GRenderer, &Map4);
//                SDL_RenderPresent(GRenderer);
//                SDL_Delay(5000);
            }
        }
    }
    return 0;
}
