#include "city.h"
#include <sstream>
using namespace std ;

//=============================================================================
// default constructor
//=============================================================================
City::City() : Entity()
{
    spriteData.width = cityNS::WIDTH;           
    spriteData.height = cityNS::HEIGHT;
	health = 4;
    spriteData.rect.bottom = cityNS::HEIGHT/2;    
    spriteData.rect.right = cityNS::WIDTH;
    velocity.x = 0;                             
    velocity.y = 0;                             
    startFrame = 0;              
    endFrame     = 0;              
    currentFrame = startFrame;
    radius = cityNS::WIDTH/2.0;                 // collision radius
    collision = false;
    collisionType = entityNS::CIRCLE;
    target = false;
	edge.bottom = -cityNS::HEIGHT/2;
	spriteData.scale = 1;
	active = true;

}

bool City::initialize(Game *gamePtr, int width, int height, int ncols,
    TextureManager *textureM)
{
	directionY = 0;
	directionX = -1;
    return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

void City::setInvisible()
{
	Image::setVisible(false);
	active = false;
}

void City::setVisible()
{
	Image::setVisible(true);
	active = true;
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void City::update(float frameTime)
{
	Entity::update(frameTime);
	int prevX = spriteData.x;
	int prevY = spriteData.y;
	if(health == 3) setCurrentFrame(1);
	else if(health == 2) setCurrentFrame(2);
	if(health <= 0) 
	{
		alive = false;
		setEdge(NO_COL_BOX);
		setCurrentFrame(3);
	}
	//incPosition(D3DXVECTOR2(velocity*frameTime));
	setPosition(VECTOR2(spriteData.x,spriteData.y));
}

void City::damage(int weapon)
{
	health -=  weapon;
}

