#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef int T;
typedef struct Vector Vector;
const int INIT_CAP=16;

void print_T(T val){
    printf("%d",val);
}

struct Vector{
    T*data;
    int _size;
    int cap;

    int(*size)(Vector*self);
    bool(*empty)(Vector*self);
    T(*back)(Vector*self);
    T(*front)(Vector*self);
    T(*get)(Vector*self,int index);
    void(*set)(Vector*self,int index,T val);

    void(*resize)(Vector*self,int new_cap);
    void(*push_back)(Vector*self,T val);
    void(*pop_back)(Vector*self);

    void(*clear)(Vector*self);
    void(*destroy)(Vector*self);
};

int My_size(Vector*self){
    return self->_size;
}
bool My_empty(Vector*self){
    return self->_size==0;
}
T My_back(Vector*self){
    return self->data[self->_size-1];
}
T My_front(Vector*self){
    return self->data[0];
}
T My_get(Vector*self,int index){
    return self->data[index];
}
void My_set(Vector*self,int index,T val){
    self->data[index]=val;
}
void My_resize(Vector*self,int new_cap){
    self->cap=new_cap;
    self->data=(T*)realloc(self->data,new_cap*sizeof(T));
}
void My_push_back(Vector*self,T val){
    if(self->_size==self->cap){
        self->resize(self,self->cap*2);
    }
    self->data[self->_size++]=val;
}
void My_pop_back(Vector*self){
    self->_size--;
}
void My_clear(Vector*self){
    self->_size=0;
}
void My_destroy(Vector*self){
    free(self->data);
    free(self);
}

Vector*creat_vector(){
    Vector*vector=(Vector*)malloc(sizeof(Vector));
    if(vector==NULL){
        return NULL;
    }
    vector->data=(T*)malloc(INIT_CAP*sizeof(T));
    if(vector->data==NULL){
        return NULL;
    }
    vector->_size=0;
    vector->cap=INIT_CAP;

    vector->size=My_size;
    vector->empty=My_empty;
    vector->back=My_back;
    vector->front=My_front;
    vector->get=My_get;
    vector->set=My_set;

    vector->resize=My_resize;
    vector->push_back=My_push_back;
    vector->pop_back=My_pop_back;

    vector->clear=My_clear;
    vector->destroy=My_destroy;

    return vector;
}


typedef struct Queue Queue;

struct Queue{
    Vector*arr;

    int head;
    int tail;

    int(*size)(Queue*self);
    bool(*empty)(Queue*self);
    T(*front)(Queue*self);
    void(*push)(Queue*self,T val);
    void(*pop)(Queue*self);
    void(*destroy)(Queue*self);
};

int My_queue_size(Queue*self){
    return self->tail-self->head;
}
bool My_queue_empty(Queue*self){
    return self->head==self->tail;
}
T My_queue_front(Queue*self){
    return self->arr->get(self->arr,self->head);
}
void My_queue_push(Queue*self,T val){
    self->arr->push_back(self->arr,val);
    self->tail++;
}
void My_queue_pop(Queue*self){
    self->head++;
}
void My_queue_destroy(Queue*self){
    self->arr->destroy(self->arr);
    free(self);
}
Queue*creat_queue(){
    Queue*queue=(Queue*)malloc(sizeof(Queue));
    if(queue==NULL){
        return NULL;
    }
    queue->arr=creat_vector();
    if(queue->arr==NULL){
        return NULL;
    }

    queue->head=0;
    queue->tail=0;

    queue->size=My_queue_size;
    queue->empty=My_queue_empty;
    queue->front=My_queue_front;
    queue->push=My_queue_push;
    queue->pop=My_queue_pop;
    queue->destroy=My_queue_destroy;

    return queue;
}

int main(void){
    Queue*queue=creat_queue();

    queue->destroy(queue);
}