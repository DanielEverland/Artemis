#include "Include/Game/Camera.h"

Camera::Camera()
{
	transform.Position = Vector3::Back * 10;
}

Matrix Camera::GetViewMatrix() const
{
	return transform.GetWorldMatrix().GetInverseMatrix();
}
