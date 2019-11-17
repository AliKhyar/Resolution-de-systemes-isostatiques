#include<stdio.h>
#include <stdlib.h>
#include<math.h>

typedef struct{
	float Pix;
	float Piy;
	float Xpi;
}ChPonctuelle;

typedef struct{
	float Qiy;
	float Xdeb;
	float Xfin;
}ChLineaire;

typedef struct{
    float Rxa;
    float Rya;
    float Ryb;
}ReactionAppui;

typedef struct{
    ChLineaire *arr_lin;
    ReactionAppui* ra;
}DataLin;
typedef struct{
    ChPonctuelle *arr_ponct;
    ReactionAppui* ra;
}DataPonct;
typedef struct{
    ChLineaire *arr_lin;
    ChPonctuelle *arr_ponct;
    ReactionAppui* ra;
}DataMixte;

static ReactionAppui reaction_appui;

ReactionAppui* calcul_reaction_ponct(int nb_charge_ponct, ChPonctuelle* arr_ponct, int L);
ReactionAppui* calcul_reaction_ponct(int nb_charge_lin, ChPonctuelle* arr_lin, int L);
void print_infos_ponct(int nb_charge_ponct,ChPonctuelle* arr_ponct,ReactionAppui* reaction_appui);
void print_infos_lin(int nb_charge_lin,ChLineaire* arr_lin,ReactionAppui* reaction_appui);
void print_infos_mix(int nb_charge_lin,int nb_charge_ponct,DataMixte* data_mix);
DataPonct choix_charg_ponct(int nb_charge_ponct,int L);
DataLin choix_charg_lin(int nb_charge_lin, int L);
DataMixte choix_calcul_charg_mixte(int nb_charge_ponct,int nb_charge_lin, int L);
void choix_sys1 ();
void choix_sys2 ();
void choix_sys3 ();
void choice();
void save_infos_ponct(float L,int nb_charge_ponct,DataPonct data_ponct);
void save_infos_lin(float L,int nb_charge_lin,DataLin data_lin);
void save_infos_mixte(float L,int nb_charge_ponct, int nb_charge_lin,DataMixte data_mix);


void main(){

    printf("Bonjour Cher utilisateur !");
    choice();
}



/*############# calculs ########################*/

ReactionAppui* calcul_reaction_ponct(int nb_charge_ponct, ChPonctuelle* arr_ponct, int L){
    int i;
    reaction_appui.Rxa=0;
    reaction_appui.Rya=0;
    reaction_appui.Ryb=0;
    for(i = 0; i < nb_charge_ponct; i++){
        reaction_appui.Rxa = reaction_appui.Rxa + abs(arr_ponct[i].Pix);
        reaction_appui.Rya = reaction_appui.Rya + (arr_ponct[i].Pix / L)*(L-arr_ponct[i].Xpi);
        reaction_appui.Ryb = reaction_appui.Ryb + (arr_ponct[i].Pix / L)*arr_ponct[i].Xpi;
    }
    return &reaction_appui;
}

ReactionAppui* calcul_reaction_lin(int nb_charge_lin, ChLineaire* arr_lin, int L){
    int i;
    int pow1;
    int pow2;
    reaction_appui.Rxa=0;
    reaction_appui.Rya=0;
    reaction_appui.Ryb=0;
    for(i = 0; i < nb_charge_lin; i++){
        pow1 = arr_lin[i].Xdeb*arr_lin[i].Xdeb;
        pow2 = arr_lin[i].Xfin*arr_lin[i].Xfin;
        reaction_appui.Rya = reaction_appui.Rya + (arr_lin[i].Qiy /(2*L))*(2*L*(L-arr_lin[i].Xdeb -arr_lin[i].Xfin)- (pow1 - pow2));
        reaction_appui.Ryb = reaction_appui.Ryb + (arr_lin[i].Qiy /(2*L))*(pow1 - pow2);
    }
    return &reaction_appui;
}


/*############# affichage ########################*/

void print_infos_ponct(int nb_charge_ponct,ChPonctuelle* arr_ponct,ReactionAppui* reaction_appui){
    int i;
    printf("---------------charge ponctuelles imposes: ---------------\n\n");
    printf("N\t Pix\t Piy\t Xpi\n");
    for(i = 0; i < nb_charge_ponct; i++){
        printf("%d\t %f\t %f\t %f\n", i+1,arr_ponct[i].Pix,arr_ponct[i].Piy,arr_ponct[i].Xpi );
    }
    
    printf("--------------Reaction d'appui--------------\n\n");
    printf("Rxa\t Rya\t Ryb\t");
    printf(" %f\t %f\t %f\n", reaction_appui->Rxa,reaction_appui->Rya,reaction_appui->Ryb);
}

