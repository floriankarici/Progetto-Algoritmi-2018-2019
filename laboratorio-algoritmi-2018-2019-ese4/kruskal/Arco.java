
package kruskal;

public class Arco<V> {
    private Number peso;
    private Vertice<V> nodo1;
    private Vertice<V> nodo2;
    
    public Arco(Number peso,Vertice<V> nodo1,Vertice<V> nodo2){
        this.peso=peso;
        this.nodo1=nodo1;
        this.nodo2=nodo2;
    }
    public Number getPeso(){
        return peso;
    }
    public void setPrimoNodo(Vertice<V> nodo1){
        this.nodo1=nodo1;
    }
    public void setSecondoNodo(Vertice<V> nodo2){
        this.nodo2=nodo2;
    }
    public Vertice<V> getPrimoNodo(){
        return nodo1;
    }
     public Vertice<V> getSecondoNodo(){
        return nodo2;
    }
}
