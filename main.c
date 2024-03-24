#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int value = 5;

int main()
{
    int fd[2]; // Array para os descritores do pipe
    pid_t pid;

    if (pipe(fd) == -1) { // Criar o pipe
        perror("pipe");
        return 1;
    }

    pid = fork();

    if (pid == 0) { // Processo filho
        close(fd[0]); // Fechar o descritor de leitura do pipe no processo filho
        printf("Entrei no filho!\n");
        value += 15;
        printf ("CHILD: value = %d\n", value); /* LINE A */
        write(fd[1], &value, sizeof(value)); // Escrever o valor no pipe
        close(fd[1]); // Fechar o descritor de escrita do pipe no processo filho
        return 0;
    }
    else if (pid > 0) { // Processo pai
        close(fd[1]); // Fechar o descritor de escrita do pipe no processo pai
        wait(NULL);
        read(fd[0], &value, sizeof(value)); // Ler o valor do pipe
        printf ("PARENT: value = %d\n", value); /* LINE A */
        close(fd[0]); // Fechar o descritor de leitura do pipe no processo pai
        return 0;
    }
}
# Lab02b
