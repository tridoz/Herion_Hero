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

            auto to_sdl() -> SDL_FPoint* {
                return new SDL_FPoint{.x = dx, .y = dy};
            }

            auto operator-(const Vector2D& other) -> Vector2D {
                return {.dx = dx - other.dx, .dy = dy - other.dy};
            }

            auto operator+(const Vector2D& other) -> Vector2D {
                return {.dx = dx + other.dx, .dy = dy + other.dy};
            }

            auto operator*(const float scalar) -> Vector2D {
                return {.dx = dx * scalar, .dy = dy * scalar};
            }

            auto operator*(const Vector2D& other) -> Vector2D {
                return {.dx = dx * other.dx, .dy = dy * other.dy};
            }

            auto operator-=(const Vector2D& other) -> Vector2D& {
                dx -= other.dx;
                dy -= other.dy;
            }

            auto operator+=(const Vector2D& other) -> Vector2D& {
                dx += other.dx;
                dy += other.dy;
                return *this;
            }

            auto operator*=(const float scalar) -> Vector2D& {
                dx *= scalar;
                dy *= scalar;
                return *this;
            }
            auto operator*=(const Vector2D& other) -> Vector2D& {
                dx *= other.dx;
                dy *= other.dy;
                return *this;
            }
        };

        namespace Shapes {

            struct FRect {

                Vector2D size;
                Vector2D position;

                auto to_sdl() -> SDL_FRect* {
                    return new SDL_FRect{.x = position.dx, .y = position.dy, .w = size.dx, .h = size.dy};
                }

                auto Move(const Vector2D& direction) -> void {
                    position += direction;
                }
                auto Resize(const Vector2D& scale) -> void {
                    size *= scale;
                }
                auto Resize(const float scale) -> void {
                    size *= scale;
                }
            };

            struct FCircle {
                Vector2D position;
                float radius;

                auto Move(const Vector2D& direction) -> void {
                    position += direction;
                }
                auto Resize(const float scale) -> void {
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
        static constexpr auto CollidedRects(Components::Shapes::FRect r1, Components::Shapes::FRect r2) -> bool {
            return SDL_HasRectIntersectionFloat(r1.to_sdl(), r2.to_sdl());
        }
        static constexpr auto CollideRectPoint(Components::Shapes::FRect r, Components::Vector2D point) -> bool {
            return SDL_PointInRectFloat(point.to_sdl(), r.to_sdl());
        }
        static constexpr auto CollidedCircles(Components::Shapes::FCircle c1, Components::Shapes::FCircle c2) -> bool {
            float dx = c1.position.dx - c2.position.dx;
            float dy = c1.position.dy - c2.position.dy;
            float distanceSquared = dx * dx + dy * dy;
            float radiusSum = c1.radius + c2.radius;
            return distanceSquared <= radiusSum * radiusSum;
        }
        static constexpr auto CollideCircleRect(Components::Shapes::FCircle c, Components::Shapes::FRect r) -> bool {
            float closestX = std::max(r.position.dx, std::min(c.position.dx, r.position.dx + r.size.dx));
            float closestY = std::max(r.position.dy, std::min(c.position.dy, r.position.dy + r.size.dy));
            float dx = c.position.dx - closestX;
            float dy = c.position.dy - closestY;
            return dx * dx + dy * dy <= c.radius * c.radius;
        }
        static constexpr auto CollideCirclePoint(Components::Shapes::FCircle c, Components::Vector2D point) -> bool {
            float dx = c.position.dx - point.dx;
            float dy = c.position.dy - point.dy;
            float distanceSquared = dx * dx + dy * dy;
            return distanceSquared <= c.radius * c.radius;
        }
    };

    namespace Math {
        constexpr float gravity = 9.80665f;
        constexpr float pi = std::numbers::pi;

        constexpr auto ApplyGravity(Components::Velocites* cmp) -> void {
            cmp->jump.dy += gravity / static_cast<float>(JSONParser::graphics::GetFrameRate());
        }

    } // namespace Math

    // namespace Shapes

} // namespace ECS
