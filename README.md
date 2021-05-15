# C program compilation tool

A simple to use linux command that will help you compile faster your c language source files.

## Description

The main reason I created this script is that I always compile c programs in a safe manner and it takes some time to always rewrite 
the gcc command in this manner, using the flags "-Wall -Wextra" and also all the time I preffer the binary file to be named after
the main source file so I also always include "-o name_of_source_file".

Therefore this script is using these flags by default and as a consequence the first provided source file will give the name of the
executable file. Also you can specify additional gcc flags to be used in compilation and also multiple source files.

## Installation

First you should make sure that you have the [gcc](https://gcc.gnu.org/) compiler installed on your machine (the only dependency).

On Debian Based Linux systems:
```bash
sudo apt install gcc
```

Then you should navigate to the folder where you cloned this repository and move the executable to a path visible location like:
```bash
sudo cp compileFaster/compile /usr/local/bin/
```

##Usage

Now the you should be able to use this script from anywhere on your machine.

Example:
```bash
compile main_source_file.c -lpthread secondary_source_file.c
```

#Contributing

I am open to contributions, if you want to add some cool features to this script, please feel free to make a pull request.

#License

This project is licensed under [MIT](https://choosealicense.com/licenses/mit/).
