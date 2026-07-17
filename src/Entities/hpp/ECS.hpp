#include "../../Textures/hpp/Texture.hpp"
#include "../../Textures/hpp/TextureManager.hpp"
#include "../../Utils/hpp/JSONParser.hpp"

#include <cstdint>
#include <unordered_map>

namespace ECS {

    namespace states {
        enum class FacingDirection : std::uint8_t { RIGHT, LEFT, UP, DOWN };

        enum class Movements : std::uint8_t { IDLE, RUN, JUMPING, FALLING };

        enum class InteractionState : std::uint8_t { USED, UNUSED };
    } // namespace states

    // namespace Shapes

    struct Frame {
        Texture* txt = nullptr;
    };

    namespace Components {

        struct Component {};

        struct Vector2D {
            float dx = 0;
            float dy = 0;

            SDL_FPoint* to_sdl() {
                return new SDL_FPoint{dx, dy};
            }

            Vector2D operator-(const Vector2D& other) {
                return {dx - other.dx, dy - other.dy};
            }

            Vector2D operator+(const Vector2D& other) {
                return {dx + other.dx, dy + other.dy};
            }

            Vector2D operator*(const float scalar) {
                return {dx * scalar, dy * scalar};
            }
            Vector2D operator*(const Vector2D& other) {
                return {dx * other.dx, dy * other.dy};
            }

            void operator-=(const Vector2D& other) {
                dx -= other.dx;
                dy -= other.dy;
            }

            void operator+=(const Vector2D& other) {
                dx += other.dx;
                dy += other.dy;
            }

            void operator*=(const float scalar) {
                dx *= scalar;
                dy *= scalar;
            }
            void operator*=(const Vector2D& other) {
                dx *= other.dx;
                dy *= other.dy;
            }
        };

        namespace Shapes {

            struct FRect {

                Vector2D size;
                Vector2D position;

                SDL_FRect* to_sdl() {
                    return new SDL_FRect{position.dx, position.dy, size.dx, size.dy};
                }

                void Move(const Vector2D& direction) {
                    position += direction;
                }
                void Resize(const Vector2D& scale) {
                    size *= scale;
                }
                void Resize(const float scale) {
                    size *= scale;
                }
            };

            struct FCircle {
                Vector2D position;
                float radius;

                void Move(const Vector2D& direction) {
                    position += direction;
                }
                void Resize(const float scale) {
                    radius += scale;
                }
            };

        } // namespace Shapes

        struct Transform : public Component {
            struct Vector2D position;
            struct Vector2D scale;
            float rotation;
            states::FacingDirection facing_direction = states::FacingDirection::RIGHT;
        };

        struct Velocites : public Component {
            struct Vector2D jump;
            struct Vector2D movement;
        };

        struct MovementState : public Component {
            states::Movements movement = states::Movements::IDLE;
            bool is_grounded = false;
            bool is_jumping = false;
            bool is_falling = false;
            bool is_attached_wall_left = false;
            bool is_attached_wall_right = false;
        };

        struct Interactable : public Component {
            bool can_interact = true;
            states::InteractionState state = states::InteractionState::UNUSED;
        };

        struct Rendering : public Component {
            SDL_Renderer* renderer;
            TextureManager* manager;
        };

        struct Sprites : public Component {
            std::unordered_map<std::string, std::vector<Frame*>> animations_frames;
            std::unordered_map<std::string, std::pair<int, int>> animations_data;
            float last_update;
            Frame* current_frame;
            Shapes::FRect sprite_rect;
        };

    } // namespace Components

    struct Collision {
        static constexpr bool CollidedRects(Components::Shapes::FRect r1, Components::Shapes::FRect r2) {
            return SDL_HasRectIntersectionFloat(r1.to_sdl(), r2.to_sdl());
        }
        static constexpr bool CollideRectPoint(Components::Shapes::FRect r, Components::Vector2D point) {
            return SDL_PointInRectFloat(point.to_sdl(), r.to_sdl());
        }
        static constexpr bool CollidedCircles(Components::Shapes::FCircle c1, Components::Shapes::FCircle c2) {
            float dx = c1.position.dx - c2.position.dx;
            float dy = c1.position.dy - c2.position.dy;
            float distanceSquared = dx * dx + dy * dy;
            float radiusSum = c1.radius + c2.radius;
            return distanceSquared <= radiusSum * radiusSum;
        }
        static constexpr bool CollideCircleRect(Components::Shapes::FCircle c, Components::Shapes::FRect r) {
            float closestX = std::max(r.position.dx, std::min(c.position.dx, r.position.dx + r.size.dx));
            float closestY = std::max(r.position.dy, std::min(c.position.dy, r.position.dy + r.size.dy));
            float dx = c.position.dx - closestX;
            float dy = c.position.dy - closestY;
            return dx * dx + dy * dy <= c.radius * c.radius;
        }
        static constexpr bool CollideCirclePoint(Components::Shapes::FCircle c, Components::Vector2D point) {
            float dx = c.position.dx - point.dx;
            float dy = c.position.dy - point.dy;
            float distanceSquared = dx * dx + dy * dy;
            return distanceSquared <= c.radius * c.radius;
        }
    };

    namespace Math {
        constexpr float gravity = 9.80665f;
        constexpr float pi = std::numbers::pi;

        constexpr void ApplyGravity(Components::Velocites* cmp) {
            cmp->jump.dy += gravity / static_cast<float>(JSONParser::graphics::GetFrameRate());
        }

    } // namespace Math

    // namespace Shapes

} // namespace ECS
