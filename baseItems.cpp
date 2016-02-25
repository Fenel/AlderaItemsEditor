#include <iostream>
#include <deque>
#include <fstream>
#include <vector>
#include <string>
#include <time.h>

#include <SFML/Graphics.hpp>
extern sf::RenderWindow App;

#include "baseItems.h"
#include "itemType.h"

using namespace std;

ItemType* BaseItems::getItemType(unsigned int mID)
{
	return &items[mID];
}

BaseItems::BaseItems()
{
	itemsCount = 0;
	parseSpriteList();
	load();
}

bool BaseItems::addNewItem()
{
	this->items.push_back(ItemType());
	this->items.at(items.size()-1).id = items.size()-1;
	this->items.at(items.size()-1).spriteID = items.size()-1;
	this->loadSprite(&items.at(items.size()-1));
	return true;
}

bool BaseItems::deleteLastItem()
{
	if(!items.empty())
	{
		this->items.erase(items.end()-1);
		return true;
	}
	return false;
}

void BaseItems::load()
{    
    clock_t time_started = clock(); 
	#ifdef _DEBUG
		std::cout << "::Loading itemData.txt...";
	#endif

	vector<std::string> lines;
	vector<std::string> elements;
	vector<std::string> names;
	vector<std::string> values;
	string tmp;

	std::ifstream file ("data/itemData.txt");
    if(file.is_open())
    {
       while(file)
       {
	      tmp.clear();
          getline(file, tmp,'\n');
		  if(tmp != "")
			lines.push_back(tmp);
       }   
       file.close(); 
	}
	else
    {
        //coutCurrentTime();
		#ifdef _DEBUG
			std::cout << "\n::Error while opening itemData.txt\n";
		#endif
    }

	for(unsigned int i = 0; i < lines.size(); i++)
	{
		string element;
		while(lines[i].find_first_of(";") != string::npos) //je¿eli linia zawiera ";"
		{
			element = lines[i].substr(0,lines[i].find_first_of(";")); //element =zbiór nazwa+wartoœæ
			lines[i].erase(0,lines[i].find_first_of(";")+2);

			elements.push_back(element);
			element.clear();
		}
		for(unsigned int j = 0; j < elements.size(); j++)
		{
			string name = elements[j];
			name.erase(name.find_first_of("="));
			names.push_back(name);

			string value = elements[j];
			value.erase(0,value.find_first_of("=")+1);
			values.push_back(value);
		}

		items.push_back(ItemType());
		itemsCount++;
		for(unsigned int i = 0; i < names.size(); i++)
		{
			if(names[i] == "miniMapColor")
				items.at(items.size()-1).miniMapColor = atoi(values[i].c_str());
			if(names[i] == "height")
				items.at(items.size()-1).height = atoi(values[i].c_str());
			if(names[i] == "animcount")
				items.at(items.size()-1).animcount = atoi(values[i].c_str());
			if(names[i] == "numsprites")
				items.at(items.size()-1).numsprites = atoi(values[i].c_str());
			if(names[i] == "spriteID")
				items.at(items.size()-1).spriteID = atoi(values[i].c_str());
			if(names[i] == "id")
				items.at(items.size()-1).id = atoi(values[i].c_str());
			if(names[i] == "group")
				items.at(items.size()-1).group = ItemGroup(atoi(values[i].c_str()));
			if(names[i] == "name")
				items.at(items.size()-1).name = values[i].c_str();
			if(names[i] == "pluralName")
				items.at(items.size()-1).pluralName = values[i].c_str();
			if(names[i] == "description")
				items.at(items.size()-1).description = values[i].c_str();
			if(names[i] == "maxItems")
				items.at(items.size()-1).maxItems = atoi(values[i].c_str());
			if(names[i] == "weight")
				items.at(items.size()-1).weight = atoi(values[i].c_str());
			if(names[i] == "showCount")
				items.at(items.size()-1).showCount = bool(atoi(values[i].c_str()));
			if(names[i] == "weaponType")
				items.at(items.size()-1).weaponType = WeaponType(atoi(values[i].c_str()));
			if(names[i] == "ammoType")
				items.at(items.size()-1).ammoType = AmmoType(atoi(values[i].c_str()));
			if(names[i] == "shootType")
				items.at(items.size()-1).shootType = ShootType(atoi(values[i].c_str()));
			if(names[i] == "magicEffect")
				items.at(items.size()-1).magicEffect = MagicEffect(atoi(values[i].c_str()));
			if(names[i] == "attack")
				items.at(items.size()-1).attack = atoi(values[i].c_str());
			if(names[i] == "defence")
				items.at(items.size()-1).defence = atoi(values[i].c_str());
			if(names[i] == "armor")
				items.at(items.size()-1).armor = atoi(values[i].c_str());
			if(names[i] == "slotPosition")
				items.at(items.size()-1).slotPosition = atoi(values[i].c_str());
			if(names[i] == "isVertical")
				items.at(items.size()-1).isVertical = bool(atoi(values[i].c_str()));
			if(names[i] == "isHorizontal")
				items.at(items.size()-1).isHorizontal = bool(atoi(values[i].c_str()));
			if(names[i] == "allowDistRead")
				items.at(items.size()-1).allowDistRead = bool(atoi(values[i].c_str()));
			if(names[i] == "clientCharges ")
				items.at(items.size()-1).clientCharges  = bool(atoi(values[i].c_str()));
			if(names[i] == "speed")
				items.at(items.size()-1).speed = atoi(values[i].c_str());
			if(names[i] == "decayTo")
				items.at(items.size()-1).decayTo = atoi(values[i].c_str());
			if(names[i] == "decayTime")
				items.at(items.size()-1).decayTime = atoi(values[i].c_str());
			if(names[i] == "stopTime")
				items.at(items.size()-1).stopTime  = bool(atoi(values[i].c_str()));
			if(names[i] == "canReadText")
				items.at(items.size()-1).canReadText  = bool(atoi(values[i].c_str()));
			if(names[i] == "canWriteText")
				items.at(items.size()-1).canWriteText  = bool(atoi(values[i].c_str()));
			if(names[i] == "maxTextLen")
				items.at(items.size()-1).maxTextLen = atoi(values[i].c_str());
			if(names[i] == "stackable")
				items.at(items.size()-1).stackable = bool(atoi(values[i].c_str()));
			if(names[i] == "useable")
				items.at(items.size()-1).useable = bool(atoi(values[i].c_str()));
			if(names[i] == "moveable")
				items.at(items.size()-1).moveable = bool(atoi(values[i].c_str()));
			if(names[i] == "alwaysOnTop")
				items.at(items.size()-1).alwaysOnTop = bool(atoi(values[i].c_str()));
			if(names[i] == "alwaysOnTopOrder")
				items.at(items.size()-1).alwaysOnTopOrder = atoi(values[i].c_str());
			if(names[i] == "pickupable")
				items.at(items.size()-1).pickupable = bool(atoi(values[i].c_str()));
			if(names[i] == "hasHeight")
				items.at(items.size()-1).hasHeight = bool(atoi(values[i].c_str()));
			if(names[i] == "rotable")
				items.at(items.size()-1).rotable = bool(atoi(values[i].c_str()));
			if(names[i] == "rotateTo")
				items.at(items.size()-1).rotateTo = atoi(values[i].c_str());         
			if(names[i] == "runeIntelligence")
				items.at(items.size()-1).runeIntelligence = atoi(values[i].c_str());
			if(names[i] == "wieldInfo")
				items.at(items.size()-1).wieldInfo = atoi(values[i].c_str());
			if(names[i] == "vocation")
				items.at(items.size()-1).vocation = Vocation(atoi(values[i].c_str()));
			if(names[i] == "minReqDex")
				items.at(items.size()-1).minReqDex = atoi(values[i].c_str());
			if(names[i] == "minReqStr")
				items.at(items.size()-1).minReqStr = atoi(values[i].c_str());
			if(names[i] == "minReqInt")
				items.at(items.size()-1).minReqInt = atoi(values[i].c_str());
			if(names[i] == "minReqMPW")
				items.at(items.size()-1).minReqMPW = atoi(values[i].c_str());
			if(names[i] == "lightLevel")
				items.at(items.size()-1).lightLevel = atoi(values[i].c_str());
			if(names[i] == "lightColor")
				items.at(items.size()-1).lightColor = atoi(values[i].c_str());
			if(names[i] == "floorChangeDown")
				items.at(items.size()-1).floorChangeDown = bool(atoi(values[i].c_str()));
			if(names[i] == "floorChangeNorth")
				items.at(items.size()-1).floorChangeNorth = bool(atoi(values[i].c_str()));
			if(names[i] == "floorChangeSouth")
				items.at(items.size()-1).floorChangeSouth = bool(atoi(values[i].c_str()));
			if(names[i] == "floorChangeEast")
				items.at(items.size()-1).floorChangeEast = bool(atoi(values[i].c_str()));
			if(names[i] == "floorChangeWest")
				items.at(items.size()-1).floorChangeWest = bool(atoi(values[i].c_str()));
			if(names[i] == "blockSolid")
				items.at(items.size()-1).blockSolid = bool(atoi(values[i].c_str()));
			if(names[i] == "blockProjectile")
				items.at(items.size()-1).blockProjectile = bool(atoi(values[i].c_str()));
			if(names[i] == "blockPathFind")
				items.at(items.size()-1).blockPathFind = bool(atoi(values[i].c_str()));
			if(names[i] == "transformEquipTo")
				items.at(items.size()-1).transformEquipTo = atoi(values[i].c_str());
			if(names[i] == "transformDeEquipTo")
				items.at(items.size()-1).transformDeEquipTo = atoi(values[i].c_str());
			if(names[i] == "showCharges")
				items.at(items.size()-1).showCharges = bool(atoi(values[i].c_str()));
			if(names[i] == "charges")
				items.at(items.size()-1).charges = atoi(values[i].c_str());
			if(names[i] == "shootRange ")
				items.at(items.size()-1).shootRange  = atoi(values[i].c_str());
			if(names[i] == "ammoAction")
				items.at(items.size()-1).ammoAction = AmmoAction(atoi(values[i].c_str()));
			if(names[i] == "combatType")
				items.at(items.size()-1).combatType = CombatType(atoi(values[i].c_str()));	
		}
		loadSprite(&items.at(items.size()-1));

		elements.clear();
		names.clear();
		values.clear();
	}
	#ifdef _DEBUG
		std::cout << " Done! ";
		std::cout << "Loaded " << items.size() << " items.";
		std::cout<<" ( " << clock() - time_started << " ms )\n";
	#endif
}

