#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX 50

int partition(int *lock, int *key, int p, int r){ // p dizinin iþlem yapýlacak kýsmýnýn baþlangýcý - r ise sonudur.
	
	int tmp; // swap için geçici deðiþken.
	int j; // dizi boyunca p den r ye kadar bütün elemanlara bakmak için kullanýlan döngü deðiþkeni.
	int i; // lock dizisinde pivotun swaplanacaðý yerin indisi.
	int l; // key dizisinde pivotun swaplanacaðý yerin indisi.
	int k = p + rand()%(r-p+1); // random seçilen pivotun indisi.
	int pivot = key[k]; // quickSort algoritmasýndaki pivot.
	
	
	for(i = p; pivot != lock[i]; i++); // random alýnan key, locklara deneniyor.
	lock[i] = lock[r]; // lock dizisinde pivot sona alýnýyor.
	lock[r] = pivot;
	key[k] = key[r]; // key dizisinde pivot sona alýnýyor.
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

void quickSort(int *lock, int *key, int p, int r){ // p dizinin iþlem yapýlacak kýsmýnýn baþlangýcý - r ise sonudur.
	
	int q; // partitionun döndürdüðü pivot indisini tutmaya yarayan deðiþken.
	
	if(p < r){
		q = partition(lock, key, p, r);
		quickSort(lock, key, p, q - 1);
		quickSort(lock, key, q + 1, r);
	}
}

void printArray(int *array, int size){
	
	int i; // döngüyü yazdýrmada kullanýlacak döngü deðikeni
	for(i = 0; i < size; i++){
		printf("%d ", array[i]);
	}
	printf("\n");
}

int main(int argc, char *argv[]) {
	
	srand(time(NULL));	
	
	int size; // key ve lock dizilerinin boyutunu tutan deðiþken.
	int i; // dizileri gezmek için kullanýlacak temel döngü deðiþkeni.
	int randomIndis; // kullanýcýdan alýnan her key dizisi elemaný için lock dizisinde random bir indis bulmada kullanýlan deðiþken.
	int key[MAX]; // istenilen key dizisi
	int lock[MAX]; // istenilen lock dizisi
	
	
	printf("Boyutu giriniz : "); scanf("%d",&size);
	
	for(i = 0; i < size; i++){ 
		lock[i] = -1; // bütün lock elemanlarý -1 yapýlýyor :
	}  				  // bu iþlem her key deðerini random bir lock indisine yazmamýzda yardýmcý olacak.
	   	
		
	for(i = 0; i < size; i++){ // key dizisi kullanýcýdan alýnýyor ve ayný deðerleri içeren indexleri farklý lock dizisi oluþturuluyor.
		
		printf("%d. anahtar : ", i + 1);
		scanf("%d",&key[i]);
		randomIndis = rand()%size;
		while(lock[randomIndis] != -1) // eðer lock[j] baþka deðer varsa üstüne yazmamalý.
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
