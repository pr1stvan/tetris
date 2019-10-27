#ifndef INFOC_FUGGVENYEK_H_INCLUDED
#define INFOC_FUGGVENYEK_H_INCLUDED

void latin2_to_unicode(unsigned char *, unsigned short *);
void utf8_to_unicode(unsigned char *, unsigned short *);
void unicode_to_utf8(unsigned short*, char*);

int input_text(Uint16 *, int, int, int , int,
               SDL_Color, SDL_Color, TTF_Font *, SDL_Surface *,int);
int nevbekeres(char *);

#endif // INFOC_FUGGVENYEK_H_INCLUDED