void print_infos_lin(int nb_charge_lin,ChLineaire* arr_lin,ReactionAppui* reaction_appui){
    int i;
    printf("---------------charge lineaires imposes: ---------------\n\n");
    printf("N\t Qiy\t Xdeb\t Xfin\n");
    for(i = 0; i < nb_charge_lin; i++){
        printf("%d\t %f\t %f\t %f\n", i+1,arr_lin[i].Qiy,arr_lin[i].Xdeb,arr_lin[i].Xfin );
    }
    
    printf("--------------Reaction d'appui--------------\n\n");
    printf("Rxa\t Rya\t Ryb\t");
    printf(" %f\t %f\t %f\n", reaction_appui->Rxa,reaction_appui->Rya,reaction_appui->Ryb);
}

void print_infos_mix(int nb_charge_lin,int nb_charge_ponct,DataMixte *data_mix){
    int i;
    printf("---------------charge lineaires imposes: ---------------\n\n");
    printf("N\t Qiy\t Xdeb\t Xfin\n");
    for(i = 0; i < nb_charge_lin+1; i++){
        printf("%d\t %f\t %f\t %f\n", i+1,data_mix->arr_lin[i].Qiy,data_mix->arr_lin[i].Xdeb,data_mix->arr_lin[i].Xfin );
    }
    printf("---------------charge ponctuelles imposes: ---------------\n\n");
    printf("N\t Pix\t Piy\t Xpi\n");
    for(i = 0; i < nb_charge_ponct+1; i++){
        printf("%d\t %f\t %f\t %f\n", i+1,data_mix->arr_ponct[i].Pix,data_mix->arr_ponct[i].Piy,data_mix->arr_ponct[i].Xpi );
        printf("%d\t %f\t %f\t %f\n", i+1,data_mix->arr_ponct[i].Pix,data_mix->arr_ponct[i].Piy,data_mix->arr_ponct[i].Xpi );
        printf("%d\t %f\t %f\t %f\n", i+1,data_mix->arr_ponct[i].Pix,data_mix->arr_ponct[i].Piy,data_mix->arr_ponct[i].Xpi );
    }

    printf("--------------Reaction d'appui--------------\n\n");
    printf("Rxa\t Rya\t Ryb\t");
    printf(" %f\t %f\t %f\n", data_mix->ra->Rxa,data_mix->ra->Rya,data_mix->ra->Ryb);
}

/*############# choix des chargements ########################*/

DataPonct choix_charg_ponct(int nb_charge_ponct,int L){
    int i;
    float data;
    int enregistrement;
    ChPonctuelle *arr_ponct = (ChPonctuelle *)malloc(nb_charge_ponct * sizeof(ChPonctuelle));
    for(i = 0; i < nb_charge_ponct; i++){
        printf("Entrer la valeur en KN de la composante horisontale de la charge ponctuelle %d\n",i+1);
        printf("P%dx =",i+1);
		scanf("%f",&data);
        arr_ponct[i].Pix = data;
        printf("Entrer la valeur en KN de la composante verticale de la charge ponctuelle %d\n",i+1);
        printf("P%dy =",i+1);
        scanf("%f",&data);
        arr_ponct[i].Piy = data;
        printf("Entrer la valeur en m d'abscisse de la charge ponctuelle %d\n",i+1);
        printf("Xp%d =",i+1);
        scanf("%f",&data);
        arr_ponct[i].Xpi=data;   
	}
    
    ReactionAppui* reaction_appui = calcul_reaction_ponct( nb_charge_ponct, arr_ponct, L);
    DataPonct data_ponct;
    data_ponct.ra = reaction_appui;
    data_ponct.arr_ponct = arr_ponct;
    return data_ponct;
    
}  



