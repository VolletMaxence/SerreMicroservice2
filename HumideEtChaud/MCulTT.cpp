#include "MCulTT.h"

MCulTT::MCulTT()
{
    MFiakTT = new QMqttClient(this);

    MFiakTT->setHostname( "192.168.65.104" );
    MFiakTT->setPort( 1883 );
    MFiakTT->connectToHost();

    connect( MFiakTT, SIGNAL( connected() ), this, SLOT( TEST() ) );

    qDebug () << "MFiakTT Connecté";
}

void MCulTT::publish( QString Topic, QByteArray Message) {

    this->MFiakTT->publish( QMqttTopicName( Topic ), Message );
}

void MCulTT::TEST( ) {

    emit jeSuisCoPetitePuteABite( );

}
