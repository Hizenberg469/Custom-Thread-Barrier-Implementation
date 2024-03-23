#include <unistd.h>
#include <stdio.h>
#include "ThreadBarrier.h"


static th_barrier_t barrier;
static pthread_t thread_pool[3];

static const char* th1 = "TH1";
static const char* th2 = "TH2";
static const char* th3 = "TH3";


void*
thread_fn_callback(void* arg) {
	
	thread_barrier_wait(&barrier);

	printf("1st Barricade cleared by thread %s\n", (char*)arg);

	thread_barrier_wait(&barrier);

	printf("2st Barricade cleared by thread %s\n", (char*)arg);

	thread_barrier_wait(&barrier);

	printf("3st Barricade cleared by thread %s\n", (char*)arg);
}

void
create_thread(pthread_t* th, void* arg) {

	pthread_create(th,
		NULL,
		thread_fn_callback,
		arg);

}
int
main(int argc, char* argv[]) {

	thread_barrier_init(&barrier, 3);

	create_thread(&thread_pool[0], (void*)th1);
	create_thread(&thread_pool[1], (void*)th2);
	create_thread(&thread_pool[2], (void*)th3);

	pthread_join(thread_pool[0], NULL);
	pthread_join(thread_pool[1], NULL);
	pthread_join(thread_pool[2], NULL);

	thread_barrier_print(&barrier);

	return 0;
}