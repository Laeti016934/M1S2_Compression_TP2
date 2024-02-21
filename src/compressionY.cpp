// main.cpp
#include <iostream>
#include "image_ppm.h"

using namespace std;

void diviserImage(OCTET* image_ppm, OCTET* image_Y, OCTET* image_Cr, OCTET* image_Cb, int nb_lignes, int nb_colonnes);

int main(int argc, char* argv[]) {
    char nom_image_ppm[250], nom_image_Y[250], nom_image_Cr[250], nom_image_Cb[250];
    if (argc != 5) {
        cout << "Usage: ImageIn.ppm ImageY.pgm ImageCR.pgm ImageCB.pgm\n";
        exit(1);
    }
    sscanf(argv[1], "%s", nom_image_ppm);
    sscanf(argv[2], "%s", nom_image_Y);
    sscanf(argv[3], "%s", nom_image_Cr);
    sscanf(argv[4], "%s", nom_image_Cb);

    int nb_lignes, nb_colonnes;
    lire_nb_lignes_colonnes_image_ppm(nom_image_ppm, &nb_lignes, &nb_colonnes);

    int taille_image = nb_lignes * nb_colonnes;
    OCTET* image_ppm = new OCTET[3 * taille_image];
    OCTET* image_Y = new OCTET[taille_image];
    OCTET* image_Cr = new OCTET[taille_image];
    OCTET* image_Cb = new OCTET[taille_image];

    lire_image_ppm(nom_image_ppm, image_ppm, taille_image);

    diviserImage(image_ppm, image_Y, image_Cr, image_Cb, nb_lignes, nb_colonnes);

    ecrire_image_pgm(nom_image_Y, image_Y, nb_lignes, nb_colonnes);
    ecrire_image_pgm(nom_image_Cr, image_Cr, nb_lignes / 2, nb_colonnes / 2);
    ecrire_image_pgm(nom_image_Cb, image_Cb, nb_lignes / 2, nb_colonnes / 2);

    delete[] image_ppm;
    delete[] image_Y;
    delete[] image_Cr;
    delete[] image_Cb;

    return 0;
}

void diviserImage(OCTET* image_ppm, OCTET* image_Y, OCTET* image_Cr, OCTET* image_Cb, int nb_lignes, int nb_colonnes) {
    for (int i = 0; i < nb_lignes; i++) {
        for (int j = 0; j < nb_colonnes; j++) {
            int index_ppm = 3 * (i * nb_colonnes + j);
            int index_Y = i * nb_colonnes + j;
            int index_CrCb = (i / 2) * (nb_colonnes / 2) + (j / 2);

            double R = image_ppm[index_ppm];
            double G = image_ppm[index_ppm + 1];
            double B = image_ppm[index_ppm + 2];

            image_Y[index_Y] = static_cast<OCTET>(0.299 * R + 0.587 * G + 0.114 * B);

            if (i % 2 == 0 && j % 2 == 0) {
                double Cb = (B - image_Y[index_Y]) / (2 - 2 * 0.114 * B) + 128;
                double Cr = (R - image_Y[index_Y]) / (2 - 2 * 0.299 * R) + 128;

                image_Cr[index_CrCb] = static_cast<OCTET>(Cr);
                image_Cb[index_CrCb] = static_cast<OCTET>(Cb);
            }
        }
    }
}