#include "Horaire.h"
#include "TimingException.h"


Horaire::Horaire(){}
Horaire::~Horaire(){}

void Horaire::ajouteProfesseur(const char* nom,const char* prenom)
{
    Professeur prof(Planifiable::idCourant,nom,prenom);
    Professeurs.insere(prof);
}

void Horaire::afficheProfesseurs()
{
    Professeurs.Affiche();
}
void Horaire::supprimeProfesseurParIndice(int ind){ Professeurs.retire(ind); }
void Horaire::supprimeProfesseurParId(int id)
{
    Iterateur<Professeur> prof(Professeurs);
    
    int verif = 1;
    int i = 0;
    for (prof.reset(); !prof.end() && verif != 0;prof++)
    {
        Professeur recup = (Professeur)prof;
        if(id == recup.getId())
        {
            verif = 0;
            Professeurs.retire(i);
        }
        i++;
    }
    
}

void Horaire::ajouteGroupe(int numero)
{
    Groupe grp(Planifiable::idCourant,numero);
    Groupes.insere(grp);
}

void Horaire::afficheGroupes()
{
    Groupes.Affiche();
}
void Horaire::supprimeGroupeParIndice(int ind){ Groupes.retire(ind); }
void Horaire::supprimeGroupeParId(int id)
{
    Iterateur<Groupe> grp(Groupes);
    
    int verif = 1;
    int i = 0;
    for (grp.reset(); !grp.end() && verif != 0;grp++)
    {
        Groupe recup = (Groupe)grp;
        if(id == recup.getId())
        {
            verif = 0;
            Groupes.retire(i);
        }
        i++;
    }
}

void Horaire::ajouteLocal(const char* nom)
{
    Local loc(Planifiable::idCourant,nom);
    Locaux.insere(loc);
}

void Horaire::afficheLocaux()
{
    Locaux.Affiche();
}
void Horaire::supprimeLocalParIndice(int ind){ Locaux.retire(ind); }
void Horaire::supprimeLocalParId(int id)
{
    Iterateur<Local> loc(Locaux);
    
    int verif = 1;
    int i = 0;
    for (loc.reset(); !loc.end() && verif != 0;loc++)
    {
        Local recup = (Local)loc;
        if(id == recup.getId())
        {
            verif = 0;
            Locaux.retire(i);
        }
        i++;
    }
}

void Horaire::supprimeCoursParId(int id)
{
    Iterateur<Cours> cours_{Cours_};
    
    int verif = 1;
    int i = 0;
    for (cours_.reset(); !cours_.end() && verif != 0;cours_++)
    {
        Cours recup = (Cours)cours_;
        if(id == recup.getCode())
        {
            verif = 0;
            Cours_.retire(i);
        }
        i++;
    }
}

const Liste<Professeur>& Horaire::getlisteProfesseurs()const
{
    return Professeurs;
}
const Liste<Groupe>& Horaire::getlisteGroupe()const
{
    return Groupes;
}
const Liste<Local>& Horaire::getlisteLocaux()const
{
    return Locaux;
}

Liste<Professeur>& Horaire::getlisteProfesseurs()
{
    return Professeurs;
}
Liste<Groupe>& Horaire::getlisteGroupe()
{
    return Groupes;
}
Liste<Local>& Horaire::getlisteLocaux()
{
    return Locaux;
}

bool Horaire::professeurDisponible(int id,const Timing& timing)
{
    Iterateur<Cours> it{Cours_};

    bool b,c;
    for(it.reset();!it.end();it++)
    {
        b = ((Cours)it).getTiming().intersecte(timing);
        c = (((Cours)it).getIdProfesseur() == id);
        if(b == true && c == true)
        {
            std::cout << "ProfNonDisponible" <<std::endl;
            return false;
        }
    }
    std::cout << "ProfDisponible" <<std::endl;
    return true;
}

bool Horaire::groupeDisponible(int id,const Timing& timing) 
{
    Iterateur<Cours> it{Cours_};

    bool b,c;
    for(it.reset();!it.end();it++)
    {
        b = ((Cours)it).getTiming().intersecte(timing);
        c = ((Cours)it).contientIdGroupe(id);

        if( b == true && c == true)
        {
            std::cout << "GroupeNonDisponible" <<std::endl;
            return false;
        }
    }
    std::cout << "GroupeDisponible" <<std::endl;
    return true;
}

