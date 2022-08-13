#pragma once
#include "Resource/Resource.h"
//#include <SDL_ttf.h>
#include <string>
#include <memory>

	struct _TTF_Font;
namespace gooblegorb
{
	class Font : public Resource
	{
	public:
		Font() = default;
		Font(const std::string& filename, int fontSize);
		~Font();

		bool Create(const std::string& filename, void* data = nullptr) override;
		void Load(const std::string& filename, int fontSize);

		friend class Text;
	private:
		_TTF_Font* m_ttfFont = nullptr;
	};
}