/*
Author:			Charlie Mathews
Created:		December 8th, 2015
Description:	(see header)
*/

#include "textManager.h"
#include <string>
#include <sstream> 
using namespace std ;

TextManager::TextManager()
{
	pool = NULL ;
	size = 0 ;
}

TextManager::~TextManager()
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

void TextManager::clear()
{
	Node* current = pool ;
	while(current != NULL)
	{
		delete current->single ;
		//delete current->pattern ;
		current = current->next ;
	}
	pool = NULL ;
	size = 0 ;
}

TextManager::Node* TextManager::getLast()
{
	if(pool == NULL) return NULL ;
	else 
	{
		Node* current = pool ;
		while(current->next != NULL) current = current->next ;
		return current ;
	}
}

void TextManager::removeDead()
{
	Node* previous = NULL ;
	Node* current = pool ;

	while(current != NULL)
	{
		if(current->elapsed >= current->duration)
		{
			delete current->single ;
			//delete current->pattern ;
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

void TextManager::add(Graphics* graphics, const DWORD color, float duration, int height, string text, int x, int y)
{
	TextDX* newText = new TextDX();
	if(newText->initialize(graphics, height, true, false, "Retro Computer") == false)
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing text font"));
	newText->setFontColor(color);

	if(pool == NULL) pool = new Node(newText, text, duration, x, y) ;
	else
	{
		Node* current = getLast();
		current->next = new Node(newText, text, duration, x, y) ;
	}
	size++ ;
	//debugOutput() ;
}

void TextManager::draw(float frameTime)
{ 
	//dxFont->print("High Scores", 50, GAME_HEIGHT/8);
	Node* current = pool ;
	
	while(current != NULL)
	{
		//if(current->single->getActive() == 1) current->single->draw(current->single->getColorFilter()) ;
		current->elapsed += frameTime ;
		if(current->elapsed <= current->duration || current->duration == 0)
		{
			string content = current->content ;
			current->single->print(content, current->x, current->y);
		}
		current = current->next ;
	}

	removeDead();
}
