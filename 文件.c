#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct FileNode{
	char name[10];//文件名 
	char faname[10];//上层文件夹名 
	char content[10];//文件内容 
	struct FileNode* father;//指向上层文件夹 
	struct FileNode* sib;//指向同一层文件 
	struct FileNode* son;//指向子文件 
	int isfile;//判断文件夹还是文件 ,真为文件，假为文件夹 
}FileNode,*pFile; 

FileNode Head;//根节点 
pFile now;

void init()
{
	strcpy(Head.name, "...");
	Head.son = NULL;
	Head.father = NULL;
	Head.sib = NULL;
	Head.isfile = 0;
	now = &Head;
}

void pwd(pFile p)//使用时pwd（now） 
{
	pFile mov = p;
	if(mov->father != NULL)
	{
		mov = mov->father;
		pwd(mov);
		
	}
	printf("%s/",p->name);
}

void ls()
{
	pFile p = now;
	p = p->son;
	while(p)
	{
		if(p->sib == NULL)
			printf("%s",p->name);
		else
			printf("%s ",p->name);
		p = p->sib;
	}
	printf("\n");
}

void mkdir()
{
	pFile p,f = now;
	int flag = 0;
	FileNode *q = (pFile)malloc(sizeof(FileNode));
	if(f->son == NULL) flag = 1;
	else
	{
		p = f->son;
		while(p->sib) p = p->sib;
	}
	scanf("%s",q->name);
	strcpy(q->faname, f->name);
	q->father = f;
	if(flag) f->son = q;
	q->sib = NULL;
	q->son = NULL;
	q->isfile = 0;
	if(flag == 0)//之前已经有子文件或子文件夹 
		p->sib = q;	
}

void touch()
{
	pFile p,f = now;
	int flag = 0;
	FileNode *q = (pFile)malloc(sizeof(FileNode));
	if(f->son == NULL) flag = 1;
	else
	{
		p = f->son;
		while(p->sib) p = p->sib;
	}
	scanf("%s",q->name);
	strcpy(q->faname, f->name);
	q->father = f;
	if(flag) f->son = q;
	q->sib = NULL;
	q->son = NULL;
	q->isfile = 1;
	if(flag == 0)//之前已经有子文件或子文件夹 
		p->sib = q;
	memset(q->content,'\0',sizeof(q->content));
}

void cat()
{
	char path[50];
	pFile mov = now;
	int p = 0,q = 0;//游标
	int l;//字符串长度
	int flag = 0;//路径是否正确 
	char part[20];//路径中截取的文件名
	scanf("%s",path);
	while(path[q] == '.')
		q++;
	switch(q)
	{
		case 0: printf("error\n");return;break;
		case 1: break;
		case 2: printf("error\n");return;break;
		case 3: mov = (&Head);break;
		default: printf("error\n");return;break;
	}
	l = strlen(path);
	
	if(path[q] == '/') q++;
	
	else{
		printf("error\n");
		return;
	}
	p = q;
	
	while(q < l)
	{
		while(q < l && path[q] != '/') q++;
		strncpy(part, path + p, q - p);
		part[q - p] = '\0';
		mov = mov->son;
		flag == 0;
		while(mov)
		{
			if(strcmp(part, mov->name) != 0)//未找到，向兄弟查询 
			{
				mov = mov->sib;
			}
			else//找到，需要判断是否最后一项为文件，不是最后一项是否为文件夹 
			{
				if(q == l)//最后一项 
				{
					if(mov->isfile)//文件 
					{
						printf("%s\n",mov->content);
						return;
					}
					else
					{
						printf("error\n");
						return;
					}
				}
				else//不是最后一项，必须为文件夹 
				{
					if(mov->isfile)
					{
						printf("error\n");
						return;
					}
					else//是文件夹 ,退出循环，进入下一层 
					{
						flag = 1;
						break;
					}
				}
			}
		}
		if(flag == 0)//未找到对应文件，路径出错 
		{
			printf("error\n");
			return;
		}
		
		q++;
		p = q;
	}
	if(mov->isfile == 0)//如果找到，mov应该停留在文件上，若在文件夹上，则最后一个字符为/，此时需要报错 
	{
		printf("error\n");
		return;
	}
}

