#include "bolide.h"

//=============================================================================
// default constructor
//=============================================================================
Bolide::Bolide() : Projectile()
{
    spriteData.width = bolideNS::WIDTH;           
    spriteData.height = bolideNS::HEIGHT;
    spriteData.x = bolideNS::X;                   
    spriteData.y = bolideNS::Y;
    spriteData.rect.bottom = bolideNS::HEIGHT/2;    
    spriteData.rect.right = bolideNS::WIDTH;
    velocity.x = 0;                             
    velocity.y = 0;                             
    currentFrame = startFrame;
    radius = bolideNS::WIDTH/2.0;                 // collision radius
    collision = false;
	collisionType = entityNS::CIRCLE;
    target = false;
	edge.bottom = -bolideNS::HEIGHT/2;
	spriteData.scale = 1;
	active = true;

}

bool Bolide::initialize(Game *gamePtr, int width, int height, int ncols,
    TextureManager *textureM)
{
	directionY = -1;
	directionX = 0;
	rotateDirection = 1;
    return(Entity::initialize(gamePtr, width, height, ncols, textureM));

}

void Bolide::setInvisible()
{
	Image::setVisible(false);
	active = false;
}

void Bolide::setVisible()
{
	Image::setVisible(true);
	active = true;
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Bolide::update(float frameTime)
{
	Entity::update(frameTime);
	
	if(getHealth() <= 0)
	{
		alive = false;
		setInvisible();
		active = false;
		return ;
	}

	int prevX = spriteData.x;
	int prevY = spriteData.y;
	setDegrees(getDegrees()+rotateDirection);
	VECTOR2 bulletLoc(spriteData.x,spriteData.y);
	////bulletLoc.x = startPos.x + bolideNS::SPEED_X* frameTime * dir.x;
	////bulletLoc.y = startPos.y + bolideNS::SPEED_Y* frameTime * dir.y;
	bulletLoc.x += velocity.x;
	bulletLoc.y += velocity.y;

	spriteData.x = bulletLoc.x ;
	spriteData.y = bulletLoc.y ;

	//incPosition(D3DXVECTOR2(velocity*frameTime));
	setPosition(VECTOR2(spriteData.x,spriteData.y));

	if(getX() <= 0) velocity.x*=-1;
	if(getX() >= GAME_WIDTH) velocity.x *= -1;
	if(getY() > GAME_HEIGHT)
	{
		setHealth(-1) ;
	}
}
VECTOR2 Bolide::getTarget()
{
	return coords;
}
void Bolide::calcVel()
{
	float distance = sqrt((coords.x-startPos.x)*(coords.x-startPos.x)+(coords.y-startPos.y)*(coords.y-startPos.y));
	float velX = velocity.x/2*(coords.x-startPos.x)/distance;
	float velY = velocity.y/2*(coords.y-startPos.y)/distance;
	setVelocity(VECTOR2(velX,velY));
}

/*
PATTERNS
*/






/*
Sensing AI
*/
/*
void Bolide::evade() // anti-tracking
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

void Bolide::deltaTrack()
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

void Bolide::vectorTrack()
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
void Bolide::ai(float time, Entity &t)
{ 
	targetEntity = t;
	//vectorTrack();
	//deltaTrack();
	//evade();
	return;
}
*/

void Bolide::damage(int weapon)
{
	health -= weapon;
}
