//
//  code for assignment 4
//  
//
//  Created by Bibhas Ghoshal on 26/08/20.
//

#include <stdio.h>
#include <unistd.h>

#ifndef ITR
#define ITR 100000
#endif

int main()
{
    int i,j,pid;
    
    pid = fork();
    
    if( pid == 0 ){
        /* Child process */
        for ( i=0;i<20;i++){
            /* 1. wait a period of time (with respect to ITR)*/
           for (j=0;j<ITR;j++);
           /* 2. echo*/
           printf("Child:%d\n",i);
           
            
        }
        
    }
    else{
        /* Parent process*/
        for ( i=0;i<20;i++){
            /* 1. wait a period of time (with respect to ITR)*/
            for (j=0;j<ITR;j++);
            /* 2. echo*/
            printf("Parent:%d\n",i);
            
        }
    }
    
}
