#include "catch.hpp"

#include <QTest>
#include <QSignalSpy>

#include "goto_line_tool.hpp"

using namespace ScIDE;

// DO NOT USE ANY Qt Test checkers, like QVERIFY, QCOMPARE - as any test failures are currently not detected

class GoToLineToolFixture {
protected:
    GoToLineTool mGoToLineWidget;
    QSpinBox* mSpinner = nullptr;
    QToolButton* mGoButton = nullptr;
    std::unique_ptr<QSignalSpy> activatedSpy;

    GoToLineToolFixture() {
        mGoToLineWidget.raise();
        mGoToLineWidget.show();
        // TODO Maybe use QTest::qWaitForWindowExposed()
        // https://doc.qt.io/qt-5/qtest.html#qWaitForWindowExposed
        // TODO Do we need to create a QWindow first, as parent for this?
        // TODO Do we need to make sure widget has a non-null parent?

        // This is needed to may sure that text in the spinner is selected, so that
        // as we type in characters, the initial text ("1") is erased
        mGoToLineWidget.setFocus();

        mSpinner = mGoToLineWidget.findChild<QSpinBox*>();
        mGoButton = mGoToLineWidget.findChild<QToolButton*>();

        {
            INFO("This test is no longer valid: the class being test has been changed");
            REQUIRE(mSpinner != nullptr);
            REQUIRE(mGoButton != nullptr);
        }

        activatedSpy = std::unique_ptr<QSignalSpy>(new QSignalSpy(&mGoToLineWidget, SIGNAL(activated(int))));
        REQUIRE(activatedSpy->isValid());
    }

    void checkActivatedSignalValue(int expectedValue) {
        QList<QVariant> arguments = activatedSpy->takeFirst();
        QVariant argument = arguments.at(0);
        CHECK(argument.type() == QVariant::Int);
        CHECK(argument.toInt() == expectedValue);
    }
};

TEST_CASE_METHOD(GoToLineToolFixture, "GoToLineTool emits signal when Go button clicked") {
    mGoToLineWidget.setMaximum(27);

    // Type a number, one digit at a time
    QTest::keyClicks(mSpinner, "1");
    QTest::keyClicks(mSpinner, "7");

    // Check that no signals have yet been emitted:
    REQUIRE(activatedSpy->count() == 0);

    // Clicking the Go button:
    mGoButton->click();

    // Check the activated() signal was emitted only once:
    REQUIRE(activatedSpy->count() == 1);

    // And check that the signal emitted the correct value
    checkActivatedSignalValue( 17 );
}
