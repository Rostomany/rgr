#include<stdio.h>
#include<stdlib.h>
#include <time.h>

void insert_sort(int* arr, int start, int end)
{
	for (int i = start + 1; i <= end; i++)
	{
		int k = i;
		while (k > start && arr[k] < arr[k - 1])
		{
			int tmp = arr[k - 1];
			arr[k - 1] = arr[k];
			arr[k] = tmp;
			k--;
		}
	}
}

void q_sort(int* arr, int start, int end)
{
	if (start < end)
	{
		int left = start;
		int right = end;
		int mid = arr[(left + right) / 2];

		do
		{
			while (arr[left] < mid)
				left++;
			while (arr[right] > mid)
				right--;
			if (left <= right)
			{
				int tmp = arr[left];
				arr[left] = arr[right];
				arr[right] = tmp;
				left++;
				right--;
			}
		} while (left < right);

		q_sort(arr, start, right);
		q_sort(arr, left, end);             
	}
}



void insert_with_qsort(int* arr, int size_arr)
{
	int series_length = 0;
	printf("Enter the length of the series(the number is not greater than the size of the array)\n");
	scanf("%d", &series_length);

	int start_series = 0;
	int end_series = series_length - 1;
	while (end_series < size_arr - 1)
	{
		insert_sort(arr, start_series, end_series);
		start_series += series_length;
		end_series += series_length;
	}
	insert_sort(arr, start_series, size_arr - 1);
	q_sort(arr, 0, (size_arr - 1));

	for (int i = 0; i < size_arr; i++)
		printf("%d ", arr[i]);

}

int main()
{
	unsigned short size_arr = 0;
	printf("Enter the number of elements in the array\n");
	scanf("%hu", &size_arr);

	int* arr = malloc(size_arr * sizeof(int));
	if (!arr)
		EXIT_FAILURE;
	for (int i = 0; i < size_arr; i++)
		arr[i] = rand()%100;
	clock_t start = clock();
	insert_with_qsort(arr, size_arr);
	clock_t finish = clock();
	double Total_time = (double)(finish - start) / CLOCKS_PER_SEC;
	printf("\nTime:%f", Total_time);

	return 0;
}