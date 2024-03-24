# squareArrayConcurrent
Atividade 5 do Laboratorio 1 da disciplina de programação concorrente.

## Objetivo: Implementar o seu primeiro programa concorrente! 
Escreva um programa com M threads, para elevar ao quadrado cada elemento de um vetor de N elementos do
tipo inteiro. (Para cada elemento ai do vetor, calcular o novo valor e escrever o resultado
na mesma posição do elemento.)

Roteiro:

1. Comece pensando em como dividir a tarefa de elevar ao quadrado todos os ele-
mentos de um vetor entre M threads.Importante: todas as threads deverao executar a mesma função. Qual(is) argumento(s) deverá(ão) ser passado(s) para a função
executada pelas threads?

2. Implemente func ̧oes separadas para inicializar e carregar o vetor e verificar se o
resultado esta correto no final.

3. Na função main, chame a funçãoo de inicialização do vetor; crie as threads; aguarde
o termino da execução das threads criadas e chame a função para verificar se os
valores finais do vetor estao corretos.

4. Execute o programa varias vezes e verifique se ele esta funcionando corretamente.