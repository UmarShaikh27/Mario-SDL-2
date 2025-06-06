#pragma once
#include <SDL.h>
#include <iostream>
#include "Playerstates.hpp"
#include <vector>
#include "Utility.hpp"
using namespace std;

/**
 * Mario class
 * Represents the player character with:
 * - Movement controls and animation
 * - Health and score tracking
 * - Jumping mechanics
 * - Collision response
 */
class Mario{

public:
    SDL_Rect moverRect,healthrect;  // Position/collision and health bar rectangles
    Playerstates* Data;             // Current animation state

    // Constructors
    Mario() = default;
    /**
     * Constructor: Initialize Mario with position and health bar
     * @param mover Position and size rectangle
     * @param health Health bar rectangle
     */
    Mario(SDL_Rect mover,SDL_Rect health){
		moverRect = mover;
		healthrect = health;
		Data = rightface;
        score = 0;
	} 



    /**
     * Updates Mario's vertical position during jumps
     * - First half of jump: Moving upward
     * - Second half: Falling back down
     */
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
   

    }
    /**
     * Increases score when collecting coins
     * Returns: true if winning score reached
     */
    bool increaseScore(){
        score+=5;
        Mix_PlayChannel(-1, coinSound, 0);
        if(score>=25){
            return true;
        }
        return false;
    }

    /**
     * Initiates a jump if not already jumping
     * Plays jump sound effect
     */
    void makeJump(){
        if(!jumping){
            Mix_PlayChannel(-1, jumpSound, 0);
            jumping = true;
            jumpStartTime = SDL_GetTicks();
        }
    }


    /**
     * Updates walking animation state
     * Cycles through three walking frames
     */
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

    /**
     * Reduces health when hit by obstacles
     * Returns: true if health depleted
     */
    bool decreaseHealth(){
        healthrect.w-=60;
        moverRect.x-=3;
        Mix_PlayChannel(-1, hitSound, 0);
        if(healthrect.w<=0){
            return true;
        }
        return false;

    }
    /**
     * Destructor: Cleans up audio resources
     */
    ~Mario(){
        Mix_FreeChunk(jumpSound);
        Mix_FreeChunk(hitSound);
        Mix_FreeChunk(coinSound);
    }
   

private:
    int score;                      // Current coin collection score
    Playerstates* rightface= new Playerstates{{12,8,26,44},{12,8,26,44} , {42,8,26,44},  {72,8,26,44}};        // Animation frames data
    static const int MARIO_HEIGHT = 90;
    static const int MARIO_WIDTH = 50;
    bool onPlatform = false;
    // int x, y;
    // int xVel = 0;
    bool jumping = false;           // Current jumping state
    Uint32 jumpStartTime = 0;       // Timestamp when jump started
    static const int JUMP_SPEED = 10; // Adjustable jump speed
    static const Uint32 JUMP_TIME = 900; // Jump duration in miliseconds
    Mix_Chunk* jumpSound = Mix_LoadWAV("Music/smb_jump.wav");
    Mix_Chunk* hitSound = Mix_LoadWAV("Music/smb_bump.wav");
    Mix_Chunk* coinSound = Mix_LoadWAV("Music/smb_coin.wav");
};