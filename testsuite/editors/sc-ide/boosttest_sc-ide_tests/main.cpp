#include <boost/test/unit_test.hpp>

int add(int i, int j) { return i + j; }

BOOST_AUTO_TEST_CASE(test_addition_of_integers) {
    BOOST_CHECK_EQUAL(add(2, 2), 4); // continues on error
    BOOST_REQUIRE_EQUAL(add(2, 2), 4); // throws on error
}
