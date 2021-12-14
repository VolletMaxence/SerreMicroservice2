#pragma once

#include <QtWidgets/QMainWindow>
#include <QtMqtt/QtMqtt>


class MCulTT : public QObject
{
	Q_OBJECT

	public:
        MCulTT();

    private :
        QMqttClient * MFiakTT;
		//Ui::TestAplicationMotBusClass ui;

	public slots:
        void publish( QString Topic, QByteArray Message);
        void TEST( );

    signals:
        void jeSuisCoPetitePuteABite( );
};

