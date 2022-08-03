#include "InputSystem.h"
#include <SDL.h>
#include <iostream>

namespace gooblegorb
{
	const uint32_t key_space = SDL_SCANCODE_SPACE;
	const uint32_t key_up = SDL_SCANCODE_UP;
	const uint32_t key_down = SDL_SCANCODE_DOWN;
	const uint32_t key_left = SDL_SCANCODE_LEFT;
	const uint32_t key_right = SDL_SCANCODE_RIGHT;
	const uint32_t key_escape = SDL_SCANCODE_ESCAPE;
	const uint32_t key_z = SDL_SCANCODE_Z;

	const uint32_t button_left = 0;
	const uint32_t button_middle = 1;
	const uint32_t button_right = 2;

	void InputSystem::Initialize()
	{
		const uint8_t* keyboardState = SDL_GetKeyboardState(&m_numKeys);

		m_keyboardState.resize(m_numKeys);
		std::copy(keyboardState, keyboardState + m_numKeys, m_keyboardState.begin());

		m_prevKeyboardState = m_keyboardState;
	}

	void InputSystem::Shutdown()
	{
		//
	}

	void InputSystem::Update()
	{
		SDL_Event event;
		SDL_PollEvent(&event);

		//saves previous keyboard state
		m_prevKeyboardState = m_keyboardState;

		//get current keyboard state
		const uint8_t* keyboardState = SDL_GetKeyboardState(nullptr);
		std::copy(keyboardState, keyboardState + m_numKeys, m_keyboardState.begin());

		//std::cout << (bool)m_keyboardState[SDL_SCANCODE_SPACE] << std::endl;

		//for ( int i = 0; i < 120; i++)
		//{
		//	std::cout << (bool)m_keyboardState[i];
		//}
		//std::cout << std::endl;

		m_prevMouseButtonState = m_mouseButtonState;
		int x, y;
		uint32_t buttons = SDL_GetMouseState(&x, &y);
		m_mousePosition = gooblegorb::Vector2{ x , y };
		m_mouseButtonState[0] = buttons & SDL_BUTTON_LMASK; // buttons [0001] & [0RML] 
		m_mouseButtonState[1] = buttons & SDL_BUTTON_MMASK; // buttons [0010] & [0RML] 
		m_mouseButtonState[2] = buttons & SDL_BUTTON_RMASK; // buttons [0100] & [0RML] 
	}

	InputSystem::KeyState InputSystem::GetKeyState(uint32_t key)
	{
		KeyState keyState = KeyState::Idle;

		bool keyDown = GetKeyDown(key);
		bool prevKeyDown = GetPreviousKeyDown(key);

		if (keyDown && prevKeyDown) keyState = KeyState::Held;
		if (keyDown && !prevKeyDown) keyState = KeyState::Pressed;
		if (!keyDown && prevKeyDown) keyState = KeyState::Released;
		if (!keyDown && !prevKeyDown) keyState = KeyState::Idle;
		// set the keyState if buttonDown (true) and prevButtonDown (true) 
		// fill in the remaining states 

		return keyState;
	}

	InputSystem::KeyState InputSystem::GetButtonState(uint32_t button)
	{
		KeyState buttonState = KeyState::Idle;

		bool buttonDown = GetButtonDown(button);
		bool prevButtonDown = GetPreviousButtonDown(button);

		if (buttonDown && prevButtonDown) buttonState = KeyState::Held;
		if (buttonDown && !prevButtonDown) buttonState = KeyState::Pressed;
		if (!buttonDown && prevButtonDown) buttonState = KeyState::Released;
		if (!buttonDown && !prevButtonDown) buttonState = KeyState::Idle;
		// set the keyState if buttonDown (true) and prevButtonDown (true) 
		// fill in the remaining states 

		return buttonState;
	}
	
}