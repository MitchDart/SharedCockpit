#include "XPLMDisplay.h"
#include "XPLMGraphics.h"
#include <string.h>
#include "xplane_environment.h"
#include "coordinator.h"
#if IBM
	#include <windows.h>
#endif
#if LIN
	#include <GL/gl.h>
#elif __GNUC__
	#include <OpenGL/gl.h>
#else
	#include <GL/gl.h>
#endif

#ifndef XPLM300
	#error This is made to be compiled against the XPLM300 SDK
#endif

//Keep globals here
Environment* environment;
Coordinator* coordinator;

PLUGIN_API int XPluginStart(
							char *		outName,
							char *		outSig,
							char *		outDesc)
{
	strcpy(outName, "SharedCockpit");
	strcpy(outSig, "dart.SharedCockpit");
	strcpy(outDesc, "Multiplayer SharedCockpit plugin allows you to fly with your friends!");
	
	environment = new XPlaneEnvironment();
	coordinator = new Coordinator(environment);
	coordinator->onStart();

	return 1;
}

PLUGIN_API void	XPluginStop(void) {
	delete coordinator;
	delete environment;
 }

PLUGIN_API void XPluginDisable(void) { }
PLUGIN_API int  XPluginEnable(void)  { return 1; }
PLUGIN_API void XPluginReceiveMessage(XPLMPluginID inFrom, int inMsg, void * inParam) { }