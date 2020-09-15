#pragma once

#include <type_traits>
#include <QCoreApplication>
#include <QTest>

namespace qft {

void sender(...);
}

#undef QCOMPARE
#define QCOMPARE(actual, expected) \
do {using namespace qft;\
    static_assert(std::is_same<decltype(sender()), QObject*>::value, "Cannot user QCOMPARE outside of a QObject slot");\
    if (!QTest::qCompare(actual, expected, #actual, #expected, __FILE__, __LINE__))\
        return;\
} while (false)
