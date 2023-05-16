#pragma once
#include <chrono>
#include <cstdint>
#include <thread>

struct Timer {
    using clock = std::chrono::steady_clock;
    using nano_t = std::chrono::nanoseconds;
    using timepoint = std::chrono::time_point<clock, nano_t>;

    explicit Timer() noexcept {
        start();
    }

    void start() noexcept { m_start = clock::now(); }

    uint64_t ellapsed() noexcept {
        auto ns_passed { clock::now() - m_start };
        return ns_passed.count();
    }

    double ellapsed_secs() { return ellapsed() / 1000000000.0f; }

    void waitUntil_ns(uint64_t to_ns) {
        std::this_thread::sleep_for(std::chrono::milliseconds(to_ns));
    }

    template < typename CALLABLE_t >
    uint64_t timedCall( CALLABLE_t func ) {
        start();
        func();
        return ellapsed();
    }

private:
    timepoint m_start;
};