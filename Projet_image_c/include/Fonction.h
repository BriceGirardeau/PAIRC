
#include <stdlib.h>
#include <stdio.h>


typedef struct image {
	int   Nblig;
	int   Nbcol;
	unsigned char*  data;
	unsigned char** pixel;
} IMAGE;

typedef struct mat {
	int   Nblig;
	int   Nbcol;
	int*  data;
	int** pixel;
} MATRICE;

typedef struct {
	int size;
	int *data;
} TABLEAU_INT;

MATRICE allocationMatrice(int Nblig, int Nbcol);

TABLEAU_INT histogrammeImage(IMAGE img, int choix);

IMAGE allocationImage(int Nblig, int Nbcol);

void liberationImage(IMAGE *img);

IMAGE lectureImage(const char *nom);

void sauvegardeImage(IMAGE img, const char *type, const char *out);

TABLEAU_INT allocationTableau(int n);

void Initialisation(void);

IMAGE choixfichier();

IMAGE Binarisation(IMAGE img, int seuil);

IMAGE Inversion(IMAGE img);

IMAGE SoustractionImage(IMAGE img1, IMAGE img2);

IMAGE Erosion(IMAGE img, IMAGE ES);

IMAGE Dilatation(IMAGE img, IMAGE ES);

IMAGE ElementStructurant(const char *type);

IMAGE Fermeture(IMAGE img, IMAGE ES);

IMAGE Ouverture(IMAGE img, IMAGE ES);

IMAGE squelette(IMAGE img, IMAGE ES, const char *rep);

int CalculAire(IMAGE img, char CObjet);

void Test2Fonction(char *NomFonction, int PremierFichier, int DernierFichier);

IMAGE FiltrageMoyen(IMAGE img, int Nbligne, int Nbcolonne);

int CaractereEquiv(int fichier);

IMAGE FiltrePasseHaut(IMAGE img);

IMAGE fct_EtiquettageImage(IMAGE ImgInput);

IMAGE fct_replicateImage(IMAGE ImgInput, int nb_duplicate);