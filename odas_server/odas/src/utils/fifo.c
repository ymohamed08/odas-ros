
    #include "fifo.h"

    fifo_obj * fifo_construct_zero(const unsigned int nMaxElements) {

        fifo_obj * obj;

        obj = (fifo_obj *) malloc(sizeof(fifo_obj));

        obj->array = (void **) malloc(sizeof(void *) * nMaxElements);
        memset(obj->array, 0x00, sizeof(void *) * nMaxElements);

        obj->nElements = 0;
        obj->nMaxElements = nMaxElements;

        pthread_mutex_init(&(obj->use), NULL);
        sem_init(&(obj->pop), 0, 0);
        sem_init(&(obj->push), 0, nMaxElements);

        return obj;

    }

    void fifo_destroy(fifo_obj * obj) {

        sem_destroy(&(obj->pop));
        sem_destroy(&(obj->push));
        pthread_mutex_destroy(&(obj->use));
        free((void *) obj->array);
        free((void *) obj);

    }

    void fifo_push(fifo_obj * obj, void * element) {

        sem_wait(&(obj->push));

        pthread_mutex_lock(&(obj->use));

        obj->array[obj->nElements] = element;
        obj->nElements++;

        pthread_mutex_unlock(&(obj->use));

        sem_post(&(obj->pop));

    }

    void * fifo_pop(fifo_obj * obj) {

        void * rtnPtr;

        sem_wait(&(obj->pop));

        pthread_mutex_lock(&(obj->use));

        rtnPtr = obj->array[0];
        memmove(&(obj->array[0]), &(obj->array[1]), (obj->nElements-1) * sizeof(void *));
        obj->nElements--;
        memset(&(obj->array[obj->nElements]), 0x00, (obj->nMaxElements-obj->nElements) * sizeof(void *));

        pthread_mutex_unlock(&(obj->use));

        sem_post(&(obj->push));

        return rtnPtr;

    }

    int fifo_nElements(fifo_obj * obj) {

        int nElements;

        pthread_mutex_lock(&(obj->use));
        nElements = obj->nElements;
        pthread_mutex_unlock(&(obj->use));

        return nElements;

    }

    void fifo_printf(const fifo_obj * obj) {

        unsigned int iElement;

        for (iElement = 0; iElement < obj->nMaxElements; iElement++) {

            printf("(%03u): %p\n",iElement,obj->array[iElement]);

        }

    }