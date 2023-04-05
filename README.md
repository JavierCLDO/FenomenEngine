**WIP**

FenomenEngine is a game engine created in C++ using Physx for physics simulation, Ogre3D for graphics rendering (on Vulkan), Fmod for audio systems and SLD2 for input and window management.

it uses an entity-component system, but changed so an Entity holds each component separately, allowing the user to inherit a component, adding it to an Entity and getting a component in O(1) complexity

I still did not add Lua support for creating a level, but once is added, the engine should ran only on user data (levels & resources)

The user could use the engine as a dll and then write their own components in C++ and adding them to the engine component factory

It runs multithreaded
