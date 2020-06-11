//Projet: PAIRC (Projet Analyse Image Reconnaissance Caractere)
//Auteurs: Blandine DEDDE, Brice GIRARDEAU DARNAND, Victor MARQUET

#include <stdlib.h>
#include <stdio.h>
#include "Fonction.h"

void main() {
	Initialisation();
	IMAGE img, bin, inv, img2, Morph, PH;

	IMAGE ES = ElementStructurant("V8");


	//Merci de creer les repertoires necessaires pour que les images soient enregistrées dans:
		// -> "..\\..\\Projet_Analyse_Image_Reconnaissance_Caractere\\out\\*.*"


	//test mode
	printf("\n*** *** TEST MODE *** ***\n\n");
	int pf=0, df=0;
	printf("premier fichier: (reco 388)\t");
	scanf("%d", &pf);

	printf("dernierier fichier: (reco 516)\t");
	scanf("%d", &df);

	//Test2Fonction("Aire", pf, df);
	Test2Fonction("Aire Top-Hat", pf, df);
	//Test2Fonction("Centre de gravite", pf, df);
	//Test2Fonction("Boucle", pf, df);

	printf("\n\n*** *** FIN TEST MODE *** ***\n");


	//Exemple des fonctions réaliser
		//Certaines fonctions ne sont pas illustrées ici
	
	//Import
	printf("\nImage pour le test des fonctions\n");
	img = choixfichier();
	sauvegardeImage(img, "P5", "..\\..\\Projet_Analyse_Image_Reconnaissance_Caractere\\out\\Original.pgm");

	//Binarisation
	bin = Binarisation(img, 128);
	sauvegardeImage(bin, "P5", "..\\..\\Projet_Analyse_Image_Reconnaissance_Caractere\\out\\Binarise.pgm");

	//Inversion
	inv = Inversion(bin);
	sauvegardeImage(inv, "P5", "..\\..\\Projet_Analyse_Image_Reconnaissance_Caractere\\out\\Negatif.pgm");

	//Soustraction img-img2
	printf("\nImage pour test de soustraction\n");
	img2 = choixfichier();
	img2 = SoustractionImage(bin, Binarisation(img2, 128));
	sauvegardeImage(img2, "P5", "..\\..\\Projet_Analyse_Image_Reconnaissance_Caractere\\out\\Soustraction.pgm");


	//Dilatation
	Morph = Dilatation(inv, ES);
	sauvegardeImage(Morph, "P5", "..\\..\\Projet_Analyse_Image_Reconnaissance_Caractere\\out\\Dilatation.pgm");
	
	//Erosion
	Morph = Erosion(inv, ES);
	sauvegardeImage(Morph, "P5", "..\\..\\Projet_Analyse_Image_Reconnaissance_Caractere\\out\\Erosion.pgm");

	//ouverture
	Morph = Ouverture(inv, ES);
	sauvegardeImage(Morph, "P5", "..\\..\\Projet_Analyse_Image_Reconnaissance_Caractere\\out\\Ouverture.pgm");

	//fermeture
	Morph = Fermeture(inv, ES);
	sauvegardeImage(Morph, "P5", "..\\..\\Projet_Analyse_Image_Reconnaissance_Caractere\\out\\Fermeture.pgm");

	//Top-Hat
	Morph = SoustractionImage(Fermeture(Binarisation(img, 128), ElementStructurant("V8")), Binarisation(img, 128));
	sauvegardeImage(Morph, "P5", "..\\..\\Projet_Analyse_Image_Reconnaissance_Caractere\\out\\Top-Hat.pgm");


	//Detection de contour (passe haut)
	PH = FiltrePasseHaut(inv);
	sauvegardeImage(PH, "P5", "..\\..\\Projet_Analyse_Image_Reconnaissance_Caractere\\out\\Laplacien.pgm");
		

	system("pause");
}