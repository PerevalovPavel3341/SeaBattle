#include <iostream>
#include <exception>
#include <vector>
#include <ctime>

#include "sea_battle_playground.h"
#include "ship_manager.h"
#include "ability_manager.h"
#include "game_state.h"
#include "game.h"
#include "game_controller.h"
#include "game_display.h"
#include "terminal_input_processor.h"
#include "terminal_renderer.h"

int main() {
    std::srand(std::time(0));
    try {
        std::cout << "a - attack\nu - use ability\nl - load game save\ns - save game\nq - quit\n";
        
        int field_width = 10;
        int field_length = 10;
        std::vector<int> ship_sizes = {1, 2, 3, 4};

        SeaBattlePlayground user_field(field_width, field_length);
        SeaBattlePlayground enemy_field(field_width, field_length);
        ShipManager user_ships(ship_sizes.size(), ship_sizes);
        ShipManager enemy_ships(ship_sizes.size(), ship_sizes);
        AbilityManager user_abilities;
        GameState game_state(&user_field, &enemy_field, &user_abilities, &user_ships, &enemy_ships);
        Game sea_battle(&user_field, &enemy_field, &user_ships, &enemy_ships, &user_abilities, &game_state);

        TerminalInputProcessor input_processor("commands.txt");
        TerminalRenderer renderer;

        GameController<TerminalInputProcessor> controller(&sea_battle, input_processor);
        GameDisplay<TerminalRenderer> display(&sea_battle, renderer);

        while (true) {
            try {
                display.render();
                bool action = controller.process_command();
                if(!action) break;
            }
            catch (const std::exception& e) {
                std::cout << "Exception: " << e.what() << std::endl;
            }
            catch (const char* e) {
                std::cerr << "Error: " << e << std::endl;
            }
        }
    }
    catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }
    catch (const char* e) {
        std::cerr << "Error: " << e << std::endl;
    }
    return 0;
}