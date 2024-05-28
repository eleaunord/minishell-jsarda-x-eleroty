#include <stdio.h>

int main(int ac, char *argv[], char *envp[]) {
	puts("Doing something here");
	int i;
	for (i = 0; envp[i]; ++i)
		puts(envp[i]);
	printf("Finished printing %d envs\n", i);
}
