#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ------ Geanderson Lemonte e Luiz Fernando Zorzanelli  -- v02 --------

typedef char string[20];

typedef struct tipoDisciplina
{
  string nome_disciplina;
  string semestreLetivo;
  float nota;
  tipoDisciplina *prox, *ante;
} TDisciplina;

typedef struct tipoAluno
{
  string nome_aluno;
  char sexo;
  tipoAluno *prox;
  TDisciplina *lista_disciplinas;
} TAluno;

typedef struct tipoTurma
{
  string nome_turma;
  tipoTurma *prox;
  TAluno *lista_alunos;
} TTurma;

typedef struct tipoCurso
{
  string nome_curso;
  tipoCurso *ante, *prox;
  TTurma *lista_turmas;
} TCurso;

typedef struct tipoLista
{
  int total;
  tipoCurso *inicio;
  tipoCurso *fim;
} TLista;

TLista lista;

// funcoes para verificacao de sexo

int verificaEntradaSexoFeminino(char valor)
{
  if ((valor == 'F' || valor == 'f'))
    return 1;
  return 0;
}
int verificaEntradaSexoMasculino(char valor)
{
  if ((valor == 'm' || valor == 'M'))
    return 1;
  return 0;
}

// ENCONTRAR VALORES

TCurso *encontrarCurso(TLista *L)
{
  string curso_selecionado;
  printf("\n\n\n");
  printf("\tInforme NOME DO CURSO:");
  scanf(" %s", curso_selecionado);

  TCurso *curso = L->inicio;
  while (curso != NULL)
  {
    char *verificar_contem = strstr(curso->nome_curso, curso_selecionado);
    if (verificar_contem != NULL)
    {
      return curso;
    }
    curso = curso->prox;
  }
  return NULL;
}

TDisciplina *encontrarDisciplina(TLista *L, TAluno *aluno, string disciplina_nome)
{
  TDisciplina *disciplina = aluno->lista_disciplinas;
  while (disciplina != NULL)
  {
    char *verificar_contem = strstr(disciplina->nome_disciplina, disciplina_nome);
    if (verificar_contem != NULL)
    {
      return disciplina;
    }
    disciplina = disciplina->prox;
  }
  return NULL;
}

TTurma *encontrarTurma(TCurso *curso, string turma_selecionado)
{
  TTurma *turma = curso->lista_turmas;
  while (turma != NULL)
  {
    char *verificar_contem = strstr(turma->nome_turma, turma_selecionado);
    if (verificar_contem != NULL)
    {
      return turma;
    }
    turma = turma->prox;
  }
  return NULL;
}
TTurma *encontrarTurmaPorCurso(TLista *L)
{
  TCurso *curso = encontrarCurso(L);
  if (curso != NULL)
  {
    string turma_selecionado;
    printf("\n\n\n");
    printf("\tInforme NOME DA TURMA:");
    scanf(" %s", turma_selecionado);
    TTurma *turma = encontrarTurma(curso, turma_selecionado);
    if (turma == NULL)
    {
      printf("\n\n ----- TURMA nao cadastrado ainda ------ \n\n");
    }
    return turma;
  }
  printf("\n\n ----- Curso nao cadastrado ainda ------ \n\n");
  return NULL;
}

TAluno *encontrarAluno(TLista *L, TTurma *turma, string aluno_nome_buscar)
{
  TAluno *aluno = turma->lista_alunos;
  while (aluno != NULL)
  {
    int verificar_contem = strcmp(aluno->nome_aluno, aluno_nome_buscar);
    if (verificar_contem == 0)
    {
      return aluno;
    }
    aluno = aluno->prox;
  }
  return NULL;
}

TAluno *encontrarAlunoPorTurma(TLista *L)
{
  TTurma *turma = encontrarTurmaPorCurso(L);
  if (turma != NULL)
  {
    string aluno_nome_buscar;
    printf("\n\n\n");
    printf("\tInforme NOME DO ALUNO:");
    scanf(" %s", aluno_nome_buscar);
    return encontrarAluno(L, turma, aluno_nome_buscar);
  }
  else
  {
    printf("\n\n ----- Aluno nao cadastrado ainda ------ \n\n");
    return NULL;
  }
}

