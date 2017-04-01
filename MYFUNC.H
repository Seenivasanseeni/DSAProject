int get_int(){
 char i[20];
 int n=0;
 cin>>i;
 for(int ii=0;ii<strlen(i);ii++){
 int asc=toascii(i[ii]);
 if((asc>=48)&&(asc<=57))
 {
 n*=10;
 n+=asc-48;
 }
 else exit(1);
 }
 return n;
}

int pow2(int x){
int f=1;
for(int i=1;i<=x;i++)
	f*=2;
return f;
}