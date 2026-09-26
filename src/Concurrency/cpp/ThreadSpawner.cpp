#include "../hpp/ThreadSpawner.hpp"

auto ThreadSpawner::Spawn(std::function<void()> func) -> std::thread {
    std::thread t(std::move(func));
    return t;
}
