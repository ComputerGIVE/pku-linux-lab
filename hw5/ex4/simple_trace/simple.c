#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define _STR(x) #x
#define STR(x) _STR(x)
#define MAX_PATH 256

char *find_debugfs(void)
{
       static char debugfs[MAX_PATH+1];
       static int debugfs_found;
       char type[100];
       FILE *fp;

       if (debugfs_found)
	       return debugfs;

       if ((fp = fopen("/proc/mounts","r")) == NULL) {
	       perror("/proc/mounts");
	       return NULL;
       }

       while (fscanf(fp, "%*s %"
	             STR(MAX_PATH)
	             "s %99s %*s %*d %*d\n",
	             debugfs, type) == 2) {
	       if (strcmp(type, "debugfs") == 0)
	               break;
       }
       fclose(fp);

       if (strcmp(type, "debugfs") != 0) {
	       fprintf(stderr, "debugfs not mounted");
	       return NULL;
       }

       /* strcat(debugfs, "/tracing/"); */ 
       debugfs_found = 1;

       return debugfs;
}

const char *tracing_file(const char *file_name)
{
       static char trace_file[MAX_PATH+1];
       snprintf(trace_file, MAX_PATH, "%s/%s", find_debugfs(), file_name);
       return trace_file;
}

int main (int argc, char **argv)
{
	struct timespec req; 
	char *debugfs;
	char path[256];
	int marker_fd, trace_fd; 
	
	req.tv_sec = 0; 
	req.tv_nsec = 1000; 
	/* sleep for 1000 nanoseconds = 1 us */

	debugfs = find_debugfs();
	printf("%s\n", debugfs); 
	if (debugfs) {
		strcpy(path, debugfs);
		strcat(path,"/tracing/tracing_on");
		trace_fd = open(path, O_WRONLY);
		if (trace_fd >= 0)
			write(trace_fd, "1", 1);

		strcpy(path, debugfs);
		strcat(path,"/tracing/trace_marker");
		marker_fd = open(path, O_WRONLY);

		write(marker_fd, "before nano\n", 12); 
		nanosleep(&req, NULL); 
		write(marker_fd, "after nano\n", 11); 
		write(trace_fd, "0", 1); 
	} else {
		printf("Fatal error: No debugfs found! \n"); 
	}
	return 0;
}
