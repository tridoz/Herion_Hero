#include "../../Utils/hpp/FileOpener.hpp"
#include "ECS.hpp"

#include <algorithm>
#include <typeindex>

class Entity {
  protected:
    std::unordered_map<std::type_index, ECS::Components::Component*> componentes;
    float delta_time;

  public:
    Entity();

    template <typename T> auto AddComponent(ECS::Components::Component* cmp) -> void {
        std::type_index index(typeid(T));
        if (this->componentes.contains(index))
            return;

        this->componentes.emplace(index, cmp);
    }

    template <typename T> auto UpdateComponent(ECS::Components::Component* cmp) -> void {
        std::type_index index(typeid(T));
        if (!this->componentes.contains(index))
            return;

        this->componentes[index] = cmp;
    }

    template <typename T> auto GetComponent() -> T* {
        std::type_index index = typeid(T);
        if (this->componentes.contains(index))
            return static_cast<T*>(this->componentes.at(index));

        return nullptr;
    }

    template <typename T> auto HasComponent() -> bool {
        std::type_index index(typeid(T));
        return this->componentes.contains(index);
    }
    auto Draw() -> void;
    auto UpdateFrame() -> void;
    auto Move() -> void;
    auto Resize(const ECS::Components::Vector2D&) -> void;
    auto Resize(const float) -> void;
    auto SetDeltaTime(float) -> void;
    auto GetDeltaTime() const -> float;

    auto LoadSprites(const std::string&) -> void;
};
