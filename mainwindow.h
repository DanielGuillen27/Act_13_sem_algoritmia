#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "grafo.hpp"
#include <QtCore>
#include <QtGui>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include<iostream>
#include <exception>
#include <string>
#include <QMainWindow>
#include <QFileDialog>
#include <QString>
#include <QMessageBox>
#include <fstream>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <iostream>


class Neurona {
private:
    int id;
    float voltaje, peso;
    int posicion_x, posicion_y;
    int red;
    int green, blue;
public:

    Neurona(): id(0), voltaje(0.0), posicion_x(0), posicion_y(0), red(0) ,green(0), blue(0), peso(0){};

    void print(){
        std::cout<<"informacion id: " << id <<"-"<< voltaje<<std::endl;

        std::cout<<"informacion voltaje: " << posicion_x<<"-"<< posicion_y << std::endl;

        std::cout<<"colores rojo, azul y verde: " <<"-"<<red <<"-"<< green; std::cout<<","<< blue << std::endl;
    }


    friend std::ostream& operator<<(std::ostream& , const Neurona& );

    friend QTextStream& operator <<(QTextStream&, const Neurona& );
    friend QTextStream& operator >> (QTextStream&, Neurona&);

    void setId(int id_1){
        id = id_1;
    }

    void setPosicionX(int x){
        posicion_x = x;
    }

    void setPosicionY(int y){
        posicion_y = y;
    }

    void setRed(int red_1){
        red = red_1;
    }

    void setBlue(int blue_1){
        blue = blue_1;
    }


    void setGreen(int green_1){
        green = green_1;
    }

    void setVoltaje(float voltaje_1){
        voltaje = voltaje_1;
    }
    void setPeso(float peso_1){
        peso = peso_1;
    }

    int getId() const{
        return id;

    }

    float getVoltaje(){
        return voltaje;
    }

    int getPosicionX(){
        return posicion_x;

    }

    int getPosicionY(){
        return posicion_y;

    }

    int getRed(){
        return red;
    }

    int getGreen(){
        return green;
    }

    int getBlue(){
        return blue;
    }
    float getPeso(){
        return peso;
    }

    static int compareByID(const Neurona& a, const Neurona& b ) {
        return a.id - b.id;
    }

    static int compareByVoltaje(const Neurona& a, const Neurona& b ) {
        return a.voltaje - b.voltaje;
    }

    friend QTextStream& operator>>(QTextStream& in, Neurona& neurona) {
        QString idStr, voltajeStr, posXStr, posYStr, blueStr, redStr, greenStr, pesoStr;

        in >> idStr >> voltajeStr >> posXStr >> posYStr >> blueStr >> redStr >> greenStr >> pesoStr;

        bool conversionExitosa;

        neurona.id = idStr.toInt(&conversionExitosa);
        neurona.voltaje = voltajeStr.toFloat(&conversionExitosa);
        neurona.posicion_x = posXStr.toInt(&conversionExitosa);
        neurona.posicion_y = posYStr.toInt(&conversionExitosa);
        neurona.blue = blueStr.toInt(&conversionExitosa);
        neurona.red = redStr.toInt(&conversionExitosa);
        neurona.green = greenStr.toInt(&conversionExitosa);
        neurona.peso = pesoStr.toFloat(&conversionExitosa);

        if (!conversionExitosa) {
            qDebug() << "Error de conversion";
        }

        return in;
    }

    friend QTextStream& operator<<(QTextStream& out, const Neurona& neurona) {
        out << neurona.id << " "
            << neurona.voltaje << " "
            << neurona.posicion_x << " "
            << neurona.posicion_y << " "
            << neurona.blue << " "
            << neurona.red << " "
            << neurona.green << " "
            << neurona.peso;

        return out;
    }
    /*
    friend std::ostream& operator<<(std::ostream& os, const Neurona& neurona) {
        os << neurona.toString();
        return os;
    }
*/

    //*****************SOBRE CARGA DE OPERADORES**********

    bool operator==(const Neurona& s) const {
        return id == s.id;
    }

