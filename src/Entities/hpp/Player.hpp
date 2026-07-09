#ifndef HERION_HERO_PLAYER_HPP
#define HERION_HERO_PLAYER_HPP

#include <unordered_map>

#include "../../Utils/hpp/Animation.hpp"
#include "../../Exceptions/hpp/HerionFileException.hpp"
#include "../../Utils/hpp/FileOpener.hpp"
#include "../../Utils/hpp/JSONParser.hpp"


#include "../../Utils/hpp/Logger.hpp"
#include "../../Utils/hpp/Reflector.hpp"

class TextureManager;

class Player {

public:
	/**
	 * @enum GameMode
	 * @brief Game Mode in which the player can be
	 */
	enum class GameMode {
		MAIN_MENU,
		GENERAL_SETTINGS_MENU,
		GRAPHICS_SETTINGS_MENU,
		AUDIO_SETTINGS_MENU,
		PAUSE_MENU,
		EDITOR_MENU,
		ROOM_SELECTION,
		EDITOR,
		INVENTORY_MENU,
		LEVEL_EDITOR,
		ANIMATION_EDITOR,
		IN_GAME,
		EXIT
	};

	/**
	 * @enum PlayerState
	 * @brief States in which the player can be
	 */
	enum class PlayerState {
		IDLE,
		RUN,
		DEATH,
		ATTACK,
		JUMP,
		FALLING
	};



	/**
	 * @enum FacingDirection
	 * @brief Direction in which the player can be facing
	 */
	enum class FacingDirection{
		WEST,
		EAST
	};



	Player();
	~Player();

	SDL_FRect player_rect;

	PlayerState GetPlayerState() const;
	GameMode GetGameMode() const;
	FacingDirection GetDirection() const;
	PlayerState GetPreviousState() const;
	GameMode GetPreviousGameMode() const;
	void SetGameMode( const GameMode new_game_mode );
	void SetPlayerState( const PlayerState new_player_state );
	void SetPlayerDirection( const FacingDirection new_direction );
	void SetTextureManager( TextureManager *new_texture_manager );
	void LoadAnimation(const std::string &filepath);
	void Update(float delta_time);
	void Draw( SDL_Renderer *renderer );
	void Move(FacingDirection direction, float delta_time);
	void UpdatePhysics(float delta_time);
	void Jump();
	void Resize();
	void Spawn( int spawn_x, int spawn_y );
	void reset();
	void SetOnGround( bool on_ground );
	float GetVelocityY() const ;
	void SetPositionY( float y );
	void SetVelocityY( float y );
	void SetAttachedToWallRight( bool attached );
	void SetAttachedToWallLeft( bool attached );
	float& GetPosX();
    float& GetPosY();
    float& GetVelocityX();
    float& GetVelocityY();
    void ParseEntityProperties( const struct JSONParser::entities::EntityProperties prop );

	[[no_discard]] bool IsJumping() const;
	[[no_discard]] bool IsFalling() const;
	[[no_discard]] bool OnGround() const;

	static constexpr auto reflect_members() {
		return std::make_tuple(
			Field<Player, PlayerState>{ "state", &Player::state },
			Field<Player, GameMode>{ "mode", &Player::mode },
			Field<Player, FacingDirection>{ "direction", &Player::direction },
			Field<Player, PlayerState>{ "previousState", &Player::previousState },
			Field<Player, GameMode>{ "previousGameMode", &Player::previousGameMode },
			Field<Player, float>{ "pos_x", &Player::pos_x },
			Field<Player, float>{ "pos_y", &Player::pos_y },
			Field<Player, float>{ "next_x", &Player::next_x },
			Field<Player, float>{ "next_y", &Player::next_y },
			Field<Player, float>{ "movement_angle", &Player::movement_angle },
			Field<Player, float>{ "velocity_x", &Player::velocity_x },
			Field<Player, float>{ "speed", &Player::speed },
			Field<Player, float>{ "fixed_pos_x", &Player::fixed_pos_x },
			Field<Player, float>{ "fixed_pos_y", &Player::fixed_pos_y },
			Field<Player, float>{ "fixed_width", &Player::fixed_width },
			Field<Player, float>{ "fixed_height", &Player::fixed_height },
			Field<Player, float>{ "scale", &Player::scale },
			Field<Player, bool>{ "is_jumping", &Player::is_jumping },
			Field<Player, bool>{ "is_falling", &Player::is_falling },
			Field<Player, bool>{ "on_ground", &Player::on_ground },
			Field<Player, TextureManager*>{ "texture_manager", &Player::texture_manager },
			Field<Player, std::unordered_map<std::string, Animation*> >{ "animations", &Player::animations },
			Field<Player, Animation*>{ "current_animation", &Player::current_animation }
		);
	}


private:

	PlayerState state;
	GameMode mode;
	FacingDirection direction;

	PlayerState previousState;
	GameMode previousGameMode;

	float pos_x, pos_y;
	float next_x, next_y;
	float movement_angle;

	float velocity_x;
	float speed;

	float fixed_pos_x, fixed_pos_y;
	float fixed_width, fixed_height;
	float scale;

	bool is_jumping;
	bool is_falling;

	bool attached_to_wall_left = false;
	bool attached_to_wall_right = false;

	float velocity_y = 0.0f;
    float gravity = 1800.0f;
    float jump_force = -800.0f;
    bool on_ground = true;

	TextureManager* texture_manager;
	std::unordered_map< std::string, Animation* > animations;
	Animation* current_animation;

	/**
	 * @brief Update animation frame if needed
	 */
	void UpdateAnimationFrame();





};


#endif //HERION_HERO_PLAYER_HPP
