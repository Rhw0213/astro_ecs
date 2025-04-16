#pragma once
#include "raylib.h"
#include "Random.h"
#include <cmath>
#include <random>

namespace astro
{
	static const int SCREEN_WIDTH = 1200;
	static const int SCREEN_HEIGHT = 800;

	enum ComponentID
	{
		TRANSFORM_COMPONENT,
		RENDER_COMPONENT,
		MOVE_COMPONENT,
		INPUT_COMPONENT,
		EFFECT_COMPONENT
	};

	enum ObjectID
	{
		GAMEOBJECT_ID,
		PLAYER_ID,
		STAR_ID,
	};

	struct MyVector2 
	{
		Vector2 vec;

		MyVector2() : vec{ 0, 0 } {}
		MyVector2(float x, float y) : vec{ x, y } {}
		MyVector2(const Vector2& v) : vec{ v } {}

		operator Vector2() const { return vec; }

		MyVector2 operator+(const MyVector2& other) const {
			return { vec.x + other.vec.x, vec.y + other.vec.y };
		}

		MyVector2 operator-(const MyVector2& other) const {
			return { vec.x - other.vec.x, vec.y - other.vec.y };
		}

		MyVector2 operator*(float scalar) const {
			return { vec.x * scalar, vec.y * scalar };
		}

		MyVector2 operator/(float scalar) const {
			if (scalar == 0) return { 0, 0 };
			return { vec.x / scalar, vec.y / scalar };
		}

		MyVector2& operator+=(const MyVector2& other) {
			vec.x += other.vec.x;
			vec.y += other.vec.y;
			return *this;
		}

		MyVector2& operator-=(const MyVector2& other) {
			vec.x -= other.vec.x;
			vec.y -= other.vec.y;
			return *this;
		}

		MyVector2& operator*=(float scalar){
			vec.x *= scalar;
			vec.y *= scalar;
			return *this;
		}

		MyVector2 DirectionTo(const MyVector2& target) const {
			return (target - *this).Normalize(); // 이름 변경 및 정규화
		}

		MyVector2 Normalize() const {
			float length = Length();
			if (length == 0) return { 0, 0 };
			return *this / length;
		}

		float Distance(const MyVector2& other) const {
			return (*this - other).Length();
		}

		float Length() const {
			return sqrtf(vec.x * vec.x + vec.y * vec.y);
		}

		float& x() { return vec.x; }
		float& y() { return vec.y; }
		const float& x() const { return vec.x; }
		const float& y() const { return vec.y; }
	};
}

