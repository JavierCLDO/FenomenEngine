#include "pch.h"
#include "inputManager.h"
#include <SDL_events.h>
#include <functional> //for std::hash
#include <cassert>

const double epsilon = 0.00001;

fenomen::InputManager::InputManager() : _actionEvents(), _actionFunctions(), _keyJustDown(), _keyJustUp(), _keyIsDown()
{
	_keyIsDown[SDL_SCANCODE_UNKNOWN] = true;
}

fenomen::InputManager::~InputManager()
{
}

int fenomen::InputManager::Init(double windowWidth, double windowHeight, double mouseRate)
{
	_inverseWindowWidth = mouseRate * 1.0 / windowWidth;
	_inverseWindowHeight = mouseRate * 1.0 / windowHeight; 

	SDL_SetRelativeMouseMode(SDL_TRUE);

	//CreateActionEvent("testAction1");
	//CreateActionEvent("testAction2");
	//CreateActionEvent("testAction3");
	//AddKeyToActionEvent("testAction1", ActionEventType::KeyDown, SDL_SCANCODE_A);
	//AddKeyToActionEvent("testAction2", ActionEventType::KeyUp, SDL_SCANCODE_A);
	//AddKeyToActionEvent("testAction3", ActionEventType::KeyDown, SDL_SCANCODE_A, SDL_SCANCODE_LSHIFT);
	/*BindAction("testAction1", this, &InputManager::testAction1);
	BindAction("testAction2", this, &InputManager::testAction2);
	BindAction("testAction3", this, &InputManager::testAction3);*/

	CreateAxisEvent("LookHorizontal");
	CreateAxisEvent("LookVertical");
	AddMouseToAxisEvent("LookHorizontal", AxisEventType::Horizontal);
	AddMouseToAxisEvent("LookVertical", AxisEventType::Vertical);

	CreateAxisEvent("Forward");
	CreateAxisEvent("Right");

	AddKeyPairToAxisEvent("Forward", KEY_S, KEY_W);
	AddKeyPairToAxisEvent("Right", KEY_A, KEY_D);

	AddKeyPairToAxisEvent("Forward", KEY_DOWN, KEY_UP);
	AddKeyPairToAxisEvent("Right", KEY_LEFT, KEY_RIGHT);

	AddControllerToAxisEvent("Forward", ControllerAxis::AXIS_LEFTY);
	AddControllerToAxisEvent("Right", ControllerAxis::AXIS_LEFTX);

	return 0;
}

bool fenomen::InputManager::Update(double deltatime)
{
	_keyJustDown.reset();
	_keyJustUp.reset();
	_mouseButtonJustDown.reset();
	_mouseButtonJustUp.reset();

	_lastLastMouseMotion_X = _lastMouseMotion_X;
	_lastLastMouseMotion_Y = _lastMouseMotion_Y;

	_lastMouseMotion_X = _mouseMotion_X;
	_lastMouseMotion_Y = _mouseMotion_Y;

	_mouseMotion_X = _mouseMotion_Y = 0.0;

	memset(_controllerAxes.data(), 0.0, sizeof(double) * NUM_CONTROLLER_AXIS);

	SDL_Event event;


	//1. Poll events from sdl
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
	//System
		case SDL_QUIT:
			return false;
			break;

	//Actions
		//Keyboard
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_ESCAPE)
				return false;

			if (!_keyIsDown[event.key.keysym.scancode]) {
				_keyJustDown.set(event.key.keysym.scancode, true);
				_keyIsDown[event.key.keysym.scancode] = true;
			}
			break;
		case SDL_KEYUP:
			_keyJustUp.set(event.key.keysym.scancode, true);
			_keyIsDown.set(event.key.keysym.scancode, false);
			break;
		//Mouse
		case SDL_MOUSEBUTTONDOWN:
			if (!_mouseButtonIsDown[event.button.button]) {
				_mouseButtonJustDown.set(event.button.button, true);
				_mouseButtonIsDown.set(event.button.button, true);
			}
			break;
		case SDL_MOUSEBUTTONUP:
			_mouseButtonJustUp.set(event.button.button, true);
			_mouseButtonIsDown.set(event.button.button, false);
			break;
		case SDL_CONTROLLERBUTTONDOWN:
			if (!_controllerButtonIsDown[event.cbutton.button]) {
				_controllerButtonJustDown.set(event.cbutton.button, true);
				_controllerButtonIsDown.set(event.cbutton.button, true);
			}
			break;
		case SDL_CONTROLLERBUTTONUP:
			_controllerButtonJustUp.set(event.cbutton.button, true);
			_controllerButtonIsDown.set(event.cbutton.button, false);
			break;
	//Axis
		//Keyboard (relies on _keyboardIsDown)	
		
		//Mouse
		case SDL_MOUSEMOTION:
			_mouseMotion_X = -(_lastLastMouseMotion_X + _lastMouseMotion_X + event.motion.xrel * _inverseWindowWidth) * 0.3333;
			_mouseMotion_Y = -(_lastLastMouseMotion_Y + _lastMouseMotion_Y + event.motion.yrel * _inverseWindowHeight) * 0.3333;
			break;
		//Controller
		case SDL_CONTROLLERAXISMOTION:
			_controllerAxes[event.caxis.axis] = double(event.caxis.value) / double(1 << 15);
		default:
			break;
		}
	}

	//2. Check which actions to shoot and shoot them
	for (const auto& [key, actions] : _actionEvents) {
		auto& f = _actionFunctions.find(key)->second; 
		bool shoot = false;
		auto it = actions.begin(), end = actions.end();
		while (it != end && !shoot) {
			shoot |= it->onEvent == ActionEventType::KeyDown && _keyJustDown[it->keyboard.mainKey] && _keyIsDown[it->keyboard.modKey1] && _keyIsDown[it->keyboard.modKey2];
			shoot |= it->onEvent == ActionEventType::KeyUp && _keyJustUp[it->keyboard.mainKey] && _keyIsDown[it->keyboard.modKey1] && _keyIsDown[it->keyboard.modKey2];
			shoot |= it->onEvent == ActionEventType::MouseDown && _mouseButtonJustDown[it->mouse.button];
			shoot |= it->onEvent == ActionEventType::MouseUp && _mouseButtonJustUp[it->mouse.button];
			shoot |= it->onEvent == ActionEventType::ButtonDown && _controllerButtonIsDown[it->controller.button];
			shoot |= it->onEvent == ActionEventType::ButtonUp && _controllerButtonJustUp[it->controller.button];
			it++;
		}
		if (shoot) FireFuncs(f);
		
	}

	//3. Check on axis and fire
	for (const auto& [key, axes] : _axisEvents) {
		auto& f = _axisFunctions.find(key)->second;	
		bool shoot = false;
		auto it = axes.begin(), end = axes.end();
		double v = 0.0;
		while (it != end && !shoot) {
			auto axis = *it++;
			switch (axis.controllerType)
			{
			case AxisControllerType::Mouse:
				switch (axis.mouse.axis) {
					case AxisEventType::Horizontal:
						if (std::abs(_mouseMotion_X) > epsilon) {
							shoot = true;
							v = _mouseMotion_X;
						}
						break;
					case AxisEventType::Vertical:
						if (std::abs(_mouseMotion_Y) > epsilon) {
							shoot = true;
							v = _mouseMotion_Y;
						}
						break;
				} 
				break;
			case AxisControllerType::Gamepad:
				v = _controllerAxes[axis.controller.axis];
				if (std::abs(v) > epsilon)
					shoot = true;
				break;
			case AxisControllerType::Keyboard: {
				v = _keyIsDown[axis.keyboard.positive] - _keyIsDown[axis.keyboard.negative];
				if (std::abs(v) > epsilon)
					shoot = true;
				break;
			}
			default:
				break;
			}
		}	

		if (shoot) FireAxisFuncs(f, deltatime, v);
	}
}

