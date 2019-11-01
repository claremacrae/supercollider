#include "catch.hpp"

// TODO Could move this test to a sub-directory widgets/util, as number of tests grows
#include "widgets/util/color_widget.hpp"

using namespace ScIDE;

TEST_CASE("ColorWidget shows without crashing") {
    ColorWidget widget;
    widget.show();
    widget.raise();
}
