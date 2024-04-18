#include<iostream>
#include<stdlib.h>
#include <queue> 
using namespace std;

struct Nodo 
{
    int dato;
    Nodo*der;
    Nodo*izq;
    Nodo*padre;
};

void menu();
Nodo*crearNodo(int,Nodo*);
void insertarNodo(Nodo*&,int,Nodo*);
void mostrarArbol(Nodo*,int);
bool busqueda(Nodo*,int);
void preOrden(Nodo*);
void inOrden(Nodo*);
void postOrden(Nodo*);
void eliminar(Nodo*&, int);
void eliminarNodo(Nodo*);
Nodo*minimo(Nodo*);
void reemplazar(Nodo*,Nodo*);
void destruirNodo(Nodo*);
void levelOrderTraversal(Nodo*); 

Nodo*arbol = NULL;

int main()
{
    menu();
    return 0;
}

void menu()
{
    int dato, opcion,contador=0;
    do
    {
        cout<<"\tMENU"<<endl;
        cout<<"1. Insertar un nuevo nodo"<<endl;
        cout<<"2. Mostrar el arbol completo"<<endl;
        cout<<"3. Buscar un elemento en el arbol"<<endl;
        cout<<"4. Recorrer el arbol en Pre-orden"<<endl;
        cout<<"5. Recorrer el arbol en In-orden"<<endl;
        cout<<"6. Recorrer el arbol en Post-orden"<<endl;
        cout<<"7. Recorrer el arbol por niveles"<<endl;
        cout<<"8. Eliminar un nodo del arbol"<<endl;        
        cout<<"9. Salir"<<endl;
        cout<<"Digite su opcion: ";
        cin >> opcion;
        
        switch(opcion)
        {
            case 1:
                cout<<"\nDigite un numero: ";
                cin>>dato;
                insertarNodo(arbol, dato,NULL);
                cout<<"\n";
                cin.get(); 
                break;
                
            case 2:
                cout<<"\nMostrando el arbol completo:\n\n";
                mostrarArbol(arbol,contador);
                cout<<"\n";
                system("pause");
                break;
            
            case 3:
                cout<<"\nDigite el elemento a buscar: ";
                cin>>dato;
                if(busqueda(arbol,dato)==true)
                {
                    cout<<"\nElemento "<<dato<<" a sido encontrado en el arbol\n";
                }
                else
                {
                    cout<<"\nElemento no encontrado\n";
                }
                cout<<"\n";
                system("pause");
                break;
                
            case 4:
                cout<<"\nRecorrido en pre-orden: ";
                preOrden(arbol);
                cout<<"\n\n";
                system("pause");
                break;
                
            case 5:
                cout<<"\nRecorrido en in-orden: ";
                inOrden(arbol);
                cout<<"\n\n";
                system("pause");
                break;
                
            case 6:
                cout<<"\nRecorrido en post-orden: ";
                postOrden(arbol);
                cout<<"\n\n";
                system("pause");
                break;
                
            case 7:
                cout << "\nRecorrido por niveles: ";
                levelOrderTraversal(arbol); 
                cout << "\n\n";
                system("pause");
                break;
                
            case 8:
                cout << "\nDigite el numero que desea eliminar: ";
                cin >> dato;
                eliminar(arbol, dato); 
                cout << "\n\n";
                system("pause");
                break;
        }
    } 
    while(opcion != 9);
}

Nodo*crearNodo(int n,Nodo*padre)
{
    Nodo*nuevo_nodo=new Nodo();
    
    nuevo_nodo->dato=n;
    nuevo_nodo->der=NULL;
    nuevo_nodo->izq=NULL;
    nuevo_nodo->padre=padre;
    
    return nuevo_nodo;
}

void insertarNodo(Nodo*&arbol,int n,Nodo*padre)
{
    if(arbol==NULL)
    {
        Nodo*nuevo_nodo=crearNodo(n,padre);
        arbol=nuevo_nodo;
    }
    else
    {
        int valorRaiz=arbol->dato;
        if(n<valorRaiz)
        {
            insertarNodo(arbol->izq,n,arbol);
        }
        else
        {
            insertarNodo(arbol->der,n,arbol);
        }
    }
}

