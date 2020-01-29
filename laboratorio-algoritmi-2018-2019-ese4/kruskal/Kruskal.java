
package kruskal;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.Map;
import static javafx.scene.input.KeyCode.V;




public class Kruskal<V> {
    public Kruskal() {}

    public Grafo KruskalMST(Grafo g) throws InterruptedException {
        System.out.println("ENTRO IN KRUSKAL");
        Grafo gk=new Grafo(g.getType());

        ArrayList<Arco>sortedArray=g.getListEdges();
        UnionFindSet uf=new UnionFindSet();
        Iterator it=g.getMap().entrySet().iterator();

        while(it.hasNext()) {
            Map.Entry entry=(Map.Entry) it.next();
            uf.MakeSet(entry.getKey());
        }

        System.out.println("MAKE SET TERMINATO");

        for(int i=0; i<sortedArray.size(); i++) {

            Arco a=sortedArray.get(i);
            Nodo<V>nodo1=(Nodo<V>) uf.getMap().get(a.getPrimoNodo().getElement());
            Nodo<V>nodo2=(Nodo<V>) uf.getMap().get(a.getSecondoNodo().getElement());
            Nodo<V>root1=uf.find(nodo1);
            Nodo<V>root2=uf.find(nodo2);

            if(root1 !=root2) {
                gk.addNodo(a.getPrimoNodo().getElement());
                gk.addNodo(a.getSecondoNodo().getElement());
                gk.aggiungiArco(a.getPrimoNodo().getElement(), a.getSecondoNodo().getElement(), a.getPeso());
                uf.Union(root1, root2);
            }
        }


        return gk;
    }
}