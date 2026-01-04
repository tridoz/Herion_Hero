#ifndef HERION_HERO_PLAYER_HPP
#define HERION_HERO_PLAYER_HPP

#include "../../Utils/hpp/Animation.hpp"
#include "../../Exceptions/hpp/HerionFileException.hpp"
#include "../../Utils/hpp/FileOpener.hpp"

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

	void LoadAnimation( const std::string &dir_filepath, const std::string &animation_name );

	void Update(SDL_Renderer* renderer);
	void Draw( SDL_Renderer *renderer );

	void Move(float x, float y);
	void Resize();


private:

	PlayerState state;
	GameMode mode;
	FacingDirection direction;

	PlayerState previousState;
	GameMode previousGameMode;

	float pos_x, pos_y;
	float next_x, next_y;
	float movement_angle;

	float speed;

	float fixed_pos_x, fixed_pos_y;
	float fixed_width, fixed_height;
	float scale;

	TextureManager* texture_manager;
	std::unordered_map< std::string, Animation* > animations;
	Animation* current_animation;

	void UpdateAnimationFrame( SDL_Renderer* renderer );

};


#endif //HERION_HERO_PLAYER_HPP