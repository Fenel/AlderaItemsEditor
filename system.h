#ifndef CSYSTEM_H
#define CSYSTEM_H

#include <SFML/Graphics.hpp>

class ItemType;

class System
{
public:
  System(unsigned int _width, unsigned int _height, unsigned int _res);
  ~System();
  void renderItemType(int x, int y, ItemType *item);

  unsigned int windowWidth, windowHeight, res;
  unsigned int activeTextbox;
  unsigned int globalTextboxesCount;
  bool keyProcessed;

  bool hold;

  sf::Font font;
private:
};


#endif
