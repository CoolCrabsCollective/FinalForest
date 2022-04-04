//
// Created by Sir Dick on 2022-04-03.
//

#include "UI/TurretMenu.h"

#include <UI/PurchaseButton.h>
#include <GameAssets.h>
#include <UI/WordsButton.h>
#include <world/animal/state/AnimalIdleState.h>
#include <world/animal/state/SquirrelGatherState.h>
#include <world/animal/state/SquirrelReturnGatherState.h>
#include <world/animal/state/SquirrelGoGathertState.h>
#include <world/animal/state/SquirrelGoDefendTheHomelandState.h>

#include <memory>
#include "UI/AnimalMenu.h"
#include "ForestScreen.h"

TurretMenu::TurretMenu(const wiz::AssetLoader &assetLoader, Forest &forest) : Menu(assetLoader, forest) {
    buttons.push_back(
    new WordsButton(
        sf::IntRect({50, 50}, {200, 100}),
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

                            if(dynamic_pointer_cast<AnimalIdleState>(closestSquirrel->getState()).get()
                               || dynamic_pointer_cast<SquirrelGatherState>(closestSquirrel->getState()).get()
                               || dynamic_pointer_cast<SquirrelGoGatherState>(closestSquirrel->getState()).get())
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
                }
                if(closestSquirrel)
                {
                    closestSquirrel->setState(std::make_shared<SquirrelGoDefendTheHomelandState>(closestSquirrel, tree));
                    forest.unassignSquirrel(closestSquirrel);
                }
            }
        },
        "Assign Squirrel Archer"
    ));

    buttons.push_back(
    new WordsButton(
            sf::IntRect({50, 200}, {200, 100}),
            forest,
            [&](Button* button) {
                Tree* tree = forest.getScreen().getSelectedTree();
                if(tree != nullptr)
                {
                    if(tree->getSquirrelCount() > 0)
                    {
                        tree->removeSquirrelTurret();
                        forest.respawnSquirrel(tree);
                    }
                }
            },
            "Unassign Squirrel Archer"
    ));
}