#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

int main(){
  int n,m;
  scanf("%d%d",&n,&m);
  char name[100][50];
  char id[100];
  for(int i=0;i<n;++i){
    scanf("%s %s",name+i,&id[i]);
  }
  while(m--){
    char s[50];
    scanf("%s",s);
    int s_len=strlen(s);
    int f1=-1;
    for(int i=0;i<n;++i){
      if(strcmp(s,name[i])==0){
        f1=i;
        break;
      }
    }
    if(f1!=-1){
      printf("%c\n",id[f1]);
      continue;
    }
    int cnt=0;
    char L,R;
    for(int i=1;i<s_len;++i){
      char l[50]={0};
      char r[50]={0};
      strncpy(l,s,i);
      strcpy(r,s+i);
      int fl=-1;
      for(int j=0;j<n;++j){
        if(strcmp(l,name[j])==0){
          fl=j;
          break;
        }
      }
      int fr=-1;
      for(int j=0;j<n;++j){
        if(strcmp(r,name[j])==0){
          fr=j;
          break;
        }
      }
      if(fl!=-1&&fr!=-1){
        cnt++;
        L=id[fl];
        R=id[fr];
      }
    }
    if(cnt==1){
      printf("%c%c\n",L,R);
    }
    else{
      printf("D\n");
    }
  }
}