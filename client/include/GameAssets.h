//
// Created by Alexander Winter on 2022-02-13.
//

#ifndef GAMETEMPLATE_GAMEASSETS_H
#define GAMETEMPLATE_GAMEASSETS_H

#include "WIZ/asset/MusicAsset.h"
#include "WIZ/asset/SoundAsset.h"
#include "WIZ/asset/FontAsset.h"
#include "WIZ/asset/TextureAsset.h"
#include "FakeAsset.h"

#ifndef ASSET
#define ASSET(TYPE, NAME, CONSTRUCTOR) extern const TYPE NAME;
#endif

namespace GameAssets {
	extern std::vector<const wiz::AssetBase*> ALL;

	ASSET(wiz::MusicAsset, GREENLIFE, ("music/greenlife.ogg"))
	ASSET(wiz::SoundAsset, JUMP, ("sfx/jump.ogg"))
	ASSET(wiz::FontAsset, SANS_TTF, ("font/sans.ttf"))

	ASSET(wiz::TextureAsset, PLAYER, ("gfx/player.png"))
	ASSET(wiz::TextureAsset, BACKGROUND, ("gfx/background.jpg"))
	ASSET(wiz::TextureAsset, WHITE_PIXEL, ("gfx/white_pixel.png"))
	ASSET(wiz::TextureAsset, LOGO, ("gfx/logo.png"))
    ASSET(wiz::TextureAsset, NUT, ("gfx/nut.png"))
    ASSET(wiz::TextureAsset, SQUIRREL, ("gfx/squirrel.png"))
    ASSET(wiz::TextureAsset, TREE, ("gfx/tree.png"))
    ASSET(wiz::TextureAsset, MANA, ("gfx/mana.png"))
    ASSET(wiz::TextureAsset, WOODCUTTER, ("gfx/woodcutter.png"))
    ASSET(wiz::TextureAsset, GREAT_OAK, ("gfx/great_oak.png"))

    ASSET(wiz::TextureAsset, GRASS1, ("gfx/grass/grass1.png"))
    ASSET(wiz::TextureAsset, GRASS2, ("gfx/grass/grass2.png"))
    ASSET(wiz::TextureAsset, GRASS3, ("gfx/grass/grass3.png"))
    ASSET(wiz::TextureAsset, GRASS4, ("gfx/grass/grass4.png"))


}


#endif //GAMETEMPLATE_GAMEASSETS_H