DataLin choix_charg_lin(int nb_charge_lin,int L){
    int i;
    float data;
    int enregistrement;
    ChLineaire *arr_lin = (ChLineaire *)malloc(nb_charge_lin * sizeof(ChLineaire));
    for(int i = 0; i < nb_charge_lin; i++){
        printf("Entrer la valeur en KN de la composante horisontale de la charge ponctuelle %d\n",i+1);
		scanf("%f",&data);
        while(data>0){
            printf("Q%dy doit etre<0\nentrer une valeur valide\n",i+1);
            scanf("%f",&data);
        }
        arr_lin[i].Qiy = data;
        printf("Entrer la valeur en KN de la composante verticale de la charge ponctuelle %d\n",i+1);
        scanf("%f",&data);
        arr_lin[i].Xdeb = data;
        printf("Entrer la valeur en m d'abscisse de la charge ponctuelle %d\n",i+1);
        scanf("%f",&data);
        arr_lin[i].Xfin=data;
	}
    
    ReactionAppui* reaction_appui = calcul_reaction_lin( nb_charge_lin, arr_lin, L);
    

    DataLin data_lin;
    data_lin.ra = reaction_appui;
    data_lin.arr_lin = arr_lin;

    return data_lin;
}

DataMixte choix_calcul_charg_mixte(int nb_charge_ponct,int nb_charge_lin, int L){
    int i;
    //ChPonctuelle *arr_ponct = (ChPonctuelle *)malloc(nb_charge_ponct * sizeof(ChPonctuelle));
    //ChLineaire *arr_lin = (ChLineaire *)malloc(nb_charge_lin * sizeof(ChLineaire));
    DataMixte data_mix;
    DataLin data_lin;
    DataPonct data_ponct;
    data_mix.ra->Rxa =0;
    data_mix.ra->Rya = 0;
    data_mix.ra->Ryb = 0;
    data_lin = choix_charg_lin(nb_charge_lin,L);
    data_ponct = choix_charg_ponct(nb_charge_ponct,L);
    int pow1;
    int pow2;
    for(i = 0; i < nb_charge_lin; i++){
        data_mix.ra->Rya = data_mix.ra->Rya + data_lin.ra->Rya;
        data_mix.ra->Ryb = data_mix.ra->Ryb + data_lin.ra->Ryb;
    }
    for(i = 0; i < nb_charge_ponct; i++){
        data_mix.ra->Rya = data_mix.ra->Rya + data_ponct.ra->Rya;
        data_mix.ra->Ryb = data_mix.ra->Ryb + data_ponct.ra->Ryb;
    }    
    return data_mix;
}
/*############# choix de systeme ########################*/

