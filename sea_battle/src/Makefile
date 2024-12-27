all : game
main.o : main.cpp
	g++ -c main.cpp
ship.o : ship.cpp
	g++ -c ship.cpp
field_cell.o : field_cell.cpp
	g++ -c field_cell.cpp
ship_manager.o : ship_manager.cpp
	g++ -c ship_manager.cpp
sea_battle_playground.o : sea_battle_playground.cpp
	g++ -c sea_battle_playground.cpp
exceptions.o : exceptions.cpp
	g++ -c exceptions.cpp
ability.o : ability.cpp
	g++ -c ability.cpp
double_damage.o : double_damage.cpp
	g++ -c double_damage.cpp
random_bombardment.o : random_bombardment.cpp
	g++ -c random_bombardment.cpp
scanner.o : scanner.cpp
	g++ -c scanner.cpp
ability_manager.o : ability_manager.cpp
	g++ -c ability_manager.cpp
game_state.o : game_state.cpp
	g++ -c game_state.cpp
game.o : game.cpp
	g++ -c game.cpp
terminal_renderer.o : terminal_renderer.cpp
	g++ -c terminal_renderer.cpp
game : main.o ship.o field_cell.o ship_manager.o sea_battle_playground.o exceptions.o ability.o double_damage.o random_bombardment.o scanner.o ability_manager.o game_state.o game.o terminal_renderer.o
	g++ main.o ship.o field_cell.o ship_manager.o sea_battle_playground.o exceptions.o ability.o double_damage.o random_bombardment.o scanner.o ability_manager.o game_state.o game.o terminal_renderer.o -o game

	rm *.o