// INSERIR DADOS

void inserirDisciplina(TDisciplina *disciplina, TAluno *aluno)
{
  TDisciplina *disciplinaAtual = aluno->lista_disciplinas;
  if (disciplinaAtual == NULL)
  {
    aluno->lista_disciplinas = disciplina;
  }
  else
  {
    while (disciplinaAtual->prox != NULL)
    {
      disciplinaAtual = disciplinaAtual->prox;
    }
    disciplinaAtual->prox = disciplina;
    disciplina->ante = disciplinaAtual;
  }
}

void inserirAluno(TAluno *aluno, TTurma *turma)
{
  TAluno *alunoAtual = turma->lista_alunos;
  if (alunoAtual == NULL)
  {
    turma->lista_alunos = aluno;
  }
  else
  {
    while (alunoAtual->prox != NULL)
    {
      alunoAtual = alunoAtual->prox;
    }
    alunoAtual->prox = aluno;
  }
}

void inserirTurma(TLista *L, TTurma *turma, TCurso *curso)
{

  if (curso->lista_turmas == NULL)
  {
    curso->lista_turmas = turma;
  }
  else
  {
    TTurma *turmaAtual = curso->lista_turmas;
    while (turmaAtual->prox != NULL)
    {
      turmaAtual = turmaAtual->prox;
    }
    turmaAtual->prox = turma;
  }
}

void inserirCurso(TLista *L, TCurso *novoCurso)
{
  if (L->inicio == NULL)
  {
    L->inicio = novoCurso;
  }
  else
  {
    TCurso *cursoAtual = L->inicio;
    while (cursoAtual->prox != NULL)
    {
      cursoAtual = cursoAtual->prox;
    }
    novoCurso->ante = cursoAtual;
    cursoAtual->prox = novoCurso;
  }
}

// INPUT DE DADOS

void inputDisciplina(TLista *L)
{
  if (L->inicio == NULL)
  {
    printf("\n\n ---- Ainda não é possivel inserir turma sem ter curso cadastrado ----- \n\n");
  }
  printf("\n\n\n");
  printf("\t=====| INSERE NOVA DISCIPLINA |=====\n\n");
  TAluno *aluno = encontrarAlunoPorTurma(L);
  if (aluno != NULL)
  {
    TDisciplina *novo = (TDisciplina *)malloc(sizeof(TDisciplina));
    printf("\tInforme NOME DA DISCIPLINA:");
    scanf(" %s", novo->nome_disciplina);
    printf("\tInforme SEMESTRE LETIVO: ");
    scanf(" %s", novo->semestreLetivo);
    printf("\tInforme NOTA: ");
    scanf("%f", &(novo->nota));
    novo->prox = NULL;
    inserirDisciplina(novo, aluno);
  }
}

void inputTurma(TLista *L)
{
  if (L->inicio == NULL)
  {
    printf("\n\n ---- Ainda não é possivel inserir turma sem ter curso cadastrado ----- \n\n");
  }
  printf("\n\n\n");
  printf("\t=====| INSERE NOVA TURMA |=====\n\n");
  TCurso *curso = encontrarCurso(L);
  if (curso != NULL)
  {
    TTurma *novo = (TTurma *)malloc(sizeof(TTurma));
    printf("\tInforme NOME DA TURMA:");
    scanf(" %s", novo->nome_turma);
    novo->prox = NULL;
    inserirTurma(L, novo, curso);
  }
  else
  {
    printf("\n\n ----- Curso nao cadastrado ainda ------ \n\n");
  }
}

void inputAluno(TLista *L)
{
  if (L->inicio == NULL)
  {
    printf("\n\n ---- Ainda não é possivel inserir aluno sem ter curso cadastrado ----- \n\n");
  }
  TTurma *turma = encontrarTurmaPorCurso(L);
  if (turma != NULL)
  {
    TAluno *novo = (TAluno *)malloc(sizeof(TAluno));
    printf("\n\n\n");
    printf("\t=====| INSERE NOVO ALUNO |=====\n\n");
    printf("\tInforme NOME DO ALUNO:");
    scanf(" %s", novo->nome_aluno);
    do
    {
      printf("\tInforme SEXO:");
      scanf(" %c", &novo->sexo);
    } while (verificaEntradaSexoMasculino(novo->sexo) == 0 && verificaEntradaSexoFeminino(novo->sexo) == 0);
    novo->prox = NULL;
    inserirAluno(novo, turma);
  }
}

