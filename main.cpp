#include <ncurses.h>
#include <stdio.h>
#include <array>
#include <string>
#include <random>
#include <time.h>

const uint8_t DEFAULT_GRID_WIDTH = 64;
const uint8_t DEFAULT_GRID_HEIGHT = 32;

enum class Grid_Item
{
  floor,
  wall_horizontal,
  wall_vertical,
  floor_2,
  floor_3,
  floor_4,
  water
};

const char *grid_symbols = "-=|*\" ~";

class Grid
{
public:
  Grid()
  {
    for (int x = 0; x < DEFAULT_GRID_WIDTH; x++)
    {
      for (int y = 0; y < DEFAULT_GRID_HEIGHT; y++)
      {
        // if (x == 0 || x == DEFAULT_GRID_WIDTH - 1)
        // {
        //   items[x][y] = Grid_Item::wall_vertical;
        // }
        // else if (y == 0 || y == DEFAULT_GRID_HEIGHT - 1)
        // {
        //   items[x][y] = Grid_Item::wall_horizontal;
        // }
        // else
        {
          items[x][y] = get_random_floor_item();
        }
      }
    }

    generate_river();
  }

  void generate_river()
  {
    for (int y = 0; y < DEFAULT_GRID_HEIGHT; y++)
    {
      if (y == 0)
      {
        const short random_int = rand() % DEFAULT_GRID_WIDTH;
        items[random_int][y] = Grid_Item::water;
      }
      else
      {
        for (int x = 0; x < DEFAULT_GRID_WIDTH; x++)
        {
          if (items[x][y - 1] == Grid_Item::water || items[x - 1][y - 1] == Grid_Item::water || items[x + 1][y - 1] == Grid_Item::water)
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

  void draw()
  {
    int row, col;
    getmaxyx(stdscr, row, col);

    for (int y = 0; y < DEFAULT_GRID_HEIGHT; y++)
    {
      for (int x = 0; x < DEFAULT_GRID_WIDTH; x++)
      {
        if (items[x][y] == Grid_Item::water)
        {
          attron(COLOR_PAIR(1));
        }
        mvaddch(row / 2 - y + DEFAULT_GRID_HEIGHT / 2, col / 2 - DEFAULT_GRID_WIDTH / 2 + x, grid_symbols[(int)items[x][y]]);
        if (items[x][y] == Grid_Item::water)
        {
          attroff(COLOR_PAIR(1));
        }
      }

      addch('\n');
    }
  }

  Grid_Item get_random_floor_item()
  {
    const short random_int = std::rand() % 4;
    switch (random_int)
    {
    case 0:
      return Grid_Item::floor;
    case 1:
      return Grid_Item::floor_2;
    case 2:
      return Grid_Item::floor_3;
    case 3:
      return Grid_Item::floor_4;
    default:
      return Grid_Item::floor;
    }
  }

private:
  std::array<std::array<Grid_Item, DEFAULT_GRID_HEIGHT>, DEFAULT_GRID_WIDTH> items;
};

int main()
{
  std::srand(time(nullptr));

  initscr();

  start_color();
  init_pair(1, COLOR_BLUE, COLOR_BLACK);

  Grid g;
  g.draw();

  refresh();

  getch();
  endwin();
  return 0;
}
