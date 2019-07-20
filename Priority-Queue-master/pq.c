#include "pq.h"
#include <stdio.h>
#include <stdlib.h>

int min_child(PQ * pq, int root);
int max_child(PQ * pq, int root);
struct pq_struct{
  int min_heap;
  int size;
  int cap;
  struct elem_struct *heap_arr;
  int *id_array;
};

typedef struct elem_struct{
  int ID;
  int priority;
}elem;

/**
* Function: pq_create
* Parameters: capacity - self-explanatory
*             min_heap - if 1 (really non-zero), then it is a min-heap
*                        if 0, then a max-heap
*                        
* Returns:  Pointer to empty priority queue with given capacity and
*           min/max behavior as specified.
*
*/
extern PQ * pq_create(int capacity, int min_heap){
  PQ * pq = (PQ*) malloc(sizeof(PQ));
  pq->min_heap = min_heap;
  pq->size = 1;
  pq->cap = capacity;
  pq->heap_arr = (elem*) malloc(sizeof(elem)*(capacity+1));
  pq->id_array = (int*) malloc(sizeof(int)*(capacity+1));
  int i;
  for(i = 1; i <= capacity; i++){
    pq->heap_arr[i].ID = -1;
    pq->heap_arr[i].priority = -1.0; 
    pq->id_array[i] = -1;
  }
  return pq;
}

extern void pq_free(PQ * pq){
  free (pq->heap_arr);
  free (pq);
}

/**
* Function: pq_insert
* Parameters: priority queue pq
*             id of entry to insert
*             priority of entry to insert
* Returns: 1 on success; 0 on failure.
*          fails if id is out of range or
*            there is already an entry for id
*          succeeds otherwise.
*          
* Desc: self-explanatory
*
* Runtime:  O(log n)
*
*/
extern int pq_insert(PQ * pq, int id, double priority){
  if(id < 1 || id > pq->cap)
    return 0;
  else if(pq->id_array[id] != -1)
    return 0;
  pq->size = pq->size + 1;
  int i = pq->size;
  double x = priority;
  int p = i/2;
  if(pq->min_heap == 0){//max heap
    while(p > 0 && x > pq->heap_arr[p].priority){
      pq->heap_arr[i].priority = pq->heap_arr[p].priority;
      pq->heap_arr[i].ID = pq->heap_arr[p].ID;
      pq->id_array[pq->heap_arr[p].ID] = i;
      i = p;
      p = i/2;
    }
  }else{//min heap
    while(p > 0 && x < pq->heap_arr[p].priority){
      pq->heap_arr[i].priority = pq->heap_arr[p].priority;
      pq->heap_arr[i].ID = pq->heap_arr[p].ID;
      pq->id_array[pq->heap_arr[p].ID] = i;
      i = p;
      p = i/2;
    }
  }
  pq->heap_arr[i].priority = priority;
  pq->heap_arr[i].ID = id;
  pq->id_array[id] = i;
  return 1;
}

/**
* Function: pq_change_priority
* Parameters: priority queue ptr pq
*             element id
*             new_priority
* Returns: 1 on success; 0 on failure
* Desc: If there is an entry for the given id, its associated
*       priority is changed to new_priority and the data 
*       structure is modified accordingly.
*       Otherwise, it is a failure (id not in pq or out of range)
* Runtime:  O(log n)
*       
*/
extern int pq_change_priority(PQ * pq, int id, double new_priority){
  if(id < 1 || id > pq->cap)
    return 0;
  else if(pq->id_array[id] == -1)
    return 0;
  int per_up = 0;
  int i = pq->id_array[id];
  double x = new_priority;
  int p = i/2;
  if(pq->min_heap == 0){//max heap
    while(p > 0 && x > pq->heap_arr[p].priority){
      per_up = 1;
      pq->heap_arr[i].priority = pq->heap_arr[p].priority;
      pq->heap_arr[i].ID = pq->heap_arr[p].ID;
      pq->id_array[pq->heap_arr[p].ID] = i;
      i = p;
      p = i/2;
    }
  }else{//min heap
    while(p > 0 && x < pq->heap_arr[p].priority){
      per_up = 1;
      pq->heap_arr[i].priority = pq->heap_arr[p].priority;
      pq->heap_arr[i].ID = pq->heap_arr[p].ID;
      pq->id_array[pq->heap_arr[p].ID] = i;
      i = p;
      p = i/2;
    }
  }
  
  if(per_up == 0){//perc down is the last check

    int n = pq->size;
    int min_c,max_c;
    if(pq->min_heap == 0){
      min_c = min_child(pq, i);
      while(min_c != -1 && pq->heap_arr[min_c].priority < x){
        pq->heap_arr[i].priority = pq->heap_arr[min_c].priority;
        pq->heap_arr[i].ID = pq->heap_arr[min_c].ID;
        pq->id_array[pq->heap_arr[min_c].ID] = i;
        i = min_c;
        min_c = min_child(pq, i);
      }
    }else{
      max_c = max_child(pq,i);
      while(max_c != -1 && pq->heap_arr[max_c].priority > x){
        pq->heap_arr[i].priority = pq->heap_arr[max_c].priority;
        pq->heap_arr[i].ID = pq->heap_arr[max_c].ID;
        pq->id_array[pq->heap_arr[max_c].ID] = i;
        i = max_c;
        max_c = max_child(pq, i);
      }
      
    }
  }
  pq->heap_arr[i].priority = new_priority;
  pq->heap_arr[i].ID = id;
  pq->id_array[id] = i;

  return 1;
}

