// MainEngine.cpp : Define las funciones de la biblioteca estática.
//

#include "pch.h"
#include "framework.h"
#include "renderEngine.h"

#include "SDL.h"
#include <SDL_video.h>
#include <SDL_syswm.h>

#include "OgreAbiUtils.h"
#include "OgreConfigFile.h"
#include "OgreException.h"
#include "OgreRoot.h"

#include "OgreCamera.h"
#include "OgreItem.h"

#include "OgreArchiveManager.h"
#include "OgreHlmsManager.h"
#include "OgreHlmsPbs.h"
#include "OgreHlmsUnlit.h"

#include "Compositor/OgreCompositorManager2.h"

#include "OgreTextureGpuManager.h"

#include "OgreWindow.h"
#include "OgreWindowEventUtilities.h"

#include "OgreFileSystemLayer.h"

#include "OgreGpuProgramManager.h"
#include "OgreHlmsDiskCache.h"

#include "OgreLogManager.h"

#include "OgrePlatformInformation.h"

#include "System/Android/AndroidSystems.h"

#include "OgreAtmosphereComponent.h"

#include "OgreMesh2.h"
#include "OgreMeshManager.h"
#include "OgreMeshManager2.h"

#include "OgreHlmsPbsDatablock.h"
#include "OgreHlmsSamplerblock.h"

#include "OgreHlmsManager.h"
#include "OgreHlmsPbs.h"
#include "OgreRoot.h"
#include "OgreTextureFilters.h"
#include "OgreTextureGpuManager.h"
#include "OgreAtmosphereComponent.h"
#include "OgreAtmosphereNpr.h"

#include "Utils/HdrUtils.h"


#include <assert.h>

#include <fstream>

using namespace fenomen::render;

std::unique_ptr<RenderEngine> RenderEngine::instance = nullptr;

RenderEngine::RenderEngine(): _resourcePath(), _datablockID(), _numMeshID(), _numCameras(), _atmosphere(nullptr)
{
}


int RenderEngine::Close()
{
	std::cout << "RenderEngine::Exit\n";
    saveTextureCache();
    saveHlmsDiskCache();

    if (_sceneManager)
    {
        delete _sceneManager->getAtmosphereRaw();
        //_root->destroySceneManager(_sceneManager);
        _root->shutdown();
    }
  

    if (_sdlWindow)
    {
        // Restore desktop resolution on exit
        SDL_SetWindowFullscreen(_sdlWindow, 0);
        SDL_DestroyWindow(_sdlWindow);
        _sdlWindow = 0;
    }

	return 0;
}


RenderEngine& RenderEngine::CreateInstance()
{
	if (instance.get() == nullptr) {
		instance.reset(new RenderEngine());
	}

	return *instance;
}

int RenderEngine::Init()
{
	std::cout << "RenderEngine::Init\n";

    _resourcePath = "RenderEngineConfig/";

    mWriteAccessFolder = _resourcePath;

	const Ogre::AbiCookie abiCookie = Ogre::generateAbiCookie();
	
#if _DEBUG
		_root = new Ogre::Root(&abiCookie, _resourcePath + "plugins_d.cfg", _resourcePath + "ogre.cfg");
#else
		_root = new Ogre::Root(&abiCookie, _resourcePath + "plugins.cfg", _resourcePath + "ogre.cfg");
#endif

	Ogre::RenderSystemList::const_iterator itor = _root->getAvailableRenderers().begin();
	Ogre::RenderSystemList::const_iterator endt = _root->getAvailableRenderers().end();

	if (!_root->restoreConfig() && !_root->showConfigDialog())
	{
		return -1;
	}

    //_root->showConfigDialog();

	setupWindow();

    setupResources();
    loadResources();
    chooseSceneManager();
    _workspace = setupCompositor();
    createScene();

	return 0;
}


