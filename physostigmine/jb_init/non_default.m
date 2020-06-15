#import <Foundation/Foundation.h>
#include <sys/sysctl.h>
#include <non_default.h>


int do_non_default() {
	system("killall -SIGSTOP cfprefsd");
	char model[32];
	size_t model_size = sizeof(model);
	sysctlbyname("hw.model", model, &model_size, NULL, 0);
	NSString* sb_plist_path = [NSString stringWithFormat:@"/System/Library/CoreServices/SpringBoard.app/%s.plist", model];
	NSMutableDictionary* sb_plist = [[NSMutableDictionary alloc] initWithContentsOfFile:sb_plist_path];
	if(!sb_plist) {
		return -1;
	}
	[[sb_plist objectForKey:@"capabilities"] setObject:@NO forKey:@"hide-non-default-apps"];
	[sb_plist writeToFile:sb_plist_path atomically:YES];
	system("killall -9 cfprefsd");
	return 0;
}