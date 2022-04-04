//
// Created by Alexander Winter on 2022-04-04.
//

#include "world/enemy/Bulldozer.h"
#include "world/Forest.h"
#include "GameAssets.h"
#include "world/animal/Bear.h"
#include "world/enemy/state/EnemyAttackState.h"
#include "ForestScreen.h"

Bulldozer::Bulldozer(Forest& forest, const b2Vec2& position)
	: Enemy(forest, position) {

	sprite.setTexture(*forest.getAssets().get(GameAssets::BULLDOZER));
	debugSprite.setTexture(*forest.getAssets().get(GameAssets::WHITE_PIXEL));

	maxHealth = 20.0f;
	setHealth(maxHealth);

	setPower(0.1f);
	setMsAttackInterval(10);
}

b2Vec2 Bulldozer::getSize() const {
	return b2Vec2(5.0f, 5.0f);
}


void Bulldozer::tick(float delta) {
	if(this->isDestroyed())
	{
		this->getForest().sendToCompost(this);
		return;
	}


	for(Entity* entity : getForest().getObjects()) {
		Bear* bear = dynamic_cast<Bear*>(entity);

		if(bear) {
			if(b2DistanceSquared(bear->getPosition(), getPosition()) < 5.0f * 5.0f) {
				this->state = std::make_shared<EnemyAttackState>(this, bear);
				break;
			}
		}
	}

	Enemy::tick(delta);
}

void Bulldozer::draw(sf::RenderTarget& target, const sf::RenderStates& states) const {
	sf::Vector2<int> rawMousePos = sf::Mouse::getPosition(forest.getScreen().getWindow());
	sf::Vector2f worldMousePos = forest.getScreen().getWindow().mapPixelToCoords({rawMousePos.x, rawMousePos.y}, sf::View({50.0f, 50.0f}, {195.56f, 110.0f}));

	sprite.setPosition({getPosition().x, 100.0f - getPosition().y - getSize().y / 4});

	float flip = facingRight ? -1.0f : 1.0f;

	if(!this->isDestroyed() && (worldMousePos.x - sprite.getPosition().x) * (worldMousePos.x - sprite.getPosition().x) +
							   (worldMousePos.y - sprite.getPosition().y) * (worldMousePos.y - sprite.getPosition().y) < 6)
	{
		whiteSprite.setPosition({getPosition().x, 100.0f - getPosition().y - getSize().y / 4});
		whiteSprite.setOrigin({0.5f * sprite.getTexture()->getSize().x, 0.5f * sprite.getTexture()->getSize().y});
		whiteSprite.setScale({flip * getSize().x * 2.5f / sprite.getTexture()->getSize().x, getSize().y * 2.5f / sprite.getTexture()->getSize().y});
		target.draw(whiteSprite);
	}

	sprite.setOrigin({0.5f * sprite.getTexture()->getSize().x, 0.5f * sprite.getTexture()->getSize().y});
	sprite.setScale({flip * getSize().x * 2.f / sprite.getTexture()->getSize().x,
					 getSize().y * 2.f / sprite.getTexture()->getSize().y});

	target.draw(sprite);
	target.draw(healthBar);

	if(!forest.getScreen().isDebug())
		return;

	drawDebug(target, states);
}