void fenomen::render::RenderEngine::setupWindow()
{
    const char* windowTitle = "FenomenEngine Window";

	_root->initialise(false, windowTitle);

	Ogre::ConfigOptionMap& cfgOpts = _root->getRenderSystem()->getConfigOptions();

	int width = 1280;
	int height = 720;

    Ogre::ConfigOptionMap::iterator opt = cfgOpts.find("Video Mode");
    if (opt != cfgOpts.end() && !opt->second.currentValue.empty())
    {
        // Ignore leading space
        const Ogre::String::size_type start = opt->second.currentValue.find_first_of("012356789");
        // Get the width and height
        Ogre::String::size_type widthEnd = opt->second.currentValue.find(' ', start);
        // we know that the height starts 3 characters after the width and goes until the next space
        Ogre::String::size_type heightEnd = opt->second.currentValue.find(' ', widthEnd + 3);
        // Now we can parse out the values
        width = Ogre::StringConverter::parseInt(opt->second.currentValue.substr(0, widthEnd));
        height = Ogre::StringConverter::parseInt(
            opt->second.currentValue.substr(widthEnd + 3, heightEnd));
    }

    Ogre::NameValuePairList params;
    bool fullscreen = Ogre::StringConverter::parseBool(cfgOpts["Full Screen"].currentValue);

    unsigned int screen = 0;
    unsigned int posX = SDL_WINDOWPOS_CENTERED_DISPLAY(screen);
    unsigned int posY = SDL_WINDOWPOS_CENTERED_DISPLAY(screen);

    if (fullscreen)
    {
        posX = SDL_WINDOWPOS_UNDEFINED_DISPLAY(screen);
        posY = SDL_WINDOWPOS_UNDEFINED_DISPLAY(screen);
    }

    _sdlWindow = SDL_CreateWindow(
        windowTitle,       // window title
        static_cast<int>(posX),  // initial x position
        static_cast<int>(posY),  // initial y position
        width,                     // width, in pixels
        height,                    // height, in pixels
        SDL_WINDOW_SHOWN | (fullscreen ? SDL_WINDOW_FULLSCREEN : 0) | SDL_WINDOW_RESIZABLE);

    // Get the native whnd
    SDL_SysWMinfo wmInfo;
    SDL_VERSION(&wmInfo.version);

    if (SDL_GetWindowWMInfo(_sdlWindow, &wmInfo) == SDL_FALSE)
    {
        OGRE_EXCEPT(Ogre::Exception::ERR_INTERNAL_ERROR, "Couldn't get WM Info! (SDL2)",
            "GraphicsSystem::initialize");
    }

    Ogre::String winHandle;
    switch (wmInfo.subsystem)
    {
#if defined( SDL_VIDEO_DRIVER_WINDOWS )
    case SDL_SYSWM_WINDOWS:
        // Windows code
        winHandle = Ogre::StringConverter::toString((uintptr_t)wmInfo.info.win.window);
        break;
#endif
#if defined( SDL_VIDEO_DRIVER_WINRT )
    case SDL_SYSWM_WINRT:
        // Windows code
        winHandle = Ogre::StringConverter::toString((uintptr_t)wmInfo.info.winrt.window);
        break;
#endif
#if defined( SDL_VIDEO_DRIVER_COCOA )
    case SDL_SYSWM_COCOA:
        winHandle = Ogre::StringConverter::toString(WindowContentViewHandle(wmInfo));
        break;
#endif
#if defined( SDL_VIDEO_DRIVER_X11 )
    case SDL_SYSWM_X11:
        winHandle = Ogre::StringConverter::toString((uintptr_t)wmInfo.info.x11.window);
        params.insert(std::make_pair(
            "SDL2x11", Ogre::StringConverter::toString((uintptr_t)&wmInfo.info.x11)));
        break;
#endif
    default:
        OGRE_EXCEPT(Ogre::Exception::ERR_NOT_IMPLEMENTED, "Unexpected WM! (SDL2)",
            "GraphicsSystem::initialize");
        break;
    }

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32 || OGRE_PLATFORM == OGRE_PLATFORM_WINRT
    params.insert(std::make_pair("externalWindowHandle", winHandle));
#else
    params.insert(std::make_pair("parentWindowHandle", winHandle));
#endif

    params.insert(std::make_pair("title", windowTitle));
    params.insert(std::make_pair("gamma", cfgOpts["sRGB Gamma Conversion"].currentValue));
    if (cfgOpts.find("VSync Method") != cfgOpts.end())
        params.insert(std::make_pair("vsync_method", cfgOpts["VSync Method"].currentValue));
    params.insert(std::make_pair("FSAA", cfgOpts["FSAA"].currentValue));
    params.insert(std::make_pair("vsync", cfgOpts["VSync"].currentValue));
    params.insert(std::make_pair("reverse_depth", "Yes"));

    _renderWindow = Ogre::Root::getSingleton().createRenderWindow(
        windowTitle,                                                      //
        static_cast<uint32_t>(width), static_cast<uint32_t>(height),  //
        fullscreen, &params);
}

