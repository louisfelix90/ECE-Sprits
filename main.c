#include "inc/init.h"
#include "inc/game.h"

BITMAP** Level_loadBitmaps( char* path, unsigned short count ) {
	int i;
	BITMAP** bmps = malloc( sizeof( BITMAP* ) * count );
	char* full_path;

	if( bmps ) {
		full_path = malloc( sizeof( char ) * ( strlen( path ) + 10 ) );

		if( full_path ) {
			for( i = 0; i < count; i++ ) {
				sprintf( full_path, "%s%d.png", path, i + 1 );

				bmps[ i ] = load_png( full_path, NULL );
				if( bmps[ i ] == NULL ) {
					allegro_message( "Erreur chargement %s", full_path );
					return 0;
				}
			}

			free( full_path );

			return bmps;
		}
	}

	return NULL;
}

int main() {
	Init();

	Level level;
	level.bmps.page = create_bitmap( 1024, 768 );
	if( !level.bmps.page ) {
		allegro_message( "Erreur creation bitmap" );
		return EXIT_FAILURE;
	}

	level.bmps.stick_col = create_bitmap( 1024, 768 );
	if( !level.bmps.stick_col ) {
		allegro_message( "Erreur creation bitmap" );
		return EXIT_FAILURE;
	}

	level.bmps.col = load_png( "images/Ncolli(1024).png", NULL );
	if( !level.bmps.col ) {
		allegro_message( "Erreur chargement Ncolli(1024).png" );
		return EXIT_FAILURE;
	}

	level.bmps.back = load_png( "images/fondniv.png", NULL );
	if( !level.bmps.back ) {
		allegro_message( "Erreur chargement fondniv.png" );
		return EXIT_FAILURE;
	}

	level.bmps.fore = NULL;

	level.stickmen = NULL;
	level.nb_stickmen_max = 10;
	level.nb_stickmen_should_arrive = 9;
	level.counter_stickmen_arrival_max = 50;

	level.bmps.stickmen_walking.bmps = Level_loadBitmaps( "images/sticks/stickMan", 20 );
	level.bmps.stickmen_walking.count = 20;

	level.bmps.stickmen_falling.bmps = Level_loadBitmaps( "images/sticks/stickManChute", 1 );
	level.bmps.stickmen_falling.count = 1;

	if( !level.bmps.stickmen_walking.bmps || !level.bmps.stickmen_falling.bmps ) {
		allegro_message( "CATASTROPHE" );
		return EXIT_FAILURE;
	}

	level.fast_dt = 2;
	level.slow_dt = 1;

	level.gravity = (Vector2) { 0, 4 };
	level.movement = (Vector2) { 1, 0 };

	Game_launch( &level );

	return 0;
}

END_OF_MAIN();