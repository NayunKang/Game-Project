
#pragma once

#include "Vec2.h"
#include <algorithm>

namespace math {

	struct rect2
	{
		vec2 bottomLeft{ 0,0 };
		vec2 topRight{ 0,0 };

		rect2() = default;
		rect2(vec2 bottomLeft, vec2 topRight)
			: bottomLeft(bottomLeft), topRight(topRight)
		{}

		constexpr bool Is_intersects(const rect2& rect) const noexcept;
		constexpr bool Is_intersects(const vec2& point) const noexcept;

		constexpr vec2 Size() const noexcept { return { Right() - Left(), Top() - Bottom() }; }
		constexpr double Left() const noexcept { return std::min(bottomLeft.x, topRight.x); }
		constexpr double Right() const noexcept { return std::max(bottomLeft.x, topRight.x); }
		constexpr double Top() const noexcept { return std::max(bottomLeft.y, topRight.y); }
		constexpr double Bottom() const noexcept { return std::min(bottomLeft.y, topRight.y); }
	};

	struct irect2
	{
		ivec2 bottomLeft{ 0, 0 };
		ivec2 topRight{ 0, 0 };

		irect2() = default;
		irect2(ivec2 bottomLeft, ivec2 topRight)
			: bottomLeft(bottomLeft), topRight(topRight)
		{}

		constexpr bool Is_intersects(const irect2& rect) const noexcept;
		constexpr bool Is_intersects(const ivec2& point) const noexcept;

		constexpr ivec2 Size() const noexcept { return { Right() - Left(), Top() - Bottom() }; }
		constexpr int Left() const noexcept { return std::min(bottomLeft.x, topRight.x); }
		constexpr int Right() const noexcept { return std::max(bottomLeft.x, topRight.x); }
		constexpr int Top() const noexcept { return std::max(bottomLeft.y, topRight.y); }
		constexpr int Bottom() const noexcept { return std::min(bottomLeft.y, topRight.y); }

		explicit operator rect2() const noexcept
		{
			return rect2{ static_cast<vec2>(bottomLeft), static_cast<vec2>(topRight) };
		}
	};
}

#include "Rect.inl"