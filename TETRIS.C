#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>

struct block
{
int x1,y1,x2,y2;
int clr;
int color;
struct block *left,*right,*up,*down;
};

struct high
{
char name[20];
int score;
struct high *next;
}*head=NULL;

struct block *start=NULL,*end=NULL,*ptr,*cpt,*tmp,*tmp1,*tmp2,*tmp3,*tmp4;
struct block *b1=NULL,*b2=NULL,*b3=NULL,*b4=NULL;

int n1=0;


void add_front(char name[],int score)
{
struct high *temp;
temp=(struct high *)malloc(sizeof(struct high));
strcpy(temp->name,name);
temp->score=score;
if(head==NULL)
{
head=temp;
head->next=NULL;
}
else
{
temp->next=head;
head=temp;
}
}


void add_end(char name [],int score)
{
struct high *temp,*curr;
temp=(struct high *)malloc(sizeof(struct high));
curr=temp;
strcpy(temp->name,name);
temp->score=score;
if(head==NULL)
{
head=temp;
temp->next=NULL;
}
else
{
curr=head;
while(curr->next!=NULL)
{
curr=curr->next;
}
temp->next=NULL;
curr->next=temp;
}
}


int position(int score)
{
struct high *curr;
int pos=1;
curr=head;
if(head!=NULL)
{
while(curr!=NULL)
{
if(score>=curr->score)
return pos;
curr=curr->next;
pos++;
}
}
return pos;
}


void add_pos(char name[],int score)
{
struct high *temp,*prev,*ptr;
int ptrpos=1;
int pos=position(score);

setbkcolor(BLACK);
setcolor(GREEN);
//printf("Player name: %s\n",name);
temp=(struct high *)malloc(sizeof(struct high));
prev=temp;
ptr=head;
if(pos==1)
{
add_front(name,score);
n1++;
}
else if(pos>n1)
{
add_end(name,score);
n1++;
}
else
{
while(ptrpos<pos)
{
ptrpos++;
prev=ptr;
ptr=ptr->next;
}
strcpy(temp->name,name);
temp->score=score;
prev->next=temp;
temp->next=ptr;
n1++;
}
}


void scores()
{
struct high *curr;
int i=0;
int x=getmaxx();
int y=getmaxy();
cleardevice();
setbkcolor(BLACK);
setcolor(BLUE);

curr=head;
settextstyle(4,0,6);
outtextxy((x/2)-200,10,"HIGH SCORES: ");

while(curr!=NULL)
{
//gotoxy(x/2,300+i);
settextstyle(6,0,4);
setcolor(GREEN);
outtextxy(20,100,"NAME: ");
outtextxy(400,100,"SCORES: ");
flushall();
gotoxy(50,12+i);
printf("\n %s\t\t",curr->name);
//outtextxy(340,50+i,"curr->score");
flushall();
gotoxy(60,12+i);
printf("%d \n",curr->score);
curr=curr->next;
i=i+3;
}
getch();
}

void draw()
{
int i,x,y;
for(x=200,y=50;x<=390;x+=10,y=50)
{
ptr=(struct block *)malloc(sizeof(struct block));
ptr->x1=x;
ptr->y1=y;
ptr->x2=x+10;
ptr->y2=y+10;
ptr->up=NULL;
ptr->down=NULL;
ptr->left=NULL;
ptr->right=NULL;
ptr->clr=0;
ptr->color=0;

if(start==NULL)
start=end=ptr;
else
{
end->right=ptr;
ptr->left=end;
end=ptr;
}
for(y+=10;y<=440;y+=10)
{
cpt=(struct block *)malloc(sizeof(struct block));
cpt->x1=x;
cpt->y1=y;
cpt->x2=x+10;
cpt->y2=y+10;
cpt->up=NULL;
cpt->down=NULL;
cpt->left=NULL;
cpt->right=NULL;
cpt->clr=0;
ptr->color=0;

if(ptr->down==NULL)
{
ptr->down=cpt;
cpt->up=ptr;
}
else
{
for(tmp=ptr->down;tmp->down!=NULL;tmp=tmp->down);
tmp->down=cpt;
cpt->up=tmp;
}
}
}

for(ptr=start,cpt=ptr->right;cpt!=NULL;ptr=cpt,cpt=cpt->right)
{
for(tmp1=ptr->down,tmp2=cpt->down;tmp1!=NULL;tmp1=tmp1->down,tmp2=tmp2->down)
{
tmp1->right=tmp2;
tmp2->left=tmp1;
}
}
}

