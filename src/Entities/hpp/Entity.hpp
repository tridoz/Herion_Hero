#include "../../Utils/hpp/FileOpener.hpp"
#include "ECS.hpp"

#include <algorithm>

class Entity {
  protected:
    std::unordered_map<std::string, ECS::Component*> componentes;
    float delta_time;

  public:
    Entity();

    void AddComponent(const std::string& name, ECS::Component* cmp);
    void UpdateComponent(const std::string& name, ECS::Component* new_cmp);
    ECS::Component* GetComponent(const std::string& name);
    bool HasComponent(const std::string& name);
    void Draw();
    void UpdateFrame();
    void Move();
    void Resize(const ECS::Vector2D& scale);
    void Resize(const float scale);
    void SetDeltaTime( float delta );
    float GetDeltaTime() const;

    void LoadSprites(const std::string& filepath);
};
