#pragma once

#include "dr4/texture.hpp"
#include <SFML/Graphics/Font.hpp>

namespace dr4 {
namespace impl {

class Font : public dr4::Font {
    friend Texture;
    friend Text;

  public:
    virtual ~Font() = default;

    virtual void
    loadFromFile( const std::string& path ) override final;

  private:
    sf::Font impl_;
};

} // namespace impl
} // namespace dr4
