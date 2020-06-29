#include <launch_daemons.h>
#include <remount.h>
#include <kernel.h>
#include <stdio.h>
#include <sys/stat.h>

// https://stackoverflow.com/a/2336245

static void mkdir_recursive(const char *dir, int mode) {
	char tmp[256];
	char *p = NULL;
	size_t len;

	snprintf(tmp, sizeof(tmp),"%s",dir);
	len = strlen(tmp);
	if(tmp[len - 1] == '/'){
		tmp[len - 1] = 0;
	}
	for(p = tmp + 1; *p; p++){
		if(*p == '/') {
			*p = 0;
			mkdir(tmp, mode);
			*p = '/';
		}
	}
	mkdir(tmp, mode);
}

int main(int argc, char *argv[], char *envp[]) {
	int ret;
	int console = open("/dev/console", O_WRONLY);
	dup2(console, 1);
	dup2(console, 2);

	if(argc > 1 && !strcmp(argv[1], "-machineBoot")) {
		mkdir_recursive("/var/tmp/launchd", 700);
	}

	printf("n1ghtshade jb loader by synackuk\n");

	printf("Initialising kernel.\n");

	ret = init_kernel();
	if(ret != 0) {
		printf("Failed to initialise kernel\n");
		return -1;
	}

	printf("Remounting filesystems.\n");

	ret = do_remount();
	if(ret != 0) {
		printf("Failed to remount filesystems\n");
		return -1;
	}

	printf("Launching daemons.\n");

	load_launch_daemons();

	printf("Done.\n");


	close(console);
	return 0;
}
