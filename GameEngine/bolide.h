
              // file is included in more than one place
#define WIN32_LEAN_AND_MEAN
#ifndef BOLIDE_H                 // Prevent multiple definitions if this 
#define BOLIDE_H   
class Bolide;

#include "entity.h"
#include "projectile.h"
#include "constants.h"

#define PI 3.14159265
namespace bolideNS
{
	const int WIDTH = 60;					// image width
	const int HEIGHT = 60;					// image height
	const int X = 0;						// location on screen
	const int Y = 0;
	const float SPEED_X = 1;				// initial velocity
	const float SPEED_Y = 1;
	}

// inherits from Entity class
class Bolide : public Projectile
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
	int rotateDirection;
	D3DXVECTOR2 startPos;
	D3DXVECTOR2 dir;
	D3DXVECTOR2 coords;

public:
    // constructor
    Bolide();

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

	void setStartPos(int x, int y)
	{
		startPos.x = x;
		startPos.y = y;
	}
	void setTargetCoords(int x, int y)
	{
		coords = VECTOR2(x,y);
	}
	void setDir()
	{
		dir = VECTOR2(coords.x-getX(),coords.y - getY());
		D3DXVec2Normalize(&dir,&dir);
	}
	void setAngle()
	{
		angle = atan2(dir.y, dir.x);
		setRadians(angle);
		calcVel();
	}
	void calcVel();
	VECTOR2 getTarget();

	void setAliveTime()
	{
		aliveTime = GetTickCount();
	}
	void damage(int weapon);
};
#endif

