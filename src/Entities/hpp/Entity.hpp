#include "ECS.hpp"
#include "../../Utils/hpp/FileOpener.hpp"


class Entity {
    protected:
        std::unordered_map<std::string, ECS::Component* > componentes;

    public:
        Entity();

        void AddComponent( const std::string& name, ECS::Component* cmp );
        void UpdateComponent( const std::string& name, ECS::Component* new_cmp );
        ECS::Component* GetComponent( const std::string& name );
        bool HasComponent( const std::string& name );
        void Draw( SDL_Renderer* renderer );
        void Move();
        void Resize( const ECS::Vector2D& scale );
        void Resize( const float scale );

        void LoadSprites( const std::string& filepath );

};
