#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>
#include <QTableWidget>
#include <cmath>

bool ok;
QString fileName;
QBrush redBrush(Qt::red);
QBrush blueBrush(Qt::blue);
QPen blackPen(Qt::black);



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QString fileName;
    scene = new QGraphicsScene(this);
    sceneGrafo = new QGraphicsScene(this);
    text = new QGraphicsTextItem();
    ui->graphicsView->setScene(scene);
    ui->viewGrafo->setScene(sceneGrafo);

}

MainWindow::~MainWindow()
{
    delete ui;


}

void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Seleccione un archivo"), "C:\\Users\\Daniel\\Downloads", tr("Text File (*.txt)"));

    QMessageBox T;

    T.setText(fileName);

    T.exec();

}
void MainWindow::on_txtId_textChanged(const QString &arg1)
{

}
void MainWindow::vaciar(){
    ui->txtId->setText("");
    ui->txtVoltaje->setText("");
    ui->txtPosX->setText("");
    ui->txtPosY->setText("");
    ui->txtRed->setText("");
    ui->txtGreen->setText("");
    ui->txtBlue->setText("");
}

void MainWindow::on_btnGuardar_clicked()
{

    //primero obtenemos los datos de cada caja de texto
    id=ui->txtId->text();
    voltaje=ui->txtVoltaje->text();
    posX = ui->txtPosX->text();
    posY =ui->txtPosY->text();
    red = ui->txtRed->text();
    green = ui->txtGreen->text();
    blue = ui->txtBlue->text();
    //en el objeto que tenemos lo agregamos los datos a cada atributo del objeto
    n.setId(id.toInt(&ok));
    n.setVoltaje(voltaje.toFloat(&ok));
    n.setPosicionX(posX.toInt(&ok));
    n.setPosicionY(posY.toInt(&ok));
    n.setBlue(blue.toInt(&ok));
    n.setGreen(green.toInt(&ok));
    n.setRed(red.toInt(&ok));

    //creamos una neurona y agregamos datos, despues lo metemos en la lista

    lista.insertData(lista.getFirstPos(),n); // se inserta al principio

    vaciar();
}

void MainWindow::on_btnMostrar_clicked()
{
    ui->tableWidget->clear();
    int fila;
    ui->tableWidget->setColumnCount(7);

    QStringList encabezado;



    encabezado << "ID" << "voltaje" << "Pos X" << "Pos y" << "Red"<< "Blue" << "Green";
    ui->tableWidget->setHorizontalHeaderLabels(encabezado);

    //ui->tableWidget->setItem(0,0,MyItem);



    //metodo de busqueda lineal
    //aqui podemos hacer que recorra y si es nullptr entonces asi sabemos que es el ultimo y nos salimos
 nuevo = lista.getFirstPos();

    ui->tableWidget->setRowCount(0);
    while(nuevo != nullptr){

        n = lista.retrieve(nuevo);
        nuevo = lista.getNextPos(nuevo);
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());
          fila = ui->tableWidget->rowCount() - 1;
        ui->tableWidget->setItem(fila, ID, new QTableWidgetItem(QString::number(n.getId())));
        ui->tableWidget->setItem(fila, VOLTAJE, new QTableWidgetItem(QString::number(n.getVoltaje())));
        ui->tableWidget->setItem(fila, POSX, new QTableWidgetItem(QString::number(n.getPosicionX())));
        ui->tableWidget->setItem(fila, POSY, new QTableWidgetItem(QString::number(n.getPosicionY())));
        ui->tableWidget->setItem(fila, RED, new QTableWidgetItem(QString::number(n.getRed())));
        ui->tableWidget->setItem(fila, BLUE, new QTableWidgetItem(QString::number(n.getBlue())));
        ui->tableWidget->setItem(fila, GREEN, new QTableWidgetItem(QString::number(n.getGreen())));
    }
}


void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{

}


void MainWindow::on_txtRed_textChanged(const QString &arg1)
{

}


