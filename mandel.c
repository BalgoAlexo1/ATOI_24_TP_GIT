#include <stdio.h>
#include <complex.h>
#include <math.h>
#include "ppm.h"


#define TRSH 2.0
#define ITER 1024ull


#define SIZEX 1500
#define SIZEY 1500

// Fonction pour calculer la partie réelle de la constante 'c' à partir de la position x
double cx(int x) {
    /* -2 ---> 1 */
    static const double qx = 3.0 / (double)SIZEX;
    return -2.0 + x * qx;
}

// Fonction pour calculer la partie imaginaire de la constante 'c' à partir de la position y
double cy(int y) {
    /* -1 ---> 1 */
    static const double qy = 2.0 / (double)SIZEY;
    return -1.0 + y * qy;
}

int main(int argc, char *argv[]) {
    struct ppm_image im;
    // Initialisation de l'image PPM avec les dimensions spécifiées
    ppm_image_init(&im, SIZEX, SIZEY);

    int i, j;
    // Calcul du facteur de couleur de référence en fonction du nombre d'itérations
    double colref = 255.0 / log(ITER);

    // Boucle pour parcourir chaque pixel de l'image
    for (i = 0; i < SIZEX; ++i) {
        for (j = 0; j < SIZEY; ++j) {

            unsigned long int iter = 0;

            // Initialisation de la constante 'c' et du nombre complexe 'z' pour chaque pixel
            double complex c = cx(i) + cy(j) * I;
            double complex z = 0;

            // Boucle pour effectuer l'itération de la fonction de Mandelbrot jusqu'à ce qu'elle converge ou atteigne le nombre maximum d'itérations
            while (iter < ITER) {
                double mod = cabs(z);

               
                if (TRSH < mod) {
                    break;
                }

                
                z = z * z + c;

                iter++;
            }

            // Calcul de la couleur en niveaux de gris en fonction du nombre d'itérations
            int grey = colref * log(iter);
            // Définition de la couleur du pixel dans l'image PPM
            ppm_image_setpixel(&im, i, j, grey, grey, grey);
        }
    }

    // Sauvegarde de l'image PPM dans un fichier
    ppm_image_dump(&im, "m.ppm");
    // Libération de la mémoire allouée pour l'image PPM
    ppm_image_release(&im);

    return 0;
}
