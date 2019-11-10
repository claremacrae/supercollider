#include "catch.hpp"

#include <QTest>
#include <QSignalSpy>

#include "goto_line_tool.hpp"

using namespace ScIDE;

// DO NOT USE ANY Qt Test checkers, like QVERIFY, QCOMPARE - as any test failures are currently not detected

TEST_CASE("GoToLineTool emits signal when Go button clicked") {
    GoToLineTool widget;
    widget.raise();
    widget.show();
    widget.setMaximum(27);

    auto spinner = widget.findChild<QSpinBox*>();
    auto goButton = widget.findChild<QToolButton*>();

    {
        INFO("This test is no longer valid: the class being test has been changed");
        REQUIRE(spinner != nullptr);
        REQUIRE(goButton != nullptr);
    }

    // This is needed to make sure that text in the spinner is selected, so that
    // as we type in characters, the initial text ("1") is erased
    widget.setFocus();

    QSignalSpy activatedSpy(&widget, SIGNAL(activated(int)));
    REQUIRE(activatedSpy.isValid());

    // Type a number, one digit at a time
    QTest::keyClicks(spinner, "1");
    QTest::keyClicks(spinner, "7");

    // Check that no signals have yet been emitted:
    REQUIRE(activatedSpy.count() == 0);

    // Clicking the Go button:
    goButton->click();

    // Check the activated() signal was emitted only once:
    REQUIRE(activatedSpy.count() == 1);

    // And check that the signal emitted the correct value
    QList<QVariant> arguments = activatedSpy.takeFirst();
    QVariant argument = arguments.at(0);
    CHECK(argument.type() == QVariant::Int);
    CHECK(argument.toInt() == 17);
}
