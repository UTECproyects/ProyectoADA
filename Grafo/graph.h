#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <map>
#include <set>
#include <limits>
#include <unordered_map>
#include <math.h>

#include <limits.h>
#include <utility>
#include <queue>
#include <algorithm>
#include <iomanip>

#include "node.h"
#include "edge.h"

#define INF 9999

using namespace std;

struct matrices
{
    int **distancias;
    int **caminos;
    matrices(const unsigned int n)
    {
        distancias = new int *[n];
        for (int i = 0; i < n; i++)
        {
            distancias[i] = new int[n];
        }
        caminos = new int *[n];
        for (int i = 0; i < n; i++)
        {
            caminos[i] = new int[n];
        }
    }
};
//kennet louden contrucccion de comppiladores
class Traits
{
public:
    typedef char N;
    typedef long E;
};

template <typename Tr>
class Graph
{
public:
    typedef Graph<Tr> self;
    typedef Node<self> node;
    typedef Edge<self> edge;
    typedef unordered_map<long, node *> NodeSeq;
    typedef unordered_map<long, edge *> EdgeSeq;
    typedef typename Tr::N N;
    typedef typename Tr::E E;
    typedef typename NodeSeq::iterator NodeIte;
    typedef typename EdgeSeq::iterator EdgeIte;

