#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

/*
Soru: Verilen A[n] ve B[n] kelimeleri ve k de�eri i�in de�i�im matrisinde ana diagonalde [0,0]�dan en fazla
ka� ad�m ilerlenmesi yeterlidir? K�saca a��klay�n�z. 

T�m i�lemlerin Copy ve Change oldu�unu varsayarsak (bu i�lemlerde �arpraz hareket edilmektedir), 
ana diagonel �zerinde K de�erinden b�y�k say� bulundu�u anda hesaplama sonlandirilir.

*/

int main(int argc, char *argv[]) {
	char k1[100], k2[100];
	int matris[100][100];
	int k, n, m, i, j;
	
	printf("ilk kelime: "); scanf("%s",k1);
	printf("ikinci kelime: "); scanf("%s",k2);
	printf("k degeri: "); scanf("%d",&k);
	n=strlen(k1); m=strlen(k2);
	printf("\n1. kelime: %s, harf sayisi: %d\n2. kelime: %s, harf sayisi: %d\n\n",k1,n,k2,m);
	
	
	for(i=0;i<n+1;i++)
	{
	

		for(j=0;j<m+1;j++)
		{	
		
				if(i==0) //matrisin ilk sat�r�na o andaki j'leri yerle�tiriyoruz (1-2-3-4... �eklinde)
					matris[i][j]=j*2;
				else if(j==0) //matrisin ilk s�tununa o andaki i'leri yerle�tiriyoruz (1-2-3-4... �eklinde)
					matris[i][j]=i*2;
				else
				{
					if(k1[i-1]==k2[j-1]) //copy ise sol �stteki cost'u aynen ge�ir
						matris[i][j]=matris[i-1][j-1];
					else //copy de�ilse
					{
						int delete;
						int insert;
						int change;
						int minimum;
						
						delete=matris[i-1][j]+2;
						insert=matris[i][j-1]+2;
						change=matris[i-1][j-1]+1;
						minimum=delete;
						
						if(insert<minimum){
							minimum=insert;
						}
						if(change<minimum){
							minimum=change;
						}
						matris[i][j]=minimum;
						if(i==j){
							if(matris[i][j]>k){
								return -1;
							}
						}
					}
				}
				
				printf("%3d ",matris[i][j]);
		
		}
		printf("\n");
	}
	
	
		printf("\n\nEdit Distance %d \n",matris[n][m]);
		
	char olusturulanString[500]="";
	char islem[]="";
	
	fonk(matris,k1,k2,n,m,olusturulanString,islem);
	
	return 0;
}


void fonk(int matris[100][100], char k1[], char k2[], int i, int j,char olusturulanString[500],char islem[])
{//	printf(" \n%c ",k1[i-1]);
	strcat(olusturulanString,islem); //yap�lan son i�lemi yol string'ine ekle
	
	if(i==0 && j==0) //ba�a gelindiyse fonksiyonu tekrar �a��rma, ve olu�turulan yolu yazd�r
	{
		printf(" \n%sstart",olusturulanString);
		printf("\n\n");
		return;
	} 
			
	if(k1[i-1]==k2[j-1]) //harfler e�itse copy yap�lm�� demektir, sol �st �apraz i�in recursive olarak fonksiyonu �a��r
	{
		char gonderilecekStringCopy[500];
		strcpy(gonderilecekStringCopy,olusturulanString);
		printf(" \n%c copy '0'",k1[i-1]);
		fonk(matris,k1,k2,i-1,j-1,gonderilecekStringCopy, " copy 0 ");
		
	}
	else //change, delete ve insert i�lemlerinden yap�lm�� olma ihtimallerini kontrol et ve recursive olarak fonksiyonlar� �a��r
	{
		if(i>0&&j>0) //s�n�r kontrol�
			if(matris[i-1][j-1]+1==matris[i][j])
			{
				char gonderilecekStringChange[500]; //yollar� g�stermede olu�an hatay� engellemek ad�na, fonkiyonua g�nderilmek �zere farkl� string'ler kullan�ld�
				strcpy(gonderilecekStringChange,olusturulanString);
				printf(" \n%c change '1'",k1[i-1]);
		
				fonk(matris,k1,k2,i-1,j-1,gonderilecekStringChange, " change 1 ");
				
			}
			
		if(i>0) //s�n�r kontrol�
			if(matris[i-1][j]+2==matris[i][j])
			{
				char gonderilecekStringDelete[500];	
				strcpy(gonderilecekStringDelete,olusturulanString);
				printf(" \n%c delete '2'",k1[i-1]);
				fonk(matris,k1,k2,i-1,j,gonderilecekStringDelete," delete 2 ");
				
			}
			
		if(j>0) //s�n�r kontrol�
			if(matris[i][j-1]+2==matris[i][j])
			{
				char gonderilecekStringInsert[500];	
				strcpy(gonderilecekStringInsert,olusturulanString);
				printf(" \n%c insert '2'",k1[i-1]);
		
				fonk(matris,k1,k2,i,j-1,gonderilecekStringInsert, " insert 2 ");
			
			}
	}
}
