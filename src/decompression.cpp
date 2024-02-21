// decompression.cpp

#include <stdio.h>
#include "image_ppm.h"
#include <iostream>

int main(int argc, char* argv[]) {
    char cNomImgOut[250], cNomImgR[250], cNomImgG[250], cNomImgB[250];
    int nH, nW, nTaille;

    if (argc != 5) {
        printf("Usage: ImageR.pgm ImageG.pgm ImageB.pgm ImageOut.ppm \n");
        exit(1);
    }

    sscanf(argv[1], "%s", cNomImgR);
    sscanf(argv[2], "%s", cNomImgG);
    sscanf(argv[3], "%s", cNomImgB);
    sscanf(argv[4], "%s", cNomImgOut);

    OCTET *ImgOut;
    OCTET *Red, *Green, *Blue;

    lire_nb_lignes_colonnes_image_pgm(cNomImgR, &nH, &nW); // Assuming the compressed images are in PGM format
    nTaille = nH * nW;

    int nTaille3 = nTaille * 3;

    // Allocate memory for ImgOut, Red, Green, and Blue
    allocation_tableau(ImgOut, OCTET, nTaille3);
    allocation_tableau(Red, OCTET, nTaille);
    allocation_tableau(Green, OCTET, nTaille / 4);
    allocation_tableau(Blue, OCTET, nTaille / 4);

    lire_image_pgm(cNomImgR, Red, nH * nW);
    lire_image_pgm(cNomImgG, Green, nTaille / 4);
    lire_image_pgm(cNomImgB, Blue, nTaille / 4);
    for (int i = 0; i < nH; i++) {
        for (int j = 0; j < nW; j++) {
            ImgOut[3 * (i * nW + j)] = Red[i * nW + j];
        }
    }
    for (int i = 0; i < nH; i++) {
        for (int j = 0; j < nW; j++) {
            ImgOut[3 * (i * nW + j) + 1] = Green[i /2 * (nW / 2) + j/2];
        }
    }
    for (int i = 0; i < nH; i++) {
        for (int j = 0; j < nW; j++) {
            ImgOut[3 * (i * nW + j) + 2] = Blue[i /2 * (nW / 2) + j/2];
        }
    }

    ecrire_image_ppm(cNomImgOut, ImgOut, nH, nW);

    // Free allocated memory
    free(ImgOut);
    free(Red);
    free(Green);
    free(Blue);
    return 1;
}