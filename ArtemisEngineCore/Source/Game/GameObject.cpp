#include "Include/Game/GameObject.h"

Vector3 GameObject::GetPosition() const
{
	return transform.Position;
}

Quaternion GameObject::GetRotation() const
{
	return transform.Rotation;
}

Vector3 GameObject::GetScale() const
{
	return transform.Scale;
}

const Transform* GameObject::GetTransform() const
{
	return &transform;
}
