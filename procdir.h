#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include "param.h"

int procdir(char *base, void (*p)(void*), void *param, int isRecursive)
{
    //(*p)(s);
    // DIR *dir = NULL;
    struct dirent *entry = NULL, **namelist;
    char path[1000];

    int num;
    num = scandir(base, &namelist, NULL, alphasort);
    if (num<0)
    {
    
        printf("Open dir %s failed!\n", base);
        return -1;
    }
    else
    {
        int i;
        for(i=0;i<num;i++)
        {
            entry = namelist[i]; 
            if(strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") ==0)
            {
                continue;
            }
            else if(entry->d_type == 8) //file
            {
                //process the file
                memset(path, '\0', sizeof(path));
                sprintf(path, "%s/%s", base, entry->d_name);
                ((STR_1_PARAM*)param)->str = path;
                (*p)(param);
            } 
            else if(isRecursive && entry->d_type == 4) //directory
            {
                //process dir
                memset(path, '\0', sizeof(path));
                sprintf(path, "%s/%s", base, entry->d_name);
                procdir(path, p, param, isRecursive);
            }
        }
    }
    return 1;
    /*
    if((dir=opendir(base)) == NULL)
    {
        printf("Open dir %s failed!\n", base);
        return -1;
    }

    
    while((entry=readdir(dir)) != NULL)
    {
        if(strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") ==0)
        {
            continue;
        }
        else if(entry->d_type == 8) //file
        {
            //process the file
            memset(path, '\0', sizeof(path));
            sprintf(path, "%s/%s", base, entry->d_name);
            printf("inode:%ld", entry->d_ino);
            ((STR_1_PARAM*)param)->str = path;
            (*p)(param);
        }
        else if(isRecursive && entry->d_type == 4) //directory
        {
            //process dir
            memset(path, '\0', sizeof(path));
            sprintf(path, "%s/%s", base, entry->d_name);
            procdir(path, p, param, isRecursive);
        }
    }
    closedir(dir);
    return 1;*/
}
