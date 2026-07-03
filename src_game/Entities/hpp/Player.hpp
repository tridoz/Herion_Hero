#ifndef HERION_HERO_PLAYER_HPP
#define HERION_HERO_PLAYER_HPP

#include <unordered_map>

#include "../../Utils/hpp/Animation.hpp"
#include "../../Exceptions/hpp/HerionFileException.hpp"
#include "../../Utils/hpp/FileOpener.hpp"

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
		ATTACK
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

	/**
	 * @brief Return the current PlayerState
	 * @return PlayerState
	 */
	PlayerState GetPlayerState() const;

	/**
	 * @brief Return the current GameMode
	 * @return GameMode
	 */
	GameMode GetGameMode() const;

	/**
	 * @brief Return the current FacingDirection
	 * @return FacingDirection
	 */
	FacingDirection GetDirection() const;

	/**
	 * @brief Return the previous PlayerState
	 * @return playerState
	 */
	PlayerState GetPreviousState() const;

	/**
	 * @brief Return the revious GameMode
	 * @return GameMdoe
	 */
	GameMode GetPreviousGameMode() const;

	/**
	 * @brief Set the new GameMode
	 * @param new_game_mode New GameMode to set
	 */
	void SetGameMode( const GameMode new_game_mode );

	/**
	 * @brief Set the new PlayerState
	 * @param new_player_state New PlayerState to set
	 */
	void SetPlayerState( const PlayerState new_player_state );

	/**
	 * @brief Set the new FacingDirection
	 * @param new_direction New FacingDirection to set
	 */
	void SetPlayerDirection( const FacingDirection new_direction );

	/**
	 * @brief Setthe TextureManager to load the textures
	 * @param new_texture_manager New TextureManager to set
	 */
	void SetTextureManager( TextureManager *new_texture_manager );

	/**
	 * @brief Load animation based on a .json configuration file
	 * @param filepath Path to the .json configuration file
	 */
	void LoadAnimation(const std::string &filepath);

	/**
	 * @brief Update the Player
	 */
	void Update();

	/**
	 * @brief Draw the player
	 * @param renderer Renderer needed to draw the player
	 */
	void Draw( SDL_Renderer *renderer );

	/**
	 * @brief Move the player in a direction by a certain amount based on delta time
	 * @param direction Direction in which to move
	 * @param delta_time Time from one frame to the other needed to calculate how much the player move
	 */
	void Move(FacingDirection direction, float delta_time);

	/**
	 * @brief Resize the Textures
	 */
	void Resize();

	/**
	 * @brief Set the coordinate of the player in a certai npoint
	 * @param spawn_x Coordinate X of spawn
	 * @param spawn_y Coordiante Y of spawn
	 */
	void Spawn( int spawn_x, int spawn_y );

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

	TextureManager* texture_manager;
	std::unordered_map< std::string, Animation* > animations;
	Animation* current_animation;

	/**
	 * @brief Update animation frame if needed
	 */
	void UpdateAnimationFrame();



};


#endif //HERION_HERO_PLAYER_HPP