void fenomen::render::RenderEngine::setupResources()
{
    // Load resource paths from config file
    Ogre::ConfigFile cf;
    cf.load(_resourcePath + "resources.cfg");

    // Go through all sections & settings in the file
    Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();

    Ogre::String secName, typeName, archName;
    while (seci.hasMoreElements())
    {
        secName = seci.peekNextKey();
        Ogre::ConfigFile::SettingsMultiMap* settings = seci.getNext();

        if (secName != "Hlms")
        {
            Ogre::ConfigFile::SettingsMultiMap::iterator i;
            for (i = settings->begin(); i != settings->end(); ++i)
            {
                typeName = i->first;
                archName = i->second;
                Ogre::ResourceGroupManager::getSingleton().addResourceLocation(archName, typeName, secName);
            }
        }
    }

    Ogre::String originalDataFolder = cf.getSetting("DoNotUseAsResource", "Hlms", "");

    if (originalDataFolder.empty())
        originalDataFolder = "./";
    else if (*(originalDataFolder.end() - 1) != '/')
        originalDataFolder += "/";

    const char* c_locations[5] = { "2.0/scripts/materials/HDR", "2.0/scripts/materials/HDR/GLSL",
                                   "2.0/scripts/materials/HDR/HLSL",
                                   "2.0/scripts/materials/HDR/Metal",
                                   "2.0/scripts/materials/PbsMaterials" };

    for (size_t i = 0; i < 5; ++i)
    {
        Ogre::String dataFolder = originalDataFolder + c_locations[i];
        Ogre::ResourceGroupManager::getSingleton().addResourceLocation(dataFolder, "FileSystem", "General");
    }
}

void fenomen::render::RenderEngine::loadResources()
{
    registerHlms();

    loadTextureCache();
    loadHlmsDiskCache();

    // Initialise, parse scripts etc
    Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups(true);

    // Initialize resources for LTC area lights and accurate specular reflections (IBL)
    Ogre::Hlms* hlms = _root->getHlmsManager()->getHlms(Ogre::HLMS_PBS);
    OGRE_ASSERT_HIGH(dynamic_cast<Ogre::HlmsPbs*>(hlms));
    Ogre::HlmsPbs* hlmsPbs = static_cast<Ogre::HlmsPbs*>(hlms);
    try
    {
        hlmsPbs->loadLtcMatrix();
    }
    catch (Ogre::FileNotFoundException& e)
    {
        Ogre::LogManager::getSingleton().logMessage(e.getFullDescription(), Ogre::LML_CRITICAL);
        Ogre::LogManager::getSingleton().logMessage(
            "WARNING: LTC matrix textures could not be loaded. Accurate specular IBL reflections "
            "and LTC area lights won't be available or may not function properly!",
            Ogre::LML_CRITICAL);
    }
}