    bool operator != (const Neurona& s) const {
        return !(*this == s);
    }

    bool operator < (const Neurona& s) const {
        return id < s.id;
    }

    bool operator <= (const Neurona& s) const {
        return *this < s or *this == s;
    }

    bool operator > (const Neurona& s) const {
        return !(*this <= s);
    }

    bool operator >= (const Neurona& s) const {

        return *this > s or *this == s;
    }
    QString toString(){
        QString resultado;

        resultado += std::to_string(id);
        resultado += " | ";
        resultado += std::to_string(voltaje);
        resultado += " | ";
        resultado += std::to_string(posicion_x);
        resultado += " | ";
        resultado += std::to_string(posicion_y);
        resultado += " | ";
        resultado += std::to_string(red);
        resultado += " | ";
        resultado += std::to_string(green);
        resultado += " | ";
        resultado += std::to_string(blue);
        resultado += " | ";
        resultado += std::to_string(peso);
        resultado += "\n";
        return resultado;

    }
    /*
    //*****************OPERADORES DE FLUJO **********
    std::ostream& operator<<(std::ostream& os, Neurona& p) { //Interactua con la pantalla

        os << p.id << std::endl;
        os << p.origen << std::endl;
        os << p.destino << std::endl;
        os << p.peso << std::endl;

        return os;
    }
    std::istream& operator >> (std::istream& is, Neurona& p) { //Interactua con el teclado
        std:: string aux,aux2;

        getline(is, aux);
        p.id =  atoi(aux.c_str());

        getline(is, p.blue);
        getline(is, p.destino);
        getline(is, aux2);
        p.peso = std::stof(aux2);

        return is;
    }
*/


};





template <class T>
class Administrar{

    class Node; // Forward Declaration

public:

    class Exception : public std::exception { // Clase anidada
    private:
        std::string msg;
    public:
        explicit Exception(const char* message) : msg(message) { }
        explicit Exception(const std::string& message): msg(message) { }
        virtual ~Exception() throw() { }
        virtual const char* what() const throw ( ) {
            return msg.c_str();
        }
    };

    typedef Node* position; //Elgancia en programacion en ves de recibir un Node* recibimos una posicion

private:
    class Node { // Clase anidada
    private:
        T data;
        position next;

    public:
        Node();
        Node(const T&);

        T getData();
        position getNext() const;

        void setData(const T&);
        void setNext(position);
        void swapData(T&,T&);

    };
    position anchor;
    int size;
    void copyAll(const Administrar<T>&);

    bool isValidPos(const position&) const;

public:

    Administrar();
    Administrar(const Administrar&);


    bool isEmpty() const;
    void insertData(const position&,const T&);
    int getSize();

    void deleteData(const position&);

    position findData(const T&) const;
    T retrieve(position) const;

    position getFirstPos() const;
    position getLastPos() const;
    position getPrevPost(position) const;
    position getNextPos(position) const;

    void sortBurbuja();
    void sortBurbuja(int(const T&, const T&));

    void deleteAll();

    QString toString() const;

    Administrar& operator = (const Administrar&);

    void escribir(QString);

    void leer(QString);

};

// inicio de node

template <class T>
Administrar<T>::Node::Node() : next(nullptr) {}

template <class T>
Administrar<T>::Node::Node (const T& e) : data(e), next(nullptr) {}

template <class T>
T Administrar<T>::Node::getData()  {
    return data;
}

template <class T>
typename Administrar<T>::position Administrar<T>::Node::getNext() const {
    return next;
}

template <class T>
void Administrar<T>::Node::setData(const T& e) {
    data = e;
}

template <class T>
void Administrar<T>::Node::setNext(position p) {
    next = p;
}

// final de node

using namespace std;

template <class T>

Administrar<T>::Administrar() : anchor(nullptr) , size(0){}

template <class T>
Administrar<T>::Administrar(const Administrar& l) {
    copyAll(l);
}


template <class T>
bool Administrar<T>::isValidPos(const position& p) const {
    position aux(anchor);

    while(aux != nullptr) { //mientras no llegue al final

        if(aux == p) { //revisa si es esa posicion
            return true;
        }
        aux = aux->getNext(); // se va recorriendo
    }
    return false; // si no la encuentra
}


