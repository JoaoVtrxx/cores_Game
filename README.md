# cores_Game

O jogo **cores** foi desenvolvido em C, funciona conforme descrito a seguir.

O jogo escolhe uma cor, na forma de 3 números aleatórios, que representam os 3 componentes dessa cor (vermelho, verde, azul). O usuário então deve tentar acertar os valores desses 3 componentes, alterandos os valores das barras de cor vermelho, verde ou azul. As setas direita e esquerda alteram o valor da barra corrente. As setas para cima e para baixo selecionam outra barra. Enter encerra a partida. A partida encerra automaticamente após 20 segundos.

Cada número da cor sempre está entre 0 e 255. 

Durante a execução é mostrado na tela dois quadrados, um com a cor sorteada e outro com a cor atualizada, que reflete os valores das barras.

A distância do chute é a soma das diferenças entre cada valor e o valor correspondente a acertar, sem sinal. A pontuação é um valor entre 0 e 100, 0 é quando a diferença é a maior possível (considerando a cor a acertar) e 100 quando a diferença é zero (os 3 valores são iguais). A pontuação é acrescida de um bônus de 5% dos pontos para cada segundo de antecipação do final da partida.

O jogo salva o registro de recordes em um arquivo, que é lido no início da execução e gravado ao final de cada partida, se a pontuação for suficiente. Além dos pontos, é registrado um nome (de pelo menos 3 letras), pedido ao usuário no final da partida.

# Galeria

<img src="https://github.com/JoaoVtrxx/cores_Game/assets/106991499/87b0ca30-26f6-46a2-b015-75f112a980ff" width="350" />
<img src="https://github.com/JoaoVtrxx/cores_Game/assets/106991499/528bfc7e-4034-43d9-b77c-415b7fc244e1" width="350" />

# Executar

Para jogar é simples, basta baixar a pasta com os arquivos e compile no terminal com o comando:

**gcc -Wall -o jogo cores.c tela.c**

Após, execute com:

**./jogo**
