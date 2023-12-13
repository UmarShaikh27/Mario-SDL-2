#pragma once
#include <SDL.h>

struct Playerstates{
    SDL_Rect srcRect,walkOne,walkTwo,walkThree;
    Playerstates() = default;
    Playerstates(SDL_Rect srcRect, SDL_Rect walkOne,SDL_Rect walkTwo,SDL_Rect walkThree):
                                                                                                                    srcRect(srcRect),
                                                                                                                    walkOne(walkOne),
                                                                                                                    walkTwo(walkTwo),
                                                                                                                    walkThree(walkThree)                                                                                                                    
                                                                                                                    {}
};