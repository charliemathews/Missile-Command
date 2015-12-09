/*
Author:			Charlie Mathews
Created:		December 8th, 2015
Description:	
*/

#ifndef TEXT_MANAGER_H				// Prevent multiple definitions if this 
#define TEXT_MANAGER_H				// file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "constants.h"
#include "textDX.h"
#include <string>
using std::string ;

class TextManager
{
private:
	struct Node {
		TextDX* single ;
		Node* next ;
		string content ;
		float duration, elapsed ;
		int x, y;
		Node(TextDX* t) : single(t), content("null"), duration(0), next(NULL), elapsed(0), x(0), y(0) {} ;
		Node(TextDX* t, string s, float d, int x, int y) : single(t), content(s), duration(d), next(NULL), elapsed(0), x(x), y(y) {} ;
		Node(TextDX* t, string s, float d, int x, int y, Node* n) : single(t), content(s), duration(d), next(n), elapsed(0), x(x), y(y) {} ;
	};
	Node* pool ;
	int size ;
	Node* getLast() ;

public:
	TextManager();
	~TextManager();
	void clear();
	void add(Graphics* graphics, const DWORD color, float duration, int height, string text, int x, int y);
	int getSize() { return size ; }

	void draw(float frameTime);
	void removeDead();
};
#endif