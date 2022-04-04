//
// Created by Cedric on 2022-04-03.
//

#ifndef LD50_CLIENT_TEXTBUTTON_H
#define LD50_CLIENT_TEXTBUTTON_H

#include "UI/Button.h"
#include "SFML/Graphics/Text.hpp"

class WordsButton : public Button {
private:
    sf::Text lblText;
    std::function<bool(void)> isEnabled;
public:
    WordsButton(sf::IntRect rectangle, Forest &forest, std::function<void(Button *)> onClick, std::function<bool(void)> isEnabled,
            std::string str);

    void draw(sf::RenderTarget &target, const sf::RenderStates &states) const override;

    void tick(float delta) override;

protected:
    void click() override;
};


#endif //LD50_CLIENT_TEXTBUTTON_H
