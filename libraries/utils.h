#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

///////////////////////////////////
//  Maths and Calculations part  //
///////////////////////////////////
// calculates the eucledian distance between point a and b
// condition: a and b must have equal size
float eucledian_distance(float* a, float* b, int rowsize) {
    float sumsquared = 0;
    for (int i = 0; i < rowsize; i++)
        sumsquared += (a[i] - b[i]) * (a[i] - b[i]);

    return sqrt(sumsquared);
}

///////////////////////////////////////////////////////////////
//  a simple structure for counting the number of occurence  //
///////////////////////////////////////////////////////////////
struct occurence_pair {
    int yvalue;
    int count;
    struct occurence_pair* next;
};

struct occurence_pair** __OCCURENCE_LIST = NULL;
int __OCCURENCE_SIZE = 0;

void init_occurence_pair(int osize) {
    __OCCURENCE_LIST = (struct occurence_pair**)malloc(osize * sizeof(struct occurence_pair*));
    __OCCURENCE_SIZE = osize;

    for (int i = 0; i < osize; i++) __OCCURENCE_LIST[i] = NULL;
}

// for basic calculation of hash values
int hashfunc(int yvalue) {
    return (yvalue % __OCCURENCE_SIZE);
}

void insert_occurence(int yvalue) {
    int index = hashfunc(yvalue);
    if (__OCCURENCE_LIST[index] == NULL) {
        __OCCURENCE_LIST[index] = (struct occurence_pair*)malloc(sizeof(struct occurence_pair));
        __OCCURENCE_LIST[index]->yvalue = yvalue;
        __OCCURENCE_LIST[index]->count = 1;
        __OCCURENCE_LIST[index]->next = NULL;
        return;
    }

    struct occurence_pair* tmp = __OCCURENCE_LIST[index];
    struct occurence_pair* hld = NULL;

    while (tmp != NULL) {
        if (tmp->yvalue == yvalue) {
            tmp->count++;
            return;
        }

        hld = tmp;
        tmp = tmp->next;
    }

    hld->next = (struct occurence_pair*)malloc(sizeof(struct occurence_pair));
    hld->next->yvalue = yvalue;
    hld->next->count = 1;
    hld->next->next = NULL;
}

//////////////////////////////////////////////////
//  for automatic tuple sorting implementation  //
//////////////////////////////////////////////////
// so, I just challenge myself with this shenanigan
struct knn_tuple {
    int yvalue;
    float distance;
    struct knn_tuple* next;
};

struct item_count {
    int count;
    int item;
};

struct knn_tuple* ROOT = NULL;
struct knn_tuple* TAIL = NULL;

// automatic sorting of distance from least to greatest
void insert_knn_tuple(int yvalue, float distance) {
    if (ROOT == NULL) {
        ROOT = (struct knn_tuple*)malloc(sizeof(struct knn_tuple));
        TAIL = ROOT;

        ROOT->yvalue = yvalue;
        ROOT->distance = distance;
        ROOT->next = NULL;
        return;
    }

    struct knn_tuple* tmp_root = ROOT;
    struct knn_tuple* tmp_prev = NULL;

    while (1) {
        if (tmp_root == NULL) {
            struct knn_tuple* new_tail = (struct knn_tuple*)malloc(sizeof(struct knn_tuple));
            new_tail->distance = distance;
            new_tail->yvalue = yvalue;
            new_tail->next = NULL;

            TAIL->next = new_tail;
            return;
        }

        if (distance <= tmp_root->distance) {
            if (tmp_prev == NULL) {
                tmp_root = ROOT;
                ROOT = (struct knn_tuple*)malloc(sizeof(struct knn_tuple));
                ROOT->distance = distance;
                ROOT->yvalue = yvalue;
                ROOT->next = tmp_root;
                return;
            } else {
                struct knn_tuple* tmp = (struct knn_tuple*)malloc(sizeof(struct knn_tuple));
                tmp->distance = distance;
                tmp->yvalue = yvalue;
                tmp->next = tmp_root;
                tmp_prev->next = tmp;
                return;
            }
        }

        tmp_prev = tmp_root;
        tmp_root = tmp_root->next;
    }
}


// returns the k least distance from the point
int* getknn_yvalues(int k) {
    struct knn_tuple* tmp_root = ROOT;
    int* yvalues = (int*)malloc(k * sizeof(int));

    for (int i = 0; (tmp_root != NULL) && (i < k); (i++, tmp_root = tmp_root->next))
        yvalues[i] = tmp_root->yvalue;

    return yvalues;
}

// for getting the most max indices in a tuple list
int getmax_id(int* yvalue_list, int arrsize, int ksize) {
    int* maxarr = (int*)malloc(ksize * sizeof(int));

    for (int i = 0, j = 0; i < arrsize; i++) {
    }
}

///////////////////////////
//  Debugging functions  //
///////////////////////////
void print_all_tuples() {
    for (struct knn_tuple* tmp_root = ROOT; tmp_root != NULL; tmp_root = tmp_root->next)
        printf("%d->", tmp_root->yvalue);
}

float** generate_random_dataset(int rowsize, int colsize, float max_num) {
    srand((unsigned int)time(NULL));
    float** returningvalue = (float**)malloc(rowsize * sizeof(float*));

    for (int i = 0; i < rowsize; i++) {
        returningvalue[i] = (float*)malloc(colsize * sizeof(float));
        for (int j = 0; j < colsize; j++) {
            returningvalue[i][j] = ((float)rand()/(float)RAND_MAX) * max_num;
        }
    }

    return returningvalue;
}