#include <chrono>
#include <functional>
#include <iostream>
#include <utility>

namespace Time {
    template <typename Func> auto MearureTime(Func&& func) -> long {
        const auto start = std::chrono::high_resolution_clock::now();
        std::invoke(std::forward<Func>(func));
        const auto end = std::chrono::high_resolution_clock::now();

        return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    }
} // namespace Time