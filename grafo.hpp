#ifndef GRAFO_HPP_INCLUDED
#define GRAFO_HPP_INCLUDED

#include <map>
#include <vector>
#include <string>
#include <utility>
#include <queue>
#include <set>
#include <limits>
#include <algorithm>
#include <iostream>
#include <QDebug>


template<class T>
class Grafo
{
private:

    class Edge;
    std::vector<T> nodosVisitados;
    class Node{

    private:

        bool visited;
        int inDegree;
        int degree;
        T* dataPtr;
        Node* next;
        Node* prev;
        std::map<int, Edge*> adjacents;
        typename std::map<int, Edge*>::const_iterator adjsIt;



    public:

        bool doIHave(Edge*) const;


        class Exception : public std::exception{

        private:
            std::string msg;

        public:

            explicit Exception(const char* message) : msg(message) {}

            explicit Exception(const std::string& message) : msg(message) {}

            virtual ~Exception() throw () {}

            virtual const char* what() const throw() {

                return msg.c_str();
            }

        };

        Node();
        Node(const T&);
        ~Node();

        void setDataPtr(T*);
        void setData(const T&);
        void setNext(Node*);
        void setPrev(Node*);
        void setAdjacency(Edge*);
        void setDegree(const int&);
        void setDegree();
        void setVisited(const bool&);
        void setInDegree(const int&);
        void setInDegree();

        bool isVisited() const;
        int getDegree() const;
        int getInDegree() const;
        T getData() const;
        T* getDataPtr() const;
        Node* getNext() const;
        Node* getPrev() const;

        std::map<int, Edge*> getAdjacency() const;
        void setAdjacency(const std::map<int, Edge*>&);


    };
    class Edge{

    private:

        double weight;
        bool directed;
        Node* fromNode;
        Node* toNode;
        Edge* next;

    public:

        Edge();
        Edge(Node*, Node*);
        Edge(Node*, Node*, const bool&, const double&);

        ~Edge();

        void setWeight(const double&);
        void setDirected(const bool&);
        void setFrom(Node*);
        void setTo(Node*);
        void setNext(Edge*);

        bool isDirected() const;
        double getWeight() const;
        Node* getFrom() const;
        Node* getTo() const;
        Edge* getNext() const;

    };

    Node* headerNode;
    Edge* anchorEdge;


    bool isValidVertex(Node*) const;
    bool isValidEdge(Edge*) const;

    void DFS(Node*);
    void BFS(Node*);
    void resetNodes();


public:

    class Exception : public std::exception{

    private:
        std::string msg;

    public:

        explicit Exception(const char* message) : msg(message) {}

        explicit Exception(const std::string& message) : msg(message) {}

        virtual ~Exception() throw () {}

        virtual const char* what() const throw() {

            return msg.c_str();

        }

    };

    typedef Node* NODE;
    typedef Edge* EDGE;
    typedef std::map<int, Edge*> ADJACENTS;
    typedef std::pair<NODE, NODE> PAIR;
    typedef typename std::map<int, Edge*>::const_iterator ITERATOR;

    Grafo();
    ~Grafo();

private:


    bool isEmptyNode() const;
    void addVertex(const NODE&, const T&);
    void deletVertex(const NODE&);
    NODE getFirstVertex() const;
    NODE getLastVertex() const;
    NODE getPrevPos(const NODE&) const;
    NODE getNextPos(const NODE&) const;

    bool isEmptyEdge() const;
    void addEdge(const EDGE&, const NODE&, const NODE&);
    void deletEdge(const EDGE&);

    void deletAllEdges();

    EDGE getFirstEdge() const;
    EDGE getLastEdge() const;
    EDGE getPrevPos(const EDGE&) const;
    EDGE getNextPos(const EDGE&) const;

    ADJACENTS getAdjacencyOf(const NODE&) const;

public:


    void addVertex(const T&);

    void deletVertex(const T&);

    void deletAllVertex();
    NODE findVertex(const T&) const;
    NODE findVertex(const T&, int(const T&, const T&)) const;

    T retrieve(const NODE&) const;

