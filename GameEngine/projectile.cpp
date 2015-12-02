#include "Projectile.h"
#include <sstream>
using namespace std ;

//=============================================================================
// default constructor
//=============================================================================
Projectile::Projectile() : Entity()
{
    spriteData.width = projectileNS::WIDTH;           
    spriteData.height = projectileNS::HEIGHT;
    spriteData.x = projectileNS::X;                   
    spriteData.y = projectileNS::Y;
    spriteData.rect.bottom = projectileNS::HEIGHT/2;    
    spriteData.rect.right = projectileNS::WIDTH;
    velocity.x = 0;                             
    velocity.y = 0;                             
    startFrame = 0;              
    endFrame     = 0;              
    currentFrame = startFrame;
    radius = projectileNS::WIDTH/2.0;                 // collision radius
    collision = false;
    collisionType = entityNS::BOX;
    target = false;
	edge.bottom = -projectileNS::HEIGHT/2;
	spriteData.scale = 1;
	active = true;
}

bool Projectile::initialize(Game *gamePtr, int width, int height, int ncols,
    TextureManager *textureM)
{
	directionY = 0;
	directionX = -1;
    return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

void Projectile::setInvisible()
{
	Image::setVisible(false);
	active = false;
}

void Projectile::setVisible()
{
	Image::setVisible(true);
	active = true;
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Projectile::update(float frameTime)
{
	Entity::update(frameTime);
	int prevX = spriteData.x;
	int prevY = spriteData.y;

	velocity.x = projectileNS::SPEED_X * directionX ;
	velocity.y = projectileNS::SPEED_Y * directionY ;

	spriteData.x += frameTime * velocity.x ;
	spriteData.y += frameTime * velocity.y ;

	//incPosition(D3DXVECTOR2(velocity*frameTime));
	setPosition(VECTOR2(spriteData.x,spriteData.y));
}
