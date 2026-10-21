#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <assert.h>
#include <errno.h>
#include <limits.h>
#include "util.h"


char *lv = "│   ";
char *t = "├── ";
char *b = "└"; 

void gen_branch(char *path, char **branch){
    
    int level = 0;
    for(int i = 0; i < strlen(path); i++){
        if(path[i] == '/') {
            level++;
        }
    }
    
    char *cur_branch = "├── ";
    for(int i = 0; i < level-1; i++) {
        char *new_branch = NULL;
        asprintf(&new_branch, "%s%s", lv, cur_branch);
        
        cur_branch = new_branch;
        free(new_branch);
    }
    *branch = cur_branch;
}



int tree( char *path) {
    DIR *dir = opendir(path);
    if(!dir) {printf("err path: %s\n", path);}
    struct dirent *entry = NULL;
    
    while((entry = readdir(dir)) != NULL) {
        
        
        if(strcmp(entry->d_name, "..") && strcmp(entry->d_name, ".")) {
            if(entry->d_type == DT_DIR){
                char newpath[PATH_MAX];
                snprintf(newpath, sizeof(newpath), "%s/%s", path, entry->d_name);
                
                char *b = NULL;
                gen_branch(path, &b);
                
                printf("%s%s\n", b, entry->d_name);
                
                tree(newpath);
            }
            else {
                char *b = NULL;
                gen_branch(path, &b);
                
                printf("%s%s\n", b, entry->d_name);
            }
        }
    } 
    
    closedir(dir);
    return 0;
}
int main() {
    tree("/");
    return 0;
    
}