bool Horaire::localDisponible(int id,const Timing& timing)
{
    Iterateur<Cours> it{Cours_};
    bool b,c;
    for(it.reset();!it.end();it++)
    {
        b = ((Cours)it).getTiming().intersecte(timing);
        c = (((Cours)it).getIdLocal() == id);

        if( b == true && c == true)
        {
            std::cout << "LocalNonDisponible" <<std::endl;
            return false;
        }
    }
    std::cout << "LocalDisponible" <<std::endl;
    return true;
}
void Horaire::planifie(Cours& c,const Timing& t)
{

    /*try
    {*/
        //parcourir la liste des cours pour trouver celui qu'il nous faut
        Iterateur<Cours> Iterateur_ = Cours_;
        
        for(Iterateur_.reset();!Iterateur_.end();Iterateur_++)
        {
            std::cout << "((Cours)Iterateur_).getIdProfesseur()=" << ((Cours)Iterateur_).getIdProfesseur() << std::endl;
            std::cout << "c.getIdProfesseur()=" << c.getIdProfesseur() << std::endl;

            std::cout << "((Cours)Iterateur_).getIdLocal()=" << ((Cours)Iterateur_).getIdLocal() << std::endl;
            std::cout << "c.getIdLocal()=" << c.getIdLocal() << std::endl;

            if( ((Cours)Iterateur_).getIdProfesseur() == c.getIdProfesseur() && 
                ((Cours)Iterateur_).getIdLocal()      == c.getIdLocal() )
            {        
                std::cout << "getliste egale ? = " << (((Cours)Iterateur_).getListeIdGroupe() == c.getListeIdGroupe()) << std::endl;       
                if(((Cours)Iterateur_).getListeIdGroupe() == c.getListeIdGroupe()) 
                {
                    if( ((Cours)Iterateur_).getTiming().intersecte(t) == true )
                        {
                            std::cout << "debut throw" << std::endl;
                            throw TimingException(TimingException::AUCUN_TIMING,"timing/professeur/intersect = true");
                        }
                    break; 
                }                  
            }
        }
        
        c.setTiming(t);
        Cours_.insere(c);
        c.Affiche();


        Cours::compteur_Cours++;
    //}
    /*catch(TimingException &e)
    {
        throw ;
    }*/
}

const Liste<Cours>& Horaire::getlisteCours()const
{
    return Cours_;
}

Liste<Cours>& Horaire::getlisteCours()
{
    return Cours_;
}


