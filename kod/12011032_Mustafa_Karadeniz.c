#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

/*
Soru: Verilen A[n] ve B[n] kelimeleri ve k deðeri için deðiþim matrisinde ana diagonalde [0,0]’dan en fazla
kaç adým ilerlenmesi yeterlidir? Kýsaca açýklayýnýz. 

Tüm iþlemlerin Copy ve Change olduðunu varsayarsak (bu iþlemlerde çarpraz hareket edilmektedir), 
ana diagonel üzerinde K deðerinden büyük sayý bulunduðu anda hesaplama sonlandirilir.

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
		
				if(i==0) //matrisin ilk satýrýna o andaki j'leri yerleþtiriyoruz (1-2-3-4... þeklinde)
					matris[i][j]=j*2;
				else if(j==0) //matrisin ilk sütununa o andaki i'leri yerleþtiriyoruz (1-2-3-4... þeklinde)
					matris[i][j]=i*2;
				else
				{
					if(k1[i-1]==k2[j-1]) //copy ise sol üstteki cost'u aynen geçir
						matris[i][j]=matris[i-1][j-1];
					else //copy deðilse
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
	strcat(olusturulanString,islem); //yapýlan son iþlemi yol string'ine ekle
	
	if(i==0 && j==0) //baþa gelindiyse fonksiyonu tekrar çaðýrma, ve oluþturulan yolu yazdýr
	{
		printf(" \n%sstart",olusturulanString);
		printf("\n\n");
		return;
	} 
			
	if(k1[i-1]==k2[j-1]) //harfler eþitse copy yapýlmýþ demektir, sol üst çapraz için recursive olarak fonksiyonu çaðýr
	{
		char gonderilecekStringCopy[500];
		strcpy(gonderilecekStringCopy,olusturulanString);
		printf(" \n%c copy '0'",k1[i-1]);
		fonk(matris,k1,k2,i-1,j-1,gonderilecekStringCopy, " copy 0 ");
		
	}
	else //change, delete ve insert iþlemlerinden yapýlmýþ olma ihtimallerini kontrol et ve recursive olarak fonksiyonlarý çaðýr
	{
		if(i>0&&j>0) //sýnýr kontrolü
			if(matris[i-1][j-1]+1==matris[i][j])
			{
				char gonderilecekStringChange[500]; //yollarý göstermede oluþan hatayý engellemek adýna, fonkiyonua gönderilmek üzere farklý string'ler kullanýldý
				strcpy(gonderilecekStringChange,olusturulanString);
				printf(" \n%c change '1'",k1[i-1]);
		
				fonk(matris,k1,k2,i-1,j-1,gonderilecekStringChange, " change 1 ");
				
			}
			
		if(i>0) //sýnýr kontrolü
			if(matris[i-1][j]+2==matris[i][j])
			{
				char gonderilecekStringDelete[500];	
				strcpy(gonderilecekStringDelete,olusturulanString);
				printf(" \n%c delete '2'",k1[i-1]);
				fonk(matris,k1,k2,i-1,j,gonderilecekStringDelete," delete 2 ");
				
			}
			
		if(j>0) //sýnýr kontrolü
			if(matris[i][j-1]+2==matris[i][j])
			{
				char gonderilecekStringInsert[500];	
				strcpy(gonderilecekStringInsert,olusturulanString);
				printf(" \n%c insert '2'",k1[i-1]);
		
				fonk(matris,k1,k2,i,j-1,gonderilecekStringInsert, " insert 2 ");
			
			}
	}
}