void inputCurso(TLista *L)
{
  TCurso *novo = (TCurso *)malloc(sizeof(TCurso));
  printf("\n\n\n");
  printf("\t=====| INSERE NOVO CURSO |=====\n\n");
  printf("\tInforme NOME DO CURSO:");
  scanf(" %s", novo->nome_curso);
  novo->ante = NULL;
  novo->prox = NULL;
  inserirCurso(L, novo);
}

void inicializa(TLista *L)
{
  L->inicio = NULL;
  L->fim = NULL;
  L->total = 0;
}

// MOSTRAR VALORES

void mostrarCurso(TCurso *curso)
{
  printf("\t=====| NOME DO CURSO:  %s |=====\n\n", curso->nome_curso);
  TTurma *turma = curso->lista_turmas;
  printf("\t=====| MOSTRAR TURMAS DO CURSO |=====\n\n");
  while (turma != NULL)
  {
    printf("\n\t------- %s ------ \n\n", turma->nome_turma);
    turma = turma->prox;
  }
}

void listarTodosOsCursos(TLista *L)
{
  TCurso *curso = L->inicio;
  printf("\n\t=====| MOSTRAR CURSOS |=====\n\n");
  while (curso != NULL)
  {
    mostrarCurso(curso);
    curso = curso->prox;
  }
}

void mostrarTurma(TTurma *turma)
{
  printf("\t=====| NOME DA TURMA: %s |=====\n\n", turma->nome_turma);
  TAluno *aluno = turma->lista_alunos;
  printf("\t=====| MOSTRAR ALUNOS DA TURMA |=====\n\n");
  while (aluno != NULL)
  {
    printf("\n\t------- %s ------ \n\n", aluno->nome_aluno);
  }
}

void listarTodasAsTurmas(TLista *L)
{
  TCurso *curso = L->inicio;
  printf("\n\t=====| MOSTRAR TURMAS |=====\n\n");
  while (curso != NULL)
  {
    TTurma *turma = curso->lista_turmas;
    while (turma != NULL)
    {
      mostrarTurma(turma);
      turma = turma->prox;
    }
    curso = curso->prox;
  }
}

void mostrarAluno(TAluno *aluno)
{
  printf("\t------- NOME DO ALUNO: %s ------ \n\n", aluno->nome_aluno);
  printf("\t=====| MOSTRAR DISCIPLINAS DO ALUNO |=====\n\n");
  TDisciplina *disciplina = aluno->lista_disciplinas;
  while (disciplina != NULL)
  {
    printf("\n\t------- %s ------ \n\n", disciplina->nome_disciplina);
  }
}

void listarTodosOsAlunos(TLista *L)
{
  TCurso *curso = L->inicio;
  printf("\n\t=====| MOSTRAR ALUNOS |=====\n\n");
  while (curso != NULL)
  {
    TTurma *turma = curso->lista_turmas;
    while (turma != NULL)
    {
      TAluno *aluno = turma->lista_alunos;
      while (aluno != NULL)
      {
        mostrarAluno(aluno);
        aluno = aluno->prox;
      }
      turma = turma->prox;
    }
    curso = curso->prox;
  }
}

void mostrarDisciplina(TDisciplina *disciplina)
{
  printf("\t------- %s ------ \n\n", disciplina->nome_disciplina);
  printf("\t------- %.2f ------ \n\n", disciplina->nota);
  printf("\t------- %s ------ \n\n", disciplina->semestreLetivo);
}

