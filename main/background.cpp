#include "background.hpp"
using namespace std;

Background::Background(GameWindow *gw, vector <SDL_Texture*> *bgTex, float velocity){
    this->gwin = gw;
    this->bgTextures = bgTex;
    this->mVelY = velocity;
    this->mOffsetY = 0;
    this->mUpBgRect = {0, -SCREEN_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT};
    this->mDownBgRect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
}

void Background::reset(int stage){
    this->mVelY = INIT_VELOCITY + 30 * stage;
    this->mOffsetY = 0;
    this->mUpBgRect = {0, -SCREEN_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT};
    this->mDownBgRect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
}

void Background::render(){
    this->gwin->blit((*bgTextures)[whichBg[0]], mUpBgRect);
    this->gwin->blit((*bgTextures)[whichBg[1]], mDownBgRect);
}

void Background::update(float dTime){
    this->mOffsetY += this->mVelY * dTime;
    if (this->mOffsetY > SCREEN_HEIGHT){
        this->mOffsetY = 0;
        whichBg[1] = whichBg[0];
        whichBg[0] = rand() % 2;
    }
    // Continuously update the starting position (y) of the two backgrounds => scrolling
    this->mUpBgRect.y = this->mOffsetY - SCREEN_HEIGHT;
    this->mDownBgRect.y = this->mOffsetY;
}

void Background::setVelY(float velocity){
    this->mVelY = velocity;
}

float Background::getVelY(){
    return this->mVelY;
}