void disp(int c,int color)
{
setcolor(c);
rectangle(b1->x1,b1->y1,b1->x2-1,b1->y2-1);
rectangle(b2->x1,b2->y1,b2->x2-1,b2->y2-1);
rectangle(b3->x1,b3->y1,b3->x2-1,b3->y2-1);
rectangle(b4->x1,b4->y1,b4->x2-1,b4->y2-1);
setfillstyle(SOLID_FILL,color);
floodfill(b1->x1+5,b1->y1+5,c);
floodfill(b2->x1+5,b2->y1+5,c);
floodfill(b3->x1+5,b3->y1+5,c);
floodfill(b4->x1+5,b4->y1+5,c);

}

void square(struct block *b)
{
b1=b;
b2=b1->right;
b3=b1->down;
b4=b1->right->down;
}

void leftL(struct block *b)
{
b1=b->right;
b2=b1->down;
b4=b2->down;
b3=b4->left;
}

void rightL(struct block *b)
{
b1=b;
b2=b1->down;
b3=b2->down;
b4=b3->right;
}

void barI(struct block *b)
{
b1=b;
b2=b1->down;
b3=b2->down;
b4=b3->down;
}

void showall()
{
for(tmp3=start;tmp3!=NULL;tmp3=tmp3->down)
{
for(tmp4=tmp3;tmp4!=NULL;tmp4=tmp4->right)
{
if(tmp4->clr==0)
{
setcolor(0);
rectangle(tmp4->x1,tmp4->y1,tmp4->x2-1,tmp4->y2-1);
setfillstyle(SOLID_FILL,0);
floodfill(tmp4->x1+5,tmp4->y1+5,0);
}
else
{
setcolor(15);
rectangle(tmp4->x1,tmp4->y1,tmp4->x2-1,tmp4->y2-1);
setfillstyle(SOLID_FILL,tmp4->color);
floodfill(tmp4->x1+5,tmp4->y1+5,15);
}
}
}
}

void eleminate()
{
for(tmp3=tmp1;tmp3!=start;tmp3=tmp3->up)
{
for(tmp4=tmp3;tmp4!=NULL;tmp4=tmp4->right)
{
tmp4->clr=tmp4->up->clr;
tmp4->color=tmp4->up->color;
}
}
}

void check(int *sc,int score[])
{
int f=0;
for(tmp1=start;tmp1!=NULL;tmp1=tmp1->down)
{
f=0;
for(tmp2=tmp1;tmp2!=NULL;tmp2=tmp2->right)
{
if(tmp2->clr==0)
f=1;
}
if(f==0)
{
for(tmp2=tmp1;tmp2!=NULL;tmp2=tmp2->right)
{
tmp2->clr=0;
tmp2->color=0;
}
eleminate();
showall();
setcolor(0);
sprintf(score,"%d",*sc);
outtextxy(90,240,score);
*sc+=10;
setcolor(15);
sprintf(score,"%d",*sc);
outtextxy(90,240,score);
}
}
}

