#include <launch_daemons.h>


void load_launch_daemons() {
	system("ls /Library/LaunchDaemons | while read a; do launchctl load /Library/LaunchDaemons/$a; done;");
	system("for file in /etc/rc.d/*; do $file; done;");
	system("launchctl unload /Library/LaunchDaemons/com.openssh.sshd.plist;/usr/libexec/sshd-keygen-wrapper"); // Hack to load openssh
}