const char* Horaire::getTuple2(const Cours& c)
{
    char* tab = new char[1000];strncpy(tab,"",1000);

    //Copies of the lists
    Iterateur<Professeur> prof_ = Professeurs;
    Iterateur<Groupe>     grp_  = Groupes;
    Iterateur<Local>      loc_  = Locaux;
    Iterateur<int>        iterateur_listeIdGroupe = c.getListeIdGroupe();
    
    Professeur        prof_recup_;
    Liste<Groupe>     grp_recup;
    Local             loc_recup;

    for(prof_.reset();!prof_.end();prof_++)
    {
        if( ((Professeur)prof_).getId() == c.getIdProfesseur() )
        {
            prof_recup_ = (Professeur)prof_;
            std::cout << "Professeur(id) recupere! =" << ((Professeur)prof_).getId() << std::endl;
            break;
        }
    }

    //std::cout << "Local(id) = " << c.getIdLocal() << std::endl;
    for(loc_.reset();!loc_.end();loc_++)
    {
        //std::cout << "Local(id) liste = " << ((Local)loc_).getId() << std::endl;

        if( ((Local)loc_).getId() == c.getIdLocal() )
        {
            loc_recup = (Local)loc_;
            std::cout << "Local(id) recupere! = " << ((Local)loc_).getId() << std::endl;
            break;
        }
    }

    for(grp_.reset();!grp_.end();grp_++)
    {
        for(iterateur_listeIdGroupe.reset();!iterateur_listeIdGroupe.end();iterateur_listeIdGroupe++)
        {
            if( ((Groupe)grp_).getId() == (int)iterateur_listeIdGroupe )
            {
                grp_recup.insere((Groupe)grp_);
                std::cout << "Groupe(id) recupere! =" << ((Groupe)grp_).getId() << std::endl;
                break;
            }
        }
    }

    //fin partie 1
    //partie 2 affichage
    //« 1;Mardi;8h30;2h00;AN;Théorie C++;Wagner Jean-Marc;G2201,G2203 »
    //using of Cours::compteur_Cours

    //1) recuperer tout les nom des groupes
    //std::cout << "Debut mise en affichage! grp_" << std::endl;

    char tab_grp[500] = "";
    Iterateur<Groupe> iterateur_grp_ = grp_recup;iterateur_grp_.reset();

    strcpy(tab_grp,((Groupe)iterateur_grp_).Txt());

    iterateur_grp_++;
    for(;!iterateur_grp_.end();iterateur_grp_++)
    {
        strcat(tab_grp,",");
        strcat(tab_grp,((Groupe)iterateur_grp_).Txt());
    }

    //std::cout << "fin mise en affichage= grp" << std::endl;
   // std::cout << "valeur de tab_grp =" << tab_grp << std::endl;

    //std::cout << "Debut sprintf=" << std::endl;
    //std::cout << "c func AFFICHE = " << std::endl;
    //c.getTiming().Affiche();
    //std::cout << "c FIN AFFICHE = " << std::endl;

    sprintf(tab,"%d;%s;%dh%d;%dh%d;%s;%s;%s;%s",c.getCode(),
    c.getTiming().getJour(),
    c.getTiming().getHeure().getHeure(),
    c.getTiming().getHeure().getMinute(),
    c.getTiming().getDuree().getHeure(),
    c.getTiming().getDuree().getMinute(),
    loc_recup.Txt(),
    c.getIntitule(),
    prof_recup_.Txt(),
    tab_grp);

    //std::cout << "Fin sprintf=" << std::endl;
    std::cout << "valeur de tab=" << std::endl << tab << std::endl << std::endl;

    return tab;
}

const char* Horaire::getTuple(const Cours& c)
{
    char* tab = new char[1000];strcpy(tab,"");
    int idLocal = c.getIdLocal();
    int idProfesseur = c.getIdProfesseur();
    Liste<int> listeIdgroupe = c.getListeIdGroupe();

    Iterateur<Professeur> itProf = Professeurs;
    Iterateur<Local> itLocal = Locaux;
    Iterateur<Groupe> itgrp = Groupes;
    Iterateur<int> itlisteGroupe = listeIdgroupe;

    Professeur prof; //element à recuperer pour l'affichage;
    Liste<Groupe> listegrp;
    Local loc;
    Timing timing_ = c.getTiming();

    itProf.reset();itLocal.reset();itgrp.reset();itlisteGroupe.reset();
    for(;!itProf.end() || !itLocal.end() ;itProf++,itLocal++)
    {
        if(idLocal == ((Local)itLocal).getId())
            loc = (Local)itLocal;
        if(idProfesseur == ((Professeur)itProf).getId())
            prof = (Professeur)itProf;
    }

    itgrp.reset();itlisteGroupe.reset();
    for(;!itgrp.end();itgrp++)
    {
        for(itlisteGroupe.reset();!itlisteGroupe.end();itlisteGroupe++)
        {
            if( ((int)itlisteGroupe) == ((Groupe)itgrp).getId() )
                listegrp.insere(((Groupe)itgrp));
        }
    }
    //«           1;Mardi;8h30 ;2h00 ;AN;Théorie C++;Wagner Jean-Marc;G2201,G2203 >>

    char tab_grp[200] = "";

    Iterateur<Groupe> itg = listegrp;
    bool istrue = false;
    for(itg.reset();!itg.end();itg++)
    {
        if(istrue == false)
        {
            strcpy(tab_grp,((Groupe)itg).Txt());
            strcat(tab_grp,",");
            istrue = true;
            continue;
        }
        
        strcat(tab_grp,((Groupe)itg).Txt());
        strcat(tab_grp,",");
    }


    sprintf(tab,"%d;%s;%dh%d;%dh%d;%s;%s;%s;%s",c.getCode(),
    timing_.getJour(),timing_.getHeure().getHeure(),timing_.getHeure().getMinute(),
    timing_.getDuree().getHeure(),timing_.getDuree().getMinute(),loc.Txt(),
    c.getIntitule(),prof.Txt(),tab_grp);
    
    return tab;
}

