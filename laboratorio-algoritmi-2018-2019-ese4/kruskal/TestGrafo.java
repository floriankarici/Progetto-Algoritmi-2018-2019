package kruskal;

import java.util.ArrayList;
import static javafx.scene.input.KeyCode.V;
import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertTrue;


import kruskal.Vertice;
import kruskal.Arco;
import kruskal.Grafo;
import org.junit.Before;
import org.junit.Test;

public class TestGrafo {
    private String n1,
    n2,
    n3,
    n4;
    private Grafo g_diretto,
    g_indiretto;

    @Before 
    public void createGrafo() {
        g_diretto=new Grafo(true);
        g_indiretto=new Grafo(false);
        n1="Milano";
        n2="Torino";
        n3="Bologna";
        n4="Venezia";
    }

    @Test 
    public void directGraph() {
        assertTrue(g_diretto.getType());
        
    }

    @Test 
    public void indirectGraph() {
        assertFalse(g_indiretto.getType());
        
    }

    @Test 
    public void insertNode() {
        g_diretto.addNodo(n1);
        assertEquals(g_diretto.getMap().containsKey(n1), true);
        
    }

    @Test 
    public void insertEdge() {
        g_diretto.addNodo(n1);
        g_diretto.addNodo(n2);
        g_diretto.aggiungiArco(n1, n2, 100);
        ArrayList a=(ArrayList) g_diretto.getMap().get(n1);
        Arco arc=(Arco) a.get(0);
        Vertice v1=arc.getPrimoNodo();
        ArrayList a3=g_diretto.getVicini(v1);
        Vertice v2=arc.getSecondoNodo();
        assertEquals(a3.contains(v2), true);
        
    }

    @Test 
    public void insertEdgeInd() {
        g_indiretto.addNodo(n1);
        g_indiretto.addNodo(n2);
        g_indiretto.aggiungiArco(n1, n2, 100);
        ArrayList a=(ArrayList) g_indiretto.getMap().get(n1);
        Arco arc=(Arco) a.get(0);
        Vertice v1=arc.getPrimoNodo();
        ArrayList a3=g_indiretto.getVicini(v1);
        Vertice v2=arc.getSecondoNodo();
        ArrayList a4=g_indiretto.getVicini(v2);
        assertEquals(a3.contains(v2), true);
        assertEquals(a4.contains(v1), true);
        

    }

    @Test 
    public void deleteNode() {
        g_diretto.addNodo(n1);
        g_diretto.addNodo(n2);
        g_diretto.deleteNode(n2);
        assertEquals(g_diretto.getMap().containsKey(n2), false);
        
    }

    @Test 
    public void deleteEdge() {
        g_diretto.addNodo(n1);
        g_diretto.addNodo(n2);
        g_diretto.addNodo(n3);
        g_diretto.aggiungiArco(n1, n2, 100);
        g_diretto.aggiungiArco(n2, n3, 500);
        ArrayList a=(ArrayList) g_diretto.getMap().get(n2);
        Arco aTemp=(Arco) a.get(0);
        g_diretto.deleteEdge(n2, aTemp);
        assertEquals(g_diretto.arcoEsiste(aTemp), false);
        
    }
    @Test 
    public void getEdges() throws InterruptedException {
        g_diretto.addNodo(n1);
        g_diretto.addNodo(n2);
        g_diretto.addNodo(n3);
        g_diretto.aggiungiArco(n1, n2, 100);
        g_diretto.aggiungiArco(n2, n3, 500);
        ArrayList a=g_diretto.getListEdges();
        assertEquals(a.size(), 2);
        
    }

    @Test 
    public void deleteEdgeInd() {
        g_indiretto.addNodo(n1);
        g_indiretto.addNodo(n2);
        g_indiretto.addNodo(n3);
        g_indiretto.aggiungiArco(n1, n2, 100);
        g_indiretto.aggiungiArco(n2, n3, 500);
        ArrayList a=(ArrayList) g_indiretto.getMap().get(n2);
        Arco aTemp=(Arco) a.get(0);
        g_indiretto.deleteEdge(n2, aTemp);
        ArrayList a2=(ArrayList) g_indiretto.getMap().get(n3);
        Arco aTemp2=(Arco) a2.get(0);
        g_indiretto.deleteEdge(n3, aTemp2);
        assertEquals(g_indiretto.arcoEsiste(aTemp), false);
        assertEquals(g_indiretto.arcoEsiste(aTemp2), false);
        
    }

