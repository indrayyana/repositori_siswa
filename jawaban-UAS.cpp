#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <ctype.h>
#include <conio.h>


/*
	UAS - Aplikasi repositori data siswa unlimited
	Nama:	I Gede Indra Adnyana
	NIM: 	210040014
	Kelas:	BA214
	Matkul:	Konsep Dasar Pemrograman
*/

typedef struct Siswa
{
	int nis;
	char nama[100];
} Siswa;

struct Node
{
	Siswa data;
	struct Node *next;
};

//Fungsi Interface
void append(struct Node** head_ref, Siswa new_data);
void bubblesort(struct Node** head_ref);
bool konfirmasidata();
bool digit_check(char key[]);
void pause();
void printList(struct Node *node);
struct Node* datasearch(struct Node *node, int nisdicari);
Siswa datadelete(struct Node **head, int nisdicari);

int main () {
	struct Node *headdata = NULL;
	char pilihanmenu[5];
	bool loopterus = true;

    printf("Selamat datang di unlimited repositori siswa, program sederhana oleh\n");
    printf("Nama    : I Gede Indra Adnyana\n");
    printf("NIM     : 210040014\n");
    printf("Kelas   : BA214\n");
    printf("Matkul  : Konsep Dasar Pemrograman\n");
    printf("Dengan ini saya bersumpah dan menyatakan bahwa program ini adalah hasil karya saya tanpa melakukan plagiasi/mencontek/copy-paste jawaban teman atau orang lain dan saya memahami.\n");
    printf("Saya menyatakan mampu memahami dan menjelaskan keseluruhan isi, cara kerja dan kode program, baik sebagian maupun kesuluruhan.\n");
    printf("Saya memahami bahwa jika dikemudian hari saya dicurigai melakukan tindakan tersebut diatas, maka saya siap untuk dibatalkan seluruh nilai saya atas matakuliah yang tertera diatas dan dinyatakan tidak lulus.\n");

	do {

		printf("\n===============MENU UTAMA===============\n");
        printf("1. Tambah Data Siswa\n");
        printf("2. Cetak Data Siswa\n");
        printf("3. Cari Nomor Induk Siswa\n");
        printf("4. Hapus data siswa\n");
        printf("0. Keluar dari program\n");
        printf("\nPilihan anda [ketik angka saja]: ");

		scanf("%s", &pilihanmenu);
		if(!digit_check(pilihanmenu)) {
		    printf("Wahai anak senja, masukan angka saja, jangan hatimu <\x03\n");
		} else {
            //switch ((int)pilihanmenu[0] - 48){  #ajaran dosen
            switch (atoi(pilihanmenu)) { // revisi
                case 1:
                    printf("Pilihan anda => Tambah Data Siswa\n");

                    Siswa buff;
                    do {
                        printf("\nMasukan Nomor Induk Siswa (Hanya angka bulat) => ");
                        scanf("%d", &buff.nis);
                        printf("Masukan Nama Siswa (Huruf tanpa spasi) => ");
                        scanf("%s", &buff.nama);
                    } while (konfirmasidata() == false);

                    append(&headdata, buff);
                    printf("Berhasil ditambahkan :)\n");
                    break;
                case 2:
                    printf("Pilihan anda => Cetak Data Siswa\n");
                    bubblesort(&headdata);
                    printList(headdata);
                    break;
                case 3:
                    printf("Pilihan anda => Cari Nomor Induk Siswa\n");

                    Siswa buffer;
                    printf("\nMasukan Nomor Induk Siswa yang akan dicari (Hanya angka bulat) => ");
                    scanf("%d", &buffer.nis);
                    datasearch(headdata, buffer.nis);
                    break;
                case 4:
                    printf("Pilihan anda => Hapus data siswa\n");

                    Siswa buffdata;
                    printf("\nMasukan Nomor Induk Siswa yang akan dihapus (Hanya angka bulat) => ");
                    scanf("%d", &buffdata.nis);
                    datadelete(&headdata, buffdata.nis);
                    break;
                case 0:
                    printf("Pilihan anda => Keluar dari aplikasi\n");
                    loopterus = false;
                    break;
                default:
                    printf("\nWahai anak muda, pilihan mu [%s] bertepuk sebelah tangan. Minum air dlu ya :)\n", pilihanmenu);
                    break;
            }
		}
		pause();
		system("cls");
	} while(loopterus);
}

