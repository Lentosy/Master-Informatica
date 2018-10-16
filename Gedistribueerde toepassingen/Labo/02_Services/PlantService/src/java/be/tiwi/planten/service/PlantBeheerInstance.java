package be.tiwi.planten.service;

import be.tiwi.planten.Plant;
import be.tiwi.planten.impl.PlantenGeheugenDB;
import java.io.IOException;
import java.nio.file.FileSystems;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.stream.Stream;


public class PlantBeheerInstance {
    private static PlantenGeheugenDB pb;
    
    public static PlantenGeheugenDB GetInstance(){
        if(pb == null){
            // in string gestopt omda ik echt nie me exceptions wil bezig zijn (bestanden inlezen enz)
            String data =   "Vuurpijl;geel;9.50;vuurpijl.jpg\n" +
                            "Daglelie 'Stella de Oro';geel;5.95;daglelie.jpg\n" +
                            "Kokardebloem 'Kobold';geel;10.99;kokardebloem.jpg\n" +
                            "Dubbelbloemige Primula mix;geel;10.50;primula.jpg\n" +
                            "Kleine maagdenpalm;blauw;9.75;maagdenpalm.jpg\n" +
                            "Iris aucheri;blauw;7.95;iris.jpg\n" +
                            "Lavendel 'Munstead' en 'Loddon Pink';blauw;18.95;lavendel.jpg\n" +
                            "Riddersporen;blauw;7.95;ridderspoor.jpg\n" +
                            "Campanula 'Emerald';blauw;9.95;campanula.gif\n" +
                            "Aquilegia vulgaris var stellata 'Black Barlow';blauw;8.50;akelei.jpg\n" +
                            "Lenteroos 'Apricot Beauty';oranje;9.75;lenteroos.jpg\n" +
                            "Zijdeplant;oranje;8.95;zijdeplant.jpg\n" +
                            "Maskerbloem 'Orange Glow';oranje;8.95;maskerbloem.jpg\n" +
                            "Lampionplant;oranje;5.75;lampionplant.jpg\n" +
                            "Iris pallida 'Variegata';paars;11.75;irisPaars.jpg\n" +
                            "Flox 'Laura';paars;4.95;flox.jpg\n" +
                            "Bonte graslelie;paars;9.95;graslelie.jpg\n" +
                            "Rode zonnehoed;paars;7.75;zonnehoed.jpg\n" +
                            "Flox 'Lilac Time';paars;4.95;floxPaars.jpg\n" +
                            "Kievitsbloem;paars;6.75;kievitsbloem.jpg\n" +
                            "Fuchsia Riccartonii;paars;11.75;fuchsia.jpg\n" +
                            "Elfenbloem;rood;10.95;elfenbloem.jpg\n" +
                            "Papaver Turkenlouis;rood;8.95;papaver.jpg\n" +
                            "Purperrode klaver;rood;7.95;klaver.jpg\n" +
                            "Griekse malva;rood;9.75;malva.jpg";
            pb = new PlantenGeheugenDB();
            for(String line : data.split("\n")){
                String[] attributes = line.split(";");
                Plant p = new Plant();
                p.setNaam(attributes[0]);
                p.setKleur(attributes[1]);
                p.setPrijs(Double.parseDouble(attributes[2]));
                p.setBestandAfbeelding(attributes[3]);
                pb.voegPlantToe(p);
            }
        }
        return pb;
    }
}
