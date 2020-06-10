//Projet: PAIRC (Projet Analyse Image Reconnaissance Caractere)
//Auteurs: Blandine DEDDE, Brice GIRARDEAU DARNAND, Victor MARQUET

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "Fonction.h"


/*
R: Permet d'allouer un espace mémoire pour le type IMAGE en fonction de sa taille. 
E: nombre de ligne et nombre de colonne de la matrice correspondant au BitMap de l'Image
S: Image de type IMAGE
*/
IMAGE allocationImage(int Nblig, int Nbcol)
{
	IMAGE mat = { 0,0,NULL,NULL };
	int i;

	mat.Nblig = Nblig;
	mat.Nbcol = Nbcol;
	mat.data = (unsigned char*)malloc(Nblig*Nbcol * sizeof(unsigned char));
	if (mat.data == NULL)
		return(mat);
	mat.pixel = (unsigned char**)malloc(Nblig * sizeof(unsigned char*));
	if (mat.pixel == NULL) {
		free(mat.data);

		mat.data = NULL;
		return(mat);
	}
	for (i = 0; i < Nblig; i++)
		mat.pixel[i] = &mat.data[i*Nbcol];

	return(mat);
}

/*
R: Permet d'allouer un espace mémoire pour le type MATRICE en fonction de sa taille.
E: nombre de ligne et nombre de colonne de la matrice
S: matrice 2D de type MATRICE
*/
MATRICE allocationMatrice(int Nblig, int Nbcol)

{
	MATRICE mat = { 0,0,NULL,NULL };
	int i;

	mat.Nblig = Nblig;
	mat.Nbcol = Nbcol;
	mat.data = (int*)malloc(Nblig*Nbcol * sizeof(int));
	if (mat.data == NULL)
		return(mat);
	mat.pixel = (int**)malloc(Nblig * sizeof(int*));
	if (mat.pixel == NULL) {
		free(mat.data);

		mat.data = NULL;
		return(mat);
	}
	for (i = 0; i < Nblig; i++)
		mat.pixel[i] = &mat.data[i*Nbcol];

	return(mat);
}

/*
R: Libère l'espace mémoire occupé par une image
E: Image de type IMAGE
S: void
*/
void liberationImage(IMAGE *img)
{
	if (img->data != NULL) {
		free(img->data);
		img->data = NULL;
	}
	if (img->pixel != NULL) {
		free(img->pixel);
		img->pixel = NULL;
	}
}

