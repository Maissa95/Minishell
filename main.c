#include <stdio.h>

//apporte execvp()

#include <unistd.h>
#include <stdlib.h>

//str...

#include <string.h>

//wait ; fork()

#include <wait.h>



int main (int argc, char ** argv) {

	char ** commandeCut = NULL;
	char * strToken;
	char commande[256];
	int count = 0;
	int i;
	int espace;
	pid_t childpid;



//on remplit notre tableau de 0 pour pas avoir des valeur rdm



	for (i = 0; i < 256; i++) {
		commande[i] = 0;
	}



//boucle while qui tourne jusqu'à que l'utilisateur saisie "close"



	while (strcmp(commande, "close")){



//initialise le tableau commande à 0 (tab caractères)



		for (i = 0; i < 256; i++) {
			commande[i] = 0;
		}



//pour faire jolie : ">"


		printf(" > ");


//récupere ce que l'utilisateur à entré 


		fgets(commande, 256, stdin);



//om remplace l'avant dernier caractere de notre commande par 0 pour supprimé \n 


		commande[strlen(commande) - 1] = 0;


//si l'utilisateur entre close on ne rentre pas dans la boucle for et retourne dans le while


		if (strcmp(commande, "close")) {


//Compte combien il y'a d'espace dans notre commande donc combien il y a de mots s'il y'a pls espace ou non



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



//tab de chaine de caractere 

//permet de reserver de la memoire en fonction de la taille de la commande



			commandeCut = malloc(sizeof(*commandeCut) * count);



//strtok permet de couper la chaine de caractere, en fonction de l'élément saisi ici " "

//strToken renvoi la premiere partie de la chaine avant le séparateur donc " "


			strToken = strtok(commande, " ");


//le premier mot du tab indice 0 = TstrToken = commande


			commandeCut[0] = strToken;


//tant que y'a quelque chose à séparer 


			for (i = 1; strToken != NULL; i++) {


//fait référence à une addresse mais on le met à null donc pas d'adresse, retourne la dernière commande saisie


				strToken = strtok(NULL, " ");


//commandeCut c'est notre commande saisie (tab chaine de caratère)

				commandeCut[i] = strToken;
			}


//on duplique le programme à l'aide fork()


			childpid = fork();



//si tu est dans le programme dupliqué (enfant) ,tu va exécuter une commande (commande,adresse de la commande)


			if (childpid == 0) {
				execvp(commandeCut[0], &commandeCut[0]);
				return 0;
			}


//ici on est dans le programme parent
//wait() on attend que le programme enfant soit complétement fermé



			wait(&childpid);



//ici on libère la memoire à l'aide du free


			free(commandeCut);
		}
	}

	printf("bye");

	return 0;
}
