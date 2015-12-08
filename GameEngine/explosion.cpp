#include "explosion.h"

//=============================================================================
// default constructor
//=============================================================================
Explosion::Explosion() : Entity()
{
	spriteData.width = explosionNS::WIDTH;           
	spriteData.height = explosionNS::HEIGHT;
	spriteData.x = explosionNS::X;                   
	spriteData.y = explosionNS::Y;
	spriteData.rect.bottom = explosionNS::HEIGHT/2;    
	spriteData.rect.right = explosionNS::WIDTH;
	velocity.x = 0;                             
	velocity.y = 0;                           
	radius = explosionNS::WIDTH/2.0;                 // collision radius
	collision = false;
	collisionType = entityNS::CIRCLE;
	target = false;
	edge.bottom = -explosionNS::HEIGHT/2;
	spriteData.scale = 1;
	active = true;
	radius = 5;
	endFrame = 3;
	startFrame = 0;
	health = 1;

}

bool Explosion::initialize(Game *gamePtr, int width, int height, int ncols,
						TextureManager *textureM)
{
	directionY = -1;
	directionX = 0;
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));

}

void Explosion::setInvisible()
{
	Image::setVisible(false);
	active = false;
}

void Explosion::setVisible()
{
	Image::setVisible(true);
	active = true;
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Explosion::update(float frameTime)
{
	Entity::update(frameTime);
	if(getHealth() <= 0)
	{
		setInvisible();
		setActive(false);
		alive = false;
	}
	/*if(getCurrentFrame() == 0)
	{
		spriteData.width = 23;
	}
	else if(getCurrentFrame() == 1)
	{
		spriteData.width = 37;
	}*/
	else if(getCurrentFrame() == 2) 
	{
		setFrameDelay(.6f);
	}
	else if(getCurrentFrame() == 3) animComplete = true;


}



/*
Sensing AI
*/
/*
void Explosion::evade() // anti-tracking
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

void Explosion::deltaTrack()
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

void Explosion::vectorTrack()
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
void Explosion::ai(float time, Entity &t)
{ 
targetEntity = t;
//vectorTrack();
//deltaTrack();
//evade();
return;
}
*/