void BaseItems::save()
{
	#ifdef _DEBUG
		std::cout << "::Saving itemData.txt...";
	#endif
	remove("data/itemDataBackup.txt");
	rename("data/itemData.txt", "data/itemDataBackup.txt");
	std::ofstream file("data/itemData.txt",ios::trunc);
	if(file.is_open())
    {	
		for(unsigned int i = 0; i < items.size(); i++)
		{
			//if(items.at(i).id)
				file<<"id="<<items.at(i).id<<"; ";
			//if(items.at(i).spriteID)
				file<<"spriteID="<<items.at(i).spriteID<<"; ";
			if(items.at(i).name != "Unnamed Item")
				file<<"name="<<items.at(i).name<<"; ";
			if(items.at(i).pluralName != "")
				file<<"pluralName="<<items.at(i).pluralName<<"; ";
			if(items.at(i).description != "")
				file<<"description="<<items.at(i).description<<"; ";
			if(items.at(i).miniMapColor != 0)
				file<<"miniMapColor="<<int(items.at(i).miniMapColor)<<"; ";
			if(items.at(i).group != 0)
				file<<"group="<<items.at(i).group<<"; ";
			if(items.at(i).height != 0)
				file<<"height="<<items.at(i).height<<"; ";
			if(items.at(i).animcount != 0)
				file<<"animcount="<<items.at(i).animcount<<"; ";
			if(items.at(i).numsprites != 0)
				file<<"numsprites="<<items.at(i).numsprites<<"; ";
			if(items.at(i).maxItems != 0)
				file<<"maxItems="<<items.at(i).maxItems<<"; ";
			if(items.at(i).weight != 0)
				file<<"weight="<<items.at(i).weight<<"; ";
			if(items.at(i).showCount == true)
				file<<"showCount="<<items.at(i).showCount<<"; ";
			if(items.at(i).weaponType != 0)
				file<<"weaponType="<<items.at(i).weaponType<<"; ";
			if(items.at(i).ammoType != 0)
				file<<"ammoType="<<items.at(i).ammoType<<"; ";
			if(items.at(i).shootType != 0)
				file<<"shootType="<<items.at(i).shootType<<"; ";
			if(items.at(i).magicEffect != 0)
				file<<"magicEffect="<<items.at(i).magicEffect<<"; ";
			if(items.at(i).attack != 0)
				file<<"attack="<<items.at(i).attack<<"; ";
			if(items.at(i).defence != 0)
				file<<"defence="<<items.at(i).defence<<"; ";
			if(items.at(i).armor != 0)
				file<<"armor="<<items.at(i).armor<<"; ";
			if(items.at(i).slotPosition != 0)
				file<<"slotPosition="<<items.at(i).slotPosition<<"; ";
			if(items.at(i).isVertical == true)
				file<<"isVertical="<<items.at(i).isVertical<<"; ";
			if(items.at(i).isHorizontal == true)
				file<<"isHorizontal="<<items.at(i).isHorizontal<<"; ";
			if(items.at(i).allowDistRead == true)
				file<<"allowDistRead="<<items.at(i).allowDistRead<<"; ";
			if(items.at(i).clientCharges == true)
				file<<"clientCharges="<<items.at(i).clientCharges<<"; ";
			if(items.at(i).speed != 0)
				file<<"speed="<<items.at(i).speed<<"; ";
			if(items.at(i).decayTo != -1)
				file<<"decayTo="<<items.at(i).decayTo<<"; ";
			if(items.at(i).decayTime != 0)
				file<<"decayTime="<<items.at(i).decayTime<<"; ";
			if(items.at(i).stopTime == true)
				file<<"stopTime="<<items.at(i).stopTime<<"; ";
			if(items.at(i).canReadText == true)
				file<<"canReadText="<<items.at(i).canReadText<<"; ";
			if(items.at(i).canWriteText == true)
				file<<"canWriteText="<<items.at(i).canWriteText<<"; ";
			if(items.at(i).maxTextLen != 0)
				file<<"maxTextLen="<<items.at(i).maxTextLen<<"; ";
			if(items.at(i).stackable == true)
				file<<"stackable="<<items.at(i).stackable<<"; ";
			if(items.at(i).useable == true)
				file<<"useable="<<items.at(i).useable<<"; ";
			if(items.at(i).moveable == true)
				file<<"moveable="<<items.at(i).moveable<<"; ";
			if(items.at(i).alwaysOnTop == true)
				file<<"alwaysOnTop="<<items.at(i).alwaysOnTop<<"; ";
			if(items.at(i).alwaysOnTopOrder != 0)
				file<<"alwaysOnTopOrder="<<items.at(i).alwaysOnTopOrder<<"; ";
			if(items.at(i).pickupable == true)
				file<<"pickupable="<<items.at(i).pickupable<<"; ";
			if(items.at(i).hasHeight == true)
				file<<"hasHeight="<<items.at(i).hasHeight<<"; ";
			if(items.at(i).rotable == true)
				file<<"rotable="<<items.at(i).rotable<<"; ";
			if(items.at(i).rotateTo != 0)
				file<<"rotateTo="<<items.at(i).rotateTo<<"; ";       
			if(items.at(i).runeIntelligence != 0)
				file<<"runeIntelligence="<<items.at(i).runeIntelligence<<"; ";
			if(items.at(i).wieldInfo != 0)
				file<<"wieldInfo="<<items.at(i).wieldInfo<<"; ";
			if(items.at(i).vocation != 0)
				file<<"vocation="<<items.at(i).vocation<<"; ";
			if(items.at(i).minReqDex != 0)
				file<<"minReqDex="<<items.at(i).minReqDex<<"; ";
			if(items.at(i).minReqStr != 0)
				file<<"minReqStr="<<items.at(i).minReqStr<<"; ";
			if(items.at(i).minReqInt != 0)
				file<<"minReqInt="<<items.at(i).minReqInt<<"; ";
			if(items.at(i).minReqMPW != 0)
				file<<"minReqMPW="<<items.at(i).minReqMPW<<"; ";
			if(items.at(i).lightLevel != 0)
				file<<"lightLevel="<<items.at(i).lightLevel<<"; ";
			if(items.at(i).lightColor != 0)
				file<<"lightColor="<<items.at(i).lightColor<<"; ";
			if(items.at(i).floorChangeDown == true)
				file<<"floorChangeDown="<<items.at(i).floorChangeDown<<"; ";
			if(items.at(i).floorChangeNorth == true)
				file<<"floorChangeNorth="<<items.at(i).floorChangeNorth<<"; ";
			if(items.at(i).floorChangeSouth == true)
				file<<"floorChangeSouth="<<items.at(i).floorChangeSouth<<"; ";
			if(items.at(i).floorChangeEast == true)
				file<<"floorChangeEast="<<items.at(i).floorChangeEast<<"; ";
			if(items.at(i).floorChangeWest == true)
				file<<"floorChangeWest="<<items.at(i).floorChangeWest<<"; ";
			if(items.at(i).blockSolid == true)
				file<<"blockSolid="<<items.at(i).blockSolid<<"; ";
			if(items.at(i).blockProjectile == true)
				file<<"blockProjectile="<<items.at(i).blockProjectile<<"; ";
			if(items.at(i).blockPathFind == true)
				file<<"blockPathFind="<<items.at(i).blockPathFind<<"; ";
			if(items.at(i).transformEquipTo != 0)
				file<<"transformEquipTo="<<items.at(i).transformEquipTo<<"; ";
			if(items.at(i).transformDeEquipTo != 0)
				file<<"transformDeEquipTo="<<items.at(i).transformDeEquipTo<<"; ";
			if(items.at(i).showCharges == true)
				file<<"showCharges="<<items.at(i).showCharges<<"; ";
			if(items.at(i).charges != 0)
				file<<"charges="<<items.at(i).charges<<"; ";
			if(items.at(i).shootRange != 0)
				file<<"shootRange="<<items.at(i).shootRange<<"; ";
			if(items.at(i).ammoAction != 0)
				file<<"ammoAction="<<items.at(i).ammoAction<<"; ";
			if(items.at(i).combatType != 0)
				file<<"ammoAction="<<items.at(i).ammoAction<<"; ";

			if(i != items.size())
			file<< "\n";
		}
	    file.close();
	#ifdef _DEBUG
		std::cout << " Done! ";
	#endif
    }
	#ifdef _DEBUG
		else
			std::cout << " Error! ";
	#endif
}


