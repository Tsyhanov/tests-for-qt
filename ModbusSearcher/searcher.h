#ifndef SEARCHER_H
#define SEARCHER_H

#include <QObject>
#include <QtSerialBus/QModbusClient>
#include <QtSerialPort/QSerialPort>
#include <QTimer>

class Searcher: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString m_currPort READ currPort WRITE setCurrPort NOTIFY currPortChanged);

    Q_PROPERTY(int m_currSearchAddr READ currSearchAddr WRITE setCurrSearchAddr NOTIFY currSearchAddrChanged);
    Q_PROPERTY(int m_startAddr READ startAddr WRITE setStartAddr NOTIFY startAddrChanged);
    Q_PROPERTY(int m_endAddr READ endAddr WRITE setEndAddr NOTIFY endAddrChanged);

public:
    Searcher(QObject *parent = nullptr);
    virtual ~Searcher() {};

    struct Settings {
        int parity = QSerialPort::EvenParity;
        int baud = QSerialPort::Baud19200;
        int dataBits = QSerialPort::Data8;
        int stopBits = QSerialPort::OneStop;
        int responseTime = 200;
        int numberOfRetries = 3;
    };

    QString currPort();
    void setCurrPort(const QString &addr);

    int currSearchAddr();
    void setCurrSearchAddr(const int &addr);

    int startAddr();
    void setStartAddr(const int &addr);

    int endAddr();
    void setEndAddr(const int &addr);


//    void startSearch();
    void sendRequest3(const int &addr);
    void readReady3();

signals:
    void currPortChanged();
    void currSearchAddrChanged();
    void startAddrChanged();
    void endAddrChanged();

public slots:
    void startSearch();

private slots:
    void on_Timer();

private:
    //timer
    QTimer *timer;
    //modbus device
    QModbusClient *modbusDevice;
    //port settings
    Settings m_portSettings;

    //current com port
    QString m_currPort;
    //current search address
    int m_currSearchAddr;
    //current find address
    int m_currFindAddr;
    //search settings
    int m_startAddr;
    int m_endAddr;
    //find param
    int m_currAddr;
    int m_currSpeed;

};
#endif // SEARCHER_H
