#include <graphics.h>
#include "iostream.h"
#include<string.h>
#include <stdio.h>
#include<ctype.h>
#include "stdlib.h"
#define YLEVEL 50
#define RADIUS 15
#define FALSE 0
#define TRUE 1
#include <conio.h>
#include "myfunc.h"
int maxx,maxy;
void init(){
   int gdriver = DETECT, gmode, errorcode;
   int xmax, ymax;
   initgraph(&gdriver, &gmode, "");
   errorcode = graphresult();
   if (errorcode != grOk)
   {
      printf("Graphics error: %s\n", grapherrormsg(errorcode));
      printf("Press any key to halt:");
      getch();
      exit(1);
   }
setlinestyle(SOLID_LINE,0xFFFF,50);
}
typedef struct{
  int key;
}element;
struct treeNode{
  treeNode *lc;
  element data;
  short int bf;
  treeNode *rc;
};


int depth(treeNode *p){
	if(p==NULL) return 0;
	int l=depth(p->lc);
	int r=depth(p->rc);
	if(l>=r)
		return l+1;
	else
		return r+1;
}
void display(treeNode *T,int x,int y,int px,int py,int color,int f=0){
if(T==NULL) return;
setcolor(color);
circle(x,y,RADIUS);
setcolor(WHITE);
char c[10];
sprintf(c,"%d",T->data.key);
if(T->data.key/100==0)
outtextxy(x-2,y-2,c);
else
outtextxy(x-3,y-2,c);
if(f==0)
line(px,py+RADIUS,x,y-RADIUS);
int a=abs(px-x)/2;
py=py;
f=1+f;;
display(T->lc,x-a,y+YLEVEL,x,y,color+1);
display(T->rc,x+a,y+YLEVEL,x,y,color+1);
}
void displayT(treeNode *T,int s=0){
  if(T==NULL) return;
  displayT(T->lc,s+10);
  for(int i=0;i<s;i++) cout<<" ";
  cout<<T->data.key<<endl;
  displayT(T->rc,s+10);
}


void leftRotate(treeNode **p,int *u){
  treeNode  *gc,*c;
  c=(*p)->lc;
  if(c->bf==1){
    (*p)->lc=c->rc;
    c->rc=*p;
    (*p)->bf=0;
    *p=c;
  }
  else{
  gc=c->rc;
  c->rc=gc->lc;
  (*p)->lc=gc->rc;
  gc->lc=c;
  gc->rc=*p;
  switch (gc->bf) {
    case -1:(*p)->bf=0;c->bf=1;break;
    case 0:(*p)->bf=c->bf=0;break;
    case 1:(*p)->bf=-1;c->bf=0;
  }
  *p=gc;
  }
(*p)->bf=0;
*u=FALSE;
}
void rightRotate(treeNode **p,int *u){
treeNode  *gc,*c;
c=(*p)->rc;
if(c->bf==-1){
  (*p)->rc=c->lc;
  c->lc=*p;
  (*p)->bf=0;
  *p=c;
}
else{
  gc=c->lc;
  (*p)->rc=gc->lc;
  c->lc=gc->rc;
  gc->lc=*p;
  gc->rc=c;
  switch (gc->bf){
    case -1:(*p)->bf=1;c->bf=0;break;
    case 0:(*p)->bf=c->bf=0;break;
    case 1:c->bf=-1;(*p)->bf=0;
  }
*p=gc;
}
(*p)->bf=0;
*u=FALSE;
}
void avlinsert(treeNode **p,element x,int * u){
if(*p==NULL){
  *u=TRUE;
  *p=(treeNode *)malloc(sizeof(treeNode));
  (*p)->lc=(*p)->rc=NULL;
  (*p)->bf=0;
  (*p)->data=x;
return;
  }
if(x.key<(*p)->data.key){
  avlinsert(&(*p)->lc,x,u);
  if(*u)
  switch ((*p)->bf) {
    case -1:(*p)->bf=0;
	    *u=FALSE;
	    break;
    case 0:(*p)->bf=1;break;
    case 1:
      cout<<"To be Rotated in Tree:::::";getch();cleardevice();
      display(*p,10*pow2(depth(*p)),RADIUS,0,0,1,1);
      getch();
    leftRotate(p,u);
    }
    return;
}
if(x.key>(*p)->data.key){
  avlinsert(&(*p)->rc,x,u);
  if(*u)
  switch ((*p)->bf) {
    case 1: (*p)->bf=0;*u=FALSE;break;
    case 0: (*p)->bf=-1;break;
    case -1:
    cout<<"\nTo be Rotated in Tree:::::";getch();cleardevice();
    display(*p,10*pow2(depth(*p)),RADIUS,0,0,1,1);
    getch();
    rightRotate(p,u);
  }
  return;
}
*u=FALSE;
printf("Duplication Error\n");
}

int main() {
   treeNode *T;
   T=NULL;
   int n;
    init();
    cout<<"\nEnter No of terms:";
    n=get_int();
    maxy=getmaxy();
    for(int i=1;i<=n;i++){
      element e;
      int *u;
      int t=FALSE;
      u=&t;
      cleardevice();
      cout<<"\nEnter data to insert:::::";
      e.key=get_int();
      cleardevice();
      avlinsert(&T,e,u);
      cleardevice();
      cout<<"\nAfter Insertion:::::::::";getch();cleardevice();
      display(T,10*pow2(depth(T)),RADIUS,0,0,1,1);
      getch();
     }
 getch();
 return 0;
}