void MainWindow::on_txtBlue_textChanged(const QString &arg1)
{

}


void MainWindow::on_btnGuardarFinal_clicked()
{
    //primero obtenemos los datos de cada caja de texto
    id=ui->txtId->text();
    voltaje=ui->txtVoltaje->text();
    posX = ui->txtPosX->text();
    posY =ui->txtPosY->text();
    red = ui->txtRed->text();
    green = ui->txtGreen->text();
    blue = ui->txtBlue->text();
    //en el objeto que tenemos lo agregamos los datos a cada atributo del objeto
    n.setId(id.toInt(&ok));
    n.setVoltaje(voltaje.toFloat(&ok));
    n.setPosicionX(posX.toInt(&ok));
    n.setPosicionY(posY.toInt(&ok));
    n.setBlue(blue.toInt(&ok));
    n.setGreen(green.toInt(&ok));
    n.setRed(red.toInt(&ok));
    //creamos una neurona y agregamos datos, despues lo metemos en la lista

    lista.insertData(lista.getLastPos(),n); // se inserta al final
    vaciar();
}

void MainWindow::on_actionguardar_triggered()
{
    //aqui vamos a guardar en el archivo
}


void MainWindow::on_pushButton_clicked()
{
     fileName = QFileDialog::getOpenFileName(this,tr("Seleccione un archivo"), "C:\\Users\\usuario\\Downloads", tr("Text File (*.txt)"));

    QMessageBox T;

    T.setText(fileName);



    T.exec();
}


void MainWindow::on_btnLeer_clicked()
{
     lista.leer(fileName);
}


void MainWindow::on_btnEscribir_clicked()
{
    lista.escribir(fileName);
}


void MainWindow::on_btnUbicacion_clicked()
{

    fileName = QFileDialog::getOpenFileName(this,
                                            tr("Seleccione un archivo"), "C:\\Users\\usuario\\Downloads", tr("Text File (*.txt)"));

    QMessageBox T;

    T.setText(fileName);

    T.exec();

}


void MainWindow::on_txtUbicacion_textChanged(const QString &arg1)
{



}


void MainWindow::on_buscarbtn_clicked()
{
    int fila;
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->insertRow(ui->tableWidget->rowCount());

    Neurona otraNeurona;
    try{

    otraNeurona.setId(ui->lineEdit->text().toInt(&ok));
    nuevo = lista.findData(otraNeurona);

    n1 = lista.retrieve(nuevo);
    }catch(exception ex){
    QMessageBox::information(this,"Alerta", "Ingrese un valor exitente");

    }
 fila = ui->tableWidget->rowCount() - 1;
    ui->tableWidget->setItem(fila, ID, new QTableWidgetItem(QString::number(n1.getId())));
    ui->tableWidget->setItem(fila, VOLTAJE, new QTableWidgetItem(QString::number(n1.getVoltaje())));
    ui->tableWidget->setItem(fila, POSX, new QTableWidgetItem(QString::number(n1.getPosicionX())));
    ui->tableWidget->setItem(fila, POSY, new QTableWidgetItem(QString::number(n1.getPosicionY())));
    ui->tableWidget->setItem(fila, RED, new QTableWidgetItem(QString::number(n1.getRed())));
    ui->tableWidget->setItem(fila, BLUE, new QTableWidgetItem(QString::number(n1.getBlue())));
    ui->tableWidget->setItem(fila, GREEN, new QTableWidgetItem(QString::number(n1.getGreen())));

}


void MainWindow::on_txtBuscar_textChanged(const QString &arg1)
{

}


void MainWindow::on_btnOrdenar_clicked()
{
    lista.sortBurbuja(Neurona::compareByID);
}


