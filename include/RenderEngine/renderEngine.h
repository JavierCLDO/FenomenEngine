#pragma once

#include <string>
#include "vector.h"
#include "colour.h"

namespace Ogre {
	class Root;
	class Window;
	class SceneManager;
	class SceneNode;
	class Camera;
	class CompositorWorkspace;
	class HlmsPbsDatablock;
	class Item;
	class AtmosphereNpr;
	class Light;
}

struct SDL_Window;

namespace fenomen::render {

class RenderEngine {

public:

	struct HDRConfig
	{
		Colour skyColour;
		Colour ambUpperHemisphere;
		Colour ambLowerHemisphere;
		float exposure;
		float minAutoExposure;
		float maxAutoExposure;
		float bloomThreshold;
		float envmapScale;
	};

public:

	/// <summary>
	/// Returns the instance of GraphicsEngine, in case there is no such instance, it creates one and returns that one
	/// </summary>
	inline static RenderEngine& Instance() { return *instance; }

	/// <summary>
	/// Creates the class instance
	/// </summary>
	static RenderEngine& CreateInstance();


	int Init();

	int Close();

	void draw(double deltaTime);

	void setHDR(const HDRConfig& cf);

	void setAtmosphere(Ogre::Light* light);

	Ogre::SceneNode* createSceneNode();
	void addNodeToScene(Ogre::SceneNode* node, uint32_t parentID = 0);
	void destroySceneNode(Ogre::SceneNode* node);
	void destroyCamera(Ogre::Camera* cam);

	Ogre::HlmsPbsDatablock* createDatablock();
	Ogre::Item* createPlaneItem(double width = 2.0, double height = 2.0, uint32_t xsegments = 1, uint32_t ysegments = 1, double utile = 1.0, double vtile = 1.0);

	Ogre::Camera* createCamera();

	const bool& isRenderWindowVisible() const;

private:

	static std::unique_ptr<RenderEngine> instance;

	RenderEngine();

	void setupWindow();

	void setupResources();
	void loadResources();
	void chooseSceneManager();
	void createScene();

	Ogre::CompositorWorkspace* setupCompositor();

	void registerHlms();
	void loadTextureCache();
	void saveTextureCache();
	void loadHlmsDiskCache();
	void saveHlmsDiskCache();

	void createAtmosphere(Ogre::Light* sunLight);

	Ogre::Root* _root;
	Ogre::Window* _renderWindow;
	Ogre::SceneManager* _sceneManager;
	Ogre::Camera* _camera;
	Ogre::CompositorWorkspace* _workspace;
	Ogre::AtmosphereNpr* _atmosphere;

	SDL_Window* _sdlWindow;

	std::string mWriteAccessFolder;
	std::string _resourcePath;

	uint32_t _datablockID, _numMeshID;
	uint32_t _numCameras;

	HDRConfig currentConfig;

public:
	inline Ogre::SceneManager* getSceneManager() { return _sceneManager; }
	inline SDL_Window* getSDLWindow() { return _sdlWindow; }
};

}