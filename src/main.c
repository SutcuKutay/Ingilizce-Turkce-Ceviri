#include <stdio.h>
#include <stdlib.h>
#include "fields.h"
#include <string.h>
#include "dllist.h"

int main(int argc,char **argv)
{
	IS sozlukis, inputis;
	int i;
	Dllist sl, stmp, stmp2; //Stringler icin liste
	sl=new_dllist();
	if(argc!=4)
	{
		fprintf(stderr,"usage: printwords filename\n");
		exit(1);
	}
	//sozluk.txt'yi inputstruct olarak acar. Hata var mı kontrol eder
	sozlukis=new_inputstruct(argv[3]); //argv[1]==./txt/sozluk.txt
	if(sozlukis==NULL)
	{
		perror(argv[3]);
		exit(1);
	}
	//sozluk.txt'deki her satiri get_line fonksiyonu ile okur.
	while(get_line(sozlukis)>=0)
	{
		//doubleList'e ekleme yap.
		for(i=1;i<sozlukis->NF;i++)
		{
			dll_append(sl, new_jval_s(strdup(sozlukis->fields[i])));
		}
	}
	//input.txt'yi okur, girilen dil parametresine gore sozluk.txt ile karsilastirma yapar ve output.txt'ye ceviriyi yazdirir
	inputis=new_inputstruct(argv[2]);
	int sayac=0;
	int okunanKelimeSayisi=0;
	stmp=sl->flink;
	stmp2=stmp;
	if(inputis==NULL)
	{
		perror(argv[2]);
		exit(1);
	}
	FILE *dosya=fopen("./txt/output.txt","w");
	while(get_line(inputis)>=0)
	{
		for(i=0;i<inputis->NF;i++)
		{
			while(stmp!=sl)
			{
				if(!strcmp(stmp->val.s,inputis->fields[i])) //input.txt icindeki kelime, sozluk.txt icinde var mi kontrolu
				{
					//ingilizce kelimelerin cevirisi
					if(sayac%2==0 && strcmp(argv[1],"eng"))
					{
						stmp=stmp->flink;
						fprintf(dosya,"%s ",stmp->val.s);
						//printf("%s ",stmp->val.s);
					}
					//turkce kelimelerin cevirisi
					else
					{
						stmp=stmp->blink;
						fprintf(dosya,"%s ",stmp->val.s);
						//printf("%s ",stmp->val.s);
					}
					break;
				}
				stmp=stmp->flink;
				sayac++;
				//sozluk.txt'de karsiligi olmayan kelimelerin cevrilmeden yazilmasi
				if (stmp==sl){
					fprintf(dosya,"%s ",inputis->fields[i]);
					//printf("%s ",inputis->fields[i]);
				}
			}
			stmp=stmp2;
			sayac=0;
			okunanKelimeSayisi=inputis->NF;
		}	
	}
	printf("Okunan kelime sayisi: %d",okunanKelimeSayisi);
	fclose(dosya);
	//new_inputstruct tarafindan kullanilan hafizayi serbest birakir ve programi sonlandirir
	jettison_inputstruct(sozlukis);
	return 0;
}	
