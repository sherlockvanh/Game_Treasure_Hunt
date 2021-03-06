#ifndef COMMON_FUNCTION_H
#define COMMON_FUNCTION_H

#include <iostream>
#include <fstream>
#include <chrono>
#include <random>
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <Windows.h>
#include <string.h>
#include <vector>
#include <algorithm>
#include "Object.h"
#include "TextObject.h"
#include "LoadObject.h"
#include "MainCharacter.h"
#define pii pair<int, int>
#define piii pair <int, pii >
#define mp make_pair
#define fi first
#define se second
using namespace std;
const int SCREEN_WIDTH = 1120;
const int SCREEN_HEIGHT = 630;
const std::string WINDOW_TITLE = "Treasure Hunt";
const int MainFrames = 6;
const int EnemyFrames = 9;
const int ArrowFrames = 2;
const int MainSpeed = 5;
const int ArrowSpeed = 4;
const int MainHp = 25;
const int ArrowDamn = 2;
const int CharacterH = 56;
const int CharacterW = 40;
static MainCharacter Explorer;
static TTF_Font *gFont = NULL, *LFont = NULL ;
static TextObject showNum;
static LoadObject BackGround[5],result[2];
static SDL_Surface *WindowSurface = NULL;
static SDL_Window *window = NULL;
static SDL_Renderer* GRenderer = NULL;
void logSDLError(std::ostream& os, const std::string &msg, bool fatal);
int getDistance(int x, int y, int u, int v);
bool Intersect(int x, int y, int h, int w, int x2, int y2, int h2, int w2);
static mt19937_64 rng(chrono::high_resolution_clock::now().time_since_epoch().count());
long long Rand(long long l, long long r);

#endif // COMMON_FUNCTION_H
