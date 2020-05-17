#include "Include/Game/Camera.h"

Camera::Camera()
{
	transform.Position = Vector3::Back * 10;
}

Matrix Camera::GetViewMatrix() const
{
	return Matrix::TranslateRotationScale(transform.Position, transform.Rotation, Vector3::One).GetInverseMatrix();
}
