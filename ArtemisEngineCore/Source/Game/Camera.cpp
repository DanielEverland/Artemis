#include "Include/Game/Camera.h"

#include "Include/Game/Screen.h"

Camera::Camera()
{
	//transform.Position = Vector3::Back * 10;

	VerticalFieldOfView = 60;
	NearClipDistance = 0.001f;
	FarClipDistance = 1000;
}

Matrix Camera::GetViewMatrix() const
{
	return Matrix::TranslateRotationScale(transform.Position, transform.Rotation, Vector3::One).GetInverseMatrix();
}

Matrix Camera::GetProjectionMatrix() const
{
	Matrix projectionMatrix = { };

	const float verticalFOV = Math::DegreesToRadians(VerticalFieldOfView);
	const float horizontalFOV = verticalFOV * Screen::GetAspectRatio();
	
	const float w = Math::Cotangent(horizontalFOV / 2);
	const float h = Math::Cotangent(verticalFOV / 2);
	const float Q = FarClipDistance / (FarClipDistance - NearClipDistance);

	projectionMatrix[0][0] = w;
	projectionMatrix[1][1] = h;
	projectionMatrix[2][2] = Q;
	projectionMatrix[3][2] = 1.0;
	projectionMatrix[2][3] = -Q * NearClipDistance;

	return projectionMatrix;
}
