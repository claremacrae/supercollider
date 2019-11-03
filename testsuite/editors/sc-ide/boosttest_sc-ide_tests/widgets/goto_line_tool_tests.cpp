#include <boost/test/unit_test.hpp>

#include <QTest>
#include <QSignalSpy>

#include "goto_line_tool.hpp"

using namespace ScIDE;

// DO NOT USE ANY Qt Test checkers, like QVERIFY, QCOMPARE - as any test failures are currently not detected

BOOST_AUTO_TEST_CASE(GoToLineTool_emits_signal_when_Go_button_clicked) {
    GoToLineTool widget;
    widget.raise();
    widget.show();
    // TODO Maybe use QTest::qWaitForWindowExposed()
    // https://doc.qt.io/qt-5/qtest.html#qWaitForWindowExposed
    // TODO Do we need to create a QWindow first, as parent for this?
    // TODO Do we need to make sure widget has a non-null parent?
    widget.setMaximum(27);

    auto spinner = widget.findChild<QSpinBox*>();
    auto goButton = widget.findChild<QToolButton*>();

    {
        const auto error_message = "This test is no longer valid: the class being test has been changed";
        if (!spinner)
            BOOST_FAIL(error_message);
        if (!goButton)
            BOOST_FAIL(error_message);
    }

    // This is needed to may sure that text in the spinner is selected, so that
    // as we type in characters, the initial text ("1") is erased
    widget.setFocus();

    QSignalSpy activatedSpy(&widget, SIGNAL(activated(int)));
    BOOST_REQUIRE(activatedSpy.isValid());

    // Type a number, one digit at a time
    QTest::keyClicks(spinner, "1");
    QTest::keyClicks(spinner, "7");

    // Check that no signals have yet been emitted:
    BOOST_REQUIRE_EQUAL(activatedSpy.count(), 0);

    // Clicking the Go button:
    goButton->click();

    // Check the activated() signal was emitted only once:
    BOOST_REQUIRE_EQUAL(activatedSpy.count(), 1);

    // And check that the signal emitted the correct value
    QList<QVariant> arguments = activatedSpy.takeFirst();
    QVariant argument = arguments.at(0);
    BOOST_CHECK_EQUAL(argument.type(), QVariant::Int);
    BOOST_CHECK_EQUAL(argument.toInt(), 17);
}
