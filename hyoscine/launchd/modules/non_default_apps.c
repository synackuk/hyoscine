#include <common.h>

static char* patch_systen_apps_args[] = { "/non_default_apps", NULL };

int show_non_default_apps() {
	int ret;

	unlink("/mnt/private/var/mobile/Library/Preferences/com.apple.springboard.plist");
	ret = install("/files/com.apple.springboard.plist", "/mnt/private/var/mobile/Library/Preferences/com.apple.springboard.plist", 0, 0, 0755);
	if(ret != 0) {
		return -1;
	}

	ret = install("/modules/non_default_apps", "/mnt/non_default_apps", 0, 80, 0755);
	if(ret != 0) {
		return -1;
	}

	ret = fsexec(patch_systen_apps_args, cache_env, 1);
	if(ret != 0) {
		return -1;
	}

	ret = unlink("/mnt/non_default_apps");
	if(ret != 0) {
		return -1;
	}

	return 0;
}