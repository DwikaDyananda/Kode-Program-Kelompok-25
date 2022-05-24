#include <stdio.h>
#include <string.h>

typedef char String[255];

typedef struct{
    int NIM;
    String nama;
}Mahasiswa;

FILE *openFile();
int inputNIM();
void menu();
void addData();
void cariData();
void profil();

int main (){
	profil();
	menu();
}

void profil(){
	
 printf("=====================================================\n");
 printf("|      PROGRAM SISTEM INFORMASI DATA MAHASISWA      |\n");
 printf("|                     KELOMPOK 25                   |\n");
 printf("=====================================================\n");
 printf("| 2105551010 MARIA CHRISTINA HARTONO                |\n");
 printf("| 2105551074 I MADE DWIKA DYANANDA KUMARA           |\n");
 printf("| 2105551081 I GUSTI PUTU AGUNG WAHYU SENTANA PUTRA |\n");
 printf("| 2105551134 ANAK AGUNG LINGGA PRATYAKSA NUGRAHA    |\n");
 printf("| 2105551139 I GUSTI AGUNG BAGUS DHAMADI WIBAWA     |\n");
 printf("| 2105551156 NI MADE RANTINI                        |\n");
 printf("=====================================================\n");
 printf("|          Tekan ENTER  untuk melanjutkan....       |\n");
 printf("=====================================================\n");
 getchar();

}

void menu(){
    char menu;

    do{
    	system("cls");
        puts("Masukan pilihan Anda: ");
        puts("1. Tambah data");
        puts("2. Cari data");
        puts("x. Exit");
        printf("Pilih : ");

        menu = getche();


        if(menu == '1' || menu == '2'){

            switch(menu){
                case '1' : addData();break;
                case '2' : cariData();break;
            }

            system("pause");
        }

        system("cls");

    }while(menu != 'x');
}

void addData(){
    FILE *file = openFile("a+");
    Mahasiswa mahasiswa;

    inAddData:
    puts("\nSilahkan masukan data mahasiswa : ");

    mahasiswa.NIM = inputNIM();

	while(!feof(file)){
        Mahasiswa mahasiswa2;
        fscanf(file, "%d_%[^\n]s\n", &mahasiswa2.NIM, &mahasiswa2.nama);
        fflush(stdin);

        if (mahasiswa2.NIM == mahasiswa.NIM){
            printf("NIM tersebut sudah ada. Coba NIM lain\n");
            goto inAddData;
            break;
        }

	}

	printf("Nama Mahasiswa : ");
	scanf("%[^\n]s", &mahasiswa.nama); fflush(stdin);


	fprintf(file,"%d_%s\n", mahasiswa.NIM, mahasiswa.nama);

    fclose(file);

    puts("Data mahasiswa berhasil ditambahkan!\n");
    getchar();
    menu();
}

void cariData(){
    Mahasiswa mahasiswas[999];
	int size = 0;

	FILE *file = openFile("r");

	while(!feof(file)){
        Mahasiswa mahasiswa;
        fscanf(file, "%d_%[^\n]s\n", &mahasiswa.NIM, &mahasiswa.nama);
        fflush(stdin);

        if (mahasiswa.NIM != 0 && (mahasiswa.NIM != mahasiswas[size-1].NIM || size == 0)){
            mahasiswas[size] = mahasiswa;
            printf("%d. %d %s\n", size+1, mahasiswas[size].NIM, mahasiswas[size].nama);
            size++;
        }

	}

    fclose(file);

    inKeyword:
    printf("");
    int keyword = inputNIM();

    int hasil = cariNIM(mahasiswas, size, keyword);
    if(hasil == -1){
        printf("Data dengan NIM %d tidak ditemukan\n", keyword);
        goto inKeyword;
    }

    printf("Data dengan NIM %d berada di urutan ke-%d\n", keyword, hasil+1);
    getchar();
    menu();
}

int cariNIM(Mahasiswa *mahasiswa, int jmlAngka, int keyword){
    int i;
    for (i = 0; i < jmlAngka; i++){
        if (mahasiswa[i].NIM == keyword){
            return i;
        }
    }
    return -1;
}

FILE *openFile(String mode){
    String nama_file;

    getFile:
    printf("\nNama file : ");
    scanf("%s", &nama_file);

    strcat(nama_file, ".txt");

    FILE *file = fopen(nama_file, mode);

    if(!file){
        printf("File %s tidak ada\n", nama_file);
        goto getFile;
    }else{
        printf("File %s didapatkan\n", nama_file);
    }

    return file;
}

int inputNIM(){
    String in;

    validation:
    printf("NIM Mahasiswa: ");
    scanf("%s", &in);fflush(stdin);

    int i = 0;
    if(strlen(in) != 10){
        printf("NIM harus 10 digit. Coba lagi\n");
        goto validation;
    }

    for(i=0; i<strlen(in); i++){
        if(in[i] < 48 || in[i] > 57){
            printf("NIM hanya boleh terdiri dari bilangan bulat positif. Coba lagi\n");
            goto validation;
        }
    }

    return atoi(in);
}