void BaseItems::parseSpriteList()
{    
    std::deque<std::string> lines;
    std::string tmp;                                           
    std::ifstream file ("data/spriteData.txt");
                                
    while(file)                 
    {  
	   tmp.clear();
       getline(file, tmp,'\n');
	   if(tmp != "")
		  lines.push_back(tmp);    
    }                           
    file.close();               
                            
                                         
    for(std::deque<std::string>::iterator line = lines.begin() ; line < lines.end(); line++)
    {  
		spritesProperties.push_back(SpriteProperties());
		spritesProperties.at(spritesProperties.size()-1).id = spritesProperties.size() - 1;

		if(line->at(0) == 'h')
		{             
		    spritesProperties.at(spritesProperties.size()-1).type = 1; //horyzontalnie
		}                    
		if(line->at(0) == 'v')
		{                    
		    spritesProperties.at(spritesProperties.size()-1).type = 2;  //vertykalnie
		}                    
		if(line->at(0) == 't')
		{                    
		    spritesProperties.at(spritesProperties.size()-1).type = 3;   //2x2
		}                    
		if(line->at(0) == 'o')
		{                    
		    spritesProperties.at(spritesProperties.size()-1).type = 0; //1x1                                    
		}                     
        line->erase( 0, line->find("|") +1 );
        spritesProperties.at(spritesProperties.size()-1).graphicId = atoi(line->data());
   }                            
}