/**
* Function: pq_remove_by_id
* Parameters: priority queue pq, 
*             element id
* Returns: 1 on success; 0 on failure
* Desc: if there is an entry associated with the given id, it is
*       removed from the priority queue.
*       Otherwise the data structure is unchanged and 0 is returned.
* Runtime:  O(log n)
*
*/
extern int pq_remove_by_id(PQ * pq, int id){
  if(pq->size == 0){
    return 0;
  }
  int n = pq->size;
  double x = pq->heap_arr[n].priority;
  int i = pq->id_array[id];
  int min_c,max_c;
  if(pq->min_heap == 0){
    min_c = min_child(pq, i);
    while(min_c != -1 && pq->heap_arr[min_c].priority < x){
      pq->heap_arr[i].priority = pq->heap_arr[min_c].priority;
      pq->heap_arr[i].ID = pq->heap_arr[min_c].ID;
      pq->id_array[pq->heap_arr[min_c].ID] = i;
      i = min_c;
      min_c = min_child(pq, i);
    }
  }else{
    max_c = max_child(pq,i);
    while(max_c != -1 && pq->heap_arr[max_c].priority > x){
      pq->heap_arr[i].priority = pq->heap_arr[max_c].priority;
      pq->heap_arr[i].ID = pq->heap_arr[max_c].ID;
      pq->id_array[pq->heap_arr[max_c].ID] = i;
      i = max_c;
      max_c = max_child(pq, i);
    }
    
  }
  pq->heap_arr[i].priority = pq->heap_arr[n].priority;
  pq->heap_arr[i].ID = pq->heap_arr[n].ID;
  pq->id_array[pq->heap_arr[n].ID] = i;
  pq->heap_arr[n].priority = -1;
  pq->id_array[pq->heap_arr[n].ID] = -1;
  pq->heap_arr[n].ID = -1;
  pq->size = pq->size - 1;
  return 1;
  return 0;
}

extern int pq_get_priority(PQ * pq, int id, double *priority){
  if(id <= 0 || id > pq->cap)
    return 0;
  else if(pq->id_array[id] == -1)
    return 0;
  int i = pq->id_array[id];
  *priority = pq->heap_arr[i].priority;
  return 1;
}

/**
* Function: pq_delete_top
* Parameters: priority queue pq
*             int pointers id and priority ("out" parameters)
* Returns: 1 on success; 0 on failure (empty priority queue)
* Desc: if queue is non-empty the "top" element is deleted and
*       its id and priority are stored in *id and *priority; 
*       The "top" element will be either min or max (wrt priority)
*       depending on how the priority queue was configured.
*    
*       If queue is empty, 0 is returned.
*
* Runtime:  O(log n)
*
*
*/
extern int pq_delete_top(PQ * pq, int *id, double *priority){
  if(pq->size == 0){
    *id = -1;
    *priority = -1.0;
    return 0;
  }
  *id = pq->heap_arr[1].ID;
  *priority = pq->heap_arr[1].priority;
  //delete the top
  int n = pq->size;
  double x = pq->heap_arr[n].priority;
  int i = 1;
  int min_c,max_c;
  if(pq->min_heap == 0){
    min_c = min_child(pq, i);
    while(min_c != -1 && pq->heap_arr[min_c].priority < x){
      pq->heap_arr[i].priority = pq->heap_arr[min_c].priority;
      pq->heap_arr[i].ID = pq->heap_arr[min_c].ID;
      pq->id_array[pq->heap_arr[min_c].ID] = i;
      i = min_c;
      min_c = min_child(pq, i);
    }
  }else{
    max_c = max_child(pq,i);
    while(max_c != -1 && pq->heap_arr[max_c].priority > x){
      pq->heap_arr[i].priority = pq->heap_arr[max_c].priority;
      pq->heap_arr[i].ID = pq->heap_arr[max_c].ID;
      pq->id_array[pq->heap_arr[max_c].ID] = i;
      i = max_c;
      max_c = max_child(pq, i);
    }
    
  }
  pq->heap_arr[i].priority = pq->heap_arr[n].priority;
  pq->heap_arr[i].ID = pq->heap_arr[n].ID;
  pq->id_array[pq->heap_arr[n].ID] = i;
  pq->heap_arr[n].priority = -1;
  pq->id_array[pq->heap_arr[n].ID] = -1;
  pq->heap_arr[n].ID = -1;
  pq->size = pq->size - 1;
  return 1;
}

int max_child(PQ * pq, int root){
  int left, right;
  left = 2*root;
  right = 2*root + 1;
  if(left > pq->size)
    return -1;
  if(left == pq->size || pq->heap_arr[left].priority > pq->heap_arr[right].priority)
    return left;
  return right;
}

int min_child(PQ * pq, int root){
  int left, right;
  left = 2*root;
  right = 2*root + 1;
  if(left > pq->size)
    return -1;
  if(left == pq->size || pq->heap_arr[left].priority < pq->heap_arr[right].priority)
    return left;
  return right;
}

extern int pq_peek_top(PQ * pq, int *id, double *priority){
  if(pq->size == 0)
    return 0;
  *id = pq->heap_arr[1].ID;
  *priority = pq->heap_arr[1].priority;
  return 1;
}

extern int pq_capacity(PQ * pq){
  return pq->cap;
}

extern int pq_size(PQ * pq){
  return pq->size;
}

