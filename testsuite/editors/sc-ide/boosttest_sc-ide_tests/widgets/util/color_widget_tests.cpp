#include <boost/test/unit_test.hpp>

#include <QApplication>

#include "color_widget.hpp"

#include "boosttest_qt_string_makers.hpp"

using namespace ScIDE;

// TODO Consider adding tags for tests
BOOST_AUTO_TEST_CASE(ColorWidget_initial_state) {
    char  arg0[] = "programName";
    char* argv[] = { &arg0[0], NULL };
    int   argc   = (int)(sizeof(argv) / sizeof(argv[0])) - 1;

    QApplication the_application(argc, &argv[0]);

    ColorWidget widget;
    QColor expected_color(0, 0, 0, 255);
    BOOST_CHECK_EQUAL(widget.color(), expected_color);
}

BOOST_AUTO_TEST_CASE(ColorWidget_changing_color_updates_and_emits_correctly) {
    // Arrange
    char  arg0[] = "programName";
    char* argv[] = { &arg0[0], NULL };
    int   argc   = (int)(sizeof(argv) / sizeof(argv[0])) - 1;

    QApplication the_application(argc, &argv[0]);

    ColorWidget widget;
    QColor red("red");

    // Act
    widget.setColor(red);

    // Assert
    BOOST_CHECK_EQUAL(widget.color(), red);
    // TODO Check that signals are emitted correctly, and only once
}
