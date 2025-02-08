#include <stdio.h>
#include <string.h>

struct Urun {
    char isim[50];
    int kod;
    float birim;
    float kilo;
};

void listProducts(struct Urun *list, int size) {
	int i;
    printf("urunler:\n");
    printf("%-10s%-20s%-15s%-15s\n", "Kod", "urun Adi", "Birim Fiyati", "Kilo Fiyati");
    for ( i = 0; i < size; ++i) {
        printf("%-10d%-20s%-15.2f%-15.2f\n", list[i].kod, list[i].isim, list[i].birim, list[i].kilo);
    }
    printf("\n");
}

float calculateTotal(struct Urun *list, int size, int productCode, int purchaseType, int amount) {
    float price;
    int i;
    for ( i = 0; i < size; ++i) {
        if (list[i].kod == productCode) {
            if (purchaseType == 1) {
                price = list[i].birim * amount;
            } else if (purchaseType == 2) {
                price = list[i].kilo * amount;
            }
            return price;
        }
    }
    return -1; // Hatalý ürün kodu
}

float calculateDiscount(float totalAmount) {
    if (totalAmount >= 100) {
        return totalAmount * 0.1;
    } else if (totalAmount >= 50) {
        return totalAmount * 0.05;
    } else {
        return 0;
    }
}

int main() {
    int i, productCode, purchaseType, amount;
    float totalAmount, discount;
    char devam;
    struct Urun list[6];
    char *urunIsim[6] = {"Domates", "Biber", "Sut", "Peynir", "Muz", "Armut"};
    int urunKod[6] = {1, 2, 3, 4, 5, 6};
    float urunBirim[6] = {8.25, 6.25, 15.85, 23, 13.45, 5.50};
    float urunKilo[6] = {23.75, 29.50, 27.15, 95.50, 45.50, 20.15};

    for (i = 0; i < 6; ++i) {
        list[i].kod = urunKod[i];
        strcpy(list[i].isim, urunIsim[i]);
        list[i].birim = urunBirim[i];
        list[i].kilo = urunKilo[i];
    }

    int flag = 0;
    while (flag == 0) {
        listProducts(list, 6);

        do {
            printf("urun kodunu girin: \n");
            scanf("%d", &productCode);
        } while (calculateTotal(list, 5, productCode, 1, 1) == -1);

        do {
            printf("Alis tipi (1: Birim, 2: Kilo) girin: \n");
            scanf("%d", &purchaseType);
        } while (purchaseType != 1 && purchaseType != 2);

        printf("Miktari girin: \n");
        scanf("%d", &amount);

        totalAmount = calculateTotal(list, 5, productCode, purchaseType, amount);
        discount = calculateDiscount(totalAmount);

        printf("Toplam tutar: %.2f TL\n", totalAmount);
        printf("Indirim: %.2f TL\n", discount);
        printf("Indirimli tutar: %.2f TL\n", totalAmount - discount);

        printf("Cikmak icin 'e' veya 'E' girin, devam etmek icin herhangi bir tusa basin: ");
        scanf(" %c", &devam);

        if (devam == 'e' || devam == 'E') {
            flag = 1;
        }
    }

    return 0;
}

