#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtBluetooth>

//RX arduino -> tx bluetooth
// TX arduino -> rx bluetooth
bool lecture = getChar(current_tours).toInt() ; //info  qui arrive du arduino
int tours_A_Faire = 3; // a fixer selon la longeur du cable

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->listWidget->hide();
    connect (agent, SIGNAL(deviceDiscovered(QBluetoothDeviceInfo)),this, SLOT(DeviceDiscovered(QBluetoothDeviceInfo)));
    agent->start();


    socket = new qBluetoothSocket(QBluethoothServiceInfo::RfcommProtocol);




//    serial = new QSerialPort();  //INICIALIZAMOS EL SERIAL
//    arduino_available = false;

//    foreach (const QSerialPortInfo &serial_Info, QSerialPortInfo::availablePorts()){ // lee informacion de cada puerto serial.
//        qDebug() << "Puerto : " << serial_info.PortName();
//        portName = serial_Info.portName();
//        qDebug() << "Vendor id :" << serial_Info.vendorIdentifier();
//        vendorId = serial_Info.vendorIdentifier();
//        qDebug() <<"Product Id:" << serial_Info.productIdentifier();
//        productId = serial_Info.productIdentifier();
//        arduino_available = true;
//}
//if ( arduino_available) arduino_init();
//}
//connect(serial, SIGNAL(readyRead(), this, SLOT(serial_read())));
//connect(ui->ChoixPoste,&QComboBox::currentTextChanged,this,&MainWindow::choisirType);


}

MainWindow::~MainWindow()
{
    delete ui;

}

//void arduino_init(){

//    serial->setPortName(portname);
//    serial->setBaudRate(QSerialPort::Baud9600);
//    serial->setDataBits(QSerialPort::Data8);
//    serial->setParity(QSerialPort::NoParity);
//    serial->setStopBits(QSerialPort::OneStop);
//    serial->setFlowControl(QSerialPort::NoFlowControl);
//    serial->open(QI0Device::ReadWrite);
//}

void MainWindow::AfficherTours(int nb_tours){

   ui->compteur->display(nb_tours);
}

//void MainWindow::serial_read(){

//    if(serial-> isWritable() && arduino_available) {
//        QByteArray current_tours = serial->readAll();
//        qDebug() <<" Vueltas leidas : "<< current_tours;
//    }
//}

void MainWindow::function(){

//    if(ui->ChoixPoste->currentText() =="1") current_tours = serial->readAll(); //  il recoit l'information donne par arduino PD: chaque pompe a un arduino

//    if(ui->ChoixPoste->currentText() =="2") current_tours = 2;

//    if(ui->ChoixPoste->currentText() =="3") current_tours = 3;

//    if(ui->ChoixPoste->currentText() =="4") current_tours = 4;

//    if(ui->ChoixPoste->currentText() =="5") current_tours = 5;

//    if(ui->ChoixPoste->currentText()=="6")  current_tours = 6;

    AfficherTours(tours_A_Faire);
    AfficherTours(current_tours);
   if ( tours_A_Faire == current_tours)  {
        ui->Led->setStyleSheet("background-color:green;");
        ui->label->setText("Rangement correct");

   }

   else {

        ui->Led->setStyleSheet("background-color:red;");
        ui->label->setText("Réessayer");
        current_tours = 0;
   }
}




void MainWindow::on_Connexion_clicked()
{
    ui->listWidget->show();
    ui->listWidget->clear();
    agent->stop();
    agent->start();

}

void MainWindow::DeviceDsicovered(const QBluetoothDeviceInfo &device)
{
    ui->listWidget->addItem(device.address().toString());
}


void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{
    string = item->text();
    item->setText(string);
    ui->listWidget->addItem(string);
    static const QString serviceUuid(QStringLiteral("00001101-0000-1000-8000-00805F9B34FB"));
    socket->connectToService(QBluetoothAddress(string),QBluetoothUuid(serviceUuid),QIODevice::ReadWrite);

}


void MainWindow::on_on_clicked()
{
    socket->write("h");
}


void MainWindow::on_off_clicked()
{
    socket->write("b");
}

