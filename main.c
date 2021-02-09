#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <wait.h>

int displayCommande (char ** commande);

int main (int argc, char ** argv) {

	char ** commandeCut = NULL;
	char * strToken;
	char commande[256];
	int count = 0;
	int i;
	int espace;
	pid_t childpid;

	for (i = 0; i < 256; i++) {
		commande[i] = 0;
	}

	while (strcmp(commande, "close")){

		for (i = 0; i < 256; i++) {
			commande[i] = 0;
		}

		printf(" > ");

		fgets(commande, 256, stdin);
		commande[strlen(commande) - 1] = 0;

		if (strcmp(commande, "exit")) {

			for (i = 0, espace = 0, count = 1; i < strlen(commande); i++){
				if (commande[i] == ' ') {
					if (!espace){
						espace = 1;
						count++;
					}
				} else {
					espace = 0;
				}
			}

			commandeCut = malloc(sizeof(*commandeCut) * count);

			strToken = strtok(commande, " ");
			commandeCut[0] = strToken;

			for (i = 1; strToken != NULL; i++) {
				strToken = strtok(NULL, " ");
				commandeCut[i] = strToken;
			}

			childpid = fork();

			if (childpid == 0) {
				execvp(commandeCut[0], &commandeCut[0]);
				return 0;
			}

			wait(&childpid);

			free(commandeCut);
		}
	}

	printf("bye");

	return 0;
}
