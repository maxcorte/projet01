#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>


struct philosophe_arg
{
	int id;
	int PHILOSOPHES;
	pthread_mutex_t *baguette;
};


void mange(int id) {
}

void* philosophe ( void* arg)
{	
	struct philosophe_arg *args = (struct philosophe_arg*) arg;
	int id = args->id;
	int PHILOSOPHES = args->PHILOSOPHES;
	pthread_mutex_t *baguette = args->baguette;
	int left;
	int right;
	if(id == 0){
		left = id;
		right = PHILOSOPHES-1;
	}else{
		left = id - 1;
		right = id;
	}
	

	int count = 0;
	while(count < 1000000) {
		pthread_mutex_lock(&baguette[left]);
		pthread_mutex_lock(&baguette[right]);
		mange(id);
		pthread_mutex_unlock(&baguette[left]);
		pthread_mutex_unlock(&baguette[right]);
		count++;
	}

	free(args);
	return (NULL);
}


int main(int argc, char *argv[]){
	int err;

	int PHILOSOPHES = atoi(argv[1]);

	pthread_t phil[PHILOSOPHES];
	pthread_mutex_t baguette[PHILOSOPHES];


	for(int i=0;i<PHILOSOPHES;i++){
		err=pthread_mutex_init(&baguette[i], NULL);
		if(err!=0)
			perror("pthread_mutex_init");
	}



	for(int i=0;i<PHILOSOPHES;i++) {
		struct philosophe_arg *arg = malloc(sizeof(struct philosophe_arg));
	
		arg->id = i;
		arg->PHILOSOPHES = PHILOSOPHES;
		arg->baguette = baguette;
		
		err=pthread_create(&(phil[i]),NULL,&philosophe,arg);
		if(err!=0)
			perror("pthread_create");
	}

	for(int i=PHILOSOPHES-1;i>=0;i--) {
		err=pthread_join(phil[i],NULL);
		if(err!=0)
			perror("pthread_join");
	}

	for(int i=0;i<PHILOSOPHES;i++){
		err=pthread_mutex_destroy(&baguette[i]);
			if(err!=0)
				perror("pthread_mutex_destroy");
	}

	return 0;
}