/*
R: Récupère une image en type IMAGE à partir de son nom dans le répertoire de travail
E: nom du fichier (avec son extention)
S: Image de type IMAGE
*/
IMAGE lectureImage(const char *in)
{
	FILE *F = NULL;
	IMAGE img = { 0,0,NULL };
	int dynamique = 0;

	if ((F = fopen(in, "r")) == NULL)
	{
		printf("Pb image inexistante");
	}
	else
	{
		char type[3];

		fgets(type, 3, F);
		fclose(F);
		/* selon le type ouverture binaire ou texte */

		if (strcmp(type, "P2") == 0)  /* cas ASCII niveaux de gris */
		{
			char buf;

			F = fopen(in, "r");

			/* lecture caractère après caractère compte-tenu de la diversité des entêtes possibles */
			fscanf(F, "%c", &type[0]);
			fscanf(F, "%c", &type[1]);
			fscanf(F, "%c", &buf); /* caractère espacement */

			fscanf(F, "%c", &buf);
			if (buf == '#') {
				/* on ignore tout jusqu'à trouver '\n' */
				while (buf != '\n')
					fscanf(F, "%c", &buf);
				fscanf(F, "%c", &buf);
			}
			while (((buf - '0') >= 0) && ((buf - '0') <= 9)) { /* possibilité d'utiliser également isdigit de la librairie standard <ctype.h> */
				img.Nbcol = img.Nbcol * 10 + (buf - '0');
				fscanf(F, "%c", &buf);
			}

			fscanf(F, "%c", &buf);
			if (buf == '#') {
				/* on ignore tout jusqu'à trouver '\n' */
				while (buf != '\n')
					fscanf(F, "%c", &buf);
				fscanf(F, "%c", &buf);
			}
			while (((buf - '0') >= 0) && ((buf - '0') <= 9)) {
				img.Nblig = img.Nblig * 10 + (buf - '0');
				fscanf(F, "%c", &buf);
			}

			fscanf(F, "%c", &buf);
			if (buf == '#') {
				/* on ignore tout jusqu'à trouver '\n' */
				while (buf != '\n')
					fscanf(F, "%c", &buf);
				fscanf(F, "%c", &buf);
			}
			while (((buf - '0') >= 0) && ((buf - '0') <= 9)) {
				dynamique = dynamique * 10 + (buf - '0');
				fscanf(F, "%c", &buf);
			}

			/* début des data */

			printf("Lecture image NG type %s avec %d lignes et %d colonnes...\n", type, img.Nblig, img.Nbcol);

			/* taille connue, allocation dynamique possible */
			img = allocationImage(img.Nblig, img.Nbcol);

			/* lecture pixel par pixel */
			{
				int i, j;
				int tmp;

				for (i = 0; i < img.Nblig; i++)
					for (j = 0; j < img.Nbcol; j++)
					{
						fscanf(F, "%d", &tmp);
						img.pixel[i][j] = (unsigned char)tmp;
					}
			}
		}
		else
			if (strcmp(type, "P5") == 0)  /* cas brut niveaux de gris */
			{
				char buf;

				F = fopen(in, "rb");

				/* lecture caractère après caractère compte-tenu de la diversité des entêtes possibles */
				type[0] = fgetc(F);
				type[1] = fgetc(F);
				buf = fgetc(F); /* caractère espacement */

				buf = fgetc(F);
				if (buf == '#') {
					/* on ignore tout jusqu'à trouver '\n' */
					while (buf != '\n')
						buf = fgetc(F);
					buf = fgetc(F);
				}
				while (((buf - '0') >= 0) && ((buf - '0') <= 9)) { /* possibilité d'utiliser également isdigit de la librairie standard <ctype.h> */
					img.Nbcol = img.Nbcol * 10 + (buf - '0');
					buf = fgetc(F);
				}

				buf = fgetc(F);
				if (buf == '#') {
					/* on ignore tout jusqu'à trouver '\n' */
					while (buf != '\n')
						buf = fgetc(F);
					buf = fgetc(F);
				}
				while (((buf - '0') >= 0) && ((buf - '0') <= 9)) {
					img.Nblig = img.Nblig * 10 + (buf - '0');
					buf = fgetc(F);
				}

				buf = fgetc(F);
				if (buf == '#') {
					/* on ignore tout jusqu'à trouver '\n' */
					while (buf != '\n')
						buf = fgetc(F);
					buf = fgetc(F);
				}
				while (((buf - '0') >= 0) && ((buf - '0') <= 9)) {
					dynamique = dynamique * 10 + (buf - '0');
					buf = fgetc(F);
				}

				/* début des data */

				printf("Lecture image NG type %s avec %d lignes et %d colonnes...\n", type, img.Nblig, img.Nbcol);

				/* taille connue, allocation dynamique possible */
				img = allocationImage(img.Nblig, img.Nbcol);

				/* lecture d'un bloc */
				fread(img.data, sizeof(unsigned char), img.Nbcol*img.Nblig, F);
			}
			else
				printf("Format non supporte pour l'instant...\n");
		fclose(F);
	}
	return img;
}

/*
R: Enregistre une image de type IMAGE en fichier ".pgm"
E:	Image de type IMAGE à enregistrer
	"P2" ou "P5" en foction du format d'enregistrement
	chemin et nom du fichier d'enregistrement (ex: "C:\\image.pgm")
S: void
*/
void sauvegardeImage(IMAGE img, const char *type, const char *out)
{
	FILE *F = NULL;

	if (img.data) /* image non vide */
	{
		printf("Sauvegarde image au type %s avec %d lignes et %d colonnes...\n", type, img.Nblig, img.Nbcol);
		/* selon le type ouverture binaire ou texte */
		if (strcmp(type, "P2") == 0)  /* cas ASCII niveaux de gris */
		{
			F = fopen(out, "w");

			fprintf(F, "%s\n", type);
			fprintf(F, "# Created by TSE FISA IPSI\n");
			fprintf(F, "%d %d %d\n", img.Nbcol, img.Nblig, 255);
			/* sauvegarde pixel par pixel */
			{
				int i, j;

				for (i = 0; i < img.Nblig; i++)
					for (j = 0; j < img.Nbcol; j++)
						fprintf(F, "%d ", img.pixel[i][j]);
			}
			fclose(F);
		}
		else
			if (strcmp(type, "P5") == 0)  /* cas brut niveaux de gris */
			{
				char tmp[255];

				F = fopen(out, "wb");

				fputs("P5\n", F);
				fputs("# Created by TSE FISA IPSI\n", F);
				sprintf(tmp, "%d %d %d\n", img.Nbcol, img.Nblig, 255);
				fputs(tmp, F);
				/* sauvegarde par bloc */
				fwrite(img.data, sizeof(unsigned char), img.Nbcol*img.Nblig, F);
				fclose(F);
			}
	}
	else
		printf("Image vide\n");
}

