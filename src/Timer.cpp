/* Timer
 * Pseudo timer that returns true if the timeToWait has elapsed based on the current time
 * USes SDL_GetTicks() to get the system time
 */

class Timer{
    
private:
	Uint32 timer = 0;
    bool timerRunning = false;
    Uint32 interval; // Time to wait 
public:    
    
    void start(Uint32 timeToWait)
    {
        timerRunning = true;
        interval = timeToWait;
        timer = SDL_GetTicks();
    }

    bool isDone()
    {
        if(!timerRunning) return true;
        Uint32 currTime = SDL_GetTicks();
        if((currTime - timer) >= interval){
            timerRunning = false;
            return true;
        }else return false;
    }
    
    void reset()
    {
        timerRunning = true;
        interval = SDL_GetTicks();
    }
    
    
};
