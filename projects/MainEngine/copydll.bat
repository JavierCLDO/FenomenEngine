cd ..\..\

dir

echo deleting dlls in bin ...
del  ".\bin\*.dll"
echo ... done

dir 

xcopy "dependencies\Fmod\lib\fmod.dll" ".\bin"

xcopy ".\dependencies\Ogre\ogre-next\build\bin\release\OgreAtmosphere.dll" ".\bin"
xcopy ".\dependencies\Ogre\ogre-next\build\bin\release\OgreHlmsPbs.dll" ".\bin"
xcopy ".\dependencies\Ogre\ogre-next\build\bin\release\OgreHlmsUnlit.dll" ".\bin"
xcopy ".\dependencies\Ogre\ogre-next\build\bin\release\OgreMain.dll" ".\bin"
xcopy ".\dependencies\Ogre\ogre-next\build\bin\release\OgreOverlay.dll" ".\bin"

xcopy ".\dependencies\Physx\physX\bin\win.x86_64.vc142.md\release\PhysX_64.dll" ".\bin"
xcopy ".\dependencies\Physx\physX\bin\win.x86_64.vc142.md\release\PhysXCommon_64.dll" ".\bin"
xcopy ".\dependencies\Physx\physX\bin\win.x86_64.vc142.md\release\PhysXCooking_64.dll" ".\bin"
xcopy ".\dependencies\Physx\physX\bin\win.x86_64.vc142.md\release\PhysXFoundation_64.dll" ".\bin"
xcopy ".\dependencies\Physx\physX\bin\win.x86_64.vc142.md\release\PhysXGpu_64.dll" ".\bin"

xcopy ".\dependencies\SDL2\build\release\SDL2.dll" ".\bin"

exit 0