void show(int n[],int color[],int f)
{
int i,j,x,y;
setcolor(15);
rectangle(450,50,500,380);

if(f==0)
{
setcolor(0);
}
else
{
setcolor(15);
}

for(i=1,j=70;i<7;i++)
{
if(n[i]==1)
{
rectangle(460,j,469,j+9);
rectangle(470,j,479,j+9);
rectangle(460,j+10,469,j+19);
rectangle(470,j+10,479,j+19);

if(f==0)
{
setfillstyle(SOLID_FILL,0);
floodfill(465,j+5,0);
floodfill(475,j+5,0);
floodfill(465,j+15,0);
floodfill(475,j+15,0);
}
else
{
setfillstyle(SOLID_FILL,color[i]);
floodfill(465,j+5,15);
floodfill(475,j+5,15);
floodfill(465,j+15,15);
floodfill(475,j+15,15);
}
j+=40;

}
else if(n[i]==2)
{
rectangle(470,j,479,j+9);
rectangle(470,j+10,479,j+19);
rectangle(470,j+19,479,j+29);
rectangle(460,j+19,469,j+29);
if(f==0)
{
setfillstyle(SOLID_FILL,0);
floodfill(475,j+5,0);
floodfill(475,j+15,0);
floodfill(475,j+25,0);
floodfill(465,j+25,0);
}
else
{
setfillstyle(SOLID_FILL,color[i]);
floodfill(475,j+5,15);
floodfill(475,j+15,15);
floodfill(475,j+25,15);
floodfill(465,j+25,15);
}
j+=50;
}
else if(n[i]==3)
{
rectangle(460,j,469,j+9);
rectangle(460,j+10,469,j+19);
rectangle(460,j+19,469,j+29);
rectangle(470,j+19,479,j+29);
if(f==0)
{
setfillstyle(SOLID_FILL,0);
floodfill(465,j+5,0);
floodfill(465,j+15,0);
floodfill(465,j+25,0);
floodfill(475,j+25,0);
}
else
{
setfillstyle(SOLID_FILL,color[i]);
floodfill(465,j+5,15);
floodfill(465,j+15,15);
floodfill(465,j+25,15);
floodfill(475,j+25,15);
}
j+=50;
}
else if(n[i]==4)
{
rectangle(465,j,474,j+9);
rectangle(465,j+10,474,j+19);
rectangle(465,j+19,474,j+29);
rectangle(465,j+29,474,j+39);
if(f==0)
{
setfillstyle(SOLID_FILL,0);
floodfill(470,j+5,0);
floodfill(470,j+15,0);
floodfill(470,j+25,0);
floodfill(470,j+35,0);
}
else
{
setfillstyle(SOLID_FILL,color[i]);
floodfill(470,j+5,15);
floodfill(470,j+15,15);
floodfill(470,j+25,15);
floodfill(470,j+35,15);
}
j+=60;
}
}
}



void fp()
{
int y=240;
char ch1=0,ch2=0;

cleardevice();

setbkcolor(15);
setcolor(4);
settextstyle(0,0,4);
outtextxy(220,50,"TETRIS");

settextstyle(0,0,1);
setcolor(4);
outtextxy(270,250,"START GAME");
outtextxy(268,290,"HIGH SCORES");
outtextxy(293,330,"EXIT");

setcolor(4);
rectangle(5,5,630,470);
rectangle(7,7,628,468);

setcolor(15);
setfillstyle(SOLID_FILL,1);
rectangle(260,120,310,170);
rectangle(310,120,360,170);
rectangle(260,170,310,220);
rectangle(310,170,360,220);

floodfill(265,125,15);
floodfill(315,125,15);
floodfill(265,175,15);
floodfill(315,175,15);

setfillstyle(SOLID_FILL,2);
rectangle(80,190,130,240);
rectangle(80,240,130,290);
rectangle(80,290,130,340);
rectangle(130,290,180,340);

floodfill(85,195,15);
floodfill(85,245,15);
floodfill(85,295,15);
floodfill(135,295,15);

setfillstyle(SOLID_FILL,5);
rectangle(500,190,550,240);
rectangle(500,240,550,290);
rectangle(500,290,550,340);
rectangle(450,290,500,340);

floodfill(505,195,15);
floodfill(505,245,15);
floodfill(505,295,15);
floodfill(455,295,15);

setfillstyle(SOLID_FILL,4);
rectangle(210,370,260,420);
rectangle(360,370,410,420);
rectangle(260,370,310,420);
rectangle(310,370,360,420);

floodfill(215,375,15);
floodfill(365,375,15);
floodfill(265,375,15);
floodfill(315,375,15);

setcolor(4);
rectangle(240,y,380,y+25);

while(ch1!=13)
{
ch1=getch();
if(ch1==13)
break;
ch2=getch();

setcolor(0);
rectangle(240,y,380,y+25);

if(ch1==0 && ch2==80)
y+=40;
if(ch1==0 && ch2==72)
y-=40;

if(y>320)
{
y=240;
rectangle(240,y,380,y+25);
}
else if(y<240)
{
y=320;
rectangle(240,y,380,y+25);
}
setcolor(4);
rectangle(240,y,380,y+25);
}

if(y==240)
return;
else if(y==280)
scores();
else
exit(0);
}

