//
// Created by Alexander Winter🤤 on 2022-02-13.
//

#ifndef GAMETEMPLATE_GAMEASSETS_H
#define GAMETEMPLATE_GAMEASSETS_H

#include "WIZ/asset/MusicAsset.h"
#include "WIZ/asset/SoundAsset.h"
#include "WIZ/asset/FontAsset.h"
#include "WIZ/asset/TextureAsset.h"

#ifndef ASSET
#define ASSET(TYPE, NAME, CONSTRUCTOR) extern const TYPE NAME;
#endif

namespace GameAssets {
	extern std::vector<const wiz::AssetBase*> ALL;

	ASSET(wiz::MusicAsset, NUTLIFE, ("music/nutlife.ogg"))

	ASSET(wiz::SoundAsset, GAMEOVER, ("sfx/gameover.ogg"))
	ASSET(wiz::SoundAsset, WAVE_CLEARED, ("sfx/wave_cleared.ogg"))
	ASSET(wiz::SoundAsset, WAVE_START, ("sfx/wave_start.ogg"))

	ASSET(wiz::SoundAsset, AXE_TREE1, ("sfx/axe_tree1.ogg"))
	ASSET(wiz::SoundAsset, AXE_TREE2, ("sfx/axe_tree2.ogg"))
	ASSET(wiz::SoundAsset, AXE_TREE3, ("sfx/axe_tree2.ogg"))

	ASSET(wiz::FontAsset, DEFAULT_FONT, ("font/pixellari.ttf"))

	ASSET(wiz::TextureAsset, WHITE_PIXEL, ("gfx/white_pixel.png"))
	ASSET(wiz::TextureAsset, LOGO, ("gfx/logo.png"))
    ASSET(wiz::TextureAsset, NUT, ("gfx/nut.png"))

    ASSET(wiz::TextureAsset, TREE, ("gfx/tree.png"))
    ASSET(wiz::TextureAsset, WHITE_TREE, ("gfx/tree_white.png"))
    ASSET(wiz::TextureAsset, TREE_STUMP, ("gfx/tree_stump.png"))
    ASSET(wiz::TextureAsset, TREE_TURRET, ("gfx/tree_turret.png"))
    ASSET(wiz::TextureAsset, MANA, ("gfx/mana.png"))
    ASSET(wiz::TextureAsset, LUMBERJACKAXE, ("gfx/lumber_jack_axe.png"))
    ASSET(wiz::TextureAsset, LUMBERJACKAXE_SWING, ("gfx/lumber_jack_axe_swing.png"))
    ASSET(wiz::TextureAsset, LUMBERJACKCHAINSAW, ("gfx/lumber_jack_chainsaw.png"))
    ASSET(wiz::TextureAsset, WHITE_LUMBERJACK, ("gfx/white_lumber_jack.png"))
    ASSET(wiz::TextureAsset, GREAT_OAK, ("gfx/great_oak.png"))
    ASSET(wiz::TextureAsset, WHITE_GREAT_OAK, ("gfx/great_oak_white.png"))
    ASSET(wiz::TextureAsset, GREAT_OAK_STUMP, ("gfx/great_oak_stump.png"))

    ASSET(wiz::TextureAsset, SQUIRREL, ("gfx/squirrel.png"))
    ASSET(wiz::TextureAsset, SQUIRREL_WITH_NUT, ("gfx/squirrel_with_nut.png"))
    ASSET(wiz::TextureAsset, SQUIRREL_IDLE, ("gfx/squirrel_idle.png"))
    ASSET(wiz::TextureAsset, SQUIRREL_ARMORED, ("gfx/squirrel_armored.png"))

	ASSET(wiz::TextureAsset, BULLDOZER, ("gfx/bulldozer.png"))

    ASSET(wiz::TextureAsset, WOLF, ("gfx/wolf.png"))

    ASSET(wiz::TextureAsset, BEAR, ("gfx/bear.png"))

	ASSET(wiz::TextureAsset, RIVER_JOINT, ("gfx/river/river_joint.png"))
	ASSET(wiz::TextureAsset, RIVER_LINE, ("gfx/river/river_line.png"))
	ASSET(wiz::TextureAsset, MAGIC_LAKE, ("gfx/great_lake.png"))

	ASSET(wiz::TextureAsset, WOOD_BRIDGE, ("gfx/bridge/wood.png"))
	ASSET(wiz::TextureAsset, METAL_BRIDGE, ("gfx/bridge/metal.png"))

    ASSET(wiz::TextureAsset, ANIMAL_MENU, ("gfx/animal_menu.png"))

	ASSET(wiz::TextureAsset, GRASS, ("gfx/grass.png"))


}


#endif //GAMETEMPLATE_GAMEASSETS_H
