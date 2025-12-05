#include "dr4/img_impl.hpp"
#include "dr4/texture_impl.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

void
dr4::impl::Image::SetPixel( size_t x, size_t y, dr4::Color color )
{
    impl_.setPixel( x, y, sf::Color{ color.r, color.g, color.b, color.a } );
}

dr4::Color
dr4::impl::Image::GetPixel( size_t x, size_t y ) const
{
    const auto& c = impl_.getPixel( x, y );
    return { c.r, c.g, c.b, c.a };
}

void
dr4::impl::Image::SetSize( dr4::Vec2f size )
{
    w_ = size.x;
    h_ = size.y;
    impl_.create( w_, h_ );
}

dr4::Vec2f
dr4::impl::Image::GetSize() const
{
    return { w_, h_ };
}

float
dr4::impl::Image::GetWidth() const
{
    return w_;
}

float
dr4::impl::Image::GetHeight() const
{
    return h_;
}

void
dr4::impl::Image::DrawOn( dr4::Texture& texture ) const
{
    auto& my_texture = dynamic_cast<dr4::impl::Texture&>( texture );

    sf::Texture temp_sf_texture;
    if ( !temp_sf_texture.create( w_, h_ ) )
    {
        return;
    }
    temp_sf_texture.update( impl_ );

    sf::Sprite sprite( temp_sf_texture );
    auto       tex_zero = my_texture.GetZero();
    sprite.setPosition( x_ + tex_zero.x, y_ + tex_zero.y );

    my_texture.GetImpl().draw( sprite );
}

void
dr4::impl::Image::SetPos( Vec2f pos )
{
    x_ = pos.x;
    y_ = pos.y;
}

dr4::Vec2f
dr4::impl::Image::GetPos() const
{
    return { x_, y_ };
}

void
dr4::impl::Image::SetRawImage( const sf::Image& img )
{
    auto sf_size = img.getSize();

    impl_ = img;
    w_    = static_cast<float>( sf_size.x );
    h_    = static_cast<float>( sf_size.y );
}
