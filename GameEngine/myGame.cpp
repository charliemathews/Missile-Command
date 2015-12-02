
#include <sstream>
using namespace std ;

#include "myGame.h"
//=============================================================================
// Constructor
//=============================================================================
myGame::myGame()
{
	//nothing here, move on
}

//=============================================================================
// Destructor
//=============================================================================
myGame::~myGame()
{
    releaseAll();           // call onLostDevice() for every graphics item
}

//=============================================================================
// Initializes the game
// Throws GameError on error
//=============================================================================
void myGame::initialize(HWND hwnd)
{
    Game::initialize(hwnd); 
	
/* INITIALIZE PATTERNS */
	lambda alien_enter = [&] (Entity* e) {
		e->setVelocity(D3DXVECTOR2(-100,0)) ;
	};
	lambda alien_camp = [&] (Entity* e) {
		e->setVelocity(D3DXVECTOR2(0,0)) ;
	};

	Pattern* alienPattern = new Pattern(8);
	alienPattern->addStep(0, "CAMP", 4, [&] (Entity* e) {
		e->setVelocity(D3DXVECTOR2(0,0)) ;
	}) ;
	
	alienPattern->addStep(1, "FIRE", .0009, [&] (Entity* e) {
		myGame::fireSpitball(VECTOR2(e->getX(),e->getY() - e->getHeight()));
	});
	alienPattern->addStep(2, "LEFT", 4, [&] (Entity* e) {
		e->setVelocity(D3DXVECTOR2(-100,0));
	});
	alienPattern->addStep(3, "FIRE", .0009, [&] (Entity* e) {
		myGame::fireSpitball(VECTOR2(e->getX(),e->getY() - e->getHeight()));
	});
	alienPattern->addStep(4, "FIRE", .0009, [&] (Entity* e) {
		myGame::fireSpitball(VECTOR2(e->getX(),e->getY() - e->getHeight()));
	});
	alienPattern->addStep(5, "LEFT", 2, [&] (Entity* e) {
		e->setVelocity(D3DXVECTOR2(-50,0));
	});
	alienPattern->addStep(6, "FIRE", .0009, [&] (Entity* e) {
		myGame::fireSpitball(VECTOR2(e->getX(),e->getY() - e->getHeight()));
	});
	alienPattern->addStep(7, "LEFT", 5, [&] (Entity* e) {
		e->setVelocity(D3DXVECTOR2(-150,0));
	});
	Pattern* alienPattern2 = new Pattern(7);

	alienPattern2->addStep(0, "CAMP", 40, [&] (Entity* e) {
		e->setVelocity(D3DXVECTOR2(0,0)) ;
	}) ;
	alienPattern2->addStep(1, "LEFT", 4, [&] (Entity* e) {
		e->setVelocity(D3DXVECTOR2(-50,0));
	});
	alienPattern2->addStep(2, "FIRE", .0009, [&] (Entity* e) {
		myGame::fireSpitball(VECTOR2(e->getX(),e->getY() - e->getHeight()));
	});
	alienPattern2->addStep(3, "FIRE", .0009, [&] (Entity* e) {
		myGame::fireSpitball(VECTOR2(e->getX(),e->getY() - e->getHeight()));
	});
	alienPattern2->addStep(4, "LEFT", 5, [&] (Entity* e) {
		e->setVelocity(D3DXVECTOR2(-100,0));
	});
	alienPattern2->addStep(5, "FIRE", .0009, [&] (Entity* e) {
		myGame::fireSpitball(VECTOR2(e->getX(),e->getY() - e->getHeight()));
	});
	alienPattern2->addStep(6, "LEFT", 5, [&] (Entity* e) {
		e->setVelocity(D3DXVECTOR2(-100,0));
	});
	//
	if(!backgroundTM.initialize(graphics,STARBACK_IMAGE))
    	throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing background texture"));
	if (!backgroundImage.initialize(graphics,0,0,1, &backgroundTM))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing backgroun image"));
	
	if(!starsTM.initialize(graphics,STAR_IMAGE))
    	throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing background texture"));
	if (!starImage.initialize(graphics,0,0,1, &starsTM))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing backgroun image"));
	// credits
	if(!creditsTM.initialize(graphics,CREDIT_IMAGE))
    	throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing background texture"));
	if (!creditsImage.initialize(graphics,0,0,1, &creditsTM))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing backgroun image"));
	//instructions
	if(!instructTM.initialize(graphics,INSTRUCT_IMAGE))
    	throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing background texture"));
	if (!instructImage.initialize(graphics,0,0,1, &instructTM))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing backgroun image"));
	// initialize texture managers
	if (!alienTM.initialize(graphics,ALIEN_IMAGE))
    	throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing alien texture"));
	if (!bolideTM.initialize(graphics,ASTEROID_IMAGE))
    	throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing bolide texture"));
	if (!rocketTM.initialize(graphics,ROCKET_IMAGE))
    	throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing rocket texture"));
    	if (!spitTM.initialize(graphics,SPIT_IMAGE))
    	throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing spit texture"));
	
	Alien* newAlien = new Alien() ;
	if (!newAlien->initialize(this, alienNS::WIDTH, alienNS::HEIGHT, 1, &alienTM))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing alien entity"));
	
	newAlien->setX(GAME_WIDTH);
	newAlien->setY(20);
	newAlien->setEdge(COLLISION_BOX_ALIEN);
	newAlien->setScale(1);
	aliens.add(newAlien, new Pattern(alienPattern2)) ;

	Alien* newAlien2 = new Alien() ;
	if (!newAlien2->initialize(this, alienNS::WIDTH, alienNS::HEIGHT, 1, &alienTM))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing alien entity"));
	
	newAlien2->setX(GAME_WIDTH);
	newAlien2->setY(40);
	newAlien2->setEdge(COLLISION_BOX_ALIEN);
	newAlien2->setScale(1);
	//newAlien2->camp() ;
	aliens.add(newAlien2, new Pattern(alienPattern)) ;


	//player
	if (!playerTM.initialize(graphics,PLAYER_IMAGE))
    	throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing player texture"));
	if (!thePlayer.initialize(this, playerNS::WIDTH, playerNS::HEIGHT, 1, &playerTM))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing alien entity"));
	thePlayer.setX((GAME_WIDTH/2)-playerNS::WIDTH/2 + 20);
	thePlayer.setY(GAME_HEIGHT - thePlayer.getHeight());
	thePlayer.setEdge(COLLISION_BOX_PLAYER);
	thePlayer.setScale(1);

	//cities
	if (!cityTM.initialize(graphics,BUILDING_IMAGE))
    	throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing city texture"));
	
	City* newCity = new City();
	if (!newCity->initialize(this, cityNS::WIDTH, cityNS::HEIGHT, 1, &cityTM))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing city entity"));
	
	newCity->setEdge(COLLISION_BOX_CITY);
	newCity->setScale(1);
	newCity->setY(GAME_HEIGHT - newCity->getHeight());
	newCity->setX(80);
	cities.add(newCity);

	City* newCity1 = new City();
	if (!newCity1->initialize(this, cityNS::WIDTH, cityNS::HEIGHT, 1, &cityTM))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing city entity"));
	
	newCity1->setEdge(COLLISION_BOX_CITY);
	newCity1->setScale(1);
	newCity1->setY(GAME_HEIGHT - newCity->getHeight());
	newCity1->setX(newCity->getX() + newCity->getWidth() + 80);
	cities.add(newCity1);

	City* newCity2 = new City();
	if (!newCity2->initialize(this, cityNS::WIDTH, cityNS::HEIGHT, 1, &cityTM))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing city entity"));
	
	newCity2->setEdge(COLLISION_BOX_CITY);
	newCity2->setScale(1);
	newCity2->setY(GAME_HEIGHT - newCity->getHeight());
	newCity2->setX(GAME_WIDTH - 80 - newCity->getWidth());
	cities.add(newCity2);

	City* newCity3 = new City();
	if (!newCity3->initialize(this, cityNS::WIDTH, cityNS::HEIGHT, 1, &cityTM))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing city entity"));
	
	newCity3->setEdge(COLLISION_BOX_CITY);
	newCity3->setScale(1);
	newCity3->setY(GAME_HEIGHT - newCity->getHeight());
	newCity3->setX(newCity2->getX() - newCity->getWidth() - 80);
	cities.add(newCity3);

	//initiialize font
	dxFont = new TextDX();
	if(dxFont->initialize(graphics, 25, true, false, "Retro Computer") == false)
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing score font"));
	dxFont->setFontColor(graphicsNS::RED);
	
	
	// Initialize Menu
	menu = new Menu();
	menu->initialize(graphics,input);

	sfxOn = true;
	score = 0;
	bolideTimer = 0 ;

	gameStates = gameMenu;
	getMouseDepressedLast = false;

	audio->playCue("background");

	srand(time(NULL));

    return;
}

