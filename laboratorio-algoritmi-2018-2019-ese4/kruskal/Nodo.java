
package kruskal;

public class Nodo<V>{
    private V element;
    private Nodo<V> parent;
    private int rank=0;
    public  Nodo(V element){
        this.element=element;
        this.parent=this;
    }
    public int getRank(){
        return rank;
    }
    public void setRank(int rank){
        this.rank=rank;
    }
    public V getElement(){
        return this.element;
    }
    public void  setParent(Nodo<V> nodo){
        this.parent=nodo;
    }
    public Nodo<V> getParent(){
        return this.parent;
    }
}