void listarTodasAsDisciplinas(TLista *L)
{
  TCurso *curso = L->inicio;
  printf("\t=====| MOSTRAR DISCIPLINAS |=====\n\n");
  while (curso != NULL)
  {
    TTurma *turma = curso->lista_turmas;
    while (turma != NULL)
    {
      TAluno *aluno = turma->lista_alunos;
      while (aluno != NULL)
      {
        TDisciplina *disciplina = aluno->lista_disciplinas;
        while (disciplina != NULL)
        {
          mostrarDisciplina(disciplina);
          disciplina = disciplina->prox;
        }
        aluno = aluno->prox;
      }
      turma = turma->prox;
    }
    curso = curso->prox;
  }
}

// CONSULTAR POR ITEM

TCurso *consultarCursos(TLista *L)
{
  return encontrarCurso(L);
}

TTurma *consultarTurma(TLista *L)
{
  TCurso *curso = L->inicio;
  string turma_selecionado;
  printf("\n\n\n");
  printf("\tInforme NOME DA TURMA:");
  scanf(" %s", turma_selecionado);
  while (curso != NULL)
  {
    TTurma *turma = encontrarTurma(curso, turma_selecionado);
    if (turma != NULL)
    {
      return turma;
    }
    curso = curso->prox;
  }
  return NULL;
}

TDisciplina *consultarDisciplina(TLista *L)
{
  TCurso *curso = L->inicio;
  string nome_disciplina_pesquisar;
  printf("\n\n\n");
  printf("\tInforme NOME DA DISCIPLINA:");
  scanf(" %s", nome_disciplina_pesquisar);
  while (curso != NULL)
  {
    TTurma *turma = curso->lista_turmas;
    while (turma != NULL)
    {
      TAluno *aluno = turma->lista_alunos;
      while (aluno != NULL)
      {
        TDisciplina *disciplina = encontrarDisciplina(L, aluno, nome_disciplina_pesquisar);
        if (disciplina != NULL)
        {
          return disciplina;
        }
        aluno = aluno->prox;
      }
      turma = turma->prox;
    }
    curso = curso->prox;
  }
  return NULL;
}

TAluno *consultarAluno(TLista *L)
{
  TCurso *curso = L->inicio;
  string nome_aluno_pesquisar;
  printf("\n\n\n");
  printf("\tInforme NOME DO ALUNO:");
  scanf(" %s", nome_aluno_pesquisar);
  while (curso != NULL)
  {
    TTurma *turma = curso->lista_turmas;
    while (turma != NULL)
    {
      TAluno *aluno = encontrarAluno(L, turma, nome_aluno_pesquisar);
      if (aluno != NULL)
      {
        return aluno;
      }
      turma = turma->prox;
    }
    curso = curso->prox;
  }
  return NULL;
}

// EXCLUIR DADOS

int desejaExcluir()
{
  int op;
  do
  {
    printf("\n\n\n\t     =====| REALMENTE DESEJA EXCLUIR ? |=====\n\n");
    printf("0 - NAO.\n");
    printf("1 - SIM.\n");
    printf("\tInforme OPCAO desejada: ");
    scanf("%d", &op);
  } while (op != 0 && op != 1);
  return op;
}

void logExcluir()
{
  printf("\n\n\n");
  printf("+--------------------------------------+\n");
  printf("|                                      |\n");
  printf("|  No REMOVIDO com SUCESSO !!!         |\n");
  printf("|                                      |\n");
  printf("+--------------------------------------+\n\n\n");
}

void excluirCurso(TLista *L)
{
  TCurso *curso = consultarCursos(L);
  if (curso != NULL)
  {
    int excluir = desejaExcluir();
    if (excluir == 1)
    {
      if (curso->lista_turmas != NULL)
      {
        printf("\n\n\n ======== NÃO É POSSIVEL EXCLUIR ESSE CURSO POIS POSSUI TURMAS CADASTRADAS ======== \n\n\n");
        return;
      }
      if (L->inicio == curso)
      {
        L->inicio = curso->prox;
      }
      if (L->fim == curso)
      {
        L->fim = curso->ante;
      }
      TCurso *ante = curso->ante;
      TCurso *prox = curso->prox;
      if (ante != NULL)
      {
        ante->prox = prox;
      }
      if (prox != NULL)
      {
        prox->ante = ante;
      }
      free(curso);
      logExcluir();
      return;
    }
  }
  else
  {
    printf("\n\n\n ----- CURSO NAO ENCONTRADO ------ \n\n\n");
    return;
  }
}

