#include <stdlib.h>
#include <stdio.h>
#include "Fonction.h"

void main() {
	//Initialisation();
	//IMAGE img, bin, inv, img2, dil, clos, open, skel;
	//TABLEAU_INT h = { 0,NULL };

	//IMAGE ES = ElementStructurant("V8");

	///*
	////test mode
	//int pf=0, df=0;
	//printf("premier fichier:\t");
	//scanf("%d", &pf);

	//printf("dernierier fichier:\t");
	//scanf("%d", &df);

	//Test2Fonction("aire", pf, df);
	//printf("fin\n");
	//*/


	//
	////Export
	//img = choixfichier();
	//sauvegardeImage(img, "P5", "..\\1.pgm");
	//

	//
	////Binarisation
	//bin = Binarisation(img, 128);
	//sauvegardeImage(bin, "P5", "..\\2.pgm");

	////Inversion
	//inv = Inversion(bin);
	//sauvegardeImage(inv, "P5", "..\\3.pgm");

	///*
	////soustraction img-img2
	//img2 = choixfichier();
	//img2 = SoustractionImage(bin, Binarisation(img2, 128));
	//sauvegardeImage(img2, "P5", "..\\..\\Projet_Analyse_Image_Reconnaissance_Caractere\\out\\sous.pgm");

	////histograme
	//h = histogrammeImage(img, 0);
	//for (int i = 0; i < h.size; i++) printf("%d\t", h.data[i]);
	//*/
	///*
	////Dilatation
	//dil = Dilatation(inv, ES);
	//sauvegardeImage(dil, "P5", "..\\..\\Projet_Analyse_Image_Reconnaissance_Caractere\\out\\Dilatation.pgm");
	//
	////Erosion
	//dil = Erosion(inv, ES);
	//sauvegardeImage(dil, "P5", "..\\..\\Projet_Analyse_Image_Reconnaissance_Caractere\\out\\Erosion.pgm");

	////ouverture
	//open = Ouverture(inv, ES);
	//sauvegardeImage(open, "P5", "..\\..\\Projet_Analyse_Image_Reconnaissance_Caractere\\out\\Ouverture.pgm");

	////fermeture
	//clos = Fermeture(inv, ES);
	//sauvegardeImage(clos, "P5", "..\\..\\Projet_Analyse_Image_Reconnaissance_Caractere\\out\\Fermeture.pgm");
	//*/

	////Squelettisation
	//skel = squelette(inv, ES, "inf");
	//sauvegardeImage(skel, "P5", "..\\5.pgm");

	////Detection de contour (passe haut)
	//img2 = FiltrePasseHaut(inv);
	//sauvegardeImage(img2, "P5", "..\\6.pgm");
	//	

	//img2 = fct_EtiquettageImage(img2);
	//sauvegardeImage(img2, "P5", "..\\7.pgm");

	printf("Hello word");
	system("pause");
	
}