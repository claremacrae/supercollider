#include "catch.hpp"

// TODO Could move this test to a sub-directory widgets/util, as number of tests grows
#include "widgets/util/color_widget.hpp"

using namespace ScIDE;

// TODO Consider adding tags for tests
TEST_CASE("ColorWidget initial state") {
    ColorWidget widget;
    // TODO Introduce a way to pretty-print QColor for nicer test output, to save having to call .name()
    QColor expected_color;
    CHECK(widget.color().name().toStdString() == expected_color.name().toStdString());
    CHECK(widget.color().alpha() == expected_color.alpha());
}

TEST_CASE("ColorWidget changing color updates and emits correctly") {
    ColorWidget widget;
    QColor red("red");
    CHECK(widget.color().name().toStdString() == red.name().toStdString());
    CHECK(widget.color().alpha() == red.alpha());
    // TODO Check that signals are emitted correctly, and only once
}
