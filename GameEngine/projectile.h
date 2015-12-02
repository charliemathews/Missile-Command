
#ifndef PROJECTILE_H				// Prevent multiple definitions if this 
#define PROJECTILE_H				// file is included in more than one place
#define WIN32_LEAN_AND_MEAN

class Projectile;

#include "entity.h"
#include "constants.h"

namespace projectileNS
{
	const int WIDTH = 200;					// image width
	const int HEIGHT = 200;					// image height
	const int X = 0;						// location on screen
	const int Y = 0;
	const float SPEED_X = 50;				// initial velocity
	const float SPEED_Y = 50;
}

// inherits from Entity class
class Projectile : public Entity
{
private:
   // puckNS::DIRECTION direction;    
    bool collision;                 
    bool target;  
	bool alive;
	int directionX;
	int directionY;

public:
    // constructor
    Projectile();

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

    // Set target
    void setTarget(bool t) {target = t;}

    // Get collision
    bool getCollision() {return collision;}

    // Get collision type
    entityNS::COLLISION_TYPE getCollisionType() {return collisionType;}

	void setInvisible();
	void setVisible();
	bool getVisibleState();

	void enterStage();
	void camp();
	void leaveStage();

	/*
	void vectorTrack();
	void deltaTrack();
	void evade();
	*/
};
#endif