    std::string toStringNodes() const;

const std::vector<T>& getNodosVisitados() const;

    void addEdge(const T&, const T&);
    void addEdge(const T&, const T&, const bool&);
    void addEdge(const T&, const T&, const bool&, const double&);
    void deletEdge(const T&, const T&);

    EDGE findEdge(const T&, const T&) const;
    EDGE findEdge(const T&, const T&, int (const T&, const T&)) const;
    std::pair<NODE, NODE> retrieve(const EDGE&) const;
    std::string toStringEdges() const;

    bool isAdjacent(const NODE&, const NODE&) const;
    ADJACENTS getAdjacencyOf(const T&) const;
    bool doIHaveEdge(const EDGE&) const;

   void depthFirstSearch(NODE startNode = nullptr);
    void breadthFirstSearch(const NODE&);


    std::string buildAdjacencyMatrix() const;

};


#endif // GRAFO_HPP_INCLUDED



template <class T>
bool Grafo<T>::Node::doIHave(Edge* e) const
{
    typename std::map<int, Edge*>::const_iterator it;

    it = adjacents.cbegin();

    for(; it != adjacents.end(); ++it)
    {

        Edge* temp = it ->second;

        if(e ->getFrom() ->getData() == temp ->getFrom() ->getData() and e ->getTo() ->getData() == temp ->getTo() ->getData())
        {
            return true;
        }

    }

    return false;
}


template <class T>
Grafo<T>::Node::Node() : next(nullptr), prev(nullptr), dataPtr(nullptr), visited(false), degree(0), inDegree(0), adjacents() {}
template <class T>
Grafo<T>::Node::Node(const T &e) : dataPtr(new T(e)), next(nullptr), prev(nullptr), visited(false), degree(0), inDegree(0), adjacents(){
    if (dataPtr == nullptr)
    {
        throw Exception("Memoria no Disponible, Creando Nodo");
    }

}
template <class T>
Grafo<T>::Node:: ~Node() { delete dataPtr; adjacents.clear(); }
template <class T>
void Grafo<T>::Node::setNext(Node* n){
    next = n;
}
template <class T>
void Grafo<T>::Node::setPrev(Node* p){
    prev = p;
}
template <class T>
void Grafo<T>::Node::setDataPtr(T* ptr){

    dataPtr = ptr;

}
template <class T>
void Grafo<T>::Node::setData(const T& e){

    if(dataPtr == nullptr){

        dataPtr = new T(e);

        if(dataPtr == nullptr){

            throw Exception("Memoria no disponible, Node::setData");

        }else{

            *dataPtr = e;

        }

    }

}
template <class T>
void Grafo<T>::Node::setDegree(const int& d){

    degree = d;

}
template <class T>
void Grafo<T>::Node::setDegree(){

    degree++;

}
template <class T>
void Grafo<T>::Node::setVisited(const bool& b){

    visited = b;
}
template <class T>
void Grafo<T>::Node::setInDegree(const int &i)
{
    inDegree = i;
}
template <class T>
void Grafo<T>::Node::setInDegree()
{
    inDegree++;
}
template <class T>
void Grafo<T>::Node::setAdjacency(Edge* e)
{

    if(doIHave(e)) return;

    if(e -> isDirected()){

        adjacents[++degree] = e;

        e ->getTo() ->setInDegree();

    }else{

        Edge* temp(new Edge(e->getTo(), e ->getFrom()));

        adjacents[++degree] = e;

        e ->getTo() ->setInDegree();

        if(!(e ->getTo() ->doIHave(temp)))
        {
            e ->getTo() ->setAdjacency(temp);
        }

        temp ->setNext(e ->getNext());

        e -> setNext(temp);

    }
}



