#pragma once

#include <memory>
#include <map>
#include <list>
#include <array>
#include <bitset>
#include <cassert>
#include "inputKeys.h"

namespace fenomen {

class InputManager {

public:

	enum ActionEventType {
		KeyDown,
		KeyUp,
		MouseDown,
		MouseUp,
		ButtonDown,
		ButtonUp
	};

	enum AxisEventType {
		Horizontal,
		Vertical
	};

	enum AxisControllerType {
		Mouse,
		Gamepad,
		Keyboard
	};

	struct ActionInfoKeyboard {
		KeyboardKey mainKey;
		KeyboardKey modKey1;
		KeyboardKey modKey2;
	};

	struct ActionInfoMouse {
		MouseButton button;
	};

	struct ActionInfoController {
		ControllerButton button;
	};

	struct MouseAxis {
		AxisEventType axis;
	};

	struct GamepadAxis {
		ControllerAxis axis;
	};

	struct KeyPairAxis {
		KeyboardKey negative;
		KeyboardKey positive;
	};


private:

	class IEventCallback {
	public:
		virtual void operator () () = 0;
		virtual void operator () (double, double) = 0;
	};

	template<typename T>
	class EventActionCallback : public IEventCallback
	{
	public:
		EventActionCallback(T* instance, void (T::* function)()) :
			instance(instance), function(function) {}

		virtual void operator () () override { (instance->*function)(); }
		virtual void operator () (double, double) override {  }

	private:
		void (T::* function)();
		T* instance;
	};

	template<typename T>
	class EventAxisCallback : public IEventCallback
	{
	public:
		EventAxisCallback(T* instance, void (T::* function)(double, double)) :
			instance(instance), function(function) {}

		virtual void operator () () override { }
		virtual void operator () (double deltaTime, double amount) override { (instance->*function)(deltaTime, amount); }

	private:
		void (T::* function)(double, double);
		T* instance;
	};

	struct Action {
		ActionEventType onEvent;

		union {
			ActionInfoKeyboard keyboard;
			ActionInfoMouse mouse;
			ActionInfoController controller;
		};
	};

	struct Axis {
		AxisControllerType controllerType;

		union {
			MouseAxis mouse;
			GamepadAxis controller;
			KeyPairAxis keyboard;
		};
	};

	struct Functions {
		std::list<std::unique_ptr<IEventCallback>> funcs;
	};

public:
	
	InputManager();
	~InputManager();

	int Init(double windowWidth, double windowHeight, double mouseRate = 100.0);

	bool Update(double deltaTime);

	void CreateActionEvent(const std::string& name);
	void CreateAxisEvent(const std::string& name);

//ACTION

	/** Keyboard */
	void AddKeyToActionEvent(const std::string& name, ActionEventType onEvent, 
		KeyboardKey mainKey, KeyboardKey modkey1 = KeyboardKey::KEY_UNKNOWN, KeyboardKey modkey2 = KeyboardKey::KEY_UNKNOWN);
	
	/** Mouse */
	void AddMouseButtonToActionEvent(const std::string& name, ActionEventType onEvent,
		MouseButton button);

	/** Gamepad */
	void AddGamepadButtonToActionEvent(const std::string& name, ActionEventType onEvent,
		ControllerButton button);

//AXIS

	/** Keyboard */
	void AddKeyPairToAxisEvent(const std::string& name,
		KeyboardKey negative, KeyboardKey positive);

	/** Mouse */
	void AddMouseToAxisEvent(const std::string& name, 
		AxisEventType onEvent);

	/** Gamepad */
	void AddControllerToAxisEvent(const std::string& name, 
		ControllerAxis axis);


	template<typename T>
	inline void BindAction(const std::string& eventName, T* instance, void (T::* function)()) {
		size_t id = std::hash<std::string>()(eventName);

		assert(_actionFunctions.contains(id));

		_actionFunctions.find(id)->second.funcs.push_back(std::unique_ptr<IEventCallback>(new EventActionCallback(instance, function)));
	}

	template<typename T>
	inline void BindAxis(const std::string& eventName, T* instance, void (T::* function)(double, double)) {
		size_t id = std::hash<std::string>()(eventName);

		assert(_axisFunctions.contains(id));

		_axisFunctions.find(id)->second.funcs.push_back(std::unique_ptr<IEventCallback>(new EventAxisCallback(instance, function)));
	}

private:

	void FireFuncs(fenomen::InputManager::Functions& f);
	void FireAxisFuncs(fenomen::InputManager::Functions& f, double deltaTime, double value);

	// Keyboard
	std::bitset<NUM_KEYS> _keyJustDown;
	std::bitset<NUM_KEYS> _keyJustUp;
	std::bitset<NUM_KEYS> _keyIsDown;

	// Mouse
	std::bitset<NUM_MOUSE_BUTTONS> _mouseButtonJustDown;
	std::bitset<NUM_MOUSE_BUTTONS> _mouseButtonJustUp;
	std::bitset<NUM_MOUSE_BUTTONS> _mouseButtonIsDown;
	double _mouseMotion_X, _lastMouseMotion_X, _lastLastMouseMotion_X;
	double _mouseMotion_Y, _lastMouseMotion_Y, _lastLastMouseMotion_Y;
	double _inverseWindowWidth, _inverseWindowHeight;

	// Controller
	std::bitset<NUM_CONTROLLER_BUTTON> _controllerButtonJustDown;
	std::bitset<NUM_CONTROLLER_BUTTON> _controllerButtonJustUp;
	std::bitset<NUM_CONTROLLER_BUTTON> _controllerButtonIsDown;
	std::array<double, NUM_CONTROLLER_AXIS> _controllerAxes;

	std::map<size_t, std::list<Action>> _actionEvents;
	std::map<size_t, std::list<Axis>> _axisEvents;

	std::map<size_t, Functions> _actionFunctions;
	std::map<size_t, Functions> _axisFunctions;
};

}