void fenomen::InputManager::FireFuncs(fenomen::InputManager::Functions& f)
{
	for (const std::unique_ptr<IEventCallback>& func : f.funcs) {
		(*func)();
	}
}

void fenomen::InputManager::FireAxisFuncs(fenomen::InputManager::Functions& f, double deltaTime, double value)
{
	for (const std::unique_ptr<IEventCallback>& func : f.funcs) {
		(*func)(deltaTime, value);
	}
}

void fenomen::InputManager::CreateActionEvent(const std::string& name)
{
	size_t id = std::hash<std::string>()(name);

	assert(!_actionEvents.contains(id));
	assert(!_actionFunctions.contains(id));

	_actionEvents.insert(std::make_pair(id, std::list<Action>()));
	_actionFunctions.insert(std::make_pair(id, Functions()));
}

void fenomen::InputManager::CreateAxisEvent(const std::string& name)
{
	size_t id = std::hash<std::string>()(name);

	assert(!_axisEvents.contains(id));
	assert(!_axisFunctions.contains(id));

	_axisEvents.insert(std::make_pair(id, std::list<Axis>()));
	_axisFunctions.insert(std::make_pair(id, Functions()));
}

void fenomen::InputManager::AddKeyToActionEvent(const std::string& name, ActionEventType onEvent, KeyboardKey mainKey, KeyboardKey modkey1, KeyboardKey modkey2)
{
	size_t id = std::hash<std::string>()(name);

	assert(_actionEvents.contains(id));

	_actionEvents.find(id)->second.push_back({ onEvent, mainKey, modkey1, modkey2 });
}

void fenomen::InputManager::AddMouseButtonToActionEvent(const std::string& name, ActionEventType onEvent, MouseButton button)
{
	size_t id = std::hash<std::string>()(name);

	assert(_actionEvents.contains(id));

	Action a;
	a.onEvent = onEvent;
	a.mouse.button = button;
	
	_actionEvents.find(id)->second.push_back(a);
}

void fenomen::InputManager::AddGamepadButtonToActionEvent(const std::string& name, ActionEventType onEvent, ControllerButton button)
{
	size_t id = std::hash<std::string>()(name);

	assert(_actionEvents.contains(id));

	Action a;
	a.onEvent = onEvent;
	a.controller.button = button;

	_actionEvents.find(id)->second.push_back(a);
}

void fenomen::InputManager::AddMouseToAxisEvent(const std::string& name, AxisEventType axis) 
{
	size_t id = std::hash<std::string>()(name);

	assert(_axisEvents.contains(id));

	Axis a = { AxisControllerType::Mouse };
	a.mouse.axis = axis;

	_axisEvents.find(id)->second.push_back(a);
}

void fenomen::InputManager::AddControllerToAxisEvent(const std::string& name, ControllerAxis axis)
{
	size_t id = std::hash<std::string>()(name);

	assert(_axisEvents.contains(id));

	Axis a = { AxisControllerType::Gamepad };
	a.controller.axis = axis;

	_axisEvents.find(id)->second.push_back(a);
}

void fenomen::InputManager::AddKeyPairToAxisEvent(const std::string& name, KeyboardKey negative, KeyboardKey positive)
{
	size_t id = std::hash<std::string>()(name);

	assert(_axisEvents.contains(id));

	Axis a = { AxisControllerType::Keyboard };
	a.keyboard.negative = negative;
	a.keyboard.positive = positive;

	_axisEvents.find(id)->second.push_back(a);
}
