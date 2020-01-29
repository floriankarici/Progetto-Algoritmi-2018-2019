
package kruskal;

import java.util.Comparator;


public  class ComparatorEdges implements Comparator<Arco> {

   @Override
    public int compare(Arco o1, Arco o2) {
      return (int) (o1.getPeso().doubleValue()-o2.getPeso().doubleValue());
       
    }
    
}
