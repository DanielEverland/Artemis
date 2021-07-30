////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _GRAPHICSCLASS_H_
#define _GRAPHICSCLASS_H_


///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "Rendering/GraphicsDevice.h"
#include "cameraclass.h"
#include "modelclass.h"
#include "colorshaderclass.h"
#include "Rendering/Renderer.h"

using namespace ArtemisEngine;

/////////////
// GLOBALS //
/////////////
const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;


////////////////////////////////////////////////////////////////////////////////
// Class name: GraphicsClass
////////////////////////////////////////////////////////////////////////////////
class GraphicsClass
{
public:
	GraphicsClass();
	bool Initialize(int, int, HWND, shared_ptr<Renderer> renderer);
	void Shutdown();
	bool Frame();

private:
	bool Render();

private:
	shared_ptr<GraphicsDevice> GraphicsDevice;
	CameraClass* m_Camera;
	ModelClass* m_Model;
	ColorShaderClass* m_ColorShader;
};

#endif