void tac()
{
	char path[50];
	char write[50];
	pFile mov = now;
	int p = 0,q = 0;//游标
	int l;//字符串长度
	int flag = 0;//路径是否正确 
	char part[20];//路径中截取的文件名
	scanf("%s",path);
	getchar();
	gets(write);
	while(path[q] == '.')
		q++;
	switch(q)
	{
		case 0: printf("error\n");return;break;
		case 1: break;
		case 2: printf("error\n");return;break;
		case 3: mov = (&Head);break;
		default: printf("error\n");return;break;
	}
	l = strlen(path);
	
	if(path[q] == '/') q++;
	
	else{
		printf("error\n");
		return;
	}
	p = q;
	
	while(q < l)
	{
		while(q < l && path[q] != '/') q++;
		strncpy(part, path + p, q - p);
		part[q - p] = '\0';
		mov = mov->son;
		flag == 0;
		while(mov)
		{
			if(strcmp(part, mov->name) != 0)//未找到，向兄弟查询 
			{
				mov = mov->sib;
			}
			else//找到，需要判断是否最后一项为文件，不是最后一项是否为文件夹 
			{
				if(q == l)//最后一项 
				{
					if(mov->isfile)//文件 
					{
						
						strcpy(mov->content,write);
						return;
					}
					else
					{
						printf("error\n");
						return;
					}
				}
				else//不是最后一项，必须为文件夹 
				{
					if(mov->isfile)
					{
						printf("error\n");
						return;
					}
					else//是文件夹 ,退出循环，进入下一层 
					{
						flag = 1;
						break;
					}
				}
			}
		}
		if(flag == 0)//未找到对应文件，路径出错 
		{
			printf("error\n");
			return;
		}
		
		q++;
		p = q;
	}
	if(mov->isfile == 0)//如果找到，mov应该停留在文件上，若在文件夹上，则最后一个字符为/，此时需要报错 
	{
		printf("error\n");
		return;
	}
}

void cd(char *path)
{
	pFile mov = now;
	int p = 0,q = 0;//游标
	int l;//字符串长度
	int flag = 0;//路径是否正确 
	char part[20];//路径中截取的文件名
	l = strlen(path);
	if(l == 0)
	{
		now = &(Head);
		return;
	}
	while(path[q] == ' ')//除去空格 
		q++;
	while(path[q] == '.')
	{
		q++;
		p++;
	}
	switch(p)
	{
		case 0: break;
		case 1: printf("error\n");return;break;
		case 2: {
			if(mov->father)
			{
				now = mov->father;return;break;
			}
			else
			{
				now = &(Head);return;break;
			}
		}
		case 3: mov = (&Head);break;
		default: printf("error\n");return;break;
	}
	
	
	if(path[q] == '/')
	{
		if(p == 3) q++;
		else
		{
			printf("error\n");return;
		}
	}
	p = q;
	
	while(q < l)
	{
		while(q < l && path[q] != '/') q++;
		strncpy(part, path + p, q - p);
		part[q - p] = '\0';
		mov = mov->son;
		flag == 0;
		while(mov)
		{
			if(strcmp(part, mov->name) != 0)//未找到，向兄弟查询 
			{
				mov = mov->sib;
			}
			else//找到，需要判断是否最为文件夹 
			{
				if(mov->isfile)
				{
					printf("error\n");
					return;
				}
				else//是文件夹 ,退出循环，进入下一层 
				{
					flag = 1;
					break;
				}
			}
		}
		if(flag == 0)//未找到对应文件，路径出错 
		{
			printf("error\n");
			return;
		}
		q++;
		p = q;
	}
	now = mov;
}

int main()
{
	char order[20];
	char path[50];
	int num; 
	init();
	scanf("%d",&num);
	while(num > 0)
	{
		scanf("%s",order);
		if(strcmp("cd",order) == 0)
		{
			gets(path);
			cd(path);
		}
		else if(strcmp("tac",order) == 0) tac();
		else if(strcmp("cat",order) == 0) cat();
		else if(strcmp("pwd",order) == 0) {
			pwd(now);printf("\n");
		}
		else if(strcmp("ls",order) == 0) ls();
		else if(strcmp("makdir",order) == 0) mkdir();
		else if(strcmp("touch",order) == 0) touch();
		else printf("error\n");
		num --;
	}
}
