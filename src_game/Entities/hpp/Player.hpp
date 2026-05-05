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
		EDITOR_MENU,
		ROOM_SELECTION,
		TEXTURE_SELECTION,
		EDITOR,
		INVENTORY_MENU,
		LEVEL_EDITOR,
		ANIMATION_EDITOR,
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

	void Update(SDL_Renderer* renderer);
	void Draw( SDL_Renderer *renderer );

	void Move(FacingDirection direction, float delta_time);
	void Resize();
	void Spawn( int spawn_x, int spawn_y );


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

	void UpdateAnimationFrame( SDL_Renderer* renderer );

};


#endif //HERION_HERO_PLAYER_HPP