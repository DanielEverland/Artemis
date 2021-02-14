#include <cmath>

#include "Character.h"
#include "ArgumentException.h"
#include "World.h"
#include "Game/Framework/Time.h"
#include "Game/Modding/ModLoader.h"

shared_ptr<Character> Character::Create(World* world)
{
	auto character = world->CreateEntity<Character>(ModLoader::GetType("Character"));
	const Json* data = character->GetData();

	if(!data->Contains("Texture"))
		throw ArgumentException("Couldn't create character because data doesn't contain field Texture");

	character->Appearance = ModLoader::GetTexture(data->At<string>("Texture"));
	
	return character;
}

void Character::Draw()
{
	Renderer::GetPrimaryRenderer()->SetDrawColor(Color::White);
	Renderer::GetPrimaryRenderer()->DrawTexture(Appearance->GetRawTexture(), GetBounds());
}

void Character::Update()
{
	Vector offset(100, 100);
	float radius = 50.f;
	float speed = 5.f;
	float time = Time::GetTime();
	time *= speed;
	Vector circlePos(cos(time) * radius, sin(time) * radius);
	LocalPosition = offset + circlePos;
}

Rect Character::GetBounds()
{
	Rect rect;
	rect.Position = LocalPosition;
	rect.Size = LocalScale * Vector(Appearance->GetWidth(), Appearance->GetHeight());

	return rect;
}
