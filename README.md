# Gerador e Extrator de Código de Barras EAN-8

Este projeto implementa dois programas em C para manipulação de códigos de barras no padrão EAN-8. Ele permite gerar imagens de códigos de barras a partir de um identificador fornecido e extrair identificadores de imagens no formato PBM.

Os dois programas são: 
- **Gerador de Código de Barras**: cria um arquivo PBM com a representação do código de barras EAN-8.
- **Extrator de Código de Barras**: lê um arquivo PBM contendo o código de barras e extrai o identificador.

Para o gerador, é obrigatório fornecer o identificador. Há também parâmetros opcionais que permitem configurar a altura, largura das barras e nome do arquivo gerado. Por exemplo, ao executar o comando `./gerador 40170725 --altura 50 --largura 3 --saida codigo.pbm`, será gerado um arquivo chamado `codigo.pbm` contendo a representação gráfica do código de barras para o identificador `40170725`.

O formato do arquivo gerado segue o padrão PBM, onde cada barra preta é representada pelo valor `1` e cada espaço branco pelo valor `0`. O cabeçalho do arquivo inclui as dimensões da imagem. Um exemplo de conteúdo gerado seria:

P1 209 58 00000000000000000000 00001110001110110000 ...


Para o extrator, você deve fornecer um arquivo PBM contendo o código de barras. O programa verificará se o arquivo é válido e, caso contenha um código de barras, exibirá o identificador correspondente. Por exemplo, ao executar o comando `./extrator codigo.pbm`, o programa exibirá no terminal a mensagem `Identificador: 40170725`.

Ambos os programas utilizam validações para garantir a integridade dos dados. No gerador, o identificador deve conter exatamente 8 dígitos, sendo que o último é o dígito verificador calculado a partir dos sete primeiros. Caso o identificador seja inválido, o programa exibirá uma mensagem de erro e encerrará a execução. Já no extrator, caso o arquivo PBM não contenha um código de barras válido, o programa informará que o código não foi encontrado.

O formato PBM é ideal para representar códigos de barras devido à sua simplicidade. Ele suporta apenas duas cores: preto (`1`) e branco (`0`), permitindo a criação de imagens compactas e fáceis de processar. O código de barras é gerado com barras de largura fixa e espaçamento configurável, garantindo a compatibilidade com scanners.

Para compilar e executar os programas, é necessário um compilador C, como o GCC, e um ambiente Linux ou compatível. Ambos os programas podem ser compilados separadamente e utilizam funções compartilhadas para manipulação do formato PBM e validação de dados.

Se desejar contribuir para o projeto, você pode fazer um fork do repositório, criar um branch para suas alterações e enviar um pull request. Para dúvidas ou melhorias, sinta-se à vontade para abrir uma issue.

Projeto desenvolvido por Kaio Zinwest.
