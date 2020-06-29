#include <common.h>

int disable_stashing() {
	int ret;

	ret = open("/mnt/.cydia_no_stash", O_WRONLY | O_CREAT, 0);
	if (ret < 0) {
		return -1;
	}
	close(ret);

	return 0;
}