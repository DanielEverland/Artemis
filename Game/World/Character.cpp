#include "Character.h"


#include "ArgumentException.h"
#include "World.h"
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
	Renderer::GetPrimaryRenderer()->DrawTexture(Appearance->GetRawTexture(), { 10, 10, 300, 300 });
}
