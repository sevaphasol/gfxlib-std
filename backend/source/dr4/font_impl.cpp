#include "dr4/font_impl.hpp"

namespace dr4 {
namespace impl {

void
dr4::impl::Font::loadFromFile( const std::string& path )
{
    impl_.loadFromFile( path );
}

} // namespace impl
} // namespace dr4
