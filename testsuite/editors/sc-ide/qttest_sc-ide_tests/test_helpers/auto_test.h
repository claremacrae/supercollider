#pragma once

#include <QTest>
#include <QList>
#include <QString>
#include <QSharedPointer>
#include <QApplication>

/*! \brief Mechanism to allow multiple Qt Test classes to be run from a single main()
 *
 * It allows QObject-based tests to be called from a single main, simply
 * by adding this after each of the QObject-based tests:
 *     <tt>DECLARE_TEST(<whatever the QObject class name is>)</tt>
 *
 * Credit: http://qtcreator.blogspot.com/2009/10/running-multiple-unit-tests.html
 */
namespace AutoTest {
typedef QList<QObject*> TestList;

inline TestList& testList() {
    static TestList list;
    return list;
}

inline bool findObject(QObject* object) {
    TestList& list = testList();
    if (list.contains(object)) {
        return true;
    }
    foreach (QObject* test, list) {
        if (test->objectName() == object->objectName()) {
            return true;
        }
    }
    return false;
}

inline void addTest(QObject* object) {
    TestList& list = testList();
    if (!findObject(object)) {
        list.append(object);
    }
}

inline int run(int argc, char* argv[]) {
    int ret = 0;

    foreach (QObject* test, testList()) { ret += QTest::qExec(test, argc, argv); }

    return ret;
}
}

template <class T> class Test {
public:
    QSharedPointer<T> child;

    Test(const QString& name): child(new T) {
        child->setObjectName(name);
        AutoTest::addTest(child.data());
    }
};

#define DECLARE_TEST(className) static Test<className> t(#className);

#define TEST_MAIN                                                                                                      \
    int main(int argc, char* argv[]) {                                                                                 \
        QApplication app(argc, argv);                                                                                  \
        return AutoTest::run(argc, argv);                                                                              \
    }