void Horaire::Save(const char* nomFichier)
{
    std::ofstream ofs;

    ofs.open(nomFichier, std::ofstream::out | std::ifstream::trunc); 

    ofs.write((char*)&Planifiable::idCourant,sizeof(int));

    int getNombreElement = Professeurs.getNombreElements();
    ofs.write((char*)&getNombreElement,sizeof(int));

    Iterateur<Professeur> ite_prof = Professeurs;
    for(ite_prof.reset();!ite_prof.end();ite_prof++)
    {
        ((Professeur)ite_prof).Save(ofs);
    }

    getNombreElement = Groupes.getNombreElements();
    ofs.write((char*)&getNombreElement,sizeof(int));

    Iterateur<Groupe> ite_grp = Groupes;
    for(ite_grp.reset();!ite_grp.end();ite_grp++)
    {
        ((Groupe)ite_grp).Save(ofs);
    }

    getNombreElement = Locaux.getNombreElements();
    ofs.write((char*)&getNombreElement,sizeof(int));

    Iterateur<Local> ite_loc = Locaux;
    for(ite_loc.reset();!ite_loc.end();ite_loc++)
    {
        ((Local)ite_loc).Save(ofs);
    }

    getNombreElement = Cours_.getNombreElements();
    ofs.write((char*)&getNombreElement,sizeof(int));

    Iterateur<Cours> ite_cours = Cours_;
    for(ite_cours.reset();!ite_cours.end();ite_cours++)
    {
        ((Cours)ite_cours).Save(ofs);
    }

    ofs.close();
}
void Horaire::Load(const char* nomFichier)
{
    std::ifstream ifs;

    std::cout << "Horaire::ouverture fichier" << std::endl;

    ifs.open(nomFichier, std::ifstream::in ); 

    std::cout << "Horaire::Lecture idCourant" << std::endl;
    ifs.read((char*)&Planifiable::idCourant,sizeof(int));

    std::cout << "Horaire::Lecture nbr element prof" << std::endl;
    int getNombreElement;
    ifs.read((char*)&getNombreElement,sizeof(int));

    for(int i = 0; i < getNombreElement;i++)
    {
        Professeur prof;
        std::cout << "Horaire::Lecture prof" << std::endl;
        prof.Load(ifs);
        Professeurs.insere(prof);
    }

    std::cout << "Horaire::Lecture nbr element groupe" << std::endl;
    ifs.read((char*)&getNombreElement,sizeof(int));

    for(int i = 0; i < getNombreElement;i++)
    {
        Groupe grp;
        std::cout << "Horaire::Lecture groupe" << std::endl;
        grp.Load(ifs);
        Groupes.insere(grp);
    }

    std::cout << "Horaire::Lecture nbr element local" << std::endl;
    ifs.read((char*)&getNombreElement,sizeof(int));

    for(int i = 0; i < getNombreElement;i++)
    {
        Local loc;
        std::cout << "Horaire::Lecture Local" << std::endl;
        loc.Load(ifs);
        Locaux.insere(loc);
    }

    std::cout << "Horaire::Lecture nbr element cours" << std::endl;
    ifs.read((char*)&getNombreElement,sizeof(int));

    for(int i = 0; i < getNombreElement;i++)
    {
        std::cout << "i(" << i << ") < Element(" << getNombreElement << ")" << std::endl;
        Cours crs;
        std::cout << "Horaire::Lecture cours" << std::endl;
        crs.Load(ifs);
        std::cout << "Horaire::Lecture apres Cours" << std::endl;
        Cours_.insere(crs);
        std::cout << "Horaire::Lecture apres insere Cours" << std::endl;
    }

    std::cout << "Horaire::fermeture" << std::endl;
    ifs.close();
}

Horaire& Horaire::operator=(const Horaire& hor)
{
    Professeurs = hor.getlisteProfesseurs();
    Groupes     = hor.getlisteGroupe();
    Locaux      = hor.getlisteLocaux();
    Cours_      = hor.getlisteCours();

    return *this;
}

void Horaire::importeProfesseurs(const char* nomFichier)
{
    std::string token_nom;
    std::string token_prenom;

    std::ifstream ifst(nomFichier, std::ifstream::in);
    if(ifst.is_open())
    {
        while( !ifst.eof())
        {
            std::getline(ifst,token_nom,';');
            std::getline(ifst,token_prenom,'\n');

            size_t found = token_prenom.find(';');
            token_prenom.erase(found);

            Planifiable::idCourant++;

            //std::cout << token_nom << " : " <<  token_prenom << std::endl;

            Professeur prof( Planifiable::idCourant,token_nom.c_str(),token_prenom.c_str() );

            Professeurs.insere( prof );
            std::cout << prof.getNom() << " : " << prof.getPrenom() << std::endl;        

        }
        std::cout << "fin importer" << std::endl;
    }
    else
        std::cout << "fichier non ouvert!" << std::endl;
    
    ifst.close();
}
void Horaire::importeGroupes(const char* nomFichier)
{
    std::ifstream ifst(nomFichier,std::ifstream::in);

    if(!ifst.is_open())
    {
        std::cout<< "Fichier non ouvert!" << std::endl;
        return;
    }

    while(!ifst.eof())
    {
        std::string numero_;

        std::getline(ifst,numero_,';');

        Planifiable::idCourant++;

        Groupe grp_;

        if(strcmp("\0",numero_.c_str()) != 0)
        {
            //std::cout << "valeur de numero = " << atoi(numero_.c_str()) << std::endl;
            grp_.setId(Planifiable::idCourant);
            grp_.setNumero(atoi(numero_.c_str()));
            std::cout << "Valeur de grp_ =" << grp_.getNumero() << std::endl;
            Groupes.insere(grp_);
        }
        
    }

    ifst.close();
}
void Horaire::importeLocaux(const char* nomFichier)
{
    std::string token_nom;

    std::ifstream ifst(nomFichier, std::ifstream::in);
    if(ifst.is_open())
    {
        while( !ifst.eof())
        {
            std::getline(ifst,token_nom,'\n');

            size_t found = token_nom.find(';');
            token_nom.erase(found);

            Planifiable::idCourant++;

            std::cout << token_nom << std::endl;

            Local loc( Planifiable::idCourant,token_nom.c_str());
            Locaux.insere( loc );
            //std::cout << loc.getNom() << std::endl;        

        }
        std::cout << "fin importer" << std::endl;
    }
    else
        std::cout << "fichier non ouvert!" << std::endl;
    
    ifst.close();
}
void Horaire::exporteHoraireProfesseur(int id)
{
    Iterateur<Professeur> Iterateur_prof = Professeurs;
    Professeur prof_recup;
    for(Iterateur_prof.reset();!Iterateur_prof.end();Iterateur_prof++)
    {
        if(id == ((Professeur)Iterateur_prof).getId())
        {
            prof_recup = (Professeur)Iterateur_prof;
            break;
        }
    }

    char filename[100]; 
    strcpy(filename,prof_recup.getNom());
    strcat(filename,"_");
    strcat(filename,prof_recup.getPrenom());
    strcat(filename,".txt");

    std::cout << "ouverture du fichier=" << filename << std::endl;
    std::ofstream ofs(filename,std::ofstream::out | std::ofstream::trunc  );
    if(!ofs.is_open())
    {
        std::cout << "ERREUR=Fichier non Ouvert" << std::endl ;
        return;
    }

    ofs << "horaire de " << prof_recup.getPrenom() << " " << prof_recup.getNom() << " :" << std::endl << std::endl;

    // Jour heure duree local intitule Liste<groupes>

    //parcourir les cours
    Iterateur<Cours> Iterateur_ = Cours_;
    for(Iterateur_.reset();!Iterateur_.end();Iterateur_++)
    {
        //cours ou le prof donne cours
        if(id == ((Cours)Iterateur_).getIdProfesseur())
        {     
            //on recupere le local correspondant au cours 
            std::cout << "on recupere le local correspondant au cours " << std::endl;
            Iterateur<Local> current_local = Locaux;
            Local loc_;
            for(current_local.reset();!current_local.end();current_local++)
            {
                if(((Cours)Iterateur_).getIdLocal() == ((Local)current_local).getId())
                {
                    loc_ = (Local)current_local;
                    //std::cout << "local="<<loc_.getNom() << std::endl;
                    break;
                }
            }

            Iterateur<Groupe> Iterateur_grp = Groupes;
            Cours c_ = (Cours)Iterateur_;
            Iterateur<int>    ite_id = c_.getListeIdGroupe();
            ListeTriee<Groupe> grp_recup;

            std::cout << "debut iterateur 1" << std::endl;
            for(Iterateur_grp.reset();!Iterateur_grp.end();Iterateur_grp++)
            {
                //std::cout << "id groupe?=" << ((Groupe)Iterateur_grp).getId() << std::endl;
                for(ite_id.reset(); !ite_id.end(); ite_id++)
                {
                    std::cout << "valeur= " << (int)ite_id << std::endl;

                    if(((Groupe)Iterateur_grp).getId() == (int)ite_id)
                    {
                        std::cout << "condition vraie !" << std::endl;
                        grp_recup.insere( (Groupe)Iterateur_grp );
                    }
                }
            }
            std::cout << "fin iterateur 1" << std::endl;
            
            Iterateur<Groupe> tab_make = grp_recup;
            tab_make.reset();
            char tab_of_grp_[1000] = "";

            strcpy(tab_of_grp_,((Groupe)tab_make).Txt());

            for(tab_make.reset();!tab_make.end();tab_make++)
            {
                strcat(tab_of_grp_,",");
                strcat(tab_of_grp_,((Groupe)tab_make).Txt());                
            }



            std::cout << "valeur de tab : " << tab_of_grp_ << std::endl;
            // Jour heure duree local intitule Liste<groupes>
            ofs << ((Cours)Iterateur_).getTiming().getJour() << " " <<((Cours)Iterateur_).getTiming().getHeure() << " " << ((Cours)Iterateur_).getTiming().getDuree() << " " << loc_.getNom() << "  " << ((Cours)Iterateur_).getIntitule() << "     " << tab_of_grp_ << std::endl;
            
        }
    }

    ofs.close();
    std::cout << "fin ExportProfesseur" << std::endl;
}
void Horaire::exporteHoraireGroupe(int id)
{
    Iterateur<Groupe> Iterateur_grp = Groupes;
    Groupe grp_recup;
    for(Iterateur_grp.reset();!Iterateur_grp.end();Iterateur_grp++)
    {
        if(id == ((Groupe)Iterateur_grp).getId())
        {
            grp_recup = (Groupe)Iterateur_grp;
            break;
        }
    }

    char filename[100]; 
    strcpy(filename,grp_recup.Txt());
    strcat(filename,".txt");

    std::cout << "ouverture du fichier=" << filename << std::endl;
    std::ofstream ofs(filename,std::ofstream::out | std::ofstream::trunc  );
    if(!ofs.is_open())
    {
        std::cout << "ERREUR=Fichier non Ouvert" << std::endl ;
        return;
    }

    ofs << "horaire de " << grp_recup.Txt() << " :" << std::endl << std::endl;

    ListeTriee<int> liste_groupe;

    Iterateur<Cours> iterateur_cours = Cours_;
    for(iterateur_cours.reset();!iterateur_cours.end();iterateur_cours++)
    {
        Cours c = ((Cours)iterateur_cours);
        Iterateur<int> ite_idGrp = c.getListeIdGroupe();
        for(ite_idGrp.reset();!ite_idGrp.end();ite_idGrp++)
        {
            if(id == (int)ite_idGrp)
            {
                Professeur rec_prof;
                Iterateur<Professeur> ite_prof = Professeurs;
                for(ite_prof.reset();!ite_prof.end();ite_prof++)
                {
                    if(c.getIdProfesseur() == ((Professeur)ite_prof).getId())
                    {
                        rec_prof = (Professeur)ite_prof;
                        break;
                    }
                }

                Local rec_loc;
                Iterateur<Local> ite_loc = Locaux;
                for(ite_loc.reset();!ite_loc.end();ite_loc++)
                {
                    if(c.getIdLocal() == ((Local)ite_loc).getId())
                    {
                        rec_loc = (Local)ite_loc;
                        break;
                    }
                }

                ofs << c.getTiming().getJour() << " " << c.getTiming().getHeure() << " " << c.getTiming().getDuree() << " " << rec_loc.getNom() << "  " << c.getIntitule() << "     " << rec_prof.getNom() << " " << rec_prof.getPrenom() << std::endl;
            }
        }

    }

    ofs.close();
    std::cout << "Fermeture fichier" << std::endl;
}
void Horaire::exporteHoraireLocal(int id)
{
    Iterateur<Local> Iterateur_loc = Locaux;
    Local loc_recup;
    for(Iterateur_loc.reset();!Iterateur_loc.end();Iterateur_loc++)
    {
        if(id == ((Local)Iterateur_loc).getId())
        {
            loc_recup = (Local)Iterateur_loc;
            break;
        }
    }

    char filename[100]; 
    strcpy(filename,loc_recup.getNom());
    strcat(filename,".txt");

    std::cout << "ouverture du fichier=" << filename << std::endl;
    std::ofstream ofs(filename,std::ofstream::out | std::ofstream::trunc  );
    if(!ofs.is_open())
    {
        std::cout << "ERREUR=Fichier non Ouvert" << std::endl ;
        return;
    }

    ofs << "horaire de " << loc_recup.getNom() << " :" << std::endl << std::endl;

    Iterateur<Cours> Iterateur_ = Cours_;
    for(Iterateur_.reset();!Iterateur_.end();Iterateur_++)
    {
        //cours ou le cours à lieux
        if(id == ((Cours)Iterateur_).getIdLocal())
        {     
            //on recupere le professeur correspondant au cours 
            std::cout << "on recupere le local correspondant au cours " << std::endl;
            Iterateur<Professeur> current_prof = Professeurs;
            Professeur prof_;
            for(current_prof.reset();!current_prof.end();current_prof++)
            {
                if(((Cours)Iterateur_).getIdProfesseur() == ((Professeur)current_prof).getId())
                {
                    prof_ = (Professeur)current_prof;
                    //std::cout << "local="<<loc_.getNom() << std::endl;
                    break;
                }
            }

            Iterateur<Groupe> Iterateur_grp = Groupes;
            Cours c_ = (Cours)Iterateur_;
            Iterateur<int>    ite_id = c_.getListeIdGroupe();
            ListeTriee<Groupe> grp_recup;

            std::cout << "debut iterateur 1" << std::endl;
            for(Iterateur_grp.reset();!Iterateur_grp.end();Iterateur_grp++)
            {
                //std::cout << "id groupe?=" << ((Groupe)Iterateur_grp).getId() << std::endl;
                for(ite_id.reset(); !ite_id.end(); ite_id++)
                {
                    std::cout << "valeur= " << (int)ite_id << std::endl;

                    if(((Groupe)Iterateur_grp).getId() == (int)ite_id)
                    {
                        std::cout << "condition vraie !" << std::endl;
                        grp_recup.insere( (Groupe)Iterateur_grp );
                    }
                }
            }
            std::cout << "fin iterateur 1" << std::endl;
            
            Iterateur<Groupe> tab_make = grp_recup;
            tab_make.reset();
            char tab_of_grp_[1000] = "";

            strcpy(tab_of_grp_,((Groupe)tab_make).Txt());

            for(tab_make.reset();!tab_make.end();tab_make++)
            {
                strcat(tab_of_grp_,",");
                strcat(tab_of_grp_,((Groupe)tab_make).Txt());                
            }



            std::cout << "valeur de tab : " << tab_of_grp_ << std::endl;
            // Jour heure duree local intitule Liste<groupes>
            ofs << ((Cours)Iterateur_).getTiming().getJour() << " " <<((Cours)Iterateur_).getTiming().getHeure() << " " << ((Cours)Iterateur_).getTiming().getDuree()  << " " << ((Cours)Iterateur_).getIntitule() << "  " << prof_.getNom() << " " << prof_.getPrenom()  << "     " << tab_of_grp_ << std::endl;
            
        }
    }

    ofs.close();
    std::cout << "Fermeture du fichier" << std::endl;
}