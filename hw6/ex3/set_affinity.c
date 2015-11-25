#define _GNU_SOURCE
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char * const argv[])
{
	int n0 = 0, n1 = 0; 
	int pid = 0, opt; 
	cpu_set_t set; 

	while ((opt = getopt(argc, argv, "01p:")) != -1) {
		switch (opt) {
		case '0':
			n0 = 1;
			break;
		case '1':
			n1 = 1;
			break;
		case 'p':
			pid = atoi(optarg);
			break;
		default: /* '?' */
			fprintf(stderr, "Usage: %s [-0 -1] -p pid\n",
				argv[0]);
			exit(EXIT_FAILURE);
	 	}
	}
	if (!pid || n0 + n1 == 0){
		fprintf(stderr, "Usage: %s [-0 -1] -p pid\n",
			argv[0]);
		exit(EXIT_FAILURE);
	}

	CPU_ZERO(&set); 
	if (n0)
		CPU_SET(0, &set); 
	if (n1)
		CPU_SET(1, &set); 
	
	if (!sched_setaffinity(pid, sizeof(cpu_set_t), &set)){
		printf("Affinity successfully set!\n"); 
	} else 
		printf("Error!\n"); 
}