/*
R: Permet d'allouer un espace mémoire pour le un tableau d'entier de type TABLEAU_INT
E: nombre d'elements du tableau
S: tableau d'entier de type TABLEAU_INT
*/
TABLEAU_INT allocationTableau(int n)
{
	TABLEAU_INT t = { 0,NULL };

	t.size = n;
	t.data = (int*)calloc(n, sizeof(int));

	return(t);
}

/*
R: Permet d'allouer un espace mémoire pour le un tableau de double de type TABLEAU_DOUBLE
E: nombre d'elements du tableau
S: tableau d'entier de type TABLEAU_DOUBLE
*/
TABLEAU_DOUBLE allocationTableauDouble(int n)
{
	TABLEAU_DOUBLE t = { 0,NULL };

	t.size = n;
	t.data = (int*)calloc(n, sizeof(int));

	return t;
}

/*
R:	Permet de faire l'histogramme d'une Image de type IMAGE dans un tableau d'entier
E:	Image de type IMAGE
	entier permettant d'enregistrer le tableau dans un csv si différent de 0
S:	un tableau d'entier de type TABLEAU_INT
*/
TABLEAU_INT histogrammeImage(IMAGE img, int choix)
{
	TABLEAU_INT h = { 0,NULL };

	if (img.data)
	{
		int i;

		h = allocationTableau(256);

		for (i = 0; i < img.Nbcol*img.Nblig; i++)
			h.data[(int)img.data[i]] += 1;

		if (choix)
		{
			/* sauvegarde dans histo.csv */
			FILE *F;

			F = fopen("..\\Res\\histo.csv", "w");
			int i;
			for (i = 0; i < h.size; i++)
				fprintf(F, "%d\n", h.data[i]);
			fclose(F);
		}
	}

	return h;
}

/*
R:	fonction d'affichage des informations du projet
E:	void
S:	void
*/
void Initialisation(void)
{
	printf("*-*-*-*-*-*-*-*-*_Projet PAIRC_*-*-*-*-*-*-*-*-*\n*_Projet Analyse Image Reconnaissance Caractere_*\n\n");
	printf("Auteurs: Blandine DEDDE, Brice GIRARDEAU DARNAND, Victor MARQUET\n\n\n");
}

/*
R:	Permet de demander l'ouverture un fichier ".pgm" dans le répertoire de travail sans utiliser son nom
E:	void (entrée de l'utilisateur)
S:	image de type IMAGE
*/
IMAGE choixfichier()
{
	char namefile[10];
	IMAGE img;

	printf("\nChoisissez un fichier\n");
	scanf("%s", &namefile);
	strcat(namefile, ".pgm");
	img = lectureImage(namefile);
	return img;
}

/*
R:	Permet la Binarisation d'une image de type image
E:	Image de type image en niveau de gris
S:	Image de type image avec que deux valeurs de gris (0 et 255)
*/
IMAGE Binarisation(IMAGE img, int seuil)
{
	IMAGE BW;
	BW = allocationImage(img.Nblig, img.Nbcol);

	for (int i = 0; i < img.Nblig*img.Nbcol; i++)
	{
		if (img.data[i] > seuil) BW.data[i] = 255;
		else BW.data[i] = 0;
	}
	return BW;
}

/*
R:	permet d'inverser les pixel d'une image
E:	Image de type IMAGE
S:	Image de type IMAGE
*/
IMAGE Inversion(IMAGE img)
{
	IMAGE inv;
	inv = allocationImage(img.Nblig, img.Nbcol);

	for (int i = 0; i < img.Nblig*img.Nbcol; i++)
	{
		inv.data[i] = 255 - img.data[i];
	}
	return inv;
}

