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


typedef struct Stack Stack;

struct Stack{
    Vector*arr;

    int(*size)(Stack*self);
    bool(*empty)(Stack*self);
    T(*top)(Stack*self);
    void(*push)(Stack*self,T val);
    void(*pop)(Stack*self);
    void(*destroy)(Stack*self);
};

int My_stack_size(Stack*self){
    return self->arr->_size;
}
bool My_stack_empty(Stack*self){
    return self->arr->empty(self->arr);
}
T My_stack_top(Stack*self){
    return self->arr->back(self->arr);
}
void My_stack_push(Stack*self,T val){
    self->arr->push_back(self->arr,val);
}
void My_stack_pop(Stack*self){
    self->arr->pop_back(self->arr);
}
void My_stack_destroy(Stack*self){
    self->arr->destroy(self->arr);
    free(self);
}
Stack*creat_stack(){
    Stack*stack=(Stack*)malloc(sizeof(Stack));
    if(stack==NULL){
        return NULL;
    }
    stack->arr=creat_vector();
    if(stack->arr==NULL){
        return NULL;
    }

    stack->size=My_stack_size;
    stack->empty=My_stack_empty;
    stack->top=My_stack_top;
    stack->push=My_stack_push;
    stack->pop=My_stack_pop;
    stack->destroy=My_stack_destroy;

    return stack;
}

int main(void){
    Stack*stack=creat_stack();

    stack->destroy(stack);
}