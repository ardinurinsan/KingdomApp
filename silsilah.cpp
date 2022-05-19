/**
 * @file silsilah.cpp
 * @author
 *  	- Irfan Khoirul - 211511017
 *      - Muhamad Ardi Nur Insan - 211511022
 * @description program : program ini menggunakan modul tugas praktikum SDA pada materi SDA Non Binary Tree 
 * @version 0.1
 * @date 2022-05-12
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "header.h"
#include "silsilah.h"
#include "display.h"

void Create_Node_Tree(nbAddr *tr)
{

	*tr = (nbAddr)malloc(sizeof(nbTreeNode));
	if (*tr != Nil)
	{
		//		printf("Alokasi Berhasil dengan Alamat : %p.\n",*p);
	}
	else
	{
		printf("Gagal Alokasi\n");
	}
}
void nbCreate(TreeSilsilah *x)
{
	(*x).root = NULL;
}
void CreateEmptyNode(nbAddr *tr)
{
	Create_Node_Tree(&(*tr));
}

int isTreeEmpty(nbAddr tr)
{
	return tr == NULL;
}

int isSilsilahEmpty(nbAddr tr)
{
	return isTreeEmpty(tr);
}

void Isi_Node_Silsilah(nbAddr *tr, nbType nama, char jenis_kelamin, int usia, nbType religion)
{
	if (isSilsilahEmpty(*tr))
	{
		printf("Node Belum di Alokasi\n");
	}
	else
	{
		fs(*tr) = NULL;
		strcpy(nama(*tr), nama);
		jenis_kelamin(*tr) = jenis_kelamin;
		usia(*tr) = usia;
		strcpy(religion(*tr), religion);
		nb(*tr) = NULL;
		parent(*tr) = NULL;
	}
}
// nbType name[], nbType gender, int age, nbType religion[]
nbAddr nbCNode(nbType nama, char jenis_kelamin, int usia, nbType religion_param)
{ // Create New Node
	nbAddr newNode;
	newNode = (nbAddr)malloc(sizeof(nbTreeNode));
	if (newNode != NULL)
	{
		strcpy(newNode->nama, nama);
		newNode->jenis_kelamin = jenis_kelamin;
		newNode->usia = usia;
		strcpy(newNode->religion, religion_param);

		newNode->fs = NULL;
		newNode->nb = NULL;
		newNode->parent = NULL;
	}
	return newNode;
}

nbAddr nbSearch(nbAddr root, nbType nameParam)
{
	nbAddr nSrc;
	if (root != NULL)
	{
		if (strcmp(root->nama, nameParam) == 0)
			return root;
		else
		{
			nSrc = nbSearch(root->fs, nameParam);
			if (nSrc == NULL)
				return nbSearch(root->nb, nameParam);
			else
				return nSrc;
		}
	}
	return NULL;
}

// nbType nama,char jenis_kelamin, int usia, nbType religion
void nbInsert(TreeSilsilah *tRoot, nbAddr parent, nbType nama_param, char jenis_kelamin_param, int usia_param, nbType religion_param)
{ // Insert New Node baru dengan keadaan tertentu
	nbAddr newNode, temp;
	newNode = nbCNode(nama_param, jenis_kelamin_param, usia_param, religion_param);
	if (newNode != NULL)
	{						// Jika penciptaan node baru berhasil
		if (parent == NULL) // Jika belum terdapat root
			tRoot->root = newNode;
		else
		{
			temp = parent;
			if (temp->fs != NULL)
			{
				temp = temp->fs;
				while (temp->nb != NULL)
					temp = temp->nb;
				temp->nb = newNode;
			}
			else
				temp->fs = newNode;
			newNode->parent = parent;
		}
	}
}

nbAddr Search(nbAddr tr, nbType SQ)
{
	boolean visit = true;
	if (isSilsilahEmpty(tr))
		return NULL;
	if (strcmp(nama(tr), SQ) == 0)
		return tr;
	else if (strcmp(nama(tr), SQ) != 0 && fs(tr) == NULL)
		return NULL;
	else
	{
		while (parent(tr) != NULL || visit)
		{
			if (fs(tr) != NULL && visit)
			{
				tr = fs(tr);
				if (strcmp(nama(tr), SQ) == 0)
					return tr;
			}
			else
			{
				if (nb(tr) != NULL)
				{
					tr = nb(tr);
					if (strcmp(nama(tr), SQ) == 0)
						return tr;
					visit = true;
				}
				else
				{
					visit = false;
					tr = parent(tr);
				}
			}
		}
		return NULL;
	}
}

void InsertSilsilah(nbAddr *tr)
{
	nbAddr TNode = NULL, temp = NULL;
	char jenis_kelamin;
	int usia;
	nbType Nama, parent, Agama;

	CreateEmptyNode(&TNode);

	if (isSilsilahEmpty(*tr))
	{
		gotoxy(101, 20);
		printf("Silsilah Belum Ada");
	}
	else
	{
		gotoxy(101, 14);
		printf("Input Anggota Kerajaan ");
		gotoxy(101, 16);
		printf("Nama              : ");
		fflush(stdin);
		gets(Nama);
		do
		{
			gotoxy(101, 17);
			printf("Jenis Kelamin L/P : ");
			fflush(stdin);
			scanf("%c", &jenis_kelamin);
			// convert to upper case
			jenis_kelamin = toupper(jenis_kelamin);
			if (jenis_kelamin != 'L' && jenis_kelamin != 'P')
			{
				gotoxy(101, 18);
				printf("Jenis Kelamin Salah!");
				getch();
				gotoxy(121, 17);
				printf("                 ");
			}
		} while (jenis_kelamin != 'L' && jenis_kelamin != 'P');
		bool jenis_kelamin_valid = false;
		int i = 1;
		do
		{
			gotoxy(101, 18);
			printf("usia              : ");
			fflush(stdin);
			scanf("%d", &usia);
			if (usia <= 11 || usia >= 100)
			{
				gotoxy(101, 19);
				printf("usia tidak boleh kurang dari 11 dan lebih dari 100");
				getch();
				jenis_kelamin_valid = true;
				gotoxy(101, 18);
				printf("usia          : ");
			}
			else
			{
				jenis_kelamin_valid = false;
			}
		} while (jenis_kelamin_valid);

		if (usia <= 11)
		{
			gotoxy(101, 19);
			printf("usia tidak boleh lebih kecil dari 11");
		}
		Isi_Node_Silsilah(&TNode, Nama, jenis_kelamin, usia, Agama);
		do
		{
			gotoxy(101, 20);
			printf("Masukkan Parent dari Anak Tersebut : ");
			fflush(stdin);
			gets(parent);
			if(strcmp(parent, "") == 0)
			{
				gotoxy(101, 21);
				printf("Parent tidak boleh kosong");
				getch();
				printf("                         ");
				gotoxy(101, 20);
				printf("Masukkan Parent dari Anak Tersebut : ");
				fflush(stdin);
				gets(parent);
			}else if(Search(*tr, parent) == NULL){
				gotoxy(101, 21);
				printf("Parent tidak ada!");
				getch();
				gotoxy(101, 21);
				printf("                 ");
				gotoxy(134, 20);
				printf("                 ");
			}
		} while (Search(*tr, parent) == NULL);
		temp = Search(*tr, parent);

		// validasi jika umur anak lebih dari umur orang tua dan umur anak lebih kecil dari umur orang tua
		if (usia >= usia(temp))
		{
			gotoxy(101, 21);
			printf("Usia tidak boleh lebih besar dengan parent yang di pilih %d", usia(temp));
		}
		else if (usia(temp) - usia <= 15)
		{ // rumus usia parent di kurangi usia inpputan dan bandingkan lebih kecil sama dengan 15
			gotoxy(101, 21);
			printf("Usia tidak boleh lebih kecil 15 tahun dari usia parent ! %d", usia(temp));

		}
		else
		{
			if (fs(temp) != NULL)
			{
				temp = fs(temp);
				while (nb(temp) != NULL)
					temp = nb(temp);
				parent(TNode) = parent(temp);
				nb(temp) = TNode;
			}
			else
			{
				parent(TNode) = temp;
				fs(temp) = TNode;
			}
			gotoxy(101, 22);
			printf("Node dengan nama %s berhasil ditambahkan dengan parent %s", Nama, parent);
		}
	}
}

// pre-order
int iterasi = 20;
void cetakSilsilah(nbAddr tr, char tab[])
{
	char tempTab[255];
	strcpy(tempTab, tab);
	strcat(tempTab, "-");
	if (tr != NULL)
	{
		// root node jangan di tampilkan
		if (strcmp(nama(tr), "root") != 0)
		{
			gotoxy(100, iterasi);
			printf("%s%s\n", tab, tr->nama);
			iterasi = iterasi + 1;
		}
		cetakSilsilah(tr->fs, tempTab);
		cetakSilsilah(tr->nb, tab);
	}
}

int hitungAnak(nbAddr tree, nbType parent)
{
	TnbTreeNode *temp;
	int jumlah = 0;
	if (!isTreeEmpty(tree))
	{
		temp = Search(tree, parent);
		// jika parent ditemukan
		if (fs(temp) != NULL)
		{
			jumlah = jumlah + 1;
			temp = fs(temp);
		}
		else
		{
			return 0;
		}
		while (nb(temp) != NULL)
		{
			temp = nb(temp);
			jumlah = jumlah + 1;
		}
		return jumlah;
	}

	return 0;
}

void urutanPewaris(nbAddr tr)
{
	boolean visit = true;
	int i = 1;
	if (tr == NULL)
	{
		gotoxy(105, 15);
		printf("Pewaris Kosong");
	}
	else
	{
		gotoxy(105, 15);
		printf("Data Pewaris Tahta");
		// check apakah ada first son atau tidak
		if (fs(tr) != NULL)
		{
			while (parent(tr) != NULL || visit)
			{
				if (fs(tr) != NULL && visit)
				{
					tr = fs(tr);
					gotoxy(105, 17 + i);
					if(jenis_kelamin(tr) == 'L' && i == 1){
						printf("%d. %s   -  RAJA ", i, nama(tr), fs(tr)->jenis_kelamin);
					} else if(jenis_kelamin(tr) == 'P' && i == 1){
						printf("%d. %s   -  RATU ", i, nama(tr), fs(tr)->jenis_kelamin);
					} else {
						printf("%d. %s", i, nama(tr));
					}
					i++;
				}
				else
				{
					if (nb(tr) != NULL)
					{
						tr = nb(tr);
						gotoxy(105, 17 + i);
						printf("%d. ", i);
						printf("%s", nama(tr));
						visit = true;
						i++;
					}
					else
					{
						tr = parent(tr);
						visit = false;
					}
				}
			}
		}
		else
		{
			gotoxy(101, 17);
			printf("Belum ada pewaris\n");
		}
	}
}

void nbUpgrade(nbAddr *root)
{
	nbAddr temp;
	temp = (*root)->nb;
	if ((*root)->fs == NULL)
		(*root)->fs = temp;
	while (temp != NULL)
	{
		temp->parent = *root;
		temp = temp->nb;
	}
}
int nbDepth(nbAddr root)
{
	int y,z;

	if(root==NULL)
		return -1;
	y=nbDepth(root->fs);
	z=nbDepth(root->nb);
	if (y > z)
		return (y+1);
	else
		return (z+1);
}

void nbLevelOrder(nbAddr root,int curLevel, int desLevel)
{
	if(root!=NULL)
	{
		// munculkan semua anak yang ada di root, dan root jangan di munculkan
		if(curLevel==desLevel)
		{
			// jangan munculkan root
			if(strcmp(nama(root),"root")!=0)
			{
				gotoxy(105,20+curLevel);
				printf("%s\n",nama(root));
			}
		}
		else
		{
			nbLevelOrder(root->fs,curLevel,desLevel);
			nbLevelOrder(root->nb,curLevel+1,desLevel);
		}
	}
}

TnbTreeNode *SearchNode(TreeSilsilah tree, nbType nama)
{
	TnbTreeNode *node = tree.root;
	while (node != NULL)
	{
		if (strcmp(nama(node), nama) == 0)
		{
			return node;
		}
		if (fs(node) != NULL)
		{
			node = fs(node);
		}
		else
		{
			if (nb(node) != NULL)
			{
				node = nb(node);
			}
			else
			{
				while (nb(node) == NULL && node != tree.root)
				{
					node = parent(node);
				}
				node = nb(node);
			}
		}
	}
	return NULL;
}

//Delete Tengah
void nbDelete(nbAddr *pDel, TreeSilsilah *pTree){
	nbAddr pCur,pAdd,pTemp;
	pCur=*pDel;

	if (pCur==pTree->root && pCur->fs==NULL){
		pTree->root=NULL;
		return;
	}

	while(pCur->fs!=NULL)
		pCur=pCur->fs;

	while (pCur!=*pDel){
		nbUpgrade(&pCur);
		if (pCur->parent!=NULL)
			pCur->nb=pCur->parent->nb;
		else
			pCur->nb=NULL;
		pCur=pCur->parent;
	}

	if (pCur->parent != NULL)
		pAdd = pCur->parent->fs;
	else
		pAdd = pCur;
	while(pAdd->nb != *pDel && pAdd != *pDel){
		pAdd = pAdd->nb;
	}
	if (pAdd != *pDel){
		if (pCur->fs != NULL)
			pAdd->nb = pCur->fs;
		else 
			pAdd->nb = pCur->nb;
	}
	else if (pCur->nb != NULL && pAdd->parent != NULL){
		pAdd->parent->fs = pCur->nb;
	}
	else {
		pTree->root = pCur->fs;
	}
	if (pCur->fs!=NULL)
		pCur->fs->parent=pCur->parent;
	if (pCur->parent==NULL)
		pTree->root=pCur;
}

// Delete Raja and Upgrade
void nbDelete2(nbAddr *pDel, TreeSilsilah *pTree){
	nbAddr pCur;
	pCur=*pDel;

	if (pCur==pTree->root && pCur->fs==NULL){
		pTree->root=NULL;
		return;
	}

	while(pCur->fs!=NULL)
		pCur=pCur->fs;

	while (pCur!=*pDel){
		nbUpgrade(&pCur);
		if (pCur->parent!=NULL)
			pCur->nb=pCur->parent->nb;
		else
			pCur->nb=NULL;
		pCur=pCur->parent;
	}

	if (pCur->parent!=NULL)
		pCur->parent->fs=pCur->fs;
	if (pCur->fs!=NULL)
		pCur->fs->parent=pCur->parent;
	if (pCur->parent==NULL)
		pTree->root=pCur;
}

//*
void nbDelete(TreeSilsilah *tree, nbType pTree)
{
	TnbTreeNode *pSearch, *temp, *pDelete, *raja;
	pSearch = SearchNode(*tree, pTree);
	raja = tree->root;

	if (pSearch == NULL)
	{
		gotoxy(100, 20);
		printf("Nama tidak ditemukan");
	}
	else
	{
		if (fs(pSearch) == NULL && nb(pSearch) == NULL)
		{
			if (pSearch == tree->root)
			{
				tree->root = NULL;
			}
			else
			{
				if (parent(pSearch)->fs == pSearch)
				{
					parent(pSearch)->fs = NULL;
				}
				else
				{
					parent(pSearch)->nb = NULL;
				}
			}
		}
		else
		{
			if (fs(pSearch) != NULL && nb(pSearch) == NULL)
			{
				if (pSearch == tree->root)
				{
					tree->root = fs(pSearch);
					fs(pSearch)->parent = NULL;
				}
				else
				{
					if (parent(pSearch)->fs == pSearch)
					{
						parent(pSearch)->fs = fs(pSearch);
						fs(pSearch)->parent = parent(pSearch);
					}
					else
					{
						parent(pSearch)->nb = fs(pSearch);
						fs(pSearch)->parent = parent(pSearch);
					}
				}
			}
			else
			{
				if (fs(pSearch) == NULL && nb(pSearch) != NULL)
				{
					if (pSearch == tree->root)
					{
						tree->root = nb(pSearch);
						nb(pSearch)->parent = NULL;
					}
					else
					{
						if (parent(pSearch)->fs == pSearch)
						{
							parent(pSearch)->fs = nb(pSearch);
							nb(pSearch)->parent = parent(pSearch);
						}
						else
						{
							parent(pSearch)
								->nb = nb(pSearch);
							nb(pSearch)->parent = parent(pSearch);
						}
					}
				}
				else
				{
					if (fs(pSearch) != NULL && nb(pSearch) != NULL)
					{
						temp = fs(pSearch);
						while (nb(temp) != NULL)
						{
							temp = nb(temp);
						}
						if (pSearch == tree->root)
						{
							tree->root = temp;
							temp->parent = NULL;
						}
						else
						{
							if (parent(pSearch)->fs == pSearch)
							{
								parent(pSearch)->fs = temp;
								temp->parent = parent(pSearch);
							}
							else
							{
								parent(pSearch)->nb = temp;
								temp->parent = parent(pSearch);
							}
						}
						pDelete = nb(temp);
						nb(temp) = NULL;
						nb(pDelete) = fs(pSearch);
						fs(pDelete)->parent = pDelete;
						fs(pSearch) = NULL;
					}
				}
			}
		}
	}
}

void menuHitungAnak(nbAddr treeSilsilahTemp){
	nbType parentTempInput;
	int src;
	gotoxy(101, 17);
	// cetakSilsilah(Tree.root, str);
	printf("Masukkan nama parent : ");
	fflush(stdin);
	gets(parentTempInput);

	// cek parent apakah ada
	if (nbSearch(treeSilsilahTemp, parentTempInput) == NULL)
	{
		gotoxy(101, 18);
		printf("Parent tidak ditemukan");
	}
	src = hitungAnak(treeSilsilahTemp, parentTempInput);
	if (src == NULL)
	{
		gotoxy(101, 18);
		printf("Parent %s tidak memiliki anak", parentTempInput);
	}
	gotoxy(101, 19);
	printf("Jumlah anak dari %s yaitu : %d", parentTempInput, src);
}

void opsiDeleteAnggotaKerajaan(nbAddr treeSilsilahTemp, TreeSilsilah treeTemp){
	int bunuh;
	nbType namaNode;
	nbAddr srcNode;

	gotoxy(101, 15);
	printf("Pilih Opsi Tahta");
	gotoxy(101, 16);
	printf("1. Turunkan Tahta Raja atau Bunuh keturunan dari Raja"); // delete raja
	gotoxy(101, 17);
	printf("2. Bunuh Saudara Raja Atau keturunan dari Saudara Raja"); // delete anak
	gotoxy(101, 18);
	printf("Pilih no : ");
	scanf("%d", &bunuh);
	switch (bunuh)
	{
	case 1:
		gotoxy(101, 19);
		printf("Masukkan nama : ");
		scanf("%s", &namaNode);
		if ((srcNode = nbSearch(treeSilsilahTemp, namaNode)) != NULL)
		{
			nbDelete2(&srcNode, &treeTemp);
			gotoxy(101, 22);
			printf("%s telah diturunkan tahtanya", namaNode);
		}
		else
		{
			gotoxy(101, 22);
			printf("Data tidak ditemukan");
		}
		break;
		case 2:
		int i;
		gotoxy(101, 20);
		for(i=0;i<=nbDepth(treeSilsilahTemp);i++)
		{
			nbLevelOrder(treeSilsilahTemp,1,i);
		}
		gotoxy(101, 21);
		printf("Masukkan Saudara Raja     : ");
		scanf("%s", &namaNode);
		if ((srcNode = nbSearch(treeSilsilahTemp, namaNode)) != NULL)
		{
			nbDelete(&srcNode, &treeTemp);
			gotoxy(101, 22);
			printf("Data telah dihapus");
		}
		else
		{
			gotoxy(101, 22);
			printf("Data tidak ditemukan");
		}
		break;
			
		default:
			gotoxy(101, 22);
			printf("Pilihan tidak ada");
		break;
	} 

}