void MainWindow::on_btnVer_clicked()
{
    blackPen.setWidth(3);
    int x = 10;
    nuevo = lista.getFirstPos();

    QColor color;

    while(nuevo != nullptr){

    n = lista.retrieve(nuevo);
    nuevo = lista.getNextPos(nuevo);
    color.setGreen(n.getGreen());
    color.setBlue(n.getBlue());
    color.setRed(n.getRed());

    QGraphicsEllipseItem *ellipse = scene->addEllipse(n.getPosicionX(), n.getPosicionY(), n.getVoltaje(), n.getVoltaje(), blackPen, color);

    scene->addItem(ellipse);

    }


}


void MainWindow::on_btnLimpiar_clicked()
{
    scene->clear();
}


void MainWindow::on_btnOrdenarVoltaje_clicked()
{
    lista.sortBurbuja(Neurona::compareByVoltaje);
}


void MainWindow::on_btnCoordenadas_clicked()
{
    scene->clear();
    blackPen.setWidth(0);
    int x = 10;
    nuevo = lista.getFirstPos();

    QColor color;

    while(nuevo != nullptr){

    n = lista.retrieve(nuevo);
    nuevo = lista.getNextPos(nuevo);
    color.setBlue(255);
    color.setRed(0);
    color.setGreen(0);

    QGraphicsEllipseItem *ellipse = scene->addEllipse(n.getPosicionX(), n.getPosicionY(), 15, 15, blackPen, color);

    scene->addItem(ellipse);

    }
}


void MainWindow::on_btnFuerza_clicked()
{
    /*LA IDEA ES QUE TENGAMOS 2 OBJETOS UNO NO SE MUEVE Y EL OTRO SI SE MUEVE EN CADA CICLO
    POR EJEMPLO EL PRIMER ELEMENTO SE COMPARA CON  LOS ANTERIORES Y ASÍ PODEMOS CHECAR EL MENOR, DESPUES DE LLEGAR AL FINAL
    DE LA LISTA PODREMOS CAMBIAR LE PRIMER OBJETO Y ASÍ HASTA LLEGAR AL FINAL. DURANTE ESO CALCULAMOS LA DISTANCIA DE CADA UNO CON EL PRIMER OBJETO
    Y YA
    n seria el elemento que va a revisar a todos los demás.
    luego cuando pase el ciclo n = lista.getNextPos(n).
    */
    QGraphicsLineItem *previousLine;
    previousLine = nullptr;

    int tamanio = lista.getSize();
    double dist1=0.0, distancia=0.0;
    nuevo = lista.getFirstPos();
    siguiente = lista.getFirstPos();


    while(nuevo != nullptr){
    n = lista.retrieve(nuevo);
    if(siguiente == nullptr){ // aqui checamos si se comparo con todos los elemento el
        nuevo = lista.getNextPos(nuevo);
        siguiente = lista.getFirstPos();
        dist1=0.0, distancia=100.0;
    }else{

        int distanciax = n.getPosicionX() - n1.getPosicionX();
        int distanciay = n.getPosicionY() - n1.getPosicionY();
        dist1 = sqrt(distanciax * distanciax + distanciay * distanciay);


        if (dist1 < distancia) {
            distancia = dist1;

            QGraphicsLineItem *line = new QGraphicsLineItem(n.getPosicionX(), n.getPosicionY(), n1.getPosicionX(), n1.getPosicionY());
            line->setPen(QPen(Qt::black, 2));
            scene->addItem(line);


        }
    }
    n1 = lista.retrieve(siguiente);

    siguiente = lista.getNextPos(siguiente);

    }
}

