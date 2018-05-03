Sample init scripts and service configuration for mb8coind
==========================================================

Sample scripts and configuration files for systemd, Upstart and OpenRC
can be found in the contrib/init folder.

    contrib/init/mb8coind.service:    systemd service unit configuration
    contrib/init/mb8coind.openrc:     OpenRC compatible SysV style init script
    contrib/init/mb8coind.openrcconf: OpenRC conf.d file
    contrib/init/mb8coind.conf:       Upstart service configuration file
    contrib/init/mb8coind.init:       CentOS compatible SysV style init script

1. Service User
---------------------------------

All three Linux startup configurations assume the existence of a "mb8coin" user
and group.  They must be created before attempting to use these scripts.
The OS X configuration assumes mb8coind will be set up for the current user.

2. Configuration
---------------------------------

At a bare minimum, mb8coind requires that the rpcpassword setting be set
when running as a daemon.  If the configuration file does not exist or this
setting is not set, mb8coind will shutdown promptly after startup.

This password does not have to be remembered or typed as it is mostly used
as a fixed token that mb8coind and client programs read from the configuration
file, however it is recommended that a strong and secure password be used
as this password is security critical to securing the wallet should the
wallet be enabled.

If mb8coind is run with the "-server" flag (set by default), and no rpcpassword is set,
it will use a special cookie file for authentication. The cookie is generated with random
content when the daemon starts, and deleted when it exits. Read access to this file
controls who can access it through RPC.

By default the cookie is stored in the data directory, but it's location can be overridden
with the option '-rpccookiefile'.

This allows for running mb8coind without having to do any manual configuration.

`conf`, `pid`, and `wallet` accept relative paths which are interpreted as
relative to the data directory. `wallet` *only* supports relative paths.

For an example configuration file that describes the configuration settings,
see `contrib/debian/examples/mb8coin.conf`.

3. Paths
---------------------------------

3a) Linux

All three configurations assume several paths that might need to be adjusted.

Binary:              `/usr/bin/mb8coind`  
Configuration file:  `/etc/mb8coin/mb8coin.conf`  
Data directory:      `/var/lib/mb8coind`  
PID file:            `/var/run/mb8coind/mb8coind.pid` (OpenRC and Upstart) or `/var/lib/mb8coind/mb8coind.pid` (systemd)  
Lock file:           `/var/lock/subsys/mb8coind` (CentOS)  

The configuration file, PID directory (if applicable) and data directory
should all be owned by the mb8coin user and group.  It is advised for security
reasons to make the configuration file and data directory only readable by the
mb8coin user and group.  Access to mb8coin-cli and other mb8coind rpc clients
can then be controlled by group membership.

3b) Mac OS X

Binary:              `/usr/local/bin/mb8coind`  
Configuration file:  `~/Library/Application Support/MB8Coin/mb8coin.conf`  
Data directory:      `~/Library/Application Support/MB8Coin`
Lock file:           `~/Library/Application Support/MB8Coin/.lock`

4. Installing Service Configuration
-----------------------------------

4a) systemd

Installing this .service file consists of just copying it to
/usr/lib/systemd/system directory, followed by the command
`systemctl daemon-reload` in order to update running systemd configuration.

To test, run `systemctl start mb8coind` and to enable for system startup run
`systemctl enable mb8coind`

4b) OpenRC

Rename mb8coind.openrc to mb8coind and drop it in /etc/init.d.  Double
check ownership and permissions and make it executable.  Test it with
`/etc/init.d/mb8coind start` and configure it to run on startup with
`rc-update add mb8coind`

4c) Upstart (for Debian/Ubuntu based distributions)

Drop mb8coind.conf in /etc/init.  Test by running `service mb8coind start`
it will automatically start on reboot.

NOTE: This script is incompatible with CentOS 5 and Amazon Linux 2014 as they
use old versions of Upstart and do not supply the start-stop-daemon utility.

4d) CentOS

Copy mb8coind.init to /etc/init.d/mb8coind. Test by running `service mb8coind start`.

Using this script, you can adjust the path and flags to the mb8coind program by
setting the MB8COIND and FLAGS environment variables in the file
/etc/sysconfig/mb8coind. You can also use the DAEMONOPTS environment variable here.

4e) Mac OS X

Copy org.mb8coin.mb8coind.plist into ~/Library/LaunchAgents. Load the launch agent by
running `launchctl load ~/Library/LaunchAgents/org.mb8coin.mb8coind.plist`.

This Launch Agent will cause mb8coind to start whenever the user logs in.

NOTE: This approach is intended for those wanting to run mb8coind as the current user.
You will need to modify org.mb8coin.mb8coind.plist if you intend to use it as a
Launch Daemon with a dedicated mb8coin user.

5. Auto-respawn
-----------------------------------

Auto respawning is currently only configured for Upstart and systemd.
Reasonable defaults have been chosen but YMMV.
