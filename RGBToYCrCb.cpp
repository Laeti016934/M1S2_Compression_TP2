#include <iostream>
#include <cstdlib>
#include "image_ppm.h"

using namespace std;

void diviserImage(OCTET* image_ppm, OCTET* image_Y, OCTET* image_Cr, OCTET* image_Cb, int nb_lignes, int nb_colonnes);

int main(int argc, char* argv[]) {
    char cNomImgLue[250], nom_image_Y[250], nom_image_Cr[250], nom_image_Cb[250];
    int nH, nW, nTaille;

    if (argc != 5) {
        cout << "Usage: ImageIn.ppm ImageY.pgm ImageCR.pgm ImageCB.pgm\n";
        exit(1);
    }

    sscanf(argv[1], "%s", cNomImgLue);
    sscanf(argv[2], "%s", nom_image_Y);
    sscanf(argv[3], "%s", nom_image_Cr);
    sscanf(argv[4], "%s", nom_image_Cb);

    OCTET *ImgIn, *Y, *Cr, *Cb;
    
    lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;

    allocation_tableau(ImgIn, OCTET, nTaille * 3);
    lire_image_ppm(cNomImgLue, ImgIn, nH * nW);

    allocation_tableau(Y, OCTET, nTaille);
    allocation_tableau(Cr, OCTET, nTaille); // Taille réduite de moitié pour Cr et Cb
    allocation_tableau(Cb, OCTET, nTaille);

    // Conversion de l'espace RGB à l'espace YCrCb
    for (int i = 0; i < nTaille; ++i) {
        int R = ImgIn[i * 3];
        int G = ImgIn[i * 3 + 1];
        int B = ImgIn[i * 3 + 2];

        Y[i]  = 0.299 * R + 0.587 * G + 0.114 * B;
        Cr[i] += 0.5 * (B - Y[i]);
        Cb[i] += 0.5 * (R - Y[i]);
    }

    ecrire_image_pgm(nom_image_Y, Y, nH, nW);
    ecrire_image_pgm(nom_image_Cr, Cr, nH, nW);
    ecrire_image_pgm(nom_image_Cb, Cb, nH, nW);

    free(ImgIn);
    free(Y);
    free(Cr);
    free(Cb);

    return 0;
}
