// includes...
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>

// objetivo:escolhe dentre as letras do alfabeto ('a'..'z') uma letra aleatoriamente
// parametros: nenhum
// retorno:a letra do alfabeto
char geraAlfabeto()
{
    int i;
    char letras[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

    i = rand() % 26;
    return (letras[i] - 32);
}
// objetivo:escolhe dentre os numeros ('0'..'9') uma numero aleatoriamente
// parametros: nenhum
// retorno:o numero
char geraNumero()
{
    int i;
    char numeros[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

    i = rand() % 9;
    return (numeros[i]);
}
// objetivo:gera aleatoriamente um numero de conta corrente no formato 999.999-X
// parametros: c onde armazera a conta gerada
// retorno:nenhum
void geraContaCorrente(char c[])
{
    // implemente aqui
    char conta[10];

    for (int i = 0; i < 6; i++)
    {
        conta[i] = geraNumero();
    }
    conta[7] = geraAlfabeto();
    sprintf(c, "%.3s.%.3s-%c", conta, conta + 3, conta[7]);
}
// objetivo:insere pontuacoes '.' e '- ' em uma conta corrente
// parametros: conta_origem a conta recebida no formato que o usuario fornecer
//             conta_destino a conta com as pontuacoes inseridas no formato 999.999-X
void insere_pontuacao_conta_corrente(char conta_origem[], char conta_destino[], int *validarConta)
{
    char numeros[9] = {0};
    char dv = '\0';
    int j = 0;
    int k = 0;

    // Verifica se a conta já está no formato correto
    for (int i = 0; i < 3; i++)
    {
        if (!isdigit(conta_origem[k]))
        {
            printf("Conta invalida: os tres primeiros caracteres devem ser numeros.\n");
            validarConta = 0;
            return; // Sai da função se a conta não estiver no formato correto
        }
        k++;
    } // 999999x
    if (conta_origem[k] == '.')
    {
        k++;
    }
    // k = 3
    for (int i = 0; i < 3; i++) // i = 1, 2
    {
        if (!isdigit(conta_origem[k]))
        {
            printf("Conta invalida: os tres ultimos caracteres, antes da letra, devem ser numeros.\n");
            validarConta = 0;
            return; // Sai da função se a conta não estiver no formato correto
        }
        k++; // 4, 5, 6
    }
    if (conta_origem[k] == '-')
    {
        k++;
    }

    if (!isalpha(conta_origem[k]))
    {
        printf("Conta invalida: o ultimo caractere deve ser uma letra.\n");
        validarConta = 0;
        return; // Sai da função se a conta não estiver no formato correto
    }
    *validarConta = 1;
    // implemente aqui

    for (int i = 0; conta_origem[i] != '\0'; i++)
    {
        if (isdigit(conta_origem[i]))
        {
            if (j < 6)
            { // no máximo 6 dígitos para a conta
                numeros[j++] = conta_origem[i];
            }
        }
        else if (isalpha(conta_origem[i]) || conta_origem[i] == 'X' || conta_origem[i] == 'x')
        {
            dv = conta_origem[i]; // guarda o último caractere não numérico como DV
        }
    }

    numeros[j] = '\0';

    if (j == 6)
    {
        sprintf(conta_destino, "%.3s.%.3s-%c", numeros, numeros + 3, toupper(dv));
    }
}

// objetivo:calcula o primeiro digito verificador de um cpf no formato 999999999
// parametros: cpf o cpf sem os digitos verificadores
// retorno: o calculo do primeiro digito verificador
int obtem_primeiro_digito_verificador(char cpf[])
{
    int digito;

    // implemente aqui

    int i = 0, j = 1;
    long long int cpfInteiro[9];
    digito = 0;

    for (i; i <= 8; i++)
    {
        cpfInteiro[i] = cpf[i] - '0'; // transforma o numero de string para inteiro e guarda na variável
        digito += cpfInteiro[i] * j;  // multiplica o digito obtido por seu indice e soma ao resultado total
        j++;
    }

    // divide o total encontrado por 11 e utiliza o resto da divisão como digito verificador
    if ((digito % 11) != 10)
    {
        digito %= 11;
    }
    else if ((digito % 11) == 10)
    {
        digito = 0;
    }

    return (digito);
}
// objetivo:calcula o segundo digito verificador de um cpf no formato 999999999
// parametros: cpf sem os digitos verificadores
// retorno: o calculo do segundo digito verificador
int obtem_segundo_digito_verificador(char cpf[])
{
    int digito;

    // implemente aqui

    // multiplica o primeiro digito verificador pelo seu índice e adiciona ao resultado total
    digito = obtem_primeiro_digito_verificador(cpf) * 9;
    int i = 0;
    long long int cpfInteiro[9];

    for (i; i <= 8; i++)
    {
        cpfInteiro[i] = cpf[i] - '0'; // transforma o numero de string para inteiro e guarda na variável
        digito += cpfInteiro[i] * i;  // multiplica o digito obtido por seu indice e soma ao resultado total
    }

    // divide o total encontrado por 11 e utiliza o resto da divisão como digito verificador
    if ((digito % 11) != 10)
    {
        digito %= 11;
    }
    else if ((digito % 11) == 10)
    {
        digito = 0;
    }

    return (digito);
}
// objetivo:verifica se um cpf no formato 999.999.999-99 e valido
// parametros: cpf a ser verificado
// retorno: 1 se cpf e valido ou 0 se cpf nao e valido
int verifica_cpf_valido(char cpf[])
{
    int valido = 1;

    // implemente aqui

    int i = 0;
    char cpfSemVerificadores[10];

    for (i; i <= 8; i++)
    {
        cpfSemVerificadores[i] = cpf[i]; // adiciona os 9 primeiros digitos do cpf na variável
    }
    cpfSemVerificadores[9] = '\0';

    int primeiroDigito = obtem_primeiro_digito_verificador(cpfSemVerificadores);
    int segundoDigito = obtem_segundo_digito_verificador(cpfSemVerificadores);

    // verifica se o primeiro digito verificador do cpf é válido
    if ((cpf[9] - '0') == primeiroDigito)
    {
        // verifica se o segundo digito verificador do cpf é válido
        if ((cpf[10] - '0') == segundoDigito)
        {
            // caso ambos sejam válidos mantém o valor original da variável
            valido = 1;
        }
        else
        {
            valido = 0;
        }
    }
    else
    {
        valido = 0;
    }

    return (valido);
}
// objetivo:insere pontuacoes '.' e '- ' em um cpf
// parametros: cpf_origem o cpf recebido no format 99999999999
//             cpf_destino o cpf com as pontuacoes inseridas no formato 999.999.999-99

void insere_pontuacao_cpf(char cpf_origem[], char cpf_destino[], int *validarCpf)
{
    char numeros[12] = {0};
    int j = 0;
    int k = 0;

    // implemente aqui
    for (int i = 0; i < 3; i++)
    {
        if (!isdigit(cpf_origem[k]))
        {
            printf("CPF invalido: os tres primeiros caracteres devem ser numeros.\n");
            validarCpf = 0;
            return; // Sai da função se o CPF não estiver no formato correto
        }
        k++;
    }
    if (cpf_origem[k] == '.')
    {
        k++;
    }

    for (int i = 0; i < 3; i++)
    {
        if (!isdigit(cpf_origem[k]))
        {
            printf("CPF invalido: os tres seguintes caracteres devem ser numeros.\n");
            validarCpf = 0;
            return; // Sai da função se o CPF não estiver no formato correto
        }
        k++;
    }
    if (cpf_origem[k] == '.')
    {
        k++;
    }

    for (int i = 0; i < 3; i++)
    {
        if (!isdigit(cpf_origem[k]))
        {
            printf("CPF invalido: os tres seguintes caracteres devem ser numeros.\n");
            validarCpf = 0;
            return; // Sai da função se o CPF não estiver no formato correto
        }
        k++;
    }
    if (cpf_origem[k] == '-')
    {
        k++;
    }

    for (int i = 0; i < 2; i++)
    {
        if (!isdigit(cpf_origem[k]))
        {
            printf("CPF invalido: os dois ultimos caracteres devem ser numeros.\n");
            validarCpf = 0;
            return; // Sai da função se o CPF não estiver no formato correto
        }
        k++;
    }

    for (int i = 0; cpf_origem[i] != '\0'; i++)
    {
        if (isdigit(cpf_origem[i]))
        {
            if (j < 11)
            { // garantir no máximo 11 dígitos
                numeros[j++] = cpf_origem[i];
            }
        }
    }
    numeros[j] = '\0';

    char cpf[12];

    for (int i = 0; i < 12; i++)
    {
        cpf[i] = numeros[i];
    }

    verifica_cpf_valido(cpf);

    if (j == 11)
    {
        sprintf(cpf_destino, "%.3s.%.3s.%.3s-%.2s", numeros, numeros + 3, numeros + 6, numeros + 9);
    }
    *validarCpf = 1;
}
// objetivo:gera aleatoriamente um cpf valido no formato 999.999.999-99
// parametros: cpf onde sera armazenado o cpf valido
// retorno: nenhum

void gera_cpf_valido(char cpf[])
{
    // implemente aqui
    char cpf_origem[12];
    int cpf_valido = 0;
    int validarCpf = 1;

    // repete a criação do cpf até que ele seja válido
    do
    {
        for (int i = 0; i < 11; i++)
        {
            cpf_origem[i] = geraNumero();
        }
        cpf_origem[11] = '\0';

        // verifica se o cpf gerado e valido
        cpf_valido = verifica_cpf_valido(cpf_origem);

    } while (cpf_valido == 0);

    char cpf_destino[15];
    insere_pontuacao_cpf(cpf_origem, cpf_destino, &validarCpf);

    strcpy(cpf, cpf_destino);
}
// objetivo: receber um numero e devolver este numero por extenso(escrito)
// paramentros: numero a ser escrito
// return void
void gera_valor_por_extenso(int valorPorExtenso)
{
    // implemente aqui
    int unidade = 0, dezena = 0, centena = 0, milhar = 0, dezenaDeMilhar = 0, centenaDeMilhar = 0;
    if (valorPorExtenso > 0)
    {
        unidade = valorPorExtenso % 10;
    }
    if (valorPorExtenso > 9)
    {
        dezena = (valorPorExtenso % 100) / 10;
    }
    if (valorPorExtenso > 99)
    {
        centena = (valorPorExtenso % 1000) / 100;
    }
    if (valorPorExtenso > 999)
    {
        milhar = (valorPorExtenso % 10000) / 1000;
    }
    if (valorPorExtenso > 9999)
    {
        dezenaDeMilhar = (valorPorExtenso % 100000) / 10000;
    }
    if (valorPorExtenso > 99999)
    {
        centenaDeMilhar = (valorPorExtenso % 1000000) / 100000;
    }

    if (centenaDeMilhar > 0)
    {
        switch (centenaDeMilhar)
        {
        case 1:
            if (dezenaDeMilhar > 0 || milhar > 0)
            {
                printf("Cento");
                break;
            }
            printf("Cem");
            break;
        case 2:
            printf("Duzentos");
            break;
        case 3:
            printf("Trezentos");
            break;
        }
    }
    if (centenaDeMilhar > 0)
    {
        printf(" e ");
    }
    if (dezenaDeMilhar > 0)
    {
        switch (dezenaDeMilhar)
        {
        case 1:
            switch (milhar)
            {
            case 0:
                printf("dez");
                break;
            case 1:
                printf("onze");
                break;
            case 2:
                printf("doze");
                break;
            case 3:
                printf("treze");
                break;
            case 4:
                printf("quatorze");
                break;
            case 5:
                printf("quinze");
                break;
            case 6:
                printf("dezesseis");
                break;
            case 7:
                printf("dezessete");
                break;
            case 8:
                printf("dezoito");
                break;
            case 9:
                printf("dezenove");
                break;
            }
            break;
        case 2:
            printf("vinte");
            break;
        case 3:
            printf("trinta");
            break;
        case 4:
            printf("quarenta");
            break;
        case 5:
            printf("cinquenta");
            break;
        case 6:
            printf("sessenta");
            break;
        case 7:
            printf("setenta");
            break;
        case 8:
            printf("oitenta");
            break;
        case 9:
            printf("noventa");
            break;
        }
    }
    if (milhar > 0 && dezenaDeMilhar != 1)
    {
        if (dezenaDeMilhar > 1)
        {
            printf(" e ");
        }
        switch (milhar)
        {
        case 1:
            if (centenaDeMilhar > 0 || dezenaDeMilhar > 0)
            {
                printf("um");
            }
            break;
        case 2:
            printf("dois");
            break;
        case 3:
            printf("tres");
            break;
        case 4:
            printf("quatro");
            break;
        case 5:
            printf("cinco");
            break;
        case 6:
            printf("seis");
            break;
        case 7:
            printf("sete");
            break;
        case 8:
            printf("oito");
            break;
        case 9:
            printf("nove");
            break;
        }
    }
    if (centenaDeMilhar > 0 || dezenaDeMilhar > 0 || milhar > 0)
    {
        printf(" mil ");
    }
    if ((centena > 0 || dezena > 0 || unidade > 0) && (centenaDeMilhar > 0 || dezenaDeMilhar > 0) && milhar == 0)
    {
        printf("e ");
    }
    if ((centenaDeMilhar > 0 || dezenaDeMilhar > 0 || milhar > 0) && centena > 1 && dezena == 0 && unidade == 0)
    {
        printf("e ");
    }

    if (centena > 0)
    {
        switch (centena)
        {
        case 1:
            if (dezena > 0 || unidade > 0)
            {
                printf("cento");
                break;
            }
            printf("cem");
            break;
        case 2:
            printf("duzentos");
            break;
        case 3:
            printf("trezentos");
            break;
        case 4:
            printf("quatrocentos");
            break;
        case 5:
            printf("quinhentos");
            break;
        case 6:
            printf("seiscentos");
            break;
        case 7:
            printf("setecentos");
            break;
        case 8:
            printf("oitocentos");
            break;
        case 9:
            printf("novecentos");
            break;
        }
    }
    if (dezena > 0 && unidade > 0 && centena > 0)
    {
        printf(" e ");
    }
    if (dezena > 0)
    {
        switch (dezena)
        {
        case 1:
            switch (unidade)
            {
            case 0:
                printf("dez");
                break;
            case 1:
                printf("onze");
                break;
            case 2:
                printf("doze");
                break;
            case 3:
                printf("treze");
                break;
            case 4:
                printf("quatorze");
                break;
            case 5:
                printf("quinze");
                break;
            case 6:
                printf("dezesseis");
                break;
            case 7:
                printf("dezessete");
                break;
            case 8:
                printf("dezoito");
                break;
            case 9:
                printf("dezenove");
                break;
            }
            break;
        case 2:
            printf("vinte");
            break;
        case 3:
            printf("trinta");
            break;
        case 4:
            printf("quarenta");
            break;
        case 5:
            printf("cinquenta");
            break;
        case 6:
            printf("sessenta");
            break;
        case 7:
            printf("setenta");
            break;
        case 8:
            printf("oitenta");
            break;
        case 9:
            printf("noventa");
            break;
        }
    }

    if (unidade > 0 && dezena != 1)
    {
        if (unidade > 0)
        {
            printf(" e ");
        }
        switch (unidade)
        {
        case 1:
            printf("um");
            break;
        case 2:
            printf("dois");
            break;
        case 3:
            printf("tres");
            break;
        case 4:
            printf("quatro");
            break;
        case 5:
            printf("cinco");
            break;
        case 6:
            printf("seis");
            break;
        case 7:
            printf("sete");
            break;
        case 8:
            printf("oito");
            break;
        case 9:
            printf("nove");
            break;
        }
    }
}
//-------------------------------------------------------

// Objetivo: melhorar legibilidade e manutenibilidade do código
#define MAX_USUARIOS 50
#define TAMANHO_CPF 15
#define TAMANHO_CONTA 10
#define MAX_SAQUES_POR_USUARIO 100

int main()
{
    int menu = 0;
    char cpf[MAX_USUARIOS][TAMANHO_CPF]; // 0, 1, 2... 49
    char c[MAX_USUARIOS][TAMANHO_CONTA];
    int valoresSacados[MAX_USUARIOS][MAX_SAQUES_POR_USUARIO];
    int quantidadeDeSaques[MAX_USUARIOS];
    int verificaSeHouveSaque[MAX_USUARIOS] = {0}; // Marca se houve saque para cada cliente
    int quantidadeDeClientesCadastrados = 0;

    int cedulasDisponiveis[8] = {450, 250, 50, 20, 10, 5, 2, 1};
    int QuantidadeDeCedulas[8] = {100, 200, 400, 800, 1600, 3200, 6400, 12800};
    int saldoExistente = 188600;
    int totalSacado = 0;

    srand(time(NULL));

    while (menu == 0)
    {
        int opcao;
        printf("Menu principal:\n1-Cliente\n2-Saque\n3-Relatorio\n4-Sair\n");
        scanf("%d", &opcao);

        while (getchar() != '\n')
            ; // Limpa o buffer de entrada
        // Menu principal

        switch (opcao)
        {
        // Menu cliente
        case 1:
        {
            int menuCliente = 1;
            while (menuCliente == 1)
            {
                int opcaoCliente;
                printf("Menu Cliente:\n1-Incluir\n2-Mostrar\n3-Alterar\n4-Excluir\n5-Sair\n");
                scanf("%d", &opcaoCliente);

                while (getchar() != '\n')
                    ; // Limpa o buffer de entrada

                switch (opcaoCliente)
                {
                // incluir
                case 1:
                {
                    if (quantidadeDeClientesCadastrados == MAX_USUARIOS)
                    {
                        printf("Nao eh possivel incluir mais clientes. Limite de clientes atingido");
                        break;
                    }

                    char convert[10];
                    int continuarInclusao = 1;
                    int contaNaoEncontrada = 0;

                    do
                    {
                        int verificaInclusaoValida = 0;
                        do
                        {

                            gera_cpf_valido(cpf[quantidadeDeClientesCadastrados]);
                            geraContaCorrente(c[quantidadeDeClientesCadastrados]);

                            if (quantidadeDeClientesCadastrados == 0)
                            {
                                contaNaoEncontrada = 1; // Primeira conta, não há comparação
                                break;
                            }
                            contaNaoEncontrada = 1; // Assume que a conta é válida inicialmente
                            for (int i = 0; i < quantidadeDeClientesCadastrados; i++)
                            {

                                if (strcmp(cpf[quantidadeDeClientesCadastrados], cpf[i]) == 0)
                                {
                                    contaNaoEncontrada = 0; // CPF duplicado, continua o loop
                                    break;
                                }
                            }

                        } while (contaNaoEncontrada == 0);

                        printf("Cliente %d: CPF: %s, Conta Corrente: %s\n", quantidadeDeClientesCadastrados + 1, cpf[quantidadeDeClientesCadastrados], c[quantidadeDeClientesCadastrados]);
                        quantidadeDeClientesCadastrados++;

                        printf("Deseja continuar? (1-Sim, 0-Nao): ");

                        while (verificaInclusaoValida != 1)
                        {
                            char entrada[10];
                            scanf("%s", &entrada);

                            while (getchar() != '\n')
                                ; // Limpa o buffer de entrada

                            if (strlen(entrada) == 1 && (entrada[0] == '0' || entrada[0] == '1'))
                            {
                                continuarInclusao = entrada[0] - '0'; // converte char '0'/'1' em int 0/1
                                if (entrada[0] == '0')
                                {
                                    opcaoCliente = 0;      // Sair do loop de inclusão
                                    continuarInclusao = 0; // Sair do loop de inclusão
                                    break;
                                }
                                if (entrada[0] == '1')
                                {
                                    opcaoCliente = 1; // Continuar no loop de inclusão
                                    break;
                                }
                                verificaInclusaoValida = 1;
                            }
                            if (verificaInclusaoValida != 1)
                            {
                                printf("Opcao invalida! Digite 1 para continuar ou 0 para sair: ");
                            }
                        }
                    } while (quantidadeDeClientesCadastrados < MAX_USUARIOS && continuarInclusao == 1);

                    if (quantidadeDeClientesCadastrados >= MAX_USUARIOS)
                    {
                        printf("Limite de clientes cadastrados atingido.\n");
                    }
                }
                break;
                // mostrar
                case 2:
                    printf("----------Clientes Cadastrados----------\n");
                    if (quantidadeDeClientesCadastrados == 0)
                    {
                        printf("Nenhum cliente cadastrado.\n");
                        break;
                    }
                    for (int i = 0; i < quantidadeDeClientesCadastrados; i++)
                    {
                        printf("Cliente %d: CPF: %s, Conta Corrente: %s\n", i + 1, cpf[i], c[i]);
                    }
                    break;
                // alterar
                case 3:
                {
                    int contaEncontrada = 0, alteracaoCpfFeita = 0, alteracaoContaFeita = 0;
                    int opcaoConfirmarAlteracao, opcaoAlterarCPF, opcaoAlterarConta;
                    int contaValida = 1, cpfValido = 1;
                    char manterConta[TAMANHO_CONTA], manterCPF[TAMANHO_CPF];

                    printf("Informe a Conta Corrente do Cliente a ser alterado:\n");

                    while (contaEncontrada == 0)
                    {
                        char conta_origem[TAMANHO_CONTA];
                        char conta_destino[TAMANHO_CONTA];
                        int validarConta = 0;
                        do
                        {
                            scanf("%10s", conta_origem);

                            while (getchar() != '\n')
                                ; // Limpa o buffer de entrada

                            insere_pontuacao_conta_corrente(conta_origem, conta_destino, &validarConta);
                        } while (validarConta == 0);

                        for (int i = 0; i < quantidadeDeClientesCadastrados; i++)
                        {
                            if (strcmp(c[i], conta_destino) == 0)
                            {
                                contaEncontrada = 1;

                                strncpy(manterCPF, cpf[i], TAMANHO_CPF);
                                strncpy(manterConta, c[i], TAMANHO_CONTA);

                                if (verificaSeHouveSaque[i] == 1)
                                {
                                    printf("Cliente com CPF: %s e Conta Corrente: %s nao pode ser alterado, pois ja houve saque.\n", cpf[i], c[i]);
                                    break;
                                }

                                printf("Tem certeza de que deseja alterar o cliente de CPF: %s e Conta Corrente: %s? Sim - 1 / Nao - 0\n", cpf[i], c[i]);
                                // logica para alterar cpf ou conta
                                do
                                {
                                    scanf("%d", &opcaoConfirmarAlteracao);

                                    while (getchar() != '\n')
                                        ; // Limpa o buffer de entrada
                                    if (opcaoConfirmarAlteracao != 0 && opcaoConfirmarAlteracao != 1)
                                    {
                                        printf("Opcao invalida! Digite 1 para confirmar ou 0 para cancelar: \n");
                                    }

                                } while (opcaoConfirmarAlteracao != 0 && opcaoConfirmarAlteracao != 1);

                                if (opcaoConfirmarAlteracao == 0)
                                {
                                    break;
                                }
                                printf("Deseja alterar o CPF do cliente? Sim - 1 / Nao - 0\n");

                                do
                                {
                                    scanf("%d", &opcaoAlterarCPF);

                                    while (getchar() != '\n')
                                        ; // Limpa o buffer de entrada
                                    if (opcaoAlterarCPF != 0 && opcaoAlterarCPF != 1)
                                    {
                                        printf("Opcao invalida! Digite 1 para confirmar ou 0 para cancelar: \n");
                                    }
                                } while (opcaoAlterarCPF != 0 && opcaoAlterarCPF != 1);

                                if (opcaoAlterarCPF == 0)
                                {
                                    printf("Alteracao de CPF cancelada.\n");
                                }
                                else
                                {
                                    int validarCpf = 0;
                                    char cpf_origem[15];
                                    char cpf_destino[15];
                                    char numeros[12] = {0};
                                    int l = 0;
                                    printf("informe o novo CPF (formato 999.999.999-99):\n");
                                    while (alteracaoCpfFeita == 0)
                                    {

                                        cpfValido = 1;

                                        do
                                        {
                                            scanf("%14s", cpf_origem);

                                            while (getchar() != '\n')
                                                ; // Limpa o buffer de entrada

                                            insere_pontuacao_cpf(cpf_origem, cpf_destino, &validarCpf);
                                        } while (validarCpf == 0);
                                        /*
                                         TODO = apagar cpf antigo e colocar o novo no lugar
                                         */

                                        for (int j = 0; j < quantidadeDeClientesCadastrados; j++)
                                        {
                                            if (strcmp(cpf_destino, cpf[j]) == 0 && i != j)
                                            {
                                                printf("CPF ja cadastrado! Por favor, tente novamente.\n");
                                                strncpy(cpf_destino, manterCPF, TAMANHO_CPF - 1);
                                                cpf_destino[TAMANHO_CPF - 1] = '\0';
                                                cpfValido = 0;
                                                break;
                                            }
                                        }
                                        if (cpfValido)
                                        {
                                            strncpy(cpf[i], cpf_destino, TAMANHO_CPF - 1);
                                            alteracaoCpfFeita = 1;
                                        }
                                    }
                                    printf("CPF alterado com sucesso para: %s\n", cpf_destino);
                                }
                                printf("Deseja alterar a Conta Corrente do cliente? Sim - 1 / Nao - 0\n");

                                do
                                {
                                    scanf("%d", &opcaoAlterarConta);

                                    while (getchar() != '\n')
                                        ; // Limpa o buffer de entrada
                                    if (opcaoConfirmarAlteracao != 0 && opcaoConfirmarAlteracao != 1)
                                    {
                                        printf("Opcao invalida! Digite 1 para confirmar ou 0 para cancelar: \n");
                                    }
                                } while (opcaoAlterarConta != 0 && opcaoAlterarConta != 1);

                                if (opcaoAlterarConta == 0)
                                {
                                    printf("Alteracao da Conta Corrente cancelada.\n");
                                }
                                else
                                {
                                    char conta_origem[TAMANHO_CONTA];
                                    char conta_destino[TAMANHO_CONTA];

                                    printf("Informe a nova Conte Corrente (formato 999.999-X):\n");

                                    while (alteracaoContaFeita == 0)
                                    {
                                        validarConta = 0;
                                        contaValida = 1;
                                        do
                                        {
                                            scanf("%9s", conta_origem);

                                            while (getchar() != '\n')
                                                ; // Limpa o buffer de entrada

                                            insere_pontuacao_conta_corrente(conta_origem, conta_destino, &validarConta);
                                        } while (validarConta == 0);

                                        for (int j = 0; j < quantidadeDeClientesCadastrados; j++)
                                        {
                                            if (strcmp(conta_destino, c[j]) == 0 && i != j)
                                            {
                                                printf("Conta Corrente ja cadastrada! Por favor, tente novamente.\n");
                                                strncpy(conta_destino, manterConta, TAMANHO_CONTA - 1);
                                                conta_destino[TAMANHO_CONTA - 1] = '\0';
                                                contaValida = 0;
                                                break;
                                            }
                                        }
                                        if (contaValida)
                                        {
                                            strncpy(c[i], conta_destino, TAMANHO_CONTA - 1);
                                            conta_destino[TAMANHO_CONTA - 1] = '\0';
                                            alteracaoContaFeita = 1;
                                        }
                                    }
                                    printf("Conta Corrente alterada com sucesso para: %s\n", conta_destino);
                                }

                                break;
                            }
                        }
                        if (contaEncontrada == 0)
                        {
                            printf("Cliente nao encontrado! Por favor, tente novamente.\n");
                        }
                    }
                }
                break;
                // excluir
                case 4:
                {
                    int contaEncontrada = 0, indiceDeExclusao = -1;
                    int opcaoConfirmarExclusao;
                    char conta_origem[10];
                    char conta_destino[10];
                    printf("Informe a Conta Corrente do Cliente a ser excluido:\n");

                    while (contaEncontrada == 0)
                    {
                        int validarConta = 0;
                        do
                        {
                            scanf("%9s", conta_origem);

                            while (getchar() != '\n')
                                ; // Limpa o buffer de entrada

                            insere_pontuacao_conta_corrente(conta_origem, conta_destino, &validarConta);
                        } while (validarConta == 0);
                        for (int i = 0; i < quantidadeDeClientesCadastrados; i++)
                        {
                            if (strcmp(c[i], conta_destino) == 0)
                            {
                                contaEncontrada = 1;

                                if (verificaSeHouveSaque[i] == 1)
                                {
                                    printf("Cliente com CPF: %s e Conta Corrente: %s nao pode ser excluido, pois ja houve saque.\n", cpf[i], c[i]);
                                    break;
                                }

                                printf("Tem certeza de que deseja excluir o cliente de CPF: %s e Conta Corrente: %s? Sim - 1 / Nao - 0\n", cpf[i], c[i]);
                                // logica para excluir cliente
                                do
                                {
                                    scanf("%d", &opcaoConfirmarExclusao);

                                    while (getchar() != '\n')
                                        ; // Limpa o buffer de entrada
                                    if (opcaoConfirmarExclusao != 0 && opcaoConfirmarExclusao != 1)
                                    {
                                        printf("Opcao invalida! Digite 1 para confirmar ou 0 para cancelar: \n");
                                    }
                                } while (opcaoConfirmarExclusao != 0 && opcaoConfirmarExclusao != 1);

                                if (opcaoConfirmarExclusao == 0)
                                {
                                    break;
                                }
                                indiceDeExclusao = i;

                                for (int i = indiceDeExclusao; i < quantidadeDeClientesCadastrados - 1; i++)
                                {
                                    strncpy(cpf[i], cpf[i + 1], TAMANHO_CPF);
                                    strncpy(c[i], c[i + 1], TAMANHO_CONTA);
                                    verificaSeHouveSaque[i] = verificaSeHouveSaque[i + 1];
                                }

                                quantidadeDeClientesCadastrados--;

                                printf("Cliente com CPF %s e Conta Corrente %s removido.\n", cpf[indiceDeExclusao], c[indiceDeExclusao]);
                                break;
                            }
                        }
                        if (contaEncontrada == 0)
                        {
                            printf("Cliente nao encontrado! Por favor, tente novamente.\n");
                            scanf("%9s", conta_origem);

                            while (getchar() != '\n')
                                ; // Limpa o buffer de entrada

                            insere_pontuacao_conta_corrente(conta_origem, conta_destino, &validarConta);
                        }
                    }
                }
                break;
                // sair
                case 5:
                    menuCliente = 0;
                    break;
                default:
                    printf("Opcao invalida! Digite uma opcao 1, 2, 3, 4 ou 5.\n");
                    break;
                }
            }
        }
        break;
        // Menu saque
        case 2:
        {
            int validarConta = 0;
            int contaEncontrada = 0, valorSaque;
            int quantidadeDeNotasASacar[8] = {0};
            char conta_origem[TAMANHO_CONTA];
            char conta_destino[TAMANHO_CONTA];

            if (quantidadeDeClientesCadastrados == 0)
            {
                printf("Nenhum cliente cadastrado. Por favor, cadastre um cliente antes de realizar um saque.\n");
                break;
            }

            printf("Informe a sua conta corrente (formato 999.999-X) para realizar o saque: \n");

            do
            {
                scanf("%10s", conta_origem);

                while (getchar() != '\n')
                    ; // Limpa o buffer de entrada

                insere_pontuacao_conta_corrente(conta_origem, conta_destino, &validarConta);
            } while (validarConta == 0);

            while (contaEncontrada == 0)
            {
                for (int i = 0; i < quantidadeDeClientesCadastrados; i++)
                {
                    int validarSaque = 0;
                    if (strcmp(c[i], conta_destino) == 0)
                    {
                        contaEncontrada = 1; // Conta encontrada
                        // int indiceUsuario = i;
                        int validarValorSaque = 0;
                        // logica do saque
                        while (validarValorSaque == 0)
                        {
                            printf("Informe o valor a ser sacado: \n");
                            scanf("%d", &valorSaque);

                            while (getchar() != '\n')
                                ; // Limpa o buffer de entrada

                            if (valorSaque <= 0)
                            {
                                printf("Valor de saque deve ser maior que zero! Por favor, tente novamente.\n");
                                continue;
                            }
                            if (valorSaque > saldoExistente)
                            {
                                printf("Saldo insuficiente! Por favor, tente novamente.\n");
                                continue;
                            }

                            validarValorSaque = 1; // Valor de saque válido
                        }
                        saldoExistente -= valorSaque; // Deduz o valor do saldo existente

                        int valorRestante = valorSaque;

                        totalSacado += valorSaque;

                        for (int i = 0; i < 8; i++)
                        {
                            if (valorRestante >= cedulasDisponiveis[i])
                            {
                                quantidadeDeNotasASacar[i] = valorRestante / cedulasDisponiveis[i];
                                QuantidadeDeCedulas[i] -= quantidadeDeNotasASacar[i];
                                valorRestante -= quantidadeDeNotasASacar[i] * cedulasDisponiveis[i];
                            }
                        }

                        printf("Saque realizado com sucesso!\n");

                        for (int i = 0; i < 8; i++)
                        {
                            if (quantidadeDeNotasASacar[i] > 0)
                            {
                                if (quantidadeDeNotasASacar[i] == 1)
                                {
                                    printf("%d nota de %d. \n", quantidadeDeNotasASacar[i], cedulasDisponiveis[i]);
                                }
                                else
                                {
                                    printf("%d notas de %d. \n", quantidadeDeNotasASacar[i], cedulasDisponiveis[i]);
                                }
                            }
                        }
                        int posicaoSaque = quantidadeDeSaques[i];
                        if (posicaoSaque < MAX_SAQUES_POR_USUARIO)
                        {
                            valoresSacados[i][posicaoSaque] = valorSaque;
                            quantidadeDeSaques[i]++;
                        }
                        else
                        {
                            printf("Limite de saques atingido para este usuario.\n");
                        }
                        verificaSeHouveSaque[i] = 1; // Marca que houve saque para o cliente
                        // ---------------

                        break;
                    }
                }
                if (contaEncontrada == 0)
                {
                    printf("Conta Corrente nao encontrada! Por favor, tente novamente.\n");
                    scanf("%10s", conta_origem);

                    while (getchar() != '\n')
                        ; // Limpa o buffer de entrada

                    insere_pontuacao_conta_corrente(conta_origem, conta_destino, &validarConta);
                }
            }
        }
        break;
        // Menu relatorio
        case 3:
        {
            int menuRelatorio = 0;
            while (menuRelatorio == 0)
            {
                int opcaoRelatorio;

                printf("\n--- MENU RELATORIO ---\n1-Valores Sacados\n2-Valor do Saldo Existente\n3-Quantidade de Cedulas Existentes\n4-Voltar ao Menu Principal\n");

                scanf("%d", &opcaoRelatorio);

                while (getchar() != '\n')
                    ; // Limpa o buffer de entrada

                switch (opcaoRelatorio)
                {
                // valores sacados
                case 1:
                    printf("----------------------------------------------------------------------------------------------------------------------------\n");
                    printf("Relatorio 'Valores Sacados'\n");
                    printf("----------------------------------------------------------------------------------------------------------------------------\n");
                    for (int i = 0; i < quantidadeDeClientesCadastrados; i++)
                    {
                        if (verificaSeHouveSaque[i] == 1)
                        {
                            printf("%s  %s          \n", c[i], cpf[i]);
                            int total = 0;
                            for (int j = 0; j < quantidadeDeSaques[i]; j++)
                            {
                                printf("                                  Saque: R$ %d\n", valoresSacados[i][j]);
                                total += valoresSacados[i][j];
                            }
                            printf("                                   Total: R$ %d\n", total);
                        }
                        // respectivos pagamentos
                    }
                    printf("----------------------------------------------------------------------------------------------------------------------------\n");

                    printf("R$%d ", totalSacado);
                    int valorPorExtenso = totalSacado;
                    gera_valor_por_extenso(valorPorExtenso);

                    printf("\n");

                    printf("----------------------------------------------------------------------------------------------------------------------------\n");

                    break;
                // valor do saldo existente
                case 2:
                    printf("----------------------------------------------------------------------------------------------------------------------------\n");
                    printf("Relatorio 'Valor do Saldo Existente'\n");
                    printf("----------------------------------------------------------------------------------------------------------------------------\n");
                    printf("R$%d ", saldoExistente);

                    valorPorExtenso = saldoExistente;
                    gera_valor_por_extenso(valorPorExtenso);

                    printf("\n");
                    printf("----------------------------------------------------------------------------------------------------------------------------\n");
                    break;
                // quantidade de cedulas existentes
                case 3:
                    printf("----------------------------------------------------------------------------------------------------------------------------\n");
                    printf("Relatorio 'Quantidade De Cedulas Existentes'\n");
                    printf("----------------------------------------------------------------------------------------------------------------------------\n");
                    for (int i = 0; i < 8; i++)
                    {
                        printf("Cedula %d quantidade %d ", cedulasDisponiveis[i], QuantidadeDeCedulas[i]);
                        valorPorExtenso = QuantidadeDeCedulas[i];
                        gera_valor_por_extenso(valorPorExtenso);

                        printf("\n");
                    }
                    printf("----------------------------------------------------------------------------------------------------------------------------\n");

                    break;
                // sair
                case 4:
                    menuRelatorio = 1;
                    break;
                default:
                    printf("Opcao invalida! Digite uma opcao 1, 2, 3 ou 4.\n");
                    break;
                }
            }
        }
        break;
        // Sair
        case 4:
            menu = 1;
            break;
        default:
            printf("Opcao invalida! Digite uma opcao 1, 2, 3 ou 4.\n");
            break;
        }
    }
    return 0;
}