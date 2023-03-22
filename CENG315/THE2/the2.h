
void swapHelper(unsigned short *array, int i, int j, long &swap, double &avg_dist, double &max_dist);

int partition(unsigned short *array, int size, long &swap, double &avg_dist, double &max_dist);

int hoareHelper(unsigned short *arr, long &swap, double &avg_dist, double &max_dist, int size);

void quickSort(unsigned short* arr, long &swap, double & avg_dist, double & max_dist, bool hoare, int size);

void quickSort3(unsigned short *arr, long &swap, long &comparison, int size);