#include<stdio.h>
#include<iostream>
#include<string.h>
#include<locale.h>

struct VIAGEM
{
	int id;
	char nome[20];
	float valor;
	float preco_custo;
};
VIAGEM viajar;
int tamanho(FILE *);
void cadastrar_viagem(FILE *);
void consultar_viagem(FILE *);
void geraarqtxt(FILE *);
void excluir(FILE *);
int pegar_id(FILE *);

int main()
{
	int op;
	FILE *arq;
	setlocale(LC_ALL,"");

	if ((arq = fopen("dados.dat", "rb+")) == NULL)
	{
		if ((arq = fopen("dados.dat", "wb+")) == NULL)
		{
			printf("Falha ao abrir o arquivo!\n");
			system("pause");
		}
	}
		do
		{
			if(op <= 0 || op > 5){
				printf("Opção inválida !\n");
				system("pause");
			}
			
			system("CLS");
			printf("\n======= Cadastro de Plano de Viagens ======= \n");
			printf("1 == Cadastro de viagens\n");
			printf("2 == Consultar por id\n");
			printf("3 == Gerar arquivo\n");
			printf("4 == Excluir registro\n");
			printf("5 == Sair\n");
			printf("Opcao:");
			scanf("%d", &op);
			switch (op)
			{
			case 1:
				cadastrar_viagem(arq);
				break;
			case 2:
				consultar_viagem(arq);
				break;
			case 3:
			     geraarqtxt(arq);
				break;
			case 4:
				excluir(arq); 
				break;
	
			case 5: fclose(arq);
			}
		} while (op != 5);
	}


	

void cadastrar_viagem(FILE *arq)
{
	int i = pegar_id(arq);
  	viajar.id = i;
	char confirma;
	system("cls");
	printf("Cadastrando nova viagem:\n");
	printf("\nDigite o nome do local da viagem:");
	scanf("%s",&viajar.nome);
	printf("Valor da passagem:");
	scanf("%f",&viajar.valor);
	printf("Preço custo da viagem:");
	scanf("%f",&viajar.preco_custo);
	printf("O id da sua venda é: %i",viajar.id);
	printf("\nConfirma <s/n>:");
	fflush(stdin);
	scanf("%c", &confirma);

	if (toupper(confirma) == 'S')
	{
		printf("\ngravando...\n\n");
		fseek(arq, 0, SEEK_END);
		fwrite(&viajar, sizeof(viajar), 1, arq);
		memset(viajar.nome,0,20);
		i++;

	}
	system("pause");
}

void consultar_viagem(FILE *arq)
{
	int id;
	printf("\nConsultar passagem pelo ID\n");
	printf("\nInforme o ID:");
	scanf("%d", &id);
	if ( id>= 0 )
  	{
      fseek(arq, id * sizeof(viajar), SEEK_SET);
      fread(&viajar, sizeof(viajar),1,arq);
      if (viajar.id >= 0)
      {
        printf("Id da viagem: %i\n",viajar.id);
        printf("País da viagem: %s\n",viajar.nome);
        printf("Preço da viagem: %.2f\n", viajar.valor);
        printf("Preço de custo: %.2f\n", viajar.preco_custo);
        system("pause");
      }    
      else
        printf("Id não encontrado.\n");
        system("pause");
  	}
}

void geraarqtxt(FILE *arq)
{
	char nomearq[20];
	printf("Nome do arquivo texto:");
	scanf("%s",  &nomearq);
	strcat(nomearq, ".txt");
	printf("Criando arquivo \n");
  	FILE *nome_arquivo = fopen(nomearq, "w");
	if (!nome_arquivo)
	{
		printf("Nao foi possivel criar esse arquivo!\n");
		system("pause");
		//return;
	}
		printf("\nO arquivo texto foi criado.");
		int nr;
		fprintf(nome_arquivo, "Id | Nome/Viagem   Valor      Preço/Custo \n");
		for (nr = 0; nr < tamanho(arq); nr++)
		{
			
			fseek(arq, nr * sizeof(VIAGEM), SEEK_SET);
			fread(&viajar, sizeof(VIAGEM), 1, arq);
		    if(viajar.id >= 0)
		    	{
					fprintf(nome_arquivo, "%i  | ", viajar.id);
					fprintf(nome_arquivo, "  %s   ", viajar.nome);
					fprintf(nome_arquivo, "R$%.2f      ", viajar.valor);
					fprintf(nome_arquivo, "R$%.2f   \n", viajar.preco_custo);
					fprintf(nome_arquivo, "===|====================================\n");
		    	}
		}
		
	
	fclose(nome_arquivo);
	system("pause");
}

void excluir(FILE *arq)
{
	char confirma;
	int nr;

	printf("\nInforme o ID da viagem para exclusão\n");
	scanf("%d", &nr);
	if ((nr <= tamanho(arq)) && (nr>0))
	{
		fseek(arq, (nr ) * sizeof(viajar), SEEK_SET);
		fread(&viajar, sizeof(viajar), 1, arq);
		if (viajar.id == nr)
		{
			printf("\nNome do país da viagem:%s", viajar.nome);
			printf("\nValor da viagem:%.2f", viajar.valor);
			printf("\nPreço custo da viagem:%.2f\n", viajar.preco_custo);
			printf("\nConfirma a exclusao: <s/n>\n");
			getchar();
			scanf("%c", &confirma);

			if (toupper(confirma) == 'S')
			{
				printf("\nexcluindo...\n\n");
				fseek(arq, (nr) * sizeof(viajar), SEEK_SET);
				viajar.id = -1;
				fwrite(&viajar, sizeof(viajar), 1, arq);
				printf("Viagem cancelada com sucesso!! \n");
			}
		}
	}else
	{
		printf("\nNumero de registro invalido!\n");
		system("pause");
	}
	system("pause");
}
int tamanho(FILE *arq)
{
  fseek(arq, 0, SEEK_END);
  return ftell(arq) / sizeof(VIAGEM);
}
int pegar_id(FILE *arq)
{
  int posicao;
  fseek(arq, 0, SEEK_END);
  posicao = ftell(arq) / sizeof(viajar);
  return posicao;
}
