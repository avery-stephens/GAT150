#pragma once
#include "Vector2.h"
#include <Math/Matrix2x2.h>

namespace gooblegorb
{
	struct Transform 
	{
		Vector2 position;
		float rotation{ 0 };
		Vector2 scale{ 1,1 };

		Matrix2x2 mxScale = Matrix2x2::CreateScale(scale);
		Matrix2x2 mxRotation = Matrix2x2::CreateRotation(math::DegtoRad(rotation));
	};
}