void mostrarArbol(Nodo*arbol,int cont)
{
    if(arbol==NULL)
    {
        return;
    }
    else
    {
        mostrarArbol(arbol->der,cont+1);
        for(int i=0;i<cont;i++)
        {
            cout<<"   ";
        }
        cout<<arbol->dato<<endl;
        mostrarArbol(arbol->izq,cont+1);
    }
}

bool busqueda(Nodo*arbol,int n)
{
    if(arbol==NULL)
    {
        return false;
    }
    
    else if(arbol->dato==n)
    {
        return true;
    }
    
    else if(n<arbol->dato)
    {
        return busqueda(arbol->izq,n);
    }
    
    else
    {
        return busqueda(arbol->der,n);
    }
}

void preOrden(Nodo*arbol)
{
    if(arbol==NULL)
    {
        return;
    }
    else
    {
        cout<<arbol->dato<<" - ";
        preOrden(arbol->izq);
        preOrden(arbol->der);
    }
}

void inOrden(Nodo*arbol)
{
    if(arbol==NULL)
    {
        return;
    }
    else
    {
        inOrden(arbol->izq);
        cout<<arbol->dato<<" - ";
        inOrden(arbol->der);
    }
}

void postOrden(Nodo*arbol)
{
    if(arbol==NULL)
    {
        return;
    }
    else
    {
        postOrden(arbol->izq);
        postOrden(arbol->der);
        cout<<arbol->dato<<" - ";
    }
}

void eliminar(Nodo*& arbol,int n) 
{
    if(arbol==NULL) 
    {
        return;
    } 
    
    else if(n<arbol->dato) 
    {
        eliminar(arbol->izq,n);
    } 
    
    else if(n>arbol->dato) 
    {
        eliminar(arbol->der,n);
    } 
    
    else 
    {
        eliminarNodo(arbol);
    }
}

Nodo*minimo(Nodo*arbol)
{
    if(arbol==NULL)
    {
        return NULL;
    }
    
    if(arbol->izq)
    {
        return minimo(arbol->izq);
    }
    
    else
    {
        return arbol;
    }
}

void reemplazar(Nodo*arbol,Nodo*nuevoNodo) 
{
    if(arbol->padre) 
    {
        if(arbol->dato==arbol->padre->izq->dato) 
        { 
            arbol->padre->izq=nuevoNodo;
        } 
        
        else if(arbol->dato==arbol->padre->der->dato) 
        { 
            arbol->padre->der=nuevoNodo;
        }
    }

    if(nuevoNodo) 
    {
        nuevoNodo->padre=arbol->padre;
    }
}

void destruirNodo(Nodo*nodo)
{
    nodo->izq=NULL;
    nodo->der=NULL;
    
    delete nodo;
}

void eliminarNodo(Nodo*nodoEliminar) 
{
    if (nodoEliminar->izq&&nodoEliminar->der) 
    {
        Nodo*menor=minimo(nodoEliminar->der);
        nodoEliminar->dato=menor->dato;
        eliminarNodo(menor);
    } 
    
    else 
    {
        Nodo*hijo=(nodoEliminar->izq!=NULL)?nodoEliminar->izq:nodoEliminar->der;
        if (hijo) 
        {
            hijo->padre=nodoEliminar->padre;
        }
        
        if(!nodoEliminar->padre) 
        {
            arbol=hijo;
        } 
        
        else if (nodoEliminar==nodoEliminar->padre->izq) 
        {
            nodoEliminar->padre->izq = hijo;
        } 
        
        else 
        {
            nodoEliminar->padre->der=hijo;
        }
        delete nodoEliminar;
    }
}

void levelOrderTraversal(Nodo*arbol)
{
    if(arbol==NULL)
        return;

    queue<Nodo*>q;
    q.push(arbol);

    while(!q.empty())
    {
        Nodo*current=q.front();
        q.pop();
        cout<<current->dato<<" ";

        if(current->izq!=NULL)
            q.push(current->izq);
        if(current->der!=NULL)
            q.push(current->der);
    }
}
