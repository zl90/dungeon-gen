#include <ncurses.h>
#include <stdio.h>
#include <array>
#include <string>
#include <random>
#include <time.h>

enum class Grid_Item
{
  floor,
  wall_horizontal,
  wall_vertical,
  brush,
  grass,
  floor_4,
  water
};

class Grid
{
public:
  Grid()
  {
    generate_ground_tiles();
    generate_river_tiles();
  }

  bool is_above_river_tile(int x, int y)
  {
    if (x == 0)
    {
      return items[x][y - 1] == Grid_Item::water || items[x + 1][y - 1] == Grid_Item::water;
    }
    else if (x == items.size() - 1)
    {
      return items[x][y - 1] == Grid_Item::water || items[x - 1][y - 1] == Grid_Item::water;
    }
    else
    {
      return items[x][y - 1] == Grid_Item::water || items[x - 1][y - 1] == Grid_Item::water || items[x + 1][y - 1] == Grid_Item::water;
    }
  }

  void generate_ground_tiles()
  {
    for (int x = 0; x < items.size(); x++)
    {
      for (int y = 0; y < items[x].size(); y++)
      {
        items[x][y] = get_random_floor_item();
      }
    }
  }

  void generate_river_tiles()
  {
    for (int y = 0; y < items[0].size(); y++)
    {
      if (y == 0)
      {
        const uint8_t random_int = rand() % items.size();
        items[random_int][y] = Grid_Item::water;
      }
      else
      {
        for (int x = 0; x < items.size(); x++)
        {
          if (is_above_river_tile(x, y))
          {
            if (rand() % 2 == 1)
            {
              items[x][y] = Grid_Item::water;
            }
          }
        }
      }
    }
  }

  void set_colour_for_item(Grid_Item item)
  {
    switch (item)
    {
    case Grid_Item::water:
      attron(COLOR_PAIR(5));
      break;
    case Grid_Item::grass:
      attron(COLOR_PAIR(2));
      break;
    case Grid_Item::brush:
      attron(COLOR_PAIR(4));
      break;
    case Grid_Item::floor:
      attron(COLOR_PAIR(3));
      break;
    default:
      attron(COLOR_PAIR(1));
      break;
    }
  }

  void unset_colour()
  {
    attron(COLOR_PAIR(1));
  }

  void draw()
  {
    int row, col;
    getmaxyx(stdscr, row, col);

    for (int y = 0; y < items[0].size(); y++)
    {
      for (int x = 0; x < items.size(); x++)
      {
        set_colour_for_item(items[x][y]);
        mvaddch(row / 2 - y + items[0].size() / 2, col / 2 - items.size() / 2 + x, grid_symbols[(int)items[x][y]]);
        unset_colour();
      }

      addch('\n');
    }
  }

  Grid_Item get_random_floor_item()
  {
    const uint8_t random_int = std::rand() % 4;
    switch (random_int)
    {
    case 0:
      return Grid_Item::floor;
    case 1:
      return Grid_Item::brush;
    case 2:
      return Grid_Item::grass;
    case 3:
      return Grid_Item::floor_4;
    default:
      return Grid_Item::floor;
    }
  }

private:
  static const uint8_t DEFAULT_GRID_WIDTH = 100;
  static const uint8_t DEFAULT_GRID_HEIGHT = 50;

  const char *grid_symbols = "-=|*\" ~";
  std::array<std::array<Grid_Item, DEFAULT_GRID_HEIGHT>, DEFAULT_GRID_WIDTH> items;
};

void initialise_colours()
{
  init_pair(1, COLOR_WHITE, COLOR_BLACK);
  init_pair(2, COLOR_GREEN, COLOR_BLACK);
  init_pair(3, COLOR_YELLOW, COLOR_BLACK);
  init_pair(4, COLOR_CYAN, COLOR_BLACK);
  init_pair(5, COLOR_BLUE, COLOR_BLACK);
}

int main()
{
  std::srand(time(nullptr));

  initscr();

  start_color();
  initialise_colours();

  int input;

  while (input != 'q' && input != 27)
  {
    Grid g;
    g.draw();

    refresh();

    input = getch();
  }
  endwin();
  return 0;
}
