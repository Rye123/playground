#include <stdio.h>
#include <stdlib.h>

char* get_id()
{
  /* Obtain the CPU manufacturer ID */
  char* manID = malloc(13 * sizeof(char));
  int ebx;
  int edx;
  int ecx;
  __asm__("\t xor %eax,%eax\n"
	  "\t cpuid\n");
  __asm__("\t movl %%ebx,%0" : "=r"(ebx));
  __asm__("\t movl %%edx,%0" : "=r"(edx));
  __asm__("\t movl %%ecx,%0" : "=r"(ecx));

  *(manID)   = *(char *) &ebx;
  *(manID+1) = *(((char *) &ebx) + 1);
  *(manID+2) = *(((char *) &ebx) + 2);
  *(manID+3) = *(((char *) &ebx) + 3);
  *(manID+4) = *(char *) &edx;
  *(manID+5) = *(((char *) &edx) + 1);
  *(manID+6) = *(((char *) &edx) + 2);
  *(manID+7) = *(((char *) &edx) + 3);
  *(manID+8) = *(char *) &ecx;
  *(manID+9) = *(((char *) &ecx) + 1);
  *(manID+10) = *(((char *) &ecx) + 2);
  *(manID+11) = *(((char *) &ecx) + 3);
  return manID;
}

int main()
{
  printf("%s\n", get_id());
  return 0;
}
