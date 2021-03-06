
              // file is included in more than one place
#define WIN32_LEAN_AND_MEAN
#ifndef CITY_H                 // Prevent multiple definitions if this 
#define CITY_H   

class City;

#include "entity.h"
#include "constants.h"

namespace cityNS
{
	const int WIDTH = 58;				// image width
	const int HEIGHT = 62;					// image height
	const int X = 0;						// location on screen
	const int Y = 0;
	const float SPEED_X = 0;				// initial velocity
	const float SPEED_Y = 0;
}

// inherits from Entity class
class City : public Entity
{
private:
    bool collision;                
    bool target;  
	bool alive;
	int directionX;
	int directionY;

public:
    // constructor
    City();

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
	
	void damage(int weapon);

};
#endif

