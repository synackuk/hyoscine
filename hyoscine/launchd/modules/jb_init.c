#include <common.h>

int install_jb_init() {
	int ret;

	unlink("/mnt/usr/libexec/rtbuddyd");
	
	ret = install("/modules/jb_init", "/mnt/usr/libexec/rtbuddyd", 0, 0, 0755);
	if(ret != 0) {
		return -1;
	}
	return 0;
}