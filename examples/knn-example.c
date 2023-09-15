#include <stdio.h>
#include "../libraries/knn.h"

int main() {
    // generate sample dataset with row if 4 and column of 6 and possible values from (0-1)
    float** datasetx = generate_random_dataset(4, 6, 1);
    int datasety[] = {0, 1, 2, 0, 1, 2};

    // load the datasets with rowsize of 4, colsize of 6, and k = 3
    load_data(datasetx, datasety, 4, 6);
    set_kdistance(3);

    // set the labels for datasety
    // 0 - "Bird"; 1 - "Person"; 2 - "Building"
    stack_label("Bird");
    stack_label("Person");
    stack_label("Building");

    // load the stacked labels to all
    set_data_label(get_stacked_labels());

    float inputs[] = {1, 2, 3, 5};
    const char* pred = knn_predict_with_labels(inputs);
    // int int_prediction = knn_predict(inputs);

    printf("Prediction: %s\n", pred);
    // printf("Prediction: %d\n", int_prediction);
}