#include "Include/Game/Transform.h"

const Transform Transform::Identity = Transform();

Transform::Transform() : Position(), Rotation(Quaternion::GetIdentity()), Scale(1.0, 1.0, 1.0)
{
}

Transform::Transform(const Vector3& position, const Quaternion& rotation, const Vector3& scale) : Position(position), Rotation(rotation), Scale(scale)
{
}

Matrix Transform::GetWorldMatrix() const
{
	return Matrix::TranslateRotationScale(Position, Rotation, Scale);
}
