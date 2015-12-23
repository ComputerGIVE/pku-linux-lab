#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <linux/prctl.h>

int main()
{
	int ans;
	ans = prctl(PR_TASK_PERF_EVENTS_DISABLE);
	printf("%d\n", ans); 
	ans = prctl(PR_TASK_PERF_EVENTS_ENABLE);
	printf("%d\n", ans); 
	return 0; 
}
