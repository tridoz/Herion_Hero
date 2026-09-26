#pragma once

#include <functional>
#include <thread>

class ThreadSpawner {
  public:
    static auto Spawn(std::function<void()>) -> std::thread;
};