void choix_sys1 (){ 
    float L;
    int choix_charg;
    int nb_charge_ponct, nb_charge_lin;
    int enregistrement;
    DataLin data_lin;
    DataPonct data_ponct;
    DataMixte data_mix;
    printf("********** RESOLUTION DE SYSTEME ISOSTATIQUE: POUTRE REPOSANT SUR DEUX APPUIS SANS DEBORDEMENT ********** \n\n ");
    printf("Choisissez la longueur de votre poutre: (0 < L < 10)m\n");
    printf("L (m) = ");
    scanf("%f",&L);
    while((L<=0) | (L>=10)){
        printf("Svp entrer une longueur >0 et <10 :");
        scanf("%f",&L);
    }
    printf("\n\n");
    printf("choisissez le type de chargement que vous disirez imposer a la poutre \n\n");
    printf("1  :  chargement ponctuel uniquement (5 chargements )\n");
    printf("2  :  chargement lineraire uniquement (2 chargements )\n");
    printf("3  :  chargement mixte (3 ponctuel et 1 lineaire \n");
    printf("choix de chargement ");
    scanf("%d",&choix_charg);
    switch (choix_charg){
    case 0:
        printf("Exiting the program....\n");
        exit(0);
    case 1:
        printf("choisisr le nombre de charge ponctuelles que vous desirer imposer: ");
        scanf("%d", &nb_charge_ponct);
        while((nb_charge_ponct>5) | (nb_charge_ponct<=0) ){
            printf("Entrer une valeur > 0 et < 5 \n");
            scanf("%d", &nb_charge_ponct);
        }   
        data_ponct = choix_charg_ponct(nb_charge_ponct,L);
        print_infos_ponct(nb_charge_ponct, data_ponct.arr_ponct,data_ponct.ra);
        printf("preferez vous d'entregistrer ces donnees? \n");
        printf("0  :  Non :\n");
        printf("1  :  Oui )\n");
        scanf("%d",&enregistrement);
        switch (enregistrement){
            case 1:
                save_infos_ponct(L,nb_charge_ponct, data_ponct);
                printf("\nbien enregistrees\n\n");
                free(data_ponct.arr_ponct);
                break;
            
            default:
                break;
        }
        break;
    case 2:
        printf("choisisr le nombre de charge lineaires que vous desirer imposer: ");
        scanf("%d", &nb_charge_lin);
        while((nb_charge_lin>2) | (nb_charge_lin<=0)){
            printf("Entrer une valeur > 0 et < 3 \n");
            scanf("%d", &nb_charge_lin);
        }
        data_lin = choix_charg_lin(nb_charge_lin, L);

        print_infos_lin(nb_charge_lin, data_lin.arr_lin,data_lin.ra);
        for_data_lin_equal_0:
        printf("preferez vous d'entregistrer ces donnees? \n");
        printf("0  :  Non :\n");
        printf("1  :  Oui )\n");
        scanf("%d",&enregistrement);
        switch (enregistrement)
        {
        case 1:
            
            save_infos_lin(L,nb_charge_lin, data_lin);
            printf("\nbien enregistrees\n\n");
            free(data_lin.arr_lin);
            break;
    
        default:
            break;
        }
        break;
    case 3:
        for_invalide_case:
        printf("choisisr le nombre de charge ponctuelles que vous desirer imposer: (3 max) ");
        scanf("%d", &nb_charge_ponct);
        if((nb_charge_ponct>3) | (nb_charge_ponct<=0) ){
            printf("Entrer une valeur < 4 \n");
            goto for_invalide_case;
        } 
        printf("choisisr le nombre de charge lineaires que vous desirer imposer: (1 max) ");
        scanf("%d", &nb_charge_lin);
        if(nb_charge_lin == 0){
            data_ponct = choix_charg_ponct(nb_charge_ponct, L);
            print_infos_ponct(nb_charge_ponct, data_ponct.arr_ponct,data_ponct.ra);
            printf("preferez vous d'entregistrer ces donnees? \n");
            printf("0  :  Non :\n");
            printf("1  :  Oui )\n");
            scanf("%d",&enregistrement);
            switch (enregistrement){
                case 1:
                    save_infos_ponct(L,nb_charge_ponct, data_ponct);
                    printf("\nbien enregistrees\n\n");
                    free(data_ponct.arr_ponct);
                    break;
                
                default:
                    break;
            }
            

        }else if(nb_charge_lin ==1){
            data_mix = choix_calcul_charg_mixte(nb_charge_ponct,1, L);
            print_infos_mix(nb_charge_lin,nb_charge_ponct, &data_mix);
            printf("preferez vous d'entregistrer ces donnees? \n");
            printf("0  :  Non :\n");
            printf("1  :  Oui )\n");
            scanf("%d",&enregistrement);
            switch (enregistrement){
                case 1:
                    save_infos_mixte(L,nb_charge_ponct, nb_charge_lin, data_mix);
                    printf("\nbien enregistrees\n\n");
                    free(data_mix.arr_ponct);
                    free(data_mix.arr_lin);

                    break;
                
                default:
                    break;
            }

            break;
        } else{
            goto for_invalide_case;            
            break;
        }

        break;
    default:
      
        break;
    }
    
}

void choix_sys2 (){
    printf("### Resolution de system isostatique compose d'une poutre reposant  sur 1 appuis ###\n\n");


}

void choix_sys3 (){
    printf("### Resolution de system isostatique Complexe compose d'un assemblage  de poutre isostatique ###\n\n");

}

void choice(){
    int choix_sys;
    label_name:
    printf("Choisissez le type de systeme que vous desirez resoudre :\n\n");
    printf("0  :  Quitter le programme :\n");
    printf("1  :  Resolution de system isostatique compose d'une poutre reposant  sur 2 appuis ( un appui double et un appui simple )\n");
    printf("2  :  Resolution de system isostatique compose d'une poutre reposant  sur 1 appuis un encastrement a gauche  et libre  a l'autre extremite\n");
    printf("3  :  Resolution de system isostatique Complexe compose d'un assemblage  de poutre isostatique\n\n");
    
    scanf("%d",&choix_sys);
    printf("%d",choix_sys);
    switch (choix_sys){
        case 0:
            printf("Exiting the program....\n");
            exit(0);
            break;
        case 1:
            choix_sys1();
            goto label_name;
        case 2:
            choix_sys2();
            goto label_name;
            
        case 3:
            choix_sys3();
        default:
            exit(0);
    }
}


/*############# enrigstrement des donnees ########################*/

