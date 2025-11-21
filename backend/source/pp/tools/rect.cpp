#include <cassert>
#include <cmath>
#include <iostream>
#include <limits>

#include "pp/shapes/rect.hpp"
#include "pp/tools/rect.hpp"

pp::impl::RectTool::RectTool( ::pp::Canvas* cvs )
    : cvs_{ cvs },
      isDrawing_( false ),
      rect_{ nullptr },
      state_{ cvs->GetState() },
      rectInd_( std::numeric_limits<size_t>::max() )
{
}

std::string_view
pp::impl::RectTool::Icon() const
{
    return "RectToolIcon";
}

std::string_view
pp::impl::RectTool::Name() const
{
    return "RectTool";
}

bool
pp::impl::RectTool::IsCurrentlyDrawing() const
{
    return isDrawing_;
}

void
pp::impl::RectTool::OnStart()
{
    if ( state_->selectedTool != nullptr )
    {
        state_->selectedTool->OnEnd();
    }
    state_->selectedTool = this;
}

void
pp::impl::RectTool::OnBreak()
{
    if ( isDrawing_ )
    {
        assert( rect_ );
        cvs_->DelShape( rectInd_ );

        if ( state_->selectedShape == rect_ )
        {
            state_->selectedShape = nullptr;
        }

        rect_      = nullptr;
        isDrawing_ = false;
    }
}

void
pp::impl::RectTool::OnEnd()
{
    if ( isDrawing_ )
    {
        isDrawing_ = false;
        rect_->OnSelect();
    }
}

bool
pp::impl::RectTool::OnMouseDown( const dr4::Event::MouseButton& evt )
{
    if ( !isDrawing_ )
    {
        isDrawing_ = true;

        rect_ = new pp::impl::Rect( cvs_->GetWindow(), cvs_->GetControlsTheme(), cvs_->GetState() );
        rectInd_ = cvs_->AddShape( rect_ );
        rect_->SetPos( evt.pos );
        return true;
    } else
    {
        isDrawing_ = false;
        rect_->OnSelect();
        return true;
    }

    return false;
}

bool
pp::impl::RectTool::OnMouseUp( const dr4::Event::MouseButton& evt )
{
    return false;
}

bool
pp::impl::RectTool::OnMouseMove( const dr4::Event::MouseMove& evt )
{
    if ( !isDrawing_ )
    {
        return false;
    }

    assert( rect_ );

    rect_->SetSize( evt.pos - rect_->GetPos() );

    return true;
}
