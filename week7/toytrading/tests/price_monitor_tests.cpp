#include "headers.hpp"

#include <cstdint>
#include <functional>
#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

namespace
{
// A tiny assertion helper keeps this example dependency-free. In a larger
// project, EXPECT_EQ from GoogleTest or REQUIRE from Catch2 fills this role.
template <typename Actual, typename Expected>
void expectEqual(
    const Actual &actual,
    const Expected &expected,
    const std::string &message)
{
    if (!(actual == expected))
        throw std::runtime_error(message);
}

void expectNoAlerts(
    const std::vector<Alert> &alerts,
    const std::string &message)
{
    expectEqual(alerts.size(), std::size_t{0}, message);
}

void testWaitsUntilBothPricesAreKnown()
{
    // Arrange: each test creates fresh state so tests cannot affect each other.
    PriceMonitor monitor;
    monitor.registerPair("A-B", "A", "B", 10);

    // Act: supply only one side of the registered pair.
    const auto alerts = monitor.updatePrice("A", 100, 1);

    // Assert: a difference cannot be evaluated until both prices are known.
    expectNoAlerts(alerts, "one known price must not produce an alert");
}

void testAlertsWhenDifferenceCrossesMaximum()
{
    // Arrange: begin with a known, acceptable difference.
    PriceMonitor monitor;
    monitor.registerPair("A-B", "A", "B", 10);
    monitor.updatePrice("A", 100, 1);
    monitor.updatePrice("B", 105, 1);

    // Act: move A so the difference changes from 5 to 15.
    const auto alerts = monitor.updatePrice("A", 120, 2);

    // Assert both the event count and its meaningful output fields.
    expectEqual(alerts.size(), std::size_t{1}, "crossing must produce one alert");
    expectEqual(alerts[0].pairId, std::string{"A-B"}, "alert has wrong pair ID");
    expectEqual(alerts[0].firstProduct, std::string{"A"}, "alert has wrong first product");
    expectEqual(alerts[0].secondProduct, std::string{"B"}, "alert has wrong second product");
    expectEqual(alerts[0].difference, std::int64_t{15}, "alert has wrong difference");
}

void testAlertsWhenSecondPriceMakesPairExceeded()
{
    // Arrange: register before either product has a known price.
    PriceMonitor monitor;
    monitor.registerPair("A-B", "A", "B", 10);
    monitor.updatePrice("A", 100, 1);

    // Act: the second price makes the pair evaluable for the first time, and its
    // difference is already beyond the allowed maximum.
    const auto alerts = monitor.updatePrice("B", 120, 1);

    // Assert: the first complete, exceeded observation is an alerting transition.
    expectEqual(
        alerts.size(),
        std::size_t{1},
        "first complete exceeded pair must produce an alert");
}

void testDoesNotRepeatWhileStillExceeded()
{
    // Arrange: put the pair into its exceeded state and consume its first alert.
    PriceMonitor monitor;
    monitor.registerPair("A-B", "A", "B", 10);
    monitor.updatePrice("A", 100, 1);
    monitor.updatePrice("B", 100, 1);
    monitor.updatePrice("A", 120, 2);

    // Act: apply another valid update while the pair remains exceeded.
    const auto alerts = monitor.updatePrice("A", 125, 3);

    // Assert: alerts describe transitions, not every abnormal observation.
    expectNoAlerts(alerts, "an exceeded pair must not repeatedly alert");
}

void testAlertsAgainAfterReturningToNormal()
{
    // Arrange: cross the limit once, then return to an acceptable difference.
    PriceMonitor monitor;
    monitor.registerPair("A-B", "A", "B", 10);
    monitor.updatePrice("A", 100, 1);
    monitor.updatePrice("B", 100, 1);
    monitor.updatePrice("A", 120, 2);
    monitor.updatePrice("A", 108, 3);

    // Act: cross the limit a second time.
    const auto alerts = monitor.updatePrice("A", 120, 4);

    // Assert: returning to normal resets the transition state.
    expectEqual(alerts.size(), std::size_t{1}, "a new crossing must alert again");
}

void testIgnoresEqualAndOlderUpdateNumbers()
{
    // Arrange: establish an acceptable pair at update number 10.
    PriceMonitor monitor;
    monitor.registerPair("A-B", "A", "B", 10);
    monitor.updatePrice("A", 100, 10);
    monitor.updatePrice("B", 100, 10);

    // Act: these prices would exceed the limit, but their sequence numbers are
    // not newer than A's last accepted update.
    const auto equalAlerts = monitor.updatePrice("A", 130, 10);
    const auto olderAlerts = monitor.updatePrice("A", 130, 9);

    // Assert: rejected updates must neither change state nor create alerts.
    expectNoAlerts(equalAlerts, "an equal update number must be ignored");
    expectNoAlerts(olderAlerts, "an older update number must be ignored");
}

void testExactMaximumIsAcceptable()
{
    // Arrange.
    PriceMonitor monitor;
    monitor.registerPair("A-B", "A", "B", 10);
    monitor.updatePrice("A", 100, 1);

    // Act: first reach exactly the maximum, then exceed it by one.
    const auto atMaximum = monitor.updatePrice("B", 110, 1);
    const auto overMaximum = monitor.updatePrice("B", 111, 2);

    // Assert: the specification says "greater than," not "greater or equal."
    expectNoAlerts(atMaximum, "the exact maximum must be acceptable");
    expectEqual(overMaximum.size(), std::size_t{1}, "maximum plus one must alert");
}

void testRegistrationDoesNotAlertOrCreateDelayedAlert()
{
    // Arrange: prices are already outside the limit before registration.
    PriceMonitor monitor;
    monitor.updatePrice("A", 100, 1);
    monitor.updatePrice("B", 130, 1);

    // Act: registration returns no alerts, and the next update remains abnormal.
    monitor.registerPair("A-B", "A", "B", 10);
    const auto stillExceeded = monitor.updatePrice("A", 101, 2);

    // Assert: registration establishes the initial state without a delayed alert.
    expectNoAlerts(
        stillExceeded,
        "registration of an exceeded pair must not cause a delayed alert");
}

void testSupportsInt64Prices()
{
    // Arrange: the public API promises 64-bit prices, so exercise values larger
    // than a 32-bit int instead of testing only convenient small numbers.
    PriceMonitor monitor;
    monitor.registerPair("A-B", "A", "B", 4'000'000'000LL);
    monitor.updatePrice("A", 0, 1);

    // Act.
    const auto alerts = monitor.updatePrice("B", 5'000'000'000LL, 1);

    // Assert.
    expectEqual(alerts.size(), std::size_t{1}, "64-bit difference must produce an alert");
    expectEqual(
        alerts[0].difference,
        std::int64_t{5'000'000'000LL},
        "64-bit alert difference was truncated");
}

using TestFunction = std::function<void()>;

struct TestCase
{
    std::string name;
    TestFunction run;
};
} // namespace

int main()
{
    // A table-driven runner avoids repetitive try/catch code and ensures every
    // test reports its own name. Real test frameworks provide a richer version.
    const std::vector<TestCase> tests{
        {"waits until both prices are known", testWaitsUntilBothPricesAreKnown},
        {"alerts when difference crosses maximum", testAlertsWhenDifferenceCrossesMaximum},
        {"alerts when second price makes pair exceeded", testAlertsWhenSecondPriceMakesPairExceeded},
        {"does not repeat while exceeded", testDoesNotRepeatWhileStillExceeded},
        {"alerts again after returning to normal", testAlertsAgainAfterReturningToNormal},
        {"ignores equal and older updates", testIgnoresEqualAndOlderUpdateNumbers},
        {"treats exact maximum as acceptable", testExactMaximumIsAcceptable},
        {"registration does not create delayed alert", testRegistrationDoesNotAlertOrCreateDelayedAlert},
        {"supports 64-bit prices", testSupportsInt64Prices},
    };

    int failures = 0;

    for (const auto &test : tests)
    {
        try
        {
            test.run();
            std::cout << "[PASS] " << test.name << '\n';
        }
        catch (const std::exception &error)
        {
            ++failures;
            std::cerr << "[FAIL] " << test.name << ": " << error.what() << '\n';
        }
    }

    std::cout << '\n'
              << tests.size() - static_cast<std::size_t>(failures)
              << "/" << tests.size() << " tests passed\n";

    return failures == 0 ? 0 : 1;
}