//=============================================================================
// Update all game items
//=============================================================================
void myGame::update()
{
	int lineOpt = 0;
	switch(gameStates)
	{
	case gameMenu:
		
		lineOpt = menu->update();
		if(lineOpt == 0) 
		{
			gameStates = gamePlay;
			tickCounter = GetTickCount();
		}
		if(lineOpt == 1)
		{
			if(sfxOn) audio->stopCue("background");
			else audio->playCue("background");
			setSFX();
		}
		if(lineOpt == 2) gameStates = instruct;
		if(lineOpt == 3) gameStates = credits;
		
		break;
	case gamePlay:
				
		if(input->getMouseLButton())getMouseDepressedLast = true;
		if(!input->getMouseLButton()&&getMouseDepressedLast)
		{
			getMouseDepressedLast = false;
			fireRocket();
		}

		if(GetTickCount() % 1000 == 0)
		{
			scrollBG();
		}
		if(GetTickCount()-tickCounter >= GAME_END_TIME)
		{
			gameStates = endGame;
		}

		if(bolideTimer < 1.00) bolideTimer += frameTime ;
		else
		{
			int randNum = (rand()%4)-1;
			spawnBolide(VECTOR2(randNum*2*cityNS::WIDTH,0));
			bolideTimer = 0 ;
		}
		aliens.update(frameTime);
		cities.update(frameTime);
		thePlayer.update(frameTime);
		rockets.update(frameTime);
		bolides.update(frameTime);
		spits.update(frameTime);

		break;
	case endGame:
		
		backgroundImage.update(frameTime);
		if(GetTickCount() % 1000 == 0)
		{
			scrollBG();
		}
		if(input->isKeyDown(VK_RETURN)) 
		{
			audio->stopCue("background");
			myGame::initialize(hwnd);
			gameStates = credits;
		}
		break;
	case credits:
		if(input->isKeyDown(VK_SPACE)/*&&!input->isKeyDown(VK_RETURN)*/) gameStates = gameMenu;
		break;
	case instruct:
		if(input->isKeyDown(VK_SPACE)/*&&!input->isKeyDown(VK_RETURN)*/) gameStates = gameMenu;
		break;
	}
	
}

