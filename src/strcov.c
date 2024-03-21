#include <stdio.h>
#include <stdlib.h>
#include <string.h>





/**
 * @brief 把输入的字符串 转换为2  8  10 16 进制
 * 
 * @param base  需要设置基数 2 8 10 16 默认的为16进制
 * 
 * @todo:: 去掉‘\n’  DONE
 * 
 */

int lineMaxLen=16;



typedef enum BASE{
    BINARY=2,
    OCTAL=8,
    DECIMAL=10,
    HEXADECIMAL=16
} BASE;



void showChar(unsigned char ch){
    unsigned char flag=0x80;
    for(int i=0;i<8;i++){
        if(ch & flag)
            printf("1");
        else
            printf("0");
        flag >>=1;
    }
    printf(" ");

}


void showStrBin(const char *str){
    for(int i=0;str[i];i++){
        showChar((unsigned char)str[i]);
        if((i % lineMaxLen) == (lineMaxLen /2 )-1)
            printf("  ");
        else if((i % lineMaxLen) == (lineMaxLen -1))
            printf("\n");
    }
}

static int showHelp(const char *exe_file){
    fprintf(stderr,"显示输入的字符2 8 10 16进制格式输出\n");
    fprintf(stderr,"Usage:%s <输出进制 default 16>\n",exe_file);
    fprintf(stderr,"exit or eof or EOF or quit to exit\n");
    return EXIT_FAILURE;
}
void ShowStrHex(const char *str){
    for(int i=0;str[i];i++){
        printf("0x%.2X ",(unsigned char)str[i]);
        if((i % lineMaxLen) == (lineMaxLen /2 )-1)
            printf("  ");
        else if((i % lineMaxLen) == (lineMaxLen -1))
            printf("\n");
        
    }
}

void ShowStrDec(const char *str){
    for(int i=0;str[i];i++){
        printf("%03d ",(unsigned char)str[i]);
        if((i % lineMaxLen) == (lineMaxLen /2 )-1)
            printf("  ");
        else if((i % lineMaxLen) == (lineMaxLen -1))
            printf("\n");
    }
}

void ShowStrOcl(const char *str){
    for(int i=0;str[i];i++){
        printf("0%d", (unsigned char)str[i] >> 6 & 0x03);
        printf("%d", (unsigned char)str[i] >> 3 & 0x07);
        printf("%d ",(unsigned char)str[i]      & 0x07);

       
        if((i % lineMaxLen) == (lineMaxLen /2 )-1)
            printf("  ");
        else if((i % lineMaxLen) == (lineMaxLen -1))
            printf("\n");
    }
}


void ShowStr(const char *str,int base){
    switch (base)
    {
    case BINARY:
        showStrBin(str);
        break;
    case OCTAL:
        ShowStrOcl(str);
        break;
    case DECIMAL:
        ShowStrDec(str);
        break;
    case HEXADECIMAL:
        ShowStrHex(str);
        break;
    
    default:
        break;
    }
}

char Buff[BUFSIZ];
int globalBase=16;

int main(int argc,char *argv[]){
    if(argc==2 && (!strncmp(argv[1],"-h",2) || !strncmp(argv[1],"-H",2))){
        
        exit(showHelp(argv[0]));
    }
    int intputBase =0;
    if(argc==2 && (intputBase=atoi(argv[1])) && ((intputBase ==2) ||(intputBase ==8)||(intputBase ==10)||(intputBase ==16))){
        globalBase=intputBase;
    }
    fprintf(stdout,"Base = %d\n",globalBase);

    char *p;
    size_t n;


    while((p = fgets(Buff,BUFSIZ,stdin))){
        // if(*p =='\n') continue;
        n=strlen(p); 
        //fgets带有换行符号 去掉
        p[--n]='\0';    

        if(n)
        {
            if(!strncmp(p,"EOF",3) || !strncmp(p,"exit",4) || !strncmp(p,"EXIT",4) || !strncmp(p,"quit",4))
                break;
            ShowStr(p,globalBase);
            putchar('\n');
        }else{
            continue;
        }



    };

    return 0;
    


}