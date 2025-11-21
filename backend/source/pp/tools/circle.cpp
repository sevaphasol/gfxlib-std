#include <cassert>
#include <cmath>
#include <limits>

#include "pp/shapes/circle.hpp"
#include "pp/tools/circle.hpp"

pp::impl::CircleTool::CircleTool( ::pp::Canvas* cvs )
    : cvs_{ cvs },
      is_drawing_( false ),
      circle_{ nullptr },
      state_{ cvs->GetState() },
      circle_ind_( std::numeric_limits<size_t>::max() )
{
}

std::string_view
pp::impl::CircleTool::Icon() const
{
    return "CircleToolIcon";
}

std::string_view
pp::impl::CircleTool::Name() const
{
    return "CircleTool";
}

bool
pp::impl::CircleTool::IsCurrentlyDrawing() const
{
    return is_drawing_;
}

void
pp::impl::CircleTool::OnStart()
{
    if ( state_->selectedTool != nullptr )
    {
        state_->selectedTool->OnEnd();
    }
    state_->selectedTool = this;
}

void
pp::impl::CircleTool::OnBreak()
{
    if ( is_drawing_ )
    {
        assert( circle_ );
        cvs_->DelShape( circle_ind_ );

        if ( state_->selectedShape == circle_ )
        {
            state_->selectedShape = nullptr;
        }

        circle_     = nullptr;
        is_drawing_ = false;
    }
}

void
pp::impl::CircleTool::OnEnd()
{
    if ( is_drawing_ )
    {
        is_drawing_ = false;
        circle_->OnSelect();
    }
}

bool
pp::impl::CircleTool::OnMouseDown( const dr4::Event::MouseButton& evt )
{
    if ( !is_drawing_ )
    {
        is_drawing_ = true;

        circle_ =
            new pp::impl::Circle( cvs_->GetWindow(), cvs_->GetControlsTheme(), cvs_->GetState() );
        circle_ind_ = cvs_->AddShape( circle_ );
        circle_->SetPos( evt.pos );
        return true;
    }

    is_drawing_ = false;
    circle_->OnSelect();
    return true;
}

bool
pp::impl::CircleTool::OnMouseUp( const dr4::Event::MouseButton& evt )
{
    return false;
}

bool
pp::impl::CircleTool::OnMouseMove( const dr4::Event::MouseMove& evt )
{
    if ( !is_drawing_ )
    {
        return false;
    }

    assert( circle_ );

    auto delta = evt.pos - circle_->GetPos();

    circle_->SetSize( { delta.x / 2, delta.y / 2 } );

    return true;
}
