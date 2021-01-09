#include "Public/Game/Camera.h"

#include "Public/Game/Input.h"
#include "Public/Game/Screen.h"
#include "Public/Game/Time.h"

Camera::Camera()
{
	//transform.Position = Vector3::Back * 10;

	VerticalFieldOfView = 60;
	NearClipDistance = 0.001f;
	FarClipDistance = 1000;
	updateEnabled = true;
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

void Camera::Update()
{
	if(Input::IsStay(Key::D))
	{
		transform.Position.X += Time::GetDeltaTime();
	}

	if(Input::IsStay(Key::A))
	{
		transform.Position.X -= Time::GetDeltaTime();
	}

	if(Input::IsStay(Key::W))
	{
		transform.Position.Z += Time::GetDeltaTime();
	}

	if(Input::IsStay(Key::S))
	{
		transform.Position.Z -= Time::GetDeltaTime();
	}

	if(Input::IsStay(Key::E))
	{
		transform.Position.Y += Time::GetDeltaTime();
	}

	if(Input::IsStay(Key::Q))
	{
		transform.Position.Y -= Time::GetDeltaTime();
	}
}
