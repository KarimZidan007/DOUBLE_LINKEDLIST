/*
*@author -> Karim_Zidan
*@LinkedIn->https://www.linkedin.com/in/karim-zidan-24a81a1b2/
*/
#include <stdio.h>
#include <stdlib.h>
/***type definition section*/
typedef unsigned int uint32_t;
typedef unsigned short uint16_t;
typedef unsigned char  uint8_t;
/*************************/
struct Node
{
    uint32_t Data ;
    struct Node *Left_Node_Link;
    struct Node *Right_Node_Link;
};


enum status
{
    STATUS_OK,
    STATUS_NOT_OK,
    LIST_EMPTY
};
/***********variable decleration section*******/
typedef enum status Std_Return ;
uint32_t status;
uint32_t userchoice;
/********how many list i want to create ?********/
struct Node *Double_Link_List_Head_1=NULL;
/***********FUNCTION DECLERATION SECTION*********/
Std_Return INSERT_NODE_AT_BEGINNING(struct Node **List);
Std_Return DISPLAY_LIST_FORWARD(struct Node *List);
Std_Return DISPLAY_LIST_REVERSE(struct Node *List);
Std_Return INSERT_NODE_AT_END(struct Node **List);
uint32_t GET_LENGTH(struct Node *List);
Std_Return DELETE_NODE_AT_BEGINNING(struct Node **List);
Std_Return INSERT_NODE_AFTER(struct Node *List);
Std_Return DELETE_NODE_AFTER(struct Node *List);
/*******************************************************/





int main ()
{

    while(1)
    {
        printf("-------------------------------\n");
        printf("Welcome To Linked List\n");
        printf("INSERT NODE AT BEGINNING - >1 \n");
        printf("INSERT NODE AT END       - >2 \n");
        printf("INSERT NODE AFTER        - >3 \n");
        printf("          GET LENGTH     - >4 \n");
        printf("DELETE NODE AT BEGINNING - >5 \n");
        printf("DELETE SPECIFIC NODE     - >6 \n");
        printf("DISPLAY_LIST_FORWARD     - >7 \n");
        printf("DISPLAY LIST REVERSE     - >8 \n");
        printf("-------------------------------\n");
        printf("USER CHOICE -> \t ");
        scanf("%i",&userchoice);
        application();
    }
    return 0 ;
}
void application (void)
{
    switch(userchoice)
    {
    case 1 :
        status=INSERT_NODE_AT_BEGINNING(&Double_Link_List_Head_1);
        break ;
    case 2 :
        status=INSERT_NODE_AT_END(&Double_Link_List_Head_1);
        break ;
    case 3 :
        status=INSERT_NODE_AFTER(Double_Link_List_Head_1);
        break ;
    case 4 :
        status=GET_LENGTH(Double_Link_List_Head_1);
        break ;
    case 5 :
        status=DELETE_NODE_AT_BEGINNING(&Double_Link_List_Head_1);
        break ;
    case 6 :
        status=DELETE_NODE_AFTER(Double_Link_List_Head_1);
        break ;
    case 7 :
        status=DISPLAY_LIST_FORWARD(Double_Link_List_Head_1);
        break ;
    case 8 :
        status=DISPLAY_LIST_REVERSE(Double_Link_List_Head_1);
        break ;
    default:
        printf("INVALID CHOICE \n ")  ;
        break ;

    }
}



/*******************************************************/
Std_Return INSERT_NODE_AT_BEGINNING(struct Node **List)
{

    Std_Return status =STATUS_NOT_OK ;
    struct Node *New_Node;
    New_Node=(struct Node*)malloc(sizeof(struct Node));
    if(NULL==New_Node)
    {
        printf("INVALID ALLOCATION FOR THE NEW NODE \n ");
        status=STATUS_NOT_OK;
    }
    else
    {
        printf("Enter The Data : \n");
        scanf("%i",&New_Node->Data);
        if(NULL==*List) // list is already empty
        {
            *List=New_Node;
            New_Node->Left_Node_Link=NULL;
            New_Node->Right_Node_Link=NULL;
            status=LIST_EMPTY;
        }
        else // list has old data
        {
            New_Node->Right_Node_Link=*List;
            New_Node->Left_Node_Link=NULL;
            (*List)->Left_Node_Link =New_Node;
            *List=New_Node;
            status=STATUS_OK;
        }

    }



    return status;
}
/*******************************************************/