template <class T>
bool Grafo<T>::Node::isVisited() const{

    return visited;

}
template <class T>
int Grafo<T>::Node::getDegree() const{

    return degree;

}
template <class T>
int Grafo<T>::Node::getInDegree() const
{
    return inDegree;
}
template <class T>
T *Grafo<T>::Node::getDataPtr() const
{
    return dataPtr;
}
template<class T>
T Grafo<T>::Node::getData() const{

    if(dataPtr == nullptr)    {

        throw Exception("Dato inexistente, Node::getData");
    }

    return *dataPtr;

}
template<class T>
typename Grafo<T>::Node* Grafo<T>::Node::getNext() const{

    return next;

}
template<class T>
typename Grafo<T>::Node* Grafo<T>::Node::getPrev() const{

    return prev;

}
template <class T>
std::map<int, typename Grafo<T>::Edge*> Grafo<T>::Node::getAdjacency() const
{
    return adjacents;
}
template <class T>
void Grafo<T>::Node::setAdjacency(const std::map<int, Edge *>& a)
{
    adjacents = a;
}

template <class T>
Grafo<T>::Edge::Edge() : weight(0.0), directed(true), fromNode(nullptr), toNode(nullptr), next(nullptr) {}
template <class T>
Grafo<T>::Edge::Edge(Node* a, Node* b) : weight(0.0), directed(true), fromNode(a), toNode(b), next(nullptr) {}
template <class T>
Grafo<T>::Edge::Edge(Node*a, Node* b, const bool& c, const double& w) : weight(w), directed(c), fromNode(a), toNode(b), next(nullptr) {}
template <class T>
Grafo<T>::Edge::~Edge() {}
template <class T>
void Grafo<T>::Edge::setWeight(const double & w)
{
    weight = w;
}
template <class T>
void Grafo<T>::Edge::setDirected(const bool& b)
{
    directed = b;
}
template <class T>
void Grafo<T>::Edge::setFrom(Node* n)
{
    fromNode = n;
}
template <class T>
void Grafo<T>::Edge::setTo(Node* n)
{
    toNode = n;
}
template <class T>
void Grafo<T>::Edge::setNext(Edge* n)
{
    next = n;
}

template <class T>
bool Grafo<T>::Edge::isDirected() const
{
    return directed;
}
template <class T>
double Grafo<T>::Edge::getWeight() const
{
    return weight;
}
template <class T>
typename Grafo<T>::Node *Grafo<T>::Edge::getFrom() const
{
    return fromNode;
}
template <class T>
typename Grafo<T>::Node *Grafo<T>::Edge::getTo() const
{
    return toNode;
}
template <class T>
typename Grafo<T>::Edge *Grafo<T>::Edge::getNext() const{
    return next;
}



template <class T>
Grafo<T>::Grafo() : headerNode(new Node), anchorEdge(nullptr)
{

    if(headerNode == nullptr)
    {
        throw Exception("Memoria no Disponible, Inicializandi la Lista");
    }

    headerNode -> setNext(headerNode);
    headerNode -> setPrev(headerNode);
}
template <class T>
Grafo<T>::~Grafo() { deletAllVertex(); deletAllEdges(); }

