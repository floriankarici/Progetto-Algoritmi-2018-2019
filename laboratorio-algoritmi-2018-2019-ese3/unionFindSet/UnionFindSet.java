package unionFindSet;

import java.util.HashMap;
import static javafx.scene.input.KeyCode.V;


public class UnionFindSet<V> {
    private HashMap<V,
    Nodo<V>>set=new HashMap<>();

    public UnionFindSet() {}

    public void MakeSet(V element) {
        Nodo<V>newNode=new Nodo(element);
        set.put(element, newNode);
    }

    
    public HashMap<V,
    Nodo<V>>getMap() {
        return this.set;
    }

    

    public void Union (Nodo<V> first_element, Nodo<V> second_element) {
        Nodo<V>parent1=find(first_element);
        Nodo<V>parent2=find(second_element);
        if(parent1==parent2) return;

        if(parent1.getRank()<=parent2.getRank()) {
            if(parent1.getRank()==parent2.getRank()) {
                parent2.setRank(1);

            }

            parent2.setParent(parent1);
        }else {
            parent1.setParent(parent2);
            parent1.setRank(1);
        }
    }

    public Nodo<V>find(Nodo<V> element) {
        Nodo<V>parent_element=element.getParent();

        if(parent_element==element) {
            return parent_element;
        }

        element.setParent(find(parent_element));
        return find(parent_element);
    }





}