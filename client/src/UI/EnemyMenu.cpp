//
// Created by william on 2022-04-03.
//

#include <UI/WordsButton.h>
#include <GameAssets.h>
#include "UI/EnemyMenu.h"
#include "ForestScreen.h"
#include "world/tree/BigAssTree.h"
#include "world/animal/state/AnimalGoAttackState.h"
#include "world/animal/Wolf.h"
#include "world/animal/Bear.h"

EnemyMenu::EnemyMenu(const wiz::AssetLoader &assetLoader, Forest &forest) : Menu(assetLoader, forest) {
    // Squirrel Button
    buttons.push_back(new WordsButton(sf::IntRect({50, 50}, {200, 100}),
                                      forest,
                                      [&](Button* button) {
                                          Enemy* enemy = forest.getScreen().getSelectedEnemy();
                                          if(enemy != nullptr)
                                          {
                                              Squirrel* closestSquirrel = nullptr;
                                              float disClosest = 0.f;
                                              for(Entity* e : forest.getObjects())
                                              {
                                                  Squirrel* s = dynamic_cast<Squirrel*>(e);
                                                  if(s)
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
                                                  closestSquirrel->setState(std::make_shared<AnimalGoAttackState>(closestSquirrel, enemy));

                                          }
                                      },
                                      "Squirrel Attack"
    ));
    // Wolf Button
    buttons.push_back(new WordsButton(sf::IntRect({50, 50}, {200, 100}),
                                      forest,
                                      [&](Button* button) {
                                          Enemy* enemy = forest.getScreen().getSelectedEnemy();
                                          if(enemy != nullptr)
                                          {
                                              Wolf* closestWolf = nullptr;
                                              float disClosest = 0.f;
                                              for(Entity* e : forest.getObjects())
                                              {
                                                  Wolf* s = dynamic_cast<Wolf*>(e);
                                                  if(s)
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
                                                  closestWolf->setState(std::make_shared<AnimalGoAttackState>(closestWolf, enemy));

                                          }
                                      },
                                      "Wolf Attack"
    ));
    // Bear Button
    buttons.push_back(new WordsButton(sf::IntRect({50, 50}, {200, 100}),
                                      forest,
                                      [&](Button* button) {
                                          Enemy* enemy = forest.getScreen().getSelectedEnemy();
                                          if(enemy != nullptr)
                                          {
                                              Bear* closestBear = nullptr;
                                              float disClosest = 0.f;
                                              for(Entity* e : forest.getObjects())
                                              {
                                                  Bear* s = dynamic_cast<Bear*>(e);
                                                  if(s)
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
                                                  closestBear->setState(std::make_shared<AnimalGoAttackState>(closestBear, enemy));

                                          }
                                      },
                                      "Bear Attack"
    ));
}
