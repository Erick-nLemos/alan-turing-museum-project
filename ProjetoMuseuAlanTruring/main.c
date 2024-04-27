                                        // By ERICK DO NASCIMENTO LEMOS & SAMARA REGINA
#include <stdio.h>
#include <stdlib.h>
#include <time.h> // Para fazer com que a função rand() sempre gere numeros aleatorios
#include <windows.h> // Lib que permite criar janelas e botões
#include <string.h> // Para manipular strings
#define STRTAM 88 // Constante que define o limite da borda
#define MAX_CAD 100 // Maximo de cadastros
#define MAX_TEXT_LENGHT 100 //Tamanho maximo do comprimento de uma string

// Dados do ingresso
typedef struct dadosVenda{
        char nomeComp[50], emailComp[50], cpfComp[12], tipoPag[20], horario[20];
        int token;
}dadosVenda;
dadosVenda dadosIng[MAX_CAD]; // array que pode armazenar 100 ingressos

//Declaração da estrutura "dadosCliente":
typedef struct dadosCliente{
    //cada um com espaço para armazenar até 100 caracteres,armazenar dados de cadastro.
    char nome[100], telefone[100], cpf[100], ender[100], email[100], senhaCliente[50];

}dadosCliente;
dadosCliente CadC[MAX_CAD];// array que pode armazenar 100 cadastros

void salvarCad(FILE *pf);
void lerCad(FILE *pf);
void linhaCol(int lin, int col);
void box(int lin1, int col1, int lin2, int col2);
void textColor(int letras, int fundo);
void boxMenu();
void Home(FILE *pf);
void opcaoMenu(FILE *pf);
void Exposicao(FILE *pf);
void Sobre();
void Vendas(FILE *pf);
void VendaConfirm(FILE *pf, int q, float *valorTotal, char sessao[]);
void Ingresso(int q,float *vTotal, FILE *pf);
void ValIng(FILE *pf);
void FaleConosco();
void LoginTipo(FILE *pf);
void LoginFunc(FILE *pf);
void TelaFunc(FILE *pf, char userFunc[], dadosVenda dadosIng[]);
void LoginCliente(FILE *pf);
void CadastroCliente(FILE *pf);
void TelaCliente(FILE *pf, char userValid[], int indiceCad);

//contador de cadastros
int numCad = 0;
//contador de Ingressos gerados
int numIng = 0;
//contador de ingressos usados
int numIng_used = 0;

// Representar Valores de Opções : Enums são frequentemente usados ​​para representar opções, no caso usamos para criar um grupo de cores.
enum{
    BLACK,
    BLUE,
    GREEN,
    RED,
    WHITE
};
enum{
_BLACK=0,
_BLUE=16,
_GREEN=32,
_RED=64,
_WHITE
};

// -----------------------------------------------------------------  Corpo Principal de Execução  ------------------------------------------------------------
int main(){

    FILE *pf = fopen("dadosC.csv", "r");
    if(pf != NULL){
        lerCad(pf);
        fclose(pf);
    }
    else{
        printf("Erro ao ler arquivo!");
    }

    //textColor(250,250); //mudar tema (cor) do sistema
    Home(pf);

}

// -----------------------------------------------------------------  Definindo Funções ------------------------------------------------------------
/*// rescrever dados de compra no arquivo csv
void salvarIng(FILE *fi){// fi = file ingresso
    for(int i = 0; i < numIng; i++){
        fprintf(fi, "%s,%s,%s,%s,%s,%d\n", dadosIng[i].nomeComp, dadosIng[i].emailComp,
                dadosIng[i].cpfComp, dadosIng[i].tipoPag, dadosIng[i].horario, dadosIng[i].token);
    }
}

// ler dados de cadastro de compra no arquivo csv
void lerIng(FILE *fi){
    char linha[MAX_TEXT_LENGHT * 6]; //maximo da linha
    numIng = 0;

    while(fgets(linha, sizeof(linha), fi) && numIng < MAX_CAD){
        sscanf(linha, "%49[^,],%49[^,],%11[^,],%19[^,],%19[^,],%d",
                dadosIng[numIng].nomeComp, dadosIng[numIng].emailComp, dadosIng[numIng].cpfComp,
                dadosIng[numIng].tipoPag, dadosIng[numIng].horario, dadosIng[numIng].token);
        numIng++;
    }

}
FILE *fi;*/

// escrever dados do cadastro em arquivo csv
void salvarCad(FILE *pf){
    for(int i = 0; i < numCad; i++){
        fprintf(pf, "%s,%s,%s,%s,%s, %s\n", CadC[i].nome, CadC[i].telefone, CadC[i].cpf, CadC[i].ender, CadC[i].email, CadC[i].senhaCliente);
    }
}

// ler dados de cadastro no arquivo csv
void lerCad(FILE *pf){
    char linha[MAX_TEXT_LENGHT * 6]; //maximo da linha
    numCad = 0;

    while(fgets(linha, sizeof(linha), pf) && numCad < MAX_CAD){
        sscanf(linha, "%99[^,],%99[^,],%99[^,],%99[^,],%99[^,],%49s",
               CadC[numCad].nome, CadC[numCad].telefone, CadC[numCad].cpf,
               CadC[numCad].ender, CadC[numCad].email, CadC[numCad].senhaCliente);
        numCad++;
    }

}

// ----------------------------------------------------------------- Montar Caixa ------------------------------------------------------------
void linhaCol(int lin, int col) {// criou uma funçao " linhaCol" para posicionar qualquer saida de dado em qualquer posição na tela
    COORD ajuste;// usou a função COORD e criou a variavel "ajuste" para alinhar a coluna e a linha do texto.
    ajuste.X = col -1; // Ajusta para 0-based index
    ajuste.Y = lin -1; // Ajusta para 0-based index

    // usou a função de posição do cursor com os dados de saida.
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), ajuste);
}

void box(int lin1, int col1, int lin2, int col2){// criou a função "box" para criar bordas e criou as variaveis de linha e coluna

    int i, j, tamlin, tamcol;// criou as variaveis de tamanho e do loop dentro do for


    tamlin= lin2-lin1;// definiu o valor de tamlin e tamcol subtraindo as linhas e as colunas
    tamcol= col2-col1;// definiu o valor de tamlin e tamcol subtraindo as linhas e as colunas

    // linhas da caixa:
    for(i=col1;i<=col2;i++){// declarou e i recebe a coluna 1, após isso ele perguntou se i é menor ou igual a coluna 2 se for verdade vai desenhar as linhas de cima e de baixo;
        linhaCol(lin1,i);// desenhar a linha de cima
        printf("%c", 196);// declarou a quantidade de caracteres e pediu para exibir na tela
        linhaCol(lin2,i);// desenhar a linha de baixo
        printf("%c",196);// declarou a quantidade de caracteres e pediu para exibir na tela
    }

    // colunas da caixa:

    // declarou e i é igual a coluna 1, após isso ele perguntou se i é menor ou igual a coluna 2 se for verdade vai desenhar as colunas de cima e de baixo;
    for(i=lin1;i<=lin2;i++){
        linhaCol(i,col1);// desenhar a coluna de cima
        printf("%c",179);// declarou a quantidade de caracteres e pediu para exibir na tela
        linhaCol(i,col2);// desenhar a coluna de baixo
        printf("%c",179);// declarou a quantidade de caracteres e pediu para exibir na tela
    }

    // fundo da caixa:
    for(i=lin1;i<lin2;i++){// enquato a linha 1 for menor que a linha 2 e...

        for(j=col1;j<col2;j++){// a coluna 1 for menor que a coluna 2...

          linhaCol(i,j);printf("");//exibir um caracter vazio na tela
        }
    }

    // posição dos cantos:
    linhaCol(lin1,col1);
    printf("%c",218);
    linhaCol(lin1,col2);
    printf("%c",191);
    linhaCol(lin2,col1);
    printf("%c",192);
    linhaCol(lin2,col2);
    printf("%c",217);

}

// criamos a função textColor juntamento com letras + fundo para atribuir cores em nossa tela de exibição.
void textColor(int letras, int fundo){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), letras+fundo);

}

