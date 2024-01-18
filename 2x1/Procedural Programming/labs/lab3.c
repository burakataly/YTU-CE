#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct s{
	int kod;
	char name[30];
	double birim;
	double kilo;
}tablo;

void printTablo(tablo* urunler, int size){
	int i;
	for(i=0;i<size;i++){
		printf("kod: %d || ", urunler[i].kod);
		printf("name: %s || ", urunler[i].name);
		printf("birim fiyat: %.2lf || ", urunler[i].birim);
		printf("kilo fiyat: %.2lf\n\n" , urunler[i].kilo);
	}
}

int validKod(tablo* urunler, int size, int kod){
	int i;
	for(i=0;i<size;i++){
		if(urunler[i].kod == kod) return i;
	}
	return -1;
}

void total(tablo* urunler, int size, int kod, int tip, int miktar, double* toplam){
	int i=0;
	while(i<size && urunler[i].kod != kod) i++;
	if(tip == 1){
		*toplam += urunler[i].birim * miktar;	
	}
	else{
		*toplam += urunler[i].kilo * miktar;
	}
}

double indirim(double toplam){
	if(toplam >= 50 && toplam < 100) return (toplam * 95) / 100;
	if(toplam >= 100) return (toplam * 90) / 100;
	return toplam;
}

int main(){
	int i, n = 6, kod, tip, miktar;
	char answer;
	double toplam = 0;
	tablo *urunler = (tablo*) malloc(n*sizeof(tablo));
	urunler[0].kod = 1;
	strcpy(urunler[0].name, "domates");
	urunler[0].birim = 8.25;
	urunler[0].kilo = 23.75;
	urunler[1].kod = 2;
	strcpy(urunler[1].name, "biber");
	urunler[1].birim = 6.25;
	urunler[1].kilo = 29.50;
	urunler[2].kod = 3;
	strcpy(urunler[2].name, "sut");
	urunler[2].birim = 15.85;
	urunler[2].kilo = 27.15;
	urunler[3].kod = 4;
	strcpy(urunler[3].name, "peynir");
	urunler[3].birim = 23;
	urunler[3].kilo = 95.50;
	urunler[4].kod = 5;
	strcpy(urunler[4].name, "muz");
	urunler[4].birim = 13.45;
	urunler[4].kilo = 45.50;
	urunler[5].kod = 6;
	strcpy(urunler[5].name, "armut");
	urunler[5].birim = 5.50;
	urunler[5].kilo = 20.15;
	
	do{
		printTablo(urunler, 6);	
		do{
			printf("urun kodu gir: ");
			scanf("%d", &kod);
		} while(validKod(urunler, n, kod) == -1);
		
		do{
			printf("alis tipi gir (birim 1, kilo 2): ");
			scanf("%d", &tip);
		} while(tip != 1 && tip != 2);
		
		do{
			printf("miktar gir: ");
			scanf("%d", &miktar);
		} while(miktar <= 0);
		total(urunler, n, kod, tip, miktar, &toplam);
		printf("toplam tutar: %.2lf\n", toplam);
		printf("devam? (E/H): ");
		scanf("\n%c", &answer);
	} while(answer == 'e' || answer == 'E');
	printf("toplam tutar: %.2lf\n", toplam);
	printf("indirimli tutar: %.2lf\n", indirim(toplam));
	
	return 0;
}
