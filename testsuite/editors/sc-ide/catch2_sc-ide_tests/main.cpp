#define CATCH_CONFIG_RUNNER
#include "catch.hpp"

#include <QApplication>

// For explanation of Catch code, see https://github.com/catchorg/Catch2/blob/master/docs/own-main.md
int main(int argc, char* argv[]) {
    Catch::Session session;

    int returnCode = session.applyCommandLine(argc, argv);
    if (returnCode != 0) // Indicates a command line error
        return returnCode;

    // Set up exactly one QApplication, so we can create QWidgets in tests
    QApplication app(argc, argv);

    return session.run();
}