// ----------------------------------------------------------------- Funções de Menu Principal ------------------------------------------------------------
// parte fixa (cabeçalho) no menu principal:
void boxMenu(){

   box(1,15,30,110);// borda externa

   box(2,20,6,105); // borda interna

   // define a cor da letra + fundo do printf
   linhaCol(4,48); // define o cursor na linha 5, coluna 10
   printf("MUSEU NACIONAL - ALAN TURING\n");// Titulo principal do Museu

    linhaCol(8, 21); // define o cursor na linha 5, coluna 10
    printf("  1 - Home   2 - Sobre  3 - Compras   4 - Exposicao   5 - Acesso   6 - Fale Conosco \n");// barra de seleção do menu superior

}

// Tela Home
void Home(FILE *pf){

            box(10,20,28,62);
            box(10,20,28,105); //borda da caixa inferior
            linhaCol(15,23);// posicionar printf
            printf("MUSEU ALAN TURING\n");// exibir ao usuario o conteudo da tela selecionada
            linhaCol(17,23);// posicionar printf
            printf("O maior museu de tecnologia\n");
            linhaCol(18,23);// posicionar printf
            printf("Do Brasil dedicado a ciencia aplicada\n");
            linhaCol(19,23);// posicionar printf
            printf("E ao desenvolvimento de tecnologia\n");
            linhaCol(22,23);// posicionar printf
            printf("Voce esta pronto para uma jornada?\n");
            linhaCol(24,23);// posicionar printf
            printf("Explore o Passado!!\n");
            linhaCol(26,23);// posicionar printf
            printf("Selecione - 4\n");

            linhaCol(14,68);// posicionar printf
            printf("JUNTE-SE A NOS !\n");// exibir ao usuario o conteudo da tela selecionada
            linhaCol(16,68);// posicionar printf
            printf("Desfrute de Beneficios Exclusivos!\n");
            linhaCol(18,68);// posicionar printf
            printf("Por que se cadastrar?\n");
            linhaCol(20,68);// posicionar printf
            printf(". Ofertas Especiais\n");
            linhaCol(21,68);// posicionar printf
            printf(". Fique por Dentro das Novidades\n");
            linhaCol(22,68);// posicionar printf
            printf(". Ofertas Especiais !!\n");
            linhaCol(24,68);// posicionar printf
            printf("Selecione - 5\n");

            boxMenu();// menu principal
            opcaoMenu(pf);// menu principal
}

// menu de opções principal
void opcaoMenu(FILE *pf){

    int opcao = 1; // variavel de opção e declarou o valor
    linhaCol(10, 26); // posicionar o cursor
    //Home();
    while(opcao > 0 && opcao <= 6){// loop para o usuario sempre ter opção de seleção

            linhaCol(11, 23);// posicionar

            box(10,20,28,105);
            box(10,20,28,105);// borda da caixa inferior
            linhaCol(12,23);// posicionar o pritf
            printf("Digite o valor para onde deseja ir: ");// exibir o que o usuario deve fazer
            scanf("%d", &opcao);// receber valor declarado a variavel opção

        switch(opcao){// função swtch para criar as opções de seleção do menu de acordo com o valor declarado a variavel

        case 1://opção 1 - Tela Home
            system("cls"); // funçao para limpar a tela
            linhaCol(14,30);// posicionar printf*/
            Home(pf); // tela principal
            break;

        case 2:// opção 2 - Tela Sobre
            system("cls"); // funçao para limpar a tela
            Sobre();//exibir ao usuario o conteudo da tela selecionada
            break;

        case 3:// opção 3 de Vendas
            system("cls"); // funçao para limpar a tela
            Vendas(pf);//exibir ao usuario o conteudo da tela selecionada
            break;

        case 4: // opção - Tela de Exposição
            system("cls"); // funçao para limpar a tela
            Exposicao(pf);//exibir ao usuario o conteudo da tela selecionada
            break;

        case 5: // opção  - Tela Login
            system("cls"); // funçao para limpar a tela
            linhaCol(13, 26);//posicionar
            LoginTipo(pf);// chama a tela de Login/cadastro
            boxMenu();//menu principal
           break;

        case 6: // opção - Tela Fale Conosco
            system("cls"); // funçao para limpar a tela
            FaleConosco();// exibir ao usuario o conteudo da tela selecionada
            break;

        default:// numero da variavel opção invalido
            system("cls"); // funçao para limpar a tela
            linhaCol(12, 30);// posicionar
            printf("Numero invalido.");// informar ao usuario que ele selecionou uma opção invalida
            boxMenu();// menu principal
            linhaCol(30,10);
            opcaoMenu(pf);
            break;
        }

    }
}

// ----------------------------------------------------------------- Tela Exposicoes  ------------------------------------------------------------
void Exposicao(FILE *pf){
    int opcao;

    void AlanTuring(){
        int voltar;

        boxMenu();
        box(10,20,28,105);
        linhaCol(12,25);
        printf("O Pai da Computacao");
        linhaCol(14,22);
        printf("    Alan Turing foi um matematico, logico e pioneiro da computacao que teve um ");
        linhaCol(15,22);
        printf("papel fundamental durante a Segunda Guerra Mundial na quebra do codigo Enigma, uma ");
        linhaCol(16,22);
        printf("maquina eletromecanica de criptografia com rotores. Utilizada tanto para ");
        linhaCol(17,22);
        printf("criptografar como para descriptografar codigos de guerra, foi usada de varias ");
        linhaCol(18,22);
        printf("formas a partir de 1920. Ao criar a maquina Colossus, a maquina precursora dos ");
        linhaCol(19,22);
        printf("computadores, Turing conseguiu descriptografar os codigos do Enigma e adiantar o");
        linhaCol(20,22);
        printf("fim da Segunda Guerra.");
        linhaCol(26,70);
        printf("Home[1] ");
        linhaCol(26,80);
        printf("Voltar[5]");
        linhaCol(26,25);
        printf("Voltar: ");
        scanf("%d", &voltar);

        switch(voltar){
        case 1:
            system("cls");
            Home(pf);
            break;

        case 5:
           system("cls");
           Exposicao(pf);
           break;

        default:
            printf("Opcao Invalida!");
            system("cls");
            AlanTuring();
            break;
        }
    }

    void ArteModerna(){
        int voltar;

        boxMenu();
        box(10,20,28,105);
        linhaCol(12,25);
        printf("Semana da Arte Moderna");
        linhaCol(14,22);
        printf("    Os 100 anos da Semana da Arte Moderna celebram o marco cultural de 1922 em ");
        linhaCol(15,22);
        printf("Sao Paulo, que revolucionou as artes no Brasil, transformando e valorizando");
        linhaCol(16,22);
        printf("a expressao artistica contemporanea, influenciando as novas geracoes.");
        linhaCol(17,22);
        printf("    A semana da da Arte Moderna representou um eompimento radical, introduzindo");
        linhaCol(18,22);
        printf("uma abordagem mais experimental, ousada e inovadora em artes visuais, literatura");
        linhaCol(19,22);
        printf("e musica.");
        linhaCol(26,70);
        printf("Home[1]");
        linhaCol(26,80);
        printf("Voltar[5] ");
        linhaCol(26,25);
        printf("Voltar: ");
        scanf("%d", &voltar);

        switch(voltar){
        case 1:
            system("cls");
            Home(pf);
            break;

        case 5:
           system("cls");
           Exposicao(pf);
           break;

        default:
            printf("Opcao Invalida!");
            system("cls");
            ArteModerna();
            break;
        }
    }

    void SantosDumont(){
        int voltar;

        boxMenu();
        box(10,20,28,105);
        linhaCol(12,25);
        printf("Santos Dumont\n\n");
        linhaCol(14,22);
        printf("    Santos Dumont eh o brasileiro reconhecido como pioneiro da aviacao, apos");
        linhaCol(15,22);
        printf("realizar o primeiro voo publico de um aviao motorizado em 1906, o famoso 14-bis,");
        linhaCol(16,22);
        printf("um feito ocorrido antes dos irmaos Wright nos Estados Unidos. ");
        linhaCol(17,22);
        printf("    Santos Dumont criou inovacoes importantes para o mundo e contribuiu");
        linhaCol(18,22);
        printf("significativamente para o desenvolvimento da aviacao ate os dias atuais.");
        linhaCol(26,70);
        printf("Home[1]");
        linhaCol(26,80);
        printf("Voltar[5] ");
        linhaCol(26,25);
        printf("Voltar: ");
        scanf("%d", &voltar);

        switch(voltar){
        case 1:
            system("cls");
            Home(pf);
            break;

        case 5:
           system("cls");
           Exposicao(pf);
           break;

        default:
            printf("Opcao Invalida!");
            system("cls");
            SantosDumont();
            break;
        }
    }

    void Olimpiadas(){
        int voltar;

        boxMenu();
        box(10,20,28,105);
        linhaCol(12,25);
        printf("Olimpiadas 2024\n\n");
        linhaCol(14,22);
        printf("    Sera realizada em Paris 2024  a XXXIII edicao do evento esportivo misturando");
        linhaCol(15,22);
        printf("tradicao e inovacao, com foco na sustentabilidade, tambem em entregar inovacoes");
        linhaCol(16,22);
        printf("tecnologicas e na celebracao do esporte global. A primeira edicao dos Olimpicos");
        linhaCol(17,22);
        printf("modernos foi realizada pela primeira vez em 1896.");
        linhaCol(26,70);
        printf("Home[1]");
        linhaCol(26,80);
        printf("Voltar[5] ");
        linhaCol(26,25);
        printf("Voltar: ");
        scanf("%d", &voltar);

        switch(voltar){
        case 1:
            system("cls");
            Home(pf);
            break;

        case 5:
           system("cls");
           Exposicao(pf);
           break;

        default:
            printf("Opcao Invalida!");
            system("cls");
            Olimpiadas();
            break;
        }

    }

    boxMenu();
    box(10,20,28,105);

    linhaCol(12,25);
    printf("Nossas Exposicoes: \n");
    linhaCol(14,23);
    printf("1 - Alan Turing - Alan Turing foi um matematico, logico e pioneiro da computacao,");
    linhaCol(15,27);
    printf("conhecido como o Pai da Computacao...");
    linhaCol(17,23);
    printf("2 - 100 anos da Semana de Arte Moderna - Celebrando o marco cultural em Sao Paulo");
    linhaCol(18,27);
    printf("que revolucionou as artes no Brasil...");
    linhaCol(20,23);
    printf("3 - 150 anos de Santos Dumont - Santos Dumont foi o brasileiro pioneiro da ");
    linhaCol(21,27);
    printf("aviacao com seu primeiro voo publico em 1906...");
    linhaCol(23,23);
    printf("4 - Jogos Olimpicos de Paris 2024 - Sera realizada em Paris 2024 a XXXIII");
    linhaCol(24,27);
    printf(" edicao do evento esportivo misturando tradicao e inovacao...");
    linhaCol(26,80);
    printf(" Voltar[5]");
    linhaCol(26,25);
    printf("Digite para saber mais: ");
    scanf("%d", &opcao);

    switch(opcao){
    case 1:
        system("cls");
        AlanTuring();
        break;

    case 2:
        system("cls");
        ArteModerna();
        break;

    case 3:
        system("cls");
        SantosDumont();
        break;

    case 4:
        system("cls");
        Olimpiadas();
        break;
    case 5:
        system("cls");
        Home(pf);
        break;

    default:
        printf("Opcao Invalida!");
        system("cls");
        Exposicao(pf);
        break;
    }
}

