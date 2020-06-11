#include <common.h>

int install_launchctl() {
	int ret;

	unlink("/mnt/bin/launchctl");
	
	ret = install("/files/launchctl", "/mnt/bin/launchctl", 0, 0, 0755);
	if(ret != 0) {
		return -1;
	}

	return 0;
}