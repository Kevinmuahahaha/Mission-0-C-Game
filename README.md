# Mission-0-C-Game
It's a simple game written with C++ and SDL2
The Details:

To-Dos Before The Game Loop:
  player.SetPlayerPosition();       // player <-- an Object from class Player
	Info::mWindowHeight = ....        // Info   <-- Shared information( used between classes )
	Info::mWindowWidth  = .... 
	ObjectManager::mUIManager = ...   // ObjectManager <-- Manages non-player Objects. For example, the background.

To-Dos Inside The Game Loop:

	SDL_RenderClear( renderer );      // Of course, clear the renderer before rendering each frame.

	[ player ( from player.h ) ]
		if( keypress )
			MovePlayer                         // <-- HandleUserInput() and such, update player's position
				--> UpdatePlayerClip();          // This animates the player
				--> uimanager.ScrollBackground() // Scroll Background when the background is long enough
        --> player.RenderPlayerClip();   // Do the actuall rendering ( run this every frame )

  [ enemy manager ( from enemymanager.h ) ] 
    // manages every single enemy
    // Not implemented. TODO
  
	[ enemy  ( from enemy.h ) ]
		move();                         // This Is Handled by an enemy manager <-- Not implemented. TODO
		detect_hit();                   // This Is Also Handled by an enmey manager <-- Not implemented. TODO
			--> UpdatePlayerScore();      // Change player's score, and inform UIManager


	[ uimanager ( from uimanager.h ) ]
		ScrollBackground(); // This Function Only Updates Background's Clip
		RenderBackground(); // ( run this every frame )
		RenderPlayerScore();
