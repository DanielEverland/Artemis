#pragma once

#include "Entity.h"

class Texture;
class World;

class Character : public Entity
{
public:
	Character(const EntityType* type, World* world) : Entity(type, world), Appearance(nullptr) { }
	virtual ~Character() = default;
	static std::shared_ptr<Character> Create(World* world);

	void Draw() override;
	
private:
	Texture* Appearance;
};
