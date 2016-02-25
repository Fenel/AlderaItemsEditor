#include <iostream>
#include <fstream>
#include "enums.h"
#include "system.h"
#include "baseItems.h"
#include "mainClass.h"

extern int mouse_x, mouse_y , mouse_b;
extern System System;
extern BaseItems BaseItems;
extern sf::RenderWindow App;
extern struct KeyStorage keyStorage;
extern std::string intToStr(int n);

MainClass::MainClass()
{
	this->guiSaveImage.loadFromFile("data/guiSave.bmp");
	this->guiSaveImage.createMaskFromColor(sf::Color(255,0,255));
	this->guiSaveTexture.loadFromImage(guiSaveImage);
	this->guiSaveIcon.setTexture(guiSaveTexture);
	this->guiSaveIcon.setPosition(776,0);

	this->guiAddItemImage.loadFromFile("data/guiAddItem.bmp");
	this->guiAddItemImage.createMaskFromColor(sf::Color(255,0,255));
	this->guiAddItemTexture.loadFromImage(guiAddItemImage);
	this->guiAddItemIcon.setTexture(guiAddItemTexture);
	this->guiAddItemIcon.setPosition(776,30);

	this->guiDeleteItemImage.loadFromFile("data/guiDeleteItem.bmp");
	this->guiDeleteItemImage.createMaskFromColor(sf::Color(255,0,255));
	this->guiDeleteItemTexture.loadFromImage(guiDeleteItemImage);
	this->guiDeleteItemIcon.setTexture(guiDeleteItemTexture);
	this->guiDeleteItemIcon.setPosition(776,60);
}

void MainClass::initialize()
{
	this->currentx = 120;
	this->currenty = 5;
	this->currentItem = BaseItems.getItemType(2);
	this->currentMinDispItem = 0;
	this->restartProperties();
}

void MainClass::addNewItem()
{
	if(BaseItems.addNewItem())
	{
		if(this->currentItem->id == BaseItems.getItemsCount()-2)
			this->currentItem = BaseItems.getItemType(BaseItems.getItemsCount()-1);

		if(this->currentMinDispItem + 36 == BaseItems.getItemsCount()-1)
			this->currentMinDispItem++;
	}
}

void MainClass::deleteLastItem()
{
	if(BaseItems.deleteLastItem())
	{
		if(this->currentItem->id == BaseItems.getItemsCount())
			this->currentItem = BaseItems.getItemType(BaseItems.getItemsCount()-1);

		if(this->currentMinDispItem + 36 > BaseItems.getItemsCount())
			this->currentMinDispItem--;
	}

}

