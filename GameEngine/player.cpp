#include "player.h"
#include <sstream>
using namespace std ;

//=============================================================================
// default constructor
//=============================================================================
Player::Player() : Entity()
{
    spriteData.width = playerNS::WIDTH;           
    spriteData.height = playerNS::HEIGHT;
    spriteData.x = playerNS::X;                   
    spriteData.y = playerNS::Y;
    spriteData.rect.bottom = playerNS::HEIGHT/2;    
    spriteData.rect.right = playerNS::WIDTH;
    velocity.x = 0;                             
    velocity.y = 0;                             
    startFrame = 0;              
    endFrame     = 0;              
    currentFrame = startFrame;
    radius = playerNS::WIDTH/2.0;                 // collision radius
    collision = false;
    collisionType = entityNS::BOX;
    target = false;
	edge.bottom = -playerNS::HEIGHT/2;
	spriteData.scale = 1;
	active = true;

}

bool Player::initialize(Game *gamePtr, int width, int height, int ncols,
    TextureManager *textureM)
{
	directionY = 0;
	directionX = -1;
    return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

void Player::setInvisible()
{
	Image::setVisible(false);
	active = false;
}

void Player::setVisible()
{
	Image::setVisible(true);
	active = true;
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Player::update(float frameTime)
{
	Entity::update(frameTime);

}
