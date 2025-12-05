#include "pp/shapes/brush.hpp"
#include "dr4/texture.hpp"

pp::impl::BrushShape::BrushShape( dr4::Window*             window,
                                  const pp::ControlsTheme& theme,
                                  pp::Canvas*              cvs )
    : cvs_( cvs ), brushColor_( theme.shapeBorderColor ), window_( window )
{
}

void
pp::impl::BrushShape::AddPoint( dr4::Vec2f point )
{
    points_.push_back( point );
}

void
pp::impl::BrushShape::DrawOn( dr4::Texture& texture ) const
{
    if ( points_.empty() )
        return;

    // Вариант 1: отрисовка цепочки кругов
    for ( const auto& p : points_ )
    {
        auto circle = window_->CreateCircle();
        circle->SetCenter( p );
        circle->SetRadius( BrushRadius );
        circle->SetFillColor( brushColor_ );
        circle->DrawOn( texture );
    }

    // Вариант 2 (лучше): отрисовка полилинии с толщиной
    // — если в dr4 есть линии с толщиной и сглаживанием.
    // Пока используем круги — проще и надёжнее.
}

void
pp::impl::BrushShape::SetPos( dr4::Vec2f pos )
{
    if ( points_.empty() )
        return;
    dr4::Vec2f offset = pos - points_[0];
    for ( auto& p : points_ )
        p += offset;
}

dr4::Vec2f
pp::impl::BrushShape::GetPos() const
{
    return points_.empty() ? dr4::Vec2f{ 0, 0 } : points_[0];
}
