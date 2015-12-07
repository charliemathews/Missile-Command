
#include <sstream>
using namespace std ;

#include "myGame.h"
//=============================================================================
// Constructor
//=============================================================================
myGame::myGame()
{
	for (int i = 0; i < MAX_SCORES_DISPLAYED; i++)
	{
		topTenScores[i] = INT_MIN;
	}

	//nothing here, move on
	//rocketsAvailable = 5;
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

#pragma region Initializing AI patterns
	/* INITIALIZE PATTERNS */
	lambda alien_enter = [&] (Entity* e) {
		e->setVelocity(D3DXVECTOR2(-100,0)) ;
	};
	lambda alien_camp = [&] (Entity* e) {
		e->setVelocity(D3DXVECTOR2(0,0)) ;
	};

	alienPattern = new Pattern(8);
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

	alienPattern2 = new Pattern(7);
	alienPattern2->addStep(0, "CAMP", 4, [&] (Entity* e) {
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


	alienPattern3 = new Pattern(7);

	alienPattern3->addStep(0, "CAMP", 4, [&] (Entity* e) {
		e->setVelocity(D3DXVECTOR2(0,0)) ;
	}) ;
	alienPattern3->addStep(1, "RIGHT", 6, [&] (Entity* e) {
		e->setVelocity(D3DXVECTOR2(100,0));
	});
	alienPattern3->addStep(2, "FIRE", .0009, [&] (Entity* e) {
		myGame::fireSpitball(VECTOR2(e->getX(),e->getY() - e->getHeight()));
	});
	alienPattern3->addStep(3, "FIRE", .0009, [&] (Entity* e) {
		myGame::fireSpitball(VECTOR2(e->getX(),e->getY() - e->getHeight()));
	});
	alienPattern3->addStep(4, "DOWN", 2, [&] (Entity* e) {
		e->setVelocity(D3DXVECTOR2(-50,100));
	});
	alienPattern3->addStep(5, "FIRE", .0009, [&] (Entity* e) {
		myGame::fireSpitball(VECTOR2(e->getX(),e->getY() - e->getHeight()));
	});
	alienPattern3->addStep(6, "LEFT", 6, [&] (Entity* e) {
		e->setVelocity(D3DXVECTOR2(-150,0));
	});

	alienPattern4 = new Pattern(7);

	alienPattern4->addStep(0, "CAMP", 4, [&] (Entity* e) {
		e->setVelocity(D3DXVECTOR2(0,0)) ;
	}) ;
	alienPattern4->addStep(1, "RIGHT", 6, [&] (Entity* e) {
		e->setVelocity(D3DXVECTOR2(100,0));
	});
	alienPattern4->addStep(2, "FIRE", .0009, [&] (Entity* e) {
		myGame::fireSpitball(VECTOR2(e->getX(),e->getY() - e->getHeight()));
	});
	alienPattern4->addStep(3, "FIRE", .0009, [&] (Entity* e) {
		myGame::fireSpitball(VECTOR2(e->getX(),e->getY() - e->getHeight()));
	});
	alienPattern4->addStep(4, "UP", .5, [&] (Entity* e) {
		e->setVelocity(D3DXVECTOR2(50,-100));
	});
	alienPattern4->addStep(5, "FIRE", .0009, [&] (Entity* e) {
		myGame::fireSpitball(VECTOR2(e->getX(),e->getY() - e->getHeight()));
	});
	alienPattern4->addStep(6, "RIGHT", 7, [&] (Entity* e) {
		e->setVelocity(D3DXVECTOR2(150,0));

	});
#pragma endregion

	//particles
	pm.initialize(graphics);

	//
	if(!backgroundTM.initialize(graphics,STARBACK_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing background texture"));
	if (!backgroundImage.initialize(graphics,0,0,1, &backgroundTM))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing backgroun image"));
	if(!background2TM.initialize(graphics,STARBACK2_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing background texture"));
	if(!backgroundImage2.initialize(graphics,0,0,1, &background2TM))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing backgroun image"));
	backgroundImage.setY(0);
	backgroundImage2.setY(backgroundImage.getHeight()-10);

	backgroundImage.setY(backgroundImage.getY() + backgroundImage.getHeight()-40);
	backgroundImage2.setY(backgroundImage.getY() - backgroundImage2.getHeight() + 20);

	if(!starsTM.initialize(graphics,STAR_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing background texture"));
	if (!starImage.initialize(graphics,0,0,1, &starsTM))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing backgroun image"));
	starImage.setY(backgroundImage.getY());
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
	//init crosshair
	if (!crossHairTM.initialize(graphics,CROSS_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing cross hair texture"));
	if (!crossHairImage.initialize(graphics,0,0,1, &crossHairTM))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing cross hair image"));

	for (int i = 0; i < MAX_ROCKETS; i++)
	{
		if (!rocketsRemaining[i].initialize(graphics, rocketNS::WIDTH, rocketNS::HEIGHT, 0, &rocketTM))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing rocket image"));

		rocketsRemaining[i].setX(10);
		rocketsRemaining[i].setY(GAME_HEIGHT - GAME_HEIGHT/8 - (i + 1) * 2 * rocketNS::HEIGHT);
	}


	//menu screen alien
	if (!mAlien.initialize(this, alienNS::WIDTH, alienNS::HEIGHT, 1, &alienTM))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menu alien image"));
	mAlien.setVelocity(VECTOR2(200,150));
	mAlien.setX(rand()%GAME_WIDTH);
	mAlien.setY(rand()%GAME_HEIGHT);
	//player
	if (!playerTM.initialize(graphics,PLAYER_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing player texture"));
	if (!thePlayer.initialize(this, playerNS::WIDTH, playerNS::HEIGHT, 1, &playerTM))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing alien entity"));
	thePlayer.setX((GAME_WIDTH/2)-playerNS::WIDTH/2+30);
	thePlayer.setY(GAME_HEIGHT - thePlayer.getHeight());
	thePlayer.setEdge(COLLISION_BOX_PLAYER);
	thePlayer.setScale(1);

	//cities
	if (!cityTM.initialize(graphics,BUILDING_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing city texture"));

	City* newCity = new City();
	if (!newCity->initialize(this, cityNS::WIDTH, cityNS::HEIGHT, 2, &cityTM))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing city entity"));

	newCity->setEdge(COLLISION_BOX_CITY);
	newCity->setScale(1);
	newCity->setY(GAME_HEIGHT - newCity->getHeight());
	newCity->setX(80);

	newCity->setCurrentFrame(0);

	cities.add(newCity);

	City* newCity1 = new City();
	if (!newCity1->initialize(this, cityNS::WIDTH, cityNS::HEIGHT, 2, &cityTM))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing city entity"));

	newCity1->setEdge(COLLISION_BOX_CITY);
	newCity1->setScale(1);
	newCity1->setY(GAME_HEIGHT - newCity->getHeight());
	newCity1->setX(newCity->getX() + newCity->getWidth() + 80);

	newCity1->setCurrentFrame(0);

	cities.add(newCity1);

	City* newCity2 = new City();
	if (!newCity2->initialize(this, cityNS::WIDTH, cityNS::HEIGHT, 2, &cityTM))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing city entity"));

	newCity2->setEdge(COLLISION_BOX_CITY);
	newCity2->setScale(1);
	newCity2->setY(GAME_HEIGHT - newCity->getHeight());
	newCity2->setX(GAME_WIDTH - 80 - newCity->getWidth());

	newCity2->setCurrentFrame(0);

	cities.add(newCity2);

	City* newCity3 = new City();
	if (!newCity3->initialize(this, cityNS::WIDTH, cityNS::HEIGHT, 2, &cityTM))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing city entity"));

	newCity3->setEdge(COLLISION_BOX_CITY);
	newCity3->setScale(1);
	newCity3->setY(GAME_HEIGHT - newCity->getHeight());
	newCity3->setX(newCity2->getX() - newCity->getWidth() - 80);

	newCity3->setCurrentFrame(0);

	cities.add(newCity3);

	//initiialize font
	dxFont = new TextDX();
	if(dxFont->initialize(graphics, 25, true, false, "Retro Computer") == false)
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing text font"));
	dxFont->setFontColor(graphicsNS::BLACK);
	scoreFont = new TextDX();
	if(scoreFont->initialize(graphics, 50, true, false, "Retro Computer") == false)
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing score font"));
	scoreFont->setFontColor(graphicsNS::WHITE);


	// Initialize Menu
	menu = new Menu();
	menu->initialize(graphics,input);

	sfxOn = true;
	score = 0;
	timer = 0;
	bolideTimer = 0 ;
	alienTimer = 0;
	scoreDispCounter = 0;
	gameStates = gameMenu;
	getMouseDepressedLast = false;
	enterDepressedLastFrame = false;
	isNight = false;
	isTutorial = true;
	nightCount = 0;
	endedGame = false;
	numCities = 0;
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


	City** cities_raw = (City**)cities.getArray();
	VECTOR2 vel;
	VECTOR2* foo;

	switch(gameStates)
	{
	case gameMenu:
		ShowCursor(true);
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
		if(lineOpt == 4) gameStates = highScore;
		//lil menu alien
		//mAlien.update(frameTime);

		break;
	case gamePlay:

		ShowCursor(false);
		if(input->getMouseLButton())getMouseDepressedLast = true;
		if(!input->getMouseLButton()&&getMouseDepressedLast)
		{
			getMouseDepressedLast = false;
			if(rockets.getSize() < MAX_ROCKETS) fireRocket();
		}

		scrollBG();
		numCities = 0;
		for(int i = 0; i < cities.getSize(); i++)
		{
			if(cities_raw[i]->getHealth() > 0) numCities++;
		}
		if(nightCount >= 3 && backgroundImage.getY() <= -740)
		{
			addHighScores(score);
			gameStates = endGame;
		}
		if(numCities == 0)
		{
			addHighScores(score);
			gameStates = endGame;
		}

		if(alienTimer < 8.00) alienTimer += frameTime;
		else if(isNight && nightCount < 3)
		{
			spawnAlien();
			alienTimer = 0;
		}
		else if(isNight && nightCount == 3)
		{
			int randNum = (rand() % 3)+1;
			for(int i = 0; i < randNum; i++)
			{
				spawnAlien();
			}
			alienTimer = 0;
		}

		if(bolideTimer < 1.70) bolideTimer += frameTime ;
		else
		{
			int randNum = (rand()%4)-1;
			spawnBolide(VECTOR2(randNum*2*cityNS::WIDTH,0));
			if(isNight && nightCount != 3) bolideTimer = -.5 ;
			else bolideTimer = .7;
		}

		if(scoreFont->getFontColor()!=graphicsNS::WHITE)
		{
			if(scoreDispCounter < 1.00) scoreDispCounter += frameTime ;
			else
			{
				City** cities_raw = (City**)cities.getArray();
				for(int i = 0; i < cities.getSize(); i++)
				{
					if(cities_raw[i]->getActive())cities_raw[i]->setColorFilter(graphicsNS::WHITE);
				}
				scoreFont->setFontColor(graphicsNS::WHITE);
				scoreDispCounter = 0;
			}
		}
		aliens.update(frameTime);
		cities.update(frameTime);
		thePlayer.update(frameTime);
		rockets.update(frameTime);
		bolides.update(frameTime);
		spits.update(frameTime);

		//
		crossHairImage.setX(input->getMouseX() - crossHairImage.getWidth()/3);
		crossHairImage.setY(input->getMouseY() - crossHairImage.getHeight()/2);

		//rockets stack
		int index;
		for (index = MAX_ROCKETS; index > (MAX_ROCKETS - rockets.getSize()); index--)
			rocketsRemaining[index - 1].setVisible(false);
		for (int i = index - 1; i >= 0; i--)
			rocketsRemaining[i].setVisible(true);

		//particles
		pm.update(frameTime);

		break;
	case endGame:

		ShowCursor(true);
		if(input->getMouseLButton()) enterDepressedLastFrame = true;
		if (!input->getMouseLButton() && enterDepressedLastFrame)
		{


			audio->stopCue("background");
			myGame::initialize(hwnd);
			gameStates = credits;
			enterDepressedLastFrame = false;
		}
		break;
	case credits:
		ShowCursor(true);
		if(input->getMouseLButton()) enterDepressedLastFrame = true;
		if (!input->getMouseLButton() && enterDepressedLastFrame)
		{
			gameStates = gameMenu;
			enterDepressedLastFrame = false;
		}
		break;
	case instruct:
		ShowCursor(true);
		if(input->getMouseLButton()) enterDepressedLastFrame = true;
		if (!input->getMouseLButton() && enterDepressedLastFrame)
		{
			gameStates = gameMenu;
			enterDepressedLastFrame = false;
		}
		break;
	case highScore:
		ShowCursor(true);
		if(input->getMouseLButton()) enterDepressedLastFrame = true;
		if (!input->getMouseLButton() && enterDepressedLastFrame)
		{
			gameStates = gameMenu;
			enterDepressedLastFrame = false;
		}
		break;
	}


}

//=============================================================================
// Artificial Intelligence
//=============================================================================
void myGame::ai()
{

	if(gameStates == gamePlay) aliens.ai(frameTime);
	//stringstream ss ;
	//ss << endl << alienPatternStepIndex << endl ;
	//OutputDebugString(ss.str().c_str());
}

//=============================================================================
// Handle collisions
//=============================================================================
void myGame::collisions()
{
	if(gameStates == gamePlay)
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
		Alien* alienCollision;

		for(int i = 0; i < bolides_size; ++i)
		{
			bolideCollision = (Bolide*)bolides.checkCollision(bolides_raw[i], collisionVector) ;
			if(bolideCollision != NULL)
			{
				bolideCollision->bounce(collisionVector, *bolides_raw[i]);
				collisionVector = D3DXVECTOR2(0,0);
			}
			bolideCollision == NULL ;

			if(rockets_size > 0)
			{
				rocketCollision = (Rocket*)rockets.checkCollision(bolides_raw[i], collisionVector) ;
				if(rocketCollision != NULL)
				{
					if(sfxOn)audio->playCue("hit");
					rocketCollision->setActive(false);
					bolides_raw[i]->setHealth(-1);
					score += 100 ;
					VECTOR2 foo = VECTOR2(bolides_raw[i]->getPositionX()-10, bolides_raw[i]->getPositionY()+5);
					VECTOR2 bar = VECTOR2(((float(rand()) / float(RAND_MAX)) * (50 - 10)) + 10,((float(rand()) / float(RAND_MAX)) * (50)) + 0);
					createParticleEffect(foo, bar, 10);
					collisionVector = D3DXVECTOR2(0,0);

					scoreFont->setFontColor(graphicsNS::GREEN);

				}
				rocketCollision == NULL ;
			}

			cityCollision = (City*)cities.checkCollision(bolides_raw[i], collisionVector) ;
			if(cityCollision != NULL)
			{
				if(cityCollision->getHealth() > 0)
				{
					if(sfxOn)audio->playCue("explosion");
					cityCollision->damage(1);
					bolides_raw[i]->setHealth(-1);
					score -= 100 ;
					scoreFont->setFontColor(graphicsNS::RED);
					cityCollision->setColorFilter(graphicsNS::RED);
					collisionVector = D3DXVECTOR2(0,0);
					VECTOR2 foo = VECTOR2(bolides_raw[i]->getPositionX()-10, bolides_raw[i]->getPositionY()+5);
					VECTOR2 bar = VECTOR2(((float(rand()) / float(RAND_MAX)) * (20 - 10)) -10,((float(rand()) / float(RAND_MAX)) * (50)) + 0);
					createParticleEffect(foo, VECTOR2(bar.x,-10), 10);
				}


			}
			cityCollision == NULL ;
		}

		if(aliens_size > 0)
		{

			Alien** aliens_raw = (Alien**)aliens.getArray();
			if(rockets_size > 0)
			{
				for(int i = 0; i < aliens_size; ++i)
				{
					rocketCollision = (Rocket*)rockets.checkCollision(aliens_raw[i], collisionVector) ;
					if(rocketCollision != NULL)
					{
						if(sfxOn)audio->playCue("explosion");
						rocketCollision->setActive(false);
						aliens_raw[i]->setHealth(-1);
						score += 250 ;
						collisionVector = D3DXVECTOR2(0,0);
						scoreFont->setFontColor(graphicsNS::GREEN);
						VECTOR2 foo = VECTOR2(aliens_raw[i]->getPositionX()-10, aliens_raw[i]->getPositionY()+5);
						VECTOR2 bar = VECTOR2(((float(rand()) / float(RAND_MAX)) * (40 - 10)) + 10,((float(rand()) / float(RAND_MAX)) * (40)) + 0);
						createParticleEffect(foo, bar, 25);
					}
					rocketCollision == NULL ;
				}
			}
			if(aliens_size > 1)
			{
				for(int i = 0; i < aliens_size; ++i)
				{
					alienCollision = (Alien*)aliens.checkCollision(aliens_raw[i], collisionVector) ;
					if(alienCollision != NULL)
					{
						alienCollision->bounce(collisionVector,*aliens_raw[i]);
						collisionVector = D3DXVECTOR2(0,0);
					}
					alienCollision == NULL ;
				}
			}
		}

		if(spits_size > 0)
		{
			Spitball** spits_raw = (Spitball**)spits.getArray();
			City** cities_raw = (City**)cities.getArray();

			for(int i = 0; i < spits_size; ++i)
			{
				rocketCollision = (Rocket*)rockets.checkCollision(spits_raw[i], collisionVector) ;
				if(rocketCollision != NULL)
				{
					if(sfxOn)audio->playCue("hit");
					rocketCollision->setActive(false);
					spits_raw[i]->setHealth(-1);
					score += 200 ;
					collisionVector = D3DXVECTOR2(0,0);
					scoreFont->setFontColor(graphicsNS::GREEN);
					VECTOR2 foo = VECTOR2(spits_raw[i]->getPositionX()-10, spits_raw[i]->getPositionY()+5);
					VECTOR2 bar = VECTOR2(((float(rand()) / float(RAND_MAX)) * (40 - 10)) + 10,((float(rand()) / float(RAND_MAX)) * (40)) + 0);
					createParticleEffect(foo, bar, 25);
				}
				rocketCollision == NULL ;

				cityCollision = (City*)cities.checkCollision(spits_raw[i], collisionVector) ;
				if(cityCollision != NULL )
				{
					if(cityCollision->getHealth() > 0)
					{
						if(sfxOn)audio->playCue("explosion");
						cityCollision->damage(1);
						spits_raw[i]->setHealth(-1);
						score -= 200 ;
						scoreFont->setFontColor(graphicsNS::RED);
						cityCollision->setColorFilter(graphicsNS::RED);
						collisionVector = D3DXVECTOR2(0,0);
						VECTOR2 foo = VECTOR2(spits_raw[i]->getPositionX()-10, spits_raw[i]->getPositionY()+5);
						VECTOR2 bar = VECTOR2(((float(rand()) / float(RAND_MAX)) * (40 - 10)) + 10,((float(rand()) / float(RAND_MAX)) * (40)) + 0);
						createParticleEffect(foo, bar, 25);
					}

				}

				cityCollision == NULL ;
			}
		}
	}

}

//=============================================================================
// Render game items
//=============================================================================
void myGame::render()
{
	RECT scoreRect = {-400,0,400,400};

	std::stringstream ss ;
	graphics->spriteBegin(); // begin drawing sprites
	int cityMultiplier = 0;

	switch(gameStates)
	{
	case gameMenu:
		menu->displayMenu();
		mAlien.draw();
		break;
	case gamePlay:
		backgroundImage2.draw();
		backgroundImage.draw();
		starImage.draw();

		ss << score;
		scoreFont->print(ss.str(), scoreRect, DT_CALCRECT);
		scoreFont->print(ss.str(), GAME_WIDTH/2-scoreWidth/2,460);
		scoreWidth = scoreRect.right - scoreRect.left;
		cities.draw();
		spits.draw();
		bolides.draw();
		aliens.draw();
		pm.draw();
		rockets.draw();
		thePlayer.draw(thePlayer.getColorFilter());

		crossHairImage.draw();

		if(!isNight && nightCount == 0)
		{
			timer += frameTime;
			if(timer <= 4.00)dxFont->print("Those darn llamas are back at it\nagain tonight...\nCould you take care of it?", 100,100);
			else if(timer <= 9.00)
			{
				dxFont->print("Click to fire your rockets\nto stop them before they take us out.\nOh, and deal with the asteroids too.", 100,100);

			}

		}

		for (int i = 0; i < MAX_ROCKETS; i++)
			rocketsRemaining[i].draw();

		//redOver.draw();
		break;
	case endGame:
		backgroundImage2.draw();
		backgroundImage.draw();
		starImage.draw();
		//TO DO add score tally at end
		if(isNight) dxFont->setFontColor(graphicsNS::WHITE);
		ss.str("");
		ss.clear();
		if(numCities > 0) dxFont->print("Nice work!", 70, 50);
		else dxFont->print("You tried...", 70, 50);


		if(nightCount == 1) dxFont->print("You didn't even make it one night...",70,150);
		else if(nightCount == 2) dxFont->print("You made it 1 night!",70,150);
		else if(nightCount == 3) dxFont->print("You made it 2 nights!",70,150);
		else if(nightCount == 4) dxFont->print("You made it all 3 nights!",70,150);

		ss.str("");
		ss.clear();
		ss << nightCount;
		dxFont->print("\t+ 200 x " + ss.str(),70,200);

		ss.str("");
		ss.clear();
		ss<<numCities;
		dxFont->print(ss.str() + " cities survived.",70,250);

		ss.str("");
		ss.clear();
		cityMultiplier = cities.getSize();
		ss << cityMultiplier;
		dxFont->print("\t+ 100 x " + ss.str(),70,300);

		if(endedGame == false) 
		{
			nightCount--;
			score+=cityMultiplier*100;
			score+=nightCount*200;
		}

		ss.str("");
		ss.clear();
		ss << score;
		dxFont->print("Final Score: " + ss.str(),70,400);

		ss.str("");
		ss.clear();
		dxFont->print("click to continue",70,450);
		endedGame = true;
		break;
	case credits:
		creditsImage.draw();
		break;
	case instruct:
		instructImage.draw();
		break;
	case highScore:
		starImage.draw();

		dxFont->setFontColor(graphicsNS::WHITE);
		dxFont->print("High Scores", GAME_WIDTH/2 - 80, GAME_HEIGHT/8);

		for (int i = 0; i < MAX_SCORES_DISPLAYED; i++)
		{
			if (topTenScores[i] == INT_MIN)
			{
				if (i == 0)
					dxFont->print("No one has beaten the Llamas yet!", GAME_WIDTH/3 - 40, GAME_HEIGHT/3);

				break;
			}

			dxFont->print(to_string(i + 1) + ". " + to_string(topTenScores[i]), GAME_WIDTH/2 - 80, GAME_HEIGHT/4 + i * 40);
		}
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
	background2TM.onLostDevice();
	starsTM.onLostDevice();
	creditsTM.onLostDevice();
	instructTM.onLostDevice();
	cityTM.onLostDevice();
	playerTM.onLostDevice();
	spitTM.onLostDevice();
	crossHairTM.onLostDevice();

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
	background2TM.onResetDevice();
	starsTM.onResetDevice();
	creditsTM.onResetDevice();
	instructTM.onResetDevice();
	cityTM.onResetDevice();
	playerTM.onResetDevice();
	spitTM.onResetDevice();
	crossHairTM.onResetDevice();
	Game::resetAll();
	return;
}


void myGame::spawnAlien()
{
	Alien* alien = new Alien();
	if (!alien->initialize(this, alienNS::WIDTH, alienNS::HEIGHT, 2, &alienTM))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing alien entity"));

	int spawn = rand()%(GAME_HEIGHT/3);

	int choosePattern = 0;
	if(nightCount <= 1) choosePattern = 0;
	else choosePattern = rand() % 4;

	if( choosePattern == 1 || choosePattern == 3) alien->setX(-alien->getWidth());
	else alien->setX(GAME_WIDTH);

	alien->setY(spawn);

	alien->setScale(1);
	alien->setEdge(COLLISION_BOX_ALIEN);
	alien->setFrames(0,2);
	alien->setCurrentFrame(0);
	alien->setFrameDelay(0.8f);

	if(choosePattern == 0)aliens.add(alien, new Pattern(alienPattern2));
	else if(choosePattern == 1) aliens.add(alien, new Pattern(alienPattern3));
	else if(choosePattern == 2)aliens.add(alien, new Pattern(alienPattern));
	else if(choosePattern == 3)aliens.add(alien, new Pattern(alienPattern4));

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

	if(GetTickCount() % 10000)
	{
		starImage.setY(starImage.getY()-50 * frameTime);
	}

	float y = backgroundImage.getY() + (-35) * frameTime;
	backgroundImage.setY(y);

	float y2 = backgroundImage2.getY() + (-35) * frameTime;
	backgroundImage2.setY(y2);

	if(backgroundImage2.getY() <= -656)
	{
		isNight = true;
	}
	else if(backgroundImage2.getY() >= 1450)
	{
		if(isNight == true) nightCount++;
		isNight = false;
	}

	if(backgroundImage.getY() + backgroundImage.getHeight()< 0)
	{
		backgroundImage.setY(backgroundImage2.getHeight()-50);
		starImage.setY(backgroundImage.getY());

	}
	if(backgroundImage2.getY() + backgroundImage2.getHeight() < 0) 
	{
		backgroundImage.setY(-10);
		backgroundImage2.setY(backgroundImage.getHeight()-10);

	}
}
void myGame::fireRocket()
{
	if (rockets.getSize() >= MAX_ROCKETS)
		return;

	Rocket* newRocket = new Rocket();
	if (!newRocket->initialize(this, rocketNS::WIDTH, rocketNS::HEIGHT,1, &rocketTM))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing rocket entity"));
	newRocket->setEdge(COLLISION_BOX_ROCKET);
	newRocket->setScale(1);
	newRocket->setVelocity(VECTOR2(rocketNS::SPEED_X,rocketNS::SPEED_Y));


	newRocket->setX(thePlayer.getX()+15);
	newRocket->setY(thePlayer.getY());

	int xClick = input->getMouseX();
	int yClick = input->getMouseY();

	newRocket->setStartPos(newRocket->getX(),thePlayer.getY());
	VECTOR2 direc(xClick-newRocket->getX(), yClick - newRocket->getY());
	newRocket->setTargetCoords(VECTOR2(xClick,yClick));
	newRocket->setDir(direc);
	newRocket->setAngle();
	newRocket->setVisible();
	newRocket->setAliveTime();
	rockets.add(newRocket);
	if(sfxOn)audio->playCue("shoot");
}

void myGame::fireSpitball(VECTOR2 source)
{
	int randTarget = (rand()%GAME_WIDTH)+1;
	Spitball* newSpitball = new Spitball();
	if (!newSpitball->initialize(this, spitballNS::WIDTH, spitballNS::HEIGHT,2, &spitTM))
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

	newSpitball->setFrames(0,1);
	newSpitball->setCurrentFrame(0);
	newSpitball->setFrameDelay(0.3f);


	spits.add(newSpitball);
	if(sfxOn)audio->playCue("shoot");
}

void myGame::createParticleEffect(VECTOR2 pos, VECTOR2 vel, int numParticles){

	pm.setPosition(pos);
	pm.setVelocity(vel);
	pm.setVisibleNParticles(numParticles);
}


bool wayToSort(int i, int j) { return i > j; }
void myGame::addHighScores(int newScore)
{

	int allScores[MAX_SCORES_DISPLAYED + 1];

	for (int i = 0; i < MAX_SCORES_DISPLAYED; i++)
	{
		allScores[i] = topTenScores[i];
	}

	allScores[MAX_SCORES_DISPLAYED] = newScore;

	std::sort(allScores, allScores + (MAX_SCORES_DISPLAYED + 1), wayToSort);

	for (int i = 0; i < MAX_SCORES_DISPLAYED; i++)
	{
		topTenScores[i] = allScores[i];
	}
}