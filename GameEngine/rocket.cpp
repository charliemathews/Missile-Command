#include "rocket.h"

//=============================================================================
// default constructor
//=============================================================================
Rocket::Rocket() : Entity()
{
	spriteData.width = rocketNS::WIDTH;           
	spriteData.height = rocketNS::HEIGHT;
	spriteData.x = rocketNS::X;                   
	spriteData.y = rocketNS::Y;
	spriteData.rect.bottom = rocketNS::HEIGHT/2;    
	spriteData.rect.right = rocketNS::WIDTH;
	velocity.x = 0;                             
	velocity.y = 0;                           
	radius = rocketNS::WIDTH/2.0;                 // collision radius
	collision = false;
	collisionType = entityNS::CIRCLE;
	target = false;
	edge.bottom = -rocketNS::HEIGHT/2;
	spriteData.scale = 1;
	active = true;
	radius = 5;

}

bool Rocket::initialize(Game *gamePtr, int width, int height, int ncols,
						TextureManager *textureM)
{
	directionY = -1;
	directionX = 0;
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));

}

void Rocket::setInvisible()
{
	Image::setVisible(false);
	active = false;
}

void Rocket::setVisible()
{
	Image::setVisible(true);
	active = true;
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Rocket::update(float frameTime)
{
	Entity::update(frameTime);
	int prevX = spriteData.x;
	int prevY = spriteData.y;


	spriteData.x += velocity.x * frameTime;
	spriteData.y += velocity.y * frameTime;

	//incPosition(D3DXVECTOR2(velocity*frameTime));
	setPosition(VECTOR2(spriteData.x,spriteData.y));
	//if(dir.x > 0)
	//{
	//	if(spriteData.x >= coords.x && spriteData.y <= coords.y)
	//	{
	//		velocity.x = 0;
	//		velocity.y = 0;	
	//		setInvisible();
	//		setActive(false);
	//		setHealth(-1);
	//	}
	//}
	//else if( dir.x <=0)
	//{
	//	if(spriteData.x <= coords.x && spriteData.y <= coords.y)
	//	{
	//		velocity.x = 0;
	//		velocity.y = 0;
	//		setInvisible();
	//		setActive(false);
	//		setHealth(-1);

	//	}
	//}

	//If the rocket goes off the screen
	if (spriteData.x < 0 || spriteData.x > GAME_WIDTH || spriteData.y > GAME_HEIGHT || spriteData.y < 0)
	{
		velocity.x = 0;
		velocity.y = 0;
		setInvisible();
		setActive(false);
		setHealth(-1);
	}


}
VECTOR2 Rocket::getTarget()
{
	return coords;
}
void Rocket::calcVel()
{
	float distance = sqrt((coords.x-startPos.x)*(coords.x-startPos.x)+(coords.y-startPos.y)*(coords.y-startPos.y));
	float velX = rocketNS::SPEED_X*(coords.x-startPos.x)/distance;
	float velY = rocketNS::SPEED_Y*(coords.y-startPos.y)/distance;
	setVelocity(VECTOR2(velX,velY));
}

/*
PATTERNS
*/






/*
Sensing AI
*/
/*
void Rocket::evade() // anti-tracking
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

void Rocket::deltaTrack()
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

void Rocket::vectorTrack()
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
void Rocket::ai(float time, Entity &t)
{ 
targetEntity = t;
//vectorTrack();
//deltaTrack();
//evade();
return;
}
*/