// -----------------------------------------------------------------  Tela Sobre o Museu  ------------------------------------------------------------
void Sobre(){

            //box(10,20,28,62);
            //box(10,20,28,105); //borda da caixa inferior
            boxMenu();// mostrar menu principal
            linhaCol(15,23);// posicionar printf
            printf("Museu Alan Turing\n");// exibir ao usuario o conteudo da tela selecionada
            linhaCol(17,23);// posicionar printf
            printf("O maior museu de tecnologia\n");
            linhaCol(18,23);// posicionar printf
            printf("e um local fascinante que oferece\n");
            linhaCol(19,23);// posicionar printf
            printf("aos visitantes uma jornada pela\n");
            linhaCol(20,23);// posicionar printf
            printf("evolucao da inovacao e da ciencia.\n");
            linhaCol(21,23);// posicionar printf
            printf("Com entrevistas interativas,artefatos\n");
            linhaCol(22,23);// posicionar printf
            printf("historicos e projecoes praticas.\n");
            linhaCol(23,23);// posicionar printf
            printf("\n");
            linhaCol(24,23);// posicionar printf
            printf("Os visitantes podem explorar\n");
            linhaCol(25,23);// posicionar printf
            printf("a influencia da tecnologia\n");
            linhaCol(26,23);// posicionar printf
            printf("em nossas vidas.\n");

            linhaCol(12,68);// posicionar printf
            printf("Fundada em 2001,uma visita ao museu \n");// exibir ao usuario o conteudo da tela selecionada
            linhaCol(13,68);// posicionar printf
            printf("e uma experiencia educativa e \n");
            linhaCol(14,68);// posicionar printf
            printf("inspiradora que revela como a\n");
            linhaCol(15,68);// posicionar printf
            printf("engenhosidade humana moldou \n");
            linhaCol(16,68);// posicionar printf
            printf("o mundo moderno.\n");
            linhaCol(18,68);// posicionar printf
            printf("Um lugar onde o passado\n");
            linhaCol(19,68);// posicionar printf
            printf("o presente e o futuro se\n");
            linhaCol(20,68);// posicionar printf
            printf("encontram em um ambiente\n");
            linhaCol(21,68);// posicionar printf
            printf("cativante.\n");

            linhaCol(24,68);// posicionar printf
            printf("Dando Continuidade a Historia !\n");
            linhaCol(26,68);// posicionar printf
            printf("Venha Conhecer nossas Exposicoes\n");

}

