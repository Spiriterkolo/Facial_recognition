//copyright Michel Chapron ENSEA Cergy-Pontoise
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

FILE *fio,*fir;

int puis_2(int n)
{
	long int k,res=1;
	for(k=1;k<=n;k++) res *=2;
	return res;

}

int main()
{
unsigned char chi;
int *io,*ir,*irr,*irv,*irb,som,som8,plage,plage8,n01,n018,ic,jc,offset,offset1,nbrpoint;
long int k,s=1,nbg;
register long int i,j;
long int dimx,dimy,dimxtemp,dimytemp,taille,nb;
char entree[35],sortie[35],chaine[10];
int TAB[100];
int jtab=0;



int ti[16]={0,-1,-2,-2,-2,-2,-2,-1,0,1,2,2,2,2,2,1};
int tj[16]={2,2,2,1,0,-1,-2,-2,-2,-2,-2,-1,0,1,2,2};
int t[17];
int ti8[8]={0,-1,-1,-1,0, 1,1,1};
int tj8[8]={1,1, 0,-1,-1,-1,0,1};
int t8[9];

printf("donner entree sans .pgm\n");
scanf("%s",entree);
strcat(entree,".pgm");

printf("donner sortie sans .ppm\n");
scanf("%s",sortie);
strcat(sortie,".ppm");

fio=fopen(entree,"rb");
fir=fopen(sortie,"wb+");

if(fio !=NULL) printf("ouverture du fichier in\n");
if(fir !=NULL) printf("ouverture du fichier out\n");

//lecture entete pgm
fscanf(fio,"%s\n",chaine);
fprintf(fir,"%s\n","P6");

i=0;
while(i<1)
{
	chi=fgetc(fio);
	fputc(chi,fir);
	if(chi=='\n') i++;
}

fscanf(fio,"%ld %ld\n",&dimx,&dimy);
fprintf(fir,"%ld %ld\n",dimx,dimy);

fscanf(fio,"%d\n",&nbg);
fprintf(fir,"%d\n",nbg);

printf("dimx=%d dimy=%d nbg=%d\n",dimx,dimy,nbg);

//allocation dynamique de mémoire des images io et ir
io=(int *)malloc(dimx*dimy*sizeof(int));
irr=(int *)malloc(dimx*dimy*sizeof(int));
irv=(int *)malloc(dimx*dimy*sizeof(int));
irb=(int *)malloc(dimx*dimy*sizeof(int));

ir=(int *)malloc(dimx*dimy*sizeof(int));
if(ir==NULL) printf("allocation ir impossible\n");

taille=dimx*dimy;
printf("taille=%ld\n",taille);

//lecture des pixels
for(i=0;i<dimy;i++)
	for(j=0;j<dimx;j++)
	{
		chi=(unsigned char)fgetc(fio);
		io[i*dimx+j]=(int)chi;
		ir[i*dimx+j]=0;
		irr[i*dimx+j]=io[i*dimx+j];
		irv[i*dimx+j]=io[i*dimx+j];
		irb[i*dimx+j]=io[i*dimx+j];
	}
dimxtemp=dimx;
dimytemp=dimy;
do
{
   dimxtemp=dimxtemp-1;
} while (  dimxtemp%10 !=0);
do
{
   dimytemp=dimytemp-1;

} while (  dimytemp%10 !=0);
printf("dimxtemp=%d dimytemp=%d \n",dimxtemp,dimytemp);

///////////////////////////////////////////////////////////////////
//TRAITEMENT
nb=0;

offset=dimxtemp/10;
offset1=dimytemp/10;


for(ic=0;ic<dimytemp;ic=ic+offset1)
	for(jc=0;jc<dimxtemp;jc=jc+offset){
	printf("ic=%d  \n",ic);
         printf("jc=%d  \n",jc);

       		 for(i=ic+2;i<ic+(offset1);i++)
            		for(j=jc+2;j<jc+(offset);j++)
	    {
	    	som=0;

	    	for(k=0;k<16;k++) if(io[(i+ti[k])*dimx+j+tj[k]]>io[i*dimx+j]) {som+=puis_2(k);t[k]=1;}
	    	else t[k]=0;
	        ir[i*dimx+j]=som;

	    	t[16]=t[0];n01=0;plage=0;
	    	for(k=1;k<17;k++)
	    	{
	    		if((t[k-1]==0)&&(t[k]==1)) n01++;
	    		if(k!=16) if(t[k]==1) plage++;
			}


		if(n01<2){
		if(plage==6)
			{
			som8=0;
	    	for(k=0;k<8;k++) if(io[(i+ti8[k])*dimx+j+tj8[k]]>io[i*dimx+j]) {som8+=puis_2(k);t8[k]=1;}
	    	else t8[k]=0;
	        ir[i*dimx+j]=som8;

	    	t8[8]=t8[0];n018=0;plage8=0;
	    	for(k=1;k<9;k++)
	    	{
	    		if((t8[k-1]==0)&&(t8[k]==1)) n018++;
	    		if(k!=8) if(t8[k]==1) plage8++;
			}

             if(n018<2){
		if(plage8==3) {
			irr[i*dimx+j]=255;irv[i*dimx+j]=0;irb[i*dimx+j]=0;
			irr[i*dimx+j+1]=255;irv[i*dimx+j+1]=0;irb[i*dimx+j+1]=0;
			irr[i*dimx+j-1]=255;irv[i*dimx+j-1]=0;irb[i*dimx+j-1]=0;
			irr[(i+1)*dimx+j]=255;irv[(i+1)*dimx+j]=0;irb[(i+1)*dimx+j]=0;
			irr[(i-1)*dimx+j]=255;irv[(i-1)*dimx+j]=0;irb[(i-1)*dimx+j]=0;
			nb++;

			}
				}
			}
	    	}

     	}
        TAB[jtab]=nb;
        jtab=jtab+1;
        nb=0;
	nbrpoint=nb;

    }
    for(i=0;i<100;i++){
 
    printf("\n nb=%ld",TAB[i]);
    nbrpoint=nbrpoint+TAB[i];


    }
   printf("\n nbrpoint=%ld",nbrpoint);

printf("\n nb=%ld",nb);
//FIN TRAITEMENT
///////////////////////////////////////////////////////////////////

//Sauvegarde de l image résultat dans le fichier fir
for(i=0;i<dimy;i++)
	for(j=0;j<dimx;j++)
	{
	fputc((unsigned char)irr[i*dimx+j],fir);
	fputc((unsigned char)irv[i*dimx+j],fir);
	fputc((unsigned char)irb[i*dimx+j],fir);
	}


//libération de de la mémoire des tableaux io et ir et fermeture des 2 fichiers fio et fir
free(io); free(ir);free(irr);free(irv);free(irb);
fclose(fio); fclose(fir);
return 0;
}
