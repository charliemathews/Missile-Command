/*
Author:			Charlie Mathews
Created:		November 6th, 2015
Description:	To serve as a substitute for vectors when storing a series of entities.
*/

#ifndef ENTITY_MANAGER_H				// Prevent multiple definitions if this 
#define ENTITY_MANAGER_H				// file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "constants.h"
#include "entity.h"
#include "pattern.h"
#include <string>

class EntityManager
{
private:
	struct Node {
		Entity* single ;
		Pattern* pattern ;
		Node* next ;
		Node(Entity* s) : single(s), pattern(NULL), next(NULL) {} ;
		Node(Entity* s, Pattern* p) : single(s), pattern(p), next(NULL) {} ;
		Node(Entity* s, Pattern* p, Node* n) : single(s), pattern(p), next(n) {} ;
	};
	Node* pool ;
	int size ;
	Node* getLast() ;
	void debugOutput() ;

public:
	EntityManager();
	~EntityManager();
	void clear();
	void remove(Entity* e);
	//void add(Entity* e);
	void add(Entity* e, Pattern* p = NULL);
	Entity** getArray();
	int getSize() { return size ; }

	void update(float frameTime);
	void ai(float frameTime);
	void draw();
	Entity* checkCollision(Entity* ent, VECTOR2 &collisionVector);
	void removeDead();
};
#endif