#include "alien.h"
#include <sstream>
using namespace std ;

//=============================================================================
// default constructor
//=============================================================================
Alien::Alien() : Entity()
{
    spriteData.width = alienNS::WIDTH;           
    spriteData.height = alienNS::HEIGHT;
    spriteData.x = alienNS::X;                   
    spriteData.y = alienNS::Y;
    spriteData.rect.bottom = alienNS::HEIGHT/2;    
    spriteData.rect.right = alienNS::WIDTH;
    velocity.x = 0;                             
    velocity.y = 0;                             
    startFrame = 0;              
    endFrame     = 0;              
    currentFrame = startFrame;
    radius = alienNS::WIDTH/3.0;                 // collision radius
    collision = false;
    collisionType = entityNS::CIRCLE;
    target = false;
	edge.bottom = -alienNS::HEIGHT/2;
	spriteData.scale = 1;
	active = true;

}

bool Alien::initialize(Game *gamePtr, int width, int height, int ncols,
    TextureManager *textureM)
{
	directionY = 0;
	directionX = -1;
    return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

void Alien::setInvisible()
{
	Image::setVisible(false);
	active = false;
}

void Alien::setVisible()
{
	Image::setVisible(true);
	active = true;
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Alien::update(float frameTime)
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

	//velocity.x = alienNS::SPEED_X * directionX ;
	//velocity.y = alienNS::SPEED_Y * directionY ;

	spriteData.x += frameTime * velocity.x ;
	spriteData.y += frameTime * velocity.y ;

	//incPosition(D3DXVECTOR2(velocity*frameTime));
	setPosition(VECTOR2(spriteData.x,spriteData.y));

}


/*
Sensing AI
*/
/*
void Alien::evade() // anti-tracking
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

void Alien::deltaTrack()
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

void Alien::vectorTrack()
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
void Alien::ai(float time, Entity &t)
{ 
	targetEntity = t;
	//vectorTrack();
	//deltaTrack();
	//evade();
	return;
}
*/
