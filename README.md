# dungeon-gen
A 2D dungeon/terrain generator I built for the purposes of learning the NCurses library. The game is played entirely in your terminal.

As of April 2024, the game is currently a very minimal immitation of the Dwarf Fortress world generator. Watch this space for updates!

![Screenshot](https://github.com/zl90/dungeon-gen/blob/main/screenshot.jpg?raw=true)

## How to play
- Use the arrow keys to move the yellow cursor around the map. This lets you inspect each location on the grid.

## How to run on Debian/Ubuntu Linux
1. Clone the repo.
2. Install [cmake](https://cmake.org/) with the command `sudo apt-get install cmake`
3. Install the [ncurses library](https://www.cyberciti.biz/faq/linux-install-ncurses-library-headers-on-debian-ubuntu-centos-fedora/) with the command: `sudo apt-get install libncurses5-dev libncursesw5-dev`
4. From the project root directory run the build script: `./build.sh`. This will build and run the program (make sure your terminal is in fullscreen mode, or the game won't display correctly).

## How to run on MacOS terminal
1. Clone the repo.
2. Install [cmake](https://cmake.org/) with the command `brew install cmake`
3. Install the [ncurses library](https://formulae.brew.sh/formula/ncurses) with the command: `brew install ncurses`
4. Add the ncurses library to your PATH list: `echo 'export PATH="/usr/local/opt/ncurses/bin:$PATH"' >> ~/.zshrc`
5. You may need to restart your terminal, or run the command `source ~/.zshrc`
6. From the project root directory run the build script: `./build.sh`. This will build and run the program (make sure your terminal is in fullscreen mode, or the game won't display correctly).

## Ideas/TODOs
- Basic cursor movement + information panel.
- ~~Random name generation for Units based on RaceType.~~
- ~~Random name generation for Structures based on StructureType and owner RaceType.~~
- River tile generation (no clustered hotspots).
- Names for continents/islands.
- Empires/kingdoms (Structures can belong to these).
- Time progression (day by day. Keep track of day/month/year).
- Unit lifecycles, travel between grid cells, fights, births, deaths, etc.
- Historical events (eg: Dwarf kills Spider, Paladin consecrates structure, etc).
- At some point I'll add Djikstra's algorithm for unit pathfinding.
