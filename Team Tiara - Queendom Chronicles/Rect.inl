
#include "Rect.h"

namespace math
{
	constexpr bool rect2::Is_intersects(const rect2& rect) const noexcept
	{
		if (this->topRight.x < rect.bottomLeft.x || this->bottomLeft.x > rect.topRight.x)
			return false;
		if (this->topRight.y < rect.bottomLeft.y || this->bottomLeft.y > rect.topRight.y)
			return false;

		return true;
	}
	constexpr bool rect2::Is_intersects(const math::vec2& point) const noexcept
	{
		if (Left() < point.x && Right() > point.x && Bottom() < point.y && Top() > point.y)
		{
			return true;
		}
		else return false;
	}

	constexpr bool irect2::Is_intersects(const irect2& rect) const noexcept
	{
		if (this->topRight.x < rect.bottomLeft.x || this->bottomLeft.x > rect.topRight.x)
			return false;
		if (this->topRight.y < rect.bottomLeft.y || this->bottomLeft.y > rect.topRight.y)
			return false;

		return true;
	}
	constexpr bool irect2::Is_intersects(const math::ivec2& point) const noexcept
	{
		if (Left() < point.x && Right() > point.x && Bottom() < point.y && Top() > point.y)
		{
			return true;
		}
		else return false;
	}
}