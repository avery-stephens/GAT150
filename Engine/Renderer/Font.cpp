#include "Font.h"
#include <SDL_ttf.h>
#include <Math/Color.h>
#include "Core/Logger.h"
#include <SDL.h> 

struct SDL_Texture;

namespace gooblegorb
{
	Font::Font(const std::string& filename, int fontSize)
	{
		// !! call Load() function below passing filename and fontSize
		Load(filename, fontSize);
	}

	Font::~Font()
	{
		// !! if m_ttfFont not null, close font (TTF_CloseFont) 
		if (m_ttfFont != nullptr)
		{
			TTF_CloseFont(m_ttfFont);
		}
	}

	/*
	bool Font::Create(const std::string& filename, void* data)
	{
		return false;
	}
	*/

	bool Font::Create(std::string filename, ...)
	{
		// va_list - type to hold information about variable arguments 
		va_list args;

		// va_start - enables access to variadic function arguments 
		va_start(args, filename);

		// va_arg - accesses the next variadic function arguments 
		int fontSize = va_arg(args, int);

		// va_end - ends traversal of the variadic function arguments 
		va_end(args);


		Load(filename, fontSize);

		return true;
	}

	void Font::Load(const std::string& filename, int fontSize)
	{
		// !! call TTF_OpenFont 
		m_ttfFont = TTF_OpenFont(filename.c_str(), fontSize);
		if (m_ttfFont == nullptr)
		{
			LOG("error could not open font %s", filename.c_str());
		}
		// !! use filename.c_str() to get the c-style string
		
		// !! assign the return value of TTF_OpenFont to m_ttfFont
	}

	SDL_Surface* Font::CreateSurface(const std::string& text, const Color& color)
	{
		SDL_Color c = *((SDL_Color*)(&color));
		SDL_Surface* surface = TTF_RenderText_Solid(m_ttfFont, text.c_str(), c);

		// !! check if surface is nullptr, if so then LOG error 
		if (surface == nullptr)
		{
			LOG(SDL_GetError());
		}

		return surface;
	}
}