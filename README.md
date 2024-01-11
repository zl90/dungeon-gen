# dungeon-gen
A 2D dungeon/terrain generator I built for the purposes of learning the NCurses library

## How to run on Debian/Ubuntu Linux
1. Install the [ncurses library](https://www.cyberciti.biz/faq/linux-install-ncurses-library-headers-on-debian-ubuntu-centos-fedora/) with the command: `sudo apt-get install libncurses5-dev libncursesw5-dev`
2. From the project root directory run the command: `g++ --std=c++20 main.cpp -lncursesw && ./a.out`