template <class T>
bool Grafo<T>::isValidVertex(Node* n) const
{
    NODE aux(headerNode ->getNext());

    while ( aux != headerNode ) {
        if(aux == n){

            return true;
        }

        aux = aux ->getNext();
    }

    return false;
}
template <class T>
bool Grafo<T>::isEmptyNode() const
{
    return headerNode ->getNext() == headerNode;
}
template <class T>
void Grafo<T>::addVertex(const NODE& p, const T &e){

    NODE copyNode(p);

    if(p != nullptr and !isValidVertex(p))
    {
        throw Exception("Posicion invalida, Lista::insertData");
    }

    NODE aux;

    try{
        aux = new Node(e);
    }
    catch(typename Node::Exception ex){

        throw Exception(ex.what());

    }
    if(aux == nullptr ) {

        throw Exception("Memoria no disponible, Lista::insertData");

    }

    if(copyNode == nullptr)
    {
        copyNode = headerNode;
    }

    aux ->setPrev(copyNode);
    aux ->setNext(copyNode ->getNext());

    copyNode ->getNext() ->setPrev(aux);
    copyNode ->setNext(aux);



}
template <class T>
void Grafo<T>::deletVertex(const NODE &p){

    if( !isValidVertex(p) ){

        throw Exception("Posicion Invalida, Grafo::deleteData");

    }

    EDGE aux(anchorEdge);
    EDGE temp;

    while (aux != nullptr) {

        temp = aux;

        if (temp->getTo() == p || temp->getFrom() == p) {

            aux = aux->getNext();

            deletEdge(temp);

        } else {

            aux = aux->getNext();

        }
    }

    p ->getPrev() ->setNext(p ->getNext());
    p ->getNext() ->setPrev(p ->getPrev());


    delete p;

}
template <class T>
void Grafo<T>::deletAllVertex()
{

    NODE aux;

    while( headerNode ->getNext() != headerNode)
    {
        aux = headerNode ->getNext();

        headerNode ->setNext(aux ->getNext());

        delete aux;

    }

    headerNode ->setPrev(headerNode);
}
template <class T>
typename Grafo<T>::NODE Grafo<T>::getFirstVertex() const
{
    if(isEmptyNode()){
        return nullptr;
    }

    return headerNode ->getNext();
}
template <class T>
typename Grafo<T>::NODE Grafo<T>::getLastVertex() const
{
    if(isEmptyNode()){
        return nullptr;
    }

    return headerNode ->getPrev();
}
template <class T>
typename Grafo<T>::NODE Grafo<T>::getPrevPos(const NODE& p) const
{
    if(!isValidVertex())
    {
        return nullptr;
    }

    return p != headerNode ->getNext() ? p ->getPrev() : headerNode ->getPrev();
}
template <class T>
typename Grafo<T>::NODE Grafo<T>::getNextPos(const NODE& p) const
{
    if(!isValidVertex(p))
    {
        return nullptr;
    }

    return p != headerNode ->getPrev() ? p ->getNext() : headerNode ->getNext();
}
template <class T>
typename Grafo<T>::NODE Grafo<T>::findVertex(const T& e) const
{
    NODE aux(headerNode ->getNext());

    while (aux != headerNode)
    {
        if(aux ->getData() == e)
        {
            return aux;
        }

        aux = aux ->getNext();
    }

    return nullptr;
}
template <class T>
typename Grafo<T>::NODE Grafo<T>::findVertex(const T &e, int argm(const T &, const T &)) const
{
    NODE aux(headerNode ->getNext());

    while (aux != headerNode)
    {
        if(0 == argm(aux ->getData(), e))
        {
            return aux;
        }

        aux = aux ->getNext();
    }

    return nullptr;
}
template <class T>
T Grafo<T>::retrieve(const NODE& p) const
{
    if(!isValidVertex(p)){

        throw Exception("Posicion invalida,  headerNode::retrieve");

    }

    return p ->getData();

}
template <class T>
typename Grafo<T>::ADJACENTS Grafo<T>::getAdjacencyOf(const NODE& p) const
{
    if(!isValidVertex(p) and p ->getDegree() == 0)
    {
        throw Exception("Posicion invalida, Grafo::getAdjacencysOf");
    }

    return p ->getAdjacency();
}
template <class T>

std::string Grafo<T>::toStringNodes() const
{
    NODE aux(headerNode ->getNext());
    std::string myStr;

    while(aux != headerNode){

        myStr += aux ->getData() + ", ";

        aux = aux ->getNext();
    }

    return myStr;
}

