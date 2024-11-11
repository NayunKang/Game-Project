
#include "Resource.h"
#include "Engine.h"

#include <doodle/doodle.hpp>

void Resource::Update_reserve(double reserve_amount)
{
	reserve += reserve_amount;
}