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

    template <typename T> void AddComponent(ECS::Components::Component* cmp) {
        std::type_index index(typeid(T));
        if (this->componentes.contains(index))
            return;

        this->componentes.emplace(index, cmp);
    }

    template <typename T> void UpdateComponent(ECS::Components::Component* cmp) {
        std::type_index index(typeid(T));
        if (!this->componentes.contains(index))
            return;

        this->componentes[index] = cmp;
    }

    template <typename T> T* GetComponent() {
        std::type_index index = typeid(T);
        if (this->componentes.contains(index))
            return static_cast<T*>(this->componentes.at(index));

        return nullptr;
    }

    template <typename T> bool HasComponent() {
        std::type_index index(typeid(T));
        return this->componentes.contains(index);
    }
    void Draw();
    void UpdateFrame();
    void Move();
    void Resize(const ECS::Components::Vector2D& scale);
    void Resize(const float scale);
    void SetDeltaTime(float delta);
    float GetDeltaTime() const;

    void LoadSprites(const std::string& filepath);
};
