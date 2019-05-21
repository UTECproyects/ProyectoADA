#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include <list>
#include <map>
#include <set>
#include <unordered_map>
#include <math.h>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include "node.h"
#include "edge.h"
#include "taxi.h"

#define INF 9999

using namespace std;

//kennet louden contrucccion de comppiladores
#ifdef _WIN32
class Traits
{
public:
    typedef char N;
    typedef long long E;
};
#else
class Traits
{
public:
    typedef char N;
    typedef long E;
};
#endif


template <typename Tr>
class Graph
{
public:
    typedef Graph<Tr> self;
    typedef Node<self> node;
    typedef Edge<self> edge;
    typedef Taxi<self> taxi;
    typedef typename Tr::N N;
    typedef typename Tr::E E;
    typedef unordered_map<E, node *> NodeSeq;
    typedef unordered_map<E, edge *> EdgeSeq;
    typedef unordered_map<E, taxi *> taxis;
    typedef typename NodeSeq::iterator NodeIte;
    typedef typename EdgeSeq::iterator EdgeIte;
    typedef typename taxis::iterator txite;

    Graph(){};
    void tipo(bool tipo)
    {
        dir = tipo;
    };
    //-----------------------------------------------------------------------TOTAL NODOS
    int total_nodos()
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
            //cout<<"Nodo "<<id <<" ya existente"<<endl;
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
            //cout<<"Arista "<<v1<<"-"<<v2<<" ya existe"<<endl;
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
        //cout<<"Nodo "<<v1<<" no existe"<<endl;
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
    //-----------------------------------------------------------------------Taxistas
    taxi *buscar_taxista(E id)
    {
        return taxistas[id];
    }
    void iniciar_taxis(int n)
    {
        map<E, E> nodesid;
        E id = 0;
        for (ni = nodes.begin(); ni != nodes.end(); ++ni)
        {
            id++;
            nodesid.insert(pair<E, E>(id, ni->first));
        }
        srand((int)time(0));
        for (int i = 0; i < n; i++)
        {
            int r = (rand() % total_nodos());
            taxi *temp = new taxi(i, nodes[nodesid[r]], nodes[nodesid[r]]->get_x(), nodes[nodesid[r]]->get_y());
            cout << temp->get() << " " << temp->nodo->get() << " " << temp->get_x() << " " << temp->get_y() << endl;
            taxistas.insert(pair<E, taxi *>(i, temp));
        }
    }
    void mover_taxis()
    {
        srand((int)time(0));
        int r;
        for (ti = taxistas.begin(); ti != taxistas.end(); ++ti)
        {
            r = (rand() % 3) + 1;
            if (r < 3)
            {
                r = (rand() % ti->second->nodo->edges.size()) + 1;
                ei = ti->second->nodo->edges.begin();
                for (int z = 1; z < r; z++)
                {
                    ei++;
                }
                ti->second->nodo = ei->second->nodes[1];
                ti->second->set_xy(ti->second->nodo->get_x(), ti->second->nodo->get_y());
                cout << ti->second->get() << " " << ti->second->get_x() << " " << ti->second->get_y() << endl;
            }
        }
    }
    NodeSeq getNodes()
    {
        return nodes;
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
    inline double DegreeToRadian(double angle)
    {
        return M_PI * angle / 180.0;
    }
    double distance(E tempini, E tempfin)
    {
        map<E, pair<double, double>> idcoords;
        double latRad1 = DegreeToRadian(idcoords[tempini].second);
        double latRad2 = DegreeToRadian(idcoords[tempfin].second);
        double lonRad1 = DegreeToRadian(idcoords[tempini].first);
        double lonRad2 = DegreeToRadian(idcoords[tempfin].first);

        double diffLa = latRad2 - latRad1;
        double doffLo = lonRad2 - lonRad1;

        double computation = asin(sqrt(sin(diffLa / 2) * sin(diffLa / 2) + cos(latRad1) * cos(latRad2) * sin(doffLo / 2) * sin(doffLo / 2)));
        return 2 * 6372.8 * computation * 1000;
    }
    pair<double, list<node *>> A_Star(E v1, E v2)
    {
        //typename multimap<double,node*>::iterator it;
        typedef typename multimap<double, node *>::iterator iter;
        iter it;
        set<E> exitt;
        node *temp = buscar_vertice(v1);
        multimap<double, node *> nodos;
        nodos.insert(pair<double, node *>(distance(v1, v2), temp));
        unordered_map<E, pair<double[2], E>> tabla;
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
                E next_node = ei->first;
                if (exitt.count(next_node) == 1)
                {
                    continue;
                }
                double new_wei = tabla[temp->get()].first[0] + ei->second->get();
                if (tabla.count(next_node) == 1)
                {
                    if (new_wei < tabla[next_node].first[0])
                    {
                        pair<iter, iter> rango;
                        rango = nodos.equal_range(tabla[next_node].first[0]);
                        tabla[next_node].first[0] = new_wei;
                        tabla[next_node].first[1] = new_wei + distance(next_node, v2);
                        tabla[next_node].second = temp->get();
                        for (it = rango.first; it != rango.second; ++it)
                        {
                            if (it->second->get() == next_node)
                            {
                                nodos.erase(it);
                                nodos.insert(pair<double, node *>(new_wei + distance(next_node, v2), ei->second->nodes[1]));
                                break;
                            }
                        }
                    }
                }
                else
                {
                    tabla[next_node].first[0] = new_wei;
                    tabla[next_node].first[1] = new_wei + distance(next_node, v2);
                    tabla[next_node].second = temp->get();
                    nodos.insert(pair<double, node *>(new_wei + distance(next_node, v2), ei->second->nodes[1]));
                }
            }
            exitt.insert(temp->get());
        }
        list<node *> lit;
        typename list<node *>::iterator itt;
        typename list<node *>::iterator ity;
        typename unordered_map<E, pair<double[2], E>>::iterator ite;
        ite = tabla.find(v2);
        double dist;
        if (ite != tabla.end())
        {
            dist = ite->second.first[0];
            //cout << dist << endl;
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
        
        ity = lit.begin();
        for (itt = lit.begin(); itt != lit.end(); ++itt)
        {
            
            cout << (*itt)->get() <<endl;                        
        }
        
        cout << endl;

        return make_pair(dist, lit);
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
    E menor_d(unordered_map<E,double> nodos){
        typedef typename unordered_map<E, double>::iterator iter;
        iter it;
        if(nodos.empty()){cout<<"error en nodos:Dijkstra";return 0;}
        double menor=99999999;
        E nodo_menor;
        for(it=nodos.begin();it!=nodos.end();++it){
            if(it->second<menor){
                nodo_menor=it->first;
                menor=it->second;
            }
        }
        return nodo_menor;
    }
    list<node *> Dijkstra(E v1, E v2){
        typedef typename unordered_map<E, double>::iterator iter;        
        unordered_map<E, double> nodos;
        unordered_map<E,E> tabla;
        set<E> exitt;
        iter it;
        node* curr_node;
        nodos.insert(pair<E,double>(v1,0));
        tabla.insert(pair<E,E>(v1,v1));        
        while(!nodos.empty()){                   
            E curr_node_id= menor_d(nodos);                           
            curr_node=buscar_vertice(curr_node_id);            
            if (curr_node->get() == v2)break;                        

            for (ei = curr_node->edges.begin(); ei != curr_node->edges.end(); ++ei){
                E next_node = ei->first;
                if (exitt.count(next_node) == 1)continue;
                double new_wei = nodos[curr_node->get()] + ei->second->get();

                if (nodos.count(next_node) == 1){
                    if (new_wei < nodos[next_node]){                        
                        nodos[next_node] = new_wei;
                        tabla[next_node]=curr_node->get();                                                
                    }
                }
                else{
                    nodos.insert(pair<E,double>(next_node,new_wei));
                    tabla.insert(pair<E,E>(next_node,curr_node->get()));                    
                }
            }
            nodos.erase(curr_node_id);
            exitt.insert(curr_node->get());                    
        }

        list<node *> lit;
        typename list<node *>::iterator its;
        typename list<node *>::iterator ity;
        typename unordered_map<E,E>::iterator ite;
        ite = tabla.find(v2);
        double dist;
        if (ite != tabla.end()){                        
            while (ite->first != v1){
                lit.push_front(buscar_vertice(ite->first));
                ite = tabla.find(ite->second);
            }
            lit.push_front(buscar_vertice(v1));
        }
        else{
            cout << "No se pudo llegar al nodo deseado" << endl;
        }
        for(its=lit.begin();its!=lit.end();++its){
            cout<<(*its)->get()<<endl;
        }
        return lit;
    }
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
    taxis taxistas;
    NodeIte ni;
    EdgeIte ei;
    txite ti;
};

typedef Graph<Traits> graph;

#endif