void fenomen::render::RenderEngine::chooseSceneManager()
{
#if OGRE_DEBUG_MODE >= OGRE_DEBUG_HIGH
    // Debugging multithreaded code is a PITA, disable it.
    const size_t numThreads = 1;
#else

    /* minus 7 threads because
        * 1 is for Engine
        * 1 is for SDL input
        * 3 are for PhysX
        * 2 are for Fmod
    */
        
    const size_t numThreads = std::max<size_t>(1, Ogre::PlatformInformation::getNumLogicalCores() - 7);
#endif

    std::cout << "ogre threads: " << numThreads << '\n';

    // Create the SceneManager, in this case a generic one
    _sceneManager = _root->createSceneManager(Ogre::ST_GENERIC, numThreads, "ExampleSMInstance");

    _camera = _sceneManager->createCamera("C_0");

    _camera->setNearClipDistance(0.2f);
    _camera->setFarClipDistance(1000.0f);
    _camera->setAutoAspectRatio(true);

    // Set sane defaults for proper shadow mappingç
    _sceneManager->setShadowDirectionalLightExtrusionDistance(500.0f);
    _sceneManager->setShadowFarDistance(500.0f);

    Demo::HdrUtils::init(_renderWindow->getSampleDescription().getColourSamples());
}


void fenomen::render::RenderEngine::createScene()
{
    HDRConfig preset = {
        Colour(0.2f, 0.4f, 0.6f) * 60.0f,  // Sky
        Colour(0.3f, 0.50f, 0.7f) * 4.5f,
        Colour(0.6f, 0.45f, 0.3f) * 2.925f,
        0.0f,   // Exposure
        -1.0f,  // Min Exposure
        1.5f,   // Max Exposure
        5.0f,   // Bloom
        16.0f   // Env. map scale
    };

    setHDR(preset);
}

Ogre::CompositorWorkspace* fenomen::render::RenderEngine::setupCompositor()
{
    Ogre::CompositorManager2* compositorManager = _root->getCompositorManager2();
    Ogre::RenderSystem* renderSystem = _root->getRenderSystem();
    const Ogre::RenderSystemCapabilities* caps = renderSystem->getCapabilities();

    Ogre::String compositorName = "HdrWorkspace";
    if (_renderWindow->isMultisample() &&
        caps->hasCapability(Ogre::RSC_EXPLICIT_FSAA_RESOLVE))
        compositorName = "HdrWorkspaceMsaa";

    return compositorManager->addWorkspace(_sceneManager, _renderWindow->getTexture(), _camera,
        compositorName, true);
}

void fenomen::render::RenderEngine::setHDR(const HDRConfig& cf)
{
    currentConfig = cf;

    Demo::HdrUtils::setSkyColour(Ogre::ColourValue(cf.skyColour.r, cf.skyColour.g, cf.skyColour.b, cf.skyColour.a), 1.0f, _workspace);
    Demo::HdrUtils::setExposure(cf.exposure, cf.minAutoExposure, cf.maxAutoExposure);
    Demo::HdrUtils::setBloomThreshold(std::max(cf.bloomThreshold - 2.0f, 0.0f),
        std::max(cf.bloomThreshold, 0.01f));

    _sceneManager->setAmbientLight(Ogre::ColourValue(cf.ambLowerHemisphere.r, cf.ambLowerHemisphere.g, cf.ambLowerHemisphere.b, cf.ambLowerHemisphere.a), 
        Ogre::ColourValue(cf.ambUpperHemisphere.r, cf.ambUpperHemisphere.g, cf.ambUpperHemisphere.b, cf.ambUpperHemisphere.a),
        _sceneManager->getAmbientLightHemisphereDir(), cf.envmapScale);
}