// -----------------------------------------------------------------  Tela de Vendas  ------------------------------------------------------------
void Vendas(FILE *pf){
    int q = 0, numIng = 0, opcao, opcaoIng = 1, opcaoH = 1;
    float valorTotal, meia = 15.00, inteira = 30.00;
    char sessao[20];

    boxMenu();//cabeçalho
    box(10,20,28,105);
    linhaCol(13,25);
    printf("Compra de Ingressos"); // titulo
    box(15,25,17,50);
    linhaCol(16,27);
    printf("Quant. de Ingressos: ");
    box(15,52,17,77);
    linhaCol(16,54);
    printf("Total:\t R$%.2f", 00.00);

    box(18,25,25,50); //opçoes preço
    linhaCol(19,26);
    printf("1 - Meia: ");
    linhaCol(19,34);
    printf("\tR$%.2f", meia);
    linhaCol(21,26);
    printf("2 - Inteira: ");
    linhaCol(21,34);
    printf("\tR$%.2f", inteira);
    box(18,52,25,77); //opções horarios
    linhaCol(19,53);
    printf("1 - Manha: ");
    linhaCol(19,61);
    printf("\t09:00");
    linhaCol(21,53);
    printf("2 - Tarde: ");
    linhaCol(21,61);
    printf("\t13:00");
    linhaCol(23,53);
    printf("3 - Noite: ");
    linhaCol(23,61);
    printf("\t17:00");

    // Texto Informaçoes necessarias sobre a compra de ingressos
    linhaCol(15,80);
    printf("Informacoes Necessarias");
    linhaCol(17,80);
    printf("Deficiente tem direito a");
    linhaCol(18,80);
    printf("entrada gratuita.");
    linhaCol(19,80);
    printf("Mostre seu ingresso na");
    linhaCol(20,80);
    printf("entrada.");
    linhaCol(21,80);
    printf("Nao eh possivel a troca");
    linhaCol(22,80);
    printf("de horario apos a compra.");
    linhaCol(25,80);
    printf("Divirta-se!");

    linhaCol(16,48);
    scanf("%d", &q); // Entrar com a quantidade de ingressos a comprar

    for(int c = 1; c <= q; c++){ // Laço de repetição que repetirar até atingir a quantidade de ingressos desejada

        system("cls");
        boxMenu();//cabeçalho
        box(10,20,28,105);
        linhaCol(13,25);
        printf("Compra de Ingressos"); // titulo
        box(15,25,17,50); // Box da entrada do tipo de ingresso
        box(15,52,17,77);
        linhaCol(16,54);
        printf("Total:\t R$%.2f", valorTotal);

        box(18,25,25,50);
        linhaCol(19,26);
        printf("1 - Meia: ");
        linhaCol(19,34);
        printf("\tR$%.2f", meia);
        linhaCol(21,26);
        printf("2 - Inteira: ");
        linhaCol(21,34);
        printf("\tR$%.2f", inteira);

        box(18,52,25,77);
        linhaCol(19,53);
        printf("1 - Manha: ");
        linhaCol(19,61);
        printf("\t09:00");
        linhaCol(21,53);
        printf("2 - Tarde: ");
        linhaCol(21,61);
        printf("\t13:00");
        linhaCol(23,53);
        printf("3 - Noite: ");
        linhaCol(23,61);
        printf("\t17:00");

        // Texto Informaçoes necessarias sobre a compra de ingressos
        linhaCol(15,80);
        printf("Informacoes Necessarias");
        linhaCol(17,80);
        printf("Deficiente eh isento de");
        linhaCol(18,80);
        printf("pagamento.");
        linhaCol(19,80);
        printf("Mostre seu ingresso na");
        linhaCol(20,80);
        printf("entrada.");
        linhaCol(21,80);
        printf("Nao eh possivel a troca");
        linhaCol(22,80);
        printf("de horario apos a compra.");
        linhaCol(25,80);
        printf("Divirta-se!");

        linhaCol(16,27);
        printf("Tipo do Ingresso %d: ", c);
        scanf("%d", &opcaoIng);
        switch(opcaoIng){ // Escolher o tipo de ingresso (meia ou inteira)
        case 1:
            valorTotal += meia; // Somando o valor total dos ingressos comprados
            break;
        case 2:
            valorTotal += inteira; // Somando o valor total dos ingressos comprados
            break;
        }

        linhaCol(16,54);
        printf("Total:\t R$%.2f", valorTotal); //Mostrar o valor total
    }

    fflush(stdin);
    linhaCol(16,27);
    printf("Horario da Sessao:   ");
    scanf(" %d", &opcaoH);
    switch(opcaoH){ // Escolher o horario da sessao
    case 1:
        strcpy(sessao, "Manha (9:00)");
        break;
    case 2:
        strcpy(sessao, "Tarde (13:00)");
        break;
    case 3:
        strcpy(sessao, "Noite (17:00)");
        break;
    }

    linhaCol(27,60);
    printf("[5] Cancelar");
    linhaCol(27,40);
    printf("[1] Confirmar ");
    linhaCol(27,25);
    printf("Escolha: ");
    scanf("%d", &opcao);

    switch(opcao){ // Confirmar compra ou cancelar
    case 1:
        system("cls");
        VendaConfirm(pf, q, &valorTotal, sessao);
        break;
    case 5:
        system("cls");
        Home(pf);
        break;
    }
}
void VendaConfirm(FILE *pf, int q, float *valorTotal, char sessao[]){
    int opcaoPag;
    float valorT = *valorTotal;

    for(int c = 1; c <= q; c++){

        system("cls");
        boxMenu();
        box(10,20,28,105);
        linhaCol(12,25);
        printf("Confirmacao de Pagamento");
        box(15,25,17,65);

        box(19,25,21,65);

        box(23,25,25,65);

        linhaCol(12,67);
        printf("Forma de Pagamento: ");
        box(15,67,25,100);
        linhaCol(17,70);
        printf("1 - Dinheiro");
        linhaCol(19,70);
        printf("2 - Cartao de Debito");
        linhaCol(21,70);
        printf("3 - Cartao de Credito");
        linhaCol(23,70);
        printf("4 - Cancelar");

        fflush(stdin);
        linhaCol(16,27);
        printf("Nome Completo: ");
        fgets(dadosIng[numIng].nomeComp, sizeof(dadosIng[numIng].nomeComp), stdin);
        dadosIng[numIng].nomeComp[strcspn(dadosIng[numIng].nomeComp, "\n")] = '\0';

        linhaCol(20,27);
        printf("CPF: ");
        fgets(dadosIng[numIng].cpfComp, sizeof(dadosIng[numIng].cpfComp), stdin);
        dadosIng[numIng].cpfComp[strcspn(dadosIng[numIng].cpfComp, "\n")] = '\0';

        linhaCol(24,27);
        printf("E-mail: ");
        fflush(stdin);
        fgets(dadosIng[numIng].emailComp, sizeof(dadosIng[numIng].emailComp), stdin);
        dadosIng[numIng].emailComp[strcspn(dadosIng[numIng].emailComp, "\n")] = '\0';

        linhaCol(12,87);
        scanf("%d", &opcaoPag);
        switch(opcaoPag){
        case 1:
            strcpy(dadosIng[numIng].tipoPag, "Dinheiro");
            break;

        case 2:
            strcpy(dadosIng[numIng].tipoPag, "Cartao de Debito");
            break;

        case 3:
            strcpy(dadosIng[numIng].tipoPag, "Cartao de Credito");
            break;

        case 4:
            system("cls");
            Home(pf);
            break;
        default:
            system("cls");
            printf("Opcao Invalida!");
            VendaConfirm(pf, q, &valorTotal, sessao);
            break;
        }
        srand((unsigned)time(NULL));
        dadosIng[numIng].token = rand()%1000;
        strcpy(dadosIng[numIng].horario, sessao); // passando o valor (string) do array sessao para o array horario

        numIng++;
    }
    Ingresso(q,&valorT, pf);
}
void Ingresso(int q,float *vTotal, FILE *pf){

    for(int c = 1; c <= q; c++){

        system("cls");
        boxMenu();
        box(10,20,28,105);
        linhaCol(12,55);
        printf("Ingresso %d", c);
        linhaCol(14,30);
        printf("Nome: %s", dadosIng[numIng-c].nomeComp);
        linhaCol(16,30);
        printf("CPF: %s", dadosIng[numIng-c].cpfComp);
        linhaCol(18,30);
        printf("E-mail: %s", dadosIng[numIng-c].emailComp);
        linhaCol(20,30);
        printf("Forma de Pagamento: %s", dadosIng[numIng-c].tipoPag);
        linhaCol(22,30);
        printf("Sessao: %s", dadosIng[numIng-c].horario);
        linhaCol(24,30);
        printf("Codigo: %d", dadosIng[numIng-c].token);
        linhaCol(14,70);
        printf("Total Ingressos Gerados: %d", numIng);
        linhaCol(27,30);
        system("pause");
    }

    system("cls");
    Home(pf);

}
void ValIng(FILE *pf){ // Validação do ticket

    int opcao, cod, ingOk = 0, ingValid = 1;
    int ingUsados[MAX_CAD];

    boxMenu();
    box(10,20,28,105);
    linhaCol(12,30);
    printf("Validar Ingresso");
    linhaCol(14,30);
    printf("Digite o codigo do Ingresso: ");
    scanf("%d", &cod);


    // verificar se codigo inserido é valido
    for(int i = 0; i < numIng; i++){
        if(dadosIng[i].token == cod){
            ingOk = 1;
            break;
        }

    }
    if(ingOk != 1){
        linhaCol(19,30);
        printf("Ingresso Invalido!");
        linhaCol(27,30);
        system("pause");
    }

    // verificar se codigo já foi usado
    for(int i = 0; i < numIng; i++){
        if(cod == ingUsados[i]){

            linhaCol(12,70);
            printf("Ingresso já usado!");
            linhaCol(27,30);
            system("pause");
            system("cls");
            ValIng(pf);
            break;
        }
        else{
            ingValid = 1;
        }
    }

    ingUsados[numIng_used] == cod;
    numIng_used++;


    if(ingOk == 1 && ingValid == 1){
        linhaCol(19,30);
        printf("Ingresso Aprovado!");
        linhaCol(21,30);
        printf("Tenha um otimo passeio!");
    }

    // validar outro ingresso ou sair
    linhaCol(25,70);
    printf("Outro Ingresso [1]");
    linhaCol(25,90);
    printf("Sair [5]");
    linhaCol(25,30);
    printf("Digite para continuar ou sair: ");
    scanf("%d", &opcao);

    switch(opcao){
    case 1:
        system("cls");
        ValIng(pf);
        break;
    case 5:
        system("cls");
        Home(pf);
    }

}
// -----------------------------------------------------------------  Tela Fale Conosco  ------------------------------------------------------------
void FaleConosco(){

    boxMenu();//Cabeçalho
    linhaCol(15,23);// posicionar printf
    printf("Fale Conosco\n");// exibir ao usuario o conteudo da tela selecionada
    linhaCol(17,23);// posicionar printf
    printf("Sugestoes, reclamacoes e duvidas:\n");
    linhaCol(18,23);// posicionar printf
    printf("mail:faleconosco@museualanturing.org.br\n");

    linhaCol(20,23);// posicionar printf
    printf("Endereco: Av Conceicao, s/n\n");
    linhaCol(21,23);// posicionar printf
    printf("Pq Dom Pedro III, Centro, Sao Paulo - SP\n");
    linhaCol(23,23);// posicionar printf
    printf("Estacionamento no local\n");

    linhaCol(25,23);// posicionar printf
    printf("11 3315 0051 ou 11 96392 1393\n");
    linhaCol(26,23);// posicionar printf
    printf("(WhatsApp) das 10h as 16h.\n");


}

