
              // file is included in more than one place
#define WIN32_LEAN_AND_MEAN
#ifndef EXPLOSION_H                 // Prevent multiple definitions if this 
#define EXPLOSION_H   
class explosion;

#include "entity.h"
#include "constants.h"

namespace explosionNS
{
	const int WIDTH = 71;					// image width
	const int HEIGHT = 75;					// image height
	const int X = 0;						// location on screen
	const int Y = 0;
}

// inherits from Entity class
class Explosion : public Entity
{
private:
   // puckNS::DIRECTION direction;    
    bool collision;                 
    bool target;  
	bool alive;
	int directionX;
	int directionY;
	float angle;
	int aliveTime;
	D3DXVECTOR2 startPos;
	D3DXVECTOR2 dir;
	D3DXVECTOR2 coords;

public:
    // constructor
    Explosion();

    // inherited member functions
    virtual bool initialize(Game *gamePtr, int width, int height, int ncols,
                            TextureManager *textureM);
    void update(float frameTime);

    // Set collision Boolean
    void setCollision(bool c)
    {collision = c;}

    // Set collision type (NONE, CIRCLE, BOX, ROTATED_BOX)
    virtual void setCollisionType(entityNS::COLLISION_TYPE ctype)
    {collisionType = ctype;}

    // Set RECT structure used for BOX and ROTATED_BOX collision detection.
    void setEdge(RECT e) {edge = e;}

    // Get collision
    bool getCollision() {return collision;}

    // Get collision type
    entityNS::COLLISION_TYPE getCollisionType() {return collisionType;}

	void setInvisible();
	void setVisible();
	bool getVisibleState();


	void setAliveTime()
	{
		aliveTime = GetTickCount();
	}
};
#endif