void fenomen::render::RenderEngine::setAtmosphere(Ogre::Light* light)
{
    if (!_atmosphere) {
        createAtmosphere(light);
        _atmosphere = static_cast<Ogre::AtmosphereNpr*>(_sceneManager->getAtmosphere());
    }

    Ogre::AtmosphereNpr::Preset atmoPreset;
    atmoPreset.time = 1.0f;
    atmoPreset.sunPower = light->getPowerScale();
    atmoPreset.skyPower = Ogre::ColourValue(currentConfig.skyColour.r, currentConfig.skyColour.g, currentConfig.skyColour.b, currentConfig.skyColour.a).toVector3().collapseMax() * 2.0f;
    atmoPreset.skyColour = Ogre::ColourValue(currentConfig.skyColour.r, currentConfig.skyColour.g, currentConfig.skyColour.b, currentConfig.skyColour.a).toVector3() / atmoPreset.skyPower;
    atmoPreset.linkedLightPower = light->getPowerScale();
    atmoPreset.envmapScale = currentConfig.envmapScale;

    // The colour we pass to Atmosphere is too greenish when displayed. Correct it a bit.
    atmoPreset.skyColour *= Ogre::Vector3(1.0f, 0.9f, 1.0f);

    atmoPreset.linkedSceneAmbientUpperPower *= 50.0f;
    atmoPreset.linkedSceneAmbientLowerPower *= 50.0f;

    _atmosphere->setPreset(atmoPreset);
}


void fenomen::render::RenderEngine::registerHlms()
{
    Ogre::ConfigFile cf;
    cf.load(_resourcePath + "resources.cfg");

    Ogre::String rootHlmsFolder = cf.getSetting("DoNotUseAsResource", "Hlms", "");

    if (rootHlmsFolder.empty())
        rootHlmsFolder = "./";
    else if (*(rootHlmsFolder.end() - 1) != '/')
        rootHlmsFolder += "/";

    // At this point rootHlmsFolder should be a valid path to the Hlms data folder

    Ogre::HlmsUnlit* hlmsUnlit = 0;
    Ogre::HlmsPbs* hlmsPbs = 0;

    // For retrieval of the paths to the different folders needed
    Ogre::String mainFolderPath;
    Ogre::StringVector libraryFoldersPaths;
    Ogre::StringVector::const_iterator libraryFolderPathIt;
    Ogre::StringVector::const_iterator libraryFolderPathEn;

    Ogre::ArchiveManager& archiveManager = Ogre::ArchiveManager::getSingleton();

    const Ogre::String& archiveType = "FileSystem";

    {
        // Create & Register HlmsUnlit
        // Get the path to all the subdirectories used by HlmsUnlit
        Ogre::HlmsUnlit::getDefaultPaths(mainFolderPath, libraryFoldersPaths);
        Ogre::Archive* archiveUnlit =
            archiveManager.load(rootHlmsFolder + mainFolderPath, archiveType, true);
        Ogre::ArchiveVec archiveUnlitLibraryFolders;
        libraryFolderPathIt = libraryFoldersPaths.begin();
        libraryFolderPathEn = libraryFoldersPaths.end();
        while (libraryFolderPathIt != libraryFolderPathEn)
        {
            Ogre::Archive* archiveLibrary =
                archiveManager.load(rootHlmsFolder + *libraryFolderPathIt, archiveType, true);
            archiveUnlitLibraryFolders.push_back(archiveLibrary);
            ++libraryFolderPathIt;
        }

        // Create and register the unlit Hlms
        hlmsUnlit = OGRE_NEW Ogre::HlmsUnlit(archiveUnlit, &archiveUnlitLibraryFolders);
        Ogre::Root::getSingleton().getHlmsManager()->registerHlms(hlmsUnlit);
    }

    {
        // Create & Register HlmsPbs
        // Do the same for HlmsPbs:
        Ogre::HlmsPbs::getDefaultPaths(mainFolderPath, libraryFoldersPaths);
        Ogre::Archive* archivePbs =
            archiveManager.load(rootHlmsFolder + mainFolderPath, archiveType, true);

        // Get the library archive(s)
        Ogre::ArchiveVec archivePbsLibraryFolders;
        libraryFolderPathIt = libraryFoldersPaths.begin();
        libraryFolderPathEn = libraryFoldersPaths.end();
        while (libraryFolderPathIt != libraryFolderPathEn)
        {
            Ogre::Archive* archiveLibrary =
                archiveManager.load(rootHlmsFolder + *libraryFolderPathIt, archiveType, true);
            archivePbsLibraryFolders.push_back(archiveLibrary);
            ++libraryFolderPathIt;
        }

        // Create and register
        hlmsPbs = OGRE_NEW Ogre::HlmsPbs(archivePbs, &archivePbsLibraryFolders);
        Ogre::Root::getSingleton().getHlmsManager()->registerHlms(hlmsPbs);
    }

    Ogre::RenderSystem* renderSystem = _root->getRenderSystem();
    if (renderSystem->getName() == "Direct3D11 Rendering Subsystem")
    {
        // Set lower limits 512kb instead of the default 4MB per Hlms in D3D 11.0
        // and below to avoid saturating AMD's discard limit (8MB) or
        // saturate the PCIE bus in some low end machines.
        bool supportsNoOverwriteOnTextureBuffers;
        renderSystem->getCustomAttribute("MapNoOverwriteOnDynamicBufferSRV",
            &supportsNoOverwriteOnTextureBuffers);

        if (!supportsNoOverwriteOnTextureBuffers)
        {
            hlmsPbs->setTextureBufferDefaultSize(512 * 1024);
            hlmsUnlit->setTextureBufferDefaultSize(512 * 1024);
        }
    }
}

