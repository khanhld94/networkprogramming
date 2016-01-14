#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#define MAX 81
int sockfd;
struct sockaddr serverAddr;
char buff[1024];
struct sockaddr_in inAddr;

int createSocket(){
  sockfd=socket(AF_INET,SOCK_STREAM,0);
  if (sockfd == -1)
    {
        printf("khong tao duoc socket\n");
        exit(1);
    }
    printf("Tao socket thanh cong\n");
    inAddr.sin_family=AF_INET;
    inAddr.sin_port=htons(5500);
    inet_aton("127.0.0.1",&inAddr.sin_addr);
    if(connect(sockfd,(struct sockaddr *)&inAddr,sizeof(struct sockaddr))<0){
      printf("connect failed.\n");
      exit(1);
    }
}
char *inputString(int size){
  int test=0;
  char *s=(char*)malloc(size);
  do{
    if(test!=0){
      printf("Moi nhap lai : ");
    }
  fgets(s,size,stdin);
  test++;
  }while(strlen(s)<=1);
  return strtok(s,"\n");
}
int todo1(){
  char *FileName;
  char *Result;
  FILE *fpt,*ft;
  int sentBytes,revedBytes;
  int Count=0;

  printf("Nhap ten file gui : ");
  FileName = inputString(20);
  fpt = fopen(FileName,"r");
  if(fpt==NULL){
    printf("Khong tim thay file");
    return -1;
  }
  printf("Nhap ten file ket qua tra ve : ");
  Result = inputString(20);
  ft = fopen(Result,"w");
  strcpy(buff,"S");
  sentBytes=send(sockfd,buff,1024,0);
  while(!feof(fpt)){
    if (fgets(buff,MAX,fpt) != NULL ){
      sentBytes=send(sockfd,buff,1024,0);
      Count = Count + strlen(buff);
      revedBytes=recv(sockfd,buff,1024,0);
      buff[revedBytes]='\0';
      fprintf(ft,"%s",buff);
    }
  }
  fclose(fpt);fclose(ft);
  strcpy(buff,"Q");
  send(sockfd,buff,1024,0);
  return Count;
}

int todo2(){
  char *FileName;
  char *Result;
  FILE *fpt,*ft;
  int sentBytes,revedBytes;
  int Count=0;
  
  printf("Nhap ten file gui : ");
  FileName = inputString(20);
  fpt = fopen(FileName,"r");
  if(fpt==NULL){
    printf("Khong tim thay file");
    return -1;
  }
  printf("Nhap ten file ket qua tra ve : ");
  Result = inputString(20);
  ft = fopen(Result,"w");
  strcpy(buff,"M");
  sentBytes=send(sockfd,buff,1024,0);
  while(!feof(fpt)){
    if (fgets(buff,MAX,fpt) != NULL ){
      sentBytes=send(sockfd,buff,1024,0);
      Count = Count + strlen(buff);
      revedBytes=recv(sockfd,buff,1024,0);
      buff[revedBytes]='\0';
      fprintf(ft,"%s",buff);
    }
  }
  fclose(fpt);fclose(ft);
  strcpy(buff,"Q");
  send(sockfd,buff,1024,0);
  return Count;
}
int main(int argc, char *argv[]){
  int chose;
  int Sum;
  createSocket();
  printf("Connection accepted\n");
  while(1){
    printf("Nhap vao 1 so : ");scanf("%d",&chose);
    switch(chose){
      case 1 : Sum = todo1();
            printf("Gui thanh cong\n");
            printf("So byte da gui : %d\n",Sum);
      break;
      case 2 : Sum = todo2();
            printf("Gui thanh cong\n");
            printf("So byte da gui : %d\n",Sum);
      break;
      case 3 :
            strcpy(buff,"exit");
            send(sockfd,buff,1024,0);
            close(sockfd);
            return 1;
      break;
      default:
      break;
    }
  }
return 0;
}
