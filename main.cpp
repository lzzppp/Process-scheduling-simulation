#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<iostream>
using namespace std;

typedef struct PCB{
	char name[100];
	int priority; 
	int children_num;
	PCB *parent;
	PCB *children[20];
	
} PCB;

typedef struct ListNode
{
    PCB *pcb;
    ListNode *next;
} Linked_list;

typedef struct ListNodercb 
{
    PCB *pcb;
    ListNodercb *next;
	ListNodercb *last;
} Linked_list_rcb;

typedef struct head_ListNode
{
    int priority_head;
    ListNode *next_same_priority;
    head_ListNode *next_priority_head;
    head_ListNode *last_priority_head;
} Linked_list_head;

typedef struct RCB{
	char name[20];
	int all;
	int reset;
	Linked_list_rcb *head; 
} RCB;

char *delblank(char *a)
{
	int i, j;
    int count = 0;
    for (i = 0, j = 0; a[i]; i++)
    {
        if (a[i] == ' '){
            count++;
        }else{
            a[j++] = a[i];
        }       
    }
    a[j] = '\0';
}

PCB *get_running_process(Linked_list_head *hhdd)
{
	Linked_list_head *hhhhh = hhdd;
	while(hhhhh != NULL)
	{
		Linked_list *jie = hhhhh->next_same_priority;
		if(jie != NULL)
		{
			return jie->pcb;
		}
		hhhhh = hhhhh->next_priority_head;
	}
	cout << "no process !!! creat !!!";
}

int is_begin_with(char *str1, char *str2)
{
    if(str1 == NULL || str2 == NULL)
        return -1;
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    if((len1 < len2) ||  (len1 == 0 || len2 == 0))
        return -1;
    char *p = str2;
    int i = 0;
    while(*p != '\0')
    {
        if(*p != str1[i])
            return 0;
        p++;
        i++;
    }
    return 1;
}

void display_ready_process(Linked_list_head *hdd)
{
	cout << "\n";
	Linked_list_head *hd=hdd;
	while(hd != NULL)
	{
		cout << "#######################"<< "priority : " << hd->priority_head <<"#######################" << endl; 
		Linked_list *jie = hd->next_same_priority;
		cout << "name_list : ";
		while(jie != NULL)
		{
			cout << jie->pcb->name << " ";
			jie = jie->next;
		}
		cout << "\n";
		cout << "##########################################################\n" << endl; 
		hd = hd->next_priority_head;
	}
}

Linked_list_head *if_have_priority(Linked_list_head *hh, int piro)
{
	Linked_list_head *h = hh;
	while(h != NULL)
	{
		if(h->priority_head==piro)
		{
			return h;
		}
		h = h->next_priority_head;
	}
	return NULL;
}

int del_ready_process(Linked_list_head *hhhh, int prioo, char *na)
{
	Linked_list_head *hhd=hhhh;
	while(hhd != NULL)
	{
		if(hhd->priority_head==prioo)
		{
		Linked_list *jie = hhd->next_same_priority;
		if(strcmp(jie->pcb->name, na)==0)
		{
			hhd->next_same_priority = jie->next;
			return 1;
		}
		while(jie -> next != NULL)
		{
			if(strcmp(jie->next->pcb->name, na)==0)
			{
				jie->next = jie->next->next;
				return 1;
			}
			jie = jie->next;
		}
		}
		hhd = hhd->next_priority_head;
	}
	return -1;
}

Linked_list_head *create_priority_head(Linked_list_head *hhh, int piroo)
{
	Linked_list_head *hh=hhh;
	if(hh->priority_head==-1)
	{
		hh->priority_head = piroo;
		return hh;
	}
	Linked_list_head *last_hh;
	while(hh != NULL)
	{
		if(piroo < hh->priority_head)
		{
			Linked_list_head *new_hh;
			new_hh = new head_ListNode;
			new_hh->priority_head = piroo;
			new_hh->next_priority_head = hh;
			new_hh->last_priority_head = hh->last_priority_head;
			if(new_hh->last_priority_head != NULL)
			{new_hh->last_priority_head->next_priority_head = new_hh;}
			new_hh->next_priority_head->last_priority_head = new_hh;
			return new_hh;
		}
		if(hh->next_priority_head==NULL)
		{
			last_hh = hh;
			hh = hh->next_priority_head;
		}
		else
		{hh = hh->next_priority_head;}
	}
	Linked_list_head *new_hh;
	new_hh = new head_ListNode;
	new_hh->priority_head = piroo;
	new_hh->next_priority_head = NULL;
	new_hh->last_priority_head = last_hh;
	last_hh->next_priority_head = new_hh;
	return new_hh;
}

