#include <common.h>

int install_jb_init() {
	int ret;

	unlink("/mnt/usr/libexec/rtbuddyd");
	
	ret = install("/modules/jb_init", "/mnt/usr/libexec/rtbuddyd", 0, 0, 0755);
	if(ret != 0) {
		return -1;
	}
	ret = install("/files/com.n1ghtshade.rtbuddyd.plist", "/mnt/System/Library/LaunchDaemons/com.n1ghtshade.rtbuddyd.plist", 0, 80, 0644);
	if(ret != 0) {
		return -1;
	}
	return 0;
}