#ifndef HERION_HERO_PLAYER_HPP
#define HERION_HERO_PLAYER_HPP

#include "../../Utils/hpp/Animation.hpp"

class TextureManager;

class Player {

public:

	enum class GameMode {
		MAIN_MENU,
		SETTINGS_MENU,
		PAUSE_MENU,
		INVENTORY_MENU,
		LOG_MENU,
		IN_GAME,
		EXIT
	};

	enum class PlayerState {
		IDLE,
		RUN,
		DEATH,
		ATTACK
	};

	 enum class FacingDirection{
		NORTH,
		WEST,
		SOUTH,
		EAST
	};

	enum class MovingDirection{
		NORTH,
		NORTH_EAST,
		EAST,
		SOUTH_EAST,
		SOUTH,
		SOUTH_WEST,
		WEST,
		NORTH_WEST
	};

	Player();
	~Player();

	PlayerState GetPlayerState() const;
	GameMode GetGameMode() const;
	FacingDirection GetDirection() const;

	PlayerState GetPreviousState() const;
	GameMode GetPreviousGameMode() const;

	void SetGameMode( const GameMode new_game_mode );
	void SetPlayerState( const PlayerState new_player_state );
	void SetPlayerDirection( const FacingDirection new_direction );

	void SetTextureManager( TextureManager *new_texture_manager );

	void LoadAnimation( const std::string &dir_filepath, const std::string &animation_name );

	void Update() const;
	void Draw( SDL_Renderer *renderer ) const;

private:

	PlayerState state;
	GameMode mode;
	FacingDirection direction;

	PlayerState previousState;
	GameMode previousGameMode;

	float pos_x, pos_y;
	float fixed_pos_x, fixed_pos_y;
	float fixed_width, fixed_height;

	TextureManager* texture_manager;
	std::unordered_map< std::string, Animation* > animations;
	Animation* current_animation;

};


#endif //HERION_HERO_PLAYER_HPP