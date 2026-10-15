#include <stdio.h> 
#include <string.h> 
#include <mpi.h> 
int main(int argc, char* argv[]) { 
int my_rank; /* rang du processus */ 
int p; /* nombre de processus */ 
int source; /* rang de l’emetteur */ 
int dest; /* rang du recepteur */ 
int tag = 0; /* etiquette du message */ 
char message[100]; 
MPI_Status status; 

printf("Avant MPI_Init\n");

/* Initialisation */ 
MPI_Init(&argc, &argv); 
MPI_Comm_rank(MPI_COMM_WORLD, &my_rank); 
MPI_Comm_size(MPI_COMM_WORLD, &p); 

printf("[rang %d %d] Après l'initialisation\n", my_rank, p);

if (my_rank != 0) { 
/* Creation du message */ 
sprintf(message, "Coucou du processus %d!", my_rank); 
dest = 0; 
printf("[rang %d] Envoi du message '%s' à %d\n", my_rank, message, dest);
MPI_Send(message, strlen(message)+1, MPI_CHAR, 
dest, tag, MPI_COMM_WORLD); 
printf("[rang %d] Message envoyé\n", my_rank);
} else { 
for (source = 1; source < p; source++) { 
    printf("[rang 0] J'attend le message du rang %d\n",source);
MPI_Recv(message, 100, MPI_CHAR, source, tag, MPI_COMM_WORLD, &status); 
printf("%s\n", message); 
} 
} 
/* Desactivation */ 
MPI_Finalize(); 
return 0; 
} 