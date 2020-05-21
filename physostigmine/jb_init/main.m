#include <launch_daemons.h>
#include <remount.h>
#include <sandbox.h>
#include <kernel.h>
#include <stdio.h>
#include <sys/stat.h>

int main(int argc, char *argv[], char *envp[]) {
	int ret;
	int console = open("/dev/console", O_WRONLY);
	dup2(console, 1);
	dup2(console, 2);

	printf("n1ghtshade jb loader by synackuk\n");

	printf("Initialising kernel.\n");

	ret = init_kernel();
	if(ret != 0) {
		printf("Failed to initialise kernel\n");
		execv("/usr/libexec/keybagd_0", argv);
		return -1;
	}

	printf("Remounting filesystems.\n");

	ret = do_remount();
	if(ret != 0) {
		printf("Failed to remount filesystems\n");
		execv("/usr/libexec/keybagd_0", argv);
		return -1;
	}

	printf("Launching daemons.\n");

	load_launch_daemons();

	printf("Done.\n");

	close(console);
	execv("/usr/libexec/keybagd_0", argv);
	return 0;
}
