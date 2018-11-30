#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void tratarAlarm(int);

int main(int argc, char const *argv[])
{
    signal(SIGALRM,tratarAlarm);

    int i = 0;
    alarm(15);
    while (i<100){
        printf("%d\n",++i);
        sleep(10);
    }
    return 0;
}

void tratarAlarm(int numSenyal){
    printf("Alarma!");
}