void fenomen::render::RenderEngine::loadTextureCache()
{
#if !OGRE_NO_JSON
    Ogre::ArchiveManager& archiveManager = Ogre::ArchiveManager::getSingleton();
    Ogre::Archive* rwAccessFolderArchive =
        archiveManager.load(_resourcePath, "FileSystem", true);
    try
    {
        const Ogre::String filename = "textureMetadataCache.json";
        if (rwAccessFolderArchive->exists(filename))
        {
            Ogre::DataStreamPtr stream = rwAccessFolderArchive->open(filename);
            std::vector<char> fileData;
            fileData.resize(stream->size() + 1);
            if (!fileData.empty())
            {
                stream->read(&fileData[0], stream->size());
                // Add null terminator just in case (to prevent bad input)
                fileData.back() = '\0';
                Ogre::TextureGpuManager* textureManager =
                    _root->getRenderSystem()->getTextureGpuManager();
                textureManager->importTextureMetadataCache(stream->getName(), &fileData[0], false);
            }
        }
        else
        {
            Ogre::LogManager::getSingleton().logMessage("[INFO] Texture cache not found at " +
                _resourcePath +
                "/textureMetadataCache.json");
        }
    }
    catch (Ogre::Exception& e)
    {
        Ogre::LogManager::getSingleton().logMessage(e.getFullDescription());
    }

    archiveManager.unload(rwAccessFolderArchive);
#endif
}

void fenomen::render::RenderEngine::saveTextureCache()
{
    if (_root->getRenderSystem())
    {
        Ogre::TextureGpuManager* textureManager = _root->getRenderSystem()->getTextureGpuManager();
        if (textureManager)
        {
            Ogre::String jsonString;
            textureManager->exportTextureMetadataCache(jsonString);
            const Ogre::String path = mWriteAccessFolder + "/textureMetadataCache.json";
            std::ofstream file(path.c_str(), std::ios::binary | std::ios::out);
            if (file.is_open())
                file.write(jsonString.c_str(), static_cast<std::streamsize>(jsonString.size()));
            file.close();
        }
    }
}

