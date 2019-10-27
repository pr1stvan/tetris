#include "header.h"

/*A f�ggv�nyek �t lettek alak�tva*/

/*Forr�s: https://infoc.eet.bme.hu/karakterkodolas.php*/
void latin2_to_unicode(unsigned char *be, unsigned short *ki)
{
    unsigned short tabla[128] = {
        /* A 0x80-0xFF karakterek Unicode megfeleloje */
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89,
        0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93,
        0x94, 0x95, 0x96, 0x97, 0x98, 0x99, 0x9A, 0x9B, 0x9C, 0x9D,
        0x9E, 0x9F, 0xA0, 0x104, 0x2D8, 0x141, 0xA4, 0x13D, 0x15A,
        0xA7, 0xA8, 0x160, 0x15E, 0x164, 0x179, 0xAD, 0x17D, 0x17B,
        0xB0, 0x105, 0x2DB, 0x142, 0xB4, 0x13E, 0x15B, 0x2C7, 0xB8,
        0x161, 0x15F, 0x165, 0x17A, 0x2DD, 0x17E, 0x17C, 0x154,
        0xC1, 0xC2, 0x102, 0xC4, 0x139, 0x106, 0xC7, 0x10C, 0xC9,
        0x118, 0xCB, 0x11A, 0xCD, 0xCE, 0x10E, 0x110, 0x143, 0x147,
        0xD3, 0xD4, 0x150, 0xD6, 0xD7, 0x158, 0x16E, 0xDA, 0x170,
        0xDC, 0xDD, 0x162, 0xDF, 0x155, 0xE1, 0xE2, 0x103, 0xE4,
        0x13A, 0x107, 0xE7, 0x10D, 0xE9, 0x119, 0xEB, 0x11B, 0xED,
        0xEE, 0x10F, 0x111, 0x144, 0x148, 0xF3, 0xF4, 0x151, 0xF6,
        0xF7, 0x159, 0x16F, 0xFA, 0x171, 0xFC, 0xFD, 0x163, 0x2D9
    };
    int i, j;

    j=0;
    /* vegig a sztringen */
    for (i=0; be[i]!=0; ++i) {
        if (be[i]<128)  /* ascii? */
            ki[j++]=be[i];
        else
            ki[j++]=tabla[be[i]-128];
    }
    /* itt is nulla a lezaro nulla */
    ki[j]=0x0000;
}

/*Forr�s: https://infoc.eet.bme.hu/karakterkodolas.php*/
void utf8_to_unicode(unsigned char *be, unsigned short *ki)
{
    int pb, pk;

    pk=0;
    for (pb=0; be[pb]!=0; ++pb) {
        if (be[pb]<0x80) {
            /* 00000000 0xxxxxxx    0x0000-0x007F    0xxxxxxx */
            ki[pk++] = be[pb];
        }
        else
        if (be[pb]>>5 == 6) {   /* 0x6 = 110 bin */
            /* 00000yyy yyxxxxxx    0x0080-0x07FF    110yyyyy 10xxxxxx */
            ki[pk++] = (be[pb]&0x1f)<<6 | (be[pb+1]&0x3f);
            pb+=1;              /* ket bajtot hasznaltunk */
        }
        else {
            /* zzzzyyyy yyxxxxxx    0x0800-0xFFFF   1110zzzz 10yyyyyy 10xxxxxx */
            ki[pk++] = (be[pb]&0x0f)<<12 | (be[pb+1]&0x3f)<<6 | (be[pb+2]&0x3f);
            pb+=2;              /* harom bajtot hasznaltunk */
        }
    }
    ki[pk]=0x0000;
}
/*Forr�s: https://infoc.eet.bme.hu/karakterkodolas.php*/
void unicode_to_utf8(unsigned short *be, char *ki)
{
    int pb, pk;

    pk=0;
    for (pb=0; be[pb]!=0x0000; ++pb) {
        /* 00000000 0xxxxxxx    0x0000-0x007F   0xxxxxxx */
        if (be[pb]<=0x007F)
            ki[pk++] = be[pb];
        else
        /* 00000yyy yyxxxxxx    0x0080-0x07FF   110yyyyy 10xxxxxx */
        if (be[pb]<=0x07FF) {
            ki[pk++] = 0xC0 | be[pb]>>6;     /* 0xC0 = 11000000 */
            ki[pk++] = 0x80 | (be[pb]&0x3F); /* 0x80 = 10000000, 0x3F = 00111111 */
        }
        /* zzzzyyyy yyxxxxxx    0x0800-0xFFFF   1110zzzz 10yyyyyy 10xxxxxx */
        else {
            ki[pk++] = 0xE0 | be[pb]>>12;    /* 0xE0 = 11100000 */
            ki[pk++] = 0x80 | ((be[pb]>>6)&0x3F);
            ki[pk++] = 0x80 | (be[pb]&0x3F);
        }
    }

    ki[pk]=0;
}
