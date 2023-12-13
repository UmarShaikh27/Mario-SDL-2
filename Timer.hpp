#include <iostream>
#include <SDL.h>
class Timer {
public:
    Timer() : startTicks(0), pausedTicks(0), paused(false), started(false) {}
    // Timer start
    void start() {
        started = true;
        paused = false;
        startTicks = SDL_GetTicks();
    }

    // Timer stop
    void stop() {
        started = false;
        paused = false;
    }

    // Pause timer and game
    void pause() {
        if (started && !paused) {
            paused = true;
            pausedTicks = SDL_GetTicks() - startTicks;
        }
    }

    // Resume timer and game
    void resume() {
        if (paused) {
            paused = false;
            startTicks = SDL_GetTicks() - pausedTicks;
            pausedTicks = 0;
        }
    }

    // Get the current time on the timer
    Uint32 getTicks() const {
        Uint32 time = 0;

        if (started) {
            if (paused) {
                time = pausedTicks;
            } else {
                time = SDL_GetTicks() - startTicks;
            }
        }

        return time;
    }

    // Check if the timer is started
    bool isStarted() const {
        return started;
    }

    // Check if the timer is paused
    bool isPaused() const {
        return paused && started;
    }

private:
    Uint32 startTicks;   // The ticks recorded when the timer starts
    Uint32 pausedTicks;  // The ticks recorded when the timer is paused
    bool paused;         // Flag indicating whether the timer is paused
    bool started;        // Flag indicating whether the timer is started
};