void fenomen::render::RenderEngine::loadHlmsDiskCache()
{
    Ogre::HlmsManager* hlmsManager = _root->getHlmsManager();
    Ogre::HlmsDiskCache diskCache(hlmsManager);

    Ogre::ArchiveManager& archiveManager = Ogre::ArchiveManager::getSingleton();

    Ogre::Archive* rwAccessFolderArchive =
        archiveManager.load(_resourcePath, "FileSystem", true);


    // Make sure the microcode cache is enabled.
    Ogre::GpuProgramManager::getSingleton().setSaveMicrocodesToCache(true);
    const Ogre::String filename = "microcodeCodeCache.cache";
    if (rwAccessFolderArchive->exists(filename))
    {
        Ogre::DataStreamPtr shaderCacheFile = rwAccessFolderArchive->open(filename);
        Ogre::GpuProgramManager::getSingleton().loadMicrocodeCache(shaderCacheFile);
    }
    

    for (size_t i = Ogre::HLMS_LOW_LEVEL + 1u; i < Ogre::HLMS_MAX; ++i)
    {
        Ogre::Hlms* hlms = hlmsManager->getHlms(static_cast<Ogre::HlmsTypes>(i));
        if (hlms)
        {
            Ogre::String filename =
                "hlmsDiskCache" + Ogre::StringConverter::toString(i) + ".bin";

            try
            {
                if (rwAccessFolderArchive->exists(filename))
                {
                    Ogre::DataStreamPtr diskCacheFile = rwAccessFolderArchive->open(filename);
                    diskCache.loadFrom(diskCacheFile);
                    diskCache.applyTo(hlms);
                }
            }
            catch (Ogre::Exception&)
            {
                Ogre::LogManager::getSingleton().logMessage(
                    "Error loading cache from " + mWriteAccessFolder + "/" + filename +
                    "! If you have issues, try deleting the file "
                    "and restarting the app");
            }
        }
    }
    

    archiveManager.unload(mWriteAccessFolder);
}

void fenomen::render::RenderEngine::saveHlmsDiskCache()
{
    if (_root->getRenderSystem() && Ogre::GpuProgramManager::getSingletonPtr())
    {
        Ogre::HlmsManager* hlmsManager = _root->getHlmsManager();
        Ogre::HlmsDiskCache diskCache(hlmsManager);

        Ogre::ArchiveManager& archiveManager = Ogre::ArchiveManager::getSingleton();

        Ogre::Archive* rwAccessFolderArchive =
            archiveManager.load(mWriteAccessFolder, "FileSystem", false);

        for (size_t i = Ogre::HLMS_LOW_LEVEL + 1u; i < Ogre::HLMS_MAX; ++i)
        {
            Ogre::Hlms* hlms = hlmsManager->getHlms(static_cast<Ogre::HlmsTypes>(i));
            if (hlms)
            {
                diskCache.copyFrom(hlms);

                Ogre::DataStreamPtr diskCacheFile = rwAccessFolderArchive->create(
                    "hlmsDiskCache" + Ogre::StringConverter::toString(i) + ".bin");
                diskCache.saveTo(diskCacheFile);
            }
        }
       
        if (Ogre::GpuProgramManager::getSingleton().isCacheDirty())
        {
            const Ogre::String filename = "microcodeCodeCache.cache";
            Ogre::DataStreamPtr shaderCacheFile = rwAccessFolderArchive->create(filename);
            Ogre::GpuProgramManager::getSingleton().saveMicrocodeCache(shaderCacheFile);
        }

        archiveManager.unload(mWriteAccessFolder);
    }
}

void fenomen::render::RenderEngine::createAtmosphere(Ogre::Light* sunLight)
{
    {
        Ogre::AtmosphereComponent* atmosphere = _sceneManager->getAtmosphereRaw();
        OGRE_DELETE atmosphere;
    }

    Ogre::AtmosphereNpr* atmosphere =
        OGRE_NEW Ogre::AtmosphereNpr(_root->getRenderSystem()->getVaoManager());

    {
        // Preserve the Power Scale explicitly set by the sample
        Ogre::AtmosphereNpr::Preset preset = atmosphere->getPreset();
        preset.linkedLightPower = sunLight->getPowerScale();
        atmosphere->setPreset(preset);
    }

    atmosphere->setSunDir(
        sunLight->getDirection(),
        std::asin(Ogre::Math::Clamp(-sunLight->getDirection().y, -1.0f, 1.0f)) /
        Ogre::Math::PI);
    atmosphere->setLight(sunLight);
    atmosphere->setSky(_sceneManager, true);
}


