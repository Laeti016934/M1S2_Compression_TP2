#include <stdio.h>
#include "image_ppm.h"
#include <iostream>
#include <algorithm>

int main(int argc, char* argv[]) {
    //Gestion des arguments
    char cNomImgLue[250], cNomImgR[250],cNomImgG[250],cNomImgB[250];
    if (argc != 5) {
        printf("Usage: ImageIn.ppm ImageR.pgm ImageG4.pgm ImageB4.pgm\n");
        exit(1);
    }
    sscanf(argv[1], "%s", cNomImgLue);
    sscanf(argv[2], "%s", cNomImgR);
    sscanf(argv[3], "%s", cNomImgG);
    sscanf(argv[4], "%s", cNomImgB);

    //Initialisation des variables images
    OCTET *ImgIn;
    OCTET *Red, *Green, *Blue;

    //Caracteristique de l'image
    int nH, nW, nTaille;
    lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;
    int nTaille3 = nTaille * 3;

    //Allocation des tableaux
    allocation_tableau(ImgIn, OCTET, nTaille3);
    allocation_tableau(Red, OCTET, nTaille);
    allocation_tableau(Green, OCTET, nTaille / 4);
    allocation_tableau(Blue, OCTET, nTaille / 4);

    //Lecture de l'image
    lire_image_ppm(cNomImgLue, ImgIn, nH * nW);

    //Matrice de la couleur Rouge
    for (int i = 0; i < nH; i++) {
        for (int j = 0; j < nW; j++) {
            Red[(i * nW + j)] = ImgIn[3 * (i * nW + j)];
        }
    }

    //Moyenne du vert
    for (int i = 0; i < nH/2; i ++) {
        int i1 = std::min(2 * i, nH - 1); //gere le cas de dépassement de ligne
        for (int j = 0; j < nW/2; j ++) {
            int j1 = std::min(2 * j, nW - 1); //gere le cas de dépassement de colone
            Green[(i * nW/2 + j)] =
                (ImgIn[3 * (i1 * nW + j1) + 1] +
                ImgIn[3 * ((i1 + 1) * nW + j1) + 1] +
                ImgIn[3 * (i1 * nW + (j1 + 1)) + 1] +
                ImgIn[3 * ((i1 + 1) * nW + (j1 + 1)) + 1])/ 4;
        }
    }
    
    //Moyenne du bleue
    for (int i = 0; i < nH/2; i ++) {
        int i1 = std::min(2 * i, nH - 1); //gere le cas de dépassement de ligne
        for (int j = 0; j < nW/2; j ++) {
            int j1 = std::min(2 * j, nW - 1); //gere le cas de dépassement de colone
            Blue[(i * nW/2 + j)] = 
                (ImgIn[3 * (i1 * nW + j1) + 2] +
                ImgIn[3 * ((i1 + 1) * nW + j1) + 2] +
                ImgIn[3 * (i1 * nW + (j1 + 1)) + 2] +
                ImgIn[3 * ((i1 + 1) * nW + (j1 + 1)) + 2]) / 4;
        }
    }

    //Ecriture des images
    ecrire_image_pgm(cNomImgR, Red, nH, nW);
    ecrire_image_pgm(cNomImgG, Green, nH/2, nW/2);
    ecrire_image_pgm(cNomImgB, Blue, nH/2, nW/2);

    //Liberation des tableaux
    free(ImgIn);
    free(Red);
    free(Green);
    free(Blue);

    return 0;
}
