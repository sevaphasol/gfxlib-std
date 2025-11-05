#include "dr4/font_impl.hpp"
#include "dr4/texture.hpp"
#include <SFML/Graphics/Text.hpp>

dr4::Rect2f
dr4::Text::GetBounds() const
{
    sf::Text sf_text;

    const dr4::impl::Font& my_font = dynamic_cast<const dr4::impl::Font&>( *font );

    sf_text.setFont( my_font.impl_ );
    sf_text.setString( text );
    sf_text.setCharacterSize( fontSize );

    auto bounds = sf_text.getLocalBounds();

    return { bounds.left, bounds.top, bounds.width, bounds.height };
}
