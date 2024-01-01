# kinet

Kinetic Art displayed on terminal using ncurses.

<p align="center">
	<img src="images/demo.gif" width="600"/>
</p>


## Todo

- [ ] Dynamic size update based on window size
- [ ] User parameter to define the trial angle
- [ ] Arrow key binding to change the rate of animation
- [ ] User parameter to set the background and foreground color
- [ ] Default background and foreground color set to same as terminal color theme [ref](https://github.com/htop-dev/htop/tree/main) 
  - How to access colors? => use terminfo database, term.h, getcap, tgetent => method that returns terminal capabilities,

## Usage

Install from apt

```
wget -O - https://raw.githubusercontent.com/maker-ATOM/apt-repo/master/public.key | sudo apt-key add -

echo "deb https://maker-atom.github.io/apt-repo stable main" | sudo tee /etc/apt/sources.list.d/maker-ATOM.list

sudo apt update
```

```
sudo apt install kinet
```

**OR**

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