void MainClass::restartProperties()
{
	this->elements.clear();
	this->currentx = 120;
	this->currenty = 5;

	addNumberBoxLabel("miniMapCol", currentItem->miniMapColor);
	addNumberBoxLabel("height", currentItem->height);
	addNumberBoxLabel("animcount", currentItem->animcount);
	addNumberBoxLabel("numsprites", currentItem->numsprites);
	addNumberBoxLabel("spriteID", currentItem->spriteID);
	addNumberBoxLabel("group", currentItem->group);
	addTextBoxLabel("name", currentItem->name);
	addTextBoxLabel("pluralName", currentItem->pluralName);
	addTextBoxLabel("description", currentItem->description);
	addNumberBoxLabel("maxItems",currentItem->maxItems);
	addNumberBoxLabel("weight",currentItem->weight);
	addCheckBoxLabel("showCount",currentItem->showCount); 
	addNumberBoxLabel("weaponType",currentItem->weaponType);
	addNumberBoxLabel("ammoType",currentItem->ammoType);
	addNumberBoxLabel("shootType",currentItem->shootType);
	addNumberBoxLabel("magicEffct",currentItem->magicEffect);
	addNumberBoxLabel("attack",currentItem->attack);
	addNumberBoxLabel("defence",currentItem->defence);
	addNumberBoxLabel("armor",currentItem->armor);
	addNumberBoxLabel("slotPosition",currentItem->slotPosition);
	addCheckBoxLabel("isVertical",currentItem->isVertical);       
	addCheckBoxLabel("isHorizontal",currentItem->isHorizontal);          
	addCheckBoxLabel("allowDistRead",currentItem->allowDistRead);         
	addCheckBoxLabel("clientCharges",currentItem->clientCharges);  
	addNumberBoxLabel("speed",currentItem->speed);
	addNumberBoxLabel("decayTo",currentItem->decayTo);
	addNumberBoxLabel("decayTime",currentItem->decayTime);
	addCheckBoxLabel("stopTime",currentItem->stopTime);  
	addCheckBoxLabel("canReadText",currentItem->canReadText);           
	addCheckBoxLabel("canWriteText",currentItem->canWriteText); 
	addNumberBoxLabel("maxTextLen",currentItem->maxTextLen);

	addCheckBoxLabel("stackable",currentItem->stackable);             
	addCheckBoxLabel("useable",currentItem->useable);               
	addCheckBoxLabel("moveable",currentItem->moveable);              
	addCheckBoxLabel("alwaysOnTop",currentItem->alwaysOnTop); 
	addNumberBoxLabel("alwTopOrder",currentItem->alwaysOnTopOrder);
	addCheckBoxLabel("pickupable",currentItem->pickupable);            
	addCheckBoxLabel("hasHeight",currentItem->hasHeight);             
	addCheckBoxLabel("rotable",currentItem->rotable);      
	addNumberBoxLabel("rotateTo",currentItem->rotateTo);

	addNumberBoxLabel("runeInt",currentItem->runeIntelligence);

	addNumberBoxLabel("wieldInfo",currentItem->wieldInfo);
	addNumberBoxLabel("vocation",currentItem->vocation);
	addNumberBoxLabel("minReqDex",currentItem->minReqDex);
	addNumberBoxLabel("minReqStr",currentItem->minReqStr);
	addNumberBoxLabel("minReqInt",currentItem->minReqInt);
	addNumberBoxLabel("minReqMPW",currentItem->minReqMPW);

	addNumberBoxLabel("lightLevel",currentItem->lightLevel);
	addNumberBoxLabel("lightColor",currentItem->lightColor);

	addCheckBoxLabel("floorChangeDown",currentItem->floorChangeDown);  
	addCheckBoxLabel("floorChangeNorth",currentItem->floorChangeNorth); 
	addCheckBoxLabel("floorChangeSouth",currentItem->floorChangeSouth); 
	addCheckBoxLabel("floorChangeEast",currentItem->floorChangeEast);  
	addCheckBoxLabel("floorChangeWest",currentItem->floorChangeWest);  
	addCheckBoxLabel("blockSolid",currentItem->blockSolid);       
	addCheckBoxLabel("blockProjectile",currentItem->blockProjectile);  
	addCheckBoxLabel("blockPathFind",currentItem->blockPathFind);  

	addNumberBoxLabel("trsEquipTo",currentItem->transformEquipTo);
	addNumberBoxLabel("trsDeEquipTo",currentItem->transformDeEquipTo);
	addCheckBoxLabel("showCharges",currentItem->showCharges);
	addNumberBoxLabel("charges",currentItem->charges);
	addNumberBoxLabel("shootRange",currentItem->shootRange);
	addNumberBoxLabel("ammoAction",currentItem->ammoAction);
	addNumberBoxLabel("combatType",currentItem->combatType);
}

MainClass::~MainClass()
{
               
}

