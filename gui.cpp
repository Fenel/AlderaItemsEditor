#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "enums.h"
#include "system.h"
#include "gui.h"

extern sf::RenderWindow App;
extern System System;
extern sf::Texture guiCheckBox, guiCheckBoxChecked;
extern int mouse_x, mouse_y, mouse_b;
extern struct KeyStorage keyStorage;
extern bool SFKeyToString(unsigned int keycode, char &keyStr, bool numbers = false); 
extern std::string intToStr(int n);

//GuiElement::GuiElement()
//{
//}

void GuiElement::draw()
{
	#ifdef _DEBUG
		std::cout << "GuiElement Virtual Draw" << std::endl;
	#endif
}

bool GuiElement::proceed()
{
     return false;
}

GuiCheckBoxLabel::GuiCheckBoxLabel(int x, int y, std::string _text, bool &Pcallback) : callback(Pcallback)
{
    local_x = x;
    local_y = y;

	this->text.setFont(System.font);
    this->text.setString(_text);
	this->text.setPosition(float(x + 15), float(y));
	this->text.setCharacterSize(11);

	this->unchecked.setTexture(guiCheckBox);
	this->unchecked.setPosition(float(x+1), float(y+1));

	this->checked.setTexture(guiCheckBoxChecked);
	this->checked.setPosition(float(x+1), float(y+1));

	rectangle.setSize(sf::Vector2f(float(318), float(15)));
	rectangle.setFillColor(sf::Color(32,32,32));
	rectangle.setOutlineColor(sf::Color(255, 255, 255));
	rectangle.setOutlineThickness(1);
	rectangle.setPosition(float(local_x), float(local_y));
}


bool GuiCheckBoxLabel::proceed()
{
      if(mouse_x >= local_x+1 && mouse_x <= local_x + 13 && mouse_y >= local_y+1 && mouse_y <= local_y + 13 && mouse_b == 1 && System.hold == false)
      {
		  callback = !callback;
          return true;
      }
	  return false;
}

void GuiCheckBoxLabel::draw()
{
	App.draw(rectangle);      

	if(callback == false)
	{
		App.draw(unchecked);
	}
	else
	{
		App.draw(checked);
	}
	App.draw(text);
}

GuiTextBoxLabel::GuiTextBoxLabel(int x, int y, std::string _label, std::string &Pcallback) : callback(Pcallback)
{
	this->caret = callback.size()-1;
	this->insert = true;
	this->iter = callback.end();

    System.globalTextboxesCount++;
    id = System.globalTextboxesCount;
    blinking = clock();
	this->label = _label;
	this->local_x = x;
	this->local_y = y;

	this->labelSF.setFont(System.font);
    this->labelSF.setString(_label);
	this->labelSF.setPosition(float(x+2), float(y));
	this->labelSF.setCharacterSize(12);

	this->callbackSF.setFont(System.font);
    this->callbackSF.setString(callback);
	this->callbackSF.setPosition(float(x+100), float(y));
	this->callbackSF.setCharacterSize(12);

	rectangle.setSize(sf::Vector2f(float(100), float(15)));
	rectangle.setOutlineColor(sf::Color(255, 255, 255));
	rectangle.setOutlineThickness(1);
	rectangle.setPosition(float(x), float(y));
}

bool GuiTextBoxLabel::proceed()
{
	if( mouse_x >= local_x+100 && mouse_x <= local_x + 320 && mouse_y >= local_y && mouse_y <= local_y + 15 && mouse_b == 1)
    {
        System.activeTextbox = id;
        return true;
    }
	if(System.activeTextbox == id && blinking + 1000 <= clock())
	{
		blinking = clock();
	}
    if(System.activeTextbox == id && System.keyProcessed == false)
	{ 
		System.keyProcessed = true;
		char ASCII;

		if(SFKeyToString(keyStorage.unicode, ASCII))
		{
		  if(insert || iter == callback.end())
		  {
			 iter = callback.insert(iter, ASCII);
		  }

		   else
		  {
			  callback.replace(caret, 1, 1, ASCII);
		  }
		  caret++;
		   iter++;
		}
		else
		{
		  switch(keyStorage.code)
		   {
			case sf::Keyboard::Delete:
			 if(iter != callback.end()) iter = callback.erase(iter);
			   break;

			case sf::Keyboard::Back:
			 if(iter != callback.begin())
			 {
			   caret--;
			   iter--;
			   iter = callback.erase(iter);
			 }break;
		 
			 case sf::Keyboard::Right:
			 if(iter != callback.end())   caret++, iter++;
			   break;
		 
			 case sf::Keyboard::Left:
			 if(iter != callback.begin()) caret--, iter--;
			   break;
		 
			 case sf::Keyboard::Insert:
			 insert = !insert;
			   break;
		       
			 case sf::Keyboard::Tab:
			 caret = 0;
			 System.activeTextbox++;
			   break;                  

			 default:
			   break;
		   } 
		}
		callbackSF.setString(callback);
		return true;
	}
	return false;
}

