/*
    A simple library for loading array and drawing conclusion using knn classification algorithm
    Author: Hubert F. Espinola I
    Written: September 12, 2023
*/

#include <stdlib.h>
#include "utils.h"

float** __TRAINABLE_X = NULL;
int* __TRAINABLE_Y = NULL;

int __K_DISTANCE = 0;
int __COLSIZE = 0;
int __ROWSIZE = 0;

const char** __LABELS = NULL;

void load_data(float** inputs, int* outputs, int rowsize, int colsize) {
    __TRAINABLE_Y = outputs;
    __TRAINABLE_X = inputs;
    __COLSIZE = colsize;
    __ROWSIZE = rowsize;
}

// other term for loading training data in memory
void train(float** inputs, int* outputs, int rowsize, int colsize) {
    load_data(inputs, outputs, rowsize, colsize);
}

// for setting label for data
void set_data_label(const char** label) {
    __LABELS = label;
}

// for setting the K-nearest distances
void set_kdistance(int k) {
    __K_DISTANCE = k;
}

// perform a knn algorithm to predict based on input data
int knn_predict(float* inputdata) {
    for (int i = 0; i < __ROWSIZE; i++)
        insert_knn_tuple(__TRAINABLE_Y[i], eucledian_distance(__TRAINABLE_X[i], inputdata, __ROWSIZE));

    int* indexes = getknn_yvalues(__K_DISTANCE);
    return get_majority_yvalue(indexes, __K_DISTANCE);
}

// perfom a knn-algorithm prediction win loaded labels
const char* knn_predict_with_labels(float* inputdata) {
    if (__LABELS == NULL) return 0;
    int index = knn_predict(inputdata);

    return __LABELS[index];
}