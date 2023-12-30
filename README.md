# kinet

Kinetic Art displayed on terminal itself using ncurses.

## Todo

- [ ] Dynamic size update based on window size
- [ ] User parameter to define the trial angle
- [ ] User parameter to set the background and foreground color
- [ ] Default background and foreground color set to same as terminal color theme.

## Usage

Build from source

```py
git clone git@github.com:maker-ATOM/kinet.git
```
```py
cd kinet
cmake -B build
cmake --build build
```

To install the file so that it can be executable from anywhere while being in the terminal,

```
cd build
make
sudo make install
```

### Dependencies
ncurses, CMake