void BaseItems::loadSprite(ItemType *item)
{
	sf::Image tempImage;

	if(this->spritesProperties.size() > item->spriteID)
	{
		if(this->spritesProperties.at(item->spriteID).type == 0) //1x1
		{
			char tempChar[25]; 
			sprintf(tempChar,"data/sprites/%d.bmp",spritesProperties.at(item->spriteID).graphicId);
			tempImage.loadFromFile(tempChar);
			tempImage.createMaskFromColor(sf::Color(255,0,255));
			item->texture.loadFromImage(tempImage);
		}
		if(this->spritesProperties.at(item->spriteID).type == 1) //horizontal
		{
			item->texture.create(64,32);
			sf::Image tempImageFinal;
			tempImageFinal.create(64,32);

			char tempChar[25]; 
			sprintf(tempChar,"data/sprites/%d.bmp",spritesProperties.at(item->spriteID).graphicId);
			tempImage.loadFromFile(tempChar);
			tempImageFinal.copy(tempImage,0,0,sf::IntRect(0,0,32,32));

			sprintf(tempChar,"data/sprites/%d.bmp",spritesProperties.at(item->spriteID).graphicId+1);
			tempImage.loadFromFile(tempChar);
			tempImageFinal.copy(tempImage,32,0,sf::IntRect(0,0,32,32));
			tempImageFinal.createMaskFromColor(sf::Color(255,0,255));
			item->texture.loadFromImage(tempImageFinal);
		}
		if(this->spritesProperties.at(item->spriteID).type == 2) //vertical
		{
			item->texture.create(32,64);
			sf::Image tempImageFinal;
			tempImageFinal.create(32,64);

			char tempChar[25]; 
			sprintf(tempChar,"data/sprites/%d.bmp",spritesProperties.at(item->spriteID).graphicId);
			tempImage.loadFromFile(tempChar);
			tempImageFinal.copy(tempImage,0,0,sf::IntRect(0,0,32,32));

			sprintf(tempChar,"data/sprites/%d.bmp",spritesProperties.at(item->spriteID).graphicId+1);
			tempImage.loadFromFile(tempChar);
			tempImageFinal.copy(tempImage,0,32,sf::IntRect(0,0,32,32));
			tempImageFinal.createMaskFromColor(sf::Color(255,0,255));
			item->texture.loadFromImage(tempImageFinal);
		}
		if(this->spritesProperties.at(item->spriteID).type == 3) //2x2
		{
			item->texture.create(64,64);
			sf::Image tempImageFinal;
			tempImageFinal.create(64,64);

			char tempChar[25]; 
			sprintf(tempChar,"data/sprites/%d.bmp",spritesProperties.at(item->spriteID).graphicId);
			tempImage.loadFromFile(tempChar);
			tempImageFinal.copy(tempImage,0,0,sf::IntRect(0,0,32,32));

			sprintf(tempChar,"data/sprites/%d.bmp",spritesProperties.at(item->spriteID).graphicId+1);
			tempImage.loadFromFile(tempChar);
			tempImageFinal.copy(tempImage,32,0,sf::IntRect(0,0,32,32));

			sprintf(tempChar,"data/sprites/%d.bmp",spritesProperties.at(item->spriteID).graphicId+2);
			tempImage.loadFromFile(tempChar);
			tempImageFinal.copy(tempImage,0,32,sf::IntRect(0,0,32,32));

			sprintf(tempChar,"data/sprites/%d.bmp",spritesProperties.at(item->spriteID).graphicId+3);
			tempImage.loadFromFile(tempChar);
			tempImageFinal.copy(tempImage,32,32,sf::IntRect(0,0,32,32));
			tempImageFinal.createMaskFromColor(sf::Color(255,0,255));
			item->texture.loadFromImage(tempImageFinal);
		}
		item->sprite.setTexture(item->texture);
		item->sprite.setPosition(20.0,20.0);
	}
	else
	{
		//tempImage.LoadFromFile("data/sprites/0.bmp");
		//tempImage.CreateMaskFromColor(sf::Color(255,0,255));
		//item->texture.LoadFromImage(tempImage);
		//item->sprite.SetTexture(item->texture);
		//item->sprite.SetPosition(32.0,32.0);
	}

}
