RM = rm
CC = `xcrun -find cc`
STRIP = `xcrun -find strip`
LDID = ldid
SYSROOT = $(THEOS)/sdks/iPhoneOS7.1.sdk
OBJECTS = syscalls.o launchd.o common.o install.o modules/disable_stashing.o modules/jb_init.o modules/launchctl.o modules/n1ghtshade_app.o  modules/non_default_apps.o
CFLAGS = -I. -arch armv6 -static -nodefaultlibs -nostdlib -isysroot$(SYSROOT) -I$(SYSROOT) -fno-stack-protector
LDFLAGS = -arch armv6 -Wl,-e,_main -Wl,-no_pie -nostartfiles

all: launchd
	@echo STRIP launchd
	@$(STRIP) launchd
	@$(LDID) -Sent.xml launchd

clean:
	@$(RM) -rf *.o
	@$(RM) -rf modules/*.o
	@$(RM) -rf launchd

launchd: $(OBJECTS)
	@echo CC -c $(<) -o $(@)
	@$(CC) -o launchd $(OBJECTS) $(CFLAGS) $(LDFLAGS)

%.o: %.c
	@$(CC) $(CFLAGS) -c $(<) -o $(@)

%.o: %.S
	@$(CC) $(CFLAGS) -c $(<) -o $(@)