template <class T>
bool Administrar<T>::isEmpty() const {
    return anchor == nullptr;
}

template <class T>
void Administrar<T>::insertData(const position& p, const T& e) { //dependiendo la posicion que damos es donde se inserta
    //es un metodo general para insertar, donde dependiendo la instruccion (posicion) se inserta ahi

    if(p != nullptr and !isValidPos(p)) {
        throw Exception("Posicion invalida, insertada");
    }

    position aux (new Node(e));

    if(aux == nullptr) {
        throw Exception("Memoria no disponible, insertData");
    }
    if(p == nullptr) { //insertar al principio

        aux->setNext(anchor);
        anchor = aux;
    }
    else { // insertamos en otro lugar
        aux->setNext(p->getNext());
        p->setNext(aux); // insercion despues del punto de interes
    }
}

template<class T>
int Administrar<T>::getSize(){
    position aux(anchor);
    size = 0;
    while(aux != nullptr) { //mientras no llegue al final
        size++;
        aux = aux->getNext(); // se va recorriendo
    }
    return size;
}
template <class T>
void Administrar<T>::deleteData(const position& p) {
    if(!isValidPos(p)) {
        throw Exception("Posicion invalida, deleteData");
    }

    if(p == anchor) { // primer elemento
        anchor = p->getNext();
    }
    else {
        getPrevPost(p)->setNext(p->getNext());
    }

    delete p;
}

template <class T>
typename Administrar<T>::position Administrar<T>::findData(const T& e) const {
    position aux(anchor);

    while( aux != nullptr and aux->getData() != e){
        aux = aux->getNext();
    }
    return aux;
}

template <class T>
T Administrar<T>::retrieve(position p) const {
    if(!isValidPos(p)){
        throw Exception("Posicion invalida, retrieve");
    }

    return p->getData();
}

template <class T>
typename Administrar<T>::position Administrar<T>::getLastPos() const {
    if(isEmpty()) {
        return nullptr;
    }
    position aux(anchor);

    while(aux->getNext() != nullptr) {
        aux = aux->getNext();
    }

    return aux;
}

template <class T>
typename Administrar<T>::position Administrar<T>::getFirstPos() const {
    return anchor;
}

template <class T>
typename Administrar<T>::position Administrar<T>::getNextPos( position p) const {
    if(!isValidPos(p)) {
        return nullptr;
    }
    return p->getNext();
}

template <class T>
typename Administrar<T>::position Administrar<T>::getPrevPost( position p) const {
    if(p == anchor) {
        return nullptr;
    }
    position aux(anchor);

    while(aux != nullptr and aux->getNext() != p) {
        aux = aux->getNext();
    }

    return aux;
}
template <class T>
QString Administrar<T>::toString() const {

    position aux(anchor);
    QString cadena;
    while(aux != nullptr) {
        cadena += aux->getData().toString();
        aux = aux->getNext();
    }
    return cadena;
}
template <class T>
void Administrar<T>::leer(QString fileName){
   QFile file(fileName);

    if(!file.open(QFile::ReadOnly | QFile::Text)){
      throw Exception("Posicion invalida, insertada");

   }

     QTextStream in(&file);

    deleteAll();

    T data;

    try {
        while(in.status() == QTextStream::Ok) {
            in >> data;
            insertData(anchor,data);

            }
        }
    catch(const Exception& ex) {

        file.close();

        throw Exception("Falló la inserción");
        }

    file.close();

}
template <class T>
void Administrar<T>::deleteAll() {
    position aux;
    size = 0;
    while(anchor != nullptr) {

        aux = anchor;
        anchor = anchor->getNext();
        delete aux;

    }
}
template <class T>
void Administrar<T>::escribir(QString fileName) {
    QFile file(fileName);
    QTextStream out(&file);
    position aux(anchor);

    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        throw Exception("No se pudo abrir el archivo para escritura");
    }

    while (aux != nullptr) {
        out << aux->getData();
        aux = aux->getNext();
    }

    file.close();
}

