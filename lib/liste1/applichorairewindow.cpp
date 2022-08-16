#include "applichorairewindow.h"
#include "ui_applichorairewindow.h"

#include <QDesktopWidget>
#include <QMessageBox>
#include <QInputDialog>
#include "./lib/Iterateur.h"
#include "./lib/Professeur.h"
#include "./lib/planifiable.h"
#include "./lib/Timing.h"
#include "./lib/ListeTriee.h"
#include "./lib/Temps.h"
#include "./lib/TempsException.h"
#include "./lib/TimingException.h"

#define DEBUG 0

#include <iostream>
using namespace std;


ApplicHoraireWindow::ApplicHoraireWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ApplicHoraireWindow)
{
    ui->setupUi(this);

    // Configuration de la table des professeurs
    ui->tableWidgetProfesseurs->setColumnCount(3);
    ui->tableWidgetProfesseurs->setRowCount(0);
    QStringList labelsTableProfesseurs;
    labelsTableProfesseurs << "id" << "Nom" << "Prenom";
    ui->tableWidgetProfesseurs->setHorizontalHeaderLabels(labelsTableProfesseurs);
    ui->tableWidgetProfesseurs->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidgetProfesseurs->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidgetProfesseurs->horizontalHeader()->setVisible(true);
    ui->tableWidgetProfesseurs->horizontalHeader()->setDefaultSectionSize(100);
    ui->tableWidgetProfesseurs->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidgetProfesseurs->verticalHeader()->setVisible(false);
    ui->tableWidgetProfesseurs->horizontalHeader()->setStyleSheet("background-color: lightyellow");

    // Configuration de la table des groupes
    ui->tableWidgetGroupes->setColumnCount(2);
    ui->tableWidgetGroupes->setRowCount(0);
    QStringList labelsTableGroupes;
    labelsTableGroupes << "id" << "Numero";
    ui->tableWidgetGroupes->setHorizontalHeaderLabels(labelsTableGroupes);
    ui->tableWidgetGroupes->setSelectionMode(QAbstractItemView::MultiSelection);
    ui->tableWidgetGroupes->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidgetGroupes->horizontalHeader()->setVisible(true);
    ui->tableWidgetGroupes->horizontalHeader()->setDefaultSectionSize(100);
    ui->tableWidgetGroupes->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidgetGroupes->verticalHeader()->setVisible(false);
    ui->tableWidgetGroupes->horizontalHeader()->setStyleSheet("background-color: lightyellow");

    // Configuration de la table des locaux
    ui->tableWidgetLocaux->setColumnCount(2);
    ui->tableWidgetLocaux->setRowCount(0);
    QStringList labelsTableLocaux;
    labelsTableLocaux << "id" << "Nom";
    ui->tableWidgetLocaux->setHorizontalHeaderLabels(labelsTableLocaux);
    ui->tableWidgetLocaux->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidgetLocaux->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidgetLocaux->horizontalHeader()->setVisible(true);
    ui->tableWidgetLocaux->horizontalHeader()->setDefaultSectionSize(100);
    ui->tableWidgetLocaux->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidgetLocaux->verticalHeader()->setVisible(false);
    ui->tableWidgetLocaux->horizontalHeader()->setStyleSheet("background-color: lightyellow");

    // Configuration de la table des cours
    ui->tableWidgetCourss->setColumnCount(8);
    ui->tableWidgetCourss->setRowCount(0);
    QStringList labelsTableCourss;
    labelsTableCourss << "code" << "Jour" << "Heure" << "Duree" << "Local" << "Intitule" << "Professeur" << "Groupes";
    ui->tableWidgetCourss->setHorizontalHeaderLabels(labelsTableCourss);
    ui->tableWidgetCourss->setSelectionMode(QAbstractItemView::NoSelection);
    //ui->tableWidgetCourss->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidgetCourss->horizontalHeader()->setVisible(true);
    ui->tableWidgetCourss->horizontalHeader()->setDefaultSectionSize(100);
    ui->tableWidgetCourss->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidgetCourss->verticalHeader()->setVisible(false);
    ui->tableWidgetCourss->horizontalHeader()->setStyleSheet("background-color: lightyellow");

    // Pour faire joli
    ui->pushButtonAjouterProfesseur->setStyleSheet("background-color: lightgreen");
    ui->pushButtonAjouterGroupe->setStyleSheet("background-color: lightgreen");
    ui->pushButtonAjouterLocal->setStyleSheet("background-color: lightgreen");
    ui->pushButtonSupprimerProfesseur->setStyleSheet("background-color: orange");
    ui->pushButtonSupprimerGroupe->setStyleSheet("background-color: orange");
    ui->pushButtonSupprimerLocal->setStyleSheet("background-color: orange");
    ui->pushButtonPlanifier->setStyleSheet("background-color: lightblue");
    ui->pushButtonSelectionner->setStyleSheet("background-color: lightblue");

    // On fixe la taille et la position de la fenetre
    setFixedSize(1070,647);
    move((QApplication::desktop()->width()-width())/2,(QApplication::desktop()->height()-height())/2);

    // Tests a supprimer ------------------------------------------------
  /*  ajouteTupleTableProfesseurs("1;Wagner;Jean-Marc");
    ajouteTupleTableProfesseurs("4;Leonard;Anne");
    ajouteTupleTableProfesseurs("6;Quettier;Patrick");

    ajouteTupleTableGroupes("4;G2221");
    ajouteTupleTableGroupes("6;G2222");
    ajouteTupleTableGroupes("7;G2201");
    ajouteTupleTableGroupes("9;G2203");
    ajouteTupleTableGroupes("10;G2204");

    ajouteTupleTableLocaux("23;AN");
    ajouteTupleTableLocaux("25;LP03");
    ajouteTupleTableLocaux("29;LE0");

    ajouteTupleTableCourss("1;Lundi;8h30;2h00;AN;Théorie C++;Wagner Jean-Marc;G2201,G2202");
    ajouteTupleTableCourss("3;Mardi;10h30;1h30;AN;Théorie UNIX;Quettier Patrick;G2225,G2226");
    ajouteTupleTableCourss("4;Jeudi;13h30;2h00;LE0;Labo C++;Leonard Anne;G2203");*/
    // -------------------------------------------------------------------
}

ApplicHoraireWindow::~ApplicHoraireWindow()
{
    delete ui;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Fonctions utiles Table des professeurs /////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicHoraireWindow::ajouteTupleTableProfesseurs(const char *tuple)
{
    // Controle du tuple recu et parsing
    char Tuple[200];
    strncpy(Tuple,tuple,199);
    char* tmp;

    if ((tmp = strtok(Tuple,";")) == NULL) return;
    char id[20];
    strcpy(id,tmp);

    if ((tmp = strtok(NULL,";")) == NULL) return;
    char nom[40];
    strcpy(nom,tmp);

    if ((tmp = strtok(NULL,";")) == NULL) return;
    char prenom[40];
    strcpy(prenom,tmp);

    // Ajout possible
    int nbLignes = ui->tableWidgetProfesseurs->rowCount();
    nbLignes++;
    ui->tableWidgetProfesseurs->setRowCount(nbLignes);

    QTableWidgetItem *item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    item->setTextAlignment(Qt::AlignCenter);
    item->setText(id);
    ui->tableWidgetProfesseurs->setItem(nbLignes-1,0,item);

    item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    item->setText(nom);
    ui->tableWidgetProfesseurs->setItem(nbLignes-1,1,item);

    item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    item->setText(prenom);
    ui->tableWidgetProfesseurs->setItem(nbLignes-1,2,item);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicHoraireWindow::videTableProfesseurs()
{
    ui->tableWidgetProfesseurs->setRowCount(0);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ApplicHoraireWindow::getIndiceProfesseurSelectionne()
{
    QModelIndexList liste = ui->tableWidgetProfesseurs->selectionModel()->selectedRows();
    if (liste.size() == 0) return -1;
    QModelIndex index = liste.at(0);
    int indice = index.row();
    return indice;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Fonctions utiles Table des groupes /////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicHoraireWindow::ajouteTupleTableGroupes(const char *tuple)
{
    // Controle du tuple recu et parsing
    char Tuple[200];
    strncpy(Tuple,tuple,199);
    char* tmp;

    if ((tmp = strtok(Tuple,";")) == NULL) return;
    char id[20];
    strcpy(id,tmp);

    if ((tmp = strtok(NULL,";")) == NULL) return;
    char numero[40];
    strcpy(numero,tmp);

    // Ajout possible
    int nbLignes = ui->tableWidgetGroupes->rowCount();
    nbLignes++;
    ui->tableWidgetGroupes->setRowCount(nbLignes);

    QTableWidgetItem *item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    item->setTextAlignment(Qt::AlignCenter);
    item->setText(id);
    ui->tableWidgetGroupes->setItem(nbLignes-1,0,item);

    item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    item->setText(numero);
    ui->tableWidgetGroupes->setItem(nbLignes-1,1,item);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicHoraireWindow::videTableGroupes()
{
    ui->tableWidgetGroupes->setRowCount(0);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ApplicHoraireWindow::getIndicesGroupesSelectionnes(int* tab)
{
    std::cerr << "debut getIndiceGroupeSelectionner" << std::endl;

    QModelIndexList liste = ui->tableWidgetGroupes->selectionModel()->selectedRows();
    if (liste.size() == 0) return 0;
    for (int i=0 ; i<liste.size() ; i++) tab[i] = liste.at(i).row();

    std::cerr << "fin getIndiceGroupeSelectionner" << std::endl;
    return liste.size();
}

int ApplicHoraireWindow::getIndicesGroupesSelectionnes()
{
    std::cerr << "debut getIndiceGroupeSelectionner 2" << std::endl;

    QModelIndexList liste = ui->tableWidgetGroupes->selectionModel()->selectedRows();
    if (liste.size() == 0) return -1;

    QModelIndex index = liste.at(0);
    int indice = index.row();

    std::cerr << "fin getIndiceGroupeSelectionner" << std::endl;
    return indice;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Fonctions utiles Table des locaux //////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicHoraireWindow::ajouteTupleTableLocaux(const char *tuple)
{
    // Controle du tuple recu et parsing
    char Tuple[200];
    strncpy(Tuple,tuple,199);
    char* tmp;

    if ((tmp = strtok(Tuple,";")) == NULL) return;
    char id[20];
    strcpy(id,tmp);

    if ((tmp = strtok(NULL,";")) == NULL) return;
    char nom[40];
    strcpy(nom,tmp);

    // Ajout possible
    int nbLignes = ui->tableWidgetLocaux->rowCount();
    nbLignes++;
    ui->tableWidgetLocaux->setRowCount(nbLignes);

    QTableWidgetItem *item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    item->setTextAlignment(Qt::AlignCenter);
    item->setText(id);
    ui->tableWidgetLocaux->setItem(nbLignes-1,0,item);

    item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    item->setText(nom);
    ui->tableWidgetLocaux->setItem(nbLignes-1,1,item);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicHoraireWindow::videTableLocaux()
{
    ui->tableWidgetLocaux->setRowCount(0);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ApplicHoraireWindow::getIndiceLocalSelectionne()
{
    QModelIndexList liste = ui->tableWidgetLocaux->selectionModel()->selectedRows();
    if (liste.size() == 0) return -1;
    QModelIndex index = liste.at(0);
    int indice = index.row();
    return indice;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Fonctions utiles Table des professeurs /////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicHoraireWindow::ajouteTupleTableCourss(const char *tuple)
{
    // Controle du tuple recu et parsing
    char Tuple[300];
    strncpy(Tuple,tuple,299);
    char* tmp;

    if ((tmp = strtok(Tuple,";")) == NULL) return;
    char code[20];
    strcpy(code,tmp);

    if ((tmp = strtok(NULL,";")) == NULL) return;
    char jour[20];
    strcpy(jour,tmp);

    if ((tmp = strtok(NULL,";")) == NULL) return;
    char heure[20];
    strcpy(heure,tmp);

    if ((tmp = strtok(NULL,";")) == NULL) return;
    char duree[20];
    strcpy(duree,tmp);

    if ((tmp = strtok(NULL,";")) == NULL) return;
    char local[20];
    strcpy(local,tmp);

    if ((tmp = strtok(NULL,";")) == NULL) return;
    char intitule[40];
    strcpy(intitule,tmp);

    if ((tmp = strtok(NULL,";")) == NULL) return;
    char professeur[60];
    strcpy(professeur,tmp);

    if ((tmp = strtok(NULL,";")) == NULL) return;
    char groupes[100];
    strcpy(groupes,tmp);

    // Ajout possible
    int nbLignes = ui->tableWidgetCourss->rowCount();
    nbLignes++;
    ui->tableWidgetCourss->setRowCount(nbLignes);

    QTableWidgetItem *item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    item->setTextAlignment(Qt::AlignCenter);
    item->setText(code);
    ui->tableWidgetCourss->setItem(nbLignes-1,0,item);

    item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    item->setText(jour);
    ui->tableWidgetCourss->setItem(nbLignes-1,1,item);

    item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    item->setText(heure);
    ui->tableWidgetCourss->setItem(nbLignes-1,2,item);

    item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    item->setText(duree);
    ui->tableWidgetCourss->setItem(nbLignes-1,3,item);

    item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    item->setText(local);
    ui->tableWidgetCourss->setItem(nbLignes-1,4,item);

    item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    item->setText(intitule);
    ui->tableWidgetCourss->setItem(nbLignes-1,5,item);

    item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    item->setText(professeur);
    ui->tableWidgetCourss->setItem(nbLignes-1,6,item);

    item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    item->setText(groupes);
    ui->tableWidgetCourss->setItem(nbLignes-1,7,item);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicHoraireWindow::videTableCourss()
{
    ui->tableWidgetCourss->setRowCount(0);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Fonctions permettant d'afficher des boites de dialogue /////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicHoraireWindow::dialogueMessage(const char* titre,const char* message)
{
   QMessageBox::information(this,titre,message);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicHoraireWindow::dialogueErreur(const char* titre,const char* message)
{
   QMessageBox::critical(this,titre,message);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char* ApplicHoraireWindow::dialogueDemandeTexte(const char* titre,const char* question)
{
    QString chaine = QInputDialog::getText(this,titre,question);
    strcpy(buffer,chaine.toStdString().c_str());
    return buffer;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ApplicHoraireWindow::dialogueDemandeInt(const char* titre,const char* question)
{
    return QInputDialog::getInt(this,titre,question);

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Fonctions utiles aux widgets de la fenetre /////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char* ApplicHoraireWindow::getNomProfesseur()
{
    strcpy(nomProfesseur,ui->lineEditNomProfesseur->text().toStdString().c_str());
    return nomProfesseur;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicHoraireWindow::setNomProfesseur(const char* nom)
{
    ui->lineEditNomProfesseur->setText(nom);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char* ApplicHoraireWindow::getPrenomProfesseur()
{
    strcpy(prenomProfesseur,ui->lineEditPrenomProfesseur->text().toStdString().c_str());
    return prenomProfesseur;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicHoraireWindow::setPrenomProfesseur(const char* nom)
{
    ui->lineEditPrenomProfesseur->setText(nom);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ApplicHoraireWindow::getNumeroGroupe()
{
    char tmp[80];
    strcpy(tmp,ui->lineEditNumeroGroupe->text().toStdString().c_str());
    int num = atoi(tmp);
    if (num == 0) num = -1;
    return num;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicHoraireWindow::videNumeroGroupe()
{
    ui->lineEditNumeroGroupe->setText("");
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char* ApplicHoraireWindow::getNomLocal()
{
    strcpy(nomLocal,ui->lineEditNomLocal->text().toStdString().c_str());
    return nomLocal;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicHoraireWindow::setNomLocal(const char* nom)
{
    ui->lineEditNomLocal->setText(nom);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char* ApplicHoraireWindow::getJourSelectionne()
{
    strcpy(jour,ui->comboBoxJour->currentText().toStdString().c_str());
    return jour;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ApplicHoraireWindow::getHeuresDebut()
{
    char tmp[80];
    strcpy(tmp,ui->lineEditHeuresDebut->text().toStdString().c_str());
    int num = atoi(tmp);
    return num;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicHoraireWindow::videHeuresDebut()
{
    ui->lineEditHeuresDebut->setText("");
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ApplicHoraireWindow::getMinutesDebut()
{
    char tmp[80];
    strcpy(tmp,ui->lineEditMinutesDebut->text().toStdString().c_str());
    int num = atoi(tmp);
    return num;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicHoraireWindow::videMinutesDebut()
{
    ui->lineEditMinutesDebut->setText("");
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ApplicHoraireWindow::getDuree()
{
    char tmp[80];
    strcpy(tmp,ui->lineEditDuree->text().toStdString().c_str());
    int num = atoi(tmp);
    if (num == 0) num = -1;
    return num;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicHoraireWindow::videDuree()
{
    ui->lineEditDuree->setText("");
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char* ApplicHoraireWindow::getIntitule()
{
    strcpy(intitule,ui->lineEditIntitule->text().toStdString().c_str());
    return intitule;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicHoraireWindow::setIntitule(const char* intitule)
{
    ui->lineEditIntitule->setText(intitule);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ApplicHoraireWindow::isJourChecked()
{
    return ui->checkBoxJour->isChecked();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicHoraireWindow::setJourChecked(bool b)
{
    ui->checkBoxJour->setChecked(b);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ApplicHoraireWindow::isProfesseurChecked()
{
    return ui->checkBoxProfesseur->isChecked();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicHoraireWindow::setProfesseurChecked(bool b)
{
    ui->checkBoxProfesseur->setChecked(b);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ApplicHoraireWindow::isGroupeChecked()
{
    return ui->checkBoxGroupe->isChecked();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicHoraireWindow::setGroupeChecked(bool b)
{
    ui->checkBoxGroupe->setChecked(b);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ApplicHoraireWindow::isLocalChecked()
{
    return ui->checkBoxLocal->isChecked();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicHoraireWindow::setLocalChecked(bool b)
{
    ui->checkBoxLocal->setChecked(b);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Fonctions clics sur les boutons ////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////
void ApplicHoraireWindow::on_pushButtonAjouterProfesseur_clicked()
{   
    Planifiable::idCourant++;
    cout << "Clic sur bouton Ajouter Professeur" << endl;

    if(strlen(getNomProfesseur()) == 0)
    {
        dialogueErreur("AjouterProfesseurErreur","Synthaxe : NOM=MAUVAIS!");
        return;
    }
    if(strlen(getPrenomProfesseur()) == 0)
    {
        dialogueErreur("AjouterProfesseurErreur","Synthaxe : PRENOM=MAUVAIS!");
        return;
    }

    videTableProfesseurs();
    horaire_.ajouteProfesseur(getNomProfesseur(),getPrenomProfesseur());

    Iterateur<Professeur> iterator( horaire_.getlisteProfesseurs() );
    for(iterator.reset();!iterator.end();iterator++)
    {
        Professeur professeur_{(Professeur)iterator};
        ajouteTupleTableProfesseurs(professeur_.Tuple());
    }

    setNomProfesseur(NULL);
    setPrenomProfesseur(NULL);

    #if DEBUG == 1

        horaire_.afficheProfesseurs();

    #endif

    //ApplicHoraireWindow::ajouteTupleTableProfesseurs(string_);
    // TO DO
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicHoraireWindow::on_pushButtonAjouterGroupe_clicked()
{
    cout << "Clic sur bouton Ajouter Groupe" << endl;
    Planifiable::idCourant++;

    if(getNumeroGroupe() == -1)
    {
        dialogueErreur("AjouterGroupeErreur","Synthaxe : NUMERO=MAUVAIS!");
        return;
    }

    videTableGroupes();
    horaire_.ajouteGroupe(getNumeroGroupe());

    Iterateur<Groupe> iterator(horaire_.getlisteGroupe());
    for(iterator.reset();!iterator.end();iterator++)
    {
        Groupe groupe_{(Groupe)iterator};
        ajouteTupleTableGroupes(groupe_.Tuple());
    }

    videNumeroGroupe();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicHoraireWindow::on_pushButtonAjouterLocal_clicked()
{
    cout << "Clic sur bouton Ajouter Local" << endl;    
    Planifiable::idCourant++;

    if(strlen(getNomLocal()) == 0)
    {
        dialogueErreur("AjouterLocalErreur","Synthaxe : NOM=MAUVAIS!");
        return;
    }

    videTableLocaux();
    horaire_.ajouteLocal(getNomLocal());

    Iterateur<Local> iterator(horaire_.getlisteLocaux());
    for(iterator.reset();!iterator.end();iterator++)
    {
        Local local_{(Local)iterator};
        ajouteTupleTableLocaux(local_.Tuple());
    }

    setNomLocal(NULL);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicHoraireWindow::on_pushButtonSupprimerProfesseur_clicked()
{
    cout << "Clic sur bouton Supprimer Professeur" << endl;
    
    int indice = getIndiceProfesseurSelectionne();
    Liste<Professeur>* professeur_{&horaire_.getlisteProfesseurs()};
    
    if(indice == -1 || !(professeur_->getNombreElements() > 0))
    {
        dialogueErreur("SupprimerProfesseurErreur","Pas d'item selectionne!");
        return;
    }

    horaire_.supprimeProfesseurParIndice(indice);

    /*if(professeur_->getNombreElements() == 0)
    {
        horaire_.getlisteProfesseurs();
    }*/
    
    videTableProfesseurs();    

    if(!(professeur_->getNombreElements() > 0))
    {
        std::cout << "fin supprimer + nbr="<<professeur_->getNombreElements() << "est vide ? = "<<professeur_->estVide() << std::endl;
        
        horaire_.afficheProfesseurs();
        return;
    }

    Iterateur<Professeur> iterator(horaire_.getlisteProfesseurs());

    for(iterator.reset();!iterator.end();iterator++)
    {
        Professeur prof_{(Professeur)iterator};
        ajouteTupleTableProfesseurs(prof_.Tuple());
    }

    std::cout << "fin supprimer" << std::endl;
    
    #if DEBUG == 1
        std::cout << "professeur est vide ? =" << professeur_->estVide() << std::endl;
        professeur_->Affiche();
        horaire_.afficheProfesseurs();
    #endif

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicHoraireWindow::TabTriFunc(const int& indice, int* const tab)
{
    ListeTriee<int> listeTri;
    std::cerr << "Affichage LISTETRI de tab[]="<< std::endl;
    for(int i = 0; i < indice;i++)
    {
        std::cerr << "valeur de tab[]=" << tab[i] << std::endl;
        listeTri.insere(tab[i]);
    }

    std::cerr << "Affichage 2 de tab[]="<< std::endl;
    for(int i = 0; i < indice;i++)
    {
        tab[i]=listeTri.retire(0);
        std::cerr << "valeur de tab[]=" << tab[i] << std::endl;        
    }
}
void ApplicHoraireWindow::on_pushButtonSupprimerGroupe_clicked()
{
    cout << "Clic sur bouton Supprimer Groupe" << endl;

    int *tab;
    Liste<Groupe>* groupe_{&horaire_.getlisteGroupe()};

    /*if(groupe_->getNombreElements() > 1)
        tab = new int[groupe_->getNombreElements()-1]{0};
    else*/
        tab = new int[groupe_->getNombreElements()]{0};

    int indice = getIndicesGroupesSelectionnes(tab);
    std::cout << "indice func = " << indice << std::endl;

    TabTriFunc(indice,tab);

    if(indice == 0 || !(groupe_->getNombreElements() > 0))
    {
        dialogueErreur("SupprimerGroupeErreur","Pas d'item selectionne!");
        return;
    }

    for(int i = 0;i<indice;i++)
    {        
        horaire_.supprimeGroupeParIndice(tab[i]-i);
        std::cout << "supprimer=" << tab[i] <<" valeur de i=" << i <<std::endl;
    }
    
    horaire_.afficheGroupes();
    videTableGroupes();    

    if(!(groupe_->getNombreElements() > 0))
    {
        std::cout << "fin supprimer + nbr="<<groupe_->getNombreElements() << "est vide ? = "<<groupe_->estVide() << std::endl;
        
        horaire_.afficheGroupes();
        return;
    }

    Iterateur<Groupe> iterator(horaire_.getlisteGroupe());

    for(iterator.reset();!iterator.end();iterator++)
    {
        Groupe grp_{(Groupe)iterator};
        ajouteTupleTableGroupes(grp_.Tuple());
    }    

    std::cout << "fin supprimer_on_Menu" << std::endl;

    delete[] tab;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicHoraireWindow::on_pushButtonSupprimerLocal_clicked()
{
    cout << "Clic sur bouton Supprimer Local" << endl;
    
    int indice = getIndiceLocalSelectionne();
    Liste<Local>* local_{&horaire_.getlisteLocaux()};
    
    if(indice == -1 || !(local_->getNombreElements() > 0))
    {
        dialogueErreur("SupprimerLocauxErreur","Pas d'item selectionne!");
        return;
    }

    horaire_.supprimeLocalParIndice(indice);
    
    videTableLocaux();    

    if(!(local_->getNombreElements() > 0))
    {
        std::cout << "fin supprimer + nbr="<<local_->getNombreElements() << "est vide ? = "<<local_->estVide() << std::endl;
        horaire_.afficheLocaux();
        return;
    }

    Iterateur<Local> iterator(horaire_.getlisteLocaux());

    for(iterator.reset();!iterator.end();iterator++)
    {
        Local loc_{(Local)iterator};
        ajouteTupleTableLocaux(loc_.Tuple());
    }

    std::cout << "fin supprimer" << std::endl;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicHoraireWindow::on_pushButtonPlanifier_clicked()
{
    cout << "Clic sur bouton Planifier" << endl;
    
    if(getIndiceProfesseurSelectionne() == -1)
    {
        dialogueErreur("PlannifierProfesseurErreur","Pas d'item=Professeur selectionne!");
        return;
    }
    if(getIndicesGroupesSelectionnes() == -1)
    {
        dialogueErreur("plannifierGroupeErreur","Pas d'item=Groupe selectionne!");
        return;
    }
    if(getIndiceLocalSelectionne() == -1)
    {
        dialogueErreur("PlannifierLocalErreur","Pas d'item=Local selectionne!");
        return;
    }

    //std::cout << "Fin des conditions bouton planifier" << std::endl;

    Liste<Professeur> listeProf_ = horaire_.getlisteProfesseurs();
    Liste<Local> listeLocal_ = horaire_.getlisteLocaux();
    Liste<Groupe> listeGrp_ = horaire_.getlisteGroupe();
    Liste<Groupe> New_listeGrp_;

    int* tab = new int[listeGrp_.getNombreElements()]{0};

    int indice = getIndicesGroupesSelectionnes(tab);

    TabTriFunc(indice,tab); 

    if(indice == 0 || !(listeGrp_.getNombreElements() > 0))
    {
        dialogueErreur("PlanifierGroupeErreur","Pas d'item selectionne!");
        return;
    }

    for(int i = 0;i<indice;i++)
    {        
        New_listeGrp_.insere(listeGrp_.retire(tab[i]-i));
        //std::cout << "supprimer=" << tab[i] <<" valeur de i=" << i <<std::endl;
    }

    //New_listeGrp_.Affiche();
    
    try
    {
        Timing timing_;

        timing_.setJour(getJourSelectionne());
        timing_.setHeure(Temps(getHeuresDebut(),getMinutesDebut()));

        int duree_ = getDuree();

        if(duree_ == -1)
        {
            duree_ = 0;
        }  

        timing_.setDuree(Temps(duree_)); 

        //declaration variable cours

        Cours cours2_;
        
        cours2_.setCode(Cours::compteur_Cours);
        cours2_.setIntitule(getIntitule());
        cours2_.setIdProfesseur((listeProf_.retire(getIndiceProfesseurSelectionne())).getId() );
        cours2_.setIdLocal((listeLocal_.retire(getIndiceLocalSelectionne())).getId() );


        cours2_.Affiche();
        //std::cout << "GetIDLOCAL=" << cours2_.getIdLocal() << std::endl;

        //fin entrance cours2

        Iterateur<Groupe> iterateurGrp_ = New_listeGrp_;
        Liste<int> listeIDgrp_;

        for(iterateurGrp_.reset();!iterateurGrp_.end();iterateurGrp_++)
        {
            listeIDgrp_.insere( ((Groupe)iterateurGrp_).getId() );
        }

        cours2_.setListeIdGroupe(listeIDgrp_);

        horaire_.planifie(cours2_,timing_);

        //timing_.Affiche();

        Iterateur<Cours> it_cours(horaire_.getlisteCours());
        videTableCourss();

        for(it_cours.reset();!it_cours.end();it_cours++)
        {
            //Cours c_cpy ( ((Cours)it_cours));
            //std::cout << "GetIDLOCAL=" << ((Cours)it_cours).getIdLocal() << std::endl;

            std::cout << std::endl << "Valeur getTiming.Affiche() = " << std::endl;
            ((Cours)it_cours).Affiche();

            std::cout << std::endl << "Ajoute table tuple" << std::endl;
            ajouteTupleTableCourss( horaire_.getTuple2( (Cours)it_cours ) );
        }

        delete[] tab;

        Cours::compteur_Cours++;

        videMinutesDebut();
        videHeuresDebut();
        videDuree();

        std::cout << "fin plannifier" << std::endl;
    }
    catch(TempsException& e)
    {
        dialogueErreur("tempsException",e.getmessage());
        std::cout << e.getmessage() << std::endl;
    }
    catch(TimingException& e)
    {
        dialogueErreur("timingException",e.getmessage());
        std::cout << e.getmessage() << std::endl;
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicHoraireWindow::on_pushButtonSelectionner_clicked()
{
    cout << "Clic sur bouton Selectionner" << endl;
    // TO DO
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Fonctions clics sur les items de menu //////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicHoraireWindow::on_actionQuitter_triggered()
{
    cout << "Clic sur Menu Fichier --> Item Quitter" << endl;
    // TO DO

    QApplication::quit();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicHoraireWindow::on_actionOuvrir_triggered()
{
    cout << "Clic sur Menu Fichier --> Item Ouvrir" << endl;

    char nomFichier[80];
    strcpy(nomFichier,dialogueDemandeTexte("Ouvrir Horaire...","Nom du fichier ?"));
    cout << "Nom fichier = " << nomFichier << endl;

    // TO DO
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicHoraireWindow::on_actionNouveau_triggered()
{
    cout << "Clic sur Menu Fichier --> Item Nouveau" << endl;
    // TO DO
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicHoraireWindow::on_actionEnregistrer_triggered()
{
    cout << "Clic sur Menu Fichier --> Item Enregistrer" << endl;

    char nomFichier[80];
    strcpy(nomFichier,dialogueDemandeTexte("Enregistrer Horaire...","Nom du fichier ?"));
    cout << "Nom fichier = " << nomFichier << endl;

    // TO DO
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicHoraireWindow::on_actionSupprimerProfesseur_triggered()
{
    cout << "Clic sur Menu Supprimer --> Item Professeur" << endl;
    
    int it = dialogueDemandeInt("SupprimerProfesseur","Entrez un ID");

    Liste<Professeur>* professeur_{&horaire_.getlisteProfesseurs()};
    
    if(it == -1 || !(professeur_->getNombreElements() > 0))
    {
        dialogueErreur("SupprimerProfesseurErreur","Pas d'item selectionne!");
        return;
    }

    horaire_.supprimeProfesseurParId(it);

    if(professeur_->getNombreElements() == 0)
    {
        horaire_.getlisteProfesseurs();
    }
    
    videTableProfesseurs();    

    if(!(professeur_->getNombreElements() > 0))
    {
        std::cout << "fin supprimer + nbr="<<professeur_->getNombreElements() << "est vide ? = "<<professeur_->estVide() << std::endl;
        
        horaire_.afficheProfesseurs();
        return;
    }

    Iterateur<Professeur> iterator(horaire_.getlisteProfesseurs());

    for(iterator.reset();!iterator.end();iterator++)
    {
        Professeur prof_{(Professeur)iterator};
        ajouteTupleTableProfesseurs(prof_.Tuple());
    }

    std::cout << "fin supprimer_on_Menu" << std::endl;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicHoraireWindow::on_actionSupprimerGroupe_triggered()
{
    cout << "Clic sur Menu Supprimer --> Item Groupe" << endl;

    int it = dialogueDemandeInt("SupprimerGroupe","Entrez un ID");


    Liste<Groupe>* groupe_{&horaire_.getlisteGroupe()};
    
    if(it == -1 || !(groupe_->getNombreElements() > 0))
    {
        dialogueErreur("SupprimerGroupeErreur","Pas d'item selectionne!");
        return;
    }

    horaire_.supprimeGroupeParId(it);

    if(groupe_->getNombreElements() == 0)
    {
        horaire_.getlisteGroupe();
    }
    
    videTableGroupes();    

    if(!(groupe_->getNombreElements() > 0))
    {
        std::cout << "fin supprimer + nbr="<<groupe_->getNombreElements() << "est vide ? = "<<groupe_->estVide() << std::endl;
        
        horaire_.afficheGroupes();
        return;
    }

    Iterateur<Groupe> iterator(horaire_.getlisteGroupe());

    for(iterator.reset();!iterator.end();iterator++)
    {
        Groupe grp_{(Groupe)iterator};
        ajouteTupleTableGroupes(grp_.Tuple());
    }

    std::cout << "fin supprimer_on_Menu" << std::endl;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicHoraireWindow::on_actionSupprimerLocal_triggered()
{
    cout << "Clic sur Menu Supprimer --> Item Local" << endl;

    int it = dialogueDemandeInt("SupprimerLocal","Entrez un ID");

    Liste<Local>* local_{&horaire_.getlisteLocaux()};
    
    if(it == -1 || !(local_->getNombreElements() > 0))
    {
        dialogueErreur("SupprimerProfesseurErreur","Pas d'item selectionne!");
        return;
    }

    horaire_.supprimeLocalParId(it);

    /*if(local_->getNombreElements() == 0)
    {
        horaire_.getlisteLocaux();
    }*/
    
    videTableLocaux();    

    if(!(local_->getNombreElements() > 0))
    {
        std::cout << "fin supprimer + nbr="<<local_->getNombreElements() << "est vide ? = "<<local_->estVide() << std::endl;
        
        horaire_.afficheLocaux();
        return;
    }

    Iterateur<Local> iterator(horaire_.getlisteLocaux());

    for(iterator.reset();!iterator.end();iterator++)
    {
        Local loc_{(Local)iterator};
        ajouteTupleTableLocaux(loc_.Tuple());
    }

    std::cout << "fin supprimer_on_Menu" << std::endl;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicHoraireWindow::on_actionSupprimerCours_triggered()
{
    cout << "Clic sur Menu Supprimer --> Item Cours" << endl;
    // TO DO
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicHoraireWindow::on_actionImporterProfesseurs_triggered()
{
    cout << "Clic sur Menu Importer --> Item Professeurs" << endl;
    // TO DO
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicHoraireWindow::on_actionImporterGroupes_triggered()
{
    cout << "Clic sur Menu Importer --> Item Groupes" << endl;
    // TO DO
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicHoraireWindow::on_actionImporterLocaux_triggered()
{
    cout << "Clic sur Menu Importer --> Item Locaux" << endl;
    // TO DO
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicHoraireWindow::on_actionExporterProfesseur_triggered()
{
    cout << "Clic sur Menu Exporter horaire --> Item Professeur" << endl;
    // TO DO
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicHoraireWindow::on_actionExporterGroupe_triggered()
{
    cout << "Clic sur Menu Exporter horaire --> Item Groupe" << endl;
    // TO DO
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicHoraireWindow::on_actionExporterLocal_triggered()
{
    cout << "Clic sur Menu Exporter horaire --> Item Local" << endl;
    // TO DO
}
