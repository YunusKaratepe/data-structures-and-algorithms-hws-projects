#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX 50

int partition(int *lock, int *key, int p, int r){ // p dizinin i�lem yap�lacak k�sm�n�n ba�lang�c� - r ise sonudur.
	
	int tmp; // swap i�in ge�ici de�i�ken.
	int j; // dizi boyunca p den r ye kadar b�t�n elemanlara bakmak i�in kullan�lan d�ng� de�i�keni.
	int i; // lock dizisinde pivotun swaplanaca�� yerin indisi.
	int l; // key dizisinde pivotun swaplanaca�� yerin indisi.
	int k = p + rand()%(r-p+1); // random se�ilen pivotun indisi.
	int pivot = key[k]; // quickSort algoritmas�ndaki pivot.
	
	
	for(i = p; pivot != lock[i]; i++); // random al�nan key, locklara deneniyor.
	lock[i] = lock[r]; // lock dizisinde pivot sona al�n�yor.
	lock[r] = pivot;
	key[k] = key[r]; // key dizisinde pivot sona al�n�yor.
	key[r] = pivot;
	
	i = p - 1; 
	l = p - 1;
	for(j = p; j <= r-1; j++){
		
		if(lock[j] < pivot){
			i++;
			tmp = lock[i];
			lock[i] = lock[j];
			lock[j] = tmp;
		}
		if(key[j] < pivot){
			l++;
			tmp = key[l];
			key[l] = key[j];
			key[j] = tmp;
		}
	}
	tmp = lock[i+1];
	lock[i+1] = lock[r];
	lock[r] = tmp;
	
	tmp = key[i+1];
	key[i+1] = key[r];
	key[r] = tmp;	
	
	return (i+1);
}

void quickSort(int *lock, int *key, int p, int r){ // p dizinin i�lem yap�lacak k�sm�n�n ba�lang�c� - r ise sonudur.
	
	int q; // partitionun d�nd�rd��� pivot indisini tutmaya yarayan de�i�ken.
	
	if(p < r){
		q = partition(lock, key, p, r);
		quickSort(lock, key, p, q - 1);
		quickSort(lock, key, q + 1, r);
	}
}

void printArray(int *array, int size){
	
	int i; // d�ng�y� yazd�rmada kullan�lacak d�ng� de�ikeni
	for(i = 0; i < size; i++){
		printf("%d ", array[i]);
	}
	printf("\n");
}

int main(int argc, char *argv[]) {
	
	srand(time(NULL));	
	
	int size; // key ve lock dizilerinin boyutunu tutan de�i�ken.
	int i; // dizileri gezmek i�in kullan�lacak temel d�ng� de�i�keni.
	int randomIndis; // kullan�c�dan al�nan her key dizisi eleman� i�in lock dizisinde random bir indis bulmada kullan�lan de�i�ken.
	int key[MAX]; // istenilen key dizisi
	int lock[MAX]; // istenilen lock dizisi
	
	
	printf("Boyutu giriniz : "); scanf("%d",&size);
	
	for(i = 0; i < size; i++){ 
		lock[i] = -1; // b�t�n lock elemanlar� -1 yap�l�yor :
	}  				  // bu i�lem her key de�erini random bir lock indisine yazmam�zda yard�mc� olacak.
	   	
		
	for(i = 0; i < size; i++){ // key dizisi kullan�c�dan al�n�yor ve ayn� de�erleri i�eren indexleri farkl� lock dizisi olu�turuluyor.
		
		printf("%d. anahtar : ", i + 1);
		scanf("%d",&key[i]);
		randomIndis = rand()%size;
		while(lock[randomIndis] != -1) // e�er lock[j] ba�ka de�er varsa �st�ne yazmamal�.
			randomIndis = rand()%size; 
		lock[randomIndis] = key[i];
	}
	
	printf("\nKapilar    : ");
	printArray(lock, size);
	printf("Anahtarlar : ");
	printArray(key, size);
	printf("---------------------------------------------------------\n");
	quickSort(lock, key, 0, size-1);
	printf("Kapilar    : ");
	printArray(lock, size);
	printf("Anahtarlar : ");
	printArray(key, size);
	
	return 0;
}
