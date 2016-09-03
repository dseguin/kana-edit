# Simple kana editor
[![Build Status](https://travis-ci.org/dseguin/kana-edit.svg?branch=master)](https://travis-ci.org/dseguin/kana-edit)

kana-edit is a simple editor for <a href="https://en.wikipedia.org/wiki/Katakana">katakana</a> and <a href="https://en.wikipedia.org/wiki/Hiragana">hiragana</a>. You can type in standard <a href="https://en.wikipedia.org/wiki/R%C5%8Dmaji">romaji</a> (english representations of kana characters) and it will "translate" what you type *on the fly*.

<img src="resources/screenshot01.png">

The top box is the input field--where input text is displayed, and the lower box is the output field--where the processed kana is displayed. In the top left is an options menu, where you can...

- Switch between Katakana mode and Hiragana mode
- Clear the screen (both text fields)
- Save what is in the output field to a unicode text file
- Exit the program

<img src="resources/screenshot02.png">

The program uses <a href="http://www.sfml-dev.org/">SFML</a> as a display interface. Future updates may make use of SFML's other features, such as sound or networking. Kana-edit currently builds on Windows, MacOSX, Linux, and {Free|Open}BSD.

# Compiling on Windows
Building kana-edit requires:
- sfml libraries (>=2.0)
- Visual Studio (or at least the visual c/c++ compiler)
   - MinGW/g++ may work, remains untested.
- git utility (optional)

Use your git utility to clone this repository
```
> git clone https://github.com/dseguin/kana-edit.git
```
or simply download and extract the <a href="https://github.com/dseguin/kana-edit/archive/master.zip">latest version of the repo</a>.

### Visual Studio 2015
Open `MSVC15/Solution_kanaedit.sln` with the Visual Studio IDE. Select your target and select `build`. VS should automatically pull the necessary sfml libraries through NuGet.

You'll find kanaedit.exe and the sfml libraries in the Release or Debug folder (whatever target you chose). Copy/move them to wherever you like.

### Command line
Make sure you have the appropriate <a href="http://www.sfml-dev.org/download.php">SFML libraries</a>.

Next, run `unzip_headers.bat` in the `MSVC15` folder to extract the font headers. Open a command prompt through your IDE to have the appropriate variables set. Change your directory to where you extracted or cloned the kana-edit repo:
```
> cd path/to/kana-edit
```
Now compile with:
```
> cl /EHsc src/*.cpp /Fekanaedit.exe /I<path/to/SFML/include> /link <path/to/SFML/lib>/sfml-graphics.lib <path/to/SFML/lib>/sfml-window.lib <path/to/SFML/lib>/sfml-system.lib
```
Then copy the appropriate .dlls from `<path/to/SFML/bin>` (system, graphics, window) to the folder containing the newly created kanaedit.exe. The .dlls need to be in the same directory for the program to run.

# Compiling on MacOSX
These instructions refer to the command line.

### Dependencies
Install the latest version of [XCode](https://developer.apple.com/xcode/). You'll need [Homebrew](http://brew.sh/) for building dependencies. Follow the instructions at http://brew.sh/. You may need to add `/usr/local/bin` to your $PATH variable. You can do this by editing your .bashrc file and adding this line:
```
export PATH="/usr/local/bin:$PATH"
```
Once you have Homebrew set up, use it to install SFML and git. On the command line:
```
brew update && brew install sfml && brew install git
```
Now use git to pull the kana-edit source code:
```
git clone https://github.com/dseguin/kana-edit.git
cd kana-edit/
```
You're now ready to build.

### Building kana-edit
You can use the gcc or clang c++ compilers, both have been shown to work. You should now be able to build kana-edit with these commands:
```sh
touch -rbuild/dummy config* aclocal* Makefile*
cd build/
../configure
make
```
If the build was successful, you'll find the `kanaedit` executable in the `src` folder.

# Compiling on Linux and FreeBSD/OpenBSD
What follows are instructions for building kana-edit on Linux and {Free|Open}BSD.

### Dependencies
Here's a list of what you'll need to build kana-edit:
- sfml-dev >=2.0
- g++ or clang++
- GNU Make
- unzip (to decompress font headers)

Some systems don't come with unicode support right away, so make sure your system can display characters within the <a href="https://en.wikipedia.org/wiki/Hiragana_%28Unicode_block%29">hiragana</a> and <a href="https://en.wikipedia.org/wiki/Katakana_%28Unicode_block%29">katakana</a> blocks.

### Build kana-edit
To build kana-edit, get a fresh clone:
```sh
$ git clone https://github.com/dseguin/kana-edit.git
$ cd kana-edit
```
Because of a quirk in GNU Make, if the timestamps on the config scripts are off, it will request a reconfigure. This can be troublesome because autotools commands are version specific, and aclocal would need additional scripts in `autoconf-archive`. So for simplicity's sake, make sure the timestamps are the same with
```sh
$ touch -rbuild/dummy config* aclocal* Makefile*
```
Next, building kana-edit should be as simple as
```sh
$ cd build
$ ../configure
$ make
```
Note for FreeBSD/OpenBSD: You'll need to set some flags when running `configure`:
```sh
$ env CPPFLAGS='-I/usr/local/include -I/usr/X11R6/include' LDFLAGS='-L/usr/local/lib -L/usr/X11R6/lib' ../configure
```
You'll find `kanaedit` in `src/`. You can move it to `/usr/local/bin/`, or `$HOME/bin/`, or somewhere else in your `$PATH`. Then run it with `kanaedit`.

# Troubleshooting (Linux)
### Linking issues
A common issue is linking SFML libraries, especially if you've built the libraries manually:
#### Undefined reference to ...
This means your linker doesn't know the location of the SFML libraries. If you yourself do not know where these libraries are, try this:
```sh
$ find / -type f -name "libsfml*.so*" 2>/dev/null
```
The easiest way to fix this is to add the location to your linker's path variable. If your linker doesn't allow that, or you would rather try something else, you can change this line in <a href="src/Makefile.am">src/Makefile.am</a>
```
kanaedit_LDADD = -lsfml-window -lsfml-system -lsfml-graphics
```
to this
```
kanaedit_LDADD = -L/path/to/sfml/libraries -lsfml-window -lsfml-system -lsfml-graphics
```
and then rerun autoreconf from the top directory.
```sh
$ cd /path/to/kana-edit
$ autoreconf --install
```
#### Error while loading shared libraries ... No such file or directory
This means that you've successfully compiled the program, but the program can't find your SFML libraries.

There are at least two ways to fix this. The first is to simply copy the libraries (or symlink them) to the directory containing the kanaedit binary. The second way is to add your lib path to a shell variable:
```sh
$ LD_LIBRARY_PATH=/path/to/sfml/libraries
$ echo $LD_LIBRARY_PATH
$ export LD_LIBRARY_PATH
```
Then try runing the program again.

# Other Issues
Report issues/bugs/feature requests on the [GitHub issues tab](https://github.com/dseguin/kana-edit/issues).
