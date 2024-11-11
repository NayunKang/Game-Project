#include "Engine.h"
#include "GameManager.h"
#include "Building.h"
#include "Game_screen.h"
#include "Building_list.h"

#include <doodle/environment.hpp>

using namespace doodle;

GameManager::~GameManager()
{
	// delete field
	delete field;

	// delete buildings_list
	auto buildings_list_iter = building_types.begin();
	for (; buildings_list_iter != building_types.end(); ++buildings_list_iter)
	{
		delete buildings_list_iter->second;
	}
	building_types.clear();

	// delete buildings
	auto buildings_iter = buildings.begin();
	for (; buildings_iter != buildings.end(); ++buildings_iter)
	{
		delete* buildings_iter;
	}
	buildings.clear();

	// delete units
	auto units_iter = units.begin();
	for (; units_iter != units.end(); ++units_iter)
	{
		delete* units_iter;
	}
	units.clear();

	// delete resources
	auto resources_iter = resources.begin();
	for (; resources_iter != resources.end(); ++resources_iter)
	{
		delete resources_iter->second;
	}
	resources.clear();
}

void GameManager::Setup()
{
	// Put Resources in resource map
	resources[Resource_list::WOOD] = new Resource{ Image{"Assets/Wood.png"} };
	resources[Resource_list::STONE] = new Resource{ Image{"Assets/stone1.png"} };
	resources[Resource_list::FOOD] = new Resource{ Image{"Assets/wheat.png"} };

	// Put Building types in building types map 
	// Make Castle
	building_types.insert({ Building_list::Castle , new Building_Type{"Castle", 13, 15, Image{"Assets/Castle.png"} } });
	//Install_building(60, 30, building_types[Building_list::Castle]);

	// Production Buildings
	building_types.insert({ Building_list::Lumber_Camp, new Production_building{ "Lumber Camp", 4, 4, 100, 100, Image{"Assets/Building.png"}, Image{"Assets/Front_building.png"}, Resource_list::WOOD, 10} });
	building_types.insert({ Building_list::Quarry, new Production_building{ "Quarry", 4, 5, 100, 100, Image{"Assets/quarry.png"}, Image{"Assets/front_quarry.png"},Resource_list::STONE, 10} });
	building_types.insert({ Building_list::Farm, new Production_building{ "Farm", 4, 5, 200, 200, Image{"Assets/farm.png"}, Image{"Assets/front_farm.png"}, Resource_list::FOOD, 10} });

	// Houses (Residental Buildings)
	building_types.insert({ Building_list::Blue_House, new Residential_building{"Blue House", 3, 3, 200, 200, Image{"Assets/House_blue.png"}, Image{"Assets/house_blue.png"}, 1} });
	building_types.insert({ Building_list::Green_House, new Residential_building{ "Green House", 3, 3, 300, 300, Image{"Assets/House_green.png"}, Image{"Assets/house_green.png"}, 2} });
	building_types.insert({ Building_list::Yellow_House, new Residential_building{ "Yellow House", 3, 3, 400, 400, Image{"Assets/House_yellow.png"}, Image{"Assets/house_yellow.png"}, 3} });
	building_types.insert({ Building_list::Pink_House, new Building_Type{ "Pink House" ,3, 3, 500, 500, Image{"Assets/House_pink.png"}} });

	// Decoration
	building_types.insert({ Building_list::Tree1, new Building_Type{ "Tree1", 1, 1, 50, 50, Image{"Assets/tree1.png"} } });
	building_types.insert({ Building_list::Tree2, new Building_Type{ "Tree2", 1, 1, 50, 50, Image{"Assets/tree2.png"} } });
	building_types.insert({ Building_list::Tree3, new Building_Type{ "Tree3" ,1, 1, 50, 50, Image{"Assets/tree3.png"}} });
	building_types.insert({ Building_list::Tree4, new Building_Type{ "Tree4" ,1, 1, 50, 50, Image{"Assets/tree4.png"} } });
	building_types.insert({ Building_list::Tree5, new Building_Type{ "Tree5" ,1, 1, 50, 50, Image{"Assets/tree5.png"} } });
	building_types.insert({ Building_list::Tree6,new Building_Type{ "Tree6" ,1, 1, 50, 50, Image{"Assets/tree6.png"} } });
	building_types.insert({ Building_list::Tree7,new Building_Type{ "Tree7" ,1, 1, 50, 50, Image{"Assets/tree7.png"} } });
	building_types.insert({ Building_list::Fence1, new Building_Type{ "Fence1", 1, 1, 50, 50, Image{"Assets/fence.png"}} });
	building_types.insert({ Building_list::Fence2, new Building_Type{ "Fence2", 1, 1, 50, 50, Image{"Assets/fence2.png"} } });
	building_types.insert({ Building_list::Fence_RightBottom, new Building_Type{ "", 1, 1, 50,50, Image{"Assets/fence_rightBottom.png"}} });
	building_types.insert({ Building_list::Fence_RightTop, new Building_Type{ "", 1, 1, 50,50, Image{"Assets/fence_rightTop.png"} } });
	building_types.insert({ Building_list::Fence_LeftBottom, new Building_Type{ "", 1, 1, 50,50, Image{"Assets/fence_leftBottom.png"} } });
	building_types.insert({ Building_list::Fence_LeftTop, new Building_Type{ "", 1, 1, 50,50, Image{"Assets/fence_leftTop.png"} } });

	// NPC
	units.push_back(new Player{ static_cast<math::vec2>(Get_field().Get_tile_position(10, 7)) });
	units.push_back(new Npc{ "Npc/Danny.npc", static_cast<math::vec2>(Get_field().Get_tile_position(7, 5)) });
	units.push_back(new Npc{ "Npc/Alex.npc", static_cast<math::vec2>(Get_field().Get_tile_position(5, 5)) });

	for (Unit* unit : units)
	{
		if (dynamic_cast<Npc*>(unit) != nullptr)
		{
			npc_sequence.insert({ unit->GetName(), 0 });
		}
	}
}
void GameManager::Set_current_building_type(Building_list building)
{
	if (building == Building_list::None)
	{
		current_building_type = nullptr;
		return;
	}

	current_building_type = building_types[building];

	Engine().Get_Music().play_BGM(BGM_list::background);
}
void GameManager::Set_current_building_type(Building_Type* building)
{
	current_building_type = building;
}
void GameManager::Set_current_npc(Npc* npc)
{
	current_npc = npc;
}