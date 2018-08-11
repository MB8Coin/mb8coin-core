Mac OS X Build Instructions and Notes
====================================
The commands in this guide should be executed in a Terminal application.
The built-in one is located in `/Applications/Utilities/Terminal.app`.

Preparation
-----------
Install the OS X command line tools:

`xcode-select --install`

When the popup appears, click `Install`.

Then install [Homebrew](http://brew.sh).

Dependencies
----------------------

    brew install automake berkeley-db4 libtool boost@1.57 --c++11 miniupnpc openssl pkg-config protobuf@2.6 qt5 libevent curl

NOTE: Building with Qt4 is still supported, however, could result in a broken UI. Building with Qt5 is recommended.

Make sure you link boost if you have another version installed

```
    brew unlink boost
    brew link boost@1.57 --force
```

Build MB8Coin Core
------------------------

1. Clone the mb8coin source code and cd into `mb8coin`

        git clone https://github.com/MB8Coin/mb8coin-core.git
        cd mb8coin-core

2.  Build mb8coin-core:

    Configure and build the headless mb8coin binaries as well as the GUI (if Qt is found).

    You can disable the GUI build by passing `--without-gui` to configure.

        ./autogen.sh
        ./configure
        make

3.  It is recommended to build and run the unit tests:

        make check

4.  You can also create a .dmg that contains the .app bundle (optional):

        make deploy

Running
-------

MB8Coin Core is now available at `./src/mb8coind`

Before running, it's recommended you create an RPC configuration file.

    echo -e "rpcuser=mb8coinrpc\nrpcpassword=$(xxd -l 16 -p /dev/urandom)" > "/Users/${USER}/Library/Application Support/MB8Coin/mb8coin.conf"

    chmod 600 "/Users/${USER}/Library/Application Support/MB8Coin/mb8coin.conf"

The first time you run mb8coind, it will start downloading the blockchain. This process could take several hours.

You can monitor the download process by looking at the debug.log file:

    tail -f $HOME/Library/Application\ Support/MB8Coin/debug.log

Other commands:
-------

    ./src/mb8coind -daemon # Starts the mb8coin daemon.
    ./src/mb8coin-cli --help # Outputs a list of command-line options.
    ./src/mb8coin-cli help # Outputs a list of RPC commands when the daemon is running.

Using Qt Creator as IDE
------------------------
You can use Qt Creator as an IDE, for mb8coin development.
Download and install the community edition of [Qt Creator](https://www.qt.io/download/).
Uncheck everything except Qt Creator during the installation process.

1. Make sure you installed everything through Homebrew mentioned above
2. Do a proper ./configure --enable-debug
3. In Qt Creator do "New Project" -> Import Project -> Import Existing Project
4. Enter "mb8coin-qt" as project name, enter src/qt as location
5. Leave the file selection as it is
6. Confirm the "summary page"
7. In the "Projects" tab select "Manage Kits..."
8. Select the default "Desktop" kit and select "Clang (x86 64bit in /usr/bin)" as compiler
9. Select LLDB as debugger (you might need to set the path to your installation)
10. Start debugging with Qt Creator

QT and Mac OS Sierra
--------------------

Installing QT through brew in MacOS Sierra could fail during compilation.

https://github.com/Homebrew/homebrew-core/pull/9297

Use the following commands to install Qt 5.7 under MacOS Sierra using a different formula.

    chown root /usr/local/bin/brew
    sudo brew update
    sudo chown -R $USER /usr/local
    brew install qt@5.7

Notes
-----

* Tested on OS X 10.7 through 10.13.3 on 64-bit Intel processors only.

* Building with downloaded Qt binaries is not officially supported. See the notes in [#7714](https://github.com/mb8coin/mb8coin/issues/7714)
