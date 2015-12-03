/*
Author:			Charlie Mathews
Created:		November 6th, 2015
Derived from:	Charles Kelly, Programming 2D Games (c) 2011,2012
*/

#ifndef _MY_GAME_H      // Prevent multiple definitions if this 
#define _MY_GAME_H      // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

class myGame;

#include <cmath>
#include <string>
#include <sstream>
#include <ctime>

#include "constants.h"
#include "entityManager.h"
#include "game.h"
#include "graphics.h"
#include "image.h"
#include "textureManager.h"
#include "textDX.h"

#include "pattern.h"
#include "menu.h"
#include "player.h"
#include "city.h"
#include "alien.h"
#include "projectile.h"
	#include "bolide.h"
	#include "spitball.h"
	#include "rocket.h"
#include "particleManager.h"

//=============================================================================
// This class is the core of the game
//=============================================================================
class myGame : public Game
{
private:
    TextureManager alienTM, rocketTM,bolideTM,cityTM,playerTM, spitTM ;
	TextureManager backgroundTM,starsTM,creditsTM,instructTM,crossHairTM ;
	Image backgroundImage, starImage, creditsImage, instructImage, crossHairImage;
    VECTOR2 collisionVector ;
	
	GameStates gameStates ;
	Menu *menu ;
	bool sfxOn ;

	TextDX* dxFont;

	Player thePlayer ;
	EntityManager aliens ;
	EntityManager rockets ;
	EntityManager bolides ;
	EntityManager cities ;
	EntityManager spits ;

	int score ;
	float bolideTimer ;
	int tickCounter;
	bool getMouseDepressedLast;
	bool enterDepressedLastFrame;
	//text
	std::stringstream buffer ;
	//particles
	ParticleManager pm;


public:
    // Constructor
    myGame();

    // Destructor
    virtual ~myGame();

    // Initialize the game
    void initialize(HWND hwnd);
    void update();      // must override pure virtual from Game
    void ai();          // "
    void collisions();  // "
    void render();      // "
    void releaseAll();
    void resetAll();
	void spawnBolide(VECTOR2 target);
	void scrollBG();
	void setSFX(){sfxOn = !sfxOn;}
	void fireRocket();
	void fireSpitball(VECTOR2 source);
	void createParticleEffect(VECTOR2 pos, VECTOR2 vel, int numParticles);
};

#endif
