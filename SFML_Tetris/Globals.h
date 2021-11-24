#pragma once

namespace Globals
{
	const int SCREEN_WIDTH = 1138;
	const int SCREEN_HEIGHT = 640;

	//20 rows works well + 3 for extra space at the top
	const int ROWS = 23;
	
	//10 columns works well
	const int COLUMNS = 10;

	const float SPRITE_SCALE = 0.5f; 

	enum ROTATION_DIRECTION
	{
		COUNTERCLOCKWISE,
		CLOCKWISE
	};

}