// -----------------------------------------------------------------  Ecolha tipo de Login  ------------------------------------------------------------
void LoginTipo(FILE *pf){
    int opcaoLogin, i;

    boxMenu();// cabeçalho principal
    box(10,20,28,105);
    linhaCol(13,33);//posição
    printf("1 - Login Cliente    2 - Login Funcionario   3 - Cadastrar-se\n");// exibição na tela
    box(16,28,22,97);// borda da caixa
    linhaCol(24,28);
    printf("Ainda nao possui um cadastro? digite [3]\t\t\t");
    printf("Voltar[4]\n");
    linhaCol(18,30);//posicionar
    printf("Qual login deseja fazer: ");//exibir mensagem na tela
    scanf("%d", &opcaoLogin);

    switch(opcaoLogin){
    case 1:
        system("cls");
        LoginCliente(pf);
        break;

    case 2:
        system("cls");
        LoginFunc(pf);
        break;

    case 3: // Ao selecionar 3 usuario eh direcionado para se cadastrar e apos eh direcionado para login
        system("cls");
        CadastroCliente(pf);
        break;

    case 4:
        system("cls");
        Home(pf);
        break;

    default:
        linhaCol(20,30);
        printf("Opcao Invalida!\n");
        system("cls");
        LoginTipo(pf);
        break;
    }

}

