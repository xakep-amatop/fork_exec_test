#include <stdio.h>

#include <unistd.h>

#define _t_interval (50000) // sleep 100 ms

int main(){
	long unsigned	_time	= 0;
	size_t	counter	= 20;
	while(1){
		if (!counter){
			printf("sleep time : %10.3f (s)\n", (float)_time / 1000000);
			fflush(stdout);
			counter = 20;
		}
		usleep(_t_interval);
		_time += _t_interval;
		--counter;

		if (_time > 2000000){
			break;
		}
	}
	return 0;
}