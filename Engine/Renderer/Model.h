#pragma once
#include "Renderer.h"
#include <vector>
#include <string>

namespace gooblegorb
{
	class Model
	{
	public:
		Model() = default;
		Model(const std::vector<gooblegorb::Vector2> points, const gooblegorb::Color& color) : 
			m_points{points},
			m_color{color}
		{
			
		}
		Model(const std::string& filename);

		void Draw(Renderer& renderer, const Vector2& position, float angle, const Vector2& scale = Vector2{1,1});

		void Load(std::string filename);
		float CalculateRadius();

		float GetRadius() { return m_radius; }
		
	private:
		gooblegorb::Color m_color{ 0,0,0,0 };
		std::vector<gooblegorb::Vector2> m_points;

		float m_radius = 0;
	};
}