    Graph(){};
    void tipo(bool tipo)
    {
        nodes
            dir = tipo;
    };
    //-----------------------------------------------------------------------TOTAL NODOS
    unsigned long total_nodos()
    {
        return nodes.size();
    }
    //-----------------------------------------------------------------------TOTAL ARISTAS
    int total_aristas()
    {
        if (nodes.empty())
        {
            return 0;
        }
        int c = 0;
        for (ni = nodes.begin(); ni != nodes.end(); ++ni)
        {
            c = c + ni->second->edges.size();
        }
        return c;
    }
    //-----------------------------------------------------------------------INFO NODO
    /*void info_nodo(){
            N vertice;
            cout<<"Inserte el vertice del que quiere informacion: ";
            cin>>vertice;
            node* temp=buscar_vertice(vertice);
            int c=0;
            if(temp==nullptr){
                cout <<"El vertice no existe"<<endl;
                return;
            }
            if(dir==1){
                cout <<"El grado de salida es: "<<temp->edges.size()<<endl;
                for (ni=nodes.begin();ni!=nodes.end();++ni){
                    for(ei=(*ni)->edges.begin();ei!=(*ni)->edges.end();++ei){
                        if((*ei)->nodes[1]->get()==vertice){
                            c++;
                        }
                    }
                }
                cout <<"El grado de entrada es: "<<c<<endl;
                if(temp->edges.size()==0 && c==0){
                    cout<<"El vertice esta aislado"<<endl;
                }else if(temp->edges.size()==0){
                    cout<<"El vertice es hundido"<<endl;
                }else if(c==0){
                    cout<<"El vertice es fuente"<<endl;
                }
            }else{
                cout <<"El grado del vertice es: "<<temp->edges.size()<<endl;
                if(temp->edges.size()==0){
                    cout<<"El vertice esta aislado"<<endl;
                }
            }
        }*/
    //-----------------------------------------------------------------------INSERTAR NODO
    void insertar_nodo(E id, double x, double y)
    {
        if (buscar_vertice(id) != nullptr)
        {
            cout << "Nodo " << id << " ya existente" << endl;
            //system("pause");
            return;
        }
        node *temp = new node(id, x, y);
        nodes.insert(pair<E, node *>(id, temp));
    };
    //-----------------------------------------------------------------------INSERTAR ARISTA
    void insertar_arista(E v1, E v2, string nombre, double peso)
    {
        if (buscar_arista(v1, v2) != nullptr)
        {
            cout << "Arista " << v1 << "-" << v2 << " ya existe" << endl;
            //system("pause");
            return;
        }
        edge *temp1 = new edge(peso, nombre, nodes[v1], nodes[v2]);
        nodes[v1]->edges.insert(pair<E, edge *>(v2, temp1));
    }
    //-----------------------------------------------------------------------ELIMINAR ARISTA
    EdgeIte eliminar_arista(E v1, E v2)
    {
        if (buscar_arista(v1, v2) == nullptr)
        {
            cout << "Arista " << v1 << " - " << v2 << " no existe" << endl;
            return;
        }
        delete nodes[v1]->edges[v2];
        return nodes[v1].erase(v2);
    }
    //-----------------------------------------------------------------------ELIMAR NODO
    void eliminar_nodo(N v1)
    {
        for (ni = nodes.begin(); ni != nodes.end(); ++ni)
        {
            ei = ni->second->edges.find(v1);
            if (ei != ni->second->edges.end())
                eliminar_arista(ni->first, v1);
        }
        for (ei = nodes[v1]->edges.begin(); ni != nodes[v1]->edges.end(); ++ei)
        {
            eliminar_arista(v1, ei->first);
        }
        delete nodes[v1];
        nodes.erase(v1);
    }
    //-----------------------------------------------------------------------BUSCAR VERTICE
    node *buscar_vertice(E v1)
    {
        ni = nodes.find(v1);
        if (ni != nodes.end())
            return ni->second;
        cout << "Nodo " << v1 << " no existe" << endl;
        return nullptr;
    }
    //-----------------------------------------------------------------------BUSCAR ARISTA
    edge *buscar_arista(E v1, E v2)
    {
        if (buscar_vertice(v1) == nullptr || buscar_vertice(v2) == nullptr)
            return nullptr;
        ei = nodes[v1]->edges.find(v2);
        if (ei != nodes[v1]->edges.end())
            return ei->second;
        return nullptr;
    }
    //-----------------------------------------------------------------------PRINT
    void print()
    {
        for (ni = nodes.begin(); ni != nodes.end(); ++ni)
        {
            cout << ni->first << endl;
            for (ei = ni->second->edges.begin(); ei != ni->second->edges.end(); ++ei)
            {
                cout << "nodo : " << ei->first << " peso : " << ei->second->get() << " name: " << ei->second->get_nombre() << " / ";
            }
            cout << endl;
        }
    }
    void printxy()
    {
        for (ni = nodes.begin(); ni != nodes.end(); ++ni)
        {
            cout << ni->first << " " << ni->second->get_x() << " " << ni->second->get_y() << endl;
        }
    }
    //-----------------------------------------------------------------------DENSIDAD
    /*double densidad(){
            if(dir==0){
                return (total_aristas()*2)/(total_nodos()*(total_nodos()-1));
            }else{
                return total_aristas()/(total_nodos()*(total_nodos()-1));
            }

        }*/
    //-----------------------------------------------------------------------DFS
    /*list<char> dfs(){
            stack<node*> q;
            list<char> tt;
            if(total_aristas()==0){
                return tt;
            }
            node* temp;
            node* temp1;
            q.push(nodes[0]);
            nodes[0]->tool=1;
            while(!q.empty()){
                temp=q.top();
                for(ei=temp->edges.begin();ei!=temp->edges.end();++ei){
                    if(temp!= (*ei)->nodes[1]){
                        temp1=(*ei)->nodes[1];
                    }else{
                        temp1=(*ei)->nodes[0];
                    }
                    if(temp1->tool==0){
                        q.push(temp1);
                        temp1->tool=1;
                        goto endwhile;
                    }

                }

                tt.push_front(q.top()->get());
                q.pop();
            endwhile:;
            }
            for (ni=nodes.begin();ni!=nodes.end();++ni){
                (*ni)->tool=0;
            }
            return tt;
        }*/
    //-----------------------------------------------------------------------CONEXO
    /*void conexo(){
            list<char> cierre=dfs();
            if(cierre.size()==nodes.size()){
                if(dir==0){
                    cout<<"El grafo es conexo"<<endl;
                }else{
                    Graph<Traits> g2;
                    g2.tipo(true);
                    for (ni=nodes.begin();ni!=nodes.end();++ni){
                        g2.insertar_nodo(1,1,(*ni)->get());
                    }
                    for (ni=nodes.begin();ni!=nodes.end();++ni){
                        for(ei=(*ni)->edges.begin();ei!=(*ni)->edges.end();++ei){
                            g2.insertar_arista((*ei)->nodes[1]->get(),(*ei)->nodes[0]->get(),1);
                        }
                    }
                    if(g2.dfs().size()==nodes.size()){
                        cout <<"El grafo es fuertemente conexo"<<endl;
                    }else{
                        cout <<"El grafo NO es fuertemente conexo"<<endl;
                    }
                }

            }else{
                cout <<"El grafo no es conexo"<<endl;
            }

        }*/
    //-----------------------------------------------------------------------PRIM
    /*void prim(){
            if(dir==1){
                cout<<"No se puede aplicar prim, el grafo es dirigido"<<endl;
            }else if(dfs().size()!=nodes.size()){
                cout<<"No se puede apliar prim, el grafo no es conexo"<<endl;
            }else{
                map<node*,bool> nodos;
                multimap<E,edge*> pesos;
                typename multimap<E,edge*>::iterator it;
                Graph<Traits> g2;
                g2.tipo(false);
                nodos.insert(pair<node*,bool>(nodes[0],0));
                g2.insertar_nodo(1,1,nodes[0]->get());
                for(ei=nodes[0]->edges.begin();ei!=nodes[0]->edges.end();++ei){
                    pesos.insert(pair<E,edge*>((*ei)->get(),(*ei)));
                }
                while(nodos.size()!=nodes.size()){
                    it=pesos.begin();
                    if(nodos.count(it->second->nodes[1])==0 || nodos.count(it->second->nodes[0])==0){
                        node* temp;
                        if(nodos.count(it->second->nodes[1])==0){
                            temp=it->second->nodes[1];
                        }else{
                            temp=it->second->nodes[0];
                        }
                        nodos.insert(pair<node*,bool>(temp,0));
                        g2.insertar_nodo(1,1,temp->get());
                        g2.insertar_arista(it->second->nodes[0]->get(),it->second->nodes[1]->get(),it->first);
                            pesos.erase(it);
                        for(ei=temp->edges.begin();ei!=temp->edges.end();++ei){
                            pesos.insert(pair<E,edge*>((*ei)->get(),(*ei)));
                        }
                    }else{
                        pesos.erase(it);
                    }
                }
                g2.print();
            }
        }*/
    //-----------------------------------------------------------------------KRUSKAL
    /*void kruskal(){
        if(dir==1){
            cout<<"No se puede aplicar kruskal, el grafo es dirigido"<<endl;
            return;
        }else if(dfs().size()!=nodes.size()){
            cout<<"No se puede aplicar kruskal, el grafo no es conexo"<<endl;
            return;
        }
            map<node*,bool> nodos;
            multimap<E,edge*, less<int>> pesos;
            typename multimap<E,edge*>::iterator it;
            Graph<Traits> g2;
            g2.tipo(false);
            nodos.insert(pair<node*,bool>(nodes[0],0));
            g2.insertar_nodo(1,1,nodes[0]->get());
            for(ei=nodes[0]->edges.begin();ei!=nodes[0]->edges.end();++ei){
                pesos.insert(pair<E,edge*>((*ei)->get(),(*ei)));
            };
            while(nodos.size()!=nodes.size()){
                it=pesos.begin();
                if(nodos.count(it->second->nodes[0])==0 || nodos.count(it->second->nodes[1])==0){
                    node* temp;
                    if(nodos.count(it->second->nodes[1])==0){
                        temp=it->second->nodes[1];
                    }else{
                        temp=it->second->nodes[0];
                    }
                    nodos.insert(pair<node*,bool>(temp,0));
                    g2.insertar_nodo(1,1,temp->get());
                    g2.insertar_arista(it->second->nodes[0]->get(),it->second->nodes[1]->get(),it->first);
                    pesos.erase(it);
                    for(ei=temp->edges.begin();ei!=temp->edges.end();++ei){
                        pesos.insert(pair<E,edge*>((*ei)->get(),(*ei)));
                    }
                }else{
                    pesos.erase(it);
                }
            }

            g2.print();

        }*/
    //-----------------------------------------------------------------------BFS
    /*bool BFS(){

            stack<node*> q;
            int a=0;
//            if(total_aristas()==0){
//                return tt;
//            }
            node* temp;
            node* temp1;
            q.push(nodes[0]);
            nodes[0]->tool=1;
            a++;
            while(!q.empty()){
                bool aed=0;
                temp=q.top();
                for(ei=temp->edges.begin();ei!=temp->edges.end();++ei){
                    if(temp!= (*ei)->nodes[1]){
                      temp1=(*ei)->nodes[1];
                    }else{
                        temp1=(*ei)->nodes[0];
                    }
                    if(temp1->tool==0){
                        q.push(temp1);
                        temp1->tool=1;
                        aed=1;
                        a++;
                    }
                }

                if(aed==0)
                q.pop();
            }

            for (ni=nodes.begin();ni!=nodes.end();++ni){
                (*ni)->tool=0;
            }

            if(a==nodes.size()){
            return true;
            }else {
                return false;
            }
        }*/
    //-----------------------------------------------------------------------BIPARTITO
    /*void bipartito(){
            if(dfs().size()!=nodes.size()){
                cout <<"El grafo no es conexo"<<endl;
                return;
            }
            map<node*,bool> nodos;
            stack<node*> q;
            node* temp;
            node* temp1;
            q.push(nodes[0]);
            nodos.insert(pair<node*,bool>(nodes[0],0));
            nodes[0]->tool=1;
            while(!q.empty()){
                temp=q.top();
                for(ei=temp->edges.begin();ei!=temp->edges.end();++ei){
                    if(temp!= (*ei)->nodes[1]){
                        temp1=(*ei)->nodes[1];
                    }else{
                        temp1=(*ei)->nodes[0];
                    }
                    if(temp1->tool==0){
                        q.push(temp1);
                        nodos.insert(pair<node*,bool>(temp1,!nodos[temp]));
                        temp1->tool=1;
                        goto endwhile;
                    }else{
                        if(nodos[temp]==nodos[temp1]){
                            cout<<"El grafo no es bipartito"<<endl;
                            return;
                        }
                    }

                }
                q.pop();
            endwhile:;
            }
            for (ni=nodes.begin();ni!=nodes.end();++ni){
                (*ni)->tool=0;
            }
            cout<<"El grafo es bipartito"<<endl;

        }*/
    //-----------------------------------------------------------------------A*
    double distance(N v1, N v2)
    {
        node *temp1 = buscar_vertice(v1);
        node *temp2 = buscar_vertice(v2);
        return sqrt(pow(temp1->get_x() - temp2->get_x(), 2) + pow(temp1->get_y() - temp2->get_y(), 2));
    }
    list<node *> A_Star(N v1, N v2)
    {
        set<N> exitt;
        node *temp = buscar_vertice(v1);
        multimap<double, node *> nodos;
        typename multimap<double, node *>::iterator it;
        nodos.insert(pair<double, node *>(distance(v1, v2), temp));
        unordered_map<N, pair<double[2], N>> tabla;
        tabla[v1].first[0] = 0;
        tabla[v1].first[1] = distance(v1, v2);
        tabla[v1].second = v1;
        while (!nodos.empty())
        {
            it = nodos.begin();
            temp = it->second;
            nodos.erase(it);
            if (temp->get() == v2)
            {
                break;
            }
            for (ei = temp->edges.begin(); ei != temp->edges.end(); ++ei)
            {
                char aa = (*ei)->goes_to(temp->get())->get();
                if (exitt.count(aa) == 1)
                {
                    continue;
                }
                double bb = tabla[temp->get()].first[0] + (*ei)->get();
                if (tabla.count(aa) == 1)
                {
                    if (bb < tabla[aa].first[0])
                    {
                        tabla[aa].first[0] = bb;
                        tabla[aa].first[1] = bb + distance(aa, v2);
                        tabla[aa].second = temp->get();
                        for (it = nodos.begin(); it != nodos.end(); ++it)
                        {
                            if (it->second->get() == aa)
                            {
                                nodos.erase(it);
                                nodos.insert(pair<double, node *>(bb + distance(aa, v2), (*ei)->goes_to(temp->get())));
                                break;
                            }
                        }
                    }
                }
                else
                {
                    tabla[aa].first[0] = bb;
                    tabla[aa].first[1] = bb + distance(aa, v2);
                    tabla[aa].second = temp->get();
                    nodos.insert(pair<double, node *>(bb + distance(aa, v2), (*ei)->goes_to(temp->get())));
                }
            }
            exitt.insert(temp->get());
        }
        list<node *> lit;
        typename list<node *>::iterator itt;
        typename unordered_map<N, pair<double[2], N>>::iterator ite;
        ite = tabla.find(v2);
        if (ite != tabla.end())
        {
            while (ite->first != v1)
            {
                lit.push_front(buscar_vertice(ite->first));
                ite = tabla.find(ite->second.second);
            }
            lit.push_front(buscar_vertice(v1));
        }
        else
        {
            cout << "No se pudo llegar al nodo deseado" << endl;
        }
        for (itt = lit.begin(); itt != lit.end(); ++itt)
        {
            cout << (*itt)->get() << " ";
        }
        cout << endl;
        return lit;
    }
    //-----------------------------------------------------------------------FLOYD WARSHALL
    /*matrices* floyd_warshall(){
            const unsigned int n=total_nodos();
            matrices* matriss=new matrices(n);
            unordered_map<E,N> refe;
            for(int i=0;i<nodes.size();i++){
                refe.insert(pair<E,N>(i,nodes[i]->get()));
            }
            for(int i=0;i<n;i++){
                for(int j=0;j<n;j++){
                    if(i==j){
                        matriss->distancias[i][j]=0;
                        continue;
                    }
                    edge* temp=buscar_arista(refe[i],refe[j]);
                    if(temp==nullptr){
                        matriss->distancias[i][j]=INF;
                    }else{
                        matriss->distancias[i][j]=temp->get();
                    }
                }
            }
            for(int i=0;i<n;i++){
                for(int j=0;j<n;j++){
                    if(i==j){
                        matriss->caminos[i][j]=INF;
                        continue;
                    }
                    matriss->caminos[i][j]=j;
                }
            }
            for(int k=0;k<n;k++){
                for(int i=0;i<n;i++){
                    if(i==k){
                        continue;
                    }
                    for(int j=0;j<n;j++){
                        if(j==k){
                            continue;
                        }
                        if(i==j){
                            continue;
                        }
                        if(matriss->distancias[i][j] > matriss->distancias[k][j] + matriss->distancias[i][k]){
                           matriss->distancias[i][j]= matriss->distancias[k][j] + matriss->distancias[i][k];
                           matriss->caminos[i][j] = k;
                        }
                    }
                }
            }
            //IMPRIMIR----------------------------
            for(int i=0;i<n;i++){
                for(int j=0;j<n;j++){
                    cout<<matriss->distancias[i][j]<<" ";
                }
                cout<<endl;
            }
            cout<<endl;

            for(int i=0;i<n;i++){
                for(int j=0;j<n;j++){
                    cout<<matriss->caminos[i][j]<<" ";
                }
                cout<<endl;
            }
            cout<<endl;
            return matriss;



        }*/

