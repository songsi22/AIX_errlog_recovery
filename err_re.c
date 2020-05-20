#include<stdio.h>
#include<unistd.h>
#include<time.h>
/* recovery errlog V1.2, made by rew */

int main(void)
{
	FILE *fp;
	char str[]={0xff,0xff};
	int s=0;
	struct tm *t;
	time_t timer;
	timer=time(NULL);
	t = localtime(&timer);
	
	if(0 == accessx("/var/adm/ras/errlog",W_OK,ACC_SELF))
	{
		printf("Recovery errlog V1.2\n");
		printf("1. After copy errlog file then recovery\n");
		printf("2. Just Recovery errlog file\n");
		printf("3. Exit\n");
		printf("choose the number : ");
		scanf("%d",&s);
		switch(s){
		case 1:
			printf("please wait, 10sec\n");
			system("cp /var/adm/ras/errlog /var/adm/ras/errlog_`date +%Y%1m%d`");
			printf("cp /var/adm/ras/errlog /var/adm/ras/errlog_%d%d%d\ndone\n",t->tm_year+1900,t->tm_mon+1,t->tm_mday);
			fp = fopen("/var/adm/ras/errlog","r+");
			fseek(fp,14,SEEK_SET);
			fwrite(&str,1,2,fp);
			fseek(fp,26,SEEK_SET);
			fwrite(&str,1,2,fp);
			fclose(fp);
			system("/usr/lib/errdemon -i /var/adm/ras/errlog");
			printf("errlog recovery done\n");
		break;
		case 2:
			printf("please wait, 10sec\n");
			fp = fopen("/var/adm/ras/errlog","r+");
			fseek(fp,14,SEEK_SET);
			fwrite(&str,1,2,fp);
			fseek(fp,26,SEEK_SET);
			fwrite(&str,1,2,fp);
			fclose(fp);
			system("/usr/lib/errdemon -i /var/adm/ras/errlog");
			printf("errlog recovery done\n");
		break;
		case 3:
		break;
		}
	}
	else{
	printf("you have no write permission\n");
	}
	return 0;
}
