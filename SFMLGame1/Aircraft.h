#pragma once

#include "SFML/Graphics.hpp"
#include "Entity.h"
#include "Textures.h"

class Aircraft : public Entity
{
public:
	enum Type
	{
		Eagle,
		Raptor,
	};

public:
	explicit Aircraft(Type type, const TextureHolder& textures);
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

	virtual unsigned int getCategory() const;

private:
	Type mType;
	sf::Sprite mSprite;
};