#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>
#include <sys/wait.h>

void catchint(int signo);

int main(){
    int i, j, num[10], sum = 0;
    sigset_t mask;

    static struct sigaction act;
    act.sa_handler = catchint;
    sigaction(SIGINT, &act, NULL);

    sigemptyset(&mask);
    sigaddset(&mask, SIGINT);

    for(i=0;i<5;i++){
        sigprocmask(SIG_SETMASK, &mask, NULL);
        // sigprocmask(SIG_BLOCK, &mask, NULL);
	scanf("%d", &num[i]);
        sigprocmask(SIG_UNBLOCK, &mask, NULL);

        sum+=num[i];

        for(j=0;j<=i;j++){
            printf("... %d\n", num[j]);
            sleep(1);
        }
    }

    printf("sum = %d\n", sum);
    exit(0);
}

void catchint(int signo){
    printf("DO NOT INTERRUPT ... \n");
}