    @Test 
    public void contEdges() {
        g_diretto.addNodo(n1);
        g_diretto.addNodo(n2);
        g_diretto.addNodo(n3);
        g_diretto.aggiungiArco(n1, n2, 100);
        g_diretto.aggiungiArco(n2, n3, 500);
        assertEquals(g_diretto.getNumEdges_n(), 2);
        
    }

    @Test 
    public void contEdgesInd() {
        g_indiretto.addNodo(n1);
        g_indiretto.addNodo(n2);
        g_indiretto.addNodo(n3);
        g_indiretto.aggiungiArco(n1, n2, 100);
        g_indiretto.aggiungiArco(n2, n3, 500);
        assertEquals(g_indiretto.getNumEdges_n(), 2);
        
    }

    @Test 
    public void totalWeight() {
        g_diretto.addNodo(n1);
        g_diretto.addNodo(n2);
        g_diretto.addNodo(n3);
        g_diretto.aggiungiArco(n1, n2, 100);
        g_diretto.aggiungiArco(n2, n3, 500);
        assertEquals(g_diretto.getTotalWeight().intValue(), 600);
        
    }

    @Test 
    public void totalWeightInd() {
        g_indiretto.addNodo(n1);
        g_indiretto.addNodo(n2);
        g_indiretto.addNodo(n3);
        g_indiretto.aggiungiArco(n1, n2, 100);
        g_indiretto.aggiungiArco(n2, n3, 500);
        assertEquals(g_indiretto.getTotalWeight().intValue(), 600);
        
    }

    @Test
     public void nodesWeight() {
        g_diretto.addNodo(n1);
        g_diretto.addNodo(n2);
        g_diretto.aggiungiArco(n1, n2, 100);
        ArrayList a=(ArrayList) g_diretto.getMap().get(n1);
        Arco arc=(Arco) a.get(0);
        Vertice v1=(Vertice) arc.getPrimoNodo();
        ArrayList a2=(ArrayList) g_diretto.getMap().get(n1);
        Arco arc2=(Arco) a2.get(0);
        Vertice v2=(Vertice) arc.getSecondoNodo();
        assertEquals(g_diretto.getWeight(v1, v2), 100);
        
    }

    

    @Test 
    public void existsEdge() {
        g_diretto.addNodo(n1);
        g_diretto.addNodo(n2);
        g_diretto.aggiungiArco(n1, n2, 100);
        assertEquals(g_diretto.aggiungiArco(n1, n2, 100), false);
        
    }

    @Test 
    public void existsEdgeInd() {
        g_indiretto.addNodo(n1);
        g_indiretto.addNodo(n2);
        g_indiretto.aggiungiArco(n1, n2, 100);
        assertEquals(g_indiretto.aggiungiArco(n1, n2, 100), false);
        assertEquals(g_indiretto.aggiungiArco(n2, n1, 100), false);
        
    }


    @Test 
    public void getNumNode() {
        g_diretto.addNodo(n1);
        g_diretto.addNodo(n2);
        g_diretto.addNodo(n3);
        assertEquals(g_diretto.getNumNode(), 3);
        
    }



    @Test 
    public void getNodi() {
        g_diretto.addNodo(n1);
        g_diretto.addNodo(n2);
        g_diretto.addNodo(n3);
        g_diretto.addNodo(n4);
        ArrayList a=g_diretto.getNodi();
        assertEquals(a.contains(n1), true);
        assertEquals(a.contains(n2), true);
        assertEquals(a.contains(n3), true);
        assertEquals(a.contains(n4), true);
        

    }


    @Test 
    public void getEdgesInd() throws InterruptedException {
        g_indiretto.addNodo(n1);
        g_indiretto.addNodo(n2);
        g_indiretto.addNodo(n3);
        g_indiretto.aggiungiArco(n1, n2, 100);
        g_indiretto.aggiungiArco(n2, n3, 500);
        ArrayList a=g_indiretto.getListEdges();
        assertEquals(a.size(), 2);
        System.out.println("eseguiti tutti i test");
    }
}