void excluirTurma(TLista *L)
{
  TTurma *turma_encontrada = consultarTurma(L);
  if (turma_encontrada != NULL)
  {
    int excluir = desejaExcluir();
    if (excluir == 1)
    {
      if (turma_encontrada->lista_alunos != NULL)
      {
        printf("\n\n\n ======== NÃO É POSSIVEL EXCLUIR ESSA TURMA POIS POSSUI ALUNOS CADASTRADOS ======== \n\n\n");
        return;
      }
      TCurso *curso = L->inicio;
      while (curso != NULL)
      {
        TTurma *turma = curso->lista_turmas;
        if (turma == turma_encontrada)
        {
          if (turma_encontrada->prox != NULL)
          {
            curso->lista_turmas = turma_encontrada->prox;
          }
          else
          {
            curso->lista_turmas = NULL;
          }
          free(turma_encontrada);
          logExcluir();
          return;
        }
        while (turma != NULL)
        {
          if (turma->prox == turma_encontrada)
          {
            if (turma_encontrada->prox != NULL)
            {
              turma = turma_encontrada->prox;
            }
            else
            {
              turma = NULL;
            }

            free(turma_encontrada);
            logExcluir();
            return;
          }
          turma = turma->prox;
        }
        curso = curso->prox;
      }
    }
  }
  else
  {
    printf("\n\n\n ----- TURMA NÃO ENCONTRADA ---- \n\n\n");
  }
}

void excluirDisciplina(TLista *L)
{
  TDisciplina *disciplina = consultarDisciplina(L);
  if (disciplina != NULL)
  {
    int excluir = desejaExcluir();
    if (excluir == 1)
    {
      TDisciplina *prox = disciplina->prox;
      TDisciplina *ante = disciplina->ante;
      TCurso *curso = L->inicio;
      while (curso != NULL)
      {
        TTurma *turma = curso->lista_turmas;
        while (turma != NULL)
        {
          TAluno *aluno = turma->lista_alunos;
          while (aluno != NULL)
          {
            TDisciplina *disciplina_atual = aluno->lista_disciplinas;
            if (disciplina_atual == disciplina)
            {
              if (prox != NULL)
              {
                aluno->lista_disciplinas = prox;
                prox->ante = NULL;
              }
              else
              {
                aluno->lista_disciplinas = NULL;
              }
              free(disciplina);
              logExcluir();
              return;
            }
            else
            {
              if (ante != NULL)
              {
                ante->prox = prox;
              }
              if (prox != NULL)
              {
                prox->ante = ante;
              }
              free(disciplina);
              logExcluir();
              return;
            }
            aluno = aluno->prox;
          }
          turma = turma->prox;
        }
        curso = curso->prox;
      }
    }
  }
  else
  {
    printf("\n\n\n ----- DISCIPLINA NÃO ENCONTRADA ---- \n\n\n");
  }
}

void excluirAluno(TLista *L)
{
  TAluno *aluno = consultarAluno(L);
  if (aluno != NULL)
  {
    int excluir = desejaExcluir();
    if (excluir == 1)
    {
      if (aluno->lista_disciplinas != NULL)
      {
        printf("\n\n\n ======== NÃO É POSSIVEL EXCLUIR ESSE ALUNO POIS POSSUI DISCIPLINAS CADASTRADAS ======== \n\n\n");
        return;
      }
      TCurso *curso = L->inicio;
      while (curso != NULL)
      {
        TTurma *turma = curso->lista_turmas;
        while (turma != NULL)
        {
          TAluno *aluno_atual = turma->lista_alunos;
          if (aluno_atual == aluno)
          {
            if (aluno->prox != NULL)
            {
              turma->lista_alunos = aluno->prox;
            }
            else
            {
              turma->lista_alunos = NULL;
            }
            free(aluno);
            logExcluir();
            return;
          }
          while (aluno_atual != NULL)
          {
            if (aluno_atual->prox == aluno)
            {
              if (aluno->prox != NULL)
              {
                aluno_atual->prox = aluno->prox;
              }
              else
              {
                aluno_atual->prox = NULL;
              }

              free(aluno);
              logExcluir();
              return;
            }
            aluno_atual = aluno_atual->prox;
          }
          turma = turma->prox;
        }
        curso = curso->prox;
      }
    }
  }
}

