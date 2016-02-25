#include <iostream>
#include <SFML/Graphics.hpp>
#include "system.h"
#include "mainClass.h"
#include "itemType.h"
#include "item.h"
#include "baseItems.h"

extern sf::RenderWindow App;
extern BaseItems BaseItems;
extern MainClass MainClass;

System::System(unsigned int _width, unsigned int _height, unsigned int _res)
{
	windowWidth = _width;
	windowHeight = _height;
	res = _res;
	App.create(sf::VideoMode(windowWidth, windowHeight, res), "Fusion Items Editor 2");
    
    activeTextbox = 0;
    globalTextboxesCount = 0;    
    hold = false;
	keyProcessed = true;

    font.loadFromFile("data/courier.ttf");
}

System::~System()
{
}

void System::renderItemType(int x, int y, ItemType *item)
{
	if(item->id > 1 && item->spriteID < BaseItems.spritesProperties.size())
	{	
		switch(BaseItems.spritesProperties.at(item->id).type)
		{
			case 0: //1x1
			  BaseItems.getItemType(item->id)->sprite.setPosition(float(x),float(y));
			  break;
			case 1: //2x1
			  BaseItems.getItemType(item->id)->sprite.setPosition(float(x-32),float(y));
			  break;
			case 2: //1x2
			  BaseItems.getItemType(item->id)->sprite.setPosition(float(x),float(y-32));
			  break;
			case 3: //2x2
			  BaseItems.getItemType(item->id)->sprite.setPosition(float(x-32),float(y-32));
			  break;
		}
		App.draw(BaseItems.getItemType(item->id)->sprite);
	}
}