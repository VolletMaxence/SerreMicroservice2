#pragma once

#include <QtWidgets/QMainWindow>
#include "qmodbustcpclient.h"
#include "MCulTT.h"

class TestAplicationMotBus : public QObject {

        Q_OBJECT

    public:
        TestAplicationMotBus();
        //Ui::TestAplicationMotBusClass ui;
        QModbusTcpClient * BelloBito;
        MCulTT * Discipline;
        QTcpSocket * twc241;

    private:

        //lecteur pour les 3 capteur humidit� terrestre
        float HumidTerre1;
        float HumidTerre2;
        float HumidTerre3;
        float HumidTerreMoy;
        //Lecteur humidit� int�rieur
        float HumidInter;
        //Lecteur temperature interieur
        float TempInter;
        //Lecteur temp�rature exterieur (non c est pas branch� mdr)
        float TempExter;

    public slots:
        void BrotherImStuck( quint16 startAddress, QVector<quint16> values );
        void lectureTout();
        void onModbusSentence(quint16 startAddress, QVector<bool> values);
};
