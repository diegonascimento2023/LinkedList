/*
Listas encadeadas são estruturas de dados que permitem armazenar uma coleção
 de elementos de um mesmo tipo.

Neste arquivo, temos a implementação de uma lista encadeada simples de inteiros.
*/

#include "lista.h"

struct lista
{
	int info;// Armazena  um elemento do tipo inteiro na estrutura lista
	struct lista *prox;// Armazena o endereço do proximo elemento que será armazenado na estrutura lista
};

// função que cria uma lista vazia (NULL)
Lista *lst_cria(void)
{
	return NULL;// Retorna uma lista vazia
}

// função que insere um elemento no início da lista
Lista *lst_insere(Lista *l, int v)//Recebe como parâmetro a lista do tipo Lista que irá receber o elemento do tipo inteiro que será inserido
{
	Lista *novo = (Lista *)malloc(sizeof(Lista));//Aloca a memória dinamicamente para que o elementop seja inserido no espaço criado.
	if (novo == NULL)//Verifica se a memoria suficiente para alocar o espaço para "novo".
	{
		printf("[ERRO] memoria insuficiente!");//Exibe a mensagem de erro caso não tenha memmória sufiente.
		exit(1);//Aborta o programa
	}
	novo->info = v;// novo->info recebe o elemento v e armazena o elemento na struct lista
	novo->prox = l;// novo->prox recebe  o endereço da lista l e armazena o endereço do proximo elemento que será armazenado na estrutura lista. Dessa forma, "novo" passa a ser o novo elemento da lista l.
	return novo;//Retorna a lista com o novo elemento e o endereço do proximo elemento que será inserido.

	/* Ou para alterar diretamente

	void lst_insere(Lista** t, int v){
	Lista* novo = (Lista*) malloc(sizeof(Lista));
	novo->info = v;
	novo->prox = *t;
	*t = novo; */
}

// função que verifica se a lista está vazia
int lst_vazia(Lista *l)//Recebe como parâmetro o endereço da lista a ser verificada
{
	return (l == NULL);//Retorna a lista recebida com parâmetro vazia
}

// função que imprime os elementos da lista
void lst_imprime(Lista *l)//Recebe como parâmetro o endereço da lista a ser impressa. Assim como, l representa o endereço  do primeiro elemento da lista.
{
	Lista *p;//Criada a variável p do tipo lista para ser o contador do laço.
	for (p = l; p != NULL; p = p->prox)//O laço é iniciado quando o contador p recebe o endereço de l(o endereço do primeiro elemento da lista), logo em seguida verifica se p é diferente de NULL, se ele for diferente quer dizer que o endereço está preenchido, então ele imprime o elemento que está no endereço e recebe o endereço do proximo elemento da lista. Após isso, ele faz novamente todo o processo  até encontrar um p igual a NULL, ou seja, o endereço está vazio e significa que  
	{
		printf("\tInfo = %d \n", p->info);//Exibe o elemento presente no endereço armazenado em p.
	}
}

// função que busca um elemento na lista
Lista *lst_busca(int elemento, Lista *l)// Recebe como parâmetro o elemento a ser buscado e em qual lista ele deve ser buscado
{
	Lista *p;//Criada a variável p do tipo lista para ser o contador do laço.
	for (p = l; p != NULL; p = p->prox)//O laço é iniciado quando o contador p recebe o endereço de l(o endereço do primeiro elemento da lista), logo em seguida verifica se p é diferente de NULL, se ele for diferente quer dizer que o endereço está preenchido, então ele compara se o elemento que está no endereço armazenado em p é  igual ao que foi recebido como parrâmetro, se for igual ele retorna o elemento presente no endereço de p, se for diferente p recebe o endereço do proximo elemento da lista.   
	
	{
		if (p->info == elemento)//Verifica se o elemento presente no endereço de p é igual ao elemento passado como parâmetro
			return p;
	}

	return NULL;//Retorna NULL se nenhum elemento presente na lista for igual ao elemento passado como parâmetro.
}

