//Ho va ten  < Tran Gia Bao > - Ma So SV : < B1811918 >
//Ho va ten  < Nguyen Hoai Linh > - Ma So SV : <B1812050 >

#include<stdlib.h>
#include<stdio.h>
#include<conio.h>

void swap(int &a, int &b)
{
    int t = a;
    a = b;
    b = t;
}


int partition(int arr[], int low, int high)
{
    int pivot = arr[high];   
    int left = low;
    int right = high - 1;
    while(true){
        while(left <= right && arr[left] < pivot) left++;
        while(right >= left && arr[right] > pivot) right--;
        if (left >= right) break;
        swap(arr[left], arr[right]);
        left++;
        right--;
    }
    swap(arr[left], arr[high]);
    return left;
}

//Thuc toan sap xep nhanh Quick Sort
void quickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        // Dat pi la chi so noi phan tu nay chia mang thanh cac mang con ben trai va ben phai
        int pi = partition(arr, low, high);

        // Sap de qui mang trai va phai
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}
// Noi hai mang
void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;

    int L[n1], R[n2];

    // Sao chep vao mang tam thoi
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];

    //Hop nhat 2 mang
    i = 0; 
    j = 0; 
    k = l;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    //Sao chép các phan tu còn lai cua mang L vào arr 
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Sao chép các phan tu còn lai cua mang R vào arr
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Merge Sort
void mergeSort(int arr[], int l, int r)
{
    if (l < r)
    {
        int m = l+(r-l)/2;

        //viet ham de qui ,chia mang lam hai nhu phia tren
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);

        merge(arr, l, m, r);
    }
}

void shakersort(int a[], int n) {
 int l, r, k ,c , b;
 r = n - 1;
 l = 0;
 k = 0;
 while(l<r) {
  for (int i = l; i < r; i++) {
   if (a[i] > a[i + 1]) {
    k = i;
    swap(a[i], a[i + 1]); //doi a[i] va a[i-1]
   }
  }
  r = k;

  for (int i = r; i > l; i--) {
   if (a[i] < a[i - 1]) {
    k = i;
    swap(a[i], a[i - 1]);
   }
  }
  l = k;
 
 }

 return;
}
//Sap xep vun dong HeapSort
void heapify(int arr[], int n, int i)
{
    int largest = i; //Khoi tao lon nhat duoi dang goc
    int l = 2*i + 1; // left = 2*i + 1
    int r = 2*i + 2; // right = 2*i + 2

    // Neu con ben trai lon hon goc
    if (l < n && arr[l] > arr[largest])
        largest = l;

    // Neu con ben phai lon hon con lon nhat cho den nay
    if (r < n && arr[r] > arr[largest])
        largest = r;

    //Neu lon nhat khong phai la goc
    if (largest != i)
    {
        swap(arr[i], arr[largest]);

        // De quy cay bi anh huong
        heapify(arr, n, largest);
    }
}

//Thuc hien sap xep
void heapSort(int arr[], int n)
{
    // Sap xep lai mang
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    //Trich xuat phan tu
    for (int i=n-1; i>0; i--)
    {
        // Di chuyen goc hienj tai
        swap(arr[0], arr[i]);

        
        heapify(arr, i, 0);
    }
}

const int MAX = 100;

// Nhap mang
void InputArray(int a[], int n){
    for(int i = 0;i < n; ++i){
        printf("\nNhap phan tu a[%d] = ", i);
        scanf("%d", &a[i]);
    }
}

// In danh sach mang
void OutputArray(int a[], int n){
     printf("\n Danh sach gom cac phan tu : ");
    for(int i = 0;i < n; ++i){
        printf(" %d  ",  a[i]);
    }
}

int main(void)
{
    int arr[MAX];
    int n;
    int Choice ;

    printf("\nVui long nhap so phan tu trong mang: ");
    do{

        scanf("%d", &n);

        if(n <= 0 || n > MAX){
            printf("\nNhap lai so phan tu trong mang : ");
        }
    }while(n <= 0 || n > MAX );

    printf("\n======Mang dau vao=====\n");
    InputArray(arr, n);
    do{
		system("cls");
		printf("----------MENU----------\n");
		printf("1. Print List Array.\n");
		printf("2. Shaker sort\n");
		printf("3. QuickSort \n");
		printf("4. MergeSort\n");
        printf("5. HeapSort \n");
		printf("0. Exit \n");
		printf("Vui long nhap su lua chon cua ban: ");
		scanf("%d", &Choice);

		switch(Choice){
			case 1:
			     OutputArray(arr, n);
			break;
			case 2:
			    printf("!!!Shaker Sort!!!");
			    shakersort(arr, n);
			    OutputArray(arr, n);
			break;
			case 3:
			    printf("!!!QuickSort!!!");
                quickSort(arr, 0, n-1);
                OutputArray(arr, n);
			break;
			case 4:
			    printf("!!!MergeSort!!!");
                mergeSort(arr, 0, n - 1);
                OutputArray(arr, n);

			break;
			case 5:
			    printf("!!!HeapSort!!!");
                heapSort(arr, n);
                OutputArray(arr, n);
			break;
			default:
				printf("Thoat chuong trinh!!!");
			break;
		}

		printf("\nBan co muon tiep tuc (Nhan y hoac n)");  // y (yes) ,n (no)
		char c ;
		fflush(stdin);
		scanf("%c", &c);
		if(c == 'y'){
			Choice = -1; // gan Choice khong phai la 1,2,3,0 thi chuong trinh se lap lai
		}else{
				system("cls");
			printf("Tam biet chuc ban mot ngay tot lanh!");
		}

	}while(Choice != 1 && Choice != 2 && Choice !=3 && Choice!=0 && Choice!=4 && Choice!=5 );

}