/*
R: Permet de soustraire une image d'une autre pixel par pixel comme Psortie= Pimg1 - Pimg2
E:	2 images de type IMAGE
S:	Une image de type IMAGE
*/
IMAGE SoustractionImage(IMAGE img1, IMAGE img2)
{
	IMAGE sub;
	sub = allocationImage(img1.Nblig, img1.Nbcol);

	if (img1.Nblig*img1.Nbcol == img2.Nblig*img2.Nbcol)
	{
		for (int i = 0; i < img1.Nblig*img1.Nbcol; i++)
		{
			sub.data[i] = img1.data[i] - img2.data[i];
		}
	}
	else sub = img1;
	return sub;
}

/*
R:	Permet de rentrer le nom d'un élément structurant prédéfinit et d'en crée son image correspondant
E:	nom de l'élement structurant souhaité
	Possibilité: V4, V8
S:	Image de type Image de l'element structurant
*/
IMAGE ElementStructurant(const char *type)
{
	IMAGE ES;
	if (type == "V4")
	{
		ES = allocationImage(3, 3);
		int mat[3][3] = { {0, 1, 0 }, {1, 1, 1 }, {0, 1, 0 } };
		for (int x = 0; x < 3; x++)
		{
			for (int y = 0; y < 3; y++)
			{
				ES.pixel[x][y] = mat[x][y];
			}
		}
	}
	if (type == "V8")
	{
		ES = allocationImage(3, 3);
		for (int i = 0; i < ES.Nbcol*ES.Nblig; i++) ES.data[i] = 1;
	}

	return ES;
}

/*
R:	Permet l'érosion d'une image par un element structurant
E:	Image de type image
	Element structurant de type Image
S:	Image de type image
*/
IMAGE Erosion(IMAGE img, IMAGE ES)
{
	IMAGE out, temp;
	out = allocationImage(img.Nblig, img.Nbcol);
	temp = allocationImage(ES.Nblig, ES.Nbcol);

	for (int ix = 0; ix < img.Nbcol; ix++)
	{
		for (int iy = 0; iy < img.Nblig; iy++)
		{
			int somme = 0;
			int not_null = 0;
			int resultpix = 1;

			for (int jx = 0; jx < ES.Nbcol; jx++)
			{
				for (int jy = 0; jy < ES.Nblig; jy++)
				{
					if (
						(ix + jx - (ES.Nblig / 2)) >= 0 &&
						(ix + jx - (ES.Nblig / 2)) < img.Nbcol &&
						(iy + jy - (ES.Nbcol / 2)) >= 0 &&
						(iy + jy - (ES.Nbcol / 2)) < img.Nblig
						)
					{
						temp.pixel[jx][jy] = img.pixel[ix + jx - (ES.Nbcol / 2)][iy + jy - (ES.Nbcol / 2)];
						not_null++;
					}
				}
			}
			
			for (int kx = 0; kx < temp.Nbcol; kx++)
			{
				for (int ky = 0; ky < temp.Nblig; ky++)
				{

					if (not_null == temp.Nbcol*temp.Nblig)
					{
						resultpix *= (temp.pixel[kx][ky] > 0);
					}
					else
					{
						resultpix = img.pixel[ix][iy];
					}
				}
			}
			out.pixel[ix][iy] = (resultpix > 0) * 255;		
		}		
	}

	return out;
}

/*
R:	Permet la dilatation d'une image par un element structurant
E:	Image de type image
	Element structurant de type Image
S:	Image de type image
*/
IMAGE Dilatation(IMAGE img, IMAGE ES)
{
	IMAGE out, temp;
	out = allocationImage(img.Nblig, img.Nbcol);
	temp = allocationImage(ES.Nblig, ES.Nbcol);

	for (int ix = 0; ix < img.Nbcol; ix++)
	{
		for (int iy = 0; iy < img.Nblig; iy++)
		{
			int somme = 0;
			int not_null = 0;
			int resultpix = 0;

			for (int jx = 0; jx < ES.Nbcol; jx++)
			{
				for (int jy = 0; jy < ES.Nblig; jy++)
				{
					if (
						(ix + jx - (ES.Nblig / 2)) >= 0 &&
						(ix + jx - (ES.Nblig / 2)) < img.Nbcol &&
						(iy + jy - (ES.Nbcol / 2)) >= 0 &&
						(iy + jy - (ES.Nbcol / 2)) < img.Nblig
						)
					{
						temp.pixel[jx][jy] = img.pixel[ix + jx - (ES.Nbcol / 2)][iy + jy - (ES.Nbcol / 2)];
						not_null++;
					}
				}
			}

			for (int kx = 0; kx < temp.Nbcol; kx++)
			{
				for (int ky = 0; ky < temp.Nblig; ky++)
				{
					if (not_null == temp.Nbcol*temp.Nblig)
					{
						resultpix += (ES.pixel[kx][ky] > 0) * (temp.pixel[kx][ky] > 0);
					}
					else
					{
						resultpix = img.pixel[ix][iy];
					}
				}
			}
			out.pixel[ix][iy] = (resultpix > 0) * 255;
		}
	}
	return out;
}