void RenderEngine::draw(double deltaTime) {
	_root->renderOneFrame(deltaTime);
}

Ogre::SceneNode* fenomen::render::RenderEngine::createSceneNode()
{
    return _sceneManager->createSceneNode();
}

void fenomen::render::RenderEngine::addNodeToScene(Ogre::SceneNode* node, uint32_t parentID)
{
    Ogre::SceneNode* parent = parentID == 0 ? _sceneManager->getRootSceneNode() : _sceneManager->getSceneNode(parentID);
    parent->addChild(node);      
}

void fenomen::render::RenderEngine::destroySceneNode(Ogre::SceneNode* node)
{
    _sceneManager->destroySceneNode(node);
}

Ogre::HlmsPbsDatablock* fenomen::render::RenderEngine::createDatablock()
{
    Ogre::HlmsManager* hlmsManager = _root->getHlmsManager();

    Ogre::HlmsPbs* hlmsPbs = static_cast<Ogre::HlmsPbs*>(hlmsManager->getHlms(Ogre::HLMS_PBS));

    Ogre::String datablockName = "DB_" + Ogre::StringConverter::toString(_datablockID++);
    Ogre::HlmsPbsDatablock* datablock = static_cast<Ogre::HlmsPbsDatablock*>(
        hlmsPbs->createDatablock(datablockName, datablockName, Ogre::HlmsMacroblock(),
            Ogre::HlmsBlendblock(), Ogre::HlmsParamVec()));

    return datablock;
}

Ogre::Item* fenomen::render::RenderEngine::createPlaneItem(double width, double height, uint32_t xsegments, uint32_t ysegments, double utile, double vtile)
{
    Ogre::String meshv1name = "M1_" + Ogre::StringConverter::toString(_numMeshID++);
    Ogre::String meshv2name = "M2_" + Ogre::StringConverter::toString(_numMeshID++);

    Ogre::v1::MeshPtr planeMeshV1 = Ogre::v1::MeshManager::getSingleton().createPlane(
        meshv1name, Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
        Ogre::Plane(Ogre::Vector3::UNIT_Y, 0.0f), width, height, xsegments, ysegments, true, 1, utile, vtile,
        Ogre::Vector3::UNIT_Z, Ogre::v1::HardwareBuffer::HBU_STATIC,
        Ogre::v1::HardwareBuffer::HBU_STATIC);

    Ogre::MeshPtr planeMesh = Ogre::MeshManager::getSingleton().createByImportingV1(
        meshv2name, Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, planeMeshV1.get(), true,
        true, true);
    
    return _sceneManager->createItem(planeMesh, Ogre::SCENE_DYNAMIC);
}

Ogre::Camera* fenomen::render::RenderEngine::createCamera()
{
    if (_numCameras++ == 0) {
        _camera->detachFromParent();
        return _camera;
    }
    else {
        Ogre::Camera* c = _sceneManager->createCamera("C_" + Ogre::StringConverter::toString(_numCameras));
        _camera->setNearClipDistance(0.2f);
        _camera->setFarClipDistance(1000.0f);
        _camera->setAutoAspectRatio(true);

        return c;
    }
}

const bool& fenomen::render::RenderEngine::isRenderWindowVisible() const
{
    return _renderWindow->isVisible();
}

void fenomen::render::RenderEngine::destroyCamera(Ogre::Camera* cam)
{
    if (_numCameras-- == 1) {
        //Cant delete the only camera
        _camera = cam;
        _sceneManager->getRootSceneNode()->createChildSceneNode()->attachObject(_camera);
    }
    else {
        _sceneManager->destroyCamera(cam);
    }
}
