# Libraries
### knn.h (*dependency: utils.h*)
Contains the basic algorithm for performing K-nearest neighboring algorithm. This accepts 2D array (representing row and column) for `x_train` and 1D array as value for `y_train` (the functions that will be documented below might overlap with the functions on `utils.h`). Below are the functions that this module contains:

- `set_kdistance` function with parameter: (`int k`) where:
    - `int k` is the number of nearest neighbor/points to be considered for prediction.

- `set_data_label` function with parameter: (const char** labels) where:
    - `const char **` is the label for the coresponding indices of the `y_train`.

  Below is an example implementation of `set_data_label` function:
  ```C
  #include <stdlib.h>
  #include "knn.h"

  int main() {
    float y_train[] = {0, 1, 2, 0, 1, 2};

    // the labels for 0-2 must be assigned so the size of this must be 3
    const char** labels = (const char**)malloc(3 * sizeof());
    labels[0] = "sampaguita";
    labels[1] = "rose";
    labels[2] = "tulips";

    // set the label for the y_train
    set_data_label(labels);
  }
  ```
  For cleaner implementation, we can use `stack_label` and `get_stacked_labels` function from `utils.h`:
  ```C
  #include "knn.h"
  #include "utils.h"

  int main() {
    // same flow as the above but used stack_label and get_stacked_labels functions
    float y_train[] = {0, 1, 2, 0, 1, 2};

    // declare the labels the same as the above
    stack_label("sampaguita");
    stack_label("rose");
    stack_label("tulips");

    set_data_label(get_stacked_labels());
  }

  ```

- `load_data` or `train` function with parameters: (`float** inputs`, `int* outputs`, `int rowsize`, `int colsize`) where:
    - `float** inputs` is a 2D array containing your `x_train` dataset.
    - `int* outputs` is a 1D array containing the `y_train` dataset.
    - `int rowsize` is the size of the `inputs`'s first dimension.
    - `int colsize` is the size of the `inputs`'s second dimension.
    - ps. i use both `load_data` and `train` as a name for the function since they can be used interchangably on lectures.

  Below is an example implementation of `load_data`/`train` function:
  ```C
  #include "utils.h"
  #include "knn.h"

  int main() {
    int row = 5;
    int col = 5;

    // generates 2D array with row and column size of 5, and random values of 0-1
    float** xtrain = generate_random_dataset(row, col, 1);

    // generates example output for 5 rows
    float ytrain[] = {0, 1, 2, 1, 0};

    // train the knn-model
    load_data(xtrain, ytrain, row, col);

    // you can now predict here...
  }
  ```