/*
R:	Permet le faire une ouverture morphologique d'une image par un element structurant
E:	Image de type image
	Element structurant de type Image
S:	Image de type image
*/
IMAGE Ouverture(IMAGE img, IMAGE ES)
{
	IMAGE out;
	out = allocationImage(img.Nblig, img.Nbcol);

	out = Erosion(out, ES);
	out = Dilatation(img, ES);

	return out;
}

/*
R:	Permet le faire une fermeture morphologique d'une image par un element structurant
E:	Image de type image
	Element structurant de type Image
S:	Image de type image
*/
IMAGE Fermeture(IMAGE img, IMAGE ES)
{
	IMAGE out;
	out = allocationImage(img.Nblig, img.Nbcol);

	out = Dilatation(img, ES);
	out = Erosion(out, ES);

	return out;
}

/*
R:	Permet de trouver le squelete d'une image binaire par morphologie avec un element structurant (ne fonctionne pas)
E:	Image de type image
	Element structurant de type Image
S:	Image de type image
*/
IMAGE squelette(IMAGE img, IMAGE ES, const char *rep)
{

	IMAGE out, temp, comparaison;
	out = allocationImage(img.Nblig, img.Nbcol);
	temp = allocationImage(img.Nblig, img.Nbcol);
	comparaison = allocationImage(img.Nblig, img.Nbcol);


	for (int i = 0; i < img.Nblig* img.Nbcol; i++)
	{
		out.data[i] = 0;
		temp.data[i] = 0;
		comparaison.data[i] = 1;
	}
	if (0)
	{
		int test = rep - 48;
		test--;
		for (int i = 0; i < rep; i++)
		{
			temp = SoustractionImage(Erosion(img, ES), Ouverture(Erosion(img, ES), ES));
			for (int j = 0; j < img.Nblig* img.Nbcol; j++)
			{
				out.data[i] = (temp.data[i] > 0) * 10 * i;
			}
		}
	}
	else if(0)
	{

		int i = 1;
		temp.data[i] = img.data[i];
		while (comparaison.data != temp.data && i<10)
		{
			comparaison.data = temp.data;
			temp = SoustractionImage(Erosion(temp, ES), Ouverture(Erosion(temp, ES), ES));
			for (int j = 0; j < img.Nblig* img.Nbcol; j++)
			{
				out.data[i] += temp.data[i];
			}
			i++;
		}
		for (int i = 0; i < img.Nblig* img.Nbcol; i++) out.data[i] = (out.data[i]>0)*250;
	}
	else
	{
		out = SoustractionImage(Erosion(img, ES), Ouverture(Erosion(img, ES), Fermeture(ES,ES)));
		comparaison.data = out.data;
		//while (comparaison.data != temp.data)
		/*for(int j=0;j<20;j++)
		{
			temp.data = comparaison.data;
			for (int i = 0; i < img.Nblig* img.Nbcol; i++) out.data[i] = ((out.data[i] > 0) || (temp.data[i] > 0)) * 250;
			comparaison = SoustractionImage(Erosion(temp, ES), Fermeture(Erosion(temp, ES), ES));
			
		}*/
		for (int i = 0; i < img.Nblig* img.Nbcol; i++) out.data[i] = ((out.data[i] > 0) || (temp.data[i] > 0)) * 250;
	}
	return out;	
}

