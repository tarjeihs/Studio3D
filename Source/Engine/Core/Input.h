#pragma once
#include <utility>

class CInput
{
public:
	virtual ~CInput() = default;
	
	inline static bool KeyPressed(int keyCode) { return s_Instance->KeyPressedImpl(keyCode); }
	inline static bool MouseButtonPressed(int keyCode) { return s_Instance->MouseButtonPressedImpl(keyCode); }

	inline static float GetMouseX() { return s_Instance->GetMouseXImpl(); }
	inline static float GetMouseY() { return s_Instance->GetMouseYImpl(); }

	inline static std::pair<float, float> GetMousePosition() { return s_Instance->GetMousePositionImpl(); }
protected:
	// Pure virtual implementation of global functions above.
	virtual bool KeyPressedImpl(int keyCode) = 0;
	virtual bool MouseButtonPressedImpl(int keyCode) = 0;

	virtual float GetMouseXImpl() = 0;
	virtual float GetMouseYImpl() = 0;

	virtual std::pair<float, float> GetMousePositionImpl() = 0;
private:
	static CInput* s_Instance;
};