void MainWindow::on_verGrafo_clicked()
{



    //aqui volvemos a checar el algoritmo de fuerza bruta, y de ahí metemos los datos al grafo
    QGraphicsLineItem *previousLine;
    QColor color;
    previousLine = nullptr;

    int tamanio = lista.getSize();
    double dist1=0.0, distancia=0.0;
    nuevo = lista.getFirstPos();
    siguiente = lista.getFirstPos();

    while(nuevo != nullptr){
    n = lista.retrieve(nuevo);



    if(siguiente == nullptr){ // aqui checamos si se comparo con todos los elemento el
        nuevo = lista.getNextPos(nuevo);
        siguiente = lista.getFirstPos();
        dist1=0.0, distancia=10000.0; // damos el primero paso, sino todos serian mayor si lo inciamos en 0
        color.setBlue(n.getBlue());
        color.setRed(n.getRed());
        color.setGreen(n.getGreen());

        QGraphicsEllipseItem *ellipse = sceneGrafo->addEllipse(n.getPosicionX(), n.getPosicionY(), n.getVoltaje(), n.getVoltaje(), blackPen, color);
        sceneGrafo->addItem(ellipse);
    }else{
        int distanciax = n.getPosicionX() - n1.getPosicionX();
        int distanciay = n.getPosicionY() - n1.getPosicionY();
        dist1 = sqrt(distanciax * distanciax + distanciay * distanciay);
        if (dist1 <= distancia) {
            distancia = dist1;
        }


        QGraphicsTextItem *textItem = new QGraphicsTextItem(QString::number(distancia));

        // Establece la posición del elemento de texto
        textItem->setPos(n.getPosicionX(), n1.getPosicionY()); // Cambia las coordenadas según sea necesario


        // Agrega el elemento de texto a la escena
        sceneGrafo->addItem(textItem);
        QGraphicsLineItem *line = new QGraphicsLineItem(n.getPosicionX(), n.getPosicionY(), n1.getPosicionX(), n1.getPosicionY());
        line->setPen(QPen(Qt::black, 2));
        sceneGrafo->addItem(line);

    }
    n1 = lista.retrieve(siguiente);
    siguiente = lista.getNextPos(siguiente);

    }
}


void MainWindow::on_limpiarGrafo_clicked()
{
            sceneGrafo->clear();
}


void MainWindow::on_VerLista_clicked()
{

    ui->txtListaAdyacencia->appendPlainText( lista.toString());
}


void MainWindow::on_generarGrafo_clicked()
{
    //aqui volvemos a checar el algoritmo de fuerza bruta, y de ahí metemos los datos al grafo
    QGraphicsLineItem *previousLine;
    previousLine = nullptr;

    int tamanio = lista.getSize();
    double dist1=0.0, distancia=0.0;
    nuevo = lista.getFirstPos();
    siguiente = lista.getFirstPos();

    while(nuevo != nullptr){
    n = lista.retrieve(nuevo);
    grafo.addVertex(n);


    if(siguiente == nullptr){ // aqui checamos si se comparo con todos los elemento el
        nuevo = lista.getNextPos(nuevo);
        siguiente = lista.getFirstPos();
        dist1=0.0, distancia=10000.0; // damos el primero paso, sino todos serian mayor si lo inciamos en 0
    }else{
        int distanciax = n.getPosicionX() - n1.getPosicionX();
        int distanciay = n.getPosicionY() - n1.getPosicionY();
        dist1 = sqrt(distanciax * distanciax + distanciay * distanciay);

        if (dist1 < distancia) {
            distancia = dist1;
            //en ves de dibujar lo metemos al grafo
            grafo.addEdge(n, n1); // nodo 1, nodo 2
        }
    }
    n1 = lista.retrieve(siguiente);
    siguiente = lista.getNextPos(siguiente);

    }
}


void MainWindow::on_btnBusqueda_clicked()
{
    int valor = ui->txtBusqueda->text().toInt();

    // Buscar el nodo en el grafo con el valor dado


    // Verificar si el nodo fue encontrado antes de llamar a depthFirstSearch
    grafo.depthFirstSearch();
    const std::vector<Neurona>& nodosVisitados = grafo.getNodosVisitados();
    int i =0;
    while (i < nodosVisitados.size()) {
     int id = nodosVisitados[i].getId();
     ui->txtListaAdyacencia->appendPlainText("Visitando nodo: " + QString::number(id));
    i++;
    }

}



void MainWindow::on_txtBusqueda_textChanged(const QString &arg1)
{

}