void over()
{
cleardevice();
setbkcolor(15);
setcolor(4);
settextstyle(0,0,4);
outtextxy(200,200,"GAME OVER");
getch();
}

int main()
{
   char ch,ch1,ch2;
   char name[50];
   int score[5],sc=0,n[7],i=0,color[7],gdriver = DETECT, gmode;
   struct block *b;
   initgraph(&gdriver, &gmode, "C:\\TC\\BGI");

   randomize();
   fp();
   cleardevice();
   setbkcolor(0);
   setcolor(15);

   line(0,50,50,0);
   line(0,70,70,0);
   line(0,430,50,480);
   line(0,410,70,480);
   line(590,0,640,50);
   line(570,0,640,70);
   line(590,480,640,430);
   line(570,480,640,410);

   rectangle(450,50,500,380);
   rectangle(199,49,401,451);
   draw();

   rectangle(30,180,190,300);
   outtextxy(40,200,"NAME:");
   outtextxy(40,240,"SCORE:");
   sprintf(score,"%d",sc);
   outtextxy(90,240,score);
   while((ch=getch())!=13)
   {
   if(ch==' ')
   break;
   name[i++]=ch;
   name[i]='\0';
   outtextxy(80,200,name);
   }


   for(i=0,b=start;i!=8;i++,b=b->right);

   for(i=0;i<6;i++)
   {
   n[i]=1+random(4);
   color[i]=1+random(14);
   }

   while(b->clr==0 && b->right->clr==0)
   {
   n[6]=1+random(4);
   color[6]=1+random(14);
   show(n,color,1);

   switch(n[0])
   {
   case 1:square(b);
	  break;
   case 2:leftL(b);
	  break;
   case 3:rightL(b);
	  break;
   case 4:barI(b);
	  break;
   }

   while(b3->down!=NULL && b4->down!=NULL && b4->down->clr==0 && b3->down->clr==0)
   {
   if(kbhit())
   {
   disp(0,0);
   ch=getch();

   if(ch=='a' && b3->left!=NULL)
   {
   if((n[0]==1 && b3->left->clr==0 && b1->left->clr==0)||((n[0]==2 || n[0]==3) && b3->left->clr==0 && b2->left->clr==0 && b1->left->clr==0)||(n[0]==4 && b4->left->clr==0 && b3->left->clr==0 && b2->left->clr==0 && b1->left->clr==0))
   {
   b1=b1->left;
   b2=b2->left;
   b3=b3->left;
   b4=b4->left;
   }
   }

   else if(ch=='d' && b4->right!=NULL)
   {
   if((n[0]==1 && b4->right->clr==0 && b2->right->clr==0)||((n[0]==2 || n[0]==3) && b4->right->clr==0 && b2->right->clr==0 && b1->right->clr==0)||(n[0]==4 && b4->right->clr==0 && b3->right->clr==0 && b2->right->clr==0 && b1->right->clr==0))
   {
   b1=b1->right;
   b2=b2->right;
   b3=b3->right;
   b4=b4->right;
   }
   }

   else if(ch=='s')
   {
   for(b3,b4;b3->down!=NULL && b4->down!=NULL && b4->down->clr==0 && b3->down->clr==0;b4=b4->down,b3=b3->down);

   if(n[0]==1)
   {
   b2=b4->up;
   b1=b2->left;
   }
   else if(n[0]==2)
   {
   b2=b4->up;
   b1=b2->up;
   }
   else if(n[0]==3 || n[0]==4)
   {
   b2=b3->up;
   b1=b2->up;
   }

   disp(15,color[0]);
   check(&sc,score);
   break;
   }
   }

   disp(15,color[0]);
   delay(100);
   disp(0,0);

   b1=b1->down;
   b2=b2->down;
   b3=b3->down;
   b4=b4->down;
   disp(15,color[0]);
   }

   b1->clr=b2->clr=b3->clr=b4->clr=1;
   b1->color=b2->color=b3->color=b4->color=color[0];

   check(&sc,score);

   show(n,color,0);
   for(i=0;i<6;i++)
   {
   n[i]=n[i+1];
   color[i]=color[i+1];
   }
   }
   add_pos(name,sc);
   start=end=NULL;
   over();
   main();
   getch();
   closegraph();
   return 0;
}