Linked_list_rcb *insert_runing_pcb_to_rcb_blocked_query(Linked_list_rcb *block_head_rcb, PCB *run_pcb)
{
	Linked_list_rcb *bhr=block_head_rcb;
	if(bhr->pcb->priority==-1)
	{
		bhr->pcb = run_pcb;
		return bhr;
	}
	Linked_list_rcb *last_hhh;
	while(bhr != NULL)
	{
		if(run_pcb->priority < bhr->pcb->priority)
		{
			Linked_list_rcb *new_hhh;
			new_hhh = new ListNodercb;
			new_hhh->pcb = run_pcb;
			new_hhh->next = bhr;
			new_hhh->last = bhr->last;
			if(new_hhh->last != NULL)
			{new_hhh->last->next = new_hhh;}
			new_hhh->next->last = new_hhh;
			return new_hhh;
		}
		if(bhr->next==NULL)
		{
			last_hhh = bhr;
			bhr = bhr->next;
		}
		else
		{bhr = bhr->next;}
	}
	Linked_list_rcb *new_hhh;
	new_hhh = new ListNodercb;
	new_hhh->pcb = run_pcb;
	new_hhh->next = NULL;
	new_hhh->last = last_hhh;
	last_hhh->next = new_hhh;
	return new_hhh;
}

void display_rcb_list(Linked_list_rcb *block_head_head, RCB rcblist[])
{
	Linked_list_rcb *bhh;
	bhh = new ListNodercb;
	bhh = block_head_head;
	int idx=0;
	while(bhh != NULL)
	{
		cout << "Blocked " << rcblist[idx].name << " List: " << bhh->pcb->name << "\n";
		idx += 1;
		bhh = bhh->next;
	}
}

