#include "Application.h"
#include "Math/Matrices/GenericMatrix.h"
#include "Math/Matrices/MatrixBase.h"

bool Application::useVSync = false;

void Application::SetVSync(bool enabled)
{
	useVSync = enabled;

	using ArtemisEngine::Math::Matrices::MatrixBase;
	using ArtemisEngine::Math::Matrices::GenericMatrix;
	GenericMatrix<float, 2, 2> a;
	GenericMatrix<float, 3, 4> b;

}
bool Application::GetVSync()
{
	return useVSync;
}