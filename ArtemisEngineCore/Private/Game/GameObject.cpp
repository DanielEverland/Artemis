#include "Public/Game/GameObject.h"

GameObject::GameObject()
{
	transform = Transform();
	updateEnabled = false;
}

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

bool GameObject::ShouldUpdate() const
{
	return updateEnabled;
}

void GameObject::Update()
{
}

void GameObject::Begin()
{
}