int main()
{	
	PCB *all_process_list[1000];
    // #### 初始化就绪队列 ######
	int process_num=0; 
	int runing_num=0;
	int pir_idx=-1;
	int children_num=0;
	Linked_list_head *head;
	head = new head_ListNode;
	head->next_priority_head = NULL;
	head->last_priority_head = NULL;
	head->priority_head = -1;
	Linked_list_head *head_store=head;
	// ########################## 
	// ##### 初始化运行程序 ##### 
	PCB *runing_pcb;
	runing_pcb = new PCB;
	// ########################## 
	// ##### 初始化资源队列 ##### 
	RCB all_resource[20];
	Linked_list_rcb *all_resource_head[20];
	// ########################## 
	
	int if_init=1;
	int resource_number=0;
    char op[1000];
    char init[20] = "init"; 
    char cr[20] = "test-cr";
    char de[20] = "test-de";
    char req[20] = "test-req";
	char rel[20] = "test-rel";
	char to[20] = "test-to";
	char list_all_pcb[40] = "test-listallprocessesandtheirstatus";
	cout << "User_name:";
    cin.getline(op, 19);
    while(strcmp(op, "out") != 0)
    {
    	if(if_init==1){
    		cout << "C:\\User:";
    		if_init=0;
		}
        cin.getline(op, 1000);
        delblank(op);
        Linked_list_head *head_same;
		head_same = new head_ListNode;
		Linked_list_rcb *head_rcb_same;
		head_rcb_same = new ListNodercb;
        if(is_begin_with(op, cr) == 1)
        {
       	    if(runing_num==0)
       	    {
       	    	process_num += 1;
	       	    for(int f=7; f<strlen(op); f++)
	       	    {
	       	    	if('0' <= op[f] && op[f] <= '9')
	       	    	{
	       	    		pir_idx=f;
	       	    		break; 
					   }
				   }
				char name[100]={};
				char pri_str[100]={};
				*name='\0';
				*pri_str='\0';
				int priority=-1;
				int n_idx=0, p_idx=0;
				for(int i=7; i<pir_idx; i++)
				{
					name[n_idx]=op[i];
					n_idx += 1;
				}
				for(int i=pir_idx; i < strlen(op); i++)
				{
					pri_str[p_idx]=op[i];
					p_idx += 1; 
				}
				priority=atoi(pri_str);
				PCB *process;
				process = new PCB;
				process->children_num=0;
				if(if_have_priority(head_store, priority)!=NULL)
				{
					head_same = if_have_priority(head_store, priority);
					*(process->name) = '\0';
					strcpy(process->name, name);
					process->priority = priority;
					Linked_list *new_head;
					new_head = new ListNode;
					new_head->pcb = process;
					new_head->next = NULL;
					new_head->next = head_same->next_same_priority;
					head_same->next_same_priority = new_head;
				}
				else
				{
					head_same = create_priority_head(head_store, priority);
					*(process->name) = '\0';
					strcpy(process->name, name);
					process->priority = priority;
					Linked_list *new_head;
					new_head = new ListNode;
	                new_head->pcb = process;
					new_head->next = NULL;
					head_same->next_same_priority = new_head;
					if(head_same->priority_head < head_store->priority_head)
					{
						head_store = head_same;
					 } 
				}
				all_process_list[process_num - 1] = process;
				while(head_same->last_priority_head!=NULL)
				{
					head_same = head_same->last_priority_head;
				}
				display_ready_process(head_same);
				   }
		else
		{
			process_num += 1;
       	    for(int f=7; f<strlen(op); f++)
       	    {
       	    	if('0' <= op[f] && op[f] <= '9')
       	    	{
       	    		pir_idx=f;
       	    		break; 
				   }
			   }
			char name[100]={};
			char pri_str[100]={};
			*name='\0';
			*pri_str='\0';
			int priority=-1;
			int n_idx=0, p_idx=0;
			for(int i=7; i<pir_idx; i++)
			{
				name[n_idx]=op[i];
				n_idx += 1;
			}
			for(int i=pir_idx; i < strlen(op); i++)
			{
				pri_str[p_idx]=op[i];
				p_idx += 1; 
			}
			priority=atoi(pri_str);
			PCB *process;
			process = new PCB;
			*(process->name) = '\0';
			strcpy(process->name, name);
			process->priority = priority;
			runing_pcb->children[runing_pcb->children_num] = new PCB;
			runing_pcb->children[runing_pcb->children_num] = process;
//			strcpy(runing_pcb.children[runing_pcb.children_num]->parent.name, process.name);
//			runing_pcb.children[runing_pcb.children_num]->parent.priority = process.priority;
			runing_pcb->children_num += 1;
			process->parent = runing_pcb;
			cout << runing_pcb->name << " child : \n";
			int child_idx = 1;
			int child_num = runing_pcb->children_num;
			while(child_num != 0)
			{
				cout << "Child " << child_idx << " " << runing_pcb->children[child_num - 1]->name << "\n";
				child_idx += 1;
				child_num -= 1;
			}
			all_process_list[process_num - 1] = process;
		}
	   }
	   else if(is_begin_with(op, de) == 1)
        {
       	    if(runing_num==0)
       	    {
       	    process_num -= 1;
			char name[100]={};
			*name='\0';
			int n_idx=0;
			for(int i=7; i<strlen(op); i++)
			{
				name[n_idx]=op[i];
				n_idx += 1;
			}
			int priority_idx=-1;
			for(int i=0; i<process_num+1; i++)
			{
				if(strcmp(all_process_list[i]->name, name)==0)
				{
					priority_idx=all_process_list[i]->priority;
					for(int j=i; j<process_num; j++)
					{
						all_process_list[j]=all_process_list[j + 1];
					}
					break;
				}
			}		
			if(priority_idx==-1)
			{
				cout << "No this process!!!! \n";
			}
			else
			{
				int flag=0;
				while(head_store->last_priority_head!=NULL)
				{
					head_store = head_store->last_priority_head;
				}
				flag = del_ready_process(head_store, priority_idx, name);
				while(head_store->last_priority_head!=NULL)
				{
					head_store = head_store->last_priority_head;
				}
				display_ready_process(head_store);
			}
			   }
			else{
				process_num -= 1;
			    char name[100]={};
			    *name='\0';
			    int n_idx=0;
			    for(int i=7; i<strlen(op); i++)
			    {
				    name[n_idx]=op[i];
				    n_idx += 1;
			    }
			    if(strcmp(runing_pcb->name, name)==0)
			    {
			    	PCB *runing_pcb;
	                runing_pcb = new PCB;
				}
				else
				{
					int child_num = runing_pcb->children_num;
					while(child_num != 0)
					{
						if(strcmp(runing_pcb->children[child_num - 1]->name, name))
						{
							for(int j=child_num-1; j<runing_pcb->children_num; j++)
							{
								runing_pcb->children[j]=runing_pcb->children[j + 1];
							}
							runing_pcb->children_num -= 1;
							break;
						}
						child_num -= 1;
					}
					cout << runing_pcb->name << " child : \n";
					int child_idx = 1;
					child_num = runing_pcb->children_num;
					while(child_num != 0)
					{
						cout << "Child " << child_idx << " " << runing_pcb->children[child_num - 1]->name << "\n";
						child_idx += 1;
						child_num -= 1;
					}
				}
			}
	   }
	   else if(is_begin_with(op, init) == 1)
        {
       	    cout << "Resource number what's you want init: \n";
       	    scanf("%d", &resource_number);
       	    for(int i=0; i< resource_number; i++)
       	    {
//       	    	scanf("%s %d", all_resource[i].name, &all_resource[i].all);
       	    	cin >> all_resource[i].name >> all_resource[i].all;
       	    	all_resource[i].reset = all_resource[i].all;
       	    	all_resource[i].head = new ListNodercb;
       	    	all_resource[i].head->last = NULL;
       	    	all_resource[i].head->next = NULL;
       	    	all_resource[i].head->pcb = new PCB;
       	    	all_resource[i].head->pcb->priority = -1;
       	    	all_resource_head[i] = all_resource[i].head;
			   }
	   }
	   else if(is_begin_with(op, req) == 1)
        {
       	    if(process_num != 0 && runing_num == 0)
			{
				while(head_store->last_priority_head!=NULL)
				{
					head_store = head_store->last_priority_head;
				}
				runing_pcb = get_running_process(head_store);
				runing_pcb->children_num = 0;
				del_ready_process(head_store, runing_pcb->priority, runing_pcb->name);
				runing_num = 1;
			}
       	    int req_i=-1;
       	    runing_num = 1;
			for(int f=8; f<strlen(op); f++)
       	    {
       	    	if('0' <= op[f] && op[f] <= '9')
       	    	{
       	    		pir_idx=f;
       	    		break; 
				   }
			   }
			char name[100]={};
			char pri_str[100]={};
			*name='\0';
			*pri_str='\0';
			int req_num=-1;
			int n_idx=0, p_idx=0;
			for(int i=8; i<pir_idx; i++)
			{
				name[n_idx]=op[i];
				n_idx += 1;
			}
			for(int i=pir_idx; i < strlen(op); i++)
			{
				pri_str[p_idx]=op[i];
				p_idx += 1; 
			}
			req_num=atoi(pri_str);
			if(runing_num != 0)
			{
				for(int i=0; i< resource_number; i++)
				{
					if(strcmp(all_resource[i].name, name)==0)
					{
						req_i = i;
						break;
					}
				}
				if(req_num <= all_resource[req_i].reset)
				{
					cout << "Runing " << runing_pcb->name << " using " << req_num << " " << all_resource[req_i].name << "\n";
					all_resource[req_i].reset -= req_num;
				}
				else
				{
					cout << "Runing " << runing_pcb->name << " using " << req_num << " " << all_resource[req_i].name << " failed" << "\n";
					head_rcb_same = insert_runing_pcb_to_rcb_blocked_query(all_resource_head[req_i], runing_pcb);
					if(head_rcb_same->pcb->priority < all_resource_head[req_i]->pcb->priority)
				    {
					    all_resource_head[req_i] = head_rcb_same;
				    } 
				    while(all_resource_head[req_i]->last!=NULL)
					{	
						all_resource_head[req_i] = all_resource_head[req_i]->last;
					}
					display_rcb_list(all_resource_head[req_i], all_resource);
					runing_num=0;
				}
			}
	   }
	   else if(is_begin_with(op, rel) == 1)
        {
       	    process_num += 1;
       	    if(runing_num==1)
       	    {
       	    	while(runing_pcb->children_num != 0)
       	    	{
       	    		process_num += 1;
	   	    		char name[20];
	   	    		*name='\0';
	   	    		int priority = runing_pcb->children[runing_pcb->children_num - 1]->priority;
	   	    		strcpy(name, runing_pcb->children[runing_pcb->children_num - 1]->name);
	   	    		PCB *process;
	   	    		process = new PCB;
					if(if_have_priority(head_store, priority)!=NULL)
					{
						head_same = if_have_priority(head_store, priority);
						*(process->name) = '\0';
						strcpy(process->name, name);
						process->priority = priority;
						Linked_list *new_head;
						new_head = new ListNode;
						new_head->pcb = process;
						new_head->next = NULL;
						new_head->next = head_same->next_same_priority;
						head_same->next_same_priority = new_head;
					}
					else
					{
						head_same = create_priority_head(head_store, priority);
						*(process->name) = '\0';
						strcpy(process->name, name);
						process->priority = priority;
						Linked_list *new_head;
						new_head = new ListNode;
		                new_head->pcb = process;
						new_head->next = NULL;
						head_same->next_same_priority = new_head;
						if(head_same->priority_head < head_store->priority_head)
						{
							head_store = head_same;
						 } 
					}
				   runing_pcb->children_num -= 1;
				   }
				process_num += 1;
   	    		char name[20];
   	    		*name='\0';
   	    		int priority = runing_pcb->priority;
   	    		strcpy(name, runing_pcb->name);
   	    		PCB *process;
   	    		process = new PCB;
				if(if_have_priority(head_store, priority)!=NULL)
				{
					head_same = if_have_priority(head_store, priority);
					*(process->name) = '\0';
					strcpy(process->name, name);
					process->priority = priority;
					Linked_list *new_head;
					new_head = new ListNode;
					new_head->pcb = process;
					new_head->next = NULL;
					new_head->next = head_same->next_same_priority;
					head_same->next_same_priority = new_head;
				}
				else
				{
					head_same = create_priority_head(head_store, priority);
					*(process->name) = '\0';
					strcpy(process->name, name);
					process->priority = priority;
					Linked_list *new_head;
					new_head = new ListNode;
	                new_head->pcb = process;
					new_head->next = NULL;
					head_same->next_same_priority = new_head;
					if(head_same->priority_head < head_store->priority_head)
					{
						head_store = head_same;
					 } 
				}
				for(int i=0; i< resource_number; i++)
       	    	{all_resource[i].reset = all_resource[i].all;}
				runing_num=0;
			   }
			else
			{
            for(int i=0; i< resource_number; i++)
       	    {
       	    	all_resource[i].reset = all_resource[i].all;
       	    	while(all_resource[i].head != NULL && all_resource[i].head->pcb->priority != -1)
       	    	{
       	    		while(all_resource[i].head->pcb->children_num != 0)
       	    	{
       	    		process_num += 1;
	   	    		char name[20];
	   	    		*name='\0';
	   	    		int priority = all_resource[i].head->pcb->children[all_resource[i].head->pcb->children_num]->priority;
	   	    		strcpy(name, all_resource[i].head->pcb->children[all_resource[i].head->pcb->children_num]->name);
	   	    		PCB *process;
	   	    		process = new PCB;
					if(if_have_priority(head_store, priority)!=NULL)
					{
						head_same = if_have_priority(head_store, priority);
						*(process->name) = '\0';
						strcpy(process->name, name);
						process->priority = priority;
						Linked_list *new_head;
						new_head = new ListNode;
						new_head->pcb = process;
						new_head->next = NULL;
						new_head->next = head_same->next_same_priority;
						head_same->next_same_priority = new_head;
					}
					else
					{
						head_same = create_priority_head(head_store, priority);
						*(process->name) = '\0';
						strcpy(process->name, name);
						process->priority = priority;
						Linked_list *new_head;
						new_head = new ListNode;
		                new_head->pcb = process;
						new_head->next = NULL;
						head_same->next_same_priority = new_head;
						if(head_same->priority_head < head_store->priority_head)
						{
							head_store = head_same;
						 } 
					}
					all_process_list[process_num - 1] = process;
				   all_resource[i].head->pcb->children_num -= 1;
				   }
				process_num += 1;
   	    		char name[20];
   	    		*name='\0';
   	    		int priority = all_resource[i].head->pcb->priority;
   	    		strcpy(name, all_resource[i].head->pcb->name);
   	    		PCB *process;
   	    		process = new PCB;
				if(if_have_priority(head_store, priority)!=NULL)
				{
					head_same = if_have_priority(head_store, priority);
					*(process->name) = '\0';
					strcpy(process->name, name);
					process->priority = priority;
					Linked_list *new_head;
					new_head = new ListNode;
					new_head->pcb = process;
					new_head->next = NULL;
					new_head->next = head_same->next_same_priority;
					head_same->next_same_priority = new_head;
				}
				else
				{
					head_same = create_priority_head(head_store, priority);
					*(process->name) = '\0';
					strcpy(process->name, name);
					process->priority = priority;
					Linked_list *new_head;
					new_head = new ListNode;
	                new_head->pcb = process;
					new_head->next = NULL;
					head_same->next_same_priority = new_head;
					if(head_same->priority_head < head_store->priority_head)
					{
						head_store = head_same;
					 } 
				}
			    all_process_list[process_num - 1] = process;
       	    	all_resource[i].head = all_resource[i].head->next;
       	    	if(all_resource[i].head != NULL)
       	    	{all_resource[i].head->last = NULL;}
				}
       	    }
	   }
	        while(head_same->last_priority_head!=NULL)
			{
				head_same = head_same->last_priority_head;
			}
			display_ready_process(head_same);
		runing_num=0;}
       else if(is_begin_with(op, to) == 1)
        {
       	    process_num += 1;
       	    if(runing_num==1)
       	    {
       	    	while(runing_pcb->children_num != 0)
       	    	{
       	    		process_num += 1;
	   	    		char name[20];
	   	    		*name='\0';
	   	    		int priority = runing_pcb->children[runing_pcb->children_num - 1]->priority;
	   	    		strcpy(name, runing_pcb->children[runing_pcb->children_num - 1]->name);
	   	    		PCB *process;
	   	    		process = new PCB;
					if(if_have_priority(head_store, priority)!=NULL)
					{
						head_same = if_have_priority(head_store, priority);
						*(process->name) = '\0';
						strcpy(process->name, name);
						process->priority = priority;
						Linked_list *new_head;
						new_head = new ListNode;
						new_head->pcb = process;
						new_head->next = NULL;
						new_head->next = head_same->next_same_priority;
						head_same->next_same_priority = new_head;
					}
					else
					{
						head_same = create_priority_head(head_store, priority);
						*(process->name) = '\0';
						strcpy(process->name, name);
						process->priority = priority;
						Linked_list *new_head;
						new_head = new ListNode;
		                new_head->pcb = process;
						new_head->next = NULL;
						head_same->next_same_priority = new_head;
						if(head_same->priority_head < head_store->priority_head)
						{
							head_store = head_same;
						 } 
					}
				   runing_pcb->children_num -= 1;
				   }
				process_num += 1;
   	    		char name[20];
   	    		*name='\0';
   	    		int priority = runing_pcb->priority;
   	    		strcpy(name, runing_pcb->name);
   	    		PCB *process;
   	    		process = new PCB;
				if(if_have_priority(head_store, priority)!=NULL)
				{
					head_same = if_have_priority(head_store, priority);
					*(process->name) = '\0';
					strcpy(process->name, name);
					process->priority = priority;
					Linked_list *new_head;
					new_head = new ListNode;
					new_head->pcb = process;
					new_head->next = NULL;
					new_head->next = head_same->next_same_priority;
					head_same->next_same_priority = new_head;
				}
				else
				{
					head_same = create_priority_head(head_store, priority);
					*(process->name) = '\0';
					strcpy(process->name, name);
					process->priority = priority;
					Linked_list *new_head;
					new_head = new ListNode;
	                new_head->pcb = process;
					new_head->next = NULL;
					head_same->next_same_priority = new_head;
					if(head_same->priority_head < head_store->priority_head)
					{
						head_store = head_same;
					 } 
				}
				for(int i=0; i< resource_number; i++)
       	    	{all_resource[i].reset = all_resource[i].all;}
				runing_num=0;
			   }
			else
			{
            for(int i=0; i< resource_number; i++)
       	    {
       	    	all_resource[i].reset = all_resource[i].all;
       	    	while(all_resource[i].head != NULL && all_resource[i].head->pcb->priority != -1)
       	    	{
       	    		while(all_resource[i].head->pcb->children_num != 0)
       	    	{
       	    		process_num += 1;
	   	    		char name[20];
	   	    		*name='\0';
	   	    		int priority = all_resource[i].head->pcb->children[all_resource[i].head->pcb->children_num]->priority;
	   	    		strcpy(name, all_resource[i].head->pcb->children[all_resource[i].head->pcb->children_num]->name);
	   	    		PCB *process;
	   	    		process = new PCB;
					if(if_have_priority(head_store, priority)!=NULL)
					{
						head_same = if_have_priority(head_store, priority);
						*(process->name) = '\0';
						strcpy(process->name, name);
						process->priority = priority;
						Linked_list *new_head;
						new_head = new ListNode;
						new_head->pcb = process;
						new_head->next = NULL;
						new_head->next = head_same->next_same_priority;
						head_same->next_same_priority = new_head;
					}
					else
					{
						head_same = create_priority_head(head_store, priority);
						*(process->name) = '\0';
						strcpy(process->name, name);
						process->priority = priority;
						Linked_list *new_head;
						new_head = new ListNode;
		                new_head->pcb = process;
						new_head->next = NULL;
						head_same->next_same_priority = new_head;
						if(head_same->priority_head < head_store->priority_head)
						{
							head_store = head_same;
						 } 
					}
					all_process_list[process_num - 1] = process;
				   all_resource[i].head->pcb->children_num -= 1;
				   }
				process_num += 1;
   	    		char name[20];
   	    		*name='\0';
   	    		int priority = all_resource[i].head->pcb->priority;
   	    		strcpy(name, all_resource[i].head->pcb->name);
   	    		PCB *process;
   	    		process = new PCB;
				if(if_have_priority(head_store, priority)!=NULL)
				{
					head_same = if_have_priority(head_store, priority);
					*(process->name) = '\0';
					strcpy(process->name, name);
					process->priority = priority;
					Linked_list *new_head;
					new_head = new ListNode;
					new_head->pcb = process;
					new_head->next = NULL;
					new_head->next = head_same->next_same_priority;
					head_same->next_same_priority = new_head;
				}
				else
				{
					head_same = create_priority_head(head_store, priority);
					*(process->name) = '\0';
					strcpy(process->name, name);
					process->priority = priority;
					Linked_list *new_head;
					new_head = new ListNode;
	                new_head->pcb = process;
					new_head->next = NULL;
					head_same->next_same_priority = new_head;
					if(head_same->priority_head < head_store->priority_head)
					{
						head_store = head_same;
					 } 
				}
			    all_process_list[process_num - 1] = process;
       	    	all_resource[i].head = all_resource[i].head->next;
       	    	if(all_resource[i].head != NULL)
       	    	{all_resource[i].head->last = NULL;}
				}
       	    }
	   }
	        while(head_same->last_priority_head!=NULL)
			{
				head_same = head_same->last_priority_head;
			}
			display_ready_process(head_same);
		runing_num=0;}
	   else if(is_begin_with(op, list_all_pcb) == 1)
	   {
	   	    cout << "Ready!!!";
	        while(head_store->last_priority_head!=NULL)
			{
				head_store = head_store->last_priority_head;
			}
			display_ready_process(head_store);
			if(runing_num==1)
			{
				cout << "Runing \n";
				cout << runing_pcb->name << "\n";
				int child_idx = 1;
				int child_num = runing_pcb->children_num;
				while(child_num != 0)
				{
					cout << runing_pcb->name << " child : \n";
					cout << "Child " << child_idx << " " << runing_pcb->children[child_num - 1]->name << "\n";
					child_idx += 1;
					child_num -= 1;
				}
			}
			for(int i=0; i< resource_number; i++)
			{
				if(all_resource[i].head->pcb->priority != -1)
				{
					while(all_resource_head[i]->last!=NULL)
					{	
						all_resource_head[i] = all_resource_head[i]->last;
					}
					display_rcb_list(all_resource_head[i], all_resource);
				}
			}	
	   }
		if_init=1;
	}
    cout<<"RETURN END"<<endl;
    return 0;
}