//=============================================================================
// Artificial Intelligence
//=============================================================================
void myGame::ai()
{
	aliens.ai(frameTime);
	//stringstream ss ;
	//ss << endl << alienPatternStepIndex << endl ;
	//OutputDebugString(ss.str().c_str());
}

//=============================================================================
// Handle collisions
//=============================================================================
void myGame::collisions()
{

	collisionVector = D3DXVECTOR2(0,0); // clear collision vector
	
	int bolides_size	= bolides.getSize();
	int spits_size		= spits.getSize();
	int rockets_size	= rockets.getSize();
	int aliens_size		= aliens.getSize();
	int cities_size		= cities.getSize();


	Bolide** bolides_raw = (Bolide**)bolides.getArray();

	// handle asteroid<->asteroid collisions
	Bolide* bolideCollision ;
	Rocket* rocketCollision ;
	City* cityCollision ;
	Spitball* spitCollision ;

	for(int i = 0; i < bolides_size; ++i)
	{
		bolideCollision = (Bolide*)bolides.checkCollision(bolides_raw[i], collisionVector) ;
		if(bolideCollision != NULL)
		{
			bolideCollision->bounce(collisionVector, *bolides_raw[i]);
			collisionVector = D3DXVECTOR2(0,0);
		}
		bolideCollision == NULL ;

		rocketCollision = (Rocket*)rockets.checkCollision(bolides_raw[i], collisionVector) ;
		if(rocketCollision != NULL)
		{
			audio->playCue("hit");
			rocketCollision->setActive(false);
			bolides_raw[i]->setHealth(-1);
			score += 50 ;
			collisionVector = D3DXVECTOR2(0,0);
		}
		rocketCollision == NULL ;

		cityCollision = (City*)cities.checkCollision(bolides_raw[i], collisionVector) ;
		if(cityCollision != NULL)
		{
			audio->playCue("explosion");
			cityCollision->damage(1);
			bolides_raw[i]->setHealth(-1);
			score -= 500 ;
			collisionVector = D3DXVECTOR2(0,0);
		}
		cityCollision == NULL ;
	}

	if(aliens_size > 0)
	{
		Alien** aliens_raw = (Alien**)aliens.getArray();
		for(int i = 0; i < aliens_size; ++i)
		{
			rocketCollision = (Rocket*)rockets.checkCollision(aliens_raw[i], collisionVector) ;
			if(rocketCollision != NULL)
			{
				audio->playCue("explosion");
				rocketCollision->setActive(false);
				aliens_raw[i]->setHealth(-1);
				score += 200 ;
				collisionVector = D3DXVECTOR2(0,0);
			}
			rocketCollision == NULL ;
		}
	}

	if(spits_size > 0)
	{
		Spitball** spits_raw = (Spitball**)spits.getArray();
		for(int i = 0; i < spits_size; ++i)
		{
			rocketCollision = (Rocket*)rockets.checkCollision(spits_raw[i], collisionVector) ;
			if(rocketCollision != NULL)
			{
				audio->playCue("hit");
				rocketCollision->setActive(false);
				spits_raw[i]->setHealth(-1);
				score += 80 ;
				collisionVector = D3DXVECTOR2(0,0);
			}
			rocketCollision == NULL ;

			cityCollision = (City*)cities.checkCollision(spits_raw[i], collisionVector) ;
			if(cityCollision != NULL)
			{
				audio->playCue("explosion");
				cityCollision->damage(1);
				spits_raw[i]->setHealth(-1);
				score -= 200 ;
				collisionVector = D3DXVECTOR2(0,0);
			}
			cityCollision == NULL ;
		}
	}

	
}

