#include "spitball.h"
#include <sstream>
using namespace std ;

//=============================================================================
// default constructor
//=============================================================================
Spitball::Spitball() : Entity()
{
    spriteData.width = spitballNS::WIDTH;           
    spriteData.height = spitballNS::HEIGHT;
    spriteData.x = spitballNS::X;                   
    spriteData.y = spitballNS::Y;
    spriteData.rect.bottom = spitballNS::HEIGHT/2;    
    spriteData.rect.right = spitballNS::WIDTH;
    velocity.x = 0;                             
    velocity.y = 0;                             
    currentFrame = startFrame;
    radius = spitballNS::WIDTH/2.0;                 // collision radius
    collision = false;
    collisionType = entityNS::CIRCLE;
    target = false;
	edge.bottom = -spitballNS::HEIGHT/2;
	spriteData.scale = 1;
	active = true;
}

bool Spitball::initialize(Game *gamePtr, int width, int height, int ncols,
    TextureManager *textureM)
{
	directionY = -1;
	directionX = 0;
    return(Entity::initialize(gamePtr, width, height, ncols, textureM));

}

void Spitball::setInvisible()
{
	Image::setVisible(false);
	active = false;
}

void Spitball::setVisible()
{
	Image::setVisible(true);
	active = true;
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Spitball::update(float frameTime)
{
	Entity::update(frameTime);
	
	if(getHealth() <= 0)
	{
		alive = false;
		setInvisible();
		active = false;
	}

	int prevX = spriteData.x;
	int prevY = spriteData.y;
	

	spriteData.x += velocity.x ;
	spriteData.y += velocity.y ;

	setPosition(VECTOR2(spriteData.x,spriteData.y));

	if(getX() <= 0) velocity.x*=-1;
	if(getX() >= GAME_WIDTH) velocity.x *= -1;
	if(getY() > GAME_HEIGHT)
	{
		setHealth(-1) ;
	}
}
VECTOR2 Spitball::getTarget()
{
	return coords;
}
void Spitball::calcVel()
{
	float distance = sqrt((coords.x-startPos.x)*(coords.x-startPos.x)+(coords.y-startPos.y)*(coords.y-startPos.y));
	float velX = spitballNS::SPEED_X*(coords.x-startPos.x)/distance;
	float velY = spitballNS::SPEED_Y*(coords.y-startPos.y)/distance;
	setVelocity(VECTOR2(velX,velY));
}

/*
PATTERNS
*/






/*
Sensing AI
*/
/*
void Spitball::evade() // anti-tracking
{
	//add code here
	//vectorTrack() ;
	// basically just reverse direction.

	
	//VECTOR2 vel = getCenterPoint() - targetEntity.getCenterPoint() ;
	//if(vel.x == 0 && vel.y == 0) return ;
	//VECTOR2* foo = D3DXVec2Normalize(&vel, &vel);
	//setVelocity(vel);
	

	vectorTrack();
	setVelocity(-getVelocity());

	return;
}

void Spitball::deltaTrack()
{
	//VECTOR2 vel = D2DXVECTOR2(1,1);
	//VECTOR2 targetCenter = targetEntity.getCenterPoint();
	//if(getCenterPoint().y <= targetCenter.y) vel.y = -1 ;
	//if(getCenterPoint().x <= targetCenter.x) vel.x = -1 ;

	//if(vel.x == 0 && vel.y == 0) return ;
	//VECTOR2* foo = D3DXVec2Normalize(&vel, &vel);
	//setVelocity(-vel);
	return ;
}

void Spitball::vectorTrack()
{
	//n.pos += dir * speed * frametime
	VECTOR2 vel = getCenterPoint() - targetEntity.getCenterPoint() ;
	if(vel.x == 0 && vel.y == 0) return ;
	VECTOR2* foo = D3DXVec2Normalize(&vel, &vel);
	setVelocity(-vel);
	return ;
}
*/


/*
void Spitball::ai(float time, Entity &t)
{ 
	targetEntity = t;
	//vectorTrack();
	//deltaTrack();
	//evade();
	return;
}
*/

void Spitball::damage(int weapon)
{
	health -= weapon;
}
