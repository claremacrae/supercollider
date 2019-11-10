#include "catch.hpp"

#include <QTest>
#include <QSignalSpy>

#include "goto_line_tool.hpp"

using namespace ScIDE;

// DO NOT USE ANY Qt Test checkers, like QVERIFY, QCOMPARE - as any test failures are currently not detected

TEST_CASE("GoToLineTool emits signal when Go button clicked") {
    // --------------------------------------------------------
    // Arrange
    GoToLineTool widget;
    widget.raise();
    widget.show();
    widget.setMaximum(27);

    // This is needed to make sure that text in the spinner is selected, so that
    // as we type in characters, the initial text ("1") is erased
    widget.setFocus();

    // Allow us to interact with widgets inside GoToLineTool:
    auto spinner = widget.findChild<QSpinBox*>();
    auto goButton = widget.findChild<QToolButton*>();

    {
        INFO("This test is no longer valid: the class being test has been changed");
        REQUIRE(spinner != nullptr);
        REQUIRE(goButton != nullptr);
    }

    // Enable tracking of one signal
    QSignalSpy activatedSpy(&widget, SIGNAL(activated(int)));
    REQUIRE(activatedSpy.isValid());

    // --------------------------------------------------------
    // Act
    // Type a number, one digit at a time
    QTest::keyClicks(spinner, "1");
    QTest::keyClicks(spinner, "7");

    // Clicking the Go button:
    goButton->click();

    // --------------------------------------------------------
    // Assert

    // Check the activated() signal was emitted only once:
    REQUIRE(activatedSpy.count() == 1);

    // And check that the signal emitted the new value:
    QList<QVariant> arguments = activatedSpy.takeFirst();
    const QVariant& argument = arguments.at(0);
    CHECK(argument.type() == QVariant::Int);
    CHECK(argument.toInt() == 17);
}
