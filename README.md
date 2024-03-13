# dungeon-gen
A 2D dungeon/terrain generator I built for the purposes of learning the NCurses library

## How to run on Debian/Ubuntu Linux
1. Install the [ncurses library](https://www.cyberciti.biz/faq/linux-install-ncurses-library-headers-on-debian-ubuntu-centos-fedora/) with the command: `sudo apt-get install libncurses5-dev libncursesw5-dev`
2. From the project root directory run the build script: `./build.sh`. This will build and run the program.

## Ideas/TODOs
- Basic cursor movement + information panel.
- Random name generation for Units based on RaceType.
- Random name generation for Structures based on StructureType and owner RaceType.
- River tile generation (no clustered hotspots).
- Names for continents/islands.
- Empires/kingdoms (Structures can belong to these).
- Time progression (day by day. Keep track of day/month/year).
- Unit lifecycles, travel between grid cells, fights, births, deaths, etc.
- Historical events (eg: Dwarf kills Spider, Paladin consecrates structure, etc).
- At some point I'll add Djikstra's algorithm for unit pathfinding.