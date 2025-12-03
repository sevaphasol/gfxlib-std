#pragma once

#include <memory>
#include <stack>

#include "dr4/event.hpp"
#include "dr4/math/vec2.hpp"
#include "dr4/texture.hpp"
#include "dr4/window.hpp"

#include "pp/canvas.hpp"
#include "pp/shape.hpp"

namespace pp {
namespace impl {

class TextTool;

class Text final : public pp::Shape {
  public:
    Text( dr4::Window* window, const pp::ControlsTheme& theme, pp::Canvas* cvs );

    bool
    OnMouseDown( const dr4::Event::MouseButton& evt ) override final;
    bool
    OnMouseUp( const dr4::Event::MouseButton& evt ) override final;
    bool
    OnMouseMove( const dr4::Event::MouseMove& evt ) override final;
    bool
    OnKeyDown( const dr4::Event::KeyEvent& evt ) override final;
    virtual bool
    OnText( const dr4::Event::TextEvent& evt ) override final;

    void
    OnSelect() override final;
    void
    OnDeselect() override final;

    void
    DrawOn( dr4::Texture& texture ) const override final;

    void
    SetPos( dr4::Vec2f pos ) override final;
    dr4::Vec2f
    GetPos() const override final;

    void
    SetIsDrawing( bool state );

  private:
    void
    refreshCursor();
    bool
    textContains( dr4::Vec2f rel ) const;

    void
    put( char c );

    void
    arrows( dr4::Event::KeyEvent evt );

    void
    home();
    void
    end();
    void
    shiftHome();
    void
    shiftEnd();

    void
    backspace();
    void
    ctrlBackspace();
    void
    del();
    void
    ctrlDel();

    void
    ctrlX();
    void
    ctrlC();
    void
    ctrlV();
    void
    ctrlA();
    void
    ctrlW();
    void
    ctrlS();
    void
    ctrlZ();
    void
    ctrlShiftZ();

    void
    decrementCursor();
    void
    incrementCursor();
    void
    moveCursorWordLeft();
    void
    moveCursorWordRight();

    bool
    onMe( dr4::Vec2f rel ) const;

    void
    updateRect();

    void
    insertCursor( dr4::Vec2f pos );
    float
    getCursorX() const;

    std::pair<size_t, size_t>
    getSelectionRange() const;

    std::string
    copySelected() const;
    void
    pasteFromClipboard();
    void
    eraseSelected();

    size_t
    getLeftWordPos();
    size_t
    getRightWordPos();

    bool
    hasSelection() const;
    void
    clearSelection();

    void
    selectWordAtCursor();
    void
    selectString();

    void
    handleTextClick( const dr4::Event::MouseButton& evt );

    bool
    OnKeyDownReadOnly( const dr4::Event::KeyEvent& evt );

  private:
    static constexpr float RectBorderThickness = 2.0f;
    static constexpr float RectMarginX         = 10.0f;
    static constexpr float RectMarginY         = 10.0f;

    std::string         string_;
    mutable std::string tmp_string_;

    std::unique_ptr<dr4::Text>      text_;
    std::unique_ptr<dr4::Rectangle> rect_;

    pp::Canvas* cvs_ = nullptr;

    std::unique_ptr<dr4::Rectangle> cursor_;

    double         cursor_blink_period_    = 0.5;
    mutable double cursor_last_blink_time_ = 0.0;
    mutable bool   cursor_visible_         = false;
    size_t         cursor_pos_             = 0;

    size_t                          selection_pos_    = 0;
    bool                            selection_active_ = false;
    bool                            is_selecting_     = false;
    std::unique_ptr<dr4::Rectangle> selection_rect_;

    bool is_drawing_ = false;
    bool is_dragged_ = false;

    float ascent_;
    float descent_;

    std::stack<std::tuple<std::string, size_t>> undo_stack_;
    std::stack<std::tuple<std::string, size_t>> redo_stack_;

    double     last_click_time_ = 0.0;
    dr4::Vec2f last_click_pos_  = { 0, 0 };
    size_t     click_count_     = 0;

    static constexpr double DoubleClickTime    = 0.45;
    static constexpr float  ClickMoveThreshold = 6.0f;
};

} // namespace impl
} // namespace pp