    //------------------------------------------------------------------------GREEDYBFS
    /*bool visitado(node* node , NodeSeq visitedNodes){
            for (int i = 0; i < visitedNodes.size(); ++i)
            {
                if (node == visitedNodes[i])
                {
                    return true;
                }
            }
            return false;
        }*/

    /*self greedyBFS(N start, N end){
            Graph* grdy = new Graph;
            NodeSeq lista_vst , ruta;
            node* inicio  = this->buscar_vertice(start);
            node* fin = this->buscar_vertice(end);
            node* temp = inicio;
            lista_vst.push_back(inicio);
            ruta.push_back(inicio);

            for (int i = 0; i < nodes.size(); ++i){
                grdy->insertar_nodo(1,1,nodes[i]->get());
            }

            while(lista_vst.back() != fin){
                node* min_opc = nullptr;
                int peso_less = numeric_limits<int>::max();
                EdgeSeq* nodeEdges = &(temp->edges);
                for(auto it : *nodeEdges){
                    if (it->get() < peso_less && !visitado(((*it).nodes[1]),lista_vst)){
                        peso_less = it->get();
                        min_opc = it->nodes[1];
                    }
                }
                if(min_opc){
                    lista_vst.push_back(min_opc);
                    ruta.push_back(min_opc);
                    temp= ruta.back();
                }else{
                    ruta.pop_back();
                    temp= ruta.back();
                }
            }

            for (int i = 0; i < ruta.size()-1; ++i){
                grdy->insertar_arista(ruta[i+1]->get(),ruta[i]->get(),
                               (this-> buscar_arista(ruta[i]->get(),
                                ruta[i+1]->get())) ->get());
            }
            grdy->print();
            return *grdy;
        }*/

