//
// Created by trida on 11/19/25.
//

#ifndef HERION_HERO_PLAYER_HPP
#define HERION_HERO_PLAYER_HPP


class Player {

public:

	typedef enum {
		MAIN_MENU,
		SETTINGS_MENU,
		PAUSE_MENU,
		INVENTORY_MENU,
		IN_GAME,
		EXIT
	}GameMode;

	typedef enum {
		IDLE,
		RUN,
		DEATH,
		ATTACK
	}PlayerState;

	Player();
	~Player();

	PlayerState GetPlayerState() const;
	GameMode GetGameMode() const;

	PlayerState GetPreviousState() const;
	GameMode GetPreviousGameMode() const;

	void SetGameMode( GameMode new_game_mode );
	void SetPlayerState( PlayerState new_player_state );

private:

	PlayerState state;
	GameMode mode;

	PlayerState previousState;
	GameMode previousGameMode;

};


#endif //HERION_HERO_PLAYER_HPP