// -----------------------------------------------------------------  Tela de Login e Cadastro Func  ------------------------------------------------------------
void LoginFunc(FILE *pf){
    int senhaOk, userOk; // var para verificação da senha (true ou false)
    char usuarioValid[50], senhaValid[50];
    char usuarioFunc[50], senhaFunc[50];
    strcpy(usuarioFunc, "Funcionario");
    strcpy(senhaFunc, "alanTuring@2023");

    boxMenu();// menu principal
    linhaCol(11,28);//posição
    printf("Acesso Funcionario: \n");// exibição na tela
    box(13,28,19,97);// borda da caixa
    linhaCol(22,77);
    printf("Digite 0 para Voltar");
    linhaCol(15,30);//posicionar
    printf("Nome do Usuario: ");//exibir mensagem na tela
    fflush(stdin);// Descarte os caracteres indesejados
    scanf("%[^\n]s", &usuarioValid);//irá ler uma linha inteira de texto até que uma quebra de linha seja encontrada.
    if(usuarioValid[0] == '0'){ // caso for digitado '0' em Nome de usuario e apertado enter, voltará para a tela anterior
        system("cls");
        LoginTipo(pf);
    }
    // validando usuario
    if(strcmp(usuarioValid, usuarioFunc) == 0){
        userOk = 1;
    }
    fflush(stdin);
    linhaCol(17,30);// posição do print
    printf("Senha: ");//exibir na tela
    gets(senhaValid);// receber o valor declarado a variavel senhaValid

    // validação senha
    //comparando a string senhaValid com as senhas cadastradas
    if(strcmp(senhaValid, senhaFunc) == 0){
        senhaOk = 1;
    }

    if(senhaOk == 1 && userOk == 1){
        system("cls");
        // o parametro userValid[] da funcao cadastroFunc recebe o valor de usuarioValid
        TelaFunc(pf, usuarioValid, dadosIng);

    }
    else{
        linhaCol(22,29);
        printf("Usuario ou Senha Invalido(a)!\n");
        linhaCol(24,29);
        system("pause");
        system("cls");
        LoginFunc(pf);
    }
}
void TelaFunc(FILE *pf, char userFunc[], dadosVenda dadosIng[]){// tela do funcionario

    int opcao, opcaoAlt, opcaoExcluir, i, quant, indiceCad; // variaveis de opções

        while(opcao != 7){

            system("cls");
            boxMenu();
            linhaCol(12,57);
            printf("Perfil Funcionario\n");
            box(10,20,28,105);
            linhaCol(15,30);
            printf("1- Cadastrar Cliente\n");
            linhaCol(17,30);
            printf("2- Consultar Cadastro\n");
            linhaCol(19,30);
            printf("3- Alterar\n");
            linhaCol(21,30);
            printf("4- Excluir\n");
            linhaCol(23,30);
            printf("5- Validar Ingresso\n");
            linhaCol(25,30);
            printf("6- Sair\n");
            linhaCol(27,30);
            printf("Qual Opcao Voce Deseja Acessar, %s? ", userFunc);
            scanf("%d", &opcao);

            switch(opcao){

            case 1:
                system("cls");
                boxMenu();
                box(13,28,19,97);
                linhaCol(16,43);
                printf("Quantos Cadastros Voce Deseja Realizar? ");
                scanf("%d", &quant);

                if(numCad < MAX_CAD){
                    for(i = 1; i<=quant; i++){
                        system("cls");
                        boxMenu();
                        linhaCol(12,52);
                        printf("Iniciar Cadastro - %d\n", i);
                        box(10,20,28,105);
                        linhaCol(15,30);
                        printf("Nome: ");
                        fflush(stdin);
                        fgets(CadC[numCad].nome, sizeof(CadC[numCad].nome), stdin);
                        CadC[numCad].nome[strcspn(CadC[numCad].nome, "\n")] = '\0';
                        linhaCol(17,30);
                        printf("Telefone: ");
                        fflush(stdin);
                        fgets(CadC[numCad].telefone, sizeof(CadC[numCad].telefone), stdin);
                        CadC[numCad].telefone[strcspn(CadC[numCad].telefone, "\n")] = '\0';
                        linhaCol(19,30);
                        printf("CPF: ");
                        fflush(stdin);
                        fgets(CadC[numCad].cpf, sizeof(CadC[numCad].cpf), stdin);
                        CadC[numCad].cpf[strcspn(CadC[numCad].cpf, "\n")] = '\0';
                        linhaCol(21,30);
                        printf("Endereco completo: ");
                        fflush(stdin);
                        fgets(CadC[numCad].ender, sizeof(CadC[numCad].ender), stdin);
                        CadC[numCad].ender[strcspn(CadC[numCad].ender, "\n")] = '\0';
                        linhaCol(23,30);
                        printf("E-mail: ");
                        fflush(stdin);
                        fgets(CadC[numCad].email, sizeof(CadC[numCad].email), stdin);
                        CadC[numCad].email[strcspn(CadC[numCad].email, "\n")] = '\0';
                        linhaCol(25,30);
                        printf("Senha: ");
                        fgets(CadC[numCad].senhaCliente, sizeof(CadC[numCad].senhaCliente), stdin);
                        CadC[numCad].senhaCliente[strcspn(CadC[numCad].senhaCliente, "\n")] = '\0';
                        linhaCol(27, 30);
                        printf("\nCadastro Concluido! ");
                        linhaCol(27,30);
                        system("pause");
                        numCad++;
                    }
                    pf = fopen("dadosC.csv", "w"); // salvando cadastro no arquivo
                    if(pf != NULL){
                        salvarCad(pf);
                        fclose(pf);
                    }
                    else{
                        printf("Erro ao salvar cadastro!");
                    }
                }
                else{
                    printf("Maximo de Cadastro atingido!");
                }
                break;

            case 2:
                system("cls");
                boxMenu();
                box(10,20,28,105);
                linhaCol(12,44);
                printf("Exibir Cadastro\n");
                linhaCol(19,30);
                printf("[Digite o numero do cadastro]");
                linhaCol(19,70);
                printf("[Total de Cadastros Feitos: %d]", numCad);
                linhaCol(15,30);
                printf("Qual Cadastro deseja acessar: ");
                scanf("%d", &indiceCad);

                if(indiceCad > 0 && indiceCad <= numCad){
                    system("cls");
                    boxMenu();
                    box(10,20,28,105);
                    linhaCol(12,44);
                    printf("Exibindo Cadastro - Cliente %d\n", indiceCad);
                    box(10,20,28,105);
                    linhaCol(15,30);
                    printf("Nome: %s\n", CadC[indiceCad-1].nome);
                    linhaCol(17,30);
                    printf("Telefone: %s\n", CadC[indiceCad-1].telefone);
                    linhaCol(19,30);
                    printf("CPF: %s\n", CadC[indiceCad-1].cpf);
                    linhaCol(21,30);
                    printf("Endereco: %s\n", CadC[indiceCad-1].ender);
                    linhaCol(23,30);
                    printf("E-mail: %s\n", CadC[indiceCad-1].email);
                    /*linhaCol(25,30);
                    printf("Senha: %s\n", CadC[i].senhaFunc);*/
                    linhaCol(27,30);
                    system("pause");
                }
                else{
                    system("cls");
                    boxMenu();
                    box(10,20,28,105);
                    linhaCol(12,44);
                    printf("Exibindo Cadastro");
                    linhaCol(15,30);
                    printf("Cadastro não encontrado!");
                    linhaCol(27,30);
                    system("pause");
                    system("cls");
                    TelaFunc(pf, userFunc, dadosIng);
                }
                break;

            case 3:
                system("cls");
                boxMenu();
                box(10,20,28,105);
                linhaCol(12,44);
                printf("Alterar Cadastro\n");
                linhaCol(19,30);
                printf("[Digite o numero do cadastro]");
                linhaCol(19,70);
                printf("[Total de Cadastros Feitos: %d]", numCad);
                linhaCol(15,30);
                printf("Qual Cadastro deseja alterar: ");
                scanf("%d", &indiceCad);

                    system("cls");
                    boxMenu();
                    linhaCol(12,44);
                    printf("Alterar Cadastro - Cliente %d\n", indiceCad);
                    box(10,20,28,105);
                    linhaCol(15,30);
                    printf("1-Nome\n");
                    linhaCol(17,30);
                    printf("2-Telefone\n");
                    linhaCol(19,30);
                    printf("3-CPF\n");
                    linhaCol(21,30);
                    printf("4-Endereco\n");
                    linhaCol(23,30);
                    printf("5-Email\n");
                    linhaCol(26,30);
                    printf("Qual Opcao Voce Deseja Acessar? \n");
                    scanf("%d", &opcaoAlt);

                    switch(opcaoAlt){
                    case 1:
                        system("cls");
                        boxMenu();
                        linhaCol(12,44);
                        printf("Alterar Cadastro - Cliente %d\n",indiceCad);
                        box(10,20,28,105);
                        linhaCol(15,30);
                        printf("Alterar Nome do Cliente: ");
                        fflush(stdin);
                        fgets(CadC[indiceCad-1].nome, sizeof(CadC[indiceCad-1].nome), stdin);
                        CadC[indiceCad-1].nome[strcspn(CadC[indiceCad-1].nome, "\n")] = '\0';
                        linhaCol(17,30);
                        printf("Novo Nome do Cliente: %s\n", CadC[indiceCad-1].nome);

                        pf = fopen("dadosC.csv", "w"); // salvando cadastro no arquivo
                        if(pf != NULL){
                            salvarCad(pf);
                            fclose(pf);
                        }
                        else{
                            printf("Erro ao salvar cadastro!");
                        }
                        linhaCol(26,30);
                        system("pause");

                        break;
                    case 2:
                        system("cls");
                        boxMenu();
                        linhaCol(12,44);
                        printf("Alterar Cadastro - Cliente %d\n",indiceCad);
                        box(10,20,28,105);
                        linhaCol(15,30);
                        printf("Alterar Telefone do Cliente: ");
                        fgets(CadC[indiceCad-1].telefone, sizeof(CadC[indiceCad-1].telefone), stdin);
                        CadC[indiceCad-1].telefone[strcspn(CadC[indiceCad-1].telefone, "\n")] = '\0';
                        linhaCol(17,30);
                        printf("Novo Telefone do Cliente: %s\n", CadC[indiceCad-1].telefone);

                        pf = fopen("dadosC.csv", "w"); // salvando cadastro no arquivo
                        if(pf != NULL){
                            salvarCad(pf);
                            fclose(pf);
                        }
                        else{
                            printf("Erro ao salvar cadastro!");
                        }
                        linhaCol(26,30);
                        system("pause");

                        break;
                    case 3:
                        system("cls");
                        boxMenu();
                        linhaCol(12,44);
                        printf("Alterar Cadastro - Cliente %d\n",indiceCad);
                        box(10,20,28,105);
                        linhaCol(15,30);
                        printf("Alterar CPF do Cliente: ");
                        fgets(CadC[indiceCad-1].cpf, sizeof(CadC[indiceCad-1].cpf), stdin);
                        CadC[indiceCad-1].cpf[strcspn(CadC[indiceCad-1].cpf, "\n")] = '\0';
                        linhaCol(17,30);
                        printf("Novo CPF do Cliente: %s\n\n\t\t", CadC[indiceCad-1].cpf);

                        pf = fopen("dadosC.csv", "w"); // salvando cadastro no arquivo
                        if(pf != NULL){
                            salvarCad(pf);
                            fclose(pf);
                        }
                        else{
                            printf("Erro ao salvar cadastro!");
                        }
                        linhaCol(26,30);
                        system("pause");

                        break;
                    case 4:
                        system("cls");
                        boxMenu();
                        linhaCol(12,44);
                        printf("Alterar Cadastro - Cliente %d\n",indiceCad);
                        box(10,20,28,105);
                        linhaCol(15,30);
                        printf("Alterar Endereço do Cliente: ");
                        fgets(CadC[indiceCad-1].ender, sizeof(CadC[indiceCad-1].ender), stdin);
                        CadC[indiceCad-1].ender[strcspn(CadC[indiceCad-1].ender, "\n")] = '\0';
                        linhaCol(17,30);
                        printf("Novo Endereco do Cliente: %s\n\n\t\t", CadC[indiceCad-1].ender);

                        pf = fopen("dadosC.csv", "w"); // salvando cadastro no arquivo
                        if(pf != NULL){
                            salvarCad(pf);
                            fclose(pf);
                        }
                        else{
                            printf("Erro ao salvar cadastro!");
                        }
                        linhaCol(26,30);
                        system("pause");

                        break;
                    case 5:
                        system("cls");
                        boxMenu();
                        linhaCol(12,44);
                        printf("Alterar Cadastro - Cliente%d\n",indiceCad);
                        box(10,20,28,105);
                        linhaCol(15,30);
                        printf("E-mail do Cliente: ");
                        fgets(CadC[indiceCad-1].email, sizeof(CadC[indiceCad-1].email), stdin);
                        CadC[indiceCad-1].email[strcspn(CadC[indiceCad-1].email, "\n")] = '\0';
                        linhaCol(17,30);
                        printf("Novo E-mail do Cliente: %s\n", CadC[indiceCad-1].email);

                        pf = fopen("dadosC.csv", "w"); // salvando cadastro no arquivo
                        if(pf != NULL){
                            salvarCad(pf);
                            fclose(pf);
                        }
                        else{
                            printf("Erro ao salvar cadastro!");
                        }
                        linhaCol(26,30);
                        system("pause");

                        break;
                    }

                break;

                case 4:
                system("cls");
                boxMenu();
                box(10,20,28,105);
                linhaCol(12,44);
                printf("Excluir Cadastro\n");
                linhaCol(19,30);
                printf("[Digite o numero do cadastro]");
                linhaCol(19,70);
                printf("[Total de Cadastros Feitos: %d]", numCad);
                linhaCol(15,30);
                printf("Qual Cadastro deseja acessar: ");
                scanf("%d", &indiceCad);

                        system("cls");
                        boxMenu();
                        linhaCol(12,44);
                        printf("Excluir Cadastro - Cliente %d\n", indiceCad);
                        box(10,20,28,105);
                        linhaCol(14,30);
                        printf("1-Nome");
                        linhaCol(16,30);
                        printf("2-Telefone");
                        linhaCol(18,30);
                        printf("3-CPF");
                        linhaCol(20,30);
                        printf("4-Endereco");
                        linhaCol(22,30);
                        printf("5-Email");
                        linhaCol(24,30);
                        printf("6-Excluir Todos os Dados\n\n");
                        linhaCol(26,30);
                        printf("Qual Opcao Voce Deseja Excluir? \n");
                        scanf("%d", &opcaoExcluir);

                        switch(opcaoExcluir){

                        case 1:
                            system("cls");
                            boxMenu();
                            box(13,28,19,97);
                            linhaCol(16,43);
                            // menset serve para excluir os dados declarado, após a excluir o sizeof permite inserir novamente.
                            memset(&CadC[indiceCad-1].nome,0,sizeof(CadC[indiceCad-1].nome));
                            printf("Nome do Cliente Excluido!\n\n");

                            pf = fopen("dadosC.csv", "w"); // salvando cadastro no arquivo
                            if(pf != NULL){
                                salvarCad(pf);
                                fclose(pf);
                            }
                            else{
                                printf("Erro ao salvar cadastro!");
                            }
                            linhaCol(26,30);
                            system("pause");

                            break;
                        case 2:
                            system("cls");
                            boxMenu();
                            box(13,28,19,97);
                            linhaCol(16,43);
                            // menset serve para excluir os dados declarado, após a excluir o sizeof permite inserir novamente.
                            memset(&CadC[indiceCad-1].telefone,0,sizeof(CadC[indiceCad-1].telefone));
                            printf("Telefone do Cliente Excluido!\n\n");

                            pf = fopen("dadosC.csv", "w"); // salvando cadastro no arquivo
                            if(pf != NULL){
                                salvarCad(pf);
                                fclose(pf);
                            }
                            else{
                                printf("Erro ao salvar cadastro!");
                            }
                            linhaCol(26,30);
                            system("pause");

                            break;
                        case 3:
                            system("cls");
                            boxMenu();
                            box(13,28,19,97);
                            linhaCol(16,43);
                            // menset serve para excluir os dados declarado, após a excluir o sizeof permite inserir novamente.
                            memset(&CadC[indiceCad-1].cpf,0,sizeof(CadC[indiceCad-1].cpf));
                            printf("CPF do Cliente Excluido!\n\n");

                            pf = fopen("dadosC.csv", "w"); // salvando cadastro no arquivo
                            if(pf != NULL){
                                salvarCad(pf);
                                fclose(pf);
                            }
                            else{
                                printf("Erro ao salvar cadastro!");
                            }
                            linhaCol(26,30);
                            system("pause");

                            break;
                        case 4:
                            system("cls");
                            boxMenu();
                            box(13,28,19,97);
                            linhaCol(16,43);
                            // menset serve para excluir os dados declarado, após a excluir o sizeof permite inserir novamente.
                            memset(&CadC[indiceCad-1].ender,0,sizeof(CadC[indiceCad-1].ender));
                            printf("Endereço do Cliente Excluido!\n\n");

                            pf = fopen("dadosC.csv", "w"); // salvando cadastro no arquivo
                            if(pf != NULL){
                                salvarCad(pf);
                                fclose(pf);
                            }
                            else{
                                printf("Erro ao salvar cadastro!");
                            }
                            linhaCol(26,30);
                            system("pause");

                            break;
                        case 5:
                            system("cls");
                            boxMenu();
                            box(13,28,19,97);
                            linhaCol(16,43);
                            // menset serve para excluir os dados declarado, após a excluir o sizeof permite inserir novamente.
                            memset(&CadC[indiceCad-1].email,0,sizeof(CadC[indiceCad-1].email));
                            printf("E-mail do Cliente Excluido!\n\n");

                            pf = fopen("dadosC.csv", "w"); // salvando cadastro no arquivo
                            if(pf != NULL){
                                salvarCad(pf);
                                fclose(pf);
                            }
                            else{
                                printf("Erro ao salvar cadastro!");
                            }
                            linhaCol(26,30);
                            system("pause");

                            break;
                        case 6:

                            system("cls");
                            boxMenu();
                            box(13,28,19,97);
                            linhaCol(16,43);
                            // menset serve para excluir os dados declarado, após a excluir o sizeof permite inserir novamente.
                            memset(&CadC[indiceCad-1].nome,0,sizeof(CadC[indiceCad-1].nome));
                            memset(&CadC[indiceCad-1].telefone,0,sizeof(CadC[indiceCad-1].telefone));
                            memset(&CadC[indiceCad-1].cpf,0,sizeof(CadC[indiceCad-1].cpf));
                            memset(&CadC[indiceCad-1].ender,0,sizeof(CadC[indiceCad-1].ender));
                            memset(&CadC[indiceCad-1].email,0,sizeof(CadC[indiceCad-1].email));

                            printf("Todos os Dados Foram Excluidos!\n\n");

                            pf = fopen("dadosC.csv", "w"); // salvando cadastro no arquivo
                            if(pf != NULL){
                                salvarCad(pf);
                                fclose(pf);
                            }
                            else{
                                printf("Erro ao salvar cadastro!");
                            }
                            linhaCol(26,30);
                            system("pause");

                            break;
                        }

                    break;

                case 5:
                    system("cls");
                    ValIng(pf);
                    break;

                case 6:
                    system("cls");
                    Home(pf);
                    break;

                default:
                    system("cls");
                    TelaFunc(pf, userFunc, dadosIng);
                    break;
            }
        }
}

