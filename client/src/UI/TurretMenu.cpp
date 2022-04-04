//
// Created by cedric on 2022-04-03.
//

#include "UI/TurretMenu.h"

#include <UI/PurchaseButton.h>
#include <GameAssets.h>
#include <UI/WordsButton.h>
#include "UI/AnimalMenu.h"
#include "ForestScreen.h"

TurretMenu::TurretMenu(const wiz::AssetLoader &assetLoader, Forest &forest) : Menu(assetLoader, forest) {

    buttons.push_back(new WordsButton(sf::IntRect({50, 50}, {200, 100}),
                                      forest,
                                      [&](Button* button) {
                                          Tree* tree = forest.getScreen().getSelectedTree();
                                          if(tree != nullptr)
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
                                                          disClosest = b2DistanceSquared(s->getPosition(), tree->getPosition());
                                                      }
                                                      else
                                                      {
                                                          float d = b2DistanceSquared(s->getPosition(), tree->getPosition());
                                                          if(d < disClosest)
                                                          {
                                                               disClosest = d;
                                                               closestSquirrel = s;
                                                          }
                                                      }
                                                  }
                                              }
                                              if(closestSquirrel)
                                                tree->addSquirrelTurret(closestSquirrel);

                                          }
                                      },
                                      "Assign Squirrel Archer"
                                      ));

    buttons.push_back(new WordsButton(sf::IntRect({50, 200}, {200, 100}),
                                      forest,
                                      [&](Button* button) {
                                          PurchaseButton* iconButton = dynamic_cast<PurchaseButton*>(button);
                                          // TODO: UNASSIGN SQUIRREL
                                      },
                                      "Unassign Squirrel Archer"
    ));
}