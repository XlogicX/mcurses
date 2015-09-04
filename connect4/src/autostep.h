#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <X11/extensions/XTest.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/stat.h>

//Uses the existence of a file as a mutex. I had troubles
//with a real mutex with a forked string
int FileExists(const char *filename) {
    struct stat st;
    int result = stat(filename, &st);
    return result == 0;
}

void * autostep(void *delay){
 	Display *display;
 	unsigned int keycode;
 	display = XOpenDisplay(NULL);
 	while (1) {
 		if (FileExists("filetex")) {	//if the 'mutex exists'
 			remove("filetex");			//remove it
 			return(0);						//but exit the loop
 		}
		usleep(*((int *)delay));
		keycode = XKeysymToKeycode(display, XK_F9);
		XTestFakeKeyEvent(display, keycode, True, 0);
		XTestFakeKeyEvent(display, keycode, False, 0);
		XFlush(display);
	}
}