template <class T>
void Administrar<T>::sortBurbuja() {
        if (!anchor) {
            return;
        }

        bool cambio = true;
        while (cambio) {
            cambio = false;
            position actual = anchor;
            position prev = nullptr;  // Un puntero para rastrear el nodo anterior

            while (actual && actual->getNext()) {
            if (actual->getData() > actual->getNext()->getData()) {
                    // Intercambiar los valores de los nodos
                    position temp = actual->getNext();
                    actual->setNext(temp->getNext());
                    temp->setNext(actual);

                    // Manejo de los punteros prev y anchor si el nodo actual es el primero
                    if (prev) {
                        prev->setNext(temp);
                    } else {
                        anchor = temp;  // Actualiza el inicio de la lista si el primer nodo cambia
                    }

                    cambio = true;
                }
                prev = actual;
                actual = actual->getNext();
            }
        }
}


template <class T>
void Administrar<T>::sortBurbuja(int cmp(const T&, const T&)) {
        if (!anchor) {
            return;
        }

        bool cambio = true;
        while (cambio) {
            cambio = false;
            position actual = anchor;
            position prev = nullptr;  // Un puntero para rastrear el nodo anterior

            while (actual && actual->getNext()) {
                // > actual->getNext()->getData()
                if (cmp(actual->getData(), actual->getNext()->getData()) > 0) {
                    // Intercambiar los valores de los nodos
                    position temp = actual->getNext();
                    actual->setNext(temp->getNext());
                    temp->setNext(actual);

                    // Manejo de los punteros prev y anchor si el nodo actual es el primero
                    if (prev) {
                        prev->setNext(temp);
                    } else {
                        anchor = temp;  // Actualiza el inicio de la lista si el primer nodo cambia
                    }

                    cambio = true;
                }
                prev = actual;
                actual = actual->getNext();
            }
        }
}
/*----------------- FINAL DE LA CLASE ADMINISTRADORA ------------------*/


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void vaciar();

private slots:

    void on_txtId_textChanged(const QString &arg1);

    void on_btnGuardar_clicked();

    void on_btnMostrar_clicked();

    void on_lineEdit_textChanged(const QString &arg1);

    void on_txtRed_textChanged(const QString &arg1);

    void on_txtBlue_textChanged(const QString &arg1);

    void on_btnGuardarFinal_clicked();

    void on_actionOpen_triggered();

    void on_actionguardar_triggered();

    void on_pushButton_clicked();

    void on_btnLeer_clicked();

    void on_btnEscribir_clicked();

    void on_btnUbicacion_clicked();

    void on_txtUbicacion_textChanged(const QString &arg1);

    void on_buscarbtn_clicked();

    void on_txtBuscar_textChanged(const QString &arg1);

    void on_btnOrdenar_clicked();

    void on_btnVer_clicked();

    void on_btnLimpiar_clicked();

    void on_btnOrdenarVoltaje_clicked();

    void on_btnCoordenadas_clicked();

    void on_btnFuerza_clicked();

    void on_verGrafo_clicked();

    void on_limpiarGrafo_clicked();

    void on_VerLista_clicked();

    void on_generarGrafo_clicked();

    void on_btnBusqueda_clicked();

    void on_txtBusqueda_textChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    Neurona n;
    Neurona n1;

    Administrar<Neurona> lista;
    Administrar<Administrar<Neurona>> listaAdyacencia; //aqui creamos la lista de lsitas
    Grafo<Neurona> grafo;

    Administrar<Neurona>::position nuevo;
    Administrar<Neurona>::position siguiente;

    QString id;
    QString voltaje;
    QString posX;
    QString posY;
    QString red;
    QString green;
    QString blue;
    QString cadena;

    QGraphicsScene *scene;
    QGraphicsScene *sceneGrafo;
    QGraphicsTextItem *text;
    QGraphicsEllipseItem *ellipse;


    enum columnas{
        ID, VOLTAJE,POSX, POSY, RED, BLUE, GREEN
    };
};
#endif // MAINWINDOW_H
