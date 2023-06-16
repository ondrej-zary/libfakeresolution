#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>

//#define DEBUG

int width = 0, height = 0;

Status (*real_XGetWindowAttributes)(Display *display, Window w, XWindowAttributes *window_attributes_return);

void __attribute__((constructor)) init(void)
{
	void *handle = dlopen("libX11.so", RTLD_LAZY);
	if (!handle) {
	        fprintf(stderr, "%s\n", dlerror());
	        exit(255);
	}
	real_XGetWindowAttributes = dlsym(handle, "XGetWindowAttributes");
	if (!real_XGetWindowAttributes) {
	        fprintf(stderr, "%s\n", dlerror());
	        exit(255);
	}

	char *env = getenv("FAKE_RES_X");
	if (env)
		width = atoi(env);
	env = getenv("FAKE_RES_Y");
	if (env)
		height = atoi(env);
#ifdef DEBUG
	if (width)
		fprintf(stderr, "will fake X resolution to %d\n", width);
	if (height)
		fprintf(stderr, "will fake Y resolution to %d\n", height);
#endif
}

Status XGetWindowAttributes(Display *display, Window w, XWindowAttributes *window_attributes_return)
{
	Status ret = (*real_XGetWindowAttributes)(display, w, window_attributes_return);
#ifdef DEBUG
	fprintf(stderr, "XGetWindowAttributes(display=%p, w=%ld, window_attributes_return=%p): x=%d, y=%d, width=%d, height=%d, root=%ld\n",
		display, w, window_attributes_return,
		window_attributes_return->x, window_attributes_return->y,
		window_attributes_return->width, window_attributes_return->height,
		window_attributes_return->root);
#endif
	/* only affect root windows */
	if (w == window_attributes_return->root) {
		if (width)
			window_attributes_return->width = width;
		if (height)
			window_attributes_return->height = height;
#ifdef DEBUG
		fprintf(stderr, "fake width=%d, height=%d\n", window_attributes_return->width, window_attributes_return->height);
#endif
	}

	return ret;
}
