#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <signal.h>

typedef void (*sighandler_t)(int);

void sign_alarm_callback(int signo)
{
	printf("sign alarm ,signal %d\n",signo);	//signo:signal serial number
}

int main()
{
	struct itimerval new_value;
	struct itimerval old_value;
	int ret = 0;
	sighandler_t handler;

	handler = signal(SIGALRM,sign_alarm_callback);	//注册SIGALRM回调函数
	if(handler == SIG_ERR) {
		perror("signal error");
		exit(-1);
	}

	new_value.it_interval.tv_sec = 3;
	new_value.it_interval.tv_usec = 0;
	new_value.it_value.tv_sec = 5;
	new_value.it_value.tv_usec = 0;
	ret = setitimer(ITIMER_REAL,&new_value,&old_value);
	if(ret == -1) {
		perror("setitimer error");
		exit(-1);
	}
	while(1);

	return 0;
}
