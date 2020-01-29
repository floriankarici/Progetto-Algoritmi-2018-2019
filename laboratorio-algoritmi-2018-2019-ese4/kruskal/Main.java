package kruskal;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Iterator;
import java.util.Map;
import java.util.Set;

public class Main {

    public static double arrotonda(double peso){
        double result=Math.pow(10, 3);
        result=Math.floor(peso*result)/result;
        return result;
    }
    public static void main(String[] args) throws IOException, InterruptedException {
        
        Kruskal k=new Kruskal();
        Grafo g=new Grafo(true);
        Grafo gk = new Grafo(g.getType());
        String csvFile= "/Users/florian/Desktop/italian_dist_graph.csv";
        BufferedReader br=null;
        String line="";
        try{
            br=new BufferedReader(new FileReader(csvFile));
          
            while((line=br.readLine())!=null){
                
                String[] s=line.split(",");
                g.addNodo(s[0]);
                g.addNodo(s[1]);
                g.aggiungiArco(s[0], s[1], Double.parseDouble(s[2]));
                
            }
        }catch (FileNotFoundException e){
            e.printStackTrace();
        }
        System.out.println("LETTURA TERMINATA");


        gk=k.KruskalMST(g);
        double pesoTotale;
        pesoTotale = arrotonda(gk.getTotalWeight().doubleValue());
        System.out.println("NUMERO NODI FORESTA MINIMA: "+gk.getNumNode());

        if(gk.getType()){
            System.out.println("NUMERO ARCHI FORESTA MINIMA: "+gk.getNumEdges_n());
            System.out.println("PESO TOTALE FORESTA MINIMA: "+pesoTotale/1000+" KM");
        }
        else {
            System.out.println("NUMERO ARCHI FORESTA MINIMA: "+gk.getNumEdges_n()/2);
            System.out.println("PESO TOTALE FORESTA MINIMA: "+pesoTotale/2000+" KM");
        }
    }
    
}

