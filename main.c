#include <string.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

int vueltas=0;
int signalON;
int main(void)
{
        int     pipe1[2],pipe2[2], nbytes;
        pid_t   childpid;
        char    readbuffer[80];
        int size = 99;
        sprintf(readbuffer, "%d\n ",size); 
        pipe(pipe1);
        pipe(pipe2);

        void sigchld_handler(int sig);
        

        if((childpid = fork()) == -1)
        {
                perror("fork");
                exit(1);
        }
 
        
        
        if(childpid == 0)
        {
                for(;;)
                {
                    printf("[-] Hijo:\n"); 
                    close(pipe1[1]); // 1 escritura
                    nbytes = read(pipe1[0], readbuffer, sizeof(readbuffer));  // 0 lectura              
                    printf("Valor recibido: %s", readbuffer);

                    int num = atoi(readbuffer);
                    num = num +3;
                    printf("+ 3 = %d\n",num);
                    sprintf(readbuffer, "%d",num);  
                    close(pipe2[0]);
                    write(pipe2[1], readbuffer, (strlen(readbuffer)));
                    vueltas = vueltas + 1;
                    if (vueltas > 10) 
                    { 
                        exit(0);
                    }
                    }
                exit(0);
        }
        else  
        {
            

                    for(;;){
                        printf("[+] Padre: \n");
                        close(pipe1[0]); // 0 lectura
                        write(pipe1[1], readbuffer, (strlen(readbuffer)+1)); // 1 escritura


                        close(pipe2[1]);                       
                        nbytes = read(pipe2[0], readbuffer, sizeof(readbuffer));               
                        printf("Valor recibido: %s", readbuffer);
                        int num = atoi(readbuffer);
                        num = num +7;
                        printf("+ 7 = %d\n",num);

                        sprintf(readbuffer, "%d ",num); 
                    }
                
            
                
        }
    

        return(0);
}

void sigchld_handler(int sig){
    signalON = 1;
}
