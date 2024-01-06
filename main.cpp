#include <ncurses.h>
#include <stdio.h>
#include <array>
#include <string>

const uint8_t DEFAULT_GRID_WIDTH = 32;
const uint8_t DEFAULT_GRID_HEIGHT = 16;

enum class Grid_Item {
	wood_floor,
	wood_wall_horizontal,
	wood_wall_vertical
};

const char * grid_item_symbol = "-=|";

class Grid {
public:
	Grid(){
		for (int y = 0; y < DEFAULT_GRID_HEIGHT; y++) {
			for (int x = 0; x < DEFAULT_GRID_WIDTH; x++) {
				items[x][y] = Grid_Item::wood_floor;
			}	
		}
	}

	void draw() {
		int row, col;
		getmaxyx(stdscr, row, col);
		
		for (int y = 0; y < DEFAULT_GRID_HEIGHT; y++) {
			std::string line = "";
			
			for (int x = 0; x < DEFAULT_GRID_WIDTH; x++) {
				line += grid_item_symbol[(int)items[x][y]];
			}	

			line += '\n';
			mvprintw(row/2 - y + DEFAULT_GRID_HEIGHT / 2, (col - line.length())/2, "%s", line.c_str());
		}
	}

private:
	std::array<std::array<Grid_Item, DEFAULT_GRID_HEIGHT>, DEFAULT_GRID_WIDTH> items;
};

int main()
{
	initscr();

	Grid g;
	g.draw();

	refresh();
	getch();
	endwin();
	return 0;
}
