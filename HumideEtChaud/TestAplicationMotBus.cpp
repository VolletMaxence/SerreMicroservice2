#include "TestAplicationMotBus.h"
#include <QTimer>

TestAplicationMotBus::TestAplicationMotBus() {
    //ui.setupUi(this);

    BelloBito = new QModbusTcpClient( "192.168.65.19", 502 );
    BelloBito->connectToHost();
    Discipline = new MCulTT();
    qDebug() << "Constructeur lancé 1";

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

        //On crée une instance (et de l'espoir) : objet FC2
        BelloBito->readMultipleInputsStatusFC2(100, 2);

        this->HumidTerre1 = 50;
        this->HumidTerre2 = 50;
        this->HumidTerre3 = 50;

        this->HumidTerreMoy = (this->HumidTerre1 + this->HumidTerre2 + this->HumidTerre3) / 3;

        this->TempInter = 20;
        this->HumidInter = 90;


        this->TempExter = 30;

        qDebug() << "lectureTout lancé 2 SVP marche sinon je me coupe la couille du milieu";


        if (this->TempInter < 1) //SI la température intérieur est inférieur à 1°C
        {
            //qDebug() << "SI la température intérieur est inférieur à 1°C";
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
        if (this->TempInter >= 10 && this->HumidInter >= 85)	//SI Température Interieur est supérieur ou égal à 10°C ET Humidité intérieur supérieur ou égal a 85%
        {
            //qDebug() << "SI Température Interieur est supérieur ou égal à 10°C ET Humidité intérieur supérieur ou égal a 85%";
            //Vasistas
            QString Topic = "vasistas";
            QByteArray Message = "start_vasistas";
            Discipline->publish(Topic, Message);

        }
        if (this->TempInter > 25)	//SI la température Interieur est supérieur a 25°C
        {
            //qDebug() << "SI la température Interieur est supérieur a 25°C";
            //Allume Brumisation
            QString Topic = "misting";
            QByteArray Message = "start_misting";
            Discipline->publish(Topic, Message);
        }
        if (this->TempInter > 25)	//SI la température Interieur est supérieur a 25°C
        {
            //qDebug() << "SI la température Interieur est supérieur a 25°C";
            //Allume Vasistas
            QString Topic = "vasistas";
            QByteArray Message = "start_vasistas";
            Discipline->publish(Topic, Message);
        }
        if (this->TempInter > 5 && this->HumidInter < 50)	//SI la température Interieur est supérieur a 5°C ET l'humidité Interieur est inférieur à 50%
        {
            //qDebug() << "SI la température Interieur est supérieur a 5°C ET l'humidité Interieur est inférieur à 50%";
            // Brumisation
            QString Topic = "misting";
            QByteArray Message = "start_misting";
            Discipline->publish(Topic, Message);
        }
        if (this->TempExter > this->TempInter && TempInter >= 10) //SI la température exterieur est plus grande que la température interieur et que la température interieur est supérieur ou egal a 10°C
        {
            qDebug() << "SI la température exterieur est plus grande que la température interieur et que la température interieur est supérieur ou egal a 10°C";
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
