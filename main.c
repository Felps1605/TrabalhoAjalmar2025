#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "uf.h"

void uf_inserir(int codigo, char descricao[], char sigla[])
{
struct UF uf;
int codigo;
printf("Insira o código da UF: ");
scanf("%d", &codigo);
uf.codigo=codigo;
printf("Insira o nome da UF ");
strcpy(uf.descricao, descricao);
printf("Insira a sigla da UF: ");
strcpy(uf.sigla, sigla);


}
