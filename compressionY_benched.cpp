#include <stdio.h>
#include "image_ppm.h"
#include <iostream>
#include <algorithm>

int main(int argc, char* argv[]) {
    //Lecture des arguments
    char cNomImgLue[250], cNomImgY[250],cNomImgCr[250],cNomImgCb[250];
    if (argc != 5) {
    printf("Usage: ImageIn.ppm ImageY.pgm ImageCR.pgm ImageCR.pgm\n");
    exit(1);
    }
    sscanf(argv[1], "%s", cNomImgLue);
    sscanf(argv[2], "%s", cNomImgY);
    sscanf(argv[3], "%s", cNomImgCr);
    sscanf(argv[4], "%s", cNomImgCb);

    //Variables
    int nH, nW, nTaille;
    OCTET *ImgIn;
    OCTET *Y, *Cr, *Cb;

    //Caracteristique fichier lu
    lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;
    int nTaille3 = nTaille * 3;

    //Allocation de tableau
    allocation_tableau(ImgIn, OCTET, nTaille3);
    allocation_tableau(Y, OCTET, nTaille);
    allocation_tableau(Cr, OCTET, nTaille / 4);
    allocation_tableau(Cb, OCTET, nTaille / 4);

    //Lecture de l'image
    lire_image_ppm(cNomImgLue, ImgIn, nH * nW);

    //Calcul luminance
    for (int i = 0; i < nH; i++) {
        for (int j = 0; j < nW; j++) {
            Y[i * nW + j] = 0.299 * ImgIn[3 * (i * nW + j)] + 0.587 * ImgIn[3 * (i * nW + j) + 1] + 0.114 * ImgIn[3 * (i * nW + j) + 2];
            Y[i * nW + j] = std::min(std::max(0, int(Y[i * nW + j])), 255);
        }
    }

    //Calcul chromatique rouge
    for (int i = 0; i < nH/2; i ++) {
        int i1 = std::min(2 * i, nH - 1); //gere le cas de dépassement de ligne
        for (int j = 0; j < nW/2; j ++) {
            int j1 = std::min(2 * j, nW - 1); //gere le cas de dépassement de colone
            int Crtemp[4];
            Crtemp[0] = (ImgIn[3 * (i1 * nW + j1)] - Y[(i1 * nW + j1)]) / (2 - 2 * 0.299 * ImgIn[3 * (i1 * nW + j1)]) + 128;
            Crtemp[1] = (ImgIn[3 * ((i1 + 1) * nW + j1)] - Y[((i1 + 1) * nW + j1)]) / (2 - 2 * 0.299 * ImgIn[3 * ((i1 + 1) * nW + j1)]) + 128;
            Crtemp[2] = (ImgIn[3 * (i1 * nW + (j1 + 1))] - Y[(i1 * nW + (j1 + 1))]) / (2 - 2 * 0.299 * ImgIn[3 * (i1 * nW + (j1 + 1))]) + 128;
            Crtemp[3] = (ImgIn[3 * ((i1 + 1) * nW + (j1 + 1)) ] - Y[((i1 + 1) * nW + (j1 + 1))]) / (2 - 2 * 0.299 * ImgIn[3 * ((i1 + 1) * nW + (j1 + 1)) ]) + 128;
            
            Cr[i * nW / 2 + j] = (Crtemp[0]+Crtemp[1]+Crtemp[2]+Crtemp[3])/4;
            Cr[i * nW / 2 + j] = std::min(std::max(0, int(Cr[i * nW / 2 + j])), 255);
        }
    }

    //Calcul chromatique bleu
    for (int i = 0; i < nH/2; i ++) {
        int i1 = std::min(2 * i, nH - 1); //gere le cas de dépassement de ligne
        for (int j = 0; j < nW/2; j ++) {
            int j1 = std::min(2 * j, nW - 1); //gere le cas de dépassement de colone
            int Cbtemp[4];
            Cbtemp[0] = (ImgIn[3 * (i1 * nW + j1)+2] - Y[(i1 * nW + j1)]) / (2 - 2 * 0.299 * ImgIn[3 * (i1 * nW + j1)+2]) + 128;
            Cbtemp[1] = (ImgIn[3 * ((i1 + 1) * nW + j1)+2] - Y[((i1 + 1) * nW + j1)]) / (2 - 2 * 0.299 * ImgIn[3 * ((i1 + 1) * nW + j1)+2]) + 128;
            Cbtemp[2] = (ImgIn[3 * (i1 * nW + (j1 + 1))+2] - Y[(i1 * nW + (j1 + 1))]) / (2 - 2 * 0.299 * ImgIn[3 * (i1 * nW + (j1 + 1))+2]) + 128;
            Cbtemp[3] = (ImgIn[3 * ((i1 + 1) * nW + (j1 + 1))+2] - Y[((i1 + 1) * nW + (j1 + 1))]) / (2 - 2 * 0.299 * ImgIn[3 * ((i1 + 1) * nW + (j1 + 1))+2]) + 128;

            Cb[i * nW / 2 + j] = (Cbtemp[0]+Cbtemp[1]+Cbtemp[2]+Cbtemp[3])/4;
            Cb[i * nW / 2 + j] = std::min(std::max(0, int(Cb[i * nW / 2 + j])), 255);
        }
    }
    
    //Ecriture des images
    ecrire_image_pgm(cNomImgY, Y, nH, nW);
    ecrire_image_pgm(cNomImgCr, Cr, nH/2, nW/2);
    ecrire_image_pgm(cNomImgCb, Cb, nH/2, nW/2);

    //Liberation du tableau
    free(ImgIn);
    free(Y);
    free(Cr);
    free(Cb);
    
    return 0;
}
