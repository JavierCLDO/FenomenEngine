cd ..\..\

dir

echo deleting dlls in bin ...
del  ".\bin\*.dll"
echo ... done

dir 

xcopy "dependencies\Fmod\lib\fmodL.dll" ".\bin"

xcopy ".\dependencies\Ogre\ogre-next\build\bin\debug\OgreAtmosphere_d.dll" ".\bin"
xcopy ".\dependencies\Ogre\ogre-next\build\bin\debug\OgreHlmsPbs_d.dll" ".\bin"
xcopy ".\dependencies\Ogre\ogre-next\build\bin\debug\OgreHlmsUnlit_d.dll" ".\bin"
xcopy ".\dependencies\Ogre\ogre-next\build\bin\debug\OgreMain_d.dll" ".\bin"
xcopy ".\dependencies\Ogre\ogre-next\build\bin\debug\OgreOverlay_d.dll" ".\bin"

xcopy ".\dependencies\Physx\physX\bin\win.x86_64.vc142.md\debug\PhysX_64.dll" ".\bin"
xcopy ".\dependencies\Physx\physX\bin\win.x86_64.vc142.md\debug\PhysXCommon_64.dll" ".\bin"
xcopy ".\dependencies\Physx\physX\bin\win.x86_64.vc142.md\debug\PhysXCooking_64.dll" ".\bin"
xcopy ".\dependencies\Physx\physX\bin\win.x86_64.vc142.md\debug\PhysXFoundation_64.dll" ".\bin"
xcopy ".\dependencies\Physx\physX\bin\win.x86_64.vc142.md\debug\PhysXGpu_64.dll" ".\bin"

xcopy ".\dependencies\SDL2\build\Debug\SDL2d.dll" ".\bin"

exit 0