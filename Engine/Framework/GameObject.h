#pragma once
#include "../Math/Transform.h"

namespace gooblegorb
{
	class GameObject
	{
	public:
		GameObject() = default;

		virtual void Update() = 0;
	};
}
