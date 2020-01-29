package kruskal;



import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;
import java.util.Set;

public class Grafo < V> {
    private HashMap < V,
    ArrayList < Arco>>setNodi;

    private Number totalWeight=0;
    boolean diretto;

    //true se il grafo e diretto false in altri casi
    public Grafo(boolean diretto) {
        setNodi=new HashMap <>();

        this.diretto=diretto;
    }

    public int getSize() {
        return setNodi.size();
    }

    public boolean getType() {
        return diretto;
    }

    public boolean addNodo(V newNodo) {
        Vertice < V>nodo=new Vertice(newNodo);

        if (setNodi.containsKey(nodo.getElement())) {
            return false;
        }

        setNodi.put((V) nodo.getElement(), new ArrayList < Arco > ());
        return true;
    }

    public boolean aggiungiArco(V nodo1, V nodo2, Number peso) {
        Vertice < V>n1=new Vertice(nodo1);
        Vertice < V>n2=new Vertice(nodo2);
        Arco < V>arcoAndata=new Arco(peso, n1, n2);
        Arco < V>arcoRitorno=new Arco(peso, n2, n1);
        if ( !setNodi.containsKey(n1.getElement()) || !setNodi.containsKey(n2.getElement())) return false;

        if (diretto) {
            if (arcoEsiste(arcoAndata)) return false;
            setNodi.get(n1.getElement()).add(arcoAndata);
            setTotalWeight(arcoAndata.getPeso().doubleValue());

            return true;
        }

        if (arcoEsiste(arcoAndata) && arcoEsiste(arcoRitorno)) return false;
        setNodi.get(n1.getElement()).add(arcoAndata);
        setNodi.get(n2.getElement()).add(arcoRitorno);
        setTotalWeight(arcoAndata.getPeso().doubleValue());
        setTotalWeight(arcoRitorno.getPeso().doubleValue());

        return true;
    }

    public boolean deleteNode(V element) {
        if ( !setNodi.containsKey(element)) return false;
        setNodi.remove(element);
        return true;
    }

    public boolean deleteEdge(V element, Arco a) {
        if ( !setNodi.containsKey(element) || !arcoEsiste(a)) return false;

        if (getType()) {
            setNodi.get(element).remove(a);
            return true;
        }

        V element2=(V) a.getSecondoNodo().getElement();
        Arco aTemp=new Arco(a.getPeso(), a.getSecondoNodo(), a.getPrimoNodo());
        setNodi.get(element).remove(a);
        setNodi.get(element2).remove(aTemp);
        return true;
    }

    public boolean arcoEsiste(Arco arco) {
        Vertice<V>n1=arco.getPrimoNodo();
        Vertice<V>n2=arco.getSecondoNodo();
        ArrayList data1=setNodi.get(n1.getElement());
        ArrayList data2=setNodi.get(n2.getElement());


        for(int j=0; j<data1.size(); j++) {
            Arco a=(Arco) data1.get(j);
            if (a.getPrimoNodo().getElement().equals(n1.getElement()) && a.getSecondoNodo().getElement().equals(n2.getElement())) return true;
        }


        return false;
    }

    public boolean containsNode(Vertice<V> element) {
        if(setNodi.containsKey(element.getElement())) return true;
        return false;
    }

    public int getNumNode() {
        return setNodi.size();
    }

    public int getNumEdges_n() {
        ArrayList<Arco>a=new ArrayList<>();
        int num=0;

        if(getType()) {
            for(Map.Entry<V, ArrayList<Arco>> entry : setNodi.entrySet()) {
                a=entry.getValue();
                num+=a.size();
            }

            return num;
        }

        for(Map.Entry<V, ArrayList<Arco>> entry : setNodi.entrySet()) {
            a=entry.getValue();
            num+=a.size();
        }

        return num/2;
    }

    public ArrayList<V>getNodi() {
        ArrayList<V>a=new ArrayList<>();

        for(Map.Entry<V, ArrayList<Arco>> entry : setNodi.entrySet()) {
            a.add(entry.getKey());
        }

        return a;
    }

    public ArrayList<Arco>getArchi() {
        ArrayList<Arco>a=new ArrayList<>();
        Arco tmp;
        Vertice<V>tmp1;

        if(getType()) {
            for(Map.Entry<V, ArrayList<Arco>> entry : setNodi.entrySet()) {
                for(int i=0; i<entry.getValue().size(); i++) a.add(entry.getValue().get(i));
            }

            return a;
        }

        for(Map.Entry<V, ArrayList<Arco>> entry : setNodi.entrySet()) {
            for(int i=0; i<entry.getValue().size(); i++) {
                tmp=entry.getValue().get(i);
                tmp1=tmp.getPrimoNodo();
                tmp.setPrimoNodo(tmp.getSecondoNodo());
                tmp.setSecondoNodo(tmp1);
                if( !a.contains(tmp)) a.add(entry.getValue().get(i));
            }
        }

        return a;
    }

    public ArrayList<Vertice<V>>getVicini(Vertice<V> element) {
        ArrayList<Vertice<V>>vicini=new ArrayList<>();
        ArrayList<Arco>a=setNodi.get(element.getElement());
        for(int i=0; i<a.size(); i++) vicini.add(a.get(i).getSecondoNodo());
        return vicini;
    }

    public HashMap<V,
    ArrayList<Arco>>getMap() {
        return setNodi;
    }

    public void setTotalWeight(Number weight) {
        totalWeight=totalWeight.doubleValue()+weight.doubleValue();
    }

    public Number getTotalWeight() {
        if(getType()) return totalWeight;
        return totalWeight.doubleValue()/2;
    }

    public ArrayList<Arco>getListEdges() throws InterruptedException {
        boolean trovato;
        ArrayList<Arco>arrayEdges=new ArrayList<>();
        ArrayList<Arco>sortedArray=new ArrayList<>();
        Iterator it=getMap().entrySet().iterator();

        if(getType()) {
            while(it.hasNext()) {
                int i=0;
                Map.Entry entry=(Map.Entry) it.next();

                arrayEdges=(ArrayList)entry.getValue();

                for(int w=0; w<arrayEdges.size(); w++) {
                    sortedArray.add(arrayEdges.get(w));
                }
            }

            Collections.sort(sortedArray, new ComparatorEdges());
            return sortedArray;
        }

        while(it.hasNext()) {
            int i=0;
            Map.Entry entry=(Map.Entry) it.next();

            arrayEdges=(ArrayList)entry.getValue();

            for(int w=0; w<arrayEdges.size(); w++) {
                sortedArray.add(arrayEdges.get(w));
            }
        }

        Collections.sort(sortedArray, new ComparatorEdges());

        for(int i=0; i<sortedArray.size(); i++) if(i%2==0) sortedArray.remove(sortedArray.get(i));
        return sortedArray;
    }

    public Number getWeight(Vertice<V> v1, Vertice<V> v2) {
        ArrayList<Arco>a=new ArrayList<>();
        Arco arc=null;
        a=setNodi.get(v1.getElement());

        for(int i=0; i<a.size(); i++) {
            arc=a.get(i);
            if(arc.getSecondoNodo().getElement().equals(v2.getElement())) return arc.getPeso();
        }

        return -1; // ritorna -1 se l'arco non esiste
    }
}