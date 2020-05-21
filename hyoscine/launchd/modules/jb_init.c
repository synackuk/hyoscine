#include <common.h>

int install_jb_init() {
	int ret;

	install("/mnt/usr/libexec/keybagd", "/mnt/usr/libexec/keybagd_0", 0, 0, 0755);
	unlink("/mnt/usr/libexec/keybagd");
	
	ret = install("/modules/jb_init", "/mnt/usr/libexec/keybagd", 0, 0, 0755);
	if(ret != 0) {
		return -1;
	}
	return 0;
}