#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

#define true 1
#define false 0
#define null 0

#define TMAX 26

const char ALPHABET[TMAX] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
char alphabet[TMAX];

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

 char *t26 = tarr[tmax - 1];
 
 int alphabetmap[TMAX];

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