template <class T>
bool Grafo<T>::isValidEdge(Edge* p) const
{
    EDGE aux(anchorEdge);

    while(aux != nullptr)
    {
        if( aux == p)
        {
            return true;
        }

        aux = aux ->getNext();
    }

    return false;
}
template <class T>
bool Grafo<T>::isEmptyEdge() const
{
    return anchorEdge == nullptr;
}
template <class T>
void Grafo<T>::addEdge(const EDGE& p, const NODE& a, const NODE& b)
{
    if(p != nullptr and !isValidEdge(p)){
        throw Exception("Posicion invalida, Grafo::addEdge");
    }

    Edge* temp(new Edge(a, b));

    if(temp == nullptr)
    {
        throw Exception("Memoria no valida, Grafo::addEdge");
    }

    if(doIHaveEdge(temp)){ return;}

    if(p == nullptr)
    {
        temp ->setNext(anchorEdge);

        anchorEdge = temp;

        anchorEdge ->getFrom() ->setAdjacency(temp);

    }else{

        temp ->setNext(p ->getNext());

        p ->setNext(temp);

        temp ->getFrom() ->setAdjacency(temp);

    }
}
template <class T>
void Grafo<T>::deletEdge(const EDGE& p)
{
    if(!isValidEdge(p))
    {
        throw Exception("Posicion invalida, Grafo::deletEdge");
    }

    if(anchorEdge == p)
    {

        anchorEdge = anchorEdge ->getNext();

    }else{

        getPrevPos(p) ->setNext(p ->getNext());

    }

    ADJACENTS adjs = p ->getFrom() ->getAdjacency();
    ITERATOR it = adjs.begin();


    for(; it != adjs.end(); ++it){

        if(it ->second == p)
        {
            adjs.erase(it ->first);
            break;
        }

    }

    p ->getFrom() ->setAdjacency(adjs);

    delete p;
}
template <class T>
void Grafo<T>::deletAllEdges()
{
    EDGE temp;

    while(anchorEdge != nullptr)
    {
        temp = anchorEdge;

        anchorEdge  = anchorEdge ->getNext();

        delete temp;
    }
}
template <class T>
typename Grafo<T>::EDGE Grafo<T>::getFirstEdge() const
{
    return anchorEdge;
}
template <class T>
typename Grafo<T>::EDGE Grafo<T>::getLastEdge() const
{
    if(isEmptyEdge()){

        return nullptr;
    }

    EDGE aux(anchorEdge);

    while(aux ->getNext() != nullptr)
    {
        aux = aux ->getNext();
    }

    return aux;
}
template <class T>
typename Grafo<T>::EDGE Grafo<T>::getPrevPos(const EDGE& p) const
{
    if(p == anchorEdge){
        return nullptr;
    }

    EDGE aux(anchorEdge);

    while(aux != nullptr and aux ->getNext() != p)
    {
        aux = aux ->getNext();
    }

    return aux;
}
template <class T>
typename Grafo<T>::EDGE Grafo<T>::getNextPos(const EDGE& p) const
{
    if(!isValidEdge(p))
    {
        return nullptr;
    }

    return p ->getNext();
}
template <class T>
typename Grafo<T>::EDGE Grafo<T>::findEdge(const T& a, const T& b) const
{
    EDGE aux(anchorEdge);

    while(aux != nullptr )
    {
        if (((aux ->getFrom()->getData()) == a) and ((aux ->getTo() ->getData()) == b))
        {
            return aux;
        }

        aux = aux ->getNext();
    }

    return aux;
}
template <class T>
std::pair<typename Grafo<T>::NODE, typename Grafo<T>::NODE> Grafo<T>::retrieve(const EDGE& p) const
{
    if(!isValidEdge(p))
    {
        throw Exception("Posicion invalida, Grafo::Edge::retrieve");
    }

    return std::make_pair(p-> getFrom(), p-> getTo());
}
template <class T>
bool Grafo<T>::doIHaveEdge(const EDGE& e) const
{
    EDGE temp(anchorEdge);

    while (temp != nullptr)
    {
        if(e ->getFrom() ->getData() == temp ->getFrom() ->getData() and e ->getTo() ->getData() == temp ->getTo() ->getData())
        {
            return true;
        }

        temp = temp ->getNext();
    }

    return false;
}
template <class T>
std::string Grafo<T>::toStringEdges() const
{
    EDGE aux(anchorEdge);
    std::string myStr;

    while (aux != nullptr)
    {

        myStr += "[ " + aux ->getFrom() ->getData() + ", " + aux ->getTo() ->getData() + " ]";

        aux = aux ->getNext();

    }

    return myStr;

}
template <class T>
bool Grafo<T>::isAdjacent(const NODE& a, const NODE& b) const
{
    if(!isValidVertex(a) and !isValidVertex(b))
    {
        throw Exception("Posicion invalida, Grafo::isAdjacent");
    }

    Edge* aux( new Edge(a,b));

    return a ->doIHave(aux);
}
template <class T>
typename Grafo<T>::ADJACENTS Grafo<T>::getAdjacencyOf(const T& e) const
{
    return getAdjacencyOf(findVertex(e));
}
template <class T>
void Grafo<T>::resetNodes()
{
    NODE aux(headerNode ->getNext());

    while(aux != headerNode)
    {

        if(aux ->isVisited())
        {
            aux ->setVisited(false);
        }

        aux = aux ->getNext();

    }

}


