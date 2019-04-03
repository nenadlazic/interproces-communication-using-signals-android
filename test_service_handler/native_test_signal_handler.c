#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<signal.h>
#include<mntent.h>
#include<android/log.h>

#define LOG_TAG "test_service_handler"

#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
#define  LOGW(...)  __android_log_print(ANDROID_LOG_WARN,LOG_TAG,__VA_ARGS__)
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)

void signalHandler(int signum, siginfo_t *info, void *extra);


void signalHandler(int signum, siginfo_t *info, void *extra)
{
    void *ptr_val = info->si_value.sival_ptr;
    int int_val = info->si_value.sival_int;

    if (signum == SIGUSR1)
    {
	LOGE("signalHandler called");
    }
}

void *test_service(void *vargp)
{
    struct sigaction action;
    action.sa_flags = SA_SIGINFO;
    action.sa_sigaction = &signalHandler;
    if (sigaction(SIGUSR1, &action, NULL) == -1) {
	LOGE("sigusr: sigaction failed\n");
    }else{
	LOGE("sigusr: sigaction ok");
    }

    while(1)
    {
	sleep(1);
        LOGE("DEBUG test_service running");
	printf("running");
    }

    return NULL;
}

int main()
{
    pthread_t thread_id;
    LOGE("test_service before start thread");
    pthread_create(&thread_id, NULL, test_service, NULL);
    pthread_join(thread_id, NULL);
    LOGE("test_service after join thread");

    exit(0);
}

