#pragma once
#define WIDTH_PLAYER  28
#define HEIGHT_PLAYER  50
#define WIDTH_PLAYER_RIGHT 28
#define HEIGHT_PLAYER_RIGHT 47
#define WIDTH_PLAYER_LEFT 28
#define HEIGHT_PLAYER_LEFT 47
class Player {
public:
	int health;
	int speed;
	void iniPlayer();
	void update_PlayerPosition(int _cmd, int framebuffer);
	void update_PlayerImage(int frameBuffer);
	void update_Player(int n_command, int framebuffer);
	struct Position
	{
		int x, y;
	};
	enum ObjectState
	{
		Live,
		Dead,
		Invulnerable
	};
	struct Direction
	{
		int up;
		int down;
		int left;
		int right;
	};
};
struct PlayerCollider
{
	int xl, xr, yu, yd;
};
extern PlayerCollider playerCollider;
extern Player::Position Struct_PlayerPosition;
extern Player::ObjectState E_TYPE_PlayerState;
void putStatePlayer();




