#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int yiginSayiI = 0;
int yiginIsaretI = 0;
#define MAX 200

// push-pop Integer-->
void pushInt(int *yiginSayi, int value){ // Yýðýna int atan.
	int i;
	yiginSayiI++;
	yiginSayi[yiginSayiI] = value;
	printf("Push %d : \tSayi Yigini : ",value);
	for(i = 1; i <= yiginSayiI; i++) printf("%d  ",yiginSayi[i]); printf("\n");	
}

int popInt(int *yiginSayi){ // Yýðýndan int çeken.
	int i;
	if(yiginSayiI == 0){
		printf("Yigin bostur.");
	}
	else{
	printf("Pop %d  : \tSayi Yigini : ",yiginSayi[yiginSayiI]);
	yiginSayiI--;
	for(i = 1; i <= yiginSayiI; i++) printf("%d  ",yiginSayi[i]); printf("\n");
	return yiginSayi[yiginSayiI + 1];
	}
}
//push-pop char-->
void pushChar(char *yiginIsaret, char sign){ // Yýðýna char atan.
	int i;
	yiginIsaretI++;
	yiginIsaret[yiginIsaretI] = sign;
	printf("Push %c : \tIsaret Yigini : ",sign);
	for(i = 1; i <= yiginIsaretI; i++) printf("%c  ",yiginIsaret[i]); printf("\n");
}
char popChar(char *yiginIsaret){ // Yýðýndan char çeken.
	int i;
	if(yiginIsaretI == 0){
		printf("Yigin bostur.");
	}
	else{
	printf("Pop %c  : \tIsaret Yigini : ",yiginIsaret[yiginIsaretI]);
	yiginIsaretI--;
	for(i = 1; i <= yiginIsaretI; i++) printf("%c  ",yiginIsaret[i]); printf("\n");
	return yiginIsaret[yiginIsaretI + 1];
	}
}

// decimal karþýlýk bulan fonksiyon -->
int decimalKarsilikBul(char *baslangicElemani, int basamakSayisi){
	
	int i;
	char *stringSayi = malloc(basamakSayisi);
		
	for(i = 0; i <= basamakSayisi; i++){
		stringSayi[i] = baslangicElemani[i];	
	}
	return atoi(stringSayi); // integer = atoi(string) -> stringden integere...	
}


// ----------------------MAIN-FONKSIYONU---------------------------
int main(int argc, char *argv[]) {
	
	int yiginSayi[MAX], i, j = 0, tmp, tmp1, tmp2, basamakSayisi;
	char yiginIsaret[MAX];
	char girilenIslem[MAX];
	char yapilacakIslem;
	char duzgunIslem[MAX];
	
	
	
	printf("Yapmak istediginiz islemi matematiksel olarak hatasiz giriniz : ");
	gets(girilenIslem);	
	
	printf("\n--PUSH/POP--       --STACK--\n");
	
	for(i = 0; girilenIslem[i] != '\0'; i++){
		
		for(i; girilenIslem[i] == ' '; i++);
		// sayýyý yýðýna atma iþlemi : 		
		if((girilenIslem[i] >= '0') && (girilenIslem[i] <= '9')){
			for(j = 0; (girilenIslem[i + j] >= '0') && (girilenIslem[i + j] <= '9'); j++);
			tmp = decimalKarsilikBul(&girilenIslem[i], j);
			pushInt(yiginSayi, tmp);
			i += j - 1;
		}
		else{
		
			if(girilenIslem[i] == '*' || girilenIslem[i] == '/'){
			
					while( (yiginIsaret[yiginIsaretI] == '*' || yiginIsaret[yiginIsaretI] == '/') && yiginIsaretI > 0 && yiginIsaret[yiginIsaretI] != '('){
					
						yapilacakIslem = popChar(yiginIsaret);
						tmp1 = popInt(yiginSayi);
						tmp2 = popInt(yiginSayi);
						
						if(yapilacakIslem == '*'){//çarp
							tmp = tmp2 * tmp1;
						}
						else if(yapilacakIslem == '/'){//böl					
							tmp = tmp2 / tmp1;
						}
						pushInt(yiginSayi, tmp);
					
					}// while bitiþ
			
				pushChar(yiginIsaret, girilenIslem[i]);
			
			}
			else if(girilenIslem[i] == '+' || girilenIslem[i] == '-'){
			
				while( (yiginIsaret[yiginIsaretI] == '*' || yiginIsaret[yiginIsaretI] == '/' || yiginIsaret[yiginIsaretI] == '+' || yiginIsaret[yiginIsaretI] == '-') && yiginIsaretI > 0 && yiginIsaret[yiginIsaretI] != '(') {
				
					yapilacakIslem = popChar(yiginIsaret);
					tmp1 = popInt(yiginSayi);
					tmp2 = popInt(yiginSayi);
					
					if(yapilacakIslem == '*'){//çarp
						tmp = tmp2 * tmp1;
					}
					else if(yapilacakIslem == '/'){//böl					
						tmp = tmp2 / tmp1;
					}
					else if(yapilacakIslem == '+'){//topla						
						tmp = tmp2 + tmp1;
					}
					else if(yapilacakIslem == '-'){//çýkar						
						tmp = tmp2 - tmp1;
					}
					pushInt(yiginSayi, tmp);
							
				}// while2 bitiþ
				
			pushChar(yiginIsaret, girilenIslem[i]);			
			}
			else if(girilenIslem[i] == '(') pushChar(yiginIsaret, '(');
			else {
				yapilacakIslem = popChar(yiginIsaret);
				while(yapilacakIslem != '('){
				
					tmp1 = popInt(yiginSayi);
					tmp2 = popInt(yiginSayi);
					if(yapilacakIslem == '*'){
						tmp = tmp2 * tmp1;
					}
					else if(yapilacakIslem == '/'){
						tmp = tmp2 / tmp1;
					}
					else if(yapilacakIslem == '+'){
						tmp = tmp2 + tmp1;
					}
					else if(yapilacakIslem == '-'){
						tmp = tmp2 - tmp1;
					}
					pushInt(yiginSayi, tmp);
					yapilacakIslem = popChar(yiginIsaret);
				}
			}	
		}
	if(girilenIslem[i+1] == NULL){
		
		while(yiginIsaretI > 0){
			
			tmp1 = popInt(yiginSayi);
			tmp2 = popInt(yiginSayi);
			yapilacakIslem = popChar(yiginIsaret);
			if(yapilacakIslem == '*'){
			tmp = tmp2 * tmp1;
			}
			else if(yapilacakIslem == '/'){
				tmp = tmp2 / tmp1;
			}
			else if(yapilacakIslem == '+'){
				tmp = tmp2 + tmp1;
			}
			else if(yapilacakIslem == '-'){
				tmp = tmp2 - tmp1;
			}
			pushInt(yiginSayi, tmp);
		}	
	}
}
		printf("\nYigin Sayi (Sonuc) : ");
		for(i = 1; i <= yiginSayiI; i++){
			printf("%d	" ,yiginSayi[i]);
		}
		printf("\nYigin Isaret (Bos) : ");
		for(i = 1; i <= yiginIsaretI; i++){
			
			printf("%c  ", yiginIsaret[i]);
		}
	
	return 0;
}