//=============================================================================
// Render game items
//=============================================================================
void myGame::render()
{
    std::stringstream ss ;
    graphics->spriteBegin(); // begin drawing sprites
	switch(gameStates)
	{
	case gameMenu:
		backgroundImage.draw();
		menu->displayMenu();
		break;
	case gamePlay:
		backgroundImage.draw();
		starImage.draw();
		
		ss << score;
		dxFont->print("Score: "+ss.str(), 0,0);

		cities.draw();
		bolides.draw();
		aliens.draw();
		thePlayer.draw();
		rockets.draw();
		spits.draw();
		break;
	case endGame:
		backgroundImage.draw();
		starImage.draw();
		//TO DO add score tally at end
		
		ss << score;
		dxFont->print("You lasted the night!", 70, 100);
		dxFont->print("Final Score: " + ss.str(),70,200);
		ss.clear();
		dxFont->print("press <enter> to continue",70,400);
		break;
	case credits:
		creditsImage.draw();
		break;
	case instruct:
		instructImage.draw();
		break;
	}
	
    graphics->spriteEnd(); // end drawing sprites
}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void myGame::releaseAll()
{
	// TextureManager::onLostDevice();
	alienTM.onLostDevice();

	rocketTM.onLostDevice();
	bolideTM.onLostDevice();
	backgroundTM.onLostDevice();
	starsTM.onLostDevice();
	creditsTM.onLostDevice();
	instructTM.onLostDevice();
	cityTM.onLostDevice();
	playerTM.onLostDevice();
	spitTM.onLostDevice();

	rockets.clear();
	cities.clear();
	bolides.clear();
	aliens.clear();
	spits.clear();

    Game::releaseAll();
    return;
}

