#pragma once
#include <cstdint>
#include <vector>
#include "../Math/Vector2.h"
#include <array>

namespace gooblegorb
{
	class InputSystem
	{
	public:
		enum KeyState
		{
			Idle,
			Pressed,
			Held,
			Released
		};

	public:
		InputSystem() = default;
		~InputSystem() = default;

		void Initialize();
		void Shutdown();

		void Update();

		KeyState GetKeyState(uint32_t button);
		bool GetKeyDown(int key) { return m_keyboardState[key]; }
		bool GetPreviousKeyDown(int key) { return m_prevKeyboardState[key]; }

	public:
		const Vector2& GetMousePosition() const { return m_mousePosition; }

		KeyState GetButtonState(uint32_t button);
		bool GetButtonDown(uint32_t button) { return m_mouseButtonState[button]; }
		bool GetPreviousButtonDown(uint32_t button)
		{
			return m_prevMouseButtonState[button];
		}
	private:
		Vector2 m_mousePosition;
		std::array<uint8_t, 3> m_mouseButtonState;
		std::array<uint8_t, 3> m_prevMouseButtonState;
	private:
		int m_numKeys;
		//int nums[4];
		std::vector<uint8_t> m_keyboardState;
		std::vector<uint8_t> m_prevKeyboardState;

	};
	extern const uint32_t button_left;
	extern const uint32_t button_middle;
	extern const uint32_t button_right;

	extern const uint32_t key_space;
	extern const uint32_t key_up;
	extern const uint32_t key_down;
	extern const uint32_t key_left;
	extern const uint32_t key_right;
	extern const uint32_t key_z;
	extern const uint32_t key_escape;
}