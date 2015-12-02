/*
Author:			Charlie Mathews
Created:		November 6th, 2015
Description:	(see header)
*/

#include "entityManager.h"
#include <sstream> 
using namespace std ;

EntityManager::EntityManager()
{
	pool = NULL ;
	size = 0 ;
}

EntityManager::~EntityManager()
{
	//for (int i = 0; i < size; ++i) delete pool[i];
	Node* current = pool ;
	while(current != NULL)
	{
		//delete current->single ;
		current = current->next ;
	}

	delete pool ;
}

void EntityManager::clear()
{
	Node* current = pool ;
	while(current != NULL)
	{
		delete current->single ;
		delete current->pattern ;
		current = current->next ;
	}
}

EntityManager::Node* EntityManager::getLast()
{
	if(pool == NULL) return NULL ;
	else 
	{
		Node* current = pool ;
		while(current->next != NULL) current = current->next ;
		return current ;
	}
}

void EntityManager::remove(Entity* e)
{
	Node* previous = NULL ;
	Node* current = pool ;

	while(current != NULL)
	{
		if(current->single == e)
		{
			delete current->single ;
			delete current->pattern ;
			if(previous == NULL) pool = current->next ;
			else previous->next = current->next ;
			size-- ;
		}
		else
		{
			previous = current ;
			current = current->next ;
		}
	}
	return ;
}

void EntityManager::removeDead()
{
	Node* previous = NULL ;
	Node* current = pool ;

	while(current != NULL)
	{
		if(current->single->getActive() == false)
		{
			delete current->single ;
			delete current->pattern ;
			if(previous == NULL) pool = current->next ;
			else previous->next = current->next ;
			current = NULL ;
			size-- ;
		}
		else
		{
			previous = current ;
			current = current->next ;
		}
	}
	return ;
}

void EntityManager::add(Entity* e, Pattern* p)
{
	if(pool == NULL) pool = new Node(e, p) ;
	else
	{
		Node* current = getLast();
		current->next = new Node(e, p) ;
	}
	size++ ;
	//debugOutput() ;
}

void EntityManager::update(float frameTime)
{
	removeDead();
	Node* current = pool ;
	
	while(current != NULL)
	{
		current->single->update(frameTime) ;
		//if(current->pattern != NULL) current->pattern->run(current->single, frameTime);
		current = current->next ;
	}
}

void EntityManager::ai(float frameTime)
{
	Node* current = pool ;
	
	while(current != NULL)
	{
		if(current->pattern != NULL) current->pattern->run(current->single, frameTime);
		current = current->next ;
	}
}

void EntityManager::draw()
{ 
	Node* current = pool ;
	
	while(current != NULL)
	{
		if(current->single->getActive() == 1) current->single->draw() ;
		current = current->next ;
	}
}

// This function assumes that the first collision is the only collision.
// Eventually we can make this return a series of collisions that will take place.
Entity* EntityManager::checkCollision(Entity* ent, VECTOR2 &collisionVector)
{
	Node* current = pool ;
	while(current != NULL)
	{
		if(current->single->collidesWith(*ent, collisionVector)) return current->single ;
		current = current->next ;
	}
	return NULL ;
}

Entity** EntityManager::getArray()
{
	if(getSize() == 0) return NULL ;

	int size = getSize() ;
	Entity** temp = new Entity*[size];

	Node* current = pool ;
	int i = 0 ;
	while(current != NULL)
	{
		temp[i] = current->single ;
		current = current->next ;
		i++ ;
	}

	return temp ;
}

void EntityManager::debugOutput()
{
	stringstream ss ;
	Node* current = pool ;
	while(current != NULL) 
	{
		ss	<< "Current:" << current
			<< " Entity:" << current->single 
			<< "(" << current->single->getActive() << ")"
			<< " Next:" << current->next 
			<< endl ;
		current = current->next ;
	}
	ss << endl ;
	OutputDebugString(ss.str().c_str());
}