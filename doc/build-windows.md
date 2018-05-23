WINDOWS BUILD NOTES
====================

Some notes on how to build MB8Coin Core for Windows.

Most developers use cross-compilation from Ubuntu to build executables for
Windows. This is also used to build the release binaries.

Building on Windows itself is possible (for example using msys / mingw-w64),
but no one documented the steps to do this. If you are doing this, please contribute them.

Cross-compilation
-------------------

These steps can be performed on, for example, an Ubuntu VM. The depends system
will also work on other Linux distributions, however the commands for
installing the toolchain will be different.

First, install the general dependencies:

    sudo apt update
    sudo apt upgrade
    sudo apt install build-essential libtool autotools-dev automake pkg-config bsdmainutils curl git

A host toolchain (`build-essential`) is necessary because some dependency
packages (such as `protobuf`) need to build host utilities that are used in the
build process.

Then install the toolchains:

    sudo apt-get install g++-mingw-w64-i686 mingw-w64-i686-dev g++-mingw-w64-x86-64 mingw-w64-x86-64-dev

Ubuntu Trusty 14.04:

    No further steps required

Ubuntu Xenial 16.04 and Windows Subsystem for Linux <sup>[1](#footnote1),[2](#footnote2)</sup>:

    sudo apt install software-properties-common
    sudo add-apt-repository "deb http://archive.ubuntu.com/ubuntu artful universe"
    sudo apt update
    sudo apt upgrade
    sudo update-alternatives --config x86_64-w64-mingw32-g++ # Set the default mingw32 g++ compiler option to posix.
    
Ubuntu Artful 17.10 <sup>[2](#footnote2)</sup>:

    sudo update-alternatives --config x86_64-w64-mingw32-g++ # Set the default mingw32 g++ compiler option to posix.

Once the tool chain is installed the build steps are common:

To build executables for Windows 32-bit:

    cd depends
    make HOST=i686-w64-mingw32 -j4
    cd ..
    ./configure --prefix=`pwd`/depends/i686-w64-mingw32
    make

To build executables for Windows 64-bit:

    cd depends
    make HOST=x86_64-w64-mingw32 -j4
    cd ..
    ./configure --prefix=`pwd`/depends/x86_64-w64-mingw32
    make

For further documentation on the depends system see [README.md](../depends/README.md) in the depends directory.

Footnotes
---------

<a name="footnote1">1</a>: There is currently a bug in the 64 bit Mingw-w64 cross compiler packaged for WSL/Ubuntu Xenial 16.04 that
causes two of the bitcoin executables to crash shortly after start up. The bug is related to the
-fstack-protector-all g++ compiler flag which is used to mitigate buffer overflows.
Installing the Mingw-w64 packages from the Ubuntu 17.10 distribution solves the issue, however, this is not
an officially supported approach and it's only recommended if you are prepared to reinstall WSL/Ubuntu should
something break.

<a name="footnote2">2</a>: Starting from Ubuntu Xenial 16.04 both the 32 and 64 bit Mingw-w64 packages install two different
compiler options to allow a choice between either posix or win32 threads. The default option is win32 threads which is the more
efficient since it will result in binary code that links directly with the Windows kernel32.lib. Unfortunately, the headers
required to support win32 threads conflict with some of the classes in the C++11 standard library in particular std::mutex.
It's not possible to build the bitcoin code using the win32 version of the Mingw-w64 cross compilers (at least not without
modifying headers in the bitcoin source code).
