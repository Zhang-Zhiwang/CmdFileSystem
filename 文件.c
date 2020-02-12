#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct FileNode{
	char name[10];//�ļ��� 
	char faname[10];//�ϲ��ļ����� 
	char content[10];//�ļ����� 
	struct FileNode* father;//ָ���ϲ��ļ��� 
	struct FileNode* sib;//ָ��ͬһ���ļ� 
	struct FileNode* son;//ָ�����ļ� 
	int isfile;//�ж��ļ��л����ļ� ,��Ϊ�ļ�����Ϊ�ļ��� 
}FileNode,*pFile; 

FileNode Head;//���ڵ� 
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

void pwd(pFile p)//ʹ��ʱpwd��now�� 
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
	if(flag == 0)//֮ǰ�Ѿ������ļ������ļ��� 
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
	if(flag == 0)//֮ǰ�Ѿ������ļ������ļ��� 
		p->sib = q;
	memset(q->content,'\0',sizeof(q->content));
}

void cat()
{
	char path[50];
	pFile mov = now;
	int p = 0,q = 0;//�α�
	int l;//�ַ�������
	int flag = 0;//·���Ƿ���ȷ 
	char part[20];//·���н�ȡ���ļ���
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
			if(strcmp(part, mov->name) != 0)//δ�ҵ������ֵܲ�ѯ 
			{
				mov = mov->sib;
			}
			else//�ҵ�����Ҫ�ж��Ƿ����һ��Ϊ�ļ����������һ���Ƿ�Ϊ�ļ��� 
			{
				if(q == l)//���һ�� 
				{
					if(mov->isfile)//�ļ� 
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
				else//�������һ�����Ϊ�ļ��� 
				{
					if(mov->isfile)
					{
						printf("error\n");
						return;
					}
					else//���ļ��� ,�˳�ѭ����������һ�� 
					{
						flag = 1;
						break;
					}
				}
			}
		}
		if(flag == 0)//δ�ҵ���Ӧ�ļ���·������ 
		{
			printf("error\n");
			return;
		}
		
		q++;
		p = q;
	}
	if(mov->isfile == 0)//����ҵ���movӦ��ͣ�����ļ��ϣ������ļ����ϣ������һ���ַ�Ϊ/����ʱ��Ҫ���� 
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
	int p = 0,q = 0;//�α�
	int l;//�ַ�������
	int flag = 0;//·���Ƿ���ȷ 
	char part[20];//·���н�ȡ���ļ���
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
			if(strcmp(part, mov->name) != 0)//δ�ҵ������ֵܲ�ѯ 
			{
				mov = mov->sib;
			}
			else//�ҵ�����Ҫ�ж��Ƿ����һ��Ϊ�ļ����������һ���Ƿ�Ϊ�ļ��� 
			{
				if(q == l)//���һ�� 
				{
					if(mov->isfile)//�ļ� 
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
				else//�������һ�����Ϊ�ļ��� 
				{
					if(mov->isfile)
					{
						printf("error\n");
						return;
					}
					else//���ļ��� ,�˳�ѭ����������һ�� 
					{
						flag = 1;
						break;
					}
				}
			}
		}
		if(flag == 0)//δ�ҵ���Ӧ�ļ���·������ 
		{
			printf("error\n");
			return;
		}
		
		q++;
		p = q;
	}
	if(mov->isfile == 0)//����ҵ���movӦ��ͣ�����ļ��ϣ������ļ����ϣ������һ���ַ�Ϊ/����ʱ��Ҫ���� 
	{
		printf("error\n");
		return;
	}
}

void cd(char *path)
{
	pFile mov = now;
	int p = 0,q = 0;//�α�
	int l;//�ַ�������
	int flag = 0;//·���Ƿ���ȷ 
	char part[20];//·���н�ȡ���ļ���
	l = strlen(path);
	if(l == 0)
	{
		now = &(Head);
		return;
	}
	while(path[q] == ' ')//��ȥ�ո� 
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
			if(strcmp(part, mov->name) != 0)//δ�ҵ������ֵܲ�ѯ 
			{
				mov = mov->sib;
			}
			else//�ҵ�����Ҫ�ж��Ƿ���Ϊ�ļ��� 
			{
				if(mov->isfile)
				{
					printf("error\n");
					return;
				}
				else//���ļ��� ,�˳�ѭ����������һ�� 
				{
					flag = 1;
					break;
				}
			}
		}
		if(flag == 0)//δ�ҵ���Ӧ�ļ���·������ 
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