    //--------------------------------------------------------------------DIJKSTRA
    /*map<N,E> dijkstra(N vertice){
            map<N,E> table;
            set<N> visited;
            node* root = buscar_vertice(vertice);
            N lesser;
            for(auto ni:nodes){
                if(ni==root){table.insert(pair<N,int>(ni->get(),0));
                }
                else{table.insert(pair<N,int>(ni->get(),INT_MAX));
                }

            }

            int menor = INT_MAX;

            while(visited.size()!=nodes.size()){

                visited.insert(root->get());

                for(auto ei:root->edges){
                    int values = table[root->get()];
                    int move = table[ei->nodes[1]->get()];
                    if(ei->get()+values < move){
                        cout << ei->nodes[0]->get()<< "-" << ei->nodes[1]->get() << ": "<< ei->get()+values << "\n";
                        table[ei->nodes[1]->get()] = ei->get()+values;
                    }
                }
                for(auto nodos:table){
                    if(nodos.second < menor && find(visited.begin(),visited.end(),nodos.first)==visited.end()){
                        menor = nodos.second;
                        lesser = nodos.first;
                    }
                }
                menor = INT_MAX;
                root = buscar_vertice(lesser);
            }

            return table;

        }*/
    //-------------------------------------------------------------BELLMANFORD
    /*map<N,E>bellmanford(N vertice){
            return dijkstra(vertice);
        }*/

    ~Graph(){
        /*for (ni=nodes.begin();ni!=nodes.end();++ni){
                eliminar_nodo((*ni)->get());
            }*/

    };

private:
    bool dir;
    NodeSeq nodes;
    NodeIte ni;
    EdgeIte ei;

public:
    NodeSeq getNodes()
    {
        return (nodes);
    }
};

typedef Graph<Traits> graph;

#endif
