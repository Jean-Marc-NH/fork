        int     fd[2], fd2[2], nbytes;
        pid_t   childpid;
        pid_t   childpid2;
        char    string[] = "Hello, world!\n";
        char    readbuffer[80];
        int c;

        pipe(fd);
        pipe(fd2);

        if((childpid = fork()) == -1)
        {
                perror("fork");
                exit(1);
        }
 
        printf("Main program:"); 

        if(childpid == 1)
        {
                int c;
                printf("Padre:"); 
                c=getchar();
                printf("C %c\n",c);
                close(fd[0]);

                write(fd[1], string, (strlen(string)+1));
                exit(0);
        }
        else
        {
                int c;
                printf("Hijo"); 
                c=getchar();
                printf("P %c\n",c);
                close(fd[1]);

                nbytes = read(fd[0], readbuffer, sizeof(readbuffer));
                printf("Received string: %s", readbuffer);
        }
