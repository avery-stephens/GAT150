#pragma once
#include "Math/Vector2.h" 
#include "Resource/Resource.h"
#include <string> 

//#include "SDL.h"
// !! forward declaration for SDL pointers below (SDL likes to use structs) 
struct SDL_Texture;
// !! add namespace 
namespace gooblegorb
{
// !! forward declaration for Renderer below 
	class Renderer;
	class Texture : public Resource
	{
	public:
		Texture() = default;
		~Texture();

		//bool Create(const std::string& filename, void* data = nullptr) override;

		bool Create(Renderer& renderer, const std::string& filename);

		bool Create(std::string filename, ...) override;

		Vector2 GetSize() const;

		friend class Renderer;

	private:
		SDL_Texture* m_texture = nullptr;
	};
}
