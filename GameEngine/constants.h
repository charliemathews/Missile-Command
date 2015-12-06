// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Chapter 6 constants.h v1.1

#ifndef _CONSTANTS_H            // Prevent multiple definitions if this 
#define _CONSTANTS_H            // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include <windows.h>

//=============================================================================
// Function templates for safely dealing with pointer referenced items.
// The functions defined by these templates may be called using a normal
// function call syntax. The compiler will create a function that replaces T
// with the type of the calling parameter.
//=============================================================================
// Safely release pointer referenced item
template <typename T>
inline void safeRelease(T& ptr)
{
    if (ptr)
    { 
        ptr->Release(); 
        ptr = NULL;
    }
}
#define SAFE_RELEASE safeRelease            // for backward compatiblility

// Safely delete pointer referenced item
template <typename T>
inline void safeDelete(T& ptr)
{
    if (ptr)
    { 
        delete ptr; 
        ptr = NULL;
    }
}
#define SAFE_DELETE safeDelete              // for backward compatiblility

// Safely delete pointer referenced array
template <typename T>
inline void safeDeleteArray(T& ptr)
{
    if (ptr)
    { 
        delete[] ptr; 
        ptr = NULL;
    }
}
#define SAFE_DELETE_ARRAY safeDeleteArray   // for backward compatiblility

// Safely call onLostDevice
template <typename T>
inline void safeOnLostDevice(T& ptr)
{
    if (ptr)
        ptr->onLostDevice(); 
}
#define SAFE_ON_LOST_DEVICE safeOnLostDevice    // for backward compatiblility

// Safely call onResetDevice
template <typename T>
inline void safeOnResetDevice(T& ptr)
{
    if (ptr)
        ptr->onResetDevice(); 
}
#define SAFE_ON_RESET_DEVICE safeOnResetDevice  // for backward compatiblility

//=============================================================================
//                  Constants
//=============================================================================

// window
const char CLASS_NAME[] = "The Llamas Are Coming";
const char GAME_TITLE[] = "The Llamas Are Coming";
const bool FULLSCREEN = false;              // windowed or fullscreen
const UINT GAME_WIDTH =  800;               // width of game in pixels
const UINT GAME_HEIGHT = 600;               // height of game in pixels
const int COLS = 18;
const int ROWS = 4;
const int MAX_ROCKETS = 5;
const int MAX_ALIENS = 10;
const int MAX_ASTEROIDS = 10;
const int MAX_CITIES = 4;
const int GAME_END_TIME = 120000;
const float MAX_PARTICLE_LIFETIME = 1.5f;
const int MAX_NUMBER_PARTICLES = 500;
// game
const double PI = 3.14159265;
const float FRAME_RATE = 200.0f;                // the target frame rate (frames/sec)
const float MIN_FRAME_RATE = 10.0f;             // the minimum frame rate
const float MIN_FRAME_TIME = 1.0f/FRAME_RATE;   // minimum desired time for 1 frame
const float MAX_FRAME_TIME = 1.0f/MIN_FRAME_RATE; // maximum time used in calculations
// collision boxes
const RECT  COLLISION_BOX_ALIEN = {-50, -20, 50, 20};
const RECT	COLLISION_BOX_CITY = {-28,-30,28,30};
const RECT	COLLISION_BOX_PLAYER = {-32,-42,32,42};
const RECT	COLLISION_BOX_ROCKET = {-3,-22,3,22};
const RECT	COLLISION_BOX_SPIT = {-16,-11,16,11};
const RECT	COLLISION_BOX_ASTEROID = {-30,-30,30,30};
// image file names
const char ALIEN_IMAGE[] = "pictures\\alien1.png" ;
const char ROCKET_IMAGE[] = "pictures\\rocket.png" ;
const char STARBACK_IMAGE[] = "pictures\\star3.png" ;
const char STARBACK2_IMAGE[] = "pictures\\star32.png" ;
const char BUILDING_IMAGE[] = "pictures\\building.png" ;
const char PLAYER_IMAGE[] = "pictures\\player.png" ;
const char CREDIT_IMAGE[] = "pictures\\credits.png" ;
const char STAR_IMAGE[] = "pictures\\topstars.png";
const char INSTRUCT_IMAGE[] = "pictures\\instruct.png";
const char SPIT_IMAGE[] = "pictures\\spitball.png";
const char ASTEROID_IMAGE[] = "pictures\\asteroid.png";
const char CROSS_IMAGE[] = "pictures\\crosshair6.png";
const char DUST_IMAGE[] = "pictures\\dust.png";
// key mappings
const UCHAR ESC_KEY      = VK_ESCAPE;       // escape key
const UCHAR ALT_KEY      = VK_MENU;         // Alt key
const UCHAR PADDLE_LEFT    = VK_LEFT;     // left arrow
const UCHAR PADDLE_RIGHT   = VK_RIGHT ;    // right arrow
const UCHAR ENTER_KEY    = VK_RETURN; 
const UCHAR PADDLE_UP	 = VK_SPACE;
const UCHAR RESET_PUCK   = VK_TAB;

// audio files
const char WAVE_BANK[]	= "audio\\Win\\Wave Bank.xwb";
const char SOUND_BANK[]	= "audio\\Win\\Sound Bank.xsb";

// audio cue
const char SHOOT[]   = "shoot";
const char HIT[] = "hit";
const char BACKGROUND_MUS[] = "background";
const char EXPLODE[] = "explosion";

// pattern steps
enum ALIEN_PATTERN_STEP_ACTION {NONE, ENTER, CAMP, LEAVE};
enum GameStates {gameMenu, gamePlay, endGame,credits,instruct};

#endif
