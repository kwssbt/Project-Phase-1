#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

int main(){
  char str[500];
  scanf("%s",str);
  int n;
  scanf("%d",&n);
  while(n--){
    int l,r;
    char pre[10],suf[10];
    scanf("%d%d",&l,&r);
    scanf("%s%s",pre,suf);
    int copy_len=r-l+1;
    char copy[500]={0};
    strncpy(copy,str+l-1,copy_len);
    copy[copy_len]='\0';
    char rest[500]={0};
    strncpy(rest,str,l-1);
    rest[l-1] = '\0';
    strcat(rest,str+r);
    int rest_len=strlen(rest);
    int pre_len=strlen(pre);
    int suf_len=strlen(suf);
    int p=-1;
    for(int i=0;i<=rest_len-pre_len;++i){
      if(strncmp(rest+i,pre,pre_len)==0){
        if(i+pre_len+suf_len<=rest_len&&strncmp(rest+i+pre_len,suf,suf_len)==0){
          p=i+pre_len;
          break;
        }
      }
    }
    if(p==-1){
      strcat(rest,copy);
      strcpy(str,rest);
    }
    else{
      char s[500]={0};
      strncpy(s,rest,p);
      s[p]='\0';
      strcat(s,copy);
      strcat(s,rest+p);
      strcpy(str,s);
    }
  }
  printf("%s",str);
}