// MENUS DE ACESSO

int menu_geral()
{
  int opcao;
  system("CLS");
  printf("\n\n\n\t     =====| MENU |=====\n\n");
  printf("0 - SAIR (Encerrar Aplicacao).\n");
  printf("1 - Cursos.\n");
  printf("2 - Turmas.\n");
  printf("3 - Disciplinas.\n");
  printf("4 - Alunos.\n");
  printf("\tInforme OPCAO desejada: ");
  scanf("%d", &opcao);

  if ((opcao > 4) || (opcao < 0))
  {
    printf("\n\n\n");
    printf("\t+-------------------------------------------------+");
    printf("\t|   ERRO:                                         |");
    printf("\t|                                                 |");
    printf("\t|   OPCAO INVALIDA!!!                             |");
    printf("\t|                                                 |");
    printf("\t|   Tente outra vez.                              |");
    printf("\t+-------------------------------------------------+\n\n");
    system("PAUSE");
  }
  return opcao;
}

int menu_cursos()
{
  int opcao;
  system("CLS");
  printf("\n\n\n\t     =====| MENU |=====\n\n");
  printf("0 - SAIR (Voltar).\n");
  printf("1 - Inserir Curso.\n");
  printf("2 - Excluir Curso.\n");
  printf("3 - Listar Todos os Cursos.\n");
  printf("4 - Consultar Cursos por Nome.\n");
  printf("\tInforme OPCAO desejada: ");
  scanf("%d", &opcao);

  if ((opcao > 4) || (opcao < 0))
  {
    printf("\n\n\n");
    printf("\t+-------------------------------------------------+");
    printf("\t|   ERRO:                                         |");
    printf("\t|                                                 |");
    printf("\t|   OPCAO INVALIDA!!!                             |");
    printf("\t|                                                 |");
    printf("\t|   Tente outra vez.                              |");
    printf("\t+-------------------------------------------------+\n\n");
    system("PAUSE");
  }
  return opcao;
}
int menu_turmas()
{
  int opcao;
  system("CLS");
  printf("\n\n\n\t     =====| MENU |=====\n\n");
  printf("0 - SAIR (Voltar).\n");
  printf("1 - Inserir Turma.\n");
  printf("2 - Excluir Turma.\n");
  printf("3 - Listar Todas as Turmas.\n");
  printf("4 - Consultar Turma por Nome.\n");
  printf("\tInforme OPCAO desejada: ");
  scanf("%d", &opcao);

  if ((opcao > 4) || (opcao < 0))
  {
    printf("\n\n\n");
    printf("\t+-------------------------------------------------+");
    printf("\t|   ERRO:                                         |");
    printf("\t|                                                 |");
    printf("\t|   OPCAO INVALIDA!!!                             |");
    printf("\t|                                                 |");
    printf("\t|   Tente outra vez.                              |");
    printf("\t+-------------------------------------------------+\n\n");
    system("PAUSE");
  }
  return opcao;
}
int menu_disciplinas()
{
  int opcao;
  system("CLS");
  printf("\n\n\n\t     =====| MENU |=====\n\n");
  printf("0 - SAIR (Voltar).\n");
  printf("1 - Inserir Disciplina.\n");
  printf("2 - Excluir Disciplina.\n");
  printf("3 - Listar Todas as Disciplinas.\n");
  printf("4 - Consultar Disciplina por Nome.\n");
  printf("\tInforme OPCAO desejada: ");
  scanf("%d", &opcao);

  if ((opcao > 4) || (opcao < 0))
  {
    printf("\n\n\n");
    printf("\t+-------------------------------------------------+");
    printf("\t|   ERRO:                                         |");
    printf("\t|                                                 |");
    printf("\t|   OPCAO INVALIDA!!!                             |");
    printf("\t|                                                 |");
    printf("\t|   Tente outra vez.                              |");
    printf("\t+-------------------------------------------------+\n\n");
    system("PAUSE");
  }
  return opcao;
}
int menu_alunos()
{
  int opcao;
  system("CLS");
  printf("\n\n\n\t     =====| MENU |=====\n\n");
  printf("0 - SAIR (Voltar).\n");
  printf("1 - Inserir Aluno.\n");
  printf("2 - Excluir Aluno.\n");
  printf("3 - Listar Todas os Alunos.\n");
  printf("4 - Consultar Aluno por Nome.\n");
  printf("\tInforme OPCAO desejada: ");
  scanf("%d", &opcao);

  if ((opcao > 4) || (opcao < 0))
  {
    printf("\n\n\n");
    printf("\t+-------------------------------------------------+");
    printf("\t|   ERRO:                                         |");
    printf("\t|                                                 |");
    printf("\t|   OPCAO INVALIDA!!!                             |");
    printf("\t|                                                 |");
    printf("\t|   Tente outra vez.                              |");
    printf("\t+-------------------------------------------------+\n\n");
    system("PAUSE");
  }
  return opcao;
}