void GuiTextBoxLabel::draw()
{  
	rectangle.setSize(sf::Vector2f(float(100), float(15)));
	rectangle.setFillColor(sf::Color(32,32,32));
	rectangle.setOutlineColor(sf::Color(255, 255, 255));
	rectangle.setOutlineThickness(1);
	rectangle.setPosition(float(local_x), float(local_y));
	App.draw(rectangle);

	rectangle.setSize(sf::Vector2f(float(220), float(15)));
	rectangle.setFillColor(sf::Color(96,96,96));
	rectangle.setPosition(float(local_x+98), float(local_y));
	App.draw(rectangle);

	App.draw(labelSF);
	App.draw(callbackSF);

    if(blinking + 500 <= clock() && System.activeTextbox == id)
	{
		rectangle.setSize(sf::Vector2f(float(1), float(13)));
		rectangle.setFillColor(sf::Color(255,255,255));
		rectangle.setOutlineColor(sf::Color(255, 255, 255));
		rectangle.setOutlineThickness(0);
		rectangle.setPosition(float(local_x+108+caret*7), float(local_y+1));
		App.draw(rectangle);
	}
}

GuiNumberBoxLabel::GuiNumberBoxLabel(int x, int y, std::string _label, int32_t &Pnumber) : number(Pnumber)
{
	this->caret = callback.size()-1;
	this->insert = true;
	this->iter = callback.end();

    System.globalTextboxesCount++;
    id = System.globalTextboxesCount;
    blinking = clock();
	this->label = _label;
	this->local_x = x;
	this->local_y = y;

	this->callback = intToStr(number);

	this->labelSF.setFont(System.font);
    this->labelSF.setString(_label);
	this->labelSF.setPosition(float(x+2), float(y));
	this->labelSF.setCharacterSize(12);

	this->callbackSF.setFont(System.font);
    this->callbackSF.setString(callback);
	this->callbackSF.setPosition(float(x+100), float(y));
	this->callbackSF.setCharacterSize(12);

	rectangle.setSize(sf::Vector2f(float(100), float(15)));
	rectangle.setOutlineColor(sf::Color(255, 255, 255));
	rectangle.setOutlineThickness(1);
	rectangle.setPosition(float(x), float(y));
}

bool GuiNumberBoxLabel::proceed()
{
	if( mouse_x >= local_x+100 && mouse_x <= local_x + 320 && mouse_y >= local_y && mouse_y <= local_y + 15 && mouse_b == 1)
    {
        System.activeTextbox = id;
        return true;
    }
	if(System.activeTextbox == id && blinking + 1000 <= clock())
	{
		blinking = clock();
	}
    if(System.activeTextbox == id && System.keyProcessed == false)
	{ 
		System.keyProcessed = true;
		char ASCII;

		if(SFKeyToString(keyStorage.unicode, ASCII, true))
		{
		  if(insert || iter == callback.end())
		  {
			 iter = callback.insert(iter, ASCII);
		  }

		   else
		  {
			  callback.replace(caret, 1, 1, ASCII);
		  }
		  caret++;
		  iter++;
		}
		else
		{
		  switch(keyStorage.code)
		   {
			case sf::Keyboard::Delete:
			 if(iter != callback.end()) iter = callback.erase(iter);
			   break;

			case sf::Keyboard::Back:
			 if(iter != callback.begin())
			 {
			   caret--;
			   iter--;
			   iter = callback.erase(iter);
			 }break;
		 
			 case sf::Keyboard::Right:
			 if(iter != callback.end())   caret++, iter++;
			   break;
		 
			 case sf::Keyboard::Left:
			 if(iter != callback.begin()) caret--, iter--;
			   break;
		 
			 case sf::Keyboard::Insert:
			 insert = !insert;
			   break;
		       
			 case sf::Keyboard::Tab:
			 caret = 0;
			 System.activeTextbox++;
			   break;                  

			 default:
			   break;
		   } 
		}
		number = atoi(callback.c_str());
		callbackSF.setString(intToStr(number));
		return true;
	}
	return false;
}

void GuiNumberBoxLabel::draw()
{       
	rectangle.setSize(sf::Vector2f(float(100), float(15)));
	rectangle.setFillColor(sf::Color(32,32,32));
	rectangle.setOutlineColor(sf::Color(255, 255, 255));
	rectangle.setOutlineThickness(1);
	rectangle.setPosition(float(local_x), float(local_y));
	App.draw(rectangle);

	rectangle.setSize(sf::Vector2f(float(220), float(15)));
	rectangle.setFillColor(sf::Color(96,96,96));
	rectangle.setPosition(float(local_x+98), float(local_y));
	App.draw(rectangle);

	App.draw(labelSF);
	App.draw(callbackSF);

    if(blinking + 500 <= clock() && System.activeTextbox == id)
	{
		rectangle.setSize(sf::Vector2f(float(1), float(13)));
		rectangle.setFillColor(sf::Color(255,255,255));
		rectangle.setOutlineColor(sf::Color(255, 255, 255));
		rectangle.setOutlineThickness(0);
		rectangle.setPosition(float(local_x+108+caret*7), float(local_y+1));
		App.draw(rectangle);
	}
}