struct Node* datasearch(struct Node *node, int nisdicari) {
	while (node != NULL) {
		if (node->data.nis == nisdicari) {
            printf("Data ditemukan sebagai berikut:\n");
            printf("\tNIS\t: %d", node->data.nis);
            printf("\n\tNama\t: %s", node->data.nama);
            return node;
		} else {
            node = node->next;
		}
	}
    printf("Data tidak ditemukan :(\n");
    return node;
}

Siswa datadelete(struct Node **head, int nisdicari) {
	struct Node *before = *head;
	struct Node *now = *head;
	Siswa buffdata;
	buffdata.nis = -1;


    while (now != NULL) {
        if (now->data.nis == nisdicari) {
            *head = now->next;
            printf("Data yang dihapus sebagai berikut:\n");
            printf("\tNIS\t: %d", now->data.nis);
            printf("\n\tNama\t: %s", now->data.nama);
            free(now);
            return buffdata;
        } else {
            before = now;
            now = now->next;
        }
        if (before->next->data.nis == nisdicari) {
            now = before->next;
            before->next = now->next;
            printf("Data yang dihapus sebagai berikut:\n");
            printf("\tNIS\t: %d", now->data.nis);
            printf("\n\tNama\t: %s", now->data.nama);
            free(now);
            return buffdata;
        }
    }
    printf("Data tidak ditemukan :(\n");
	return buffdata;
}

void bubblesort(struct Node** head_ref){
	struct Node *p = NULL;
	struct Node *q = NULL;
	struct Node *r = NULL;

	int sortcounter = 1;
	bool swapped;

	do {
		swapped = false;
        p = (*head_ref);
        r = (*head_ref);

        if (p == NULL) {
            return;
        }

        do {
            if (p->next == NULL) {
                return;
            }
            q = p->next;
            if(p->data.nis > q->data.nis) {
                p->next = q->next;
                q->next = p;
                if(p == (*head_ref)) {
                    (*head_ref) = q;
                } else {
                    r->next = q;
                }

                struct Node *buff = p;
                p = q;
                q = buff;
                swapped = true;
            }
            r = p;
            p = p->next;
        } while(q->next != NULL);
	} while (swapped);

	return;
}

void append(struct Node** head_ref, Siswa new_data){
	struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));
	struct Node *last = *head_ref;
	new_node->data = new_data;
	new_node->next = NULL;
	if (*head_ref == NULL)
	{
		*head_ref = new_node;
		return;
	}
	while (last->next != NULL)
		last = last->next;
	last->next = new_node;
	return;
}

bool konfirmasidata() {
	char konfirmasi[5];
	do {
		printf("Apakah data sudah benar [y/n]? ");
		scanf("%s", &konfirmasi);
	} while ((strcmp(konfirmasi, "y") != 0) && (strcmp(konfirmasi, "n") != 0));

	if	(strcmp(konfirmasi, "y") == 0) {
		return true;
	} else {
		return false;
	}
}

bool digit_check(char key[]){
    for(int i = 0; i < strlen(key); i++)
    {
        if(isdigit(key[i])==0)
        {
            return false;
        }
    }
    return true;
}

void pause(){
	printf("\n[Tekan keyboard apa saja untuk melanjutkan....]");
	getch();
}

void printList(struct Node *node){
	int count = 1;
	if (node == NULL) {
		printf("\n*Data kosong cuy...\n");
		return;
	}

	printf("NO\tNIS\t\tNAMA\n");
	while (node != NULL)
	{
		printf("%d\t%d\t\t%s\n", count++, node->data.nis, node->data.nama);
		node = node->next;
	}
	printf("\n**PERHATIAN: bagaimana pun data yang dimasukan. Cetakannya selalu terurut sesuai NIS.\n");
}
