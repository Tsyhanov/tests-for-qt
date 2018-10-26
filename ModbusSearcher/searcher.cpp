#include "searcher.h"
#include <QDebug>
#include <QtSerialBus/QModbusRtuSerialMaster>
#include <QtTest/QTest>

Searcher::Searcher(QObject *parent) : QObject(parent){

    qDebug("Searcher constructor");
    setCurrSearchAddr(1);
    timer = new QTimer;

    modbusDevice = new QModbusRtuSerialMaster(this);
    if (!modbusDevice) {
        qDebug("Could not create Modbus Master");
        return;
    }
    connect(timer, SIGNAL(timeout()), this, SLOT(on_Timer()));
}

void Searcher::startSearch()
{
    qDebug() << "Start search";
    if (!modbusDevice){
        qDebug() << "Wrong Modbus device";
        return;
    }

    qDebug() << "Open port: " + currPort();

    if (modbusDevice->state() != QModbusDevice::ConnectedState) {
//            if (static_cast<ModbusConnection> (ui->connectType->currentIndex()) == Serial) {
            modbusDevice->setConnectionParameter(QModbusDevice::SerialPortNameParameter,
                currPort());
            modbusDevice->setConnectionParameter(QModbusDevice::SerialParityParameter,
                m_portSettings.parity);
            modbusDevice->setConnectionParameter(QModbusDevice::SerialBaudRateParameter,
                m_portSettings.baud);
            modbusDevice->setConnectionParameter(QModbusDevice::SerialDataBitsParameter,
                m_portSettings.dataBits);
            modbusDevice->setConnectionParameter(QModbusDevice::SerialStopBitsParameter,
                m_portSettings.stopBits);
            modbusDevice->setTimeout(m_portSettings.responseTime);
    }

    if (!modbusDevice->connectDevice())
        qDebug("Connect failed");
    //current search addr = startAddr
    setCurrSearchAddr(startAddr());
    //if modbus dev then start send request timer
    timer->setSingleShot(true);
    timer->start(100);
}


void Searcher::on_Timer()
{
    qDebug() << "onTimer:" << QString::number(currSearchAddr()) ;
    //sendRequest3 with every changed addr
    sendRequest3(currSearchAddr());
    setCurrSearchAddr(currSearchAddr()+1);
}

void Searcher::sendRequest3(const int &addr)
{
    qDebug() << "sendRequest3" + QString::number(addr);
    const auto table = QModbusDataUnit(QModbusDataUnit::HoldingRegisters, 100, 2);
    if (auto *reply = modbusDevice->sendReadRequest(table, addr)){
        if (!reply->isFinished())
            connect(reply, &QModbusReply::finished, this, &Searcher::readReady3);
        else
            delete reply;//broadcast
    } else {
        qDebug() << "sendRequest error";
    }
}

void Searcher::readReady3()
{
    qDebug("readReady3");
    auto reply = qobject_cast<QModbusReply *>(sender());
    if (!reply)
        return;

    if (reply->error() == QModbusDevice::NoError) {
        const QModbusDataUnit unit = reply->result();
        qDebug() << "valueCount:" + QString::number(unit.valueCount());
        for (uint i = 0; i < unit.valueCount(); i++) {
            qDebug() << "Address:" + QString::number(unit.startAddress() + i);
            qDebug() << "Value:" + QString::number(unit.value(i));
        }}
    else {
        qDebug() << "read error";
    }
    if (currSearchAddr()==endAddr()){
        qDebug() << "Stop timer!";
        timer->stop();
    } else {
        timer->setSingleShot(true);
        timer->start(100);
    }
}


QString Searcher::currPort(){
    return m_currPort;
}

void Searcher::setCurrPort(const QString &port){
    m_currPort = port;
    emit currPortChanged();
}

int Searcher::currSearchAddr(){
    return m_currSearchAddr;
}

void Searcher::setCurrSearchAddr(const int &addr){
    m_currSearchAddr = addr;
    emit currSearchAddrChanged();
}

int Searcher::startAddr(){
    return m_startAddr;
}

void Searcher::setStartAddr(const int &addr){
    m_startAddr = addr;
    emit startAddrChanged();
}

int Searcher::endAddr(){
    return m_endAddr;
}

void Searcher::setEndAddr(const int &addr){
    m_endAddr = addr;
    emit endAddrChanged();
}