void opcao_cursos(TLista *L)
{
  int curso_op;
  do
  {
    curso_op = menu_cursos();
    switch (curso_op)
    {
    case 0:
      break;
    case 1:
      inputCurso(L);
      break;
    case 2:
      excluirCurso(L);
      break;
    case 3:
      listarTodosOsCursos(L);
      break;
    case 4:
      TCurso *curso = consultarCursos(L);
      if (curso == NULL)
      {
        printf("\n\n ----- Curso Não encontrado ----- \n\n");
      }
      else
      {
        mostrarCurso(curso);
      }
      break;
    }
  } while (curso_op != 0);
}

void opcao_turmas(TLista *L)
{
  int turmas_op;
  do
  {
    turmas_op = menu_turmas();
    switch (turmas_op)
    {
    case 0:
      break;
    case 1:
      inputTurma(L);
      break;
    case 2:
      excluirTurma(L);
      break;
    case 3:
      listarTodasAsTurmas(L);
      break;
    case 4:
      TTurma *turma = consultarTurma(L);
      if (turma == NULL)
      {
        printf("\n\n ----- Turma nao cadastrado ainda ------ \n\n");
      }
      else
      {
        mostrarTurma(turma);
      }
      break;
    }
  } while (turmas_op != 0);
}

void opcao_disciplinas(TLista *L)
{
  int disciplinas_op;
  do
  {
    disciplinas_op = menu_disciplinas();
    switch (disciplinas_op)
    {
    case 0:
      break;
    case 1:
      inputDisciplina(L);
      break;
    case 2:
      excluirDisciplina(L);
      break;
    case 3:
      listarTodasAsDisciplinas(L);
      break;
    case 4:
      TDisciplina *disciplina = consultarDisciplina(L);
      if (disciplina == NULL)
      {
        printf("\n\n ----- Disciplina nao cadastrado ainda ------ \n\n");
      }
      else
      {
        mostrarDisciplina(disciplina);
      }
      break;
    }
  } while (disciplinas_op != 0);
}

void opcao_alunos(TLista *L)
{
  int alunos_op;
  do
  {
    alunos_op = menu_alunos();
    switch (alunos_op)
    {
    case 0:
      break;
    case 1:
      inputAluno(L);
      break;
    case 2:
      excluirAluno(L);
      break;
    case 3:
      listarTodosOsAlunos(L);
      break;
    case 4:
      TAluno *aluno = consultarAluno(L);
      if (aluno == NULL)
      {
        printf("\n\n ----- Aluno nao cadastrado ainda ------ \n\n");
      }
      else
      {
        mostrarAluno(aluno);
      }
      break;
    }
  } while (alunos_op != 0);
}

void selecionar_primeira_opcao(TLista *L)
{
  int op;
  do
  {
    op = menu_geral();
    switch (op)
    {
    case 1:
      opcao_cursos(L);
      break;
    case 2:
      opcao_turmas(L);
      break;
    case 3:
      opcao_disciplinas(L);
      break;
    case 4:
      opcao_alunos(L);
      break;
    }

  } while (op != 0);
}

int main()
{
  inicializa(&lista);
  selecionar_primeira_opcao(&lista);
}