void mergesort(char array[], int lower, int upper) {
  if (lower < upper) {
    int middle = (lower + upper) / 2;
    mergesort(array, lower, middle);
    mergesort(array, middle+1, upper);
    merge(array, lower, middle, upper);
  }
}


void merge(char array[], int lower, int middle, int upper) {
  int len_left = middle - lower + 1;
  int len_right = upper - middle;
  struct Word left[len_left], right[len_right];
  int i, j, k;

  for (i = 0, j=lower; i < len_left; i++, j++)
    left[i] = array[j];

  for (i = 0, j = middle+1 ; i < len_right; i++, j++)
    right[i] = array[j];

  i = j = 0; k = lower;
  while (i < len_left && j < len_right) {
    if ( strcmp(left[i].word, right[j].word) <= 0) array[k++] = left[ i++ ];
    else  array[k++] = right [ j++ ];
  }

  while (i < len_left)  array[k++] = left [ i++ ];
  while (j < len_right) array[k++] = right[ j++ ];

}