void save_infos_ponct(float L,int nb_charge_ponct,DataPonct data_ponct){
    int i;
    char nom_prob[40];
    FILE *fptr;
    fptr = fopen("program.txt", "a");
    if(fptr == NULL){
        printf("Error!");
        exit(1);
    }
    printf("donner un nom a ce probleme: ");
    scanf("%s",nom_prob);
    fprintf(fptr,"#############################\n");
    fprintf(fptr,"\t\t%s\n",nom_prob);    
    fprintf(fptr,"Longueur de poutre \t\t%.2f\n",L);    

    fprintf(fptr,"---------------charge ponctuelles imposes: ---------------\n\n");
    fprintf(fptr,"N\t Pix\t Piy\t Xpi\n");
    for(i = 0; i < nb_charge_ponct; i++){
        fprintf(fptr,"%d\t %.2f\t %.2f\t %.2f\n", i+1,data_ponct.arr_ponct[i].Pix,data_ponct.arr_ponct[i].Piy,data_ponct.arr_ponct[i].Xpi );
    }
    
    fprintf(fptr,"--------------Reaction d'appui--------------\n\n");
    fprintf(fptr,"Rxa\t Rya\t Ryb\t");
    fprintf(fptr," %.2f\t %.2f\t %.2f\n\n", data_ponct.ra->Rxa,data_ponct.ra->Rya,data_ponct.ra->Ryb);
    fprintf(fptr,"\n\n");
    fclose(fptr);


}

void save_infos_lin(float L,int nb_charge_lin,DataLin data_lin){
    int i;
    char nom_prob[40];
    printf("donner un nom a ce probleme: ");
    FILE *fptr;
    fptr = fopen("program.txt", "a");
    if(fptr == NULL){
        printf("Error!");
        exit(1);
    }
    scanf("%s",nom_prob);
    fprintf(fptr,"#############################\n");
    fprintf(fptr,"\t\t%s\n",nom_prob);
    fprintf(fptr,"Longueur de poutre \t\t%.2f\n",L);
    fprintf(fptr,"---------------charge lineaires imposes: ---------------\n\n");
    fprintf(fptr,"N\t Qiy\t Xdeb\t Xfin\n");
    for(i = 0; i < nb_charge_lin; i++){
        fprintf(fptr,"%d\t %.2f\t %.2f\t %.2f\n", i+1,data_lin.arr_lin[i].Qiy,data_lin.arr_lin[i].Xdeb,data_lin.arr_lin[i].Xfin );
    }
    
    fprintf(fptr,"--------------Reaction d'appui--------------\n\n");
    fprintf(fptr,"Rxa\t Rya\t Ryb\t");
    fprintf(fptr," %.2f\t %.2f\t %.2f\n\n", data_lin.ra->Rxa,data_lin.ra->Rya,data_lin.ra->Ryb);
    fprintf(fptr,"\n\n");
    fclose(fptr);


}

void save_infos_mixte(float L,int nb_charge_ponct, int nb_charge_lin,DataMixte data_mix){
    int i;
    char nom_prob[40];
    printf("donner un nom a ce probleme: ");
    FILE *fptr;
    fptr = fopen("program.txt", "a");
    if(fptr == NULL){
        printf("Error!");
        exit(1);
    }

    scanf("%s",nom_prob);
    fprintf(fptr,"#############################\n");
    fprintf(fptr,"\t\t%s\n",nom_prob);
    fprintf(fptr,"Longueur de poutre \t\t%.2f\n",L);
    fprintf(fptr,"---------------charge ponctuelles imposes: ---------------\n\n");
    fprintf(fptr,"N\t Qiy\t Xdeb\t Xfin\n");
    for(i = 0; i < nb_charge_lin; i++){
        fprintf(fptr,"%d\t %.2f\t %.2f\t %.2f\n", i+1,data_mix.arr_ponct[i].Pix ,data_mix.arr_ponct[i].Piy,data_mix.arr_ponct[i].Xpi );
    }
    fprintf(fptr,"---------------charge lineaires imposes: ---------------\n\n");
    fprintf(fptr,"N\t Qiy\t Xdeb\t Xfin\n");
    for(i = 0; i < nb_charge_lin; i++){
        fprintf(fptr,"%d\t %f\t %f\t %f\n", i+1,data_mix.arr_lin[i].Qiy,data_mix.arr_lin[i].Xdeb,data_mix.arr_lin[i].Xfin );
    }
    
    fprintf(fptr,"--------------Reaction d'appui--------------\n\n");
    fprintf(fptr,"Rxa\t Rya\t Ryb\t");
    fprintf(fptr," %.2f\t %.2f\t %.2f\n", data_mix.ra->Rxa,data_mix.ra->Rya,data_mix.ra->Ryb);
    fprintf(fptr,"\n\n");
    fclose(fptr);


}