void MainClass::loop()
{
	while(App.isOpen())
	{		
		sf::Event Event;
        while (App.pollEvent(Event))
        {
			if (Event.type == Event.MouseButtonPressed && sf::Mouse::isButtonPressed(sf::Mouse::Left))
			mouse_b = 1;
			if (Event.type == Event.MouseButtonPressed && sf::Mouse::isButtonPressed(sf::Mouse::Right))
			mouse_b = 2;
			if (Event.type == Event.MouseButtonPressed && sf::Mouse::isButtonPressed(sf::Mouse::Middle))
			mouse_b = 3;
			if (Event.type == Event.MouseButtonReleased && (Event.mouseButton.button == sf::Mouse::Left || Event.mouseButton.button == sf::Mouse::Right || Event.mouseButton.button == sf::Mouse::Middle))
			mouse_b = 0;
			if (Event.type == Event.MouseMoved)
			{
				mouse_x = Event.mouseButton.x;
				mouse_y = Event.mouseButton.y;
			}
			if(Event.type == sf::Event::KeyPressed)
	        {
				if(Event.key.code == sf::Keyboard::Down && this->currentMinDispItem + 36 < BaseItems.getItemsCount())
				{
					this->currentMinDispItem++;
				}
				else if(Event.key.code == sf::Keyboard::Up && this->currentMinDispItem > 0)
					this->currentMinDispItem--;
				else
				{
					System.keyProcessed = false;
					keyStorage.code = Event.key.code;
					keyStorage.alt = Event.key.alt;
					keyStorage.shift = Event.key.shift;
					keyStorage.control = Event.key.control;
					keyStorage.unicode = Event.text.unicode;
				}
	        }
			if(Event.type == sf::Event::MouseButtonPressed)
	        {
				if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && Event.mouseButton.x > 0 && Event.mouseButton.x < 100 && Event.mouseButton.y > 65 && Event.mouseButton.y < 600 && System.hold == false)
				{
					for(unsigned int y = 0; y < BaseItems.getItemsCount() - this->currentMinDispItem + 1; y++)
					{
						if(Event.mouseButton.y >= y*15+65 && Event.mouseButton.y < y*15 + 80)
						{
							this->currentItem = BaseItems.getItemType(y + this->currentMinDispItem);
							this->restartProperties();
							System.hold = true;
						}
					}
				}
				else if(!elements.empty() && System.hold == false)
				{
					for(unsigned int iter = 0; iter < elements.size(); iter++)
					{
						if(elements[iter]->proceed())
						{
							System.hold = true;
							break;
						}
					}
				}
				if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && Event.mouseButton.x > 776 && Event.mouseButton.x < 800 && Event.mouseButton.y > 0 && Event.mouseButton.y < 24 && System.hold == false)
				{
					BaseItems.save();
					System.hold = true;
				}
				if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && Event.mouseButton.x > 776 && Event.mouseButton.x < 800 && Event.mouseButton.y > 30 && Event.mouseButton.y < 54 && System.hold == false)
				{
					this->addNewItem();
					System.hold = true;
				}
				if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && Event.mouseButton.x > 776 && Event.mouseButton.x < 800 && Event.mouseButton.y > 60 && Event.mouseButton.y < 84 && System.hold == false)
				{
					this->deleteLastItem();
					System.hold = true;
				}
	        } 
			if(Event.type == sf::Event::MouseButtonReleased)
	        {
				 System.hold = false;
				
	        } 
			if (Event.type == Event.MouseWheelMoved && Event.mouseWheel.x > 0 && Event.mouseWheel.x < 100 && Event.mouseWheel.x > 65 && Event.mouseWheel.x < 600)
			{
				if(Event.mouseWheel.delta == true && this->currentMinDispItem + 36 < BaseItems.getItemsCount())
				{
					this->currentMinDispItem++;
				}
				else if(Event.mouseWheel.delta == false && this->currentMinDispItem > 0)
					this->currentMinDispItem--;
			}
			if(Event.type == sf::Event::Closed)
			   App.close();
        }
		if(!elements.empty())
			for(unsigned int iter = 0; iter < elements.size(); iter++)
			{
				elements[iter]->proceed();
				elements[iter]->draw();
			}

		this->itemsList();
		System.renderItemType(32,32,this->currentItem);
		App.draw(guiSaveIcon);
		App.draw(guiAddItemIcon);
		App.draw(guiDeleteItemIcon);

		App.display();
		App.clear(sf::Color(160,160,160));
	}
}

void MainClass::itemsList()
{
	static sf::RectangleShape rectangle;
	static sf::Text text;
	static std::string basestring = "Item ID: ";

	rectangle.setFillColor(sf::Color(128, 128, 128));
	rectangle.setSize(sf::Vector2f(float(64), float(64)));
	rectangle.setOutlineColor(sf::Color(0, 0, 0));
	rectangle.setOutlineThickness(1);
	rectangle.setPosition(float(0), float(0));
	App.draw(rectangle);

	bool color_mig = false;
	for(int i = 0; i < 41; i++)
	{
		if(color_mig == false)
		{
			color_mig = true;
			rectangle.setFillColor(sf::Color(96, 96, 96));
		}
		else
		{
			color_mig = false; 
			rectangle.setFillColor(sf::Color(128, 128, 128));
		}
		rectangle.setSize(sf::Vector2f(float(100), float(14)));
		if(i + this->currentMinDispItem == this->currentItem->id)
		{
			rectangle.setSize(sf::Vector2f(float(100), float(13)));
			rectangle.setOutlineColor(sf::Color(255, 0, 0));
		}
		else
		{
			rectangle.setOutlineColor(sf::Color(0, 0, 0));
		}
		rectangle.setOutlineThickness(1);
		rectangle.setPosition(float(0), float(65+i*15));
		App.draw(rectangle);

		if(i + this->currentMinDispItem <= BaseItems.getItemsCount())
		{
			std::string napis;
			napis = basestring;
			napis += intToStr(i + this->currentMinDispItem);
			text.setPosition(float(2),float(65+i*15));
			text.setString(napis);
			text.setCharacterSize(10);
			App.draw(text);
		} 
	}
}

void MainClass::addCheckBoxLabel(std::string label, bool &Pcallback)
{
	if(currenty > 570)
	{
		currenty = 5;
		currentx = 450;
	}
	elements.push_back(new GuiCheckBoxLabel(currentx, currenty, label, Pcallback));
	currenty+=17;
}

void MainClass::addTextBoxLabel(std::string label, std::string &text)
{
	if(currenty > 570)
	{
		currenty = 5;
		currentx = 450;
	}
	elements.push_back(new GuiTextBoxLabel(currentx, currenty, label, text));
	currenty+=17;
}

void MainClass::addNumberBoxLabel(std::string label, int32_t &number)
{
	if(currenty > 570)
	{
		currenty = 5;
		currentx = 450;
	}
	elements.push_back(new GuiNumberBoxLabel(currentx, currenty, label, number));
	currenty+=17;
}
