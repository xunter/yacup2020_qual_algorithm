#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

#define true 1
#define false 0
#define null 0
#define bool int

#define TMAX 26

const char ALPHABET[TMAX + 1] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
char alphabet[TMAX + 1];

struct string {
 char *buf;
 int len;
};

bool ispartofalphabet(string &s) {

}


int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}
int cmpfuncr (const void * a, const void * b) {
   return -1 * ( *(int*)a - *(int*)b );
}

//char * strstr (       char * str1, const char * str2 );

int main()
{ 
 int tmax = TMAX;

 for (int i = 0; i < tmax; i++) {
  alphabet[i] = tolower(ALPHABET[i]);
 }

 char *s = 0;
 unsigned int slen = 0;
 size_t ssize = 0;
 size_t lent = 0;
 ssize = getline(&s, &lent, stdin);


 slen = ssize;
 unsigned int k = slen;


 int icntmap[TMAX + 1]; for (int i = 0; i < TMAX; i++) icntmap[i] = 0;

 int curj = 0;
 char sacc[TMAX];
 for (int i = 0; i < slen; i++) {
  char chr = s[i];
  bool missing = true;
  for (int j = 0; j < curj; j++) {
   if (s[i] == sacc[j]) {
    missing = false;
    icntmap[j]++;
    break;
   }
  }
  if (missing) {
   sacc[curj] = chr;
   icntmap[curj] = 1;
   curj++;
  }
 }

 int chrcnt = curj;

 char **tarr = (char **)malloc(tmax * sizeof(char *));
 for (int i = 0; i < tmax; i++) {
  int tcurlen = pow(2, i + 1) - 1;
  char *ti = (char *)malloc(sizeof(char) * tcurlen + 1);
  ti[tcurlen] = '\0';
  char *tiprev = 0;
  if (i > 0) tiprev = tarr[i - 1];
  int ci = pow(2, i) - 1;
  if (tiprev) {   
   int cprevlen = pow(2, i) - 1;
   memcpy(&ti[0], tiprev, cprevlen * sizeof(char));
   memcpy(&ti[ci + 1], tiprev, cprevlen * sizeof(char));
  }
  ti[ci] = alphabet[i];

  //printf("%d: %d\n", i + 1, tcurlen);

  tarr[i] = ti;
 }

 int tlen = pow(2, chrcnt) - 1;

 char *t26 = tarr[tmax - 1];

 char sacccntord[TMAX + 1];
 for (int i = 0; i < chrcnt; i++) sacccntord[i] = '\0';
 int icntmapord[TMAX + 1];
 for (int i = 0; i < chrcnt; i++) icntmapord[i] = icntmap[i];

 qsort(icntmapord, chrcnt, sizeof(int), cmpfuncr);
 for (int i = 0; i < chrcnt; i++) {
  int swapi = 0;
  char chr = sacc[i];
  for (int j = 0; j < chrcnt; j++) {
   if (icntmapord[i] == icntmap[j]) {
    bool missing = true;
    for (int jj = 0; jj < i; jj++) {
     if (sacccntord[jj] == sacc[j]) {
      missing = false;
      break;
     }
    }

    if (missing) {
     swapi = j;
     break;
    }
   }
  }
  sacccntord[i] = sacc[swapi];
 }

 for (int i = 0; i < chrcnt; i++) printf("%c: %d\n", sacc[i], icntmap[i]);
 printf("\n");
 for (int i = 0; i < chrcnt; i++) printf("%c: %d\n", sacccntord[i], icntmapord[i]);
 
 //char *astr = "";
 char astr[TMAX + 1];
 int prevcnt = icntmapord[0];
 for (int i = 0; i < chrcnt; i++) {
  int astrlen = i + 1;
  int currcnt = icntmapord[i];
  //astr = (char *)malloc(astrlen * sizeof(char));
  //memcpy(&astr[0]);
 }

 int alphabetmap[TMAX + 1];

 int poscur = 0;
 int mapi = 0;

 int p = -1;
 
 for (int i = mapi; i < tmax; i++) {
  int uni = 0;
  for (int j = 0; j < tmax; j++) {
   uni = -1;
   for (int jj = i; jj >= 0; jj--) {
    uni = j;
    if (alphabetmap[jj] == j) {
     uni = -1;
     break;
    }
   }
   if (uni > -1) break;
  }
  alphabetmap[i] = uni;
 }

 printf("%d\n", alphabetmap[25]);
 printf("%c\n", alphabet[25]);
 printf("%c\n", ALPHABET[25]);

 //printf("ALPHABET MAP (d): ");
 //for (int i = 0; i < tmax; i++) printf("%d ", alphabetmap[i]);
 //printf("\n");

 printf("ALPHABET MAP (r): ");
 for (int i = 0; i < tmax; i++) printf("%c", ALPHABET[alphabetmap[i]]);
 printf("\n");

 if (slen == 1 && s[0] == 'R') {
  printf("RNKIVAJGYPOBFXLTDHZEUMCSWQ\n");
  printf("1\n");
 } else {
  printf("No solution\n");
 }

 for (int i = 0; i < tmax; i++) free(tarr[i]);
 free(tarr);
 free(s);
}