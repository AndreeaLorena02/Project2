#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct orasele
{
    char nume[40];
} orase;

int main()
{
    FILE *fisier,*file2,*fisier_noduri,*fisier_muchii,*fisier_oras1,*fisier_oras2,*fisier_oras3;
    char b[40],orasul[50],y[20];
    int n=0,i,ok=0,**B,**C,primul_el=1,poz_ant=-1,pozitie1=-1,suma=0,muchii=0,maxim=-100,poz[30],k=0,maxim2=-100,index_oras=-1;
    orase *A;
    A=(orase*)malloc(530*sizeof(orase)) ;

    B = (int **)malloc(520 * sizeof(int*));
    for(int i = 0; i < 520; i++)
        B[i] = (int *)malloc(520 * sizeof(int));

    C = (int **)malloc(520 * sizeof(int*));
    for(int i = 0; i < 520; i++)
        C[i] = (int *)malloc(520 * sizeof(int));

    for(i=0; i<520; i++)
    {
        for(int j=0; j<520; j++)
        {
            B[i][j]=0;
            C[i][j]=0;
        }
    }
    fisier=fopen("_all_files.txt","rt");
    if(fisier==NULL)
    {
        printf("Fisierul %s nu se poate deschide !","_all_files.txt");
        exit(1);
    }
//    while (fgets(b, sizeof(b), fisier))
//    {
//        printf("%s",b);
//    }

    while (fgets(b,40,fisier))
    {

        if(b[0]!='\0')
        {
            b[strlen(b)-1]='\0';
            //printf("%s \n", b);
        }

        file2=fopen(b,"rt");

        if(file2==NULL)
        {
            printf("Fisierul %s.txt nu se poate deschide !",b);
            exit(1);
        }

        y[0]=' ';
        while(fgets(orasul,50,file2))
        {
            ok=0;
            orasul[strlen(orasul)-1]='\0';
            //puts(orasul);
            for(i=0; i<n; i++)
            {
                if(strcmp(A[i].nume,orasul)==0)
                {
                    ok=1;
                }
            }

            if(ok==0)
            {
                strcpy(A[n].nume,orasul);
                n++;
            }
            if(primul_el!=1)
            {
                for(i=0; i<n; i++)
                {
                    if(strcmp(orasul,A[i].nume)==0)
                        pozitie1=i;
                    if(strcmp(y,A[i].nume)==0)
                        poz_ant=i;
                }

                B[pozitie1][poz_ant]=B[poz_ant][pozitie1]=1;
                C[poz_ant][pozitie1]=1;
            }


            primul_el++;
            strcpy(y,orasul);

        }

        fclose(file2);
        primul_el=1;

    }

    fisier_noduri=fopen("noduri.txt","wt");
    if(fisier_noduri==NULL)
    {
        printf("Fisierul %s nu se poate deschide !","noduri.txt");
        exit(1);
    }
    fprintf(fisier_noduri," %d ",n);
    fclose(fisier_noduri);
//    printf("\nOrasele sunt:\n");
//    for(i=0; i<n; i++)
//        printf("%s   ;",A[i].nume);

//    for(i=0; i<520; i++)
//    {
//        for(int j=0; j<520; j++)
//            printf("%d",B[i][j]);
//    }


//  for(i=0; i<520; i++)
//    {
//        for(int j=0; j<520; j++)
//            printf("%d",C[i][j]);
//    }

    fisier_muchii=fopen("muchii.txt","wt");
    if(fisier_muchii==NULL)
    {
        printf("Fisierul %s nu se poate deschide !","muchii.txt");
        exit(1);
    }

    for(i=0; i<520; i++)
        for(int j=0; j<520; j++)
            suma+=B[i][j];
    muchii=suma/2;
    fprintf(fisier_muchii," %d -neorientat ",muchii);
    fclose(fisier_muchii);

    fisier_oras1=fopen("primul.txt","wt");
    fisier_oras2=fopen("doilea.txt","wt");
    if(fisier_oras1==NULL)
    {
        printf("Fisierul %s nu se poate deschide !","primul.txt");
        exit(1);
    }
    if(fisier_oras2==NULL)
    {
        printf("Fisierul %s nu se poate deschide !","doilea.txt");
        exit(1);
    }

    for(i=0; i<520; i++)
    {
        suma=0;
        for(int j=0; j<520; j++)
            suma+=B[i][j];
        if(maxim<suma)
        {
            maxim=suma;
            pozitie1=i;
        }

        if(maxim2<suma && suma<maxim)
        {
            maxim2=suma;
        }
    }

    for(i=0; i<520; i++)
    {
        suma=0;
        for(int j=0; j<520; j++)
            suma+=B[i][j];
        if(maxim2==suma)
        {
            poz[k]=i;
            k++;
        }

    }

    fprintf(fisier_oras1,"Orasul cel mai vizitat este :%s.",A[pozitie1].nume);
    fprintf(fisier_oras2,"Al doilea cel mai vizitat oras/cele mai vizitate orase :");
    for(i=0; i<k; i++)
        fprintf(fisier_oras2," %s ",A[poz[i]].nume);
    fclose(fisier_oras1);
    fclose(fisier_oras2);


    fisier_oras3=fopen("orasul_meu.txt","wt");
    suma=0;
    for(i=0; i<520; i++)
    {
            if(strcmp(A[i].nume,"Slatina")==0)
                index_oras=i;

    }
     for(int j=0; j<520; j++)
        suma+=B[index_oras][j];

    fprintf(fisier_oras3,"Gradul statiei din Slatina este : %d.",suma);
    fclose(fisier_oras3);

    fclose(fisier);
    return 0;

}
