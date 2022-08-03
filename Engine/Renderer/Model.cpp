#include "Model.h"
#include "../Core/File.h"
#include <iostream>
#include <sstream>

namespace gooblegorb
{
	Model::Model(const std::string& filename)
	{
		Load(filename);
		m_radius = CalculateRadius();
	}

	void gooblegorb::Model::Draw(Renderer& renderer, const Vector2& position, float angle, float scale)
	{
		/*neu::Color color;
		color.r = neu::random(256);
		color.g = neu::random(256);
		color.b = neu::random(256);
		color.a = 255;
		//renderer.SetClearColor(color);

		//draw model
		//for (auto& v : model)
		//{
		//	v += move;
		//}
		*/

		//draw model
		for (int i = 0; i < m_points.size() - 1; i++)
		{
			gooblegorb::Vector2 p1 = Vector2::Rotate((m_points[i] * scale),angle) + position;
			gooblegorb::Vector2 p2 = Vector2::Rotate((m_points[i + 1] * scale),angle) + position;

			renderer.DrawLine(p1, p2, m_color);
		}
	}

	void Model::Load(std::string filename)
	{
		std::string buffer;
		gooblegorb::ReadFile(filename, buffer);

		//m_color.r = 255;
		//m_color.g = 255;
		//m_color.b= 255;
		//m_color.a = 255;

		std::istringstream stream(buffer);
		stream >> m_color;

		//read number of points
		std::string line;
		std::getline(stream, line);

		//get number of points
		size_t numPoints = std::stoi(line);

		//read model points
		for (size_t i = 0; i < numPoints; i++)
		{
			Vector2 point;

			stream >> point;

			m_points.push_back(point);
		}
	}

	float Model::CalculateRadius()
	{
		float radius = 0;

		//find the largest length (radius)
		for (auto& point : m_points)
		{
			if (point.Length() > radius) radius = point.Length();
		}

		return radius;
	}

}
