#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <sys/signal.h>

#include <time.h>

pid_t pid;

void PrintHelp(char * name, FILE * _file);

void kill_child(int a){
	kill(pid, SIGKILL);
}

int main(int argc, char * argv[]){
	if(argc < 3){
		fprintf(stderr, "Error!!! Inadequate number of arguments!\n\n");
		PrintHelp(argv[0], stderr);
		return EXIT_FAILURE;
	}

	long int	_time_s	= atoi(argv[1]);

	if (_time_s < 0){
		fprintf(stderr, "Error!!! Time to kill child process set to negative!\n");
		return EXIT_FAILURE;
	}

	printf("Time set to work child process: %li (s)\n", _time_s);

	pid = fork();

	if (pid < 0){
		fprintf(stderr, "Error!!! Can not create process copy!\n");
		return EXIT_FAILURE;
	}
	else if(!pid) {
		if (execv(argv[2], (argv + 2)) == -1){
			perror(argv[2]);
		}
	}
	else{
		if (!_time_s){
			kill(pid, SIGKILL);
		}
		else{
			if (sigaction(SIGALRM, NULL, NULL) == -1){
				fprintf(stderr, "Error!!! Cannot create signal action!\n");
			}
			signal(SIGALRM, kill_child); // assigning an alarm handler for SIGALRM
			alarm(_time_s);
		}
		time_t begin_time	= time(NULL);

		waitpid(pid, NULL, 0);

		time_t end_time		= time(NULL);

		printf("\nExecution time of child process %s: %u\n", argv[2], (unsigned)(end_time - begin_time));
	}

	return EXIT_SUCCESS;
}

void PrintHelp(char * name, FILE * _file){
	char * _n = strrchr(name, '/');
	fprintf(_file,
		"\tUsage: %s <time to kill child> <name child>\n\n",
		_n ? ++_n : name
	);
}