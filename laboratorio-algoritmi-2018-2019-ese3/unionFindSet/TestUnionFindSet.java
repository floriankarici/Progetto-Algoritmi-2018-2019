package unionFindSet;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertTrue;
import org.junit.Before;
import org.junit.Test;


public class TestUnionFindSet {
    private UnionFindSet uf;
    private Integer i1=1,
    i2=2,
    i3=3;


    @Before
    public void createUnion() {
        uf=new UnionFindSet();

    }

    @Test 
    public void insert_element() {
        uf.MakeSet(i1);
        assertEquals(uf.getMap().containsKey(i1), true);
    }

    @Test 
    public void find_element() {
        uf.MakeSet(i1);
        Nodo < Integer>n=new Nodo <>(i1);
        assertEquals(uf.find(n).getElement(), i1);
    }

    public void union_element() {
        uf.MakeSet(i1);
        uf.MakeSet(i2);
        Nodo < Integer>n1=new Nodo <>(i1);
        Nodo < Integer>n2=new Nodo <>(i2);
        uf.Union(n1, n2);
        assertEquals(n1.getParent().getElement(), n2.getParent().getElement());

    }
}