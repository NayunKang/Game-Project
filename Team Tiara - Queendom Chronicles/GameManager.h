#pragma once

#include "Field.h"
#include "Resource.h"
#include "Building.h"
#include "Unit.h"
#include "Player.h"
#include "Npc.h"
#include "Game_status.h"

#include <vector>
#include <unordered_map>

enum class Building_list;

enum class Moving_mode
{
	CAMERA,
	PLAYER
};

class GameManager
{
private:
	// field
	Field* field{ new Field };

	// Current Moving mode
	Moving_mode current_moving_mode{ Moving_mode::CAMERA };

	// Building & Unit map, vectors
	std::unordered_map<Building_list, Building_Type*> building_types{};
	std::vector<Building*> buildings{};
	std::vector<Unit*> units{};
	std::unordered_map<std::string, int> npc_sequence{};
	
	// Resource map
	std::unordered_map<Resource_list, Resource*> resources{};

	// Current building type that mouse holds
	Building_Type* current_building_type{ nullptr };

	// Current unit that player interacts
	Npc* current_npc{ nullptr };

	// Current player level
	int level{ 1 };
	const int max_level{ 5 };

public:
	GameManager() = default;
	~GameManager();

	void Setup();

	// Get Field
	Field& Get_field() const { return *field; }

	// Get & Change current mode
	Moving_mode Get_mode() const { return current_moving_mode; }
	void Change_mode(Moving_mode next_mode) { current_moving_mode = next_mode; }

	// Get & Set Buildings
	std::unordered_map<Building_list, Building_Type*>& Get_building_types() { return building_types; }
	Building_Type* Get_current_building_type() const { return current_building_type; }
	std::vector<Building*>& Get_buildings() { return buildings; }
	Building& Get_building(int index) const { return *buildings[index]; }
	void Set_current_building_type(Building_list building);
	void Set_current_building_type(Building_Type* building);

	// Get Resource
	Resource& Get_resource(Resource_list resource) { return *resources[resource]; }

	// Get & Set Units
	std::vector<Unit*>& Get_units() { return units; }
	template<typename T>
	T* Get_unit(Unit* unit)
	{
		T* ptr = dynamic_cast<T*>(unit);
		return ptr;
	}
	int Get_sequence(std::string name) const { return npc_sequence.at(name); }
	void Increment_sequence(std::string name) { npc_sequence.at(name)++; }
	Npc* Get_current_npc() { return current_npc; }
	void Set_current_npc(Npc* npc);

	// Get & Set Level
	int Get_level() const { return level; }
};