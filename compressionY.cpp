// CompressionYCrCb.cpp

#include <iostream>
#include <cstdlib>
#include "image_ppm.h"

using namespace std;

void diviserImage(OCTET* image_ppm, OCTET* image_Y, OCTET* image_Cr, OCTET* image_Cb, int nb_lignes, int nb_colonnes);

int main(int argc, char* argv[]) {
    char nom_image_Y[250], nom_image_Cr[250], nom_image_Cb[250];
    int nH, nW, nTaille;

    if (argc != 4) {
        cout << "Usage: ImageY.pgm ImageCR.pgm ImageCB.pgm\n";
        exit(1);
    }

    sscanf(argv[1], "%s", nom_image_Y);
    sscanf(argv[3], "%s", nom_image_Cr);
    sscanf(argv[4], "%s", nom_image_Cb);

    OCTET *ImgIn, *Y, *Cr, *Cb;
    
    lire_nb_lignes_colonnes_image_ppm(nom_image_Y, &nH, &nW);
    nTaille = nH * nW;

    allocation_tableau(Y, OCTET, nTaille);
    allocation_tableau(Cr, OCTET, ?);
    allocation_tableau(Cb, OCTET, ?);

    // TODO : Compression de l'image

    ecrire_image_pgm("nouveauY", Y, nH, nW);
    ecrire_image_pgm("nouveauCr", Cr, nH / 2, nW / 2);
    ecrire_image_pgm("nouveauCb", Cb, nH / 2, nW / 2);

    free(Y);
    free(Cr);
    free(Cb);

    return 0;
}