// -----------------------------------------------------------------  Tela de Login e Cadastro de Cliente ------------------------------------------------------------
void LoginCliente(FILE *pf){// tela de login do cliente

    int senhaOk = 0, userOk = 0,indiceCad; //senhaCliente = 123456;
    char usuarioValid[50], senhaValid[50]; //variavel para validar a senha no login

    boxMenu();// menu principal
    linhaCol(11,28);//posição
    printf(" Acesso Cliente: \n");// exibição na tela
    box(13,28,19,97);// borda da caixa
    linhaCol(22,77);
    printf("Digite 0 para Voltar");
    linhaCol(15,30);//posicionar
    printf("Nome do Usuario: ");//exibir mensagem na tela
    fflush(stdin);// Descarte os caracteres indesejados
    fgets(usuarioValid, sizeof(usuarioValid), stdin);//irá ler uma linha inteira de texto até que uma quebra de linha seja encontrada.
    usuarioValid[strcspn(usuarioValid, "\n")] = '\0';
    if(usuarioValid[0] == '0'){ // caso for digitado '0' em Nome de usuario e apertado enter, voltará para a tela anterior
        system("cls");
        LoginTipo(pf);
    }
    fflush(stdin);
    linhaCol(17,30);// posicionar
    printf("Senha: ");//exibir na tela
    fgets(senhaValid, sizeof(senhaValid), stdin);
    senhaValid[strcspn(senhaValid, "\n")] = '\0';


    pf = fopen("dadosC.csv", "r");
    if(pf != NULL){
        lerCad(pf);
        fclose(pf);
    }
    else{
        printf("Erro ao ler arquivo!");
    }
    // validação senha
    for(int i = 0; i < numCad; i++){
        //comparando a string senhaValid e a usuarioValid com as senhas e o nomes cadastrados
        if(strcmp(CadC[i].nome, usuarioValid) == 0 && strcmp(CadC[i].senhaCliente, senhaValid) == 0){
            userOk = 1;
            senhaOk = 1;
            indiceCad = i; //indiceCad recebe o valor equivalente ao indice do cadastro logado
            break;
        }
    }

    if(senhaOk == 1 && userOk == 1){
        system("cls");
        // o parametro userValid[] da funcao cadastroCliente receber o valor de usuarioValid
        TelaCliente(pf, usuarioValid, indiceCad);

    }
    else{
        linhaCol(22,29);
        printf("Usuario ou Senha Invalido(a)!\n");
        linhaCol(24,29);
        system("pause");
        system("cls");
        LoginCliente(pf);
    }

}
void CadastroCliente(FILE *pf){// tela de cadastro do cliente

    boxMenu();
    linhaCol(12,52);
    printf("Iniciar Cadastro\n" );
    box(10,20,28,105);
    if(numCad < MAX_CAD){
        linhaCol(15,30);
        printf("Nome: ");
        fflush(stdin);
        fgets(CadC[numCad].nome, sizeof(CadC[numCad].nome), stdin);
        CadC[numCad].nome[strcspn(CadC[numCad].nome, "\n")] = '\0'; // Para remover a quebra de linha
        linhaCol(17,30);
        printf("Telefone: ");
        fflush(stdin);
        scanf("%[^\n]s",&CadC[numCad].telefone);
        linhaCol(19,30);
        printf("CPF: ");
        fflush(stdin);
        scanf("%[^\n]s",&CadC[numCad].cpf);
        linhaCol(21,30);
        printf("Endereco completo: ");
        fflush(stdin);
        fgets(CadC[numCad].ender, sizeof(CadC[numCad].ender), stdin);
        CadC[numCad].ender[strcspn(CadC[numCad].ender, "\n")] = '\0';
        linhaCol(23,30);
        printf("E-mail: ");
        fflush(stdin);
        fgets(CadC[numCad].email, sizeof(CadC[numCad].email), stdin);
        CadC[numCad].email[strcspn(CadC[numCad].email, "\n")] = '\0';
        linhaCol(25, 30);
        printf("Criar Senha: ");
        fflush(stdin);
        fgets(CadC[numCad].senhaCliente, sizeof(CadC[numCad].senhaCliente), stdin);
        CadC[numCad].senhaCliente[strcspn(CadC[numCad].senhaCliente, "\n")] = '\0';
        numCad++;

        pf = fopen("dadosC.csv", "w"); // salvando cadastro no arquivo
        if(pf != NULL){
            salvarCad(pf);
            fclose(pf);
        }
        else{
            printf("Erro ao salvar cadastro!");
        }
    }
    else{
        printf("Maximo de Cadastro atingido!");
    }

    linhaCol(27,30);
    system("pause");
    system("cls");
    LoginCliente(pf);

}
void TelaCliente(FILE *pf, char userValid[], int indiceCad){// tela do cliente

    int opcao, opcaoAlt, opcaoExcluir, i;// quant;
    userValid[50];

            do{
                system("cls");
                boxMenu();
                linhaCol(12,57);
                printf("Perfil Cliente\n");
                box(10,20,28,105);
                linhaCol(15,30);
                printf("1- Exibir Dados\n");
                linhaCol(17,30);
                printf("2- Alterar\n");
                linhaCol(19,30);
                printf("3- Comprar Ingressos\n");
                linhaCol(21,30);
                printf("4- Sair\n");
                linhaCol(26,30);
                printf("Qual Opcao Deseja Acessar, %s? ", userValid);
                scanf("%d", &opcao);

                switch(opcao){

                case 0:
                    system("cls");
                    boxMenu();
                    box(13,28,19,97);
                    CadastroCliente(pf);
                    break;

                case 1: //exibir
                    system("cls");
                    boxMenu();
                    linhaCol(12,44);
                    printf("Exibindo Cadastro - Cliente\n", numCad);
                    box(10,20,28,105);
                    linhaCol(15,30);
                    printf("Nome: %s\n", CadC[indiceCad].nome);
                    linhaCol(17,30);
                    printf("Telefone: %s\n", CadC[indiceCad].telefone);
                    linhaCol(19,30);
                    printf("CPF: %s\n", CadC[indiceCad].cpf);
                    linhaCol(21,30);
                    printf("Endereco: %s\n", CadC[indiceCad].ender);
                    linhaCol(23,30);
                    printf("E-mail: %s\n", CadC[indiceCad].email);
                    linhaCol(26,30);
                    system("pause");

                    break;

                case 2: //alterar
                    system("cls");
                        boxMenu();
                        linhaCol(12,44);
                        printf("Alterar Cadastro - Cliente\n", numCad);
                        box(10,20,28,105);
                        linhaCol(15,30);
                        printf("1- Nome\n");
                        linhaCol(17,30);
                        printf("2- Telefone\n");
                        linhaCol(19,30);
                        printf("3-CPF\n");
                        linhaCol(21,30);
                        printf("4- Endereco\n");
                        linhaCol(23,30);
                        printf("5- Email\n");
                        linhaCol(26,30);
                        printf("Qual Opcao Voce Deseja Acessar? ");
                        scanf("%d", &opcaoAlt);

                        switch(opcaoAlt){
                        case 1:
                                system("cls");
                                boxMenu();
                                linhaCol(12,44);
                                printf("Alterar Cadastro - Cliente\n",numCad);
                                box(10,20,28,105);
                                linhaCol(15,30);
                                printf("Alterar Nome: ");
                                fflush(stdin);
                                fgets(CadC[indiceCad].nome, sizeof(CadC[indiceCad].nome), stdin);
                                CadC[indiceCad].nome[strcspn(CadC[indiceCad].nome, "\n")] = '\0';
                                linhaCol(17,30);
                                printf("Novo Nome: %s\n", CadC[indiceCad].nome);

                                pf = fopen("dadosC.csv", "w"); // salvando cadastro no arquivo
                                if(pf != NULL){
                                    salvarCad(pf);
                                    fclose(pf);
                                }
                                else{
                                    printf("Erro ao salvar cadastro!");
                                }
                                linhaCol(26,30);
                                system("pause");

                            break;
                        case 2:
                                system("cls");
                                boxMenu();
                                linhaCol(12,44);
                                printf("Alterar Cadastro - Cliente\n",numCad);
                                box(10,20,28,105);
                                linhaCol(15,30);
                                printf("Alterar Telefone: ");
                                fflush(stdin);
                                fgets(CadC[indiceCad].telefone, sizeof(CadC[indiceCad].telefone), stdin);
                                CadC[indiceCad].telefone[strcspn(CadC[indiceCad].telefone, "\n")] = '\0';
                                linhaCol(17,30);
                                printf("Novo Telefone: %s \n", CadC[indiceCad].telefone);

                                pf = fopen("dadosC.csv", "w"); // salvando cadastro no arquivo
                                if(pf != NULL){
                                    salvarCad(pf);
                                    fclose(pf);
                                }
                                else{
                                    printf("Erro ao salvar cadastro!");
                                }
                                linhaCol(26,30);
                                system("pause");

                            break;
                        case 3:
                                system("cls");
                                boxMenu();
                                linhaCol(12,44);
                                printf("Alterar Cadastro - Cliente\n",numCad);
                                box(10,20,28,105);
                                linhaCol(15,30);
                                printf("Alterar CPF: ");
                                fflush(stdin);
                                fgets(CadC[indiceCad].cpf, sizeof(CadC[indiceCad].cpf), stdin);
                                CadC[indiceCad].cpf[strcspn(CadC[indiceCad].cpf, "\n")] = '\0';
                                linhaCol(17,30);
                                printf("Novo CPF: %s\n\n\t\t", CadC[indiceCad].cpf);

                                pf = fopen("dadosC.csv", "w"); // salvando cadastro no arquivo
                                if(pf != NULL){
                                    salvarCad(pf);
                                    fclose(pf);
                                }
                                else{
                                    printf("Erro ao salvar cadastro!");
                                }
                                linhaCol(26,30);
                                system("pause");

                            break;
                        case 4:
                                system("cls");
                                boxMenu();
                                linhaCol(12,44);
                                printf("Alterar Cadastro - Cliente\n",numCad);
                                box(10,20,28,105);
                                linhaCol(15,30);
                                printf("Alterar Endereço: ");
                                fflush(stdin);
                                fgets(CadC[indiceCad].ender, sizeof(CadC[indiceCad].ender), stdin);
                                CadC[indiceCad].ender[strcspn(CadC[indiceCad].ender, "\n")] = '\0';;
                                linhaCol(17,30);
                                printf("Novo Endereco: %s\n\n\t\t", CadC[indiceCad].ender);

                                pf = fopen("dadosC.csv", "w"); // salvando cadastro no arquivo
                                if(pf != NULL){
                                    salvarCad(pf);
                                    fclose(pf);
                                }
                                else{
                                    printf("Erro ao salvar cadastro!");
                                }
                                linhaCol(26,30);
                                system("pause");

                            break;
                        case 5:
                                system("cls");
                                boxMenu();
                                linhaCol(12,44);
                                printf("Alterar Cadastro - Cliente\n",numCad);
                                box(10,20,28,105);
                                linhaCol(15,30);
                                printf("E-mail: ");
                                fflush(stdin);
                                fgets(CadC[indiceCad].email, sizeof(CadC[indiceCad].email), stdin);
                                CadC[indiceCad].email[strcspn(CadC[indiceCad].email, "\n")] = '\0';
                                linhaCol(17,30);
                                printf("Novo E-mail: %s\n", CadC[indiceCad].email);

                                pf = fopen("dadosC.csv", "w"); // salvando cadastro no arquivo
                                if(pf != NULL){
                                    salvarCad(pf);
                                    fclose(pf);
                                }
                                else{
                                    printf("Erro ao salvar cadastro!");
                                }
                                linhaCol(26,30);
                                system("pause");

                            break;
                        }
                    break;

                case 3:
                    system("cls");
                    Vendas(pf);
                    break;

                case 4:
                    system("cls");
                    Home(pf);
                    break;
                }
            }while(opcao != 6);
}