template <class T>
void Grafo<T>::DFS(Node* p)
{

    p ->setVisited(true);

    // Mensaje indicando que el nodo fue visitado
    qDebug() << "Visitando nodo:";
    nodosVisitados.push_back(p->getData());

    //std::cout << "Visitando nodo: " << p->getData() << std::endl;

    //std::cout << p ->getData() << ", ";


    ADJACENTS myAds = p ->getAdjacency();

    ITERATOR it;

    it = myAds.cbegin();

    for(; it != myAds.end(); ++it){

        NODE aux = it ->second ->getTo();

        if(!aux->isVisited()){

            DFS(aux);
        }
    }

}
template <class T>
const std::vector<T>& Grafo<T>::getNodosVisitados() const {
    return nodosVisitados;
}
template <class T>
void Grafo<T>::BFS(Node* p)
{
    resetNodes();

    std::queue<NODE> myQueue;

    myQueue.push(p);

    p ->setVisited(true);

    while(!myQueue.empty())
    {
        NODE aux(myQueue.front());

        myQueue.pop();

        std::cout << aux ->getData() << ", ";

        ADJACENTS myAds = aux ->getAdjacency();

        ITERATOR it;

        it = myAds.cbegin();

        for(; it != myAds.end(); ++it)
        {
            NODE temp(it ->second ->getTo());

            if(!temp ->isVisited())
            {
                myQueue.push(temp);

                temp ->setVisited(true);
            }
        }

    }

}
template <class T>
void Grafo<T>::depthFirstSearch(NODE startNode)
{
    resetNodes();

    if (startNode == nullptr) {
        startNode = getFirstVertex();
    }

    if (startNode == nullptr) {
        // Manejar el caso en que el grafo esté vacío
       qDebug() << "Grafo vacio";
            return;
    }

    DFS(startNode);
}
template <class T>
void Grafo<T>::breadthFirstSearch(const NODE& p)
{
    resetNodes();

    BFS(p);
}
template <class T>
void Grafo<T>::addVertex(const T &e)
{
    addVertex(getLastVertex(), e);
}
template <class T>
void Grafo<T>::deletVertex(const T& e)
{
    deletVertex(findVertex(e));
}
template <class T>
void Grafo<T>::addEdge(const T& a, const T& b)
{
    addEdge(getLastEdge(), findVertex(a), findVertex(b));
}
template <class T>
void Grafo<T>::deletEdge(const T& a, const T& b)
{
    deletEdge(findEdge(a, b));
}
template <class T>
std::string Grafo<T>::buildAdjacencyMatrix() const
{
    std::string myStrMax = "* | ";
    NODE aux(headerNode ->getNext());
    NODE temp;
    NODE dataABS;

    int i(0);
    while(aux != headerNode){

        if(aux == headerNode ->getNext()){
            dataABS = aux;

            while (dataABS != headerNode){
                myStrMax += dataABS ->getData() + " | ";
                dataABS = dataABS ->getNext();
            }

            myStrMax += "\n";
        }

        int j(0);
        myStrMax += aux ->getData();
        temp = headerNode ->getNext();

        while(temp != headerNode){

            if(isAdjacent(aux, temp))
            {
                myStrMax += " | 1";
            }else{
                myStrMax += " | 0";
            }
            temp = temp ->getNext();
            j++;
        }
        myStrMax += " | \n";
        aux = aux ->getNext();
        i++;
    }
    return myStrMax;
}


