//
// Created by william on 2022-04-03.
//

#include <UI/WordsButton.h>
#include <GameAssets.h>
#include "UI/EnemyMenu.h"
#include "ForestScreen.h"
#include "world/tree/BigAssTree.h"
#include "world/animal/state/AnimalAttackState.h"
#include "world/animal/Wolf.h"
#include "world/animal/Bear.h"

EnemyMenu::EnemyMenu(const wiz::AssetLoader &assetLoader, Forest &forest) : Menu(assetLoader, forest) {

    enemyMenu.setTexture(*assetLoader.get(GameAssets::ENEMY_MENU));
    enemyMenu.setPosition({25, 20});
    enemyMenu.setColor(sf::Color::White);
    enemyMenu.setScale({4.f, 4.f});

    buttons.push_back(new WordsButton(sf::IntRect({50, 125}, {200, 100}),
                                      forest,
                                      [&](Button* button) {
                                          if (!dynamic_cast<Enemy*>(forest.getScreen().getEntityClickSelection().getSelectedEntity()))
                                              return;
                                          Enemy* enemy = dynamic_cast<Enemy*>(forest.getScreen().getEntityClickSelection().getSelectedEntity());
                                          if(enemy != nullptr)
                                          {
                                              Squirrel* closestSquirrel = nullptr;
                                              float disClosest = 0.f;
                                              for(Entity* e : forest.getObjects())
                                              {
                                                  Squirrel* s = dynamic_cast<Squirrel*>(e);
                                                  if(s && !s->isAttacking())
                                                  {
                                                      if(closestSquirrel == nullptr)
                                                      {
                                                          closestSquirrel = s;
                                                          disClosest = b2DistanceSquared(s->getPosition(), enemy->getPosition());
                                                      }
                                                      else
                                                      {
                                                          float d = b2DistanceSquared(s->getPosition(), enemy->getPosition());
                                                          if(d < disClosest)
                                                          {
                                                              disClosest = d;
                                                              closestSquirrel = s;
                                                          }
                                                      }
                                                  }
                                              }
                                              if(closestSquirrel)
                                              {
                                                  closestSquirrel->setState(std::make_shared<AnimalAttackState>(closestSquirrel, enemy));
                                                  forest.unassignSquirrel(closestSquirrel);
                                              }
                                          }
                                      },
                                      [&](){ return forest.getSquirrelCount() > 0; },
                                      "Squirrel Attack"
    ));
    // Wolf Button
    buttons.push_back(new WordsButton(sf::IntRect({50, 270}, {200, 100}),
                                      forest,
                                      [&](Button* button) {
                                          if (!dynamic_cast<Enemy*>(forest.getScreen().getEntityClickSelection().getSelectedEntity()))
                                              return;
                                          Enemy* enemy = dynamic_cast<Enemy*>(forest.getScreen().getEntityClickSelection().getSelectedEntity());
                                          if(enemy != nullptr)
                                          {
                                              Wolf* closestWolf = nullptr;
                                              float disClosest = 0.f;
                                              for(Entity* e : forest.getObjects())
                                              {
                                                  Wolf* s = dynamic_cast<Wolf*>(e);
                                                  if(s && !s->isAttacking())
                                                  {
                                                      if(closestWolf == nullptr)
                                                      {
                                                          closestWolf = s;
                                                          disClosest = b2DistanceSquared(s->getPosition(), enemy->getPosition());
                                                      }
                                                      else
                                                      {
                                                          float d = b2DistanceSquared(s->getPosition(), enemy->getPosition());
                                                          if(d < disClosest)
                                                          {
                                                              disClosest = d;
                                                              closestWolf = s;
                                                          }
                                                      }
                                                  }
                                              }
                                              if(closestWolf)
                                                  closestWolf->setState(std::make_shared<AnimalAttackState>(closestWolf, enemy));

                                          }
                                      },
                                      [&](){ return true; },
                                      "Wolf Attack"
    ));
    // Bear Button
    buttons.push_back(new WordsButton(sf::IntRect({50, 415}, {200, 100}),
                                      forest,
                                      [&](Button* button) {
                                          if (!dynamic_cast<Enemy*>(forest.getScreen().getEntityClickSelection().getSelectedEntity()))
                                              return;
                                          Enemy* enemy = dynamic_cast<Enemy*>(forest.getScreen().getEntityClickSelection().getSelectedEntity());
                                          if(enemy != nullptr)
                                          {
                                              Bear* closestBear = nullptr;
                                              float disClosest = 0.f;
                                              for(Entity* e : forest.getObjects())
                                              {
                                                  Bear* s = dynamic_cast<Bear*>(e);
                                                  if(s && !s->isAttacking())
                                                  {
                                                      if(closestBear == nullptr)
                                                      {
                                                          closestBear = s;
                                                          disClosest = b2DistanceSquared(s->getPosition(), enemy->getPosition());
                                                      }
                                                      else
                                                      {
                                                          float d = b2DistanceSquared(s->getPosition(), enemy->getPosition());
                                                          if(d < disClosest)
                                                          {
                                                              disClosest = d;
                                                              closestBear = s;
                                                          }
                                                      }
                                                  }
                                              }
                                              if(closestBear)
                                                  closestBear->setState(std::make_shared<AnimalAttackState>(closestBear, enemy));

                                          }
                                      },
                                      [&](){ return true; },
                                      "Bear Attack"
    ));
}

void EnemyMenu::draw(sf::RenderTarget &target, const sf::RenderStates &states) const {
    if(!hidden)
        target.draw(enemyMenu);
    Menu::draw(target, states);
}
