#include <stdio.h>
#include <stdlib.h>

void BubbleSort(int *a, int nCount)	//int a[] 等价于 int *a
{
	int i = 0;
	int j = 0;
	//控制次数
	for(j = 0; j < nCount; j++)
	{
		//一次冒泡
		for(i = 0; i < nCount - 1; i++)
		{
			if(a[i]>a[i+1])
			{
				int temp = a[i];
				a[i] = a[i+1];
				a[i+1] = temp;
			}
		}
	}

}

int main()
{
	int arrData[]={6,7,3,4,2,9,8,1,0,5};
	int i = 0;
	BubbleSort(arrData, 10);

	for(i = 0; i < 10; i++)
		printf("%d",arrData[i]);
	pirntf("%d",arrData[10]);
	printf("\n");
	system("pause");
	return 0;
}