// função que retira um elemento da lista
Lista *lst_retira(Lista *l, int v)// Recebe como parâmetro o elemento a ser retirado e em qual lista ele deve ser retirado
{
	Lista *ant = NULL; /* ponteiro para elemento anterior */
	Lista *p = l;	   /* ponteiro para percorrer a lista*/
	/* procura elemento na lista, guardando anterior */
	while (p->info != v)
	{
		if (p == NULL)
			return l; /* n�o achou: retorna lista original */
		ant = p;
		p = p->prox;
		/* verifica se achou elemento */
	}
	/* retira elemento */
	if (ant == NULL)
		/* retira elemento do inicio */
		l = p->prox;
	else
		/* retira elemento do meio da lista */
		ant->prox = p->prox;
	free(p);
	return l;
}

// função que libera a memória alocada para a lista
void lst_libera(Lista *l)// Recebe como parâmetro a lista que irá ter sua memória liberada 
{
	Lista *p = l; /* ponteiro para percorrer a lista*/
	Lista *t;/*Ponteiro auxiliar*/
	while (p != NULL)/* procura o final da lista, liberando a memoria alocada */
	{
		t = p->prox;//t recebe o endereço do proximo elemento
		free(p);//Libera a memoria alocada para p
		p = t;//p recebe o endereço do elemento sucessor de p
	}
}

// Função que insere de forma ordenada um elemento na lista
Lista *lst_insere_ordenada(Lista *l, int v)// Recebe como parâmetro o elemento a ser inserido e ordenado e em qual lista ele deve ser inserido e ordenado
{
    Lista *novo;  // ponteeiro para um novo elemento da lista
    Lista *ant = NULL; // Ponteiro para o elemento anterior e que recebe NULL
    Lista *p = l; // Ponteiro para percorrer a lista

    while (p != NULL && p->info < v) // Percorre a lista até encontrar o local correto para inserir o elemento de forma ordenada
    {
        ant = p; // Mantém um ponteiro para o elemento anterior
        p = p->prox; // Move para o próximo elemento na lista
    }

    novo = (Lista *)malloc(sizeof(Lista)); // Aloca memória para o novo elemento
    novo->info = v; // Define o valor do novo elemento que foi passado como parâmetro

    if (ant == NULL) // Se ant for NULL, o novo elemento deve ser inserido no início da lista
    {
        novo->prox = l;// O próximo do novo elemento aponta para o início da lista
        l = novo; // Atualiza o início da lista para o novo elemento
      
    }
    else
    {
        novo->prox = ant->prox; // Caso contrário, o novo elemento é inserido após o elemento anterior
        ant->prox = novo; // O próximo do elemento anterior aponta para o novo elemento
    }

    return l; // Retorna a lista atualizada
}


// Função que lê de um arquivo e armazena na lista encadeada de inteiros
Lista *lst_ler_arquivo(char *nome_arquivo)// Recebe como parâmetro o nome do arquivo a ser aberto e lido.
{
    FILE *arquivo; // Declara um ponteiro para um arquivo
    int valor; // Variável para armazenar o valor lido do arquivo
    Lista *l = lst_cria(); // Inicializa uma lista vazia

    arquivo = fopen(nome_arquivo, "r"); // Abre o arquivo para leitura
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo!\n"); // Se houver um erro ao abrir o arquivo, exibe uma mensagem de erro
        exit(1); // Encerra o programa
    }
    while (fscanf(arquivo, "%d", &valor) != EOF) // Lê valores inteiros do arquivo até o final do arquivo (EOF)
    {
        l = lst_insere(l, valor); // Insere o valor lido na lista usando a função lst_insere
    }
    fclose(arquivo); // Fecha o arquivo
    return l; // Retorna a lista com os valores lidos do arquivo
}

