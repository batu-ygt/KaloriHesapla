#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main() {
//Kalori Text'i Okunmak Üzere, Sipariş Dosyası İçerisine Veri Girilmek Üzere Açıldı (Pointer Atandı)
    FILE* fkalori = fopen("kalori.txt","r");
    FILE* fsiparis = fopen("siparis.txt","w");

    struct kalori { // Kalori.txt okumak için kalori adında yapı oluşturuldu.
        char yemek2[20];
        int kalori_miktari;
    } kalori;

    struct siparis { //Siparis.txt icine yazmak ve okumak icin siparis adinda yapı oluşturuldu.
        char yemek[20];
        float porsiyon;
    } siparis;

//Dosyanın Açılıp Açılamadığı Kontrol Edildi.
    if(fkalori == NULL||fsiparis == NULL) {
        printf("Dosya bulunamadi.\n");
        return 1;
    }

    char kontrol = 'E';

    while(kontrol != 'H')
    {
        printf("Menuden secmek istediginiz yemegin ismini ve porsiyon adedini giriniz..\n");
        scanf(" %s %f", siparis.yemek, &siparis.porsiyon);
        fprintf(fsiparis,"%s %.1f\n", siparis.yemek, siparis.porsiyon);
        //Sipariş Dosyasına Gerekli Veriler (Yemek Adı ve Porsiyon Miktarı) Girildi.
        printf("Daha siparis verecek misiniz? E/H\n");
        scanf(" %c", &kontrol);
        kontrol = toupper(kontrol);
    }

    printf("Siparisleriniz alinmistir..\n");
    fclose(fsiparis);

    //Sipariş Text'i Okunmak Üzere Açıldı.
    fsiparis = fopen("siparis.txt","r");
    float toplam = 0;

/*Kalori Text'indeki Satırlar Okunup Sipariş Text'inden Okunan Değerlerle Karşılaştırıp Eşleşen String
Değeri Olursa O Satırdaki Kalori Miktarıyla Girilen Porsiyon Miktarı Çarpılıp Toplama Eklenir.*/
    while(fscanf(fkalori," %s%d", kalori.yemek2, &kalori.kalori_miktari)==2)
    {
        rewind(fsiparis);   //Satır başına geçti
        fscanf(fsiparis," %s %f",siparis.yemek,&siparis.porsiyon);
        while(!feof(fsiparis))
        {
            if(strcmp(siparis.yemek,kalori.yemek2) == 0)
            {
                toplam += kalori.kalori_miktari*siparis.porsiyon;
            }
            fscanf(fsiparis, " %s%f",siparis.yemek, &siparis.porsiyon);
        }

    }

printf("Toplam kalori = %.2f", toplam);
    fclose(fkalori);
    fclose(fsiparis);
}