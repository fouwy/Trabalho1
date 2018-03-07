/*****************************************************************/
/*         Trabalho pratico 1 | PROG2 | MIEEC | 2017/18          */
/*****************************************************************/
/*                    FUNCOES A IMPLEMENTAR                      */
/*****************************************************************/

#include "cidades.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

vetor* cidades_load(const char *nomef)
{
    int i = 0;
    vetor *v;
    cidade c;
    FILE *f;

    v = vetor_novo();

    if(v == NULL){
        printf("Erro");
        return NULL;
    }

    f = fopen(nomef, "rb");

    if(f == NULL){
        printf("Erro");
        return NULL;
    }


    while(fread(&c, sizeof(cidade), 1, f) == 1){
      if(vetor_insere(v, c, i) == -1){
          printf("Erro");
          break;
      }
      i++;

    }
 
    fclose(f);

    return v;
}

int cidades_save(const vetor *vec, const char *nomef)
{

 FILE *f;
 int i;
 f = fopen(nomef, "wb");

 if (f == NULL)
 {
      printf("Impossivel criar o ficheiro\n");
      return -1;
 }

     for ( i = 0; i < vec->tamanho; i++){

          fwrite(&(vec->elementos[i]), sizeof(cidade), 1, f);

     }

 fclose(f);

 return i;

}

int cidades_peek(const char *nomef, const char *nomecidade, cidade *resultado)
{
  int i = 0;
  FILE *f;

  f = fopen(nomef, "rb");

  if(f == NULL){
    printf("Erro");
    return -1;
  }

  while(fread(resultado, sizeof(cidade), 1, f) == 1){
    if(strcmp(resultado->nome, nomecidade) == 0){
      fclose(f);
      return i;
    }
    else i++;
  }

	return -1;
}

int cidades_poke(const char *nomef, const char *nomecidade, cidade nova)
{
  FILE* f1;

    cidade cidade1;
    int pos_change; /* posicao da cidade a alterar*/

    pos_change = cidades_peek(nomef, nomecidade, &cidade1);

    if(pos_change == -1){
      printf("Erro");
      return -1;
    }

    f1 = fopen(nomef, "wb");

    /*posiciona o apontador na posicao da cidade a alterar*/
    fseek(f1, pos_change, SEEK_SET);

    /*escreve a nova cidade na posicao da anterior*/
    fwrite(&nova, sizeof(cidade), 1, f1);

    fclose(f1);

    return pos_change;
}

int cidades_resort(vetor *v, char criterio)
{
  int i, j;
  cidade tmp;

  if(criterio == 'p'){
    for (i = 1; i < v->tamanho; i++)
    {
      tmp = v->elementos[i];
        for (j = i; j>0 && strcmp(tmp.pais, v->elementos[j-1].pais) < 0; j--){
          if(strcmp(tmp.pais, v->elementos[j-1].pais) < 0)
          v->elementos[j] = v->elementos[j-1];
        }
      v->elementos[j] = tmp;
    }
    printf("%s %s %s %s %s", v->elementos[0].pais, v->elementos[1].pais, v->elementos[2].pais, v->elementos[3].pais, v->elementos[4].pais);
    return 0;
  }



  if(criterio == 'a'){
    for (i = 1; i < v->tamanho; i++)
    {
      tmp = v->elementos[i];
        for (j = i; j>0 && tmp.area <= v->elementos[j-1].area; j--){
          if(tmp.area == v->elementos[j-1].area && tmp.populacao < v->elementos[j-1].populacao)
            v->elementos[j] = v->elementos[j-1];
          if(tmp.area < v->elementos[j-1].area)
            v->elementos[j] = v->elementos[j-1];

        }
      v->elementos[j] = tmp;
    }
    printf("%s %d %d %d %d", v->elementos[v->tamanho-1].nome, v->elementos[v->tamanho-2].area, v->elementos[2].area, v->elementos[3].area, v->elementos[4].area);
    return 0;
 }
  return -1;
}

char** cidades_similar (vetor *vec, const char *nomecidade, int deltapop, int *nsimilares)
{
  int i, j=0;
  int pop = 0; /*guarda a populacao da cidade especifica*/
  int pos; /*guarda posicao no vetor da cidade esp.*/

  /*array de strings para as cidades similares*/
  int num = 50; /*numero de strings e caracteres de cada string*/

  /*alocar memoria para o vetor de strings*/
  char **same_pop = (char**)malloc(sizeof(char*) * num);

  for(i=0; i<num; i++)
  {
    same_pop[i] = (char*)malloc(sizeof(char) * num);
  }


  /*percorre o vetor e encontra a cidade que tem o nome igual ao parametro "nomecidade"*/
  for(i=0; i<vec->tamanho; i++)
  {
    if(strcmp(vec->elementos[i].nome, nomecidade) == 0)
    {
      pop = vec->elementos[i].populacao;
      pos = i;

      break;
    }
  }

  /*controlo*/
  if(pop == 0)
  {
    return NULL;
  }


  /*percorre o vetor e calcula se a populacao esta dentro do "deltapop" escolhido;
  **se estiver, guarda o nome da cidade no vetor de strings same_pop e adiciona 1 ao contador(j)*/
  for(i=0; i<vec->tamanho; i++)
  {
    if(vec->elementos[i].populacao <= pop + deltapop && vec->elementos[i].populacao >= pop - deltapop
        && i != pos)
    {
      strcpy(same_pop[j], vec->elementos[i].nome);
      
      j++;
    }
  }

  /*controlo*/
  if(j == 0)
  {
    return NULL;
  }


  *nsimilares = j;

  return same_pop;
}    /*testetetestes*/
