#ifndef PPM_H
#define PPM_H

// Définition de la structure pour représenter un pixel PPM
struct ppm_pixel {
  unsigned char r; 
  unsigned char g; 
  unsigned char b; 
};

// Fonction pour définir les valeurs d'un pixel
static inline void ppm_setpixel(struct ppm_pixel *px, unsigned char r,
                                unsigned char g, unsigned char b) {
  px->r = r;
  px->g = g;
  px->b = b;
}

// Définition de la structure pour représenter une image PPM
struct ppm_image {
  unsigned int width;
  unsigned int height;
  struct ppm_pixel *px;
};

// Fonction pour initialiser une image PPM
int ppm_image_init(struct ppm_image *im, int w, int h);

// Fonction pour libérer la mémoire utilisée par une image PPM
int ppm_image_release(struct ppm_image *im);

// Fonction pour définir les valeurs d'un pixel dans une image PPM
static inline void ppm_image_setpixel(struct ppm_image *im, int x, int y,
                                      unsigned char r, unsigned char g,
                                      unsigned char b) {
                                        
  struct ppm_pixel *px = im->px + im->width * y + x;
  // Appel de la fonction ppm_setpixel pour définir les valeurs du pixel
  ppm_setpixel(px, r, g, b);
}

// Fonction pour sauvegarder une image PPM dans un fichier
int ppm_image_dump(struct ppm_image *im, char *path);

#endif /* PPM_H */
