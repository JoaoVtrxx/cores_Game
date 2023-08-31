
#include "tela.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct{
    char nome[20];
    float pontos;
}Rg_jogador;

typedef struct 
{
  posicao pos;
  cor user;
  cor pc;
  Rg_jogador jogador_atual;
  Rg_jogador ranking[3];
  char resposta;
  double tempo;
  int camada;
  int tecla;
  bool enter;
}Rg_jogo;

void func_pos(Rg_jogo *jogo, int l, int c){
   jogo->pos.linha = l;
   jogo->pos.coluna = c;
}

void configura_tela_inicial(Rg_jogo *jogo){
  tela_cria();
  jogo->pos.linha = 1;
  jogo->pos.coluna = 10;
  tela_posiciona(jogo->pos);
  printf("-------Jogo das Cores------\n");
}

void cor_user_padrao(Rg_jogo *jogo)
{
  jogo->user.vermelho = 127;
  jogo->user.verde  = 127;
  jogo->user.azul  = 127;
}

void randomiza(Rg_jogo *jogo)
{
  jogo->pc.vermelho = (rand() % 256);
  jogo->pc.verde = (rand() % 256);
  jogo->pc.azul = (rand() % 256);
}

void inicializa_valores(Rg_jogo *jogo){
  cor_user_padrao(jogo);
  randomiza(jogo);
  jogo->jogador_atual.pontos = 0;
  strcpy(jogo->jogador_atual.nome,"");
  jogo->camada = 0;
  jogo->enter = false;
}

float distancia_maxima(int cor)
{
  if (cor > 127)
  {
    return cor;
  }
  else
  {
    return 255 - cor;
  }
}

float distancia_usuario(int cor, int user)
{
  if (cor > user)
  {
    return cor - user;
  }
  else
  {
    return user - cor;
  }
}

void compara(Rg_jogo *jogo){
  int i;
  int user[3] = {jogo->user.vermelho, jogo->user.verde, jogo->user.azul};
  int pc[3] = {jogo->pc.vermelho, jogo->pc.verde, jogo->pc.azul};
  float pontos = 0;
  float distancia_max;
  float distancia_user;
  jogo->tempo = 1 + (20 - jogo->tempo) / 20;
  for (i = 0; i < 3; i++)
  {
    distancia_max = distancia_maxima(pc[i]);
    distancia_user = distancia_usuario(pc[i], user[i]);
    pontos = 100 - (distancia_user / distancia_max) * 100 + pontos;
  }
  jogo->jogador_atual.pontos = (pontos / 3) + jogo->tempo;
}

void titulo_quadrados(Rg_jogo *jogo){
  func_pos(jogo, 9,9);
  tela_posiciona(jogo->pos);
  printf("| Cor Gerada |");
  func_pos(jogo, 9,25);
  tela_posiciona(jogo->pos);
  printf("| Cor Escolhida |\n");
}

void quadrados(Rg_jogo *jogo){
  int i;
  for (i = 0; i < 5; i++)
  {
    func_pos(jogo, 4+i, 10);
    tela_posiciona(jogo->pos);
    printf("   ");
    tela_cor_fundo(jogo->pc);
    tela_cor_letra(jogo->pc);
    printf("       ");
    tela_cor_normal();
    printf("         ");
    tela_cor_fundo(jogo->user);
    tela_cor_letra(jogo->user);
    printf("       ");
    tela_cor_normal();
    printf("\n");
  }
  titulo_quadrados(jogo);
}

void switch_linhas(int h, int i){
  cor cores[3] = {{i * 4, 0, 0}, {0, i * 4, 0}, {0, 0, i * 4}};
  tela_cor_letra(cores[h]);
  tela_cor_fundo(cores[h]);
}

void imprime_seta_linha(int camada, int h, int cores[3]){
  if(camada == h){
      printf("< %d \n\n", cores[h]);
    }else{
      printf("  %d \n\n", cores[h]);
    }
}

void linhas(Rg_jogo *jogo){
  int cores[3] = {jogo->user.vermelho, jogo->user.verde, jogo->user.azul};
  int h, i, linhas[3];
  func_pos(jogo, 11,1);
  tela_posiciona(jogo->pos);
  for (h = 0; h < 3; h++){
    linhas[h] = cores[h] / 4;
    for (i = 0; i < 64; i++){
      if (i == linhas[h])
      {
        tela_cor_normal();
        printf(" ");
      }
      else
      {
        switch_linhas(h, i);
        printf(" ");
      }
    }
    tela_cor_normal();
    imprime_seta_linha(jogo->camada, h, cores);
  }
}

void cronometro(Rg_jogo *jogo){
  jogo->pos.linha = 2;
  jogo->pos.coluna = 1;
  tela_posiciona(jogo->pos);
  printf("Tempo: %.1lf", jogo->tempo);
}

void desenha_tela(Rg_jogo *jogo){
  cronometro(jogo);
  quadrados(jogo);
  linhas(jogo);
}

void processa_up(Rg_jogo *jogo){
  if (jogo->camada > 0)
  {
    jogo->camada--;
  }
}

void processa_down(Rg_jogo *jogo){
  if (jogo->camada < 2)
  {
    jogo->camada++;
  }
}

void processa_left(Rg_jogo *jogo){
  switch (jogo->camada){
    case 0:
      if (jogo->user.vermelho > 0){
        jogo->user.vermelho--;
      }
      break;
    case 1:
      if (jogo->user.verde > 0){
        jogo->user.verde--;
      }
      break;
    case 2:
      if (jogo->user.azul > 0){
        jogo->user.azul--;
      }
      break;
    default:
      break;
  }
}