//=============================================================================
// The grahics device has been reset.
// Recreate all surfaces.
//=============================================================================
void myGame::resetAll()
{
	// TextureManager::onResetDevice();
	alienTM.onResetDevice();
	rocketTM.onResetDevice();
	bolideTM.onResetDevice();
	backgroundTM.onResetDevice();
	starsTM.onResetDevice();
	creditsTM.onResetDevice();
	instructTM.onResetDevice();
	cityTM.onResetDevice();
	playerTM.onResetDevice();
	spitTM.onResetDevice();
    Game::resetAll();
    return;
}


void myGame::spawnBolide(VECTOR2 target)
{
	Bolide* bolide = new Bolide();
	if (!bolide->initialize(this, bolideNS::WIDTH, bolideNS::HEIGHT, 1, &bolideTM))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing bolide entity"));

	float size = ((rand()%2)+1);

	if(size == 1)	size = .5;
	else			size = .3;

	int spawn = rand()%(GAME_WIDTH-bolide->getWidth());

	bolide->setScale(size);
	bolide->setX(spawn);
	bolide->setY(0);
	bolide->setVelocity(VECTOR2(bolideNS::SPEED_X*0.8,bolideNS::SPEED_Y*0.8));
	bolide->setEdge(COLLISION_BOX_ASTEROID);
	bolide->setStartPos(bolide->getX(),bolide->getY());

	int targetX = rand()%(GAME_WIDTH) ;

	bolide->setTargetCoords(targetX, static_cast<int>(GAME_HEIGHT));
	bolide->setAngle();

	bolides.add(bolide);
}

void myGame::scrollBG()
{
	int prev = backgroundImage.getY();
	if(GetTickCount() % 10000)
	{
		starImage.setY(starImage.getY()-2);
	};
	backgroundImage.setY(backgroundImage.getY()-2);
	if(backgroundImage.getY()+backgroundImage.getHeight() <= GAME_HEIGHT)
	{
		backgroundImage.setY(prev);
	}
}
void myGame::fireRocket()
{
	Rocket* newRocket = new Rocket();
	if (!newRocket->initialize(this, rocketNS::WIDTH, rocketNS::HEIGHT,1, &rocketTM))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing rocket entity"));

	newRocket->setX(thePlayer.getCenterX());
	newRocket->setY(thePlayer.getY());
	newRocket->setEdge(COLLISION_BOX_ROCKET);
	newRocket->setScale(1);
	newRocket->setVelocity(VECTOR2(rocketNS::SPEED_X,rocketNS::SPEED_Y));
		
	newRocket->setX(thePlayer.getX() + 30);
	newRocket->setY(thePlayer.getY());

	int xClick = input->getMouseX();
	int yClick = input->getMouseY();

	newRocket->setStartPos(newRocket->getX(),GAME_HEIGHT-thePlayer.getHeight());
	VECTOR2 direc(xClick-newRocket->getX(), yClick - newRocket->getY());
	newRocket->setTargetCoords(VECTOR2(xClick,yClick));
	newRocket->setDir(direc);
	newRocket->setAngle();
	newRocket->setVisible();
	newRocket->setAliveTime();
	newRocket->setScale(2);
	rockets.add(newRocket);
	if(sfxOn)audio->playCue("shoot");
}

void myGame::fireSpitball(VECTOR2 source)
{
	int randTarget = (rand()%GAME_WIDTH)+1;
	Spitball* newSpitball = new Spitball();
	if (!newSpitball->initialize(this, spitballNS::WIDTH, spitballNS::HEIGHT,1, &spitTM))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing spitball entity"));

		newSpitball->setX(source.x);
		newSpitball->setY(source.y + alienNS::HEIGHT);
		newSpitball->setEdge(COLLISION_BOX_SPIT);

		VECTOR2 spitTarget(randTarget,GAME_HEIGHT);
		newSpitball->setStartPos(newSpitball->getX(),newSpitball->getY());
		VECTOR2 direc(spitTarget.x-newSpitball->getX(), spitTarget.y - newSpitball->getY());
						
		newSpitball->setTargetCoords(spitTarget);
		newSpitball->setDir(direc);
		newSpitball->setAngle();
		newSpitball->setVisible();
		newSpitball->setAliveTime();
		newSpitball->setActive(true);

		spits.add(newSpitball);
		if(sfxOn)audio->playCue("shoot");
}