Std_Return INSERT_NODE_AT_END(struct Node **List)
{

    Std_Return status =STATUS_NOT_OK ;
    struct Node *New_Node;
    struct Node *Previous_Node=*List;
    New_Node=(struct Node*)malloc(sizeof(struct Node));
    if(NULL==New_Node)
    {
        printf("INVALID ALLOCATION FOR THE NEW NODE \n ");
        status=STATUS_NOT_OK;
    }
    else
    {
        printf("Enter The Data : \n");
        scanf("%i",&New_Node->Data);
        if(NULL==*List) // list is already empty
        {
            status=LIST_EMPTY;
            printf("List is Already Empty Please use INSERT AT BEGINNING \n");
        }
        else // list has old data
        {
            while(Previous_Node->Right_Node_Link!=NULL)
            {
                Previous_Node= Previous_Node->Right_Node_Link; // iam here on the previous end node
            }

            New_Node->Right_Node_Link=NULL;
            New_Node->Left_Node_Link=Previous_Node;
            Previous_Node->Right_Node_Link=New_Node;
            status=STATUS_OK;

        }

    }



    return status;
}
/***********************************************************/
Std_Return INSERT_NODE_AFTER(struct Node *List)
{
    Std_Return status =STATUS_NOT_OK;
    uint32_t counter =1 ;
    uint32_t list_length =0;
    uint32_t Node_Pos =0 ;
    struct Node *New_Node=NULL;
    struct Node *Prev_Node=List;
    printf("Enter The Node Position 'first position =1' \n->");
    scanf("%i",&Node_Pos);
    list_length=GET_LENGTH(List);
    if((Node_Pos>list_length)||(0==list_length)||(Node_Pos==list_length))
    {
        printf("ERROR ON NODE POSITION U INSERT %i or LIST is empty -> list length =%i\n",Node_Pos,list_length);
        status=STATUS_NOT_OK;
    }
    else
    {
        New_Node=(struct Node *)malloc(sizeof(struct Node));
        if(NULL==New_Node)
        {
            printf("ERROR ON ALLOCATION \n");
            status=STATUS_NOT_OK;
        }
        else
        {
            printf("Enter The Data \n -> ");
            scanf("%i",&(New_Node->Data));
            while(counter<Node_Pos)
            {
                counter++;
                Prev_Node=Prev_Node->Right_Node_Link;
            }
            New_Node->Right_Node_Link=Prev_Node->Right_Node_Link;

            (New_Node->Right_Node_Link)->Left_Node_Link=New_Node;
            New_Node->Left_Node_Link=Prev_Node;

            Prev_Node->Right_Node_Link=New_Node;

            status=STATUS_OK;
        }

    }


    return status;

}


/***********************************************************/
Std_Return DISPLAY_LIST_FORWARD(struct Node *List) // traversing // double pointer
{
    struct Node *Node_Traverse=List;

    if(Node_Traverse==NULL)
    {
        printf("List is empty\n");
    }
    else
    {
        printf("List Data is : ");
        while(Node_Traverse!=NULL)
        {
            printf("->%i",Node_Traverse->Data);
            Node_Traverse=Node_Traverse->Right_Node_Link;
        }
        if(NULL==Node_Traverse)
        {
            printf("->NULL\n");
        }

    }
    return status;

}
/*******************************************************/
Std_Return DISPLAY_LIST_REVERSE(struct Node *List) // traversing // double pointer
{
    Std_Return status =STATUS_NOT_OK;
    struct Node *Node_Traverse=List;



    if(List==NULL)
    {
        printf("List is empty\n");
        status=LIST_EMPTY;
    }
    else
    {

        while(Node_Traverse->Right_Node_Link!=NULL)
        {
            Node_Traverse=Node_Traverse->Right_Node_Link;
        }

        printf("List Data is : ");
        while(Node_Traverse!=NULL)
        {
            printf("->%i",Node_Traverse->Data);
            Node_Traverse=Node_Traverse->Left_Node_Link;
        }
        if(NULL==Node_Traverse)
        {
            printf("->NULL\n");
            status=STATUS_OK;
        }

    }

    return status ;
}
/**********************************************/
uint32_t GET_LENGTH(struct Node *List)
{
    struct Node *Temp=List;
    uint32_t length =1;
    if(NULL==List)
    {
        length =0;
    }
    else
    {
        while(Temp->Right_Node_Link!=NULL)
        {
            length++;
            Temp=Temp->Right_Node_Link;

        }
    }





    return length;
}
/*******************************************************/
Std_Return DELETE_NODE_AT_BEGINNING(struct Node **List)
{
    struct Node *Temp_Node =NULL;
    Std_Return status =STATUS_NOT_OK ;
    if(*List==NULL)
    {
        printf("List Already Empty \n");
        status =LIST_EMPTY;
    }
    else
    {
        Temp_Node=*List;
        (Temp_Node->Right_Node_Link)->Left_Node_Link=NULL;
        *List=Temp_Node->Right_Node_Link;
        free(Temp_Node);
        status =STATUS_OK;
    }





    return status ;
}
/*******************************************************/
Std_Return DELETE_NODE_AFTER(struct Node *List)
{
    uint32_t Node_Pos=0;
    uint32_t list_length=0;
    uint32_t counter=1;
    struct Node*Pre_Node=List;
    struct Node*Temp_Node =NULL;
    Std_Return status =STATUS_NOT_OK;
    printf("Enter The Position -> \n");
    scanf("%i",&Node_Pos);
    list_length=GET_LENGTH(List);
    if((Node_Pos>list_length)||(list_length==0)||(list_length==1))
    {
        switch(list_length)
        {
        case 0 :
            printf("LIST IS EMPTY \n");
            status=LIST_EMPTY;
            status = LIST_EMPTY;
            break;
        case 1 :
            printf("PLEASE USE DELETE AT BEGINNING FUNCTION \n ");
            status =STATUS_NOT_OK;
            break;
        default :
            printf("INVALID NODE POS %i \n ",Node_Pos);
            status =STATUS_NOT_OK;
            break;
        }
    }
    else
    {
        while(counter<(Node_Pos-1))
        {
            counter++;
            Pre_Node=Pre_Node->Right_Node_Link; //4
        }
        if(NULL==Pre_Node->Right_Node_Link->Right_Node_Link)
        {
            Temp_Node=Pre_Node->Right_Node_Link;
            Pre_Node->Right_Node_Link=NULL;
            status =STATUS_OK;
        }
        else
        {
            Temp_Node=Pre_Node->Right_Node_Link; //5
            Pre_Node->Right_Node_Link=Temp_Node->Right_Node_Link;  //4->6
            (Temp_Node->Right_Node_Link)->Left_Node_Link=Pre_Node;  // 6->4
            status =STATUS_OK;

        }


    }

    return status;
}
