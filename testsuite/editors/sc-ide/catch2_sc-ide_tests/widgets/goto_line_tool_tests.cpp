#include "catch.hpp"

#include <QTest>
#include <QSignalSpy>

#include "goto_line_tool.hpp"

using namespace ScIDE;

// DO NOT USE ANY Qt Test checkers, like QVERIFY, QCOMPARE - as any test failures are currently not detected

class GoToLineToolFixture {
private:
    GoToLineTool mGoToLineWidget;
    QSpinBox* mSpinner = nullptr;
    QToolButton* mGoButton = nullptr;
    std::unique_ptr<QSignalSpy> mActivatedSpy;

protected:
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

        mActivatedSpy = std::unique_ptr<QSignalSpy>(new QSignalSpy(&mGoToLineWidget, SIGNAL(activated(int))));
        REQUIRE(mActivatedSpy->isValid());
    }

    void setMaximumLineCount(int maxLines) {
        mGoToLineWidget.setMaximum(27);
    }

    void typeCharacterInSpinner(QChar character) {
        QTest::keyClicks(mSpinner, character);
    }

    void clickGoButton() {
        mGoButton->click();
    }

    void checkActivatedSignalCount(int expectedCount) {
        REQUIRE(mActivatedSpy->count() == expectedCount);
    }

    void checkActivatedSignalValue(int expectedValue) {
        QList<QVariant> arguments = mActivatedSpy->takeFirst();
        QVariant argument = arguments.at(0);
        CHECK(argument.type() == QVariant::Int);
        CHECK(argument.toInt() == expectedValue);
    }
};

TEST_CASE_METHOD(GoToLineToolFixture, "GoToLineTool emits signal when Go button clicked") {
    setMaximumLineCount(27);

    // Type a number, one digit at a time
    typeCharacterInSpinner('1');
    typeCharacterInSpinner('7');

    // Check that no signals have yet been emitted:
    checkActivatedSignalCount(0);

    // Clicking the Go button:
    clickGoButton();

    // Check the activated() signal was emitted only once:
    checkActivatedSignalCount(1);

    // And check that the signal emitted the correct value
    checkActivatedSignalValue( 17 );
}
