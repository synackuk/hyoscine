#include <remount.h>
#include <kernel.h>


static int hfs_mount(char* device, const char* mountdir, int options) {
	struct hfs_mount_args args;
	args.fspec = device;
	return mount("hfs", mountdir, options, &args);
}

static uint32_t find_v_mount() {
	static uint8_t kernel_dump[KERNEL_DUMP_SIZE + IMAGE_OFFSET] = {0};
	uint32_t kernel_base_address = get_kernel_region(get_kernel_task());
	if(!kernel_base_address) {
		return 0;
	}
	if(*(uint32_t*)kernel_dump != 0xFEEDFACE) {
		dump_kernel(get_kernel_task(), kernel_base_address, kernel_dump);
	}
	char* boot_args = (char*)kern_bootargs();
	uint32_t rootvnode_offset;
	char* rootvnode_boot_arg = strstr(boot_args, "rootvnode_addr=");
	if(!rootvnode_boot_arg) {
		return 0;
	}
	sscanf(rootvnode_boot_arg, "rootvnode_addr=%x", &rootvnode_offset);
	if(!rootvnode_offset) {
		return 0;
	}
	uint32_t rootfs_vnode = *(uint32_t*)&kernel_dump[rootvnode_offset];
	uint32_t vnode_mount = rk32(rootfs_vnode + KSTRUCT_OFFSET_VNODE_V_UN);
	if(!vnode_mount) {
		return 0;
	}
	return vnode_mount;

}

static uint32_t get_vfs_flags() {
	uint32_t vnode_mount = find_v_mount();
	if(!vnode_mount) {
		return 0;
	}
	uint32_t vfs_flags = rk32(vnode_mount + KSTRUCT_OFFSET_MOUNT_MNT_FLAG + 1);
	return vfs_flags;
}

static int set_vfs_flags(uint32_t vfs_flags) {
	uint32_t vnode_mount = find_v_mount();
	if(!vnode_mount) {
		return -1;
	}
	return wk32(vnode_mount + KSTRUCT_OFFSET_MOUNT_MNT_FLAG + 1, vfs_flags);
}

int do_remount() {
	int ret = 0;
	uint32_t vfs_flags = get_vfs_flags();
	if(!vfs_flags) {
		printf("Failed to get vfs_flags\n");
		return -1;
	}
	ret = set_vfs_flags(vfs_flags & ~(MNT_ROOTFS >> 8));
	if(ret != 0) {
		printf("Failed to set vfs_flags\n");
		return -1;
	}

	ret = hfs_mount(strdup("/dev/disk0s1s1"), "/", MNT_UPDATE);
	if(ret != 0) {
		printf("Failed remount\n");
		return -1;
	}

	ret = set_vfs_flags(vfs_flags);
	if(ret != 0) {
		printf("Failed to reset vfs_flags\n");
		return -1;
	}

	return 0;
}