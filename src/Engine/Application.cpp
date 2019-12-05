#include "Application.h"
#include <Debug/Output.h>

//#include <Engine/Math/Vectors/Vector2Base.h>
//#include <Engine/Vector2.h>

#include <Engine/Vector2.h>

bool Application::useVSync = false;

void Application::SetVSync(bool enabled)
{
	useVSync = enabled;

	using ArtemisEngine::Vector2;
	//using ArtemisEngine::Vector2;
	//using ArtemisEngine::Math::Vectors::DoubleVector2;
	//using ArtemisEngine::Math::Vectors::Vector2Base;
	
	Vector2 a;
	a[0] = 45;
	a[1] = 32;
}
bool Application::GetVSync()
{
	return useVSync;
}