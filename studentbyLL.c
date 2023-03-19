#include<stdio.h>
#include<stdlib.h>

struct stud{
    int roll_no;
    char name[20];
    float perc;
    struct stud *prev_link,*next_link;
}*start;

float GetPerc(){
    float perc;
    int p,c,m,b;
    P:
    printf("\n\nEnter Marks Obtained in Physics : ");
    scanf("%d",&p);
    if(p>100 || p<0){
        printf("\n\nInvalid marks...Please Enter marks out off 100 .");
        goto P;
    }
    C:
    printf("\n\nEnter Marks Obtained in Chemistry : ");
    scanf("%d",&c);
    if(c>100 || c<0){
        printf("\n\nInvalid marks...Please Enter marks out off 100 .");
        goto C;
    }
    M:
    printf("\n\nEnter Marks Obtained in Maths : ");
    scanf("%d",&m);
    if(m>100 || m<0){
        printf("\n\nInvalid marks...Please Enter marks out off 100 .");
        goto M;
    }
    B:
    printf("\n\nEnter Marks Obtained in Biology : ");
    scanf("%d",&b);
    if(b>100 || b<0){
        printf("\n\nInvalid marks...Please Enter marks out off 100 .");
        goto B;
    }

    perc = (p+c+m+b)/4;
    printf("\n\nYour Percentage is : %0.2f",perc);
    return perc;
}

void AddStud(){ 
    struct stud *new,*curr;
    new=malloc(sizeof(struct stud));
    printf("\n\nEnter Roll Number of student : ");
    scanf("%d",&new->roll_no);
    printf("\n\nEnter Name of student : ");
    scanf("%s",new->name);

    new->perc=GetPerc();

    if(start==NULL){
        start=new;
        new->next_link=NULL;
        new->prev_link=NULL;
    }else{
        if(new->perc>start->perc){          // code to adding student at rank 1
            new->prev_link=NULL;
            new->next_link=start;
            start->prev_link=new;
            start=new;
        }else{
            curr=start;
            while(new->perc<curr->perc){
                if(curr->next_link==NULL){
                    break;
                }else{
                    curr=curr->next_link;
                }
            }
            if(curr->perc<new->perc){
                curr=curr->prev_link;
            }
            if(curr->next_link==NULL){          // code to add last ranking student
                curr->next_link=new;
                new->next_link=NULL;
                new->prev_link=curr;
            }else{                              // code to add student at middle of the list
                new->next_link=curr->next_link;
                new->prev_link=curr;
                curr->next_link=new;
                new->next_link->prev_link=new;
            }
        }
    }

}

void Display(){
    struct stud *curr;
    if(start==NULL){
        printf("\n\nNo student in record.");
    }else{
        curr=start;
        int rank=1;
        while(curr!=NULL){
            printf("\n\n----------Student at Rank %d----------\n\nRoll Number : %d\nName : %s\nPercentage : %0.2f\n\n-------------------------------------",rank,curr->roll_no,curr->name,curr->perc);
            curr=curr->next_link;
            rank++;
        }
    }
}

void DelStud(int r){
    // r => roll number of sttudent to be deleted

    struct stud *curr,*temp;
    if(start->roll_no==r){         // code to delete first student 
        temp=start;
        start=start->next_link;
        start->prev_link=NULL;
        free(temp);
    }else{
        curr=start;
        while(curr->roll_no!=r){
            curr=curr->next_link;
        }
        if(curr->next_link==NULL){      // code to delete last student 
            curr->prev_link->next_link=NULL;
            free(curr);
        }else{   
            curr->prev_link->next_link=curr->next_link;
            curr->next_link->prev_link=curr->prev_link;
            free(curr);
        }
    }

}   

void GetResult(int r){
    // r => roll number of student 
    struct stud *curr;
    int rank=1;
    curr=start;
    while(curr->roll_no!=r){
        curr=curr->next_link;
        rank++;
    }
    printf("\n\n*======================*RESULT*======================*\n\nName : %s\nRoll Number : %d\nPercentage : %0.2f\nRank : %d",curr->name,curr->roll_no,curr->perc,rank);
    if(curr->perc>=35){
        printf("\n\nCONGRATULATIONS, %s !!!\nYou Passed eith rank %d.\n\n*====================================================*",curr->name,rank);
    }else{
        printf("\n\nBETTER LUCK NEXT TIME...\nYou failed Exam with percentage %0.2f\n\n*====================================================*",curr->perc);
    }
}

int main(){

    int ch,r;
    // r => roll number input
    start=NULL;

    

    do{

        printf("\n\nMenus:\n\n1.Add student\n2.Display Student List\n3.Delete student\n4.Get Result of student\n\nEnter your choice : ");
        scanf("%d",&ch);

        switch(ch){

            case 1:

                AddStud();
                break;

            case 2:

                printf("\n\nSTUDENT LIST =>");
                Display();
                break;

            case 3:

                printf("\n\nEnter Roll Number of student to be deleted : ");
                scanf("%d",&r);
                DelStud(r);
                break;

            case 4:

                printf("\n\nEnter Roll Number of student for result : ");
                scanf("%d",&r);
                GetResult(r);

                break;

            default:

                printf("\n\nInvalid Choice...");

        }

        printf("\n\nPress 1 to continue : ");
        scanf("%d",&ch);

    }while(ch==1);

    return 0;
}