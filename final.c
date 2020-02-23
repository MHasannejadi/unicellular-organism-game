#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "node.h"

char map[100][100];  //status of every point
int ppos[100][100]; //cells map & position
char visual[300][300];
int pos_energy[100][100]; //energy of every position
int n;   //length of square side
int cn,cn1,cn2;
void textcolor (int color)
{
    static int __BACKGROUND;

    HANDLE h = GetStdHandle ( STD_OUTPUT_HANDLE );
    CONSOLE_SCREEN_BUFFER_INFO csbiInfo;


    GetConsoleScreenBufferInfo(h, &csbiInfo);

    SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE),
                             color + (__BACKGROUND << 2));
}
void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}


void fjadval(void)
{
    int i,j,t;


    for(i=0; i<4*n+1; i+=4)
    {
        int c=3;
        for(t=0; t<n/2; t++)
        {


            for(j=2*c-1; j<2*(c+1); j++)
            {
                visual[j][i]='_';


            }
            c+=4;
        }
    }
    for(i=2; i<4*n+5; i+=4)
    {
        int c=1;
        for(t=0; t<(n+1)/2; t++)
        {


            for(j=2*c-1; j<2*(c+1); j++)
            {
                visual[j][i]='_';
                //textcolor(c);

            }
            c+=4;
        }
    }
    for(i=1; i<3; i++)
    {
        int z=2;
        for(t=0; t<n/2; t++)
        {
            for(j=2*z; j<=2*(z+2); j+=4)
            {
                visual[j][i]='|';
            }
            z+=4;
        }
    }
    for(i=3; i<4*n+3; i++)
    {
        for(j=0; j<4*n+1; j+=4)
        {
            visual[j][i]='|';
        }
    }
    if(n%2==0)
    {
        visual[4*n][4*n+1]=' ';
        visual[4*n][4*n+2]=' ';
    }

}
void addblock(void)
{
    int i,j;
    for(i=0; i<n; i++)
    {
        for(j=0; j<n; j++)
        {
            if(map[j][i]=='1')
            {
                //textcolor(12);
                if(j%2==0)
                    visual[j*4+2][i*4+3]='E';
                else
                    visual[j*4+2][i*4+1]='E';
            }
            else if(map[j][i]=='2')
            {
                textcolor(14);
                if(j%2==0)
                    visual[j*4+2][i*4+3]='M';
                else
                    visual[j*4+2][i*4+1]='M';
            }
            else if(map[j][i]=='3')
            {
               // textcolor(16);
                if(j%2==0)
                    visual[j*4+2][i*4+3]='F';
                else
                    visual[j*4+2][i*4+1]='F';
            }
            else if(map[j][i]=='4')
            {
                //textcolor(18);
                if(j%2==0)
                    visual[j*4+2][i*4+3]='N';
                else
                    visual[j*4+2][i*4+1]='N';
            }
        }
    }

}
void addcell_single(struct node *head)
{
    int c=0;
    while(head!=NULL)
    {
        int x=head->x;
        int y=head->y;
        int energy=head->cenergy;
        char k=(c+49);
        c++;
        if(x%2==0)
        {
            visual[x*4+1][y*4+5]='X';
            visual[x*4+2][y*4+5]=k;
        }
        else
        {
            visual[x*4+1][y*4+3]='X';
            visual[x*4+2][y*4+3]=k;
        }
        head=head->next;
    }


}
void addcell_multiple(struct node *head1,struct node *head2)
{
    int c=0;
    while(head1!=NULL)
    {
        int x=head1->x;
        int y=head1->y;
        int energy=head1->cenergy;
        char k=(c+49);
        c++;
        if(x%2==0)
        {
            visual[x*4+1][y*4+5]='X';
            visual[x*4+2][y*4+5]=k;
        }
        else
        {
            visual[x*4+1][y*4+3]='X';
            visual[x*4+2][y*4+3]=k;
        }
        head1=head1->next;
    }
    c=0;
    while(head2!=NULL)
    {
        int x=head2->x;
        int y=head2->y;
        int energy=head2->cenergy;
        char k=(c+49);
        c++;
        if(x%2==0)
        {
            visual[x*4+1][y*4+5]='Y';
            visual[x*4+2][y*4+5]=k;
        }
        else
        {
            visual[x*4+1][y*4+3]='Y';
            visual[x*4+2][y*4+3]=k;
        }
        head2=head2->next;
    }


}
void add_energy(void)
{
    int i,j;
    char a[4];
    for(i=0;i<4*n+5;i++){
        for(j=0;j<4*n+5;j++){
            if(map[j][i]=='1'){
                sprintf(a,"%d",pos_energy[j][i]);
                if(j%2==0){
                    visual[j*4+1][i*4+4]=a[0];
                    visual[j*4+2][i*4+4]=a[1];
                    visual[j*4+3][i*4+4]=a[2];
                }
                else{
                    visual[j*4+1][i*4+2]=a[0];
                    visual[j*4+2][i*4+2]=a[1];
                    visual[j*4+3][i*4+2]=a[2];
                }
            }
        }
    }

}
void remove_cell(void)
{
    int i,j;
    for(i=0; i<4*n+5; i++)
    {
        for(j=0; j<4*n+5; j++)
        {
            visual[j][i]=' ';
        }

    }

}
void show(void)
{

    fjadval();
    addblock();
    add_energy();
    int i,j;
    for(i=0; i<4*n+5; i++)
    {
        for(j=0; j<4*n+1; j++)
        {
            printf("%c",visual[j][i]);
        }
        printf("\n");
    }


}
void distribution_energy(void)
{
    int i,j;
    for(i=0; i<n; i++)
    {
        for(j=0; j<n; j++)
        {
            if(map[i][j]=='1')
            {
                pos_energy[i][j]=100;
            }

        }
    }
    return;
}
void move_cell1(struct node * head,int cellnum)
{
    struct node *copy = head;
    int i;

    for(i=0; i<cellnum-1; i++)
    {
        copy=copy->next;
    }

    int x=copy->x,y=copy->y,movech; //movechoice

    int a[10]={0},j=0;

    while(j==0)
    {
        if(x%2==0){

            if(ppos[x-1][y+1]==0&&map[x-1][y+1]!='3'&&y+1<n&&x-1>=0)
            {
                printf("1)south west\n");
                a[1]=1;
            }

            if(ppos[x][y+1]==0&&map[x][y+1]!='3'&&y+1<n)
            {
                printf("2)south\n");
                a[2]=1;
            }

            if(ppos[x+1][y+1]==0&&map[x+1][y+1]!='3'&&y+1<n&&x+1<n)
            {
                printf("3)south east\n");
                a[3]=1;
            }

            if(ppos[x-1][y]==0&&map[x-1][y]!='3'&&x-1>=0)
            {
                printf("7)north west\n");
                a[7]=1;
            }

            if(ppos[x][y-1]==0&&map[x][y-1]!='3'&&y-1>=0)
            {
                printf("8)north\n");
                a[8]=1;
            }

            if(ppos[x+1][y]==0&&map[x+1][y]!='3'&&x+1<n)
            {
                printf("9)north east\n");
                a[9]=1;
            }





        }
        else{

            if(ppos[x-1][y]==0&&map[x-1][y]!='3'&&x-1>=0)
            {
                printf("1)south west\n");
                a[1]=1;
            }

            if(ppos[x][y+1]==0&&map[x][y+1]!='3'&&y+1<n)
            {
                printf("2)south\n");
                a[2]=1;
            }

            if(ppos[x+1][y]==0&&map[x+1][y]!='3'&&x+1<n)
            {
                printf("3)south east\n");
                a[3]=1;
            }

            if(ppos[x-1][y-1]==0&&map[x-1][y-1]!='3'&&y-1>=0&&x-1>=0)
            {
                printf("7)north west\n");
                a[7]=1;
            }

            if(ppos[x][y-1]==0&&map[x][y-1]!='3'&&y-1>=0)
            {
                printf("8)north\n");
                a[8]=1;
            }

            if(ppos[x+1][y-1]==0&&map[x+1][y-1]!='3'&&y-1>=0&&x+1<n)
            {
                printf("9)north east\n");
                a[9]=1;
            }
        }
        scanf("%d",&movech);
        j++;
        if(a[movech]==0)
        {
            printf("cell couldn't move to choosen move .please choose another place to move\n");
            j=0;
        }
    }
        if(x%2==0){
            if(movech==8)
            {
                ppos[copy->x][copy->y]=0;
                (copy->y)--;
                ppos[copy->x][copy->y]=1;
            }
            else if(movech==9)
            {
                ppos[copy->x][copy->y]=0;
                (copy->x)++;
                ppos[copy->x][copy->y]=1;
            }
            else if(movech==3)
            {
                ppos[copy->x][copy->y]=0;
                (copy->y)++;
                (copy->x)++;
                ppos[copy->x][copy->y]=1;
            }
            else if(movech==2)
            {
                ppos[copy->x][copy->y]=0;
                (copy->y)++;
                ppos[copy->x][copy->y]=1;
            }
            else if(movech==1)
            {
                ppos[copy->x][copy->y]=0;
                (copy->y)++;
                (copy->x)--;
                ppos[copy->x][copy->y]=1;
            }
            else if(movech==7)
            {
                ppos[copy->x][copy->y]=0;
                (copy->x)--;
                ppos[copy->x][copy->y]=1;
            }
        }
        else{
            if(movech==8)
            {
                ppos[copy->x][copy->y]=0;
                (copy->y)--;
                ppos[copy->x][copy->y]=1;
            }
            else if(movech==9)
            {
                ppos[copy->x][copy->y]=0;
                (copy->y)--;
                (copy->x)++;
                ppos[copy->x][copy->y]=1;
            }
            else if(movech==3)
            {
                ppos[copy->x][copy->y]=0;

                (copy->x)++;
                ppos[copy->x][copy->y]=1;
            }
            else if(movech==2)
            {
                ppos[copy->x][copy->y]=0;
                (copy->y)++;
                ppos[copy->x][copy->y]=1;
            }
            else if(movech==1)
            {
                ppos[copy->x][copy->y]=0;

                (copy->x)--;
                ppos[copy->x][copy->y]=1;
            }
            else if(movech==7)
            {
                ppos[copy->x][copy->y]=0;
                (copy->y)--;
                (copy->x)--;
                ppos[copy->x][copy->y]=1;
            }
        }


    return;
}
void move_cell2(struct node * head,int cellnum)
{
    struct node *copy = head;
    int i;
    for(i=0; i<cellnum-1; i++)
    {
        copy=copy->next;
    }
    int x=copy->x,y=copy->y,movech; //movechoice
    int a[10]= {0},j=0;
    while(j==0)
    {


        if(x%2==0){

            if(ppos[x-1][y+1]==0&&map[x-1][y+1]!='3'&&y+1<n&&x-1>=0)
            {
                printf("1)south west\n");
                a[1]=1;
            }

            if(ppos[x][y+1]==0&&map[x][y+1]!='3'&&y+1<n)
            {
                printf("2)south\n");
                a[2]=1;
            }

            if(ppos[x+1][y+1]==0&&map[x+1][y+1]!='3'&&y+1<n&&x+1<n)
            {
                printf("3)south east\n");
                a[3]=1;
            }

            if(ppos[x-1][y]==0&&map[x-1][y]!='3'&&x-1>=0)
            {
                printf("7)north west\n");
                a[7]=1;
            }

            if(ppos[x][y-1]==0&&map[x][y-1]!='3'&&y-1>=0)
            {
                printf("8)north\n");
                a[8]=1;
            }

            if(ppos[x+1][y]==0&&map[x+1][y]!='3'&&x+1<n)
            {
                printf("9)north east\n");
                a[9]=1;
            }





        }
        else{

            if(ppos[x-1][y]==0&&map[x-1][y]!='3'&&x-1>=0)
            {
                printf("1)south west\n");
                a[1]=1;
            }

            if(ppos[x][y+1]==0&&map[x][y+1]!='3'&&y+1<n)
            {
                printf("2)south\n");
                a[2]=1;
            }

            if(ppos[x+1][y]==0&&map[x+1][y]!='3'&&x+1<n)
            {
                printf("3)south east\n");
                a[3]=1;
            }

            if(ppos[x-1][y-1]==0&&map[x-1][y-1]!='3'&&y-1>=0&&x-1>=0)
            {
                printf("7)north west\n");
                a[7]=1;
            }

            if(ppos[x][y-1]==0&&map[x][y-1]!='3'&&y-1>=0)
            {
                printf("8)north\n");
                a[8]=1;
            }

            if(ppos[x+1][y-1]==0&&map[x+1][y-1]!='3'&&y-1>=0&&x+1<n)
            {
                printf("9)north east\n");
                a[9]=1;
            }







        }
        scanf("%d",&movech);
        j++;
        if(a[movech]==0)
        {
            printf("cell couldn't move to choosen move .please choose another place to move\n");
            j=0;
        }
    }
        if(x%2==0){
            if(movech==8)
            {
                ppos[copy->x][copy->y]=0;
                (copy->y)--;
                ppos[copy->x][copy->y]=2;
            }
            else if(movech==9)
            {
                ppos[copy->x][copy->y]=0;
                (copy->x)++;
                ppos[copy->x][copy->y]=2;
            }
            else if(movech==3)
            {
                ppos[copy->x][copy->y]=0;
                (copy->y)++;
                (copy->x)++;
                ppos[copy->x][copy->y]=2;
            }
            else if(movech==2)
            {
                ppos[copy->x][copy->y]=0;
                (copy->y)++;
                ppos[copy->x][copy->y]=2;
            }
            else if(movech==1)
            {
                ppos[copy->x][copy->y]=0;
                (copy->y)++;
                (copy->x)--;
                ppos[copy->x][copy->y]=2;
            }
            else if(movech==7)
            {
                ppos[copy->x][copy->y]=0;
                (copy->x)--;
                ppos[copy->x][copy->y]=2;
            }
        }
        else{
            if(movech==8)
            {
                ppos[copy->x][copy->y]=0;
                (copy->y)--;
                ppos[copy->x][copy->y]=2;
            }
            else if(movech==9)
            {
                ppos[copy->x][copy->y]=0;
                (copy->y)--;
                (copy->x)++;
                ppos[copy->x][copy->y]=2;
            }
            else if(movech==3)
            {
                ppos[copy->x][copy->y]=0;

                (copy->x)++;
                ppos[copy->x][copy->y]=2;
            }
            else if(movech==2)
            {
                ppos[copy->x][copy->y]=0;
                (copy->y)++;
                ppos[copy->x][copy->y]=2;
            }
            else if(movech==1)
            {
                ppos[copy->x][copy->y]=0;

                (copy->x)--;
                ppos[copy->x][copy->y]=2;
            }
            else if(movech==7)
            {
                ppos[copy->x][copy->y]=0;
                (copy->y)--;
                (copy->x)--;
                ppos[copy->x][copy->y]=2;
            }
        }


    return;
}
void split_cell1(struct node ** head,int cellnum)
{
    struct node *copy = *head;
    int i;
    for(i=0; i<cellnum-1; i++)
    {
        copy=copy->next;
    }
    int energy=copy->cenergy;
    char name[20];
    strcpy(name,copy->name);///added
    int x=copy->x,y=copy->y;
    if((energy<80)||(map[x][y]!='2'))
    {
        printf("cell don't split");///added
        return;
    }
    int j,c=0;
    for(i=x-1; i<x+2; i++)
    {
        for(j=y-1; j<y+2; j++)
        {
            if(map[i][j]=='3'||ppos[i][j]!=0)
            {
                c++;
            }
        }
    }
    if(c>8)
    {
        return;
    }

    int cx=x+rand()%3-1;
    int cy=y+rand()%3-1;
    if(x%2==0){
        while(map[cx][cy]=='3'||ppos[cx][cy]!=0||cx>=n||cx<0||cy>=n||cy<0||(cx>x&&cy<y)||(cx<x&&cy<y))///added
        {
            cx=x+rand()%3-1;
            cy=y+rand()%3-1;
        }
    }
    else{
        while(map[cx][cy]=='3'||ppos[cx][cy]!=0||cx>=n||cx<0||cy>=n||cy<0||(cx<x&&cy>y)||(cx>x&&cy>y))///added
        {
            cx=x+rand()%3-1;
            cy=y+rand()%3-1;
        }
    }
    ppos[cx][cy]=1;
    int energy1=40;
    int energy2=40;
    char name1[20],name2[20];
    printf("please enter two name for two new cells\n");
    scanf("%s%s",name1,name2);
    pushback(head,name1,40,x,y);
    pushback(head,name2,40,cx,cy);
    deletenode(head,name);
    cn++;
    cn1++;
    return;
}
void split_cell2(struct node ** head,int cellnum)
{
    struct node *copy = *head;
    int i;
    for(i=0; i<cellnum-1; i++)
    {
        copy=copy->next;
    }
    int energy=copy->cenergy;
    char name[20];
    strcpy(name,copy->name);
    int x=copy->x,y=copy->y;
    if((energy<80)||(map[x][y]!='2'))
    {
        printf("cell don't split");
        return;
    }
    int j,c=0;
    for(i=x-1; i<x+2; i++)
    {
        for(j=y-1; j<y+2; j++)
        {
            if(map[i][j]=='3'||ppos[i][j]!=0)
            {
                c++;
            }
        }
    }
    if(c>8)
    {
        return;
    }
    int cx=x+rand()%3-1;
    int cy=y+rand()%3-1;

    if(x%2==0){
        while(map[cx][cy]=='3'||ppos[cx][cy]!=0||cx>=n||cx<0||cy>=n||cy<0||(cx>x&&cy>y)||(cx<x&&cy>y))///added
        {
            cx=x+rand()%3-1;
            cy=y+rand()%3-1;
        }
    }
    else{
        while(map[cx][cy]=='3'||ppos[cx][cy]!=0||cx>=n||cx<0||cy>=n||cy<0||(cx<x&&cy<y)||(cx>x&&cy<y))///added
        {
            cx=x+rand()%3-1;
            cy=y+rand()%3-1;
        }
    }
    ppos[cx][cy]=2;
    int energy1=40;
    int energy2=40;
    char name1[20],name2[20];
    printf("please enter two name for two new cells\n");
    scanf("%s%s",name1,name2);
    pushback(head,name1,40,x,y);
    pushback(head,name2,40,cx,cy);
    deletenode(head,name);
    cn2++;
    return;
}
void boost_energy(struct node * head,int cellnum)
{
    struct node *copy = head;
    int i;
    for(i=0; i<cellnum-1; i++)
    {
        copy=copy->next;
    }

    int energy=copy->cenergy;
    //char name[20];
    //strcpy(name,copy->name);
    int x=copy->x,y=copy->y;
    if(map[x][y]!='1'){
        printf("here isn't energy");
        return;
    }
    if(pos_energy[x][y]==0)
    {
        printf("unfortunately this place dont have energy\n");
    }
    else if(pos_energy[x][y]<=15&&energy<=85)
    {
         printf("OK\n");
        copy->cenergy=energy+pos_energy[x][y];
        pos_energy[x][y]=0;
    }
    else if(pos_energy[x][y]<=15&&energy>85)
    {

        int tmp=100-energy;
        if(tmp>pos_energy[x][y])
        {
            pos_energy[x][y]=0;
            copy->cenergy=energy+pos_energy[x][y];
        }
        else
        {
            pos_energy[x][y]-=tmp;
            copy->cenergy=energy+tmp;
        }

    }
    else if(pos_energy[x][y]>15&&energy<=85)
    {
        pos_energy[x][y]-=15;
        copy->cenergy=energy+15;
    }
    else if(pos_energy[x][y]>15&&energy>85)
    {
        int tmp=100-energy;
        pos_energy[x][y]-=tmp;
        copy->cenergy=energy+tmp;
    }

    return;
}
void save_single(struct node *head)
{
    FILE *fs=fopen("information.bin","wb");
    struct node *copy = head;
    int a=1;  //1 player
    fwrite(&a,sizeof(int),1,fs);
    fwrite(&cn,sizeof(int),1,fs);
    while(copy!=NULL)
    {
        fwrite(copy,sizeof(struct node),1,fs);
        copy=copy->next;
    }
    int i,j;
    for(i=0; i<n; i++)
    {
        for(j=0; j<n; j++)
        {
            fwrite(&pos_energy[i][j],sizeof(int),1,fs);
        }
    }
    fclose(fs);
}
void save_multiple(struct node *head1,struct node *head2)
{
    FILE *fs=fopen("information.bin","wb");
    struct node *copy1 = head1;
    struct node *copy2 = head2;
    int a=2;  //2 players
    fwrite(&a,sizeof(int),1,fs);
    fwrite(&cn1,sizeof(int),1,fs);
    fwrite(&cn2,sizeof(int),1,fs);
    while(copy1!=NULL)
    {
        fwrite(copy1,sizeof(struct node),1,fs);
        copy1=copy1->next;
    }
    while(copy2!=NULL)
    {
        fwrite(copy2,sizeof(struct node),1,fs);
        copy2=copy2->next;
    }
    int i,j;
    for(i=0; i<n; i++)
    {
        for(j=0; j<n; j++)
        {
            fwrite(&pos_energy[i][j],sizeof(int),1,fs);
        }
    }
    fclose(fs);

}
void newgame_single(void)
{
    int x,z;
    for(x=0;x<n;x++){
        for(z=0;z<n;z++){
            ppos[x][z]=0;
        }
    }
    distribution_energy();
    struct node *list1 = NULL ;
    system("cls");
    printf("please enter cells number\n");
    int i;     //cells number
    scanf("%d",&cn);
    for(i=0; i<cn; i++)
    {
        char name[20];
        int x,y,cenergy=0;
        system("cls");
        printf("please enter name of cell %d\n",i+1);
        scanf("%s",name);
        x=rand()%n;
        y=rand()%n;
        while(ppos[x][y]==1||map[x][y]=='3')
        {
            x=rand()%n;
            y=rand()%n;
        }
        pushback(&list1,name,cenergy,x,y);
        ppos[x][y]=1;

    }

    while(1)
    {
        system("cls");
        remove_cell();
        addcell_single(list1);
        show();
        int i=0;
        struct node * copy = list1;
        printf("Please choose one of your cells:\n");
        while(copy!=NULL)
        {
            printf("%d) %s (%d , %d) with energy : %d\n",i+1,copy->name,copy->x+1,copy->y+1,copy->cenergy);
            copy=copy->next;
            i++;
        }
        int cellch; //cellchoose
        scanf("%d",&cellch);
        system("cls");
        remove_cell();
        addcell_single(list1);
        show();
        int actch;
        printf("1)move\n2)split a cell\n3)boost energy\n4)save\n5)exit\n");
        scanf("%d",&actch); //act choose
        system("cls");
        remove_cell();
        addcell_single(list1);
        show();
        switch(actch)
        {
        case 1:
            move_cell1(list1,cellch);
            break;
        case 2:
            split_cell1(&list1,cellch);///change
            break;
        case 3:
            boost_energy(list1,cellch);
            break;
        case 4:
            save_single(list1);
            break;
        case 5:
            return;
        }
        remove_cell();
        addcell_single(list1);
        show();
    }
}
void newgame_multiple(void)
{
    int x,z;
    for(x=0;x<n;x++){
        for(z=0;z<n;z++){
            ppos[x][z]=0;
        }
    }
    distribution_energy();
    struct node * list1 = NULL ;
    struct node * list2 = NULL ;
    system("cls");
    printf("please enter cells number\n");
    int i;     //cells number
    cn1=cn;
    cn2=cn;
    scanf("%d",&cn);
    cn1=cn;
    cn2=cn;
    for(i=0; i<cn; i++)
    {
        char name[20];
        int x,y,cenergy=0;
        system("cls");
        printf("player 1 !! please enter name of cell %d\n",i+1);
        scanf("%s",name);    //***doubtful
        x=rand()%n;
        y=rand()%n;
        while(ppos[x][y]==1||map[x][y]=='3'||ppos[x][y]==2)
        {
            x=rand()%n;
            y=rand()%n;
        }
        pushback(&list1,name,cenergy,x,y);
        ppos[x][y]=1;
    }

    for(i=0; i<cn; i++)
    {
        char name[20];
        int x,y,cenergy=0;
        system("cls");
        printf("player 2 !! please enter name of cell %d\n",i+1);
        scanf("%s",name);    //***doubtful
        x=rand()%n;
        y=rand()%n;
        while(ppos[x][y]==1||map[x][y]=='3'||ppos[x][y]==2)
        {
            x=rand()%n;
            y=rand()%n;
        }
        pushback(&list2,name,cenergy,x,y);
        ppos[x][y]=1;
    }
    int c=0;
    while(1)
    {
        struct node * copy1 = list1;
        struct node * copy2 = list2;
        if(c%2==0)
        {
            system("cls");
            remove_cell();
            addcell_multiple(list1,list2);
            show();
            int i=0;
            printf("player %d !! Please choose one of your cells:\n",c%2+1);
            while(copy1!=NULL)
            {
                printf("%d) %s (%d , %d) with energy : %d\n",i+1,copy1->name,copy1->x+1,copy1->y+1,copy1->cenergy);
                copy1=copy1->next;
                i++;
            }
            int cellch; //cellchoose
            scanf("%d",&cellch);
            system("cls");
            remove_cell();
            addcell_multiple(list1,list2);
            show();
            int actch;
            printf("1)move\n2)split a cell\n3)boost energy\n4)save\n5)exit\n");
            scanf("%d",&actch); //act choose
            system("cls");
            remove_cell();
            addcell_multiple(list1,list2);
            show();
            switch(actch)
            {
            case 1:
                move_cell1(list1,cellch);
                break;
            case 2:
                split_cell1(&list1,cellch);
                break;
            case 3:
                boost_energy(list1,cellch);
                break;
            case 4:
                save_multiple(list1,list2);
                break;
            case 5:
                return;
            }
            c++;
        }
        else
        {

            system("cls");
            remove_cell();
            addcell_multiple(list1,list2);
            show();
            int i=0;
            printf("player %d !! Please choose one of your cells:\n",c%2+1);
            while(copy2!=NULL)
            {
                printf("%d) %s (%d , %d) with energy : %d\n",i+1,copy2->name,copy2->x+1,copy2->y+1,copy2->cenergy);
                copy2=copy2->next;
                i++;
            }
            int cellch; //cellchoose
            scanf("%d",&cellch);
            system("cls");
            remove_cell();
            addcell_multiple(list1,list2);
            show();
            int actch;
            printf("1)move\n2)split a cell\n3)boost energy\n4)save\n5)exit\n");
            scanf("%d",&actch); //act choose
            system("cls");
            remove_cell();
            addcell_multiple(list1,list2);
            show();
            switch(actch)
            {
            case 1:
                move_cell2(list2,cellch);
                break;
            case 2:
                split_cell2(&list2,cellch);
                break;
            case 3:
                boost_energy(list2,cellch);
                break;
            case 4:
                save_multiple(list1,list2);
                break;
            case 5:
                return;
            }
            c++;
        }


    }
}
void load(void)
{
    int x,z;
    for(x=0;x<n;x++){
        for(z=0;z<n;z++){
            ppos[x][z]=0;
        }
    }
    FILE *fp=fopen("information.bin","rb");
    if(fp==NULL)
    {
        printf("loading is impossible! please start a newgame");
    }
    int a;
    fread(&a,sizeof(int),1,fp);
    if(a==1)     ///single
    {

        struct node *list=NULL;
        int i,j,cn;
        fread(&cn,sizeof(int),1,fp);

        for ( i = 0 ; i < cn ; i++ )
        {
            struct node *o = malloc(sizeof(struct node));

            fread (o,sizeof(struct node),1,fp);

            ppos[o->x][o->y]=1;

            addstruct(&list,o);
        }
        //printf("%d\n",cn);
        for(i=0; i<n; i++)
        {
            for(j=0; j<n; j++)
            {
                fread(&pos_energy[i][j],sizeof(int),1,fp);
            }
        }
        fclose(fp);

        while(1)
        {
            system("cls");
            remove_cell();
            addcell_single(list);
            show();
            int i=0;
            struct node * copy = list;
            printf("Please choose one of your cells:\n");
            while(copy!=NULL)
            {
                printf("%d) %s (%d , %d) with energy : %d\n",i+1,copy->name,copy->x+1,copy->y+1,copy->cenergy);
                copy=copy->next;
                i++;
            }
            int cellch; //cellchoose
            scanf("%d",&cellch);
            system("cls");
            remove_cell();
            addcell_single(list);
            show();
            int actch;
            printf("1)move\n2)split a cell\n3)boost energy\n4)save\n5)exit\n");
            scanf("%d",&actch); //act choose
            system("cls");
            remove_cell();
            addcell_single(list);
            show();
            switch(actch)
            {
            case 1:
                move_cell1(list,cellch);
                break;
            case 2:
                split_cell1(&list,cellch);///change
                break;
            case 3:
                boost_energy(list,cellch);
                break;
            case 4:
                save_single(list);
                break;
            case 5:
                return;
            }
            remove_cell();
            addcell_single(list);
            show();
        }
    }
    else  /////multiply
    {
        struct node *list1=NULL;
        struct node *list2=NULL;
        int i,j;
        fread(&cn1,sizeof(int),1,fp);
        fread(&cn2,sizeof(int),1,fp);
        for ( i = 0 ; i < cn1 ; i++)
        {

            struct node *o=malloc(sizeof(struct node));
            fread(o,sizeof(struct node),1,fp);
            ppos[o->x][o->y]=1;
            addstruct(&list1,o);
        }
        printf("ok\n");
        for ( i = 0 ; i < cn2 ; i++)
        {
            struct node *t=malloc(sizeof(struct node));
            fread(t,sizeof(struct node),1,fp);
            addstruct(&list2,t);
            ppos[t->x][t->y]=2;
        }
        for(i=0; i<n; i++)
        {
            for(j=0; j<n; j++)
            {
                fread(&pos_energy[i][j],sizeof(int),1,fp);
            }
        }
        fclose(fp);

        int c=0;
        while(1)
        {
            struct node * copy1 = list1;
        struct node * copy2 = list2;
        if(c%2==0)
        {
            system("cls");
            remove_cell();
            addcell_multiple(list1,list2);
            show();
            int i=0;
            printf("player %d !! Please choose one of your cells:\n",c%2+1);
            while(copy1!=NULL)
            {
                printf("%d) %s (%d , %d) with energy : %d\n",i+1,copy1->name,copy1->x+1,copy1->y+1,copy1->cenergy);
                copy1=copy1->next;
                i++;
            }
            //printf("%d\n",cn);
            int cellch; //cellchoose
            scanf("%d",&cellch);
            system("cls");
            remove_cell();
            addcell_multiple(list1,list2);
            show();
            int actch;
            printf("1)move\n2)split a cell\n3)boost energy\n4)save\n5)exit\n");
            scanf("%d",&actch); //act choose
            system("cls");
            remove_cell();
            addcell_multiple(list1,list2);
            show();
            switch(actch)
            {
            case 1:
                move_cell1(list1,cellch);
                break;
            case 2:
                split_cell1(&list1,cellch);
                break;
            case 3:
                boost_energy(list1,cellch);
                break;
            case 4:
                save_multiple(list1,list2);
                break;
            case 5:
                return;
            }
            c++;
        }
        else
        {

            system("cls");
            remove_cell();
            addcell_multiple(list1,list2);
            show();
            int i=0;
            printf("player %d !! Please choose one of your cells:\n",c%2+1);
            while(copy2!=NULL)
            {
                printf("%d) %s (%d , %d) with energy : %d\n",i+1,copy2->name,copy2->x+1,copy2->y+1,copy2->cenergy);
                copy2=copy2->next;
                i++;
            }
            int cellch; //cellchoose
            scanf("%d",&cellch);
            system("cls");
            remove_cell();
            addcell_multiple(list1,list2);
            show();
            int actch;
            printf("1)move\n2)split a cell\n3)boost energy\n4)save\n5)exit\n");
            scanf("%d",&actch); //act choose
            system("cls");
            remove_cell();
            addcell_multiple(list1,list2);
            show();
            switch(actch)
            {
            case 1:
                move_cell2(list2,cellch);
                break;
            case 2:
                split_cell2(&list2,cellch);
                break;
            case 3:
                boost_energy(list2,cellch);
                break;
            case 4:
                save_multiple(list1,list2);
                break;
            case 5:
                return;
            }
            c++;
        }


        }
    }
}
int main()
{
    srand(time(NULL));
    FILE *fp;
    fp = fopen("map6.bin","rb");
    int i,j;
    if(fp==NULL)
    {
        printf("cannot read from file\n");
        return -1;
    }
    fread(&n,sizeof(int),1,fp);
    for(i=0; i<n; i++)
    {
        for(j=0; j<n; j++)
        {
            fread(&map[j][i],sizeof(char),1,fp);

        }
    }

    fclose(fp);

    int c=0;
    while(c!=4)
    {
        system("cls");
        printf("1) load\n2) new single player\n3) new multiplayer\n4) exit\n");
        scanf("%d",&c);
        system("cls");
        switch(c)
        {
        case 1:
            load();
            break;
        case 2:
            newgame_single();
            break;
        case 3:
            newgame_multiple();
            break;
        case 4:
            break;
        }
    }

    return 0;
}
