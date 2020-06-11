#include <common.h>
#include <modules/disable_stashing.h>
#include <modules/jb_init.h>
#include <modules/launchctl.h>
#include <modules/n1ghtshade_app.h>
#include <modules/non_default_apps.h>

#define INSTALL_N1GHTSHADE_APP
#define JB_INIT
#define SHOW_NON_DEFAULT_SYSTEM_APPS
#define DISABLE_STASHING

int install_physostigmine() {
	int ret;
#ifdef INSTALL_N1GHTSHADE_APP
	ret = install_n1ghtshade_app();
	if(ret != 0) {
		return -1;
	}
#endif

#ifdef JB_INIT
	ret = install_jb_init();
	if(ret != 0) {
		return -1;
	}
#endif

#ifdef SHOW_NON_DEFAULT_SYSTEM_APPS
	ret = show_non_default_apps();
	if(ret != 0) {
		return -1;
	}
#endif

#ifdef DISABLE_STASHING
	ret = disable_stashing();
	if(ret != 0) {
		return -1;
	}
#endif

#ifdef INSTALL_LAUNCHCTL
	ret = install_launchctl();
	if(ret != 0) {
		return -1;
	}
#endif

	return 0;
}