void processa_right(Rg_jogo *jogo){
  switch (jogo->camada){
    case 0:
      if (jogo->user.vermelho < 255){
        jogo->user.vermelho++;
      }
      break;
    case 1:
      if (jogo->user.verde < 255){
        jogo->user.verde++;
      }
      break;
    case 2:
      if (jogo->user.azul < 255){
        jogo->user.azul++;
      }
      break;
    default:
      break;
  }
}

void verifica_tecla(Rg_jogo *jogo){
  switch (jogo->tecla){
    case c_up:
      processa_up(jogo);
      break;
    case c_down:
      processa_down(jogo);
      break;
    case c_left:
      processa_left(jogo);
      break;
    case c_right:
      processa_right(jogo);
      break;
    case c_enter:
      jogo->enter = true;
      break;
  }
}

void loop(Rg_jogo *jogo)
{
  tela_mostra_cursor(false);
  double inicio = tela_relogio();
  do{
    jogo->tempo = tela_relogio() - inicio;
    desenha_tela(jogo);
    jogo->tecla = tela_le_char();
    verifica_tecla(jogo);
  } while (jogo->tempo < 20 && jogo->enter == false);
  tela_cor_normal();
  tela_mostra_cursor(true);
}

void tela_resultado(Rg_jogo *jogo){
  tela_limpa();
  func_pos(jogo, 1,1);
  tela_posiciona(jogo->pos);
  printf("Pontuaçao Final: %.2f\n", jogo->jogador_atual.pontos);
  printf("Sua cor: (%d, %d, %d)\n", jogo->user.vermelho, jogo->user.verde, jogo->user.azul);
  printf("Resposta: (%d, %d, %d)\n", jogo->pc.vermelho, jogo->pc.verde, jogo->pc.azul);
  tela_cor_normal();
}

void while_enter_confirma(){
  printf("Clique Enter");
  while (tela_le_char() != c_enter);
}

void partida(Rg_jogo *jogo){
  srand(time(0));
  inicializa_valores(jogo);
  loop(jogo);
  compara(jogo);
  while_enter_confirma();
  tela_destroi();
}

void print_placar(Rg_jogo jogo){
  printf("\nTop Pontuaçoes: ");
  printf("\n1- %.2f   %s", jogo.ranking[0].pontos, jogo.ranking[0].nome);
  printf("\n2- %.2f   %s", jogo.ranking[1].pontos, jogo.ranking[1].nome);
  printf("\n3- %.2f   %s", jogo.ranking[2].pontos, jogo.ranking[2].nome);
}

void funcao_ranking(Rg_jogo *jogo){
  int pontos_jogador = jogo->jogador_atual.pontos;

    for(int i=0; i<3; i++){
        if(pontos_jogador > jogo->ranking[i].pontos){
            if(i<2){
                jogo->ranking[2] = jogo->ranking[1];
            }
            if(i < 1){
                jogo->ranking[1] = jogo->ranking[0];
            }
            jogo->ranking[i] = jogo->jogador_atual;
            break;
        }
    }
}

void pergunta_nome(Rg_jogo *jogo){
  char nome[20];
  strcpy(nome, jogo->jogador_atual.nome);
  while ((strcmp(nome, jogo->ranking[0].nome) == 0 || strcmp(nome, jogo->ranking[1].nome) == 0 || strcmp(nome, jogo->ranking[2].nome) == 0) || strlen(nome) < 3)
  {
    printf("\nDigite seu nome: ");
    scanf(" %[^\n]s ", jogo->jogador_atual.nome);
    strcpy(nome, jogo->jogador_atual.nome);
  }
}

void jogar_de_novo(char *resposta){
  printf("\nJogar novamente? S ou N\n");
  scanf(" %c", resposta);
}

void le_arquivo(Rg_jogo *jogo){
    FILE *file;
    file = fopen("arquivo.txt", "r");

    if(file != NULL){
        fscanf(file, "%f %20[^,],%f %20[^,],%f %20[^,]", &jogo->ranking[0].pontos, jogo->ranking[0].nome, &jogo->ranking[1].pontos, jogo->ranking[1].nome, &jogo->ranking[2].pontos, jogo->ranking[2].nome);
        //Lê até máximo 20 caracteres ou até achar a vírgula ((pra funcionar com espaço)
        fclose(file);
    }
}

void escreve_arquivo(Rg_jogo jogo){
    FILE *file;
    file = fopen("arquivo.txt", "w");
    fprintf(file, "%f %s,%f %s,%f %s\n", jogo.ranking[0].pontos, jogo.ranking[0].nome, jogo.ranking[1].pontos, jogo.ranking[1].nome, jogo.ranking[2].pontos, jogo.ranking[2].nome);
    fclose(file);
}

void roda_partida(Rg_jogo *jogo){ 
    configura_tela_inicial(jogo);
    partida(jogo);
    tela_resultado(jogo);
    pergunta_nome(jogo);
    funcao_ranking(jogo);
    print_placar(*jogo);
}

void configura_tela_final(){
  tela_limpa();
  posicao pos = {1,1};
  tela_posiciona(pos);
  printf("Jogo Finalizado!\n");
}

int main()
{
  Rg_jogo jogo = {
    .user = {0,0,0},
    .pc = {0,0,0},
    .jogador_atual.nome = "",
    .jogador_atual.pontos = 0,
    .ranking = {{"-", 0}, {"-", 0}, {"-", 0}},
    .resposta = 'S'
   };

  le_arquivo(&jogo);

  while (jogo.resposta == 'S')
  {
    roda_partida(&jogo);
    jogar_de_novo(&jogo.resposta);
  }
  escreve_arquivo(jogo);
  configura_tela_final();
  return 0;
}
