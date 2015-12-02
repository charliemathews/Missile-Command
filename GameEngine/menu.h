
              
#ifndef MENU_H              // Prevent multiple definitions if this 
#define MENU_H				// file is included in more than one place
#define WIN32_LEAN_AND_MEAN

class Menu;

#include "graphics.h"
#include "constants.h"
#include "textDX.h"
#include <string>
#include <sstream>
#include "input.h"
#include "textureManager.h"
#include "image.h"

// #include <math.h> ... eliminate warnings with (int) floor(aFloat + 0.5);

namespace menuNS
{ }

// inherits from Entity class
class Menu 
{
private:
   TextDX *menuItemFont;
   TextDX *menuItemFontHighlight;
   TextDX *menuHeadingFont;
   Input   *input;         // pointer to the input system
   Graphics *graphics;

   Image llamaHead;
   TextureManager llamaTexture;

   int selectedItem;
   std::string menuHeading;
   std::string menuItem1;
   std::string menuItem2;
   std::string menuItem3;
   std::string menuItem4;
   D3DXVECTOR2 menuAnchor;
   int verticalOffset;
   int linePtr;
   COLOR_ARGB highlightColor ;
   COLOR_ARGB normalColor;
   bool upDepressedLastFrame;
   bool downDepressedLastFrame;
   bool enterDepressedLastFrame;
   int lastPressed;

public:
    // constructor
    Menu();
	void initialize(Graphics *g, Input *i);
	int update();
	int getSelectedItem() {return selectedItem;}
	void displayMenu();
};
#endif

