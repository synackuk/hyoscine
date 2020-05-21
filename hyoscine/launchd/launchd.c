#include <common.h>
#include <hfs_mount.h>
#include <install.h>

int console;

char* fsck_system_args[] = { "/sbin/fsck_hfs", "-fy", "/dev/rdisk0s1s1", NULL };

__attribute__((noreturn)) void done(int should_reboot) {
	sync();
	puts("Unmounting filesystem\n");
	unmount("/mnt/dev", 0);
	unmount("/mnt", 0);
	puts("Flushing buffers\n");
	sync();
	if(should_reboot) {
		puts("Rebooting\n");
		close(console);
		reboot(1);
	}
	while(1){}
}

int main(int argc, char** argv, char** env) {
	int ret;
	struct stat status;

	console = open("/dev/console", O_WRONLY);
	dup2(console, 1);
	dup2(console, 2);

	puts("Running hyoscine\n");

	while (stat("/dev/disk0s1s1", &status) != 0) {
		puts("Waiting for disk\n");
		sleep(1);
	}

	puts("Mounting filesystem r/o\n");
	
	ret = hfs_mount("/dev/disk0s1s1", "/mnt", MNT_ROOTFS | MNT_RDONLY);
	if(ret != 0) {
		puts("Failed to mount filesystem r/o\n");
		done(0);
	}

	puts("Mounting dev filesystem\n");
	
	ret = mount("devfs", "/mnt/dev", 0, NULL);
	if(ret != 0) {
		puts("Failed to mount dev filesystem\n");
		done(0);
	}


	puts("Checking filesystem\n");

	ret = fsexec(fsck_system_args, cache_env, 1);
	if(ret != 0) {
		puts("Failed to check filesystem\n");
		done(0);
	}

	puts("Mounting filesystem r/w\n");

	ret = hfs_mount("/dev/disk0s1s1", "/mnt", MNT_ROOTFS | MNT_UPDATE);
	if(ret != 0) {
		puts("Failed to mount filesystem r/w\n");
		done(0);
	}

	puts("Installing physostigmine\n");

	ret = install_physostigmine();
	if(ret != 0) {
		puts("Failed to install physostigmine\n");
		done(0);
	}

	puts("Installed physostigmine\n");

	done(1);

	return 0;
}