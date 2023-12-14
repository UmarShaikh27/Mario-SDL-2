#pragma once
#include <SDL.h>
#include <iostream>
#include "Playerstates.hpp"
#include <vector>
#include "Utility.hpp"
using namespace std;

class Mario{

public:
    SDL_Rect moverRect,healthrect;
    Playerstates* Data;
    Mario() = default;
    Mario(SDL_Rect mover,SDL_Rect health){
		moverRect = mover;
		healthrect = health;
		Data = rightface;
	}
    // string image="playerimg/redmanright.png";
                            
    // virtual void deletePlayer() = 0;     



    void checkjump() {
        // Handle jumping
        if(this->jumping) {
            Uint32 currentTime = SDL_GetTicks();
            Uint32 jumpDuration = currentTime - jumpStartTime;

            if (jumpDuration < JUMP_TIME) {
                // Move Mario upward during the first half of the jump
                moverRect.y -= JUMP_SPEED;
            } else {
                // Move Mario downward during the second half of the jump
                moverRect.y += JUMP_SPEED;
            }

            if (jumpDuration >= 2 * JUMP_TIME) {
                jumping = false;
            }
        }
        ////
        

        

    }

    void makeJump(){
        if(!jumping){
            Mix_PlayChannel(-1, jumpSound, 0);
            jumping = true;
            jumpStartTime = SDL_GetTicks();
        }
    }

    
    void changeState(){
        if(Data->srcRect.x == Data->walkOne.x && Data->srcRect.y == Data->walkOne.y){
            Data->srcRect = Data->walkTwo;
        }
        else if(Data->srcRect.x == Data->walkTwo.x && Data->srcRect.y == Data->walkTwo.y){
            Data->srcRect = Data->walkThree;
        }
        else{
            Data->srcRect = Data->walkOne;
        }
    }

    void decreaseHealth(){
        healthrect.w-=7;
    }
   

private:
    Playerstates* rightface= new Playerstates{{12,8,26,44},{12,8,26,44} , {42,8,26,44},  {72,8,26,44}};
    static const int MARIO_HEIGHT = 90;
    static const int MARIO_WIDTH = 50;
    bool onPlatform = false;
    // int x, y;
    // int xVel = 0;
    bool jumping = false;
    Uint32 jumpStartTime = 0;
    static const int JUMP_SPEED = 10; // Adjust the jump speed
    static const Uint32 JUMP_TIME = 900; // Adjust the jump duration in milliseconds
    Mix_Chunk* jumpSound = Mix_LoadWAV("Music/smb_jump.wav");
};