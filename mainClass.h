#ifndef CMENU_H
#define CMENU_H

#include <string>
#include <deque>
#include "enums.h"
#include "gui.h"
#include "itemType.h"

using namespace std;

class MainClass
{
public:
  MainClass();
  void initialize();
  void restartProperties();
  void addNewItem();
  void deleteLastItem();
  ~MainClass();
  //void showItems();
  void saveItems();
  void loop();
  void itemsList();
  void addCheckBoxLabel(std::string label, bool &Pcallback);
  void addTextBoxLabel(std::string label, std::string &text);
  void addNumberBoxLabel(std::string label, int32_t &number);
private:
  sf::Image guiSaveImage, guiAddItemImage, guiDeleteItemImage;
  sf::Texture guiSaveTexture, guiAddItemTexture, guiDeleteItemTexture;
  sf::Sprite guiSaveIcon, guiAddItemIcon, guiDeleteItemIcon;
  deque<GuiElement*> elements;
  int currentx, currenty;
  unsigned int currentMinDispItem;
  ItemType *currentItem;
};

#endif

