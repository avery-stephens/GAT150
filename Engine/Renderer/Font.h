#pragma once
#include "Resource/Resource.h"
//#include <SDL_ttf.h>
#include <string>
#include <memory>

struct _TTF_Font;
struct SDL_Surface;

namespace gooblegorb
{
	struct Color;

	class Font : public Resource
	{
	public:
		Font() = default;
		Font(const std::string& filename, int fontSize);
		~Font();

		//bool Create(const std::string& filename, void* data = nullptr) override;

		bool Create(std::string filename, ...) override;
		SDL_Surface* CreateSurface(const std::string& text, const Color& color);

		void Load(const std::string& filename, int fontSize);

		friend class Text;
	private:
		_TTF_Font* m_ttfFont = nullptr;
	};
}