/*
R:	Calcul la surface en pixel d'un objet
E:	Image de type image
	la couleur de l'image 'b' ou 'w' pour black and white
S:	un entier correspondant au nombre de pixel de la couleur demandé
*/
int CalculAire(IMAGE img,char CouleurObjet)
{
	int aire = 0;
	int BW = 128;
	if (CouleurObjet == 'b') for (int i = 0; i < img.Nbcol*img.Nblig; i++)aire += (img.data[i] > BW);
	else if (CouleurObjet == 'w') for (int i = 0; i < img.Nbcol*img.Nblig; i++)aire += (img.data[i] < BW);
	else aire = img.Nbcol*img.Nblig;
	return aire;
}

/*
R:	Permet d'exporter les resultats d'une fonction sur de nombreux fichiers 
E:	Nom de la fonction à automatiser en chaîne de caractères: "Aire", "Aire Top-Hat", "Boucle"
	Entier correspondant au nom du premier fichier à tester,
	Entier correspondant au nom du dernier fichier à tester,
S:	Void (mais resultats dans le fichier "result.csv")
*/
void Test2Fonction(char *NomFonction, int PremierFichier, int DernierFichier)
{
	IMAGE img;
	char namefile[10];
	TABLEAU_INT remplissage = allocationTableau(10);
	MATRICE res_caractere = allocationMatrice(10, DernierFichier - PremierFichier);
	int equiv;

	for (int i = PremierFichier; i <= DernierFichier; i++)
	{
		sprintf(namefile,"%d", i);
		strcat(namefile, ".pgm");
		img = lectureImage(namefile);
		equiv = CaractereEquiv(i);
		if(NomFonction == "Aire")	res_caractere.pixel[equiv][remplissage.data[equiv]] = CalculAire(Binarisation(img, 128), 'b');
		if (NomFonction == "Aire Top-Hat")	res_caractere.pixel[equiv][remplissage.data[equiv]] = CalculAire(SoustractionImage(Fermeture(Binarisation(img, 128),ElementStructurant("V8")),Binarisation(img, 128)), 'b');
		if (NomFonction == "Boucle") res_caractere.pixel[equiv][remplissage.data[equiv]] = NbComposante(Boucle(Inversion(Binarisation(img, 128))));
		if (NomFonction == "Centre de gravite")
		{
			POINT P1 = { 0,0 };
			res_caractere.pixel[equiv][remplissage.data[equiv]] = (int)DistancePixels(CentreGravite(img), P1);
		}
		remplissage.data[equiv]++;
	}

	//Enregistrement dans "result.csv"
	FILE *F;
	F = fopen("..\\..\\Projet_Analyse_Image_Reconnaissance_Caractere\\out\\result.csv", "w");
	fprintf(F, "%s;de;%d;%d\n\ncaractère;min;max\n", NomFonction, PremierFichier, DernierFichier);
	for (int i = 0; i < remplissage.size; i++)
	{
		int j = 0;
		int max=0, min=0;
		while (j < remplissage.data[i])
		{
			printf("%d\n", res_caractere.pixel[i][j]);
			if (max == 0 || max < res_caractere.pixel[i][j]) max = res_caractere.pixel[i][j];
			if (min == 0 || min > res_caractere.pixel[i][j]) min = res_caractere.pixel[i][j];
			j++;
		}

		fprintf(F, "%d;%d;%d\n", i, min, max);
	}
	fclose(F);

}

/*
R:	permet d'avoir l'équivalence du caractère avec le nom de fichier
E:	Entier du nom de fichier
S:	Entier du caractère sur l'image
*/
int CaractereEquiv(int fichier)
{
	int equiv;

	switch ((fichier - 388) % 10)
	{
	case 0:
		equiv = 1;
		break;
	case 1:
		equiv = 0;
		break;
	case 2:
		equiv = 9;
		break;
	case 3:
		equiv = 2;
		break;
	case 4:
		equiv = 3;
		break;
	case 5:
		equiv = 4;
		break;
	case 6:
		equiv = 5;
		break;
	case 7:
		equiv = 6;
		break;
	case 8:
		equiv = 7;
		break;
	case 9:
		equiv = 8;
		break;
	default:
		equiv = 10;
		break;
	}

	return equiv;
}

/*
R:	Permet de faire un moyennage d'une image de type IMAGE
E:	Image de type IMAGE
	Nombre de ligne de l'element structurant
	Nombre de colonne de l'element structurant
S:	Image de type IMAGE
*/
IMAGE FiltrageMoyen(IMAGE img, int Nbligne, int Nbcolonne)
{
	IMAGE out, temp, ES;

	ES = allocationImage(Nbligne, Nbcolonne);
	for (int i = 0; i < ES.Nbcol*ES.Nblig; i++) ES.data[i] = 1;

	out = allocationImage(img.Nblig, img.Nblig);
	temp = allocationImage(ES.Nblig, ES.Nbcol);


	for (int ix = 0; ix < img.Nbcol; ix++)
	{
		for (int iy = 0; iy < img.Nblig; iy++)
		{
			int somme = 0;
			int not_null = 0;

			for (int jx = 0; jx < ES.Nbcol; jx++)
			{
				for (int jy = 0; jy < ES.Nblig; jy++)
				{
					int test = ES.Nblig / 2;
					if (
						(ix + jx - (ES.Nblig / 2)) >= 0 &&
						(ix + jx - (ES.Nblig / 2)) < img.Nbcol &&
						(iy + jy - (ES.Nbcol / 2)) >= 0 &&
						(iy + jy - (ES.Nbcol / 2)) < img.Nblig
						)
					{
						temp.pixel[jx][jy] = img.pixel[ix + jx - (ES.Nblig / 2)][iy + jy - (ES.Nbcol / 2)];
						not_null++;
					}
					else
					{
						temp.pixel[jx][jy] = -1;
					}
				}
			}

			for (int kx = 0; kx < temp.Nbcol; kx++)
			{
				for (int ky = 0; ky < temp.Nblig; ky++)
				{

					if (temp.pixel[kx][ky] != -1)
					{
						somme += ES.pixel[kx][ky] * temp.pixel[kx][ky];
						not_null++;
					}
				}
			}
			out.pixel[ix][iy] = somme / not_null;
		}
	}

	return out;
}

/*
R:	Permet de faire une detection de contour d'une image de type IMAGE
E:	Image de type IMAGE
S:	Image de type IMAGE
*/
IMAGE FiltrePasseHaut(IMAGE img)
{
	IMAGE out, temp, ES;

	ES = allocationImage(3, 3);
	int mat[3][3] = { {0, 1, 0 }, {1, -4, 1 }, {0, 1, 0 } };
	for (int x = 0; x < 3; x++)
	{
		for (int y = 0; y < 3; y++)
		{
			ES.pixel[x][y] = mat[x][y];
		}
	}


	out = allocationImage(img.Nblig, img.Nblig);
	temp = allocationImage(ES.Nblig, ES.Nbcol);


	for (int ix = 0; ix < img.Nbcol; ix++)
	{
		for (int iy = 0; iy < img.Nblig; iy++)
		{
			int somme = 0;
			int not_null = 0;

			for (int jx = 0; jx < ES.Nbcol; jx++)
			{
				for (int jy = 0; jy < ES.Nblig; jy++)
				{
					int test = ES.Nblig / 2;
					if (
						(ix + jx - (ES.Nblig / 2)) >= 0 &&
						(ix + jx - (ES.Nblig / 2)) < img.Nbcol &&
						(iy + jy - (ES.Nbcol / 2)) >= 0 &&
						(iy + jy - (ES.Nbcol / 2)) < img.Nblig
						)
					{
						temp.pixel[jx][jy] = img.pixel[ix + jx - (ES.Nblig / 2)][iy + jy - (ES.Nbcol / 2)];
						not_null++;
					}
					else
					{
						temp.pixel[jx][jy] = -1;
					}
				}
			}

			for (int kx = 0; kx < temp.Nbcol; kx++)
			{
				for (int ky = 0; ky < temp.Nblig; ky++)
				{

					if (temp.pixel[kx][ky] != -1)
					{
						somme += ES.pixel[kx][ky] * temp.pixel[kx][ky];
					}
				}
			}
			out.pixel[ix][iy] = somme;
		}
	}

	return out;
}

/*
R:	Permet de trouver le centre de gravité d'une image
E:	Image de type IMAGE
S:	Point du centre de gravité de type POINT
*/
POINT CentreGravite(IMAGE Img)
{
	POINT p = { 0,0 };
	int i, j, nbpoint = 0;
	for (i = 0; i < Img.Nblig; i++)
	{
		for (j = 0; j < Img.Nbcol; j++)
		{

			if (Img.pixel[i][j] == 255)
			{
				p.x = p.x + (double)i;
				p.y = p.y + (double)j;
				nbpoint = nbpoint + 1;
			}
		}
	}
	p.x = (int)p.x / (nbpoint);
	p.y = (int)p.y / (nbpoint);
	return p;
}

/*
R:	Permet de trouver la distance entre deux points utiliser pour les pixels dans notre cas
E:	deux points de type POINT
S:	une disatance de type double
*/
double DistancePixels(POINT P1, POINT P2)
{
	double distance;
	distance = sqrt((double)(P1.x - P2.x) + (double)(P1.y - P2.y));
	return distance;
}

/*
R:	Permet de trouver le cercle circonscrit d'une image
E:	Image de type IMAGE
S:	le rayon de type double du cercle circonscrit de centre le centre de gravité de type double
*/
double Cercle_Circonscrit(IMAGE Img)
{
	double R = 0;
	int k = 0;
	POINT pG = { 0,0 };
	POINT Centre = CentreGravite(Img, pG);
	POINT pR = { 0,0 };
	TABLEAU_DOUBLE TabDist;
	TabDist = allocationTableauDouble (Img.Nblig * Img.Nbcol);

	for (int i = 0; i < Img.Nblig; i++)
	{
		for (int j = 0; j < Img.Nbcol; j++)
		{
			if (Img.pixel[i][j] == 255)
			{

				pR.x = (double)i;
				pR.y = (double)j;
				TabDist.data[k] = DistancePixels(Centre, pR);
				k++;
			}
		}
	}
	R = TabDist.data[0];
	for (int i = 1; i < Img.Nblig * Img.Nbcol; i++)
	{
		if (TabDist.data[i] > R && TabDist.data[i] != 0)
		{
			R = TabDist.data[i];
		}
	}
	return R;
}

/*
R:	Permet d'extraire le contenu des bouclesd'une image (ne fonctionne pas)
E:	Image de type IMAGE
S:	Image de type IMAGE
*/
IMAGE Boucle(IMAGE Img)
{
	int boucle = 0;
	IMAGE out, temp;
	temp = allocationImage(Img.Nblig, Img.Nbcol);
	temp = Img;
	out = allocationImage(Img.Nblig, Img.Nbcol);

	for (int i = 0; i < Img.Nblig - 1; i++)
	{
		for (int j = 1; j < Img.Nbcol - 1; j++)
		{
			int somme = 0;

			if (i == 0 || i == Img.Nblig - 1)
			{
				temp.pixel[i][j] = 1;
			}
			else
			{
				for (int a = -1; a < 2; a++)
				{
					for (int b = -1; b < 2; b++)
					{
						if (temp.pixel[i + a][j + b] == 1) somme++;
					}
				}
			}			
			if (somme > 0 || temp.pixel[i][j] == 1)
			{
				temp.pixel[i][j] = 1;
			}
		}
	}

	for (int i = Img.Nblig-2; i > 0; i--)
	{
		for (int j = Img.Nbcol-2; j > 0; j--)
		{
			int somme = 0;
			for (int a = -1; a < 2; a++)
			{
				for (int b = -1; b < 2; b++)
				{
					if (temp.pixel[i + a][j + b] == 1) somme++;
				}
			}

			if (somme > 0 || temp.pixel[i][j] == 1)
			{
				temp.pixel[i][j] = 1;
			}
			
		}
	}

	for (int i = 1; i < Img.Nblig; i++)
	{
		for (int j = 1; j < Img.Nbcol ; j++)
		{
			if (temp.pixel[i][j] == 1 ) out.pixel[i][j] = 255;
			else out.pixel[i][j] = 0;
		}
	}

	return out;
}

/*
R:	Permet de sortir le nombre d'élément dans l'image (ne fonctonne pas)
E:	Image de type IMAGE
S:	nombre de composant de type integer
*/
int NbComposante(IMAGE img)
{
	int nb=1;

	for (int i = img.Nblig - 2; i > 0; i--)
	{
		for (int j = img.Nbcol - 2; j > 0; j--)
		{
			if (img.pixel[i][j] == 255)
			{
				int in = 0;
				for (int a = -1; i < 2; a++)
				{
					for (int b = -1; j < 2; b++)
					{
						if (img.pixel[i + a][j + b] > 0 || img.pixel[i + a][j + b] < 255) in = img.pixel[i + a][j + b];
					}
				}
				if (in > 0) img.pixel[i][j] = in;
				else
				{
					img.pixel[i][j] = nb;
					nb++;
				}
			}
		}
	}

	return nb-1;
}