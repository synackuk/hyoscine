#include <common.h>

int show_non_default_apps() {
	int ret;

	unlink("/mnt/private/var/mobile/Library/Preferences/com.apple.springboard.plist");
	ret = install("/files/com.apple.springboard.plist", "/mnt/private/var/mobile/Library/Preferences/com.apple.springboard.plist", 0, 0, 0755);
	if(ret != 0) {
		return -1;
	}

	return 0;
}