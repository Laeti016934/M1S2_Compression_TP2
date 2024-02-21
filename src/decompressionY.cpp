#include <stdio.h>
#include "image_ppm.h"
#include <iostream>

int main(int argc, char* argv[]) {
    char cNomImgOut[250], cNomImgY[250], cNomImgCr[250], cNomImgCb[250];
    int nH, nW, nTaille;

    if (argc != 5) {
        printf("Usage: ImageY.pgm ImageCr.pgm ImageCb.pgm ImageOut.ppm \n");
        exit(1);
    }

    sscanf(argv[1], "%s", cNomImgY);
    sscanf(argv[2], "%s", cNomImgCr);
    sscanf(argv[3], "%s", cNomImgCb);
    sscanf(argv[4], "%s", cNomImgOut);

    OCTET *ImgOut;
    OCTET *Y, *Cr, *Cb;

    lire_nb_lignes_colonnes_image_pgm(cNomImgY, &nH, &nW); // Assuming the compressed images are in PGM format
    nTaille = nH * nW;

    int nTaille3 = nTaille * 3;

    // Allocate memory for ImgOut, Red, Green, and Blue
    allocation_tableau(ImgOut, OCTET, nTaille3);
    allocation_tableau(Y, OCTET, nTaille);
    allocation_tableau(Cr, OCTET, nTaille / 4);
    allocation_tableau(Cb, OCTET, nTaille / 4);

    lire_image_pgm(cNomImgY, Y, nH * nW);
    lire_image_pgm(cNomImgCr, Cr, nTaille / 4);
    lire_image_pgm(cNomImgCb, Cb, nTaille / 4);

    for (int i = 0; i < nH; i++) {
        for (int j = 0; j < nW; j++) {
            ImgOut[3 * (i * nW + j)] = Y[i * nW + j] + 1.402 * (Cr[i /2 * (nW / 2) + j/2] - 128);
            ImgOut[3 * (i * nW + j)+1] = Y[i * nW + j] - 0.344136 * (Cb[i /2 * (nW / 2) + j/2] - 128) - 0.714136 * (Cr[i /2 * (nW / 2) + j/2] - 128);
            ImgOut[3 * (i * nW + j)+2] =Y[i * nW + j] + 1.772 * (Cb[i /2 * (nW / 2) + j/2] - 128);
            ImgOut[3 * (i * nW + j)] = std::min(std::max(0, int(ImgOut[3 * (i * nW + j)])), 255);
            ImgOut[3 * (i * nW + j)+1] = std::min(std::max(0, int(ImgOut[3 * (i * nW + j)+1])), 255);
            ImgOut[3 * (i * nW + j)+2] = std::min(std::max(0, int(ImgOut[3 * (i * nW + j)+2])), 255);
        }
    }

    ecrire_image_ppm(cNomImgOut, ImgOut, nH, nW);

    // Free allocated memory
    free(ImgOut);
    free(Y);
    free(Cr);
    free(Cb);
    return 1;
}