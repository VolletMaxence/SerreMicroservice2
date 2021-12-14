#include "TestAplicationMotBus.h"
#include <QTimer>

TestAplicationMotBus::TestAplicationMotBus() {
    //ui.setupUi(this);

    BelloBito = new QModbusTcpClient( "192.168.65.19", 502 );
    BelloBito->connectToHost();
    Discipline = new MCulTT();
    qDebug() << "Constructeur lanc� 1";

    connect(BelloBito, &QModbusTcpClient::onReadMultipleInputsStatusSentence, this, &TestAplicationMotBus::onModbusSentence);

    //Qtimer pour faire ca tout les x temps (actuell : 10sec) :
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT( lectureTout() ));
    timer->start(10000);
}

void TestAplicationMotBus::onModbusSentence(quint16 startAddress, QVector<bool> values)
{
    qDebug() << values;
}

void TestAplicationMotBus::lectureTout() {

        //On cr�e une instance (et de l'espoir) : objet FC2
        BelloBito->readMultipleInputsStatusFC2(100, 2);

        this->HumidTerre1 = 50;
        this->HumidTerre2 = 50;
        this->HumidTerre3 = 50;

        this->HumidTerreMoy = (this->HumidTerre1 + this->HumidTerre2 + this->HumidTerre3) / 3;

        this->TempInter = 20;
        this->HumidInter = 90;


        this->TempExter = 30;

        qDebug() << "lectureTout lanc� 2 SVP marche sinon je me coupe la couille du milieu";


        if (this->TempInter < 1) //SI la temp�rature int�rieur est inf�rieur � 1�C
        {
            //qDebug() << "SI la temp�rature int�rieur est inf�rieur � 1�C";
            //Chauffage
            QString Topic = "heating";
            qDebug() << Topic;
            QByteArray Message = "start_heating";


            Discipline->publish( Topic, Message);

        } else {
            //Stop Chauffage
            QString Topic = "heating";
            qDebug() << Topic;
            QByteArray Message = "stop_heating";


            Discipline->publish( Topic, Message);
        }
        if (this->TempInter >= 10 && this->HumidInter >= 85)	//SI Temp�rature Interieur est sup�rieur ou �gal � 10�C ET Humidit� int�rieur sup�rieur ou �gal a 85%
        {
            //qDebug() << "SI Temp�rature Interieur est sup�rieur ou �gal � 10�C ET Humidit� int�rieur sup�rieur ou �gal a 85%";
            //Vasistas
            QString Topic = "vasistas";
            QByteArray Message = "start_vasistas";
            Discipline->publish(Topic, Message);

        }
        if (this->TempInter > 25)	//SI la temp�rature Interieur est sup�rieur a 25�C
        {
            //qDebug() << "SI la temp�rature Interieur est sup�rieur a 25�C";
            //Allume Brumisation
            QString Topic = "misting";
            QByteArray Message = "start_misting";
            Discipline->publish(Topic, Message);
        }
        if (this->TempInter > 25)	//SI la temp�rature Interieur est sup�rieur a 25�C
        {
            //qDebug() << "SI la temp�rature Interieur est sup�rieur a 25�C";
            //Allume Vasistas
            QString Topic = "vasistas";
            QByteArray Message = "start_vasistas";
            Discipline->publish(Topic, Message);
        }
        if (this->TempInter > 5 && this->HumidInter < 50)	//SI la temp�rature Interieur est sup�rieur a 5�C ET l'humidit� Interieur est inf�rieur � 50%
        {
            //qDebug() << "SI la temp�rature Interieur est sup�rieur a 5�C ET l'humidit� Interieur est inf�rieur � 50%";
            // Brumisation
            QString Topic = "misting";
            QByteArray Message = "start_misting";
            Discipline->publish(Topic, Message);
        }
        if (this->TempExter > this->TempInter && TempInter >= 10) //SI la temp�rature exterieur est plus grande que la temp�rature interieur et que la temp�rature interieur est sup�rieur ou egal a 10�C
        {
            qDebug() << "SI la temp�rature exterieur est plus grande que la temp�rature interieur et que la temp�rature interieur est sup�rieur ou egal a 10�C";
            //Vasistas
            QString Topic = "vasistas";
            QByteArray Message = "start_vasistas";
            Discipline->publish(Topic, Message);
        }
}

void TestAplicationMotBus::BrotherImStuck( quint16 startAddress, QVector<quint16> values )
{
    //BelloBito->readMultipleInputsStatusFC2(100, 1);
    qDebug() << values;
}
