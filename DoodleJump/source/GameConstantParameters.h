#pragma once
namespace game_constant_parameters
{
	constexpr int WIN_WIDTH = 800, WIN_HEIGHT = 600;
	constexpr char FONT[] = "data\\Font\\MSComicSans.ttf";
	constexpr char ICON[] = "data\\Icon@2x.png";

// MenuScene
	constexpr char MENU_COVER[] = "data\\Background\\Default@2x.png";

// GameScene
	constexpr char SEQ_FILE[] = "data\\gameData\\platform_sequence.txt";
	constexpr char coverBackground[] = "data\\Background\\space-bck@2x.png";
	constexpr char imgTopBar[] = "data\\ScoreBoard\\score_board.png";
	constexpr char buttonPause[] = "data\\PAUSE_ORIGINAL.png";

// PauseScene
	constexpr char coverPause[] = "data\\Background\\pause-cover.png";

// GameoverScene
	constexpr char coverGameOver[] = "data\\Background\\gameover-cover.png";

// Doodle
	constexpr float DOODLE_VY = 0.7f; // pixels per miliseconds
	constexpr float DOODLE_VY_SPRING = 1.3f;
	constexpr float DOODLE_VX = 0.42f;
	constexpr float G = 14 / 10000.0f;

}
