#ifndef GUI_H
#define GUI_H

#include <SFML/Graphics.hpp>

using namespace std;

class GuiElement
{
public:
 //GuiElement();
 virtual void draw();
 virtual bool proceed();
protected:
 int local_x, local_y;
};


class GuiCheckBoxLabel : public GuiElement
{
public:
 GuiCheckBoxLabel::GuiCheckBoxLabel(int x, int y, std::string _text, bool &Pcallback);
 bool proceed();
 void draw();
 sf::Sprite checked;
 sf::Sprite unchecked;
private:
 bool &callback;
 sf::Text text;

  sf::RectangleShape rectangle;
};

class GuiTextBoxLabel: public GuiElement
{
public:
 GuiTextBoxLabel(int x, int y, std::string label, std::string &Pcallback);
 bool proceed();
 void draw();
private:
 int id;
 string::iterator iter;
 int caret;
 bool insert; 

 std::string &callback;
 std::string label;
 sf::Text labelSF;
 sf::Text callbackSF;

 sf::RectangleShape rectangle;
 
 clock_t blinking;
};

class GuiNumberBoxLabel: public GuiElement
{
public:
 GuiNumberBoxLabel(int x, int y, std::string label, int32_t &number);
 bool proceed();
 void draw();
private:
 int id;
 string::iterator iter;
 int caret;
 bool insert; 

 int32_t &number;
 std::string callback;
 std::string label;
 sf::Text labelSF;
 sf::Text callbackSF;

 sf::RectangleShape